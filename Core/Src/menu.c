/*
 * menu.c
 *
 *  Created on: 29-Jun-2026
 *      Author: Hita Jadhav
 */

#include "menu.h"
#include "lcd.h"
#include "button.h"

const char *MainMenu[] =
{
    "GPIO Test",
    "PWM Control",
    "ADC Monitor",
    "UART Test",
    "RTC Clock",
    "Settings"
};
const char *GPIO_Menu[] =
{
    "LED1",
    "LED2",
};
const char *PWM_Menu[] =
{
    "Duty",
    "Frequency"
};
const char *UART_Menu[]=
{

		"BaudRate",
		"Parity"
};
const char *PARITY_Menu[]=
{
		"NONE",
		"EVEN",
		 "ODD"
};
const char *RTC_Menu[] =
{
    "Time",
    "Date"
};

const char *Settings_Menu[] =
{
    "Brightness",
    "Contrast",
    "Reset"
};
MENU_STATE CurrentState = HOME_SCREEN;
uint8_t MenuIndex = 0;
uint8_t DisplayIndex=0;
uint8_t HomePage = 0;
uint8_t GPIOIndex = 0;
uint8_t GPIODisplayIndex = 0;
uint8_t LED1_State = 0;
uint8_t LED2_State = 0;
uint8_t PWMIndex = 0;

uint8_t PWMDuty =50;      // %
uint16_t PWMFreq = 1000;   //Hz
uint16_t ADCValue = 330;
uint8_t UARTIndex = 0;

uint32_t BaudRate = 115200;

uint8_t Parity = 0;

uint8_t RTCIndex = 0;

uint8_t Hour = 12;
uint8_t Minute = 30;

uint8_t DateCursor = 0;
uint8_t TimeCursor = 0;
uint8_t Date = 29;
uint8_t Month = 6;
uint16_t Year = 2026;

uint8_t SettingsIndex = 0;

