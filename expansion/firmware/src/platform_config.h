
#ifndef _PLATFORM_CONFIG_H_
#define _PLATFORM_CONFIG_H_

#include <pinout.h>

#define DEBUG

#ifdef DEBUG
#  define UTILS_DEBUG /* print assert statements */
#  define SI473X_DEBUG
#endif
#define DEBUG_UART       huart2
#define MAX_TIMEOUT      0xffff

#ifdef DEBUG
#  define DEBUG_OUT(format, ...) printf("%s:%d: " format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define DEBUG_OUT(format, ...)
#endif

#define SI473X_I2C
#define SI473X_I2C_SEN_0

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;

#endif

