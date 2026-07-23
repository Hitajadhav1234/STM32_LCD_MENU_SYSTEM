/*
 * menu.h
 *
 *  Created on: 29-Jun-2026
 *      Author: Hita Jadhav
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "main.h"

typedef enum
{
    BOOT_SCREEN = 0,
    HOME_SCREEN,
    MAIN_MENU,
    GPIO_MENU,
    LED1_MENU,
    LED2_MENU,

    PWM_MENU,
	DUTY_MENU,
	FREQ_MENU,

	ADC_MENU,

    UART_MENU,
    BAUD_MENU,
    PARITY_MENU,

	RTC_MENU,
	DATE_MENU,
	TIME_MENU,
    SETTINGS_MENU,
	CONTRAST_MENU,
	BRIGHTNESS_MENU

}MENU_STATE;

extern MENU_STATE CurrentState;
extern uint8_t LED1_State;
extern uint8_t LED2_State;

extern uint8_t PWMDuty;
extern uint16_t PWMFreq;

extern uint16_t ADCValue;

extern uint32_t BaudRate;

extern uint8_t Hour;
extern uint8_t Minute;

extern uint8_t Date;
extern uint8_t Month;

void Menu_Task(void);
void Menu_Display(void);
void GPIO_Display(void);
void PWM_Display(void);
void Duty_Display(void);
void Frequency_Display(void);
void ADC_Display(void);
void UART_Display(void);
void Baud_Display (void);
void Parity_Display (void);
void RTC_Display(void);
void Time_Display(void);
void Date_Display(void);
void Settings_Display(void);
void Brightness_Display(void);
void Contrast_Display(void);
#endif /* INC_MENU_H_ */
