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


void sensorRead(void)
{
	uint8_t sensorADDR = 0x18;
	uint8_t mfgIDReg = 0x06;		
	uint8_t rd_buf[2] = {0};	//expected 0x0054

	i2c_Read(sensorADDR, mfgIDReg, rd_buf, 2);	
	port_pin_toggle_output_level( LED_0_PIN );
}

void flashLED(void)
{
// IO Panel LEDs on PA06, PA05, PB14 and PB15
port_pin_toggle_output_level( LED_PWR_RED_PIN );
delay_ms(100);
port_pin_toggle_output_level( LED_PWR_GREEN_PIN );
delay_ms(100);
port_pin_toggle_output_level( LED_MEAS_WHITE_PIN );
delay_ms(100);
port_pin_toggle_output_level( LED_STOP_RED_PIN );

}

int main (void)
{
	system_init();
	config_board();

	usart_Hello();

	//uint8_t wr_buffer[I2C_DATA_LENGTH] = {0xAA};
	//uint8_t rd_buffer[I2C_DATA_LENGTH] = {0};
	
	uint8_t sensorADDR = 0x18;
	uint8_t cfgReg = 0x01;	
	uint8_t	wr_buffer[1] = {0xE0};		
	//uint8_t rd_buffer[1] = {0xAA};

	while(true)
	{
		//port_pin_toggle_output_level( LED_0_PIN );
		//delay_ms(100);

		//In Terminal, echo every 5 characters typed forever and toggle LED0
		//usart_Echo();
		
		sensorRead();
		delay_ms(100);

		i2c_Write(sensorADDR, cfgReg, wr_buffer, 1);
		port_pin_toggle_output_level( LED_0_PIN );
		delay_ms(100);

		flashLED();

	}

}//main
