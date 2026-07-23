/*
 * dashboard.c
 *
 *  Created on: 30-Jun-2026
 *      Author: Hita Jadhav
 */

#include "dashboard.h"
#include "lcd.h"
#include "menu.h"
uint8_t DashboardPage = 0;

void Dashboard_Display(void)
{

	LCD_COMMAND(0x01);

	    switch(DashboardPage)
	    {
	    	case 0:

	            LCD_STRING("DASHBOARD_");
	            LCD_COMMAND(0xC0);

	        /*---------------- Page 1 ----------------*/

	            LCD_STRING("LD1:");

	            if(LED1_State)
	                LCD_STRING("ON ");
	            else
	                LCD_STRING("OFF ");

	            LCD_COMMAND(0xC8);      // Move cursor to column 9 of second line

	            LCD_STRING("LD2:");

	            if(LED2_State)
	                LCD_STRING("ON");
	            else
	                LCD_STRING("OFF");
	        break;
	        /*---------------- Page 2 ----------------*/
	        case 1:

	            LCD_STRING("Duty:");

	            if(PWMDuty == 100)
	            {
	                LCD_DATA('1');
	                LCD_DATA('0');
	                LCD_DATA('0');
	            }
	            else
	            {
	                if(PWMDuty >= 10)
	                {
	                    LCD_DATA((PWMDuty/10)+'0');
	                    LCD_DATA((PWMDuty%10)+'0');
	                }
	                else
	                {
	                    LCD_DATA(PWMDuty+'0');
	                }
	            }

	            LCD_DATA('%');

	            LCD_COMMAND(0xC0);

	            LCD_STRING("Freq:");

	            LCD_DATA((PWMFreq/1000)+'0');
	            LCD_DATA(((PWMFreq%1000)/100)+'0');
	            LCD_DATA(((PWMFreq%100)/10)+'0');
	            LCD_DATA((PWMFreq%10)+'0');

	        break;

	        /*---------------- Page 3 ----------------*/
	        case 2:

	            LCD_STRING("ADC:");

	            LCD_DATA((ADCValue/100)+'0');
	            LCD_DATA('.');
	            LCD_DATA(((ADCValue%100)/10)+'0');
	            LCD_DATA((ADCValue%10)+'0');

	            LCD_COMMAND(0xC0);

	            LCD_STRING("UART:");

	            if(BaudRate == 115200)
	                LCD_STRING("115K");
	            else if(BaudRate == 57600)
	                LCD_STRING("57K");
	            else if(BaudRate == 38400)
	                LCD_STRING("38K");
	            else if(BaudRate == 19200)
	                LCD_STRING("19K");
	            else
	                LCD_STRING("9600");

	        break;

	        /*---4------------ Page 4 ----------------*/
	        case 3:

	            LCD_STRING("T:");

	            LCD_DATA((Hour/10)+'0');
	            LCD_DATA((Hour%10)+'0');

	            LCD_DATA(':');

	            LCD_DATA((Minute/10)+'0');
	            LCD_DATA((Minute%10)+'0');

	            LCD_COMMAND(0xC0);

	            LCD_STRING("D:");

	            LCD_DATA((Date/10)+'0');
	            LCD_DATA((Date%10)+'0');

	            LCD_DATA('/');

	            LCD_DATA((Month/10)+'0');
	            LCD_DATA((Month%10)+'0');

	        break;
	    }
}
