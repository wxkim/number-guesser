//
// Created by William Kim on 4/29/25.
//

#include "keypad.h"

GPIO_TypeDef* KEYPAD_ROW_PORTS[NROWS] = {ROW1_PORT, ROW2_PORT, ROW3_PORT, ROW4_PORT};
uint16_t      KEYPAD_ROW_PINS[NROWS]  = {ROW1_PIN,  ROW2_PIN,  ROW3_PIN,  ROW4_PIN};

GPIO_TypeDef* KEYPAD_COL_PORTS[NCOLS] = {COL1_PORT, COL2_PORT, COL3_PORT, COL4_PORT};
uint16_t      KEYPAD_COL_PINS[NCOLS]  = {COL1_PIN,  COL2_PIN,  COL3_PIN,  COL4_PIN};

char KEYS[NROWS][NCOLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//todo: in cubeMX, make rows pins GPIO outputs
//todo: in cubeMX, make column pins GPIO input with pulldown
//todo: get game logic from tyler
//todo: get keypad to read to LCD
//todo: fix keypad drivers

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

        if (KEYS[row][col] == key) return 1;

      }
    }

    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[row], KEYPAD_ROW_PINS[row], GPIO_PIN_RESET);
  }

  return 0;
}

void KEYPAD_Debug(void) {
  uint8_t k = KEYPAD_WaitPress();
  if (k == '*') {
    LCD_Clear();  // Clear display if * is pressed
  }

  else if (k == '#') {
    LCD_nextLine();
  }

  else {
    const char buf[2] = { (char)k, '\0' };
    LCD_SendString(buf);
  }
}
