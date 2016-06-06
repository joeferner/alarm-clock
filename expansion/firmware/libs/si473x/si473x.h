
#ifndef _SI473X_H_

#include <platform_config.h>
#include <stdbool.h>

#ifndef SI473X_SPI_TIMEOUT
#  define SI473X_SPI_TIMEOUT 1000
#endif

#ifdef SI473X_DEBUG
#  define SI473X_DEBUG_OUT(format, ...) printf("%s:%d: SI473X: " format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define SI473X_DEBUG_OUT(format, ...)
#endif

#define SI473X_CMD_POWER_UP        0x01
#define SI473X_CMD_GET_REV         0x10
#define SI473X_CMD_POWER_DOWN      0x11
#define SI473X_CMD_SET_PROPERTY    0x12
#define SI473X_CMD_GET_PROPERTY    0x13
#define SI473X_CMD_GET_INT_STATUS  0x14
#define SI473X_CMD_FM_TUNE_FREQ    0x20
#define SI473X_CMD_FM_SEEK_START   0x21
#define SI473X_CMD_FM_TUNE_STATUS  0x22
#define SI473X_CMD_TX_TUNE_FREQ    0x30
#define SI473X_CMD_TX_TUNE_POWER   0x31
#define SI473X_CMD_TX_TUNE_MEASURE 0x32
#define SI473X_CMD_TX_TUNE_STATUS  0x33
#define SI473X_CMD_TX_ASQ_STATUS   0x34
#define SI473X_CMD_TX_RDS_BUFF     0x35
#define SI473X_CMD_TX_RDS_PS       0x36
#define SI473X_CMD_GPIO_CTL        0x80
#define SI473X_CMD_GPIO_SET        0x81

typedef uint8_t SI473X_Status;
#define SI473X_STATUS_CTS    0b10000000 //< Clear to Send
#define SI473X_STATUS_ERR    0b01000000 //< Error
#define SI473X_STATUS_RDSINT 0b00000100 //< RDS Interrupt (RDS interrupt has been triggered)
#define SI473X_STATUS_ASQINT 0b00000010 //< ASQ Interrupt (Signal quality measurement has not been triggere Signal quality measurement has been triggered)
#define SI473X_STATUS_STCINT 0b00000001 //< STC Interrupt (Tune complete has not been triggere Tune complete has been triggered)

#define SI473X_POWER_UP_ARG1_CTSIEN   0b10000000 //< CTS Interrupt Enable
#define SI473X_POWER_UP_ARG1_GPO2OEN  0b01000000 //< GPO2 Output Enable
#define SI473X_POWER_UP_ARG1_PATCH    0b00100000 //< Patch Enable
#define SI473X_POWER_UP_ARG1_XOSCEN   0b00010000 //< Crystal Oscillator Enable
#define SI473X_POWER_UP_ARG1_FUNC_RX  0b00000000 //< Function: Receive
#define SI473X_POWER_UP_ARG1_FUNC_TX  0b00000010 //< Function: Transmit
#define SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID       0b00001111 //< Function: Query Library ID

#define SI473X_POWER_UP_ARG2_OPMODE_RDS_OUTPUT_ONLY    0b00000000
#define SI473X_POWER_UP_ARG2_OPMODE_ANALOG_AUDIO_OUT   0b00000101 //< Analog audio outputs (LOUT/ROUT)
#define SI473X_POWER_UP_ARG2_OPMODE_DIGITAL_AUDIO_OUT1 0b00001011 //< Digital audio output (DCLK, LOUT/DFS, ROUT/DIO)
#define SI473X_POWER_UP_ARG2_OPMODE_DIGITAL_AUDIO_OUT2 0b10110000 //< Digital audio outputs (DCLK, DFS, DIO)
#define SI473X_POWER_UP_ARG2_OPMODE_A_AND_D_AUDIO_OUT  0b10110101 //< Analog and digital audio outputs (LOUT/ROUT and DCLK, DFS, DIO)
#define SI473X_POWER_UP_ARG2_OPMODE_ANALOG_AUDIO_IN    0b01010000 //< Analog audio inputs (LIN/RIN)
#define SI473X_POWER_UP_ARG2_OPMODE_DIGITAL_AUDIO_IN   0b00001111 //< Digital audio inputs (DIN/DFS/DCLK)

