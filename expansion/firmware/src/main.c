
#include "platform_config.h"
#include "radio.h"
#include <utils/debug.h>
#include <utils/time.h>

void setup() {
  debug_setup();
  sleep_ms(100);
  DEBUG_OUT("setup\n");

  radio_setup();

  DEBUG_OUT("END setup\n");
}

void loop() {
  debug_tick();
  radio_tick();
}
