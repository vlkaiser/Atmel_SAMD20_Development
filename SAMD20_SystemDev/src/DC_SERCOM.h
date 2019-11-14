/*
 * SERCOM.h
 *
 * Created: 11/14/2019 12:13:36 PM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"

#define MAX_RX_BUFFER_LENGTH	5

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];


void configure_usart(void);
void configure_usart_callbacks(void);
void usart_read_callback( struct usart_module *const usart_module );
void usart_write_callback( struct usart_module *const usart_module );
void usart_Hello(void);
void usart_Echo(void);



#endif /* DC_SERCOM_H_ */