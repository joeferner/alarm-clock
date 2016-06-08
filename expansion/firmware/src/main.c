
#include "platform_config.h"
#include "radio.h"
#include <utils/debug.h>
#include <utils/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup() {
  debug_setup();
  sleep_ms(100);
  DEBUG_OUT("setup\n");

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  radio_setup();

  DEBUG_OUT("END setup\n");
}

void loop() {
  debug_tick();
  radio_tick();
}

void debug_processLine(const char* line) {
  if (strlen(line) == 0) {
  } else if (strcmp(line, "seek") == 0) {
    radio_seekUp();
  } else if (strcmp(line, "status") == 0) {
    radio_status();
  } else if (strncmp(line, "tune", 4) == 0) {
    uint32_t frequency = atoi(line + 4);
    radio_tune(frequency);
  } else {
    printf("invalid debug command: %s\n", line);
  }
  printf("> ");
}
