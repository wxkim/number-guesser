//
// Created by William Kim on 4/29/25.
//

#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "lcd.h"
#include "dwt.h"

#define NROWS 4
#define NCOLS 4

#define ROW1_PORT GPIOB
#define ROW1_PIN  GPIO_PIN_1
#define ROW2_PORT GPIOC
#define ROW2_PIN  GPIO_PIN_5
#define ROW3_PORT GPIOA
#define ROW3_PIN  GPIO_PIN_7
#define ROW4_PORT GPIOA
#define ROW4_PIN  GPIO_PIN_5

#define COL1_PORT GPIOA
#define COL1_PIN  GPIO_PIN_3
#define COL2_PORT GPIOA
#define COL2_PIN  GPIO_PIN_1
#define COL3_PORT GPIOC
#define COL3_PIN  GPIO_PIN_3
#define COL4_PORT GPIOC
#define COL4_PIN  GPIO_PIN_1



extern GPIO_TypeDef* KEYPAD_ROW_PORTS[4];
extern uint16_t      KEYPAD_ROW_PINS[4];
extern GPIO_TypeDef* KEYPAD_COL_PORTS[4];
extern uint16_t      KEYPAD_COL_PINS[4];
extern char          KEYS[4][4];

void KEYPAD_Init(void);
char KEYPAD_GetChar(void);
char KEYPAD_WaitPress(void);
uint8_t KEYPAD_IsPressed(char key);
void KEYPAD_Debug();




#endif //KEYPAD_H
