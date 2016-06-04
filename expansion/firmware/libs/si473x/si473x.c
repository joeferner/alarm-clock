
#include "si473x.h"
#include <utils/time.h>
#include <utils/utils.h>
#include <string.h>

// TODO: SPI Disable: Let's try initializing without disabling SPI first

#define SI473X_SPI_CONTROL_WRITE_CMD   0x48
#define SI473X_SPI_CONTROL_READ1_SDIO  0x80
#define SI473X_SPI_CONTROL_READ16_SDIO 0xc0
#define SI473X_SPI_CONTROL_READ1_GPO1  0xa0
#define SI473X_SPI_CONTROL_READ16_GPO1 0xe0

void _SI473X_assertReset(SI473X* si473x);
void _SI473X_deassertReset(SI473X* si473x);
void _SI473X_assertCS(SI473X* si473x);
void _SI473X_deassertCS(SI473X* si473x);
HAL_StatusTypeDef _SI473X_statusToHALStatus(SI473X_Status* status);
HAL_StatusTypeDef _SI473X_spiWriteCommand(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength);
HAL_StatusTypeDef _SI473X_read1(SI473X* si473x, SI473X_Status* status);
HAL_StatusTypeDef _SI473X_read16(SI473X* si473x, uint8_t* rxBuffer, uint8_t rxBufferLength);
HAL_StatusTypeDef _SI473X_spiWriteCommandRead1(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength, SI473X_Status* status);
HAL_StatusTypeDef _SI473X_spiWriteCommandRead16(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength);

HAL_StatusTypeDef SI473X_setup(SI473X* si473x) {
  // TODO: SPI Disable: GPIO_InitTypeDef gpo1Gpio;
  
  // TODO: SPI Disable: HAL_SPI_DeInit(si473x->spi);
  _SI473X_deassertCS(si473x);
  sleep_ms(10);
  _SI473X_assertReset(si473x);
  
  // Set SI473X GPO1 pin to input and pull up to enable SPI mode
  // TODO: SPI Disable: gpo1Gpio.Pin = si473x->gpo1Pin;
  // TODO: SPI Disable: gpo1Gpio.Mode = GPIO_MODE_INPUT;
  // TODO: SPI Disable: gpo1Gpio.Pull = GPIO_PULLUP;
  // TODO: SPI Disable: HAL_GPIO_Init(si473x->gpo1Port, &gpo1Gpio);
  
  _SI473X_deassertReset(si473x);
  sleep_ms(10);
  
  // TODO: SPI Disable: HAL_GPIO_DeInit(si473x->gpo1Port, &gpo1Gpio);
  // TODO: SPI Disable: HAL_SPI_Init(si473x->spi);

  return HAL_OK;
}

void SI473X_tick(SI473X* si473x) {
}

void _SI473X_assertReset(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->resetPort, si473x->resetPin, GPIO_PIN_RESET);
}

void _SI473X_deassertReset(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->resetPort, si473x->resetPin, GPIO_PIN_SET);
}

void _SI473X_assertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_RESET);
}

void _SI473X_deassertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_SET);
}

HAL_StatusTypeDef _SI473X_statusToHALStatus(SI473X_Status* status) {
  return (status->error) ? HAL_ERROR : HAL_OK;
}

