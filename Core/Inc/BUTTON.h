/*
 * BUTTON.h
 *
 *  Created on: 29-Jun-2026
 *      Author: Hita Jadhav
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum
{
    BTN_NONE = 0,
    BTN_MENU,
    BTN_LEFT,
    BTN_UP,
    BTN_DOWN,
    BTN_ENTER,
    BTN_RIGHT

}BUTTON_EVENT;

BUTTON_EVENT Button_Read(void);


#endif /* INC_BUTTON_H_ */