uint8_t Brightness = 5;
uint8_t Contrast = 5;
void Menu_Task(void)
{
    BUTTON_EVENT Key;

    Key = Button_Read();

    switch(CurrentState)
    {
        case HOME_SCREEN:

            if(Key == BTN_RIGHT)
            {
                if(DashboardPage < 3)
                    DashboardPage++;
                else
                    DashboardPage = 0;

                Dashboard_Display();
            }

            if(Key == BTN_LEFT)
            {
                if(DashboardPage > 0)
                    DashboardPage--;
                else
                    DashboardPage = 3;

                Dashboard_Display();
            }

            if(Key == BTN_MENU)
            {
                MenuIndex = 0;
                DisplayIndex = 0;

                Menu_Display();

                CurrentState = MAIN_MENU;
            }

        break;

        case MAIN_MENU:
        	if(Key == BTN_DOWN)
        	{
        	    if(MenuIndex < 5)
        	    {
        	        MenuIndex++;

        	        if(MenuIndex > (DisplayIndex + 1))
        	        {
        	            DisplayIndex ++;
        	        }

        	        Menu_Display();
        	    }
        	}
        	if(Key == BTN_UP)
        	{
        	    if(MenuIndex > 0)
        	    {
        	        MenuIndex--;

        	        if(MenuIndex < DisplayIndex)
        	        {
        	            DisplayIndex --;
        	        }

        	        Menu_Display();
        	    }
        	}
        	if(Key == BTN_ENTER)
        	{
        	    if(MenuIndex == 0)
        	    {
        	        GPIOIndex = 0;
        	        GPIODisplayIndex = 0;

        	        GPIO_Display();

        	        CurrentState = GPIO_MENU;
        	    }
        	}
        	if(Key == BTN_ENTER)
        	{
        	    if(MenuIndex == 1)
        	    {
        	        PWMIndex = 0;

        	        PWM_Display();

        	        CurrentState = PWM_MENU;
        	    }
        	}
        	if(Key == BTN_ENTER)
        	{
        	    if(MenuIndex == 2)
        	    {
        	        ADC_Display();

        	        CurrentState = ADC_MENU;
        	    }
        	}
        	if(Key == BTN_ENTER)
        	{
        		if(MenuIndex == 3)
        		{
        			UART_Display();
        			CurrentState = UART_MENU;
        		}
        	}
        	if(Key == BTN_ENTER)
        	{
        		if(MenuIndex == 4)
        		{
        			RTC_Display();
        			CurrentState = RTC_MENU;
        		}
        	}
        	if( Key == BTN_ENTER)
        	{
        		if(MenuIndex == 5)
        		{
        			Settings_Display();
        			CurrentState = SETTINGS_MENU;
        		}
        	}
        	if(Key == BTN_MENU)
        	{
        	    DashboardPage = 0;          // Always return to the Dashboard welcome page
        	    Dashboard_Display();        // Display "DASHBOARD"
        	    CurrentState = HOME_SCREEN;
        	}

        break;
        case GPIO_MENU:
        	if(Key == BTN_DOWN)
        	{
        	    if(GPIOIndex < 1)
        	    {
        	        GPIOIndex++;

        	        if(GPIOIndex > (GPIODisplayIndex + 1))
        	        {
        	            GPIODisplayIndex ++;
        	        }

        	        GPIO_Display();
        	    }
        	}
        	if(Key == BTN_UP)
        	{
        	    if(GPIOIndex >0)
        	    {
        	        GPIOIndex--;

        	        if(GPIOIndex < GPIODisplayIndex)
        	        {
        	            GPIODisplayIndex --;
        	        }

        	        GPIO_Display();
        	    }
        	}
            if(Key == BTN_MENU)
            {
                Menu_Display();

                CurrentState = MAIN_MENU;
            }
            if(Key == BTN_ENTER)
            {
                if(GPIOIndex == 0)
                {
                    CurrentState = LED1_MENU;

                    LCD_COMMAND(0x01);

                    if(LED1_State)
                        LCD_STRING("LED1 : ON");
                    else
                        LCD_STRING("LED1 : OFF");
                }

                else if(GPIOIndex == 1)
                {
                    CurrentState = LED2_MENU;

                    LCD_COMMAND(0x01);

                    if(LED2_State)
                        LCD_STRING("LED2 : ON");
                    else
                        LCD_STRING("LED2 : OFF");
                }

                else if(GPIOIndex == 2)
                {
                    Menu_Display();

                    CurrentState = MAIN_MENU;
                }
            }

        break;
        case LED1_MENU:

            if(Key == BTN_ENTER)
            {
                LED1_State = !LED1_State;

                HAL_GPIO_WritePin(LED1_GPIO_Port,
                                  LED1_Pin,
                                  LED1_State ? GPIO_PIN_SET : GPIO_PIN_RESET);

                LCD_COMMAND(0x01);

                if(LED1_State)
                    LCD_STRING("LED1 : ON");
                else
                    LCD_STRING("LED1 : OFF");
            }

            if(Key == BTN_MENU)
            {
                GPIO_Display();

                CurrentState = GPIO_MENU;
            }

        break;
        case LED2_MENU:

            if(Key == BTN_ENTER)
            {
                LED2_State = !LED2_State;

                HAL_GPIO_WritePin(LED2_GPIO_Port,
                                  LED2_Pin,
                                  LED2_State ? GPIO_PIN_SET : GPIO_PIN_RESET);

                LCD_COMMAND(0x01);

                if(LED2_State)
                    LCD_STRING("LED2 : ON");
                else
                    LCD_STRING("LED2 : OFF");
            }

            if(Key == BTN_MENU)
            {
                GPIO_Display();

                CurrentState = GPIO_MENU;
            }

        break;
        case PWM_MENU:

            if(Key == BTN_DOWN)
            {
                if(PWMIndex < 1)
                {
                    PWMIndex++;
                    PWM_Display();
                }
            }

            if(Key == BTN_UP)
            {
                if(PWMIndex > 0)
                {
                    PWMIndex--;
                    PWM_Display();
                }
            }

            if(Key == BTN_ENTER)
            {
                if(PWMIndex == 0)
                {
                    LCD_COMMAND(0x01);
                    Duty_Display();

                    CurrentState = DUTY_MENU;
                }

                else if(PWMIndex == 1)
                {
                    LCD_COMMAND(0x01);
                    Frequency_Display();

                    CurrentState = FREQ_MENU;
                }
            }

            if(Key == BTN_MENU)
            {
                Menu_Display();
                CurrentState = MAIN_MENU;
            }

        break;
        case DUTY_MENU:
        	if(Key == BTN_UP)
        	{
        	    if(PWMDuty < 100)
        	    {
        	        PWMDuty += 5;
        	    }

        	    Duty_Display();
        	}

        	if(Key == BTN_DOWN)
        	{
        	    if(PWMDuty > 0)
        	    {
        	        PWMDuty -= 5;
        	    }

        	    Duty_Display();
        	}
            if(Key == BTN_MENU)
            {
                PWM_Display();
                CurrentState = PWM_MENU;
            }

        break;
        case FREQ_MENU:
            if(Key == BTN_UP)
            {
                if(PWMFreq < 5000)
                    PWMFreq += 100;

                Frequency_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(PWMFreq > 100)
                    PWMFreq -= 100;

                Frequency_Display();
            }
            if(Key == BTN_MENU)
            {
                PWM_Display();
                CurrentState = PWM_MENU;
            }

        break;
        case ADC_MENU:

            if(Key == BTN_UP)
            {
                if(ADCValue < 500)
                    ADCValue += 5;

                ADC_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(ADCValue > 0)
                    ADCValue -= 5;

                ADC_Display();
            }

            if(Key == BTN_MENU)
            {
                Menu_Display();

                CurrentState = MAIN_MENU;
            }

        break;
        case UART_MENU:
        	if(Key == BTN_DOWN)
        	            {
        	                if(UARTIndex < 1)
        	                {
        	                    UARTIndex++;
        	                    UART_Display();
        	                }
        	            }

        	            if(Key == BTN_UP)
        	            {
        	                if(UARTIndex > 0)
        	                {
        	                    UARTIndex--;
        	                    UART_Display();
        	                }
        	            }

        	            if(Key == BTN_ENTER)
        	            {
        	                if(UARTIndex == 0)
        	                {
        	                    LCD_COMMAND(0x01);
        	                    Baud_Display();

        	                    CurrentState = BAUD_MENU;
        	                }

        	                else if(UARTIndex == 1)
        	                {
        	                    LCD_COMMAND(0x01);
        	                    Parity_Display();

        	                    CurrentState = PARITY_MENU;
        	                }
        	            }
        	            if(Key == BTN_MENU)
        	            {
        	                Menu_Display();
        	                CurrentState = MAIN_MENU;
        	            }
        	    break;
        case BAUD_MENU:
        	if(Key == BTN_UP)
        	    {
        	        if(BaudRate == 9600)
        	            BaudRate = 19200;

        	        else if(BaudRate == 19200)
        	            BaudRate = 38400;

        	        else if(BaudRate == 38400)
        	            BaudRate = 57600;

        	        else if(BaudRate == 57600)
        	            BaudRate = 115200;

        	        Baud_Display();
        	    }

        	    if(Key == BTN_DOWN)
        	    {
        	        if(BaudRate == 115200)
        	            BaudRate = 57600;

        	        else if(BaudRate == 57600)
        	            BaudRate = 38400;

        	        else if(BaudRate == 38400)
        	            BaudRate = 19200;

        	        else if(BaudRate == 19200)
        	            BaudRate = 9600;

        	        Baud_Display();
        	    }

        	    if(Key == BTN_MENU)
        	    {
        	        UART_Display();

        	        CurrentState = UART_MENU;
        	    }

        	break;
        case PARITY_MENU:
        	if(Key == BTN_UP)
        	    {
        	        if(Parity < 2)
        	        {
        	            Parity++;
        	        }

        	        Parity_Display();
        	    }

        	    if(Key == BTN_DOWN)
        	    {
        	        if(Parity > 0)
        	        {
        	            Parity--;
        	        }

        	        Parity_Display();
        	    }

        	    if(Key == BTN_MENU)
        	    {
        	        UART_Display();

        	        CurrentState = UART_MENU;
        	    }

        	break;
        case RTC_MENU:

            if(Key == BTN_DOWN)
            {
                if(RTCIndex < 1)
                {
                    RTCIndex++;
                    RTC_Display();
                }
            }

            if(Key == BTN_UP)
            {
                if(RTCIndex > 0)
                {
                    RTCIndex--;
                    RTC_Display();
                }
            }

            if(Key == BTN_ENTER)
            {
                if(RTCIndex == 0)
                {
                    Time_Display();

                    CurrentState = TIME_MENU;
                }

                else if(RTCIndex == 1)
                {
                    Date_Display();

                    CurrentState = DATE_MENU;
                }
            }

            if(Key == BTN_MENU)
            {
                Menu_Display();

                CurrentState = MAIN_MENU;
            }

        break;
        case TIME_MENU:
            if(Key == BTN_LEFT)
            {
                if(TimeCursor > 0)
                {
                    TimeCursor--;
                }

                Time_Display();
            }

            if(Key == BTN_RIGHT)
            {
                if(TimeCursor < 1)
                {
                    TimeCursor++;
                }

                Time_Display();
            }
            if(Key == BTN_UP)
            {
                if(TimeCursor == 0)          // Cursor on Hour
                {
                    if(Hour < 23)
                        Hour++;
                }
                else                         // Cursor on Minute
                {
                    if(Minute < 59)
                        Minute++;
                }

                Time_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(TimeCursor == 0)
                {
                    if(Hour > 0)
                        Hour--;
                }
                else
                {
                    if(Minute > 0)
                        Minute--;
                }

                Time_Display();
            }

            if(Key == BTN_MENU)
            {
                RTC_Display();

                CurrentState = RTC_MENU;
            }

        break;
        case DATE_MENU:
            if(Key == BTN_LEFT)
            {
                if(DateCursor > 0)
                {
                    DateCursor--;
                }

                Date_Display();
            }

            if(Key == BTN_RIGHT)
            {
                if(DateCursor < 1)
                {
                	DateCursor++;
                }

                Date_Display();
            }

            if(Key == BTN_UP)
            {
                if(DateCursor == 0)          // Date selected
                {
                    if(Date < 31)
                        Date++;
                }
                else                         // Month selected
                {
                    if(Month < 12)
                        Month++;
                }

                Date_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(DateCursor == 0)
                {
                    if(Date > 1)
                        Date--;
                }
                else
                {
                    if(Month > 1)
                        Month--;
                }

                Date_Display();
            }
            if(Key == BTN_MENU)
            {
                RTC_Display();

                CurrentState = RTC_MENU;
            }

        break;
        case SETTINGS_MENU:

            if(Key == BTN_DOWN)
            {
                if(SettingsIndex < 1)
                {
                    SettingsIndex++;

                    Settings_Display();
                }
            }

            if(Key == BTN_UP)
            {
                if(SettingsIndex > 0)
                {
                    SettingsIndex--;

                    Settings_Display();
                }
            }

            if(Key == BTN_ENTER)
            {
                if(SettingsIndex == 0)
                {
                    Brightness_Display();

                    CurrentState = BRIGHTNESS_MENU;
                }

                else if(SettingsIndex == 1)
                {
                    Contrast_Display();

                    CurrentState = CONTRAST_MENU;
                }
            }

            if(Key == BTN_MENU)
            {
                Menu_Display();

                CurrentState = MAIN_MENU;
            }

        break;
        case BRIGHTNESS_MENU:

            if(Key == BTN_UP)
            {
                if(Brightness < 9)
                    Brightness++;

                Brightness_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(Brightness > 0)
                    Brightness--;

                Brightness_Display();
            }

            if(Key == BTN_MENU)
            {
                Settings_Display();

                CurrentState = SETTINGS_MENU;
            }

        break;
        case CONTRAST_MENU:

            if(Key == BTN_UP)
            {
                if(Contrast < 9)
                    Contrast++;

                Contrast_Display();
            }

            if(Key == BTN_DOWN)
            {
                if(Contrast > 0)
                    Contrast--;

                Contrast_Display();
            }

            if(Key == BTN_MENU)
            {
                Settings_Display();

                CurrentState = SETTINGS_MENU;
            }

        break;
        default:

        break;
    }
}

