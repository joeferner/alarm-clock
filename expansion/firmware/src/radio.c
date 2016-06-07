
#include "radio.h"
#include <si473x/si473x.h>
#include <utils/utils.h>
#include <utils/time.h>

SI473X _si473x;

HAL_StatusTypeDef radio_setup() {
  HAL_StatusTypeDef ret;
  SI473X_Status status;
  
  DEBUG_OUT("BEGIN radio_setup\n");
  
  _si473x.spi = &hspi1;
  _si473x.csPort = SI473X_CS_PORT;
  _si473x.csPin = SI473X_CS_PIN;
  _si473x.resetPort = SI473X_RESET_PORT;
  _si473x.resetPin = SI473X_RESET_PIN;
  _si473x.interruptPort = SI473X_INT_PORT;
  _si473x.interruptPin = SI473X_INT_PIN;
  // TODO: SPI Disable: _si473x.gpo1Port = SPI1_MISO_PORT;
  // TODO: SPI Disable: _si473x.gpo1Pin = SPI1_MISO_PIN;
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
  sleep_ms(10);
  
  SI473X_GetRevResponse getRevResponse;
  DEBUG_OUT("SI473X_getRev\n");
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
  sleep_ms(10);

  uint16_t gpoien = SI473X_PROP_GPO_IEN_CTSIEN
    | SI473X_PROP_GPO_IEN_ERRIEN
    | SI473X_PROP_GPO_IEN_RSQIEN
    | SI473X_PROP_GPO_IEN_STCIEN;
  DEBUG_OUT("SI473X_setProperty\n");
  ret = SI473X_setProperty(&_si473x, SI473X_PROP_GPO_IEN, gpoien, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_setProperty failed: 0x%02x\n", ret);
    return ret;
  }
  sleep_ms(10);
  
  uint16_t freq = SI473X_fmFrequencyToUint16(101.1 * 1000000);
  DEBUG_OUT("SI473X_fmTuneFreq\n");
  ret = SI473X_fmTuneFreq(&_si473x, false, false, freq, 0, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneFreq failed: 0x%02x\n", ret);
    return ret;
  }
  sleep_ms(10);
  
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
    sleep_ms(100);
  }
  
  SI473X_FmTuneStatusResponse tuneStatus;
  DEBUG_OUT("SI473X_fmTuneStatus\n");
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
  sleep_ms(10);
  
  DEBUG_OUT("END radio_setup\n");
  
  return HAL_OK;
}

void radio_tick() {
  SI473X_tick(&_si473x);
}


