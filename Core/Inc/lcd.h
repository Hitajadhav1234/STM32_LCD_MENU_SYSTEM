/*
 * lcd.h
 *
 *  Created on: 27-Jun-2026
 *      Author: Hita Jadhav
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
#include"main.h"




void Delay_us(uint16_t us);
void LCD_Enable(void);
void LCD_SENDBYTE(uint8_t data);
void LCD_COMMAND(uint8_t cmd);
void LCD_DATA(uint8_t data);
void LCD_STRING(const char *str);
void LCD_Init(void);


#endif /* INC_LCD_H_ */
