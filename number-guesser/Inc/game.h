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
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef enum {
  NOT_STARTED,
  IN_GAME,
  GAME_OVER_LOSE,
  GAME_OVER_WIN,
  ERROR_CODE
} game_state_t;

typedef struct {
  uint16_t target; /*number to guess for*/
  uint16_t currentGuess; /*current guess input*/
  uint16_t numAttempts; /*number of guesses*/
  uint16_t soCloseUpper; /*integer bound to say so close*/
  uint16_t soCloseLower; /*integer bound to say so close*/
  uint16_t maxAttempts;
  game_state_t state; /**/
} game_t;

extern game_t game;
extern game_state_t state;

void circleUserLED(void);
HAL_StatusTypeDef sendToLCD(void);
game_state_t Game_Run(game_t* game);
game_t* Game_Init();

#endif /*GAME_H*/
// EOF FILE GAME_H
