
#include "platform_config.h"
#include <utils/debug.h>
#include <utils/time.h>

void setup() {
  debug_setup();
  sleep_ms(100);
  DEBUG_OUT("setup\n");
}

void loop() {
  debug_tick();
  DEBUG_OUT("loop\n");
  HAL_GPIO_WritePin(PIN_USER_LED_PORT, PIN_USER_LED_PIN, GPIO_PIN_SET);
  sleep_ms(1000);
  HAL_GPIO_WritePin(PIN_USER_LED_PORT, PIN_USER_LED_PIN, GPIO_PIN_RESET);
  sleep_ms(1000);
}
