//
// Created by William Kim on 4/29/25.
//

#include "keypad.h"

void KEYPAD_Init(void) {
  for (int r = 0; r < 4; r++)
    HAL_GPIO_WritePin(KEYPAD_ROW_PORTS[r], KEYPAD_ROW_PINS[r], GPIO_PIN_RESET);
}

char KEYPAD_GetChar(void) {

}

char KEYPAD_WaitPress(void) {

}

uint8_t KEYPAD_IsPressed(char key) {

}
