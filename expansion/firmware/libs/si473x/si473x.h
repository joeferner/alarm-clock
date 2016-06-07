
#ifndef _SI473X_H_

#include <platform_config.h>
#include <stdbool.h>

#ifndef SI473X_SPI_TIMEOUT
#  define SI473X_SPI_TIMEOUT 1000
#endif

#define PACKED __attribute__((packed))

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
#define SI473X_CMD_PATCH_ARGS      0x15
#define SI473X_CMD_PATCH_DATA      0x16
#define SI473X_CMD_FM_TUNE_FREQ    0x20
#define SI473X_CMD_FM_SEEK_START   0x21
#define SI473X_CMD_FM_TUNE_STATUS  0x22
#define SI473X_CMD_FM_RSQ_STATUS   0x23
#define SI473X_CMD_FM_RDS_STATUS   0x24
#define SI473X_CMD_FM_AGC_STATUS   0x27
#define SI473X_CMD_FM_AGC_OVERRIDE 0x28
#define SI473X_CMD_TX_TUNE_FREQ    0x30
#define SI473X_CMD_TX_TUNE_POWER   0x31
#define SI473X_CMD_TX_TUNE_MEASURE 0x32
#define SI473X_CMD_TX_TUNE_STATUS  0x33
#define SI473X_CMD_TX_ASQ_STATUS   0x34
#define SI473X_CMD_TX_RDS_BUFF     0x35
#define SI473X_CMD_TX_RDS_PS       0x36
#define SI473X_CMD_AM_TUNE_FREQ    0x40
#define SI473X_CMD_AM_SEEK_START   0x41
#define SI473X_CMD_AM_TUNE_STATUS  0x42
#define SI473X_CMD_AM_RSQ_STATUS   0x43
#define SI473X_CMD_AM_AGC_STATUS   0x47
#define SI473X_CMD_AM_AGC_OVERRIDE 0x48
#define SI473X_CMD_WB_TUNE_FREQ    0x50
#define SI473X_CMD_WB_TUNE_STATUS  0x52
#define SI473X_CMD_WB_RSQ_STATUS   0x53
#define SI473X_CMD_WB_SAME_STATUS  0x54
#define SI473X_CMD_WB_ASQ_STATUS   0x55
#define SI473X_CMD_WB_AGC_STATUS   0x57
#define SI473X_CMD_WB_AGC_OVERRIDE 0x58
#define SI473X_CMD_GPIO_CTL        0x80
#define SI473X_CMD_GPIO_SET        0x81

