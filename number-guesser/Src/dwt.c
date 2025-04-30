//
// Created by William Kim on 4/29/25.
//

#include "dwt.h"

void DWT_Init(void) {
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void DWT_Delay_uS(const uint32_t ticks) {
  const uint32_t cycles = ticks * (SystemCoreClock / 1000000);
  const uint32_t start = DWT->CYCCNT;
  while (DWT->CYCCNT - start < cycles);
}
