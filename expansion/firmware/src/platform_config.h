
#ifndef _PLATFORM_CONFIG_H_
#define _PLATFORM_CONFIG_H_

#include <pinout.h>

#define DEBUG

#ifdef DEBUG
#  define UTILS_DEBUG /* print assert statements */
#  define SI473X_DEBUG
#endif
#define DEBUG_UART       huart1
#define MAX_TIMEOUT      0xffff

#ifdef DEBUG
#  define DEBUG_OUT(format, ...) printf("%s:%d: " format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define DEBUG_OUT(format, ...)
#endif

extern UART_HandleTypeDef huart1;
extern SPI_HandleTypeDef hspi1;

#endif

