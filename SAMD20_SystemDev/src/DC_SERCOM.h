/*
 * SERCOM.h
 *
 * Created: 11/14/2019 12:13:36 PM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"

#define CONF_I2C_MASTER_MODULE SERCOM0

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
//void i2c_Write(void);
//void i2c_Read(void);
//TODO - Update with a Return for status
void i2c_Write(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t size);
void i2c_Read(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t size);



#endif /* DC_SERCOM_H_ */