typedef struct {
  SI473X_Status status;
  uint8_t partNumber;
  uint8_t fwMajor;
  uint8_t fwMinor;
  uint8_t reserved0;
  uint8_t reserved1;
  uint8_t chipRev;
  uint8_t libraryRev;
} SI473X_PowerUpQueryLibraryIdResponse;

typedef struct {
  SI473X_Status status;
  uint8_t partNumber;
  uint8_t fwMajor;
  uint8_t fwMinor;
  uint16_t patch;
  uint8_t componentMajorRev;
  uint8_t componentMinorRev;
  uint8_t chipRev;
} SI473X_GetRevResponse;

typedef struct {
  uint8_t reserved; // always write 0
  uint16_t property;
  uint16_t value;
} SI473X_SetPropertyArgs;

typedef struct {
  uint8_t reserved; // always write 0
  uint16_t property;
} SI473X_GetPropertyArgs;

typedef struct {
  SI473X_Status status;
  uint8_t reserved;
  uint16_t value;
} SI473X_GetPropertyReponse;

typedef struct {
  uint8_t reserved;
  uint16_t frequency;
} SI473X_TxTuneFreqArgs;

typedef struct {
  uint8_t reserved;
  uint16_t power;
} SI473X_TxTunePowerArgs;

typedef struct {
  uint8_t reserved;
  uint16_t frequency;
  uint8_t antennaTuningCapacitor;
} SI473X_TxTuneMeasureArgs;

typedef struct {
  uint8_t reserved;
  uint8_t arg1;
} SI473X_TxTuneStatusArgs;
#define SI473X_TX_TUNE_STATUS_ARG1_INTACK 0b00000001

typedef struct {
  SI473X_Status status;
  uint8_t reserved0;
  uint16_t readFrequency;
  uint8_t reserved1;
  uint8_t readRfDb;
  uint8_t readAntCap;
  uint8_t rnl;
} SI473X_TxTuneStatusResponse;

typedef struct {
  uint8_t reserved;
  uint8_t arg1;
} SI473X_TxAsqStatusArgs;
#define SI473X_TX_ASQ_STATUS_ARG1_INTACK 0b00000001

typedef struct {
  SI473X_Status status;
  uint8_t resp1;
  uint8_t reserved0;
  uint8_t reserved1;
  uint8_t inputAudioLevel;
} SI473X_TxAsqStatusResponse;
#define SI473X_TX_ASQ_STATUS_RESP1_OVERMOD 0b00000100
#define SI473X_TX_ASQ_STATUS_RESP1_IALH    0b00000010
#define SI473X_TX_ASQ_STATUS_RESP1_IALL    0b00000001

typedef struct {
  uint8_t arg1;
  uint16_t rdsBlockB;
  uint16_t rdsBlockC;
  uint16_t rdsBlockD;
} SI473X_TxRdsBufferArgs;
#define SI473X_TX_RDS_BUFF_ARG1_FIFO   0b10000000
#define SI473X_TX_RDS_BUFF_ARG1_LDBUFF 0b00000100
#define SI473X_TX_RDS_BUFF_ARG1_MTBUFF 0b00000010
#define SI473X_TX_RDS_BUFF_ARG1_INTACK 0b00000001

typedef struct {
  SI473X_Status status;
  uint8_t resp1;
  uint8_t cbAvail;
  uint8_t cbUsed;
  uint8_t fifoAvail;
  uint8_t fifoUsed;
} SI473X_TxRdsBufferResponse;
#define SI473X_TX_RDS_BUFF_RESP1_RDSPSXMIT 0b00010000
#define SI473X_TX_RDS_BUFF_RESP1_CBUFXMIT  0b00001000
#define SI473X_TX_RDS_BUFF_RESP1_FIFOXMIT  0b00000100
#define SI473X_TX_RDS_BUFF_RESP1_CBUFWRAP  0b00000010
#define SI473X_TX_RDS_BUFF_RESP1_FIFOMT    0b00000001

