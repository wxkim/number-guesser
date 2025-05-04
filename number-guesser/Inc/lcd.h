//
// Created by William Kim on 4/29/25.
//

#ifndef LCD_H
#define LCD_H

#include "gpio.h"
#include "stdint.h"

// LCD Control Pins
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RS_Pin       GPIO_PIN_11

#define LCD_E_GPIO_Port  GPIOE
#define LCD_E_Pin        GPIO_PIN_15

// LCD Data Pins (4-bit mode: D4–D7)
#define LCD_D_GPIO_Port  GPIOE
#define LCD_D4_Pin       GPIO_PIN_13
#define LCD_D5_Pin       GPIO_PIN_11
#define LCD_D6_Pin       GPIO_PIN_9
#define LCD_D7_Pin       GPIO_PIN_7

void LCD_EnablePulse(void);
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_WriteData4B(uint8_t data);
void LCD_SendString(const char *str);
void LCD_Clear(void);
void LCD_nextLine(void);

#endif /* LCD_H */
// EOF FILE LCD_H