#define SI473X_PROP_GPO_IEN                       0x0001
#define SI473X_PROP_DIGITAL_OUTPUT_FORMAT         0x0102
#define SI473X_PROP_DIGITAL_OUTPUT_SAMPLE_RATE    0x0104
#define SI473X_PROP_REFCLK_FREQ                   0x0201
#define SI473X_PROP_REFCLK_PRESCALE               0x0202
#define SI473X_PROP_FM_DEEMPHASIS                 0x1100
#define SI473X_PROP_FM_CHANNEL_FILTER             0x1102
#define SI473X_PROP_FM_BLEND_STEREO_THRESHOLD     0x1105
#define SI473X_PROP_FM_BLEND_MONO_THRESHOLD       0x1106
#define SI473X_PROP_FM_ANTENNA_INPUT              0x1107
#define SI473X_PROP_FM_MAX_TUNE_ERROR             0x1108
#define SI473X_PROP_FM_RSQ_INT_SOURCE             0x1200
#define SI473X_PROP_FM_RSQ_SNR_HI_THRESHOLD       0x1201
#define SI473X_PROP_FM_RSQ_SNR_LO_THRESHOLD       0x1202
#define SI473X_PROP_FM_RSQ_RSSI_HI_THRESHOLD      0x1203
#define SI473X_PROP_FM_RSQ_RSSI_LO_THRESHOLD      0x1204
#define SI473X_PROP_FM_RSQ_MULTIPATH_HI_THRESHOLD 0x1205
#define SI473X_PROP_FM_RSQ_MULTIPATH_LO_THRESHOLD 0x1206
#define SI473X_PROP_FM_RSQ_BLEND_THRESHOLD        0x1207
#define SI473X_PROP_FM_SOFT_MUTE_RATE             0x1300
#define SI473X_PROP_FM_SOFT_MUTE_SLOPE            0x1301
#define SI473X_PROP_FM_SOFT_MUTE_MAX_ATTENUATION  0x1302
#define SI473X_PROP_FM_SOFT_MUTE_SNR_THRESHOLD    0x1303
#define SI473X_PROP_FM_SOFT_MUTE_RELEASE_RATE     0x1304
#define SI473X_PROP_FM_SOFT_MUTE_ATTACH_RATE      0x1305
#define SI473X_PROP_FM_SEEK_BAND_BOTTOM           0x1400
#define SI473X_PROP_FM_SEEK_BAND_TOP              0x1401
#define SI473X_PROP_FM_SEEK_FREQ_SPACING          0x1402
#define SI473X_PROP_FM_SEEK_TUNE_SNR_THRESHOLD    0x1403
#define SI473X_PROP_FM_SEEK_TUNE_RSSI_THRESHOLD   0x1404
#define SI473X_PROP_FM_RDS_INT_SOURCE             0x1500
#define SI473X_PROP_FM_RDS_INT_FIFO_COUNT         0x1501
#define SI473X_PROP_FM_RDS_CONFIG                 0x1502
#define SI473X_PROP_FM_RDS_CONFIDENCE             0x1503
#define SI473X_PROP_FM_AGC_ATTACK_RATE            0x1700
#define SI473X_PROP_FM_AGC_RELEASE_RATE           0x1701
#define SI473X_PROP_FM_BLEND_RSSI_STEREO_THRESHOLD 0x1800
#define SI473X_PROP_FM_BLEND_RSSI_MONO_THRESHOLD  0x1801
#define SI473X_PROP_FM_BLEND_RSSI_ATTACK_RATE     0x1802
#define SI473X_PROP_FM_BLEND_RSSI_RELEASE_RATE    0x1803
#define SI473X_PROP_FM_BLEND_SNR_STEREO_THRESHOLD 0x1804
#define SI473X_PROP_FM_BLEND_SNR_MONO_THRESHOLD   0x1805
#define SI473X_PROP_FM_BLEND_SNR_ATTACH_RATE      0x1806
#define SI473X_PROP_FM_BLEND_SNR_RELEASE_RATE     0x1807
#define SI473X_PROP_FM_BLEND_MULTIPATH_STEREO_THRESHOLD 0x1808
#define SI473X_PROP_FM_BLEND_MULTIPATH_MONO_THRESHOLD   0x1809
#define SI473X_PROP_FM_BLEND_MULTIPATH_ATTACH_RATE      0x180a
#define SI473X_PROP_FM_BLEND_MULTIPATH_RELEASE_RATE     0x180b
#define SI473X_PROP_FM_BLEND_MAX_STEREO_SEPERATION      0x180c
#define SI473X_PROP_FM_NB_DETECT_THRESHOLD        0x1900
#define SI473X_PROP_FM_NB_INTERVAL                0x1901
#define SI473X_PROP_FM_NB_RATE                    0x1902
#define SI473X_PROP_FM_NB_IIR_FILTER              0x1903
#define SI473X_PROP_FM_NB_DELAY                   0x1904
#define SI473X_PROP_FM_HICUT_SNR_HIGH_THRESHOLD   0x1a00
#define SI473X_PROP_FM_HICUT_SNR_LOW_THRESHOLD    0x1a01
#define SI473X_PROP_FM_HICUT_ATTACH_RATE          0x1a02
#define SI473X_PROP_FM_HICUT_RELEASE_RATE         0x1a03
#define SI473X_PROP_FM_HICUT_MULTIPATH_TRIGGER_THRESHOLD 0x1a04
#define SI473X_PROP_FM_HICUT_MULTIPATH_END_THRESHOLD     0x1a05
#define SI473X_PROP_FM_HICUT_CUTOFF_FREQUENCY     0x1a06
#define SI473X_PROP_RX_VOLUME                     0x4000
#define SI473X_PROP_RX_HARD_MUTE                  0x4001