typedef struct {
  uint8_t reserved;
  uint8_t psid;
  uint8_t psChar[4];
} SI473X_TxRdsPsArgs;

typedef struct {
  uint8_t arg1;
} SI473X_GpioCtlArgs;
#define SI473X_GPIO_CTL_ARG1_GPO3OEN 0b00001000
#define SI473X_GPIO_CTL_ARG1_GPO2OEN 0b00000100
#define SI473X_GPIO_CTL_ARG1_GPO1OEN 0b00000010

typedef struct {
  uint8_t arg1;
} SI473X_GpioSetArgs;
#define SI473X_GPIO_SET_ARG1_GPO3LEVEL 0b00001000
#define SI473X_GPIO_SET_ARG1_GPO2LEVEL 0b00000100
#define SI473X_GPIO_SET_ARG1_GPO1LEVEL 0b00000010

typedef struct {
  uint8_t arg1;
  uint16_t frequency;
  uint8_t antennaCapacitor;
} SI473X_FmTuneFreqArgs;
#define SI473X_FM_TUNE_FREQ_ARG1_FREEZE 0b00000010
#define SI473X_FM_TUNE_FREQ_ARG1_FAST   0b00000001

typedef struct {
  uint8_t arg1;
} SI473X_FmSeekStartArgs;
#define SI473X_FM_TUNE_FREQ_ARG1_SEEKUP 0b00001000
#define SI473X_FM_TUNE_FREQ_ARG1_WRAP   0b00000100

typedef struct {
  uint8_t arg1;
} SI473X_FmTuneStatusArgs;
#define SI473X_FM_TUNE_STATUS_ARG1_CANCEL 0b00000010
#define SI473X_FM_TUNE_STATUS_ARG1_INTACK 0b00000001

typedef struct {
  SI473X_Status status;
  uint8_t resp1;
  uint16_t readFrequency;
  uint8_t rssi;
  uint8_t snr;
  uint8_t mult;
  uint8_t readAntCap;
} SI473X_FmTuneStatusResponse;
#define SI473X_FM_TUNE_STATUS_RESP1_BLTF  0b10000000
#define SI473X_FM_TUNE_STATUS_RESP1_AFCRL 0b00000010
#define SI473X_FM_TUNE_STATUS_RESP1_VALID 0b00000001

typedef struct {
  SPI_HandleTypeDef* spi;
  GPIO_TypeDef* csPort;
  uint16_t csPin;
  GPIO_TypeDef* resetPort;
  uint16_t resetPin;
  GPIO_TypeDef* interruptPort;
  uint16_t interruptPin;
  // TODO: SPI Disable: GPIO_TypeDef* gpo1Port;
  // TODO: SPI Disable: uint16_t gpo1Pin;
} SI473X;

HAL_StatusTypeDef SI473X_setup(SI473X* si473x);
void SI473X_tick(SI473X* si473x);

uint16_t SI473X_fmFrequencyToUint16(float frequency);

HAL_StatusTypeDef SI473X_powerUp(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_Status* status);
HAL_StatusTypeDef SI473X_powerUpQueryLibraryId(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_PowerUpQueryLibraryIdResponse* response);
HAL_StatusTypeDef SI473X_getRev(SI473X* si473x, SI473X_GetRevResponse* response);
HAL_StatusTypeDef SI473X_powerDown(SI473X* si473x, SI473X_Status* status);
HAL_StatusTypeDef SI473X_setProperty(SI473X* si473x, uint16_t property, uint16_t value, SI473X_Status* status);
HAL_StatusTypeDef SI473X_getProperty(SI473X* si473x, uint16_t property, SI473X_GetPropertyReponse* response);
HAL_StatusTypeDef SI473X_getIntStatus(SI473X* si473x, SI473X_Status* status);

