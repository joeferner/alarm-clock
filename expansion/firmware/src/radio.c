
#include "radio.h"
#include <si473x/si473x.h>

SI473X _si473x;

HAL_StatusTypeDef radio_setup() {
  HAL_StatusTypeDef ret;
  SI473X_Status status;
  
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

  uint8_t powerUpArg1 = SI473X_POWER_UP_ARG1_FUNC_RX | SI473X_POWER_UP_ARG1_CTSIEN;
  uint8_t powerUpArg2 = SI473X_POWER_UP_ARG2_OPMODE_ANALOG_AUDIO_OUT;
  ret = SI473X_powerUp(&_si473x, powerUpArg1, powerUpArg2, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_powerUp failed: 0x%02x\n", ret);
    return ret;
  }

  uint16_t freq = SI473X_fmFrequencyToUint16(101.1);
  ret = SI473X_fmTuneFreq(&_si473x, false, false, freq, 0, &status);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_fmTuneFreq failed: 0x%02x\n", ret);
    return ret;
  }
  
  return HAL_OK;
}

void radio_tick() {
  SI473X_tick(&_si473x);
}


