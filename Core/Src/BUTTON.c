/*
 * BUTTON.c
 *
 *  Created on: 29-Jun-2026
 *      Author: Hita Jadhav
 */

#include "BUTTON.h"

BUTTON_EVENT Button_Read(void)
{
    if(HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin)==GPIO_PIN_RESET);

        return BTN_MENU;
    }

    if(HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin)==GPIO_PIN_RESET);

        return BTN_LEFT;
    }

    if(HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin)==GPIO_PIN_RESET);

        return BTN_UP;
    }

    if(HAL_GPIO_ReadPin(SW5_GPIO_Port,SW5_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW5_GPIO_Port,SW5_Pin)==GPIO_PIN_RESET);

        return BTN_DOWN;
    }

    if(HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin)==GPIO_PIN_RESET);

        return BTN_ENTER;
    }

    if(HAL_GPIO_ReadPin(SW6_GPIO_Port,SW6_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(20);

        while(HAL_GPIO_ReadPin(SW6_GPIO_Port,SW6_Pin)==GPIO_PIN_RESET);

        return BTN_RIGHT;
    }

    return BTN_NONE;
}
