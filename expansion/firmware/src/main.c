
#include "platform_config.h"
#include "radio.h"
#include <utils/debug.h>
#include <utils/time.h>

void setup() {
  debug_setup();
  sleep_ms(100);
  radio_setup();
  
  DEBUG_OUT("setup\n");
}

void loop() {
  debug_tick();
  radio_tick();
}