#define SI473X_PROP_GPO_IEN_RSQREP  0x0800
#define SI473X_PROP_GPO_IEN_RDSREP  0x0400
#define SI473X_PROP_GPO_IEN_STCREP  0x0100
#define SI473X_PROP_GPO_IEN_CTSIEN  0x0080
#define SI473X_PROP_GPO_IEN_ERRIEN  0x0040
#define SI473X_PROP_GPO_IEN_RSQIEN  0x0008
#define SI473X_PROP_GPO_IEN_RDSIEN  0x0004
#define SI473X_PROP_GPO_IEN_STCIEN  0x0001

typedef uint8_t SI473X_Status;
#define SI473X_STATUS_CTS    0b10000000 //< Clear to Send
#define SI473X_STATUS_ERR    0b01000000 //< Error
#define SI473X_STATUS_RDSINT 0b00000100 //< RDS Interrupt
#define SI473X_STATUS_ASQINT 0b00000010 //< ASQ Interrupt (Signal Quality)
#define SI473X_STATUS_STCINT 0b00000001 //< STC Interrupt (Seek/Tune Complete Interrupt)

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
  uint8_t arg1;
  uint8_t arg2;
} PACKED SI473X_PowerUpArgs;

typedef struct {
  SI473X_Status status;
  uint8_t partNumber;
  uint8_t fwMajor;
  uint8_t fwMinor;
  uint8_t reserved0;
  uint8_t reserved1;
  uint8_t chipRev;
  uint8_t libraryRev;
} PACKED SI473X_PowerUpQueryLibraryIdResponse;

typedef struct {
  SI473X_Status status;
  uint8_t partNumber;
  uint8_t fwMajor;
  uint8_t fwMinor;
  uint16_t patch;
  uint8_t componentMajorRev;
  uint8_t componentMinorRev;
  uint8_t chipRev;
} PACKED SI473X_GetRevResponse;

typedef struct {
  uint8_t reserved; // always write 0
  uint16_t property;
  uint16_t value;
} PACKED SI473X_SetPropertyArgs;

typedef struct {
  uint8_t reserved; // always write 0
  uint16_t property;
} PACKED SI473X_GetPropertyArgs;

typedef struct {
  SI473X_Status status;
  uint8_t reserved;
  uint16_t value;
} PACKED SI473X_GetPropertyReponse;

typedef struct {
  uint8_t arg1;
  uint16_t frequency;
  uint8_t antennaCapacitor;
} PACKED SI473X_FmTuneFreqArgs;
#define SI473X_FM_TUNE_FREQ_ARG1_FREEZE 0b00000010
#define SI473X_FM_TUNE_FREQ_ARG1_FAST   0b00000001

typedef struct {
  uint8_t arg1;
} PACKED SI473X_FmSeekStartArgs;
#define SI473X_FM_TUNE_FREQ_ARG1_SEEKUP 0b00001000
#define SI473X_FM_TUNE_FREQ_ARG1_WRAP   0b00000100

typedef struct {
  uint8_t arg1;
} PACKED SI473X_FmTuneStatusArgs;
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
} PACKED SI473X_FmTuneStatusResponse;
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
  GPIO_TypeDef* gpo1Port;
  uint16_t gpo1Pin;
} SI473X;

HAL_StatusTypeDef SI473X_setup(SI473X* si473x);
void SI473X_tick(SI473X* si473x);

uint16_t SI473X_fmFrequencyToUint16(uint32_t frequency);

HAL_StatusTypeDef SI473X_powerUp(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_Status* status);
HAL_StatusTypeDef SI473X_powerUpQueryLibraryId(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_PowerUpQueryLibraryIdResponse* response);
HAL_StatusTypeDef SI473X_getRev(SI473X* si473x, SI473X_GetRevResponse* response);
HAL_StatusTypeDef SI473X_powerDown(SI473X* si473x, SI473X_Status* status);
HAL_StatusTypeDef SI473X_setProperty(SI473X* si473x, uint16_t property, uint16_t value, SI473X_Status* status);
HAL_StatusTypeDef SI473X_getProperty(SI473X* si473x, uint16_t property, SI473X_GetPropertyReponse* response);
HAL_StatusTypeDef SI473X_getIntStatus(SI473X* si473x, SI473X_Status* status);

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