HAL_StatusTypeDef _SI473X_spiWriteCommand(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength) {
  int i;
  uint8_t tx[17];
  uint8_t rx[17];
  
  tx[0] = SI473X_SPI_CONTROL_WRITE_CMD;
  tx[1] = cmd;
  for (i = 2; i < argsLength + 2; i++) {
    tx[i] = args[i - 2];
  }
  for (; i < 17; i++) {
    tx[i] = 0;
  }
  
  HAL_StatusTypeDef spiTxRxResult = HAL_SPI_TransmitReceive(si473x->spi, tx, rx, 9, SI473X_SPI_TIMEOUT);
  if (spiTxRxResult != HAL_OK) {
    SI473X_DEBUG_OUT("spiWriteCommand: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  return spiTxRxResult;
}

HAL_StatusTypeDef _SI473X_read1(SI473X* si473x, SI473X_Status* status) {
  uint8_t tx[2];
  uint8_t rx[2];

  tx[0] = SI473X_SPI_CONTROL_READ1_GPO1;
  tx[1] = 0x00;
  HAL_StatusTypeDef spiTxRxResult = HAL_SPI_TransmitReceive(si473x->spi, tx, rx, 2, SI473X_SPI_TIMEOUT);
  if (spiTxRxResult == HAL_OK) {
    *((uint8_t*)status) = rx[1];
    if (status->error) {
      SI473X_DEBUG_OUT("read1: error\n");
    }
  } else {
    SI473X_DEBUG_OUT("read1: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  
  return spiTxRxResult;
}

HAL_StatusTypeDef _SI473X_read16(SI473X* si473x, uint8_t* rxBuffer, uint8_t rxBufferLength) {
  uint8_t tx[17];
  uint8_t rx[17];

  tx[0] = SI473X_SPI_CONTROL_READ16_GPO1;
  memset(tx + 1, 0, 16);
  HAL_StatusTypeDef spiTxRxResult = HAL_SPI_TransmitReceive(si473x->spi, tx, rx, 17, SI473X_SPI_TIMEOUT);
  if (spiTxRxResult == HAL_OK) {
    memcpy(rxBuffer, rx + 1, rxBufferLength);
    if (rxBuffer[0] & SI473X_STATUS_ERR) {
      SI473X_DEBUG_OUT("read16: error: 0x%02x\n", rxBuffer[0]);
    }
  } else {
    SI473X_DEBUG_OUT("read16: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  
  return spiTxRxResult;
}

HAL_StatusTypeDef _SI473X_spiWriteCommandRead1(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength, SI473X_Status* status) {
  HAL_StatusTypeDef ret;
  
  _SI473X_assertCS(si473x);
  ret = _SI473X_spiWriteCommand(si473x, cmd, args, argsLength);
  if (ret == HAL_OK) {
    ret = _SI473X_read1(si473x, status);
  }  
  _SI473X_deassertCS(si473x);
  
  return ret;
}

HAL_StatusTypeDef _SI473X_spiWriteCommandRead16(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength) {
  HAL_StatusTypeDef ret;
  
  _SI473X_assertCS(si473x);
  ret = _SI473X_spiWriteCommand(si473x, cmd, args, argsLength);
  if (ret == HAL_OK) {
    ret = _SI473X_read16(si473x, (uint8_t*)rxBuffer, rxBufferLength);
  }  
  _SI473X_deassertCS(si473x);
  
  return ret;
}

HAL_StatusTypeDef SI473X_powerUp(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_Status* status) {
  HAL_StatusTypeDef ret;
  uint8_t args[2] = { arg1, arg2 };
  if (testBits(arg1, SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID)) {
    SI473X_DEBUG_OUT("invalid call, use SI473X_powerUpQueryLibraryId\n");
    return HAL_ERROR;
  } else {
    ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_POWER_UP, args, 2, status);
  }
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_powerUpQueryLibraryId(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_PowerUpQueryLibraryIdResponse* response) {
  HAL_StatusTypeDef ret;
  uint8_t args[2] = { arg1, arg2 };
  if (testBits(arg1, SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID)) {
    ret = _SI473X_spiWriteCommandRead16(si473x, SI473X_CMD_POWER_UP, args, 2, response, sizeof(SI473X_PowerUpQueryLibraryIdResponse));
  } else {
    SI473X_DEBUG_OUT("invalid call, use SI473X_powerUp\n");
    return HAL_ERROR;
  }
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&response->status);
}

HAL_StatusTypeDef SI473X_getRev(SI473X* si473x, SI473X_GetRevResponse* response) {
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(si473x, SI473X_CMD_GET_REV, NULL, 0, response, sizeof(response));
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&response->status);
}

HAL_StatusTypeDef SI473X_powerDown(SI473X* si473x, SI473X_Status* status) {
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_POWER_UP, NULL, 0, status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}
