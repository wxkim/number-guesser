//
// Created by William Kim on 4/29/25.
//

#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "dwt.h"

#define NROWS 4
#define NCOLS 4

GPIO_TypeDef* KEYPAD_ROW_PORTS[NROWS] = {GPIOB, GPIOC, GPIOA, GPIOA};

uint16_t KEYPAD_ROW_PINS[NROWS]  =
  {GPIO_PIN_1, GPIO_PIN_5, GPIO_PIN_7, GPIO_PIN_5};

GPIO_TypeDef* KEYPAD_COL_PORTS[NCOLS] = {GPIOA, GPIOA, GPIOC, GPIOC};

uint16_t KEYPAD_COL_PINS[NCOLS] =
  {GPIO_PIN_3, GPIO_PIN_1, GPIO_PIN_3, GPIO_PIN_1};

const char KEYS[NROWS][NCOLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void KEYPAD_Init(void);
char KEYPAD_GetChar(void);
char KEYPAD_WaitPress(void);
uint8_t KEYPAD_IsPressed(char key);


#endif //KEYPAD_H
