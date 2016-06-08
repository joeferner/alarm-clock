
#ifndef _RADIO_H_
#define _RADIO_H_

#include "platform_config.h"

HAL_StatusTypeDef radio_setup();
void radio_tick();
HAL_StatusTypeDef radio_seekUp();
HAL_StatusTypeDef radio_status();
HAL_StatusTypeDef radio_tune(uint32_t frequency);

#endif
