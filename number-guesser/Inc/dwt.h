//
// Created by William Kim on 4/29/25.
//

#ifndef DWT_H
#define DWT_H

#include "stdint.h"
#include "stm32f4xx_hal.h"

void DWT_Init(void);
void DWT_Delay_uS(const uint32_t ticks);

#endif //DWT_H