//void Menu_Display(void)
//{
//    LCD_COMMAND(0x01);
//
//    if(MenuIndex == 0)
//    {
//        LCD_STRING("> GPIO Test");
//
//        LCD_COMMAND(0xC0);
//
//        LCD_STRING("  PWM Control");
//    }
//
//    else if(MenuIndex == 1)
//    {
//        LCD_STRING("  GPIO Test");
//
//        LCD_COMMAND(0xC0);
//
//        LCD_STRING("> PWM Control");
//    }
//}
void Menu_Display(void)
{
    LCD_COMMAND(0x01);

    /* First Line */

    if(MenuIndex == DisplayIndex)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(MainMenu[DisplayIndex]);

    /* Second Line */

    LCD_COMMAND(0xC0);

    if(MenuIndex == DisplayIndex + 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(MainMenu[DisplayIndex + 1]);
}

void GPIO_Display(void)
{
    LCD_COMMAND(0x01);

    if(GPIOIndex == GPIODisplayIndex)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(GPIO_Menu[GPIODisplayIndex]);

    LCD_COMMAND(0xC0);

    if(GPIOIndex == GPIODisplayIndex + 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(GPIO_Menu[GPIODisplayIndex + 1]);
}

void PWM_Display(void)
{
    LCD_COMMAND(0x01);

    if(PWMIndex == 0)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(PWM_Menu[0]);

    LCD_COMMAND(0xC0);

    if(PWMIndex == 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(PWM_Menu[1]);
}

void Duty_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("Duty : ");

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
            LCD_DATA((PWMDuty / 10) + '0');
            LCD_DATA((PWMDuty % 10) + '0');
        }
        else
        {
            LCD_DATA(PWMDuty + '0');
        }
    }

    LCD_DATA('%');
}
void Frequency_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("Freq : ");

    LCD_DATA((PWMFreq / 1000) + '0');
    LCD_DATA(((PWMFreq % 1000) / 100) + '0');
    LCD_DATA(((PWMFreq % 100) / 10) + '0');
    LCD_DATA((PWMFreq % 10) + '0');

    LCD_STRING("Hz");
}

