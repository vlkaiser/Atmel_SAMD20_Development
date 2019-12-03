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
/* TODO: Tesseract Definitions LEDs:
#define LED_PWR_RED_PIN				PIN_PA05
#define LED_PWR_GREEN_PIN			PIN_PA06
#define LED_MEAS_WHITE_PIN			PIN_PB14
#define LED_STOP_RED_PIN			PIN_PB02
*/
/* TODO: Tesseract Definitions PBs:
#define PB_PWR_PIN					PIN_PB00
#define PB_MEAS_PIN					PIN_PB01
#define PB_STOP_PIN					PIN_PB02
*/

#define LED_ACTIVE					FALSE
#define LED_INACTIVE				~LED_ACTIVE

#define PB_ACTIVE					FALSE
#define PB_INACTIVE					!PB_ACTIVE

//Interrupt Definitions 
//TODO - Flesh out Interrupt Definitions for PushButtons on IO Panel
//These PIN definitions are temporary for Xplained board
#define LED_PWR_RED_PIN				PIN_PA05
#define LED_PWR_GREEN_PIN			PIN_PA20
#define LED_MEAS_WHITE_PIN			PIN_PA21
#define LED_STOP_RED_PIN			PIN_PB15

#define PB_PWR_PIN					PIN_PB05
#define PB_PWR_EIC_PIN				PIN_PB05A_EIC_EXTINT5	
#define PB_PWR_EIC_MUX				MUX_PB05A_EIC_EXTINT5
#define PB_PWR_EIC_PINMUX			PINMUX_PB05A_EIC_EXTINT5
#define PB_PWR_EIC_LINE				05

#define BUTTON_PWR_PIN				PB_PWR_PIN
#define BUTTON_PWR_EIC_PIN			PB_PWR_EIC_PIN	
#define BUTTON_PWR_EIC_MUX			PB_PWR_EIC_MUX
#define BUTTON_PWR_EIC_PINMUX		PB_PWR_EIC_PINMUX
#define BUTTON_PWR_EIC_LINE			PB_PWR_EIC_LINE
/* 
@
*/
#define PB_MEAS_PIN					PIN_PB06
#define PB_MEAS_EIC_PIN				PIN_PB06A_EIC_EXTINT6
#define PB_MEAS_EIC_MUX				MUX_PB06A_EIC_EXTINT6
#define PB_MEAS_EIC_PINMUX			PINMUX_PB06A_EIC_EXTINT6
#define PB_MEAS_EIC_LINE			06

#define BUTTON_MEAS_PIN				PB_MEAS_PIN
#define BUTTON_MEAS_EIC_PIN			PB_MEAS_EIC_PIN
#define BUTTON_MEAS_EIC_MUX			PB_MEAS_EIC_MUX
#define BUTTON_MEAS_EIC_PINMUX		PB_MEAS_EIC_PINMUX
#define BUTTON_MEAS_EIC_LINE		PB_MEAS_EIC_LINE
/*
@
*/
#define PB_ESTOP_PIN				PIN_PB07
#define PB_ESTOP_EIC_PIN			PIN_PB07A_EIC_EXTINT7
#define PB_ESTOP_EIC_MUX			MUX_PB07A_EIC_EXTINT7
#define PB_ESTOP_EIC_PINMUX			PINMUX_PB07A_EIC_EXTINT7
#define PB_ESTOP_EIC_LINE			07

#define BUTTON_ESTOP_PIN			PB_ESTOP_PIN
#define BUTTON_ESTOP_EIC_PIN		PB_ESTOP_EIC_PIN
#define BUTTON_ESTOP_EIC_MUX		PB_ESTOP_EIC_MUX
#define BUTTON_ESTOP_EIC_PINMUX		PB_ESTOP_EIC_PINMUX
#define BUTTON_ESTOP_EIC_LINE		PB_ESTOP_EIC_LINE

//Xplained Pro Onboard Definition are in User_Board.h


/* Prototypes */
void config_led(void);
void config_IO_LEDS(void);

void configure_extint_channel0(void);
void configure_extint_Power(void);
void configure_extint_Measure(void);
void configure_extint_EStop(void);

void configure_extint_callbacks(void);

void extint_detection_callback(void);
void extint_detection_callback_pwr(void);
void extint_detection_callback_meas(void);
void extint_detection_callback_estop(void);

#endif /* DC_PERIPHERALS_H_ */