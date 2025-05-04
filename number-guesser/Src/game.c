#include "game.h"

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

void runGame(uint16_t target) {

    LCD_Clear();
    LCD_SendString("Guess 0-9:");

    while (1) {
      char input = KEYPAD_WaitPress();

      if (input >= '0' && input <= '9') {
        LCD_Clear();
        LCD_SendString("You guessed: ");
        LCD_WriteData4B(input);

        if ((input - '0') == target) {
          LCD_SendCommand(0xC0);
          LCD_SendString("Correct!");
          DWT_Delay_uS(1500000);  // Delay 1.5s
          break;
        } else {
          LCD_SendCommand(0xC0);
          LCD_SendString("Wrong. Try again.");
          DWT_Delay_uS(1500000);
          LCD_Clear();
          LCD_SendString("Guess 0-9:");
        }
      } else if (input == '*') {
        LCD_Clear();
        LCD_SendString("Game Reset");
        DWT_Delay_uS(1000000);
        break;
      }
    }
}

// EOF FILE GAME.C
