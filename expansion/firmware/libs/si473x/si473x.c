
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
HAL_StatusTypeDef _SI473X_spiWriteCommandRead1(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, SI473X_Status* status);
HAL_StatusTypeDef _SI473X_spiWriteCommandRead16(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength);

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

uint16_t SI473X_fmFrequencyToUint16(float frequency) {
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

void _SI473X_assertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_RESET);
}

void _SI473X_deassertCS(SI473X* si473x) {
  HAL_GPIO_WritePin(si473x->csPort, si473x->csPin, GPIO_PIN_SET);
}

HAL_StatusTypeDef _SI473X_statusToHALStatus(SI473X_Status* status) {
  return testBits(*status, SI473X_STATUS_ERR) ? HAL_ERROR : HAL_OK;
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
    if (testBits(*status, SI473X_STATUS_ERR)) {
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

HAL_StatusTypeDef _SI473X_spiWriteCommandRead1(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, SI473X_Status* status) {
  HAL_StatusTypeDef ret;
  
  _SI473X_assertCS(si473x);
  ret = _SI473X_spiWriteCommand(si473x, cmd, (uint8_t*)args, argsLength);
  if (ret == HAL_OK) {
    ret = _SI473X_read1(si473x, status);
  }  
  _SI473X_deassertCS(si473x);
  
  return ret;
}

HAL_StatusTypeDef _SI473X_spiWriteCommandRead16(SI473X* si473x, uint8_t cmd, void* args, uint8_t argsLength, void* rxBuffer, uint8_t rxBufferLength) {
  HAL_StatusTypeDef ret;
  
  _SI473X_assertCS(si473x);
  ret = _SI473X_spiWriteCommand(si473x, cmd, (uint8_t*)args, argsLength);
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
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_POWER_DOWN, NULL, 0, status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_setProperty(SI473X* si473x, uint16_t property, uint16_t value, SI473X_Status* status) {
  SI473X_SetPropertyArgs args;
  args.reserved = 0;
  args.property = property;
  args.value = value;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_SET_PROPERTY, &args, sizeof(SI473X_SetPropertyArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_getProperty(SI473X* si473x, uint16_t property, SI473X_GetPropertyReponse* response) {
  SI473X_GetPropertyArgs args;
  args.reserved = 0;
  args.property = property;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(si473x, SI473X_CMD_GET_PROPERTY, &args, sizeof(SI473X_GetPropertyArgs), response, sizeof(SI473X_GetPropertyReponse));
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&response->status);
}

HAL_StatusTypeDef SI473X_getIntStatus(SI473X* si473x, SI473X_Status* status) {
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_GET_INT_STATUS, NULL, 0, status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_txTuneFreq(SI473X* si473x, uint16_t frequency, SI473X_Status* status) {
  SI473X_TxTuneFreqArgs args;
  args.reserved = 0;
  args.frequency = frequency;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_TX_TUNE_FREQ, &args, sizeof(SI473X_SetPropertyArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_txTunePower(SI473X* si473x, uint16_t power, SI473X_Status* status) {
  SI473X_TxTunePowerArgs args;
  args.reserved = 0;
  args.power = power;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_TX_TUNE_POWER, &args, sizeof(SI473X_TxTunePowerArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_txTuneMeasure(SI473X* si473x, uint16_t frequency, uint8_t antennaCapacitor, SI473X_Status* status) {
  SI473X_TxTuneMeasureArgs args;
  args.reserved = 0;
  args.frequency = frequency;
  args.antennaTuningCapacitor = antennaCapacitor;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_TX_TUNE_MEASURE, &args, sizeof(SI473X_TxTuneMeasureArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_txTuneStatus(SI473X* si473x, bool interruptClear, SI473X_TxTuneStatusResponse* status) {
  SI473X_TxTuneStatusArgs args;
  args.reserved = 0;
  args.arg1 = interruptClear ? SI473X_TX_TUNE_STATUS_ARG1_INTACK : 0;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(
    si473x, 
    SI473X_CMD_TX_TUNE_STATUS, 
    &args, sizeof(SI473X_TxTuneStatusArgs), 
    status, sizeof(SI473X_TxTuneStatusResponse)
  );
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&status->status);
}

HAL_StatusTypeDef SI473X_txAsqStatus(SI473X* si473x, bool interruptAck, SI473X_TxAsqStatusResponse* status) {
  SI473X_TxAsqStatusArgs args;
  args.reserved = 0;
  args.arg1 = interruptAck ? SI473X_TX_ASQ_STATUS_ARG1_INTACK : 0;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(
    si473x, 
    SI473X_CMD_TX_ASQ_STATUS, 
    &args, sizeof(SI473X_TxAsqStatusArgs), 
    status, sizeof(SI473X_TxAsqStatusResponse)
  );
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&status->status);
}

HAL_StatusTypeDef SI473X_txRdsBuffer(
  SI473X* si473x,
  SI473X_TxRdsBufferArgs* args,
  SI473X_TxRdsBufferResponse* status
) {
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(
    si473x, 
    SI473X_CMD_TX_ASQ_STATUS, 
    args, sizeof(SI473X_TxRdsBufferArgs), 
    status, sizeof(SI473X_TxRdsBufferResponse)
  );
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&status->status);
}

HAL_StatusTypeDef SI473X_txRdsPs(
  SI473X* si473x,
  uint8_t psid,
  uint8_t* psChar,
  SI473X_Status* status
) {
  SI473X_TxRdsPsArgs args;
  args.reserved = 0;
  args.psid = psid & 0x0f;
  args.psChar[0] = psChar[0];
  args.psChar[1] = psChar[1];
  args.psChar[2] = psChar[2];
  args.psChar[3] = psChar[3];
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_TX_RDS_PS, &args, sizeof(SI473X_TxRdsPsArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_gpioCtl(
  SI473X* si473x,
  bool gpo1OutputEnable,
  bool gpo2OutputEnable,
  bool gpo3OutputEnable,
  SI473X_Status* status
) {
  SI473X_GpioCtlArgs args;
  args.arg1 = 
    (gpo1OutputEnable ? SI473X_GPIO_CTL_ARG1_GPO1OEN : 0)
    | (gpo2OutputEnable ? SI473X_GPIO_CTL_ARG1_GPO2OEN : 0)
    | (gpo3OutputEnable ? SI473X_GPIO_CTL_ARG1_GPO3OEN : 0);
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_GPIO_CTL, &args, sizeof(SI473X_GpioCtlArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
}

HAL_StatusTypeDef SI473X_gpioSet(
  SI473X* si473x,
  bool gpo1,
  bool gpo2,
  bool gpo3,
  SI473X_Status* status
) {
  SI473X_GpioSetArgs args;
  args.arg1 = 
    (gpo1 ? SI473X_GPIO_SET_ARG1_GPO1LEVEL : 0)
    | (gpo2 ? SI473X_GPIO_SET_ARG1_GPO2LEVEL : 0)
    | (gpo3 ? SI473X_GPIO_SET_ARG1_GPO3LEVEL : 0);
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_GPIO_SET, &args, sizeof(SI473X_GpioSetArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
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
  args.frequency = frequency;
  args.antennaCapacitor = antCap;
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_FM_TUNE_FREQ, &args, sizeof(SI473X_FmTuneFreqArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
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
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead1(si473x, SI473X_CMD_FM_SEEK_START, &args, sizeof(SI473X_FmSeekStartArgs), status);
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(status);
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
  HAL_StatusTypeDef ret = _SI473X_spiWriteCommandRead16(
    si473x, 
    SI473X_CMD_FM_TUNE_STATUS, 
    &args, sizeof(SI473X_FmTuneStatusArgs), 
    status, sizeof(SI473X_FmTuneStatusResponse)
  );
  if (ret != HAL_OK) {
    return ret;
  }
  return _SI473X_statusToHALStatus(&status->status);
}
