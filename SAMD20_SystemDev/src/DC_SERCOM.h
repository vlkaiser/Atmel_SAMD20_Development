/*
 * SERCOM.h
 *
 * Created: 11/14/2019 12:13:36 PM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"

 /*
 * Global Variables
 */
 struct usart_module	usart_instance;
 struct i2c_master_module i2c_master_instance;
 struct i2c_master_config config_i2c_master;
 struct i2c_master_packet write_packet;
 struct i2c_master_packet read_packet;


#define MAX_RX_BUFFER_LENGTH	5
#define I2C_SLAVE_ADDRESS		0x18
#define I2C_DATA_LENGTH			10
#define I2C_TIMEOUT				10

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

void configure_usart(void);
void configure_usart_callbacks(void);
void usart_read_callback( struct usart_module *const usart_module );
void usart_write_callback( struct usart_module *const usart_module );
void usart_Hello(void);
void usart_Echo(void);

void configure_i2c_master(void);
void configure_i2c_callbacks(void);

int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len);

void i2c_write_complete_callback(struct i2c_master_module *const module);


#endif /* DC_SERCOM_H_ */