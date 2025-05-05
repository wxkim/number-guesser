#include "game.h"

game_t game = {0};

void circleUserLED(void) {
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // Set pin high
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); // Set pin high
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); // Set pin high
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); // Set pin high
  HAL_Delay(45);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // Set pin lo
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET); // Set pin lo
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // Set pin lo
  HAL_Delay(45);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET); // Set pin lo
  HAL_Delay(45);
}

HAL_StatusTypeDef sendToLCD(void) {
  const char key = KEYPAD_WaitPress();
  const char buf[2] = {key, '\0'};
  LCD_SendCommand(0x01);
  DWT_Delay_uS(2500);
  LCD_SendString(buf);

  return HAL_OK;
}

game_t* Game_Init(void) {
  game.target = rand() % 10;     // Target number: 0–9
  game.currentGuess = 0;
  game.numAttempts = 0;
  game.maxAttempts = 8;
  game.soCloseLower = (game.target > 0) ? game.target - 1 : 0;
  game.soCloseUpper = (game.target < 9) ? game.target + 1 : 9;
  game.state = NOT_STARTED;

  return &game;
}



game_state_t Game_Run(game_t* game) {
  game->state = IN_GAME;

  LCD_Clear();
  LCD_SendString("Press any key\nto start.");
  KEYPAD_WaitPress();

  LCD_Clear();
  LCD_SendString("Press * to\nrestart.");
  HAL_Delay(1500);

  LCD_Clear();
  HAL_Delay(500);

  while (1) {
    LCD_SendString("Pick a num 0-9\nPrs * rstrt.");
    char key = KEYPAD_WaitPress();
    LCD_Clear();

    #define DEBUG

    #ifdef DEBUG
      char buf[17];
      snprintf(buf, sizeof(buf), "Target: %d", game->target);
      LCD_SendString(buf);
      HAL_Delay(1000);
      LCD_Clear();
    #endif

    if (key == '*') {
      game->state = NOT_STARTED;
      //TODO fn pointer to beginning of game
      return game->state;
    }

    if (key >= '0' && key <= '9') {
      game->currentGuess = key - '0';
      game->numAttempts++;

      LCD_Clear();
      char buf[17];
      snprintf(buf, sizeof(buf), "You guessed: %c", key);
      LCD_SendString(buf);
      LCD_SendCommand(0xC0);  // Move to second line
      HAL_Delay(1500);
      LCD_Clear();

      if (game->currentGuess == game->target) {
        LCD_SendString("Correct!\nGAME OVER");
        game->state = GAME_OVER_WIN;
        HAL_Delay(3500);
        return game->state;
      }

      else if (game->currentGuess >= game->soCloseLower &&
                 game->currentGuess <= game->soCloseUpper) {
        LCD_SendString("So close!");
      }

      else if (game->currentGuess > game->target) {
        LCD_SendString("Too high!");
      }

      else {
        LCD_SendString("Too low!");
      }

      HAL_Delay(1500);
      LCD_Clear();

      // Add tries remaining
      char msg[20];
      snprintf(msg, sizeof(msg), "Tries left: %d", game->maxAttempts - game->numAttempts);
      LCD_SendString(msg);

      HAL_Delay(1500);
      LCD_Clear();

      if (game->numAttempts >= 5 && game->state != GAME_OVER_LOSE) {
        LCD_Clear();
        LCD_SendString("Out of tries.\nYou lost.");
        HAL_Delay(3500);
        LCD_Clear();
        game->state = GAME_OVER_LOSE;
      }
    }
  }


}

// EOF FILE GAME.C
