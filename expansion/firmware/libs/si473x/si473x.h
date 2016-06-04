
#ifndef _SI473X_H_

#include <platform_config.h>

#ifndef SI473X_SPI_TIMEOUT
#  define SI473X_SPI_TIMEOUT 1000
#endif

#ifdef SI473X_DEBUG
#  define SI473X_DEBUG_OUT(format, ...) printf("%s:%d: SI473X: " format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define SI473X_DEBUG_OUT(format, ...)
#endif

#define SI473X_CMD_POWER_UP   0x01
#define SI473X_CMD_GET_REV    0x10
#define SI473X_CMD_POWER_DOWN 0x11

typedef struct {
  uint8_t cts: 1;
  uint8_t error: 1;
  uint8_t unused: 3;
  uint8_t rdsInterrupt: 1;
  uint8_t asqInterrupt: 1;
  uint8_t stcInterrupt: 1;
} SI473X_Status;
#define SI473X_STATUS_CTS    0b10000000 //< Clear to Send
#define SI473X_STATUS_ERR    0b01000000 //< Error
#define SI473X_STATUS_RDSINT 0b00000100 //< RDS Interrupt (RDS interrupt has been triggered)
#define SI473X_STATUS_ASQINT 0b00000010 //< ASQ Interrupt (Signal quality measurement has not been triggere Signal quality measurement has been triggered)
#define SI473X_STATUS_STCINT 0b00000001 //< STC Interrupt (Tune complete has not been triggere Tune complete has been triggered)

#define SI473X_POWER_UP_ARG1_CTSIEN   0b10000000 //< CTS Interrupt Enable
#define SI473X_POWER_UP_ARG1_GPO2OEN  0b01000000 //< GPO2 Output Enable
#define SI473X_POWER_UP_ARG1_PATCH    0b00100000 //< Patch Enable
#define SI473X_POWER_UP_ARG1_XOSCEN   0b00010000 //< Crystal Oscillator Enable
#define SI473X_POWER_UP_ARG1_FUNC_TX  0b00000010 //< Function: Transmit
#define SI473X_POWER_UP_ARG1_FUNC_QUERY_LIB_ID       0b00001111 //< Function: Query Library ID

#define SI473X_POWER_UP_ARG2_OPMODE_ANALOG_AUDIO_IN  0b01010000 //< Analog audio inputs (LIN/RIN)
#define SI473X_POWER_UP_ARG2_OPMODE_DIGITAL_AUDIO_IN 0b00001111 //< Digital audio inputs (DIN/DFS/DCLK)

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
  uint8_t patchHigh;
  uint8_t patchLow;
  uint8_t componentMajorRev;
  uint8_t componentMinorRev;
  uint8_t chipRev;
} SI473X_GetRevResponse;

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
HAL_StatusTypeDef SI473X_powerUp(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_Status* status);
HAL_StatusTypeDef SI473X_powerUpQueryLibraryId(SI473X* si473x, uint8_t arg1, uint8_t arg2, SI473X_PowerUpQueryLibraryIdResponse* response);
HAL_StatusTypeDef SI473X_getRev(SI473X* si473x, SI473X_GetRevResponse* response);
HAL_StatusTypeDef SI473X_powerDown(SI473X* si473x, SI473X_Status* status);

#endif
