/***************************************************************************************************************************
* Project							: SAMD20 System Development
* Program Name						:
* Author							: vkaiser
* Date Created						: Nov-14-2019
*
* Purpose							: Implement GPIO 
*									: Implement USART
*									: Implement I2C between two SAMD20 MCUs; One as MS, one as SL
*
*
* MCU								: ATSAMD20J18
* Language							: C
* Hardware Modifications			: N/A
* Debugger							: EDBG (On-board)
*
* Repo / Revision History			: https://github.com/vlkaiser/
*
* - Special Setup -
*  Header files for all drivers that have been imported from Atmel Software Framework (ASF).
*  Use in conjunction with			:
*  Wiring Details					:
*
* Revision History					:
* 	Date				Author			Notes
* 						vkaiser			- Initial commit
*
***************************************************************************************************************************/
#include "main.h"

void SysTick_Handler(void)
{
	// Your code goes here
}

int main (void)
{
	system_init();
	config_board();

	while(true)
	{
		port_pin_toggle_output_level( LED_0_PIN );
		delay_ms(100);
	}

}//main
