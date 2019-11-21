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
	uint8_t mfgIDReg = 0x06;		//expected 0x0054
	uint8_t rd_buf[2] = {0};

	//int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len);
	i2c_Read(sensorADDR, mfgIDReg, rd_buf, 2);
	
	port_pin_toggle_output_level( LED_0_PIN );

}

int main (void)
{
	system_init();
	config_board();

	usart_Hello();

	//uint8_t wr_buffer[I2C_DATA_LENGTH] = {0};
	//uint8_t rd_buffer[I2C_DATA_LENGTH] = {0};

	//wr_buffer[0] = 0x06;		
	//wr_buffer[1] = 0xAA;

	while(true)
	{
		//port_pin_toggle_output_level( LED_0_PIN );
		//delay_ms(100);

		//In Terminal, echo every 5 characters typed forever and toggle LED0
		//usart_Echo();
		
		sensorRead();

		/* Read from slave until success. */
		//i2c_Read(0x18, buffer, I2C_DATA_LENGTH);

		//i2c_Write(0x18, 0x06, 1);
		//i2c_Read(0x18, rd_buffer, 2);
		//port_pin_toggle_output_level( LED_0_PIN );

		//wr_buffer = rd_buffer & ~0x0100;
		/* Write buffer to slave until success. */
		//i2c_Write(0x18, wr_buffer, sizeof(wr_buffer));
		//port_pin_toggle_output_level( LED_0_PIN );


		delay_ms(100);


	}

}//main
