//
// Created by William Kim on 4/29/25.
//

#include "keypad.h"

void KEYPAD_Init(void) {
  for (int r = 0; r < 4; r++)
    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[r], KEYPAD_ROW_PINS[r], GPIO_PIN_RESET);
}

char KEYPAD_GetChar(void) {
  for (int row = 0; row < 4; row++) {
    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_SET);

    for (int col = 0; col < 4; col++) {
      if (HAL_GPIO_ReadPin(KEYPAD_COL_PORTS[col], KEYPAD_COL_PINS[col]) == GPIO_PIN_SET) {
        HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_RESET);
        return KEYS[row][col];
      }
    }

    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_RESET);
  }

  return '\0';
}

char KEYPAD_WaitPress(void) {
  char key = '\0';

  while (key == '\0') key = KEYPAD_GetChar();

  // simple debounce wait
  DWT_Delay_uS(200000);  // 200 ms
  return key;
}

uint8_t KEYPAD_IsPressed(char key) {
  for (int row = 0; row < 4; row++) {
    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_SET);

    for (int col = 0; col < 4; col++) {
      if (HAL_GPIO_ReadPin(KEYPAD_COL_PORTS[col], KEYPAD_COL_PINS[col]) == GPIO_PIN_SET) {
        HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_RESET);
        if (KEYS[row][col] == key) {
          return 1;
        }
      }
    }

    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_RESET);
  }

  return 0;
}