/**
 * @param frequency Tune Frequency. Selects the tune frequency in units of 10 kHz. The valid range is from 7600
 *                  to 10800 (76–108 MHz). The frequency must be a multiple of 50 kHz. See SI473X_fmFrequencyToUint16
 */
HAL_StatusTypeDef SI473X_txTuneFreq(SI473X* si473x, uint16_t frequency, SI473X_Status* status);

/**
 * @param power Tune Power. Sets the tune power in dBμV in 1 dB steps. The valid range is from 88–115 dBμV.
 *              Power may be set as high as 120 dBμV; however, voltage accuracy is not guaranteed.
 */
HAL_StatusTypeDef SI473X_txTunePower(SI473X* si473x, uint16_t power, SI473X_Status* status);

/**
 * @param frequency Tune Frequency. Selects the tune frequency in units of 10 kHz. In FM mode the valid range
 *                  is from 7600 to 10800 (76–108 MHz). The frequency must be a multiple of 50 kHz.
 * @param antennaCapacitor Antenna Tuning Capacitor. This selects the value of the antenna tuning capacitor
 *                         manually, or automatic if set to zero. The valid range is 0–191.
 */
HAL_StatusTypeDef SI473X_txTuneMeasure(SI473X* si473x, uint16_t frequency, uint8_t antennaCapacitor, SI473X_Status* status);

/**
 * @param interruptClear Seek/Tune Interrupt Clear. If set clears the seek/tune complete interrupt status indicator.
 */
HAL_StatusTypeDef SI473X_txTuneStatus(SI473X* si473x, bool interruptClear, SI473X_TxTuneStatusResponse* status);

/**
 * @param interruptAck Clears ASQINT, OVERMOD, IALDH, and IALDL.
 */
HAL_StatusTypeDef SI473X_txAsqStatus(SI473X* si473x, bool interruptAck, SI473X_TxAsqStatusResponse* status);

HAL_StatusTypeDef SI473X_txRdsBuffer(
  SI473X* si473x,
  SI473X_TxRdsBufferArgs* args,
  SI473X_TxRdsBufferResponse* status
);

HAL_StatusTypeDef SI473X_txRdsPs(
  SI473X* si473x,
  uint8_t psid,
  uint8_t* psChar,
  SI473X_Status* status
);

HAL_StatusTypeDef SI473X_gpioCtl(
  SI473X* si473x,
  bool gpo1OutputEnable,
  bool gpo2OutputEnable,
  bool gpo3OutputEnable,
  SI473X_Status* status
);

HAL_StatusTypeDef SI473X_gpioSet(
  SI473X* si473x,
  bool gpo1,
  bool gpo2,
  bool gpo3,
  SI473X_Status* status
);

/**
 * @param freeze    Freeze Metrics During Alternate Frequency Jump. If set will cause
 *                  the blend, hicut, and softmute to transition as a function of the
 *                  associated attack/release parameters rather than instantaneously
 *                  when tuning to alternate station.
 * @param fast      FAST Tuning. If set, executes fast and invalidated tune. The tune
 *                  status will not be accurate.
 * @param frequency Tune Frequency. Selects the tune frequency in 10 kHz. In
 *                  FM mode the valid range is from 6400 to 10800 (64–108 MHz).
 * @param antCap    Antenna Tuning Capacitor (valid only when using TXO/LPI pin as
 *                  the antenna input). This selects the value of the antenna tuning
 *                  capacitor manually, or automatically if set to zero. The valid
 *                  range is 0 to 191. Automatic capacitor tuning is recommended.
 */
HAL_StatusTypeDef SI473X_fmTuneFreq(
  SI473X* si473x,
  bool freeze,
  bool fast,
  uint16_t frequency,
  uint8_t antCap,
  SI473X_Status* status
);

HAL_StatusTypeDef SI473X_fmSeekStart(
  SI473X* si473x,
  bool seekUp,
  bool wrap,
  SI473X_Status* status
);

HAL_StatusTypeDef SI473X_fmTuneStatus(
  SI473X* si473x,
  bool cancel,
  bool intAck,
  SI473X_FmTuneStatusResponse* status
);

#endif
