/*
 * lcd.c
 *
 *  Created on: 27-Jun-2026
 *      Author: Hita Jadhav
 */
#include"lcd.h"

int A=0;
uint8_t i=0;
uint8_t data;

uint8_t cmd;
const char *str;
GPIO_TypeDef *LCD_PORT[8] =
{
    LCD_DB0_GPIO_Port,
    LCD_DB1_GPIO_Port,
    LCD_DB2_GPIO_Port,
    LCD_DB3_GPIO_Port,
    LCD_DB4_GPIO_Port,
    LCD_DB5_GPIO_Port,
    LCD_DB6_GPIO_Port,
    LCD_DB7_GPIO_Port
};

uint16_t LCD_PIN[8] =
{
    LCD_DB0_Pin,
    LCD_DB1_Pin,
    LCD_DB2_Pin,
    LCD_DB3_Pin,
    LCD_DB4_Pin,
    LCD_DB5_Pin,
    LCD_DB6_Pin,
    LCD_DB7_Pin
};
extern TIM_HandleTypeDef htim14;

void Delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim14, 0);

    while(__HAL_TIM_GET_COUNTER(&htim14) < us);
}
void LCD_Enable()
{
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);   // EN = 1
    Delay_us(1);                                          // Wait 1 µs
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET); // EN = 0
    Delay_us(100);
}
void LCD_SENDBYTE(uint8_t data)
{
	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(LCD_PORT[i], LCD_PIN[i], (data & (1<<i) ? GPIO_PIN_SET:GPIO_PIN_RESET ));
	}
	LCD_Enable();
}
void LCD_COMMAND(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RW_GPIO_Port,LCD_RW_Pin,GPIO_PIN_RESET);
	LCD_SENDBYTE(cmd);

	    if(cmd == 0x01 || cmd == 0x02)
	    {
	        HAL_Delay(2);      // Clear display and Return Home need longer delay
	    }
	    else
	    {
	        Delay_us(50);
	    }
}
void LCD_DATA(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RW_GPIO_Port,LCD_RW_Pin,GPIO_PIN_RESET);
	LCD_SENDBYTE(data);
	Delay_us(50);
}
void LCD_Init()
{
    HAL_Delay(20);             // Wait after power ON

    LCD_COMMAND(0x38);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x06);
    LCD_COMMAND(0x01);     // Function Set
    HAL_Delay(2);
}
void LCD_STRING(const char *str)
{
	while(*str)
	    {
	        LCD_DATA(*str);
	        str++;
	    }
}
