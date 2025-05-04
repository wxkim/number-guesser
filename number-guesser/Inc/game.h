//
// Created by William Kim on 4/29/25.
//

#ifndef GAME_H
#define GAME_H

#include "gpio.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "keypad.h"
#include "lcd.h"

void circleUserLED(void);
HAL_StatusTypeDef sendToLCD(void);
void runGame(uint16_t target);

#endif /*GAME_H*/
// EOF FILE GAME_H
