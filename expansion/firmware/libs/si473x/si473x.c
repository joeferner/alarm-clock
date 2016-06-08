
#include "si473x.h"
#include <utils/time.h>
#include <utils/utils.h>
#include <string.h>

#ifdef SI473X_SPI
#define SI473X_SPI_CONTROL_WRITE_CMD   0x48
#define SI473X_SPI_CONTROL_READ1_SDIO  0x80
#define SI473X_SPI_CONTROL_READ16_SDIO 0xc0
#define SI473X_SPI_CONTROL_READ1_GPO1  0xa0
#define SI473X_SPI_CONTROL_READ16_GPO1 0xe0
#endif

void _SI473X_assertReset(SI473X* si473x);
void _SI473X_deassertReset(SI473X* si473x);
void _SI473X_assertCS(SI473X* si473x);
void _SI473X_deassertCS(SI473X* si473x);
HAL_StatusTypeDef _SI473X_statusToHALStatus(SI473X_Status* status);
HAL_StatusTypeDef _SI473X_writeCommand(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength);
HAL_StatusTypeDef _SI473X_read1(SI473X* si473x, SI473X_Status* status);
HAL_StatusTypeDef _SI473X_read16(SI473X* si473x, uint8_t* rxBuffer, uint8_t rxBufferLength);
HAL_StatusTypeDef _SI473X_writeCommandRead1(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, SI473X_Status* status);
HAL_StatusTypeDef _SI473X_writeCommandRead16(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength);

#ifdef SI473X_SPI
HAL_StatusTypeDef _SI473X_spiTxRx(SI473X* si473x, uint8_t* tx, uint8_t* rx, uint8_t length);
#endif

HAL_StatusTypeDef SI473X_setup(SI473X* si473x) {
#ifdef SI473X_SPI
  GPIO_InitTypeDef gpo1Gpio;
  GPIO_InitTypeDef gpo2Gpio;
  
  HAL_SPI_DeInit(si473x->spi);
  HAL_GPIO_DeInit(si473x->gpo1Port, si473x->gpo1Pin);
  HAL_GPIO_DeInit(si473x->interruptPort, si473x->interruptPin);
  
  _SI473X_deassertCS(si473x);
  sleep_ms(10);
  _SI473X_assertReset(si473x);
  
  // Set SI473X GPO1 and GPO2 pin to output and pull up to enable SPI mode
  gpo1Gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpo1Gpio.Pin = si473x->gpo1Pin;
  gpo1Gpio.Pull = GPIO_NOPULL;
  gpo1Gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(si473x->gpo1Port, &gpo1Gpio);

  gpo2Gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpo2Gpio.Pin = si473x->interruptPin;
  gpo2Gpio.Pull = GPIO_NOPULL;
  gpo2Gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(si473x->interruptPort, &gpo2Gpio);

  HAL_GPIO_WritePin(si473x->gpo1Port, si473x->gpo1Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(si473x->interruptPort, si473x->interruptPin, GPIO_PIN_SET);
  
  sleep_ms(10);
  _SI473X_deassertReset(si473x);
  sleep_ms(10);
  
  gpo1Gpio.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(si473x->gpo1Port, &gpo1Gpio);

  gpo2Gpio.Mode = GPIO_MODE_IT_RISING;
  HAL_GPIO_Init(si473x->interruptPort, &gpo2Gpio);

  HAL_GPIO_DeInit(si473x->gpo1Port, si473x->gpo1Pin);
  HAL_SPI_Init(si473x->spi);
#endif
  
#ifdef SI473X_I2C
  sleep_ms(10);
  _SI473X_assertReset(si473x);

  sleep_ms(10);
  _SI473X_deassertReset(si473x);
  sleep_ms(10);
#endif
  
  return HAL_OK;
}

void SI473X_tick(SI473X* si473x) {
}

uint16_t SI473X_fmFrequencyToUint16(uint32_t frequency) {
  uint16_t f = frequency / 10000;
  // TODO round to 50kHz?
  return f;
}

void _SI473X_assertReset(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->resetPort, si473x->resetPin, GPIO_PIN_RESET);
}