void ADC_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("ADC : ");

    LCD_DATA((ADCValue / 100) + '0');
    LCD_DATA('.');

    LCD_DATA(((ADCValue % 100) / 10) + '0');
    LCD_DATA((ADCValue % 10) + '0');

    LCD_DATA('V');
}

void UART_Display(void)
{
    LCD_COMMAND(0x01);

    if(UARTIndex == 0)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(UART_Menu[0]);

    LCD_COMMAND(0xC0);

    if(UARTIndex == 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(UART_Menu[1]);
}

void Baud_Display(void)
{
	LCD_COMMAND(0X01);
	LCD_STRING("BAUD RATE:");
	if(BaudRate == 9600)
	    {
	        LCD_STRING("9600");
	    }
	    else if(BaudRate == 19200)
	    {
	        LCD_STRING("19200");
	    }
	    else if(BaudRate == 38400)
	    {
	        LCD_STRING("38400");
	    }
	    else if(BaudRate == 57600)
	    {
	        LCD_STRING("57600");
	    }
	    else if(BaudRate == 115200)
	    {
	        LCD_STRING("115200");
	    }
}

void Parity_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("PARITY : ");

    LCD_STRING(PARITY_Menu[Parity]);
}

void RTC_Display(void)
{
    LCD_COMMAND(0x01);

    if(RTCIndex == 0)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(RTC_Menu[0]);

    LCD_COMMAND(0xC0);

    if(RTCIndex == 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING(RTC_Menu[1]);
}

void Time_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("TIME : ");

    if(TimeCursor == 0)
        LCD_DATA('>');

    LCD_DATA((Hour/10)+'0');
    LCD_DATA((Hour%10)+'0');

    if(TimeCursor == 0)
        LCD_DATA('<');

    LCD_DATA(':');

    if(TimeCursor == 1)
        LCD_DATA('>');

    LCD_DATA((Minute/10)+'0');
    LCD_DATA((Minute%10)+'0');

    if(TimeCursor == 1)
        LCD_DATA('<');
}
void Date_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("DATE : ");

    if(DateCursor == 0)
        LCD_DATA('>');

    LCD_DATA((Date/10)+'0');
    LCD_DATA((Date%10)+'0');

    if(DateCursor == 0)
        LCD_DATA('<');

    LCD_DATA('/');

    if(DateCursor == 1)
        LCD_DATA('>');

    LCD_DATA((Month/10)+'0');
    LCD_DATA((Month%10)+'0');

    if(DateCursor == 1)
        LCD_DATA('<');
}

void Settings_Display(void)
{
    LCD_COMMAND(0x01);

    if(SettingsIndex == 0)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING("Brightness");

    LCD_COMMAND(0xC0);

    if(SettingsIndex == 1)
        LCD_DATA('>');
    else
        LCD_DATA(' ');

    LCD_STRING("Contrast");
}
void Brightness_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("Bright : ");

    LCD_DATA(Brightness + '0');
}
void Contrast_Display(void)
{
    LCD_COMMAND(0x01);

    LCD_STRING("Contrast : ");

    LCD_DATA(Contrast + '0');
}
