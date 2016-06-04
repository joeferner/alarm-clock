
#include "radio.h"
#include <si473x/si473x.h>

SI473X _si473x;

HAL_StatusTypeDef radio_setup() {
  HAL_StatusTypeDef ret;
  
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

  ret = SI473X_powerUp(&_si473x, SI473X_POWER_UP_ARG1_CTSIEN, 0);
  if (ret != HAL_OK) {
    DEBUG_OUT("SI473X_powerUp failed: 0x%02x\n", ret);
    return ret;
  }
  
  return HAL_OK;
}

void radio_tick() {
  SI473X_tick(&_si473x);
}


