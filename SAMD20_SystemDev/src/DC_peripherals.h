/*
 * Peripherals.h
 *
 * Created: 11/14/2019 11:27:53 AM
 *  Author: VKaiser
 */ 


#ifndef DC_PERIPHERALS_H_
#define DC_PERIPHERALS_H_

#include "main.h"
//#include "user_board.h"

/* Define IO Panel LEDs and Push Buttons */
#define LED_PWR_RED_PIN           PIN_PA05
#define LED_PWR_GREEN_PIN         PIN_PA06
#define LED_MEAS_WHITE_PIN        PIN_PB14
#define LED_STOP_RED_PIN          PIN_PB02

#define PB_PWR_PIN                PIN_PB00
#define PB_MEAS_PIN               PIN_PB01
#define PB_STOP_PIN               PIN_PB02

#define LED_ACTIVE				  FALSE
#define LED_INACTIVE			  ~LED_ACTIVE

#define PB_ACTIVE                FALSE
#define PB_INACTIVE              !PB_ACTIVE

//Interrupt Definitions 
//TODO - Flesh out Interrupt Definitions for PushButtons on IO Panel
/*
*/

//Xplained Pro Onboard Definition are in User_Board.h


/* Prototypes */
void config_led(void);
void config_IO_LEDS(void);

void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);

#endif /* DC_PERIPHERALS_H_ */