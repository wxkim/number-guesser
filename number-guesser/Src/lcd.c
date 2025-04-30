

#include "lcd.h"
#include "game.h"
#include "dwt.h"

/**
 * initializes the LCD registers
 */
void LCD_Init(void) {
  //
  DWT_Delay_uS(50000);

  LCD_WriteData4B(0x03);
  DWT_Delay_uS(5000);

  LCD_WriteData4B(0x03);
  DWT_Delay_uS(5000);

  LCD_WriteData4B(0x03);
  DWT_Delay_uS(5000);

  LCD_WriteData4B(0x02);
  DWT_Delay_uS(2500);

  LCD_SendCommand(0x28);
  LCD_SendCommand(0x0C);
  LCD_SendCommand(0x06);
  LCD_SendCommand(0x01);

  DWT_Delay_uS(2500);

}

/**
 * pulls the register select low
 * @param cmd the command to send
 */
void LCD_SendCommand(const uint8_t cmd) {
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
  LCD_WriteData4B(cmd >> 4);
  LCD_WriteData4B(cmd & 0x0F);
  DWT_Delay_uS(100);
}

/**
 * pulls register select high
 * @param data the data to send
 */
void LCD_SendData(const uint8_t data) {
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
  LCD_WriteData4B(data >> 4);
  LCD_WriteData4B(data & 0x0F);
  DWT_Delay_uS(100);
}

/**
 * parallel 4 bit data line
 * @param data, sent over GPIO 1 bit per pin
 */
void LCD_WriteData4B(const uint8_t data) {
  HAL_GPIO_WritePin(LCD_D_GPIO_Port, LCD_D4_Pin, (data >> 0) & 0x01);
  HAL_GPIO_WritePin(LCD_D_GPIO_Port, LCD_D5_Pin, (data >> 1) & 0x01);
  HAL_GPIO_WritePin(LCD_D_GPIO_Port, LCD_D6_Pin, (data >> 2) & 0x01);
  HAL_GPIO_WritePin(LCD_D_GPIO_Port, LCD_D7_Pin, (data >> 3) & 0x01);

  LCD_EnablePulse();
  //
}

/**
 * printer
 * @param str, the string to print
 */
void LCD_SendString(const char *str) {
  //
  while (*str) {
    if (*str == '\n') {
      LCD_SendCommand(0xC0);  // Move to start of second line
    }
    else if ((*str >= 32) && (*str <= 126) ) {
      LCD_SendData((uint8_t)*str);
    }
    str++;
  }
}

/**
 * read enable pulse
 */
void LCD_EnablePulse(void) {
  //circleUserLED();
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
  DWT_Delay_uS(1);
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
  DWT_Delay_uS(1);
}
