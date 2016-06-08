
#include "radio.h"
#include <si473x/si473x.h>
#include <utils/utils.h>
#include <utils/time.h>

SI473X _si473x;

HAL_StatusTypeDef radio_setup() {
  HAL_StatusTypeDef ret;
  SI473X_Status status;
  
  DEBUG_OUT("BEGIN radio_setup\n");
  
  _si473x.i2c = &hi2c1;
  _si473x.resetPort = SI473X_RESET_PORT;
  _si473x.resetPin = SI473X_RESET_PIN;
  _si473x.interruptPort = SI473X_INT_PORT;
  _si473x.interruptPin = SI473X_INT_PIN;
  ret = SI473X_setup(&_si473x);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_setup failed: 0x%02x\n", ret);
    return ret;
  }

  DEBUG_OUT("SI473X_powerUp\n");
  uint8_t powerUpArg1 = SI473X_POWER_UP_ARG1_FUNC_RX | SI473X_POWER_UP_ARG1_CTSIEN | SI473X_POWER_UP_ARG1_GPO2OEN;
  uint8_t powerUpArg2 = SI473X_POWER_UP_ARG2_OPMODE_ANALOG_AUDIO_OUT;
  ret = SI473X_powerUp(&_si473x, powerUpArg1, powerUpArg2, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_powerUp failed: 0x%02x\n", ret);
    return ret;
  }
    
  SI473X_GetRevResponse getRevResponse;
  DEBUG_OUT("SI473X_getRev\n");
  SI473X_waitForCTS(&_si473x);
  ret = SI473X_getRev(&_si473x, &getRevResponse);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_getRev failed: 0x%02x\n", ret);
    return ret;
  }
  DEBUG_OUT("rev        partNumber: 0x%02x\n", getRevResponse.partNumber);
  DEBUG_OUT("rev           fwMajor: 0x%02x\n", getRevResponse.fwMajor);
  DEBUG_OUT("rev           fwMinor: 0x%02x\n", getRevResponse.fwMinor);
  DEBUG_OUT("rev             patch: 0x%04x\n", getRevResponse.patch);
  DEBUG_OUT("rev componentMajorRev: 0x%02x\n", getRevResponse.componentMajorRev);
  DEBUG_OUT("rev componentMinorRev: 0x%02x\n", getRevResponse.componentMinorRev);
  DEBUG_OUT("rev           chipRev: 0x%02x\n", getRevResponse.chipRev);

  uint16_t gpoien = SI473X_PROP_GPO_IEN_CTSIEN
    | SI473X_PROP_GPO_IEN_ERRIEN
    | SI473X_PROP_GPO_IEN_RSQIEN
    | SI473X_PROP_GPO_IEN_STCIEN;
  DEBUG_OUT("SI473X_setProperty gpio ien\n");
  SI473X_waitForCTS(&_si473x);
  ret = SI473X_setProperty(&_si473x, SI473X_PROP_GPO_IEN, gpoien, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_setProperty gpio ien failed: 0x%02x\n", ret);
    return ret;
  }

  DEBUG_OUT("SI473X_setProperty volume\n");
  SI473X_waitForCTS(&_si473x);
  ret = SI473X_setProperty(&_si473x, SI473X_PROP_RX_VOLUME, 63, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_setProperty volume failed: 0x%02x\n", ret);
    return ret;
  }

  uint16_t freq = SI473X_fmFrequencyToUint16(101100000);
  DEBUG_OUT("SI473X_fmTuneFreq\n");
  ret = SI473X_fmTuneFreq(&_si473x, false, false, freq, 0, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneFreq failed: 0x%02x\n", ret);
    return ret;
  }
  
  /*
  DEBUG_OUT("SI473X_fmSeekStart\n");
  SI473X_waitForCTS(&_si473x);
  ret = SI473X_fmSeekStart(&_si473x, true, true, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmSeekStart failed: 0x%02x\n", ret);
    return ret;
  }
  */
  
  while(1) {
    ret = SI473X_getIntStatus(&_si473x, &status);
    if (ret != HAL_OK) {
      DEBUG_OUT("SI473X_getIntStatus failed: 0x%02x\n", ret);
      return ret;
    }
    if (testBits(status, SI473X_STATUS_STCINT)) {
      break;
    }
    DEBUG_OUT("SI473X_getIntStatus: 0x%02x\n", status);
    sleep_ms(1000);
  }

  //sleep_ms(3000);
  
  SI473X_FmTuneStatusResponse tuneStatus;
  DEBUG_OUT("SI473X_fmTuneStatus\n");
  SI473X_waitForCTS(&_si473x);
  ret = SI473X_fmTuneStatus(&_si473x, false, true, &tuneStatus);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneStatus failed: 0x%02x\n", ret);
    return ret;
  }
  DEBUG_OUT("fmTuneStatus         resp1: 0x%02x\n", tuneStatus.resp1);
  DEBUG_OUT("fmTuneStatus readFrequency: 0x%04x\n", tuneStatus.readFrequency);
  DEBUG_OUT("fmTuneStatus          rssi: 0x%02x\n", tuneStatus.rssi);
  DEBUG_OUT("fmTuneStatus           snr: 0x%04x\n", tuneStatus.snr);
  DEBUG_OUT("fmTuneStatus    readAntCap: 0x%02x\n", tuneStatus.readAntCap);
  
  DEBUG_OUT("END radio_setup\n");
  
  return HAL_OK;
}

void radio_tick() {
  SI473X_tick(&_si473x);
}

HAL_StatusTypeDef radio_seekUp() {
  SI473X_Status status;
  
  DEBUG_OUT("SI473X_fmSeekStart\n");
  SI473X_waitForCTS(&_si473x);
  HAL_StatusTypeDef ret = SI473X_fmSeekStart(&_si473x, true, true, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmSeekStart failed: 0x%02x\n", ret);
  }
  return ret;
}

HAL_StatusTypeDef radio_status() {
  SI473X_FmTuneStatusResponse tuneStatus;
  DEBUG_OUT("SI473X_fmTuneStatus\n");
  SI473X_waitForCTS(&_si473x);
  HAL_StatusTypeDef ret = SI473X_fmTuneStatus(&_si473x, false, true, &tuneStatus);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneStatus failed: 0x%02x\n", ret);
    return ret;
  }
  DEBUG_OUT("fmTuneStatus         resp1: 0x%02x\n", tuneStatus.resp1);
  DEBUG_OUT("fmTuneStatus readFrequency: 0x%04x\n", tuneStatus.readFrequency);
  DEBUG_OUT("fmTuneStatus          rssi: 0x%02x\n", tuneStatus.rssi);
  DEBUG_OUT("fmTuneStatus           snr: 0x%04x\n", tuneStatus.snr);
  DEBUG_OUT("fmTuneStatus    readAntCap: 0x%02x\n", tuneStatus.readAntCap);
  return ret;
}

HAL_StatusTypeDef radio_tune(uint32_t frequency) {
  SI473X_Status status;
  uint16_t freq = SI473X_fmFrequencyToUint16(frequency);
  DEBUG_OUT("SI473X_fmTuneFreq\n");
  HAL_StatusTypeDef ret = SI473X_fmTuneFreq(&_si473x, false, false, freq, 0, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneFreq failed: 0x%02x\n", ret);
  }
  return ret;
}