void _SI473X_deassertReset(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->resetPort, si473x->resetPin, GPIO_PIN_SET);
}

#ifdef SI473X_SPI
void _SI473X_assertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_RESET);
}

void _SI473X_deassertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_SET);
}
#endif

HAL_StatusTypeDef _SI473X_statusToHALStatus(SI473X_Status* status) {
  return testBits(*status, SI473X_STATUS_ERR) ? HAL_ERROR : HAL_OK;
}

#ifdef SI473X_SPI
HAL_StatusTypeDef _SI473X_spiTxRx(SI473X* si473x, uint8_t* tx, uint8_t* rx, uint8_t length) {
  HAL_StatusTypeDef ret;
  uint8_t i;
  _SI473X_assertCS(si473x);
  sleep_us(1);
  for (i = 0; i < length; i++) {
    ret = HAL_SPI_TransmitReceive(si473x->spi, tx + i, rx + i, 1, SI473X_SPI_TIMEOUT);
    if (ret != HAL_OK) {
      return ret;
    }
    sleep_us(1);
  }
  _SI473X_deassertCS(si473x);
  return HAL_OK;
}
#endif

HAL_StatusTypeDef _SI473X_writeCommand(SI473X* si473x, uint8_t cmd, uint8_t* args, uint8_t argsLength) {
#ifdef SI473X_SPI
  int i;
  uint8_t tx[9];
  uint8_t rx[9];
  
  tx[0] = SI473X_SPI_CONTROL_WRITE_CMD;
  tx[1] = cmd;
  for (i = 2; i < argsLength + 2; i++) {
    tx[i] = args[i - 2];
  }
  for (; i < 9; i++) {
    tx[i] = 0;
  }
  
  HAL_StatusTypeDef spiTxRxResult = _SI473X_spiTxRx(si473x, tx, rx, 9);
  if (spiTxRxResult != HAL_OK) {
    SI473X_DEBUG_OUT("writeCommand: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  return spiTxRxResult;
#endif
#ifdef SI473X_I2C
  int i;
  uint8_t tx[8];
  memset(tx, 0, 8);
  tx[0] = cmd;
  memcpy(tx + 1, args, argsLength);

  SI473X_DEBUG_OUT("writeCommand: tx: ");
  for (i = 0; i < 8; i++) {
    printf("0x%02x ", tx[i]);
  }
  printf("\n");
  
  HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(si473x->i2c, SI473X_I2C_ADDR, tx, 8, SI473X_SPI_TIMEOUT);
  if (ret != HAL_OK) {
    SI473X_DEBUG_OUT("writeCommand: tx error: 0x%02x\n", ret);
  }
  return ret;
#endif
}

HAL_StatusTypeDef _SI473X_read1(SI473X* si473x, SI473X_Status* status) {
#ifdef SI473X_SPI
  uint8_t tx[2];
  uint8_t rx[2];

  tx[0] = SI473X_SPI_CONTROL_READ1_GPO1;
  tx[1] = 0x00;
  HAL_StatusTypeDef spiTxRxResult = _SI473X_spiTxRx(si473x, tx, rx, 2);
  if (spiTxRxResult == HAL_OK) {
    *((uint8_t*)status) = rx[1];
    if (testBits(*status, SI473X_STATUS_ERR)) {
      SI473X_DEBUG_OUT("read1: error 0x%02x\n", *status);
    }
  } else {
    SI473X_DEBUG_OUT("read1: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  
  return spiTxRxResult;
#endif
#ifdef SI473X_I2C
  uint8_t rx[1];
  HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(si473x->i2c, SI473X_I2C_ADDR, rx, 1, SI473X_SPI_TIMEOUT);
  if (ret == HAL_OK) {
    *((uint8_t*)status) = rx[0];
    SI473X_DEBUG_OUT("read1: rx: 0x%02x\n", *((uint8_t*)status));
  } else {
    SI473X_DEBUG_OUT("read1: rx error: 0x%02x\n", ret);
  }
  return ret;
#endif
}

HAL_StatusTypeDef _SI473X_read16(SI473X* si473x, uint8_t* rxBuffer, uint8_t rxBufferLength) {
#ifdef SI473X_SPI
  uint8_t tx[17];
  uint8_t rx[17];

  memset(tx, 0, 17);
  tx[0] = SI473X_SPI_CONTROL_READ16_GPO1;
  HAL_StatusTypeDef spiTxRxResult = _SI473X_spiTxRx(si473x, tx, rx, 17);
  if (spiTxRxResult == HAL_OK) {
    memcpy(rxBuffer, rx + 1, rxBufferLength);
  } else {
    SI473X_DEBUG_OUT("read16: tx/rx error: 0x%02x\n", spiTxRxResult);
  }
  
  return spiTxRxResult;
#endif
#ifdef SI473X_I2C
  int i;
  uint8_t rx[16];
  HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(si473x->i2c, SI473X_I2C_ADDR, rx, 16, SI473X_SPI_TIMEOUT);
  if (ret == HAL_OK) {
    memcpy(rxBuffer, rx, rxBufferLength);
    SI473X_DEBUG_OUT("read16: rx: ");
    for (i = 0; i < 16; i++) {
      printf("0x%02x ", rx[i]);
    }
    printf("\n");
  } else {
    SI473X_DEBUG_OUT("read16: rx error: 0x%02x\n", ret);
  }
  return ret;
#endif
}

HAL_StatusTypeDef _SI473X_writeCommandRead1(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, SI473X_Status* status) {
  HAL_StatusTypeDef ret;
  
  ret = _SI473X_writeCommand(si473x, cmd, (uint8_t*)args, argsLength);
  if (ret == HAL_OK) {
    sleep_us(100);
    ret = _SI473X_read1(si473x, status);
  }  
  
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef _SI473X_writeCommandRead16(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength) {
  HAL_StatusTypeDef ret;
  
  ret = _SI473X_writeCommand(si473x, cmd, (uint8_t*)args, argsLength);
  if (ret == HAL_OK) {
    sleep_us(100);
    ret = _SI473X_read16(si473x, (uint8_t*)rxBuffer, rxBufferLength);
  }  
  
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&((uint8_t*)rxBuffer)[0]);
}

HAL_StatusTypeDef SI473X_powerUp(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_Status* status) {
  SI473X_PowerUpArgs args;
  args.arg1 = arg1;
  args.arg2 = arg2;
  if (testBits(arg1, SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID)) {
    SI473X_DEBUG_OUT("invalid call, use SI473X_powerUpQueryLibraryId\n");
    return HAL_ERROR;
  } else {
    return _SI473X_writeCommandRead1(si473x, SI473X_CMD_POWER_UP, &args, sizeof(SI473X_PowerUpArgs), status);
  }
}

HAL_StatusTypeDef SI473X_powerUpQueryLibraryId(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_PowerUpQueryLibraryIdResponse* response) {
  SI473X_PowerUpArgs args;
  args.arg1 = arg1;
  args.arg2 = arg2;
  if (testBits(arg1, SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID)) {
    return _SI473X_writeCommandRead16(si473x, SI473X_CMD_POWER_UP, &args, sizeof(SI473X_PowerUpArgs), response, sizeof(SI473X_PowerUpQueryLibraryIdResponse));
  } else {
    SI473X_DEBUG_OUT("invalid call, use SI473X_powerUp\n");
    return HAL_ERROR;
  }
}

HAL_StatusTypeDef SI473X_getRev(SI473X* si473x, SI473X_GetRevResponse* response) {
  return _SI473X_writeCommandRead16(si473x, SI473X_CMD_GET_REV, NULL, 0, response, sizeof(response));
}

HAL_StatusTypeDef SI473X_powerDown(SI473X* si473x, SI473X_Status* status) {
  return _SI473X_writeCommandRead1(si473x, SI473X_CMD_POWER_DOWN, NULL, 0, status);
}

HAL_StatusTypeDef SI473X_setProperty(SI473X* si473x, uint16_t property, uint16_t value, SI473X_Status* status) {
  SI473X_SetPropertyArgs args;
  args.reserved = 0;
  args.property = SWAP_UINT16(property);
  args.value = SWAP_UINT16(value);
  return _SI473X_writeCommandRead1(si473x, SI473X_CMD_SET_PROPERTY, &args, sizeof(SI473X_SetPropertyArgs), status);
}

HAL_StatusTypeDef SI473X_getProperty(SI473X* si473x, uint16_t property, SI473X_GetPropertyReponse* response) {
  SI473X_GetPropertyArgs args;
  args.reserved = 0;
  args.property = SWAP_UINT16(property);
  HAL_StatusTypeDef ret = _SI473X_writeCommandRead16(si473x, SI473X_CMD_GET_PROPERTY, &args, sizeof(SI473X_GetPropertyArgs), response, sizeof(SI473X_GetPropertyReponse));
  response->value = SWAP_UINT16(response->value);
  return ret;
}

HAL_StatusTypeDef SI473X_getIntStatus(SI473X* si473x, SI473X_Status* status) {
  return _SI473X_writeCommandRead1(si473x, SI473X_CMD_GET_INT_STATUS, NULL, 0, status);
}

HAL_StatusTypeDef SI473X_waitForCTS(SI473X* si473x) {
  SI473X_Status status;
  HAL_StatusTypeDef ret;
  
  do {
    ret = SI473X_getStatus(si473x, &status);
    if (ret != HAL_OK) {
      return ret;
    }
  } while(!(status & SI473X_STATUS_CTS));
  return HAL_OK;
}

HAL_StatusTypeDef SI473X_getStatus(SI473X* si473x, SI473X_Status* status) {
  return _SI473X_read1(si473x, status);
}

HAL_StatusTypeDef SI473X_fmTuneFreq(
  SI473X* si473x,
  bool freeze,
  bool fast,
  uint16_t frequency,
  uint8_t antCap,
  SI473X_Status* status
) {
  SI473X_FmTuneFreqArgs args;
  args.arg1 = 
    (freeze ? SI473X_FM_TUNE_FREQ_ARG1_FREEZE : 0)
    | (fast ? SI473X_FM_TUNE_FREQ_ARG1_FAST : 0);
  args.frequency = SWAP_UINT16(frequency);
  args.antennaCapacitor = antCap;
  return _SI473X_writeCommandRead1(si473x, SI473X_CMD_FM_TUNE_FREQ, &args, sizeof(SI473X_FmTuneFreqArgs), status);
}

HAL_StatusTypeDef SI473X_fmSeekStart(
  SI473X* si473x,
  bool seekUp,
  bool wrap,
  SI473X_Status* status
) {
  SI473X_FmSeekStartArgs args;
  args.arg1 = 
    (seekUp ? SI473X_FM_TUNE_FREQ_ARG1_SEEKUP : 0)
    | (wrap ? SI473X_FM_TUNE_FREQ_ARG1_WRAP : 0);
  return _SI473X_writeCommandRead1(si473x, SI473X_CMD_FM_SEEK_START, &args, sizeof(SI473X_FmSeekStartArgs), status);
}

HAL_StatusTypeDef SI473X_fmTuneStatus(
  SI473X* si473x,
  bool cancel,
  bool intAck,
  SI473X_FmTuneStatusResponse* status
) {
  SI473X_FmTuneStatusArgs args;
  args.arg1 =
    (cancel ? SI473X_FM_TUNE_STATUS_ARG1_CANCEL : 0)
    | (intAck ? SI473X_FM_TUNE_STATUS_ARG1_INTACK : 0);
  HAL_StatusTypeDef ret = _SI473X_writeCommandRead16(
    si473x, 
    SI473X_CMD_FM_TUNE_STATUS, 
    &args, sizeof(SI473X_FmTuneStatusArgs), 
    status, sizeof(SI473X_FmTuneStatusResponse)
  );
  status->readFrequency = SWAP_UINT16(status->readFrequency);
  return ret;
}
