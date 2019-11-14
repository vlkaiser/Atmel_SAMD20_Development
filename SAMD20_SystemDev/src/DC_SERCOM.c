/*
 * SERCOM.c
 *
 * Created: 11/14/2019 12:13:27 PM
 *  Author: VKaiser
 */ 
 #include "DC_SERCOM.h"

 /* 
* Global Variables 
*/
struct usart_module	usart_instance;
uint8_t newLine[] = "\r\n";

/* 
* Function Definitions 
*/

/**********************************************************************
 * @fn					- configure_usart
 * @brief				- Configure USART for SAMD20J18 PA24 (TX) and PA25 (RX)
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/

 void configure_usart(void)
 {
	 struct usart_config config_usart;			//create instance of usart_config
	 usart_get_config_defaults(&config_usart);	//get defaults

	 config_usart.baudrate		= 9600;
	 config_usart.mux_setting	= USART_RX_3_TX_2_XCK_3;
	 config_usart.pinmux_pad2	= PINMUX_PA24C_SERCOM3_PAD2;
	 config_usart.pinmux_pad3	= PINMUX_PA25C_SERCOM3_PAD3;

	 while ( usart_init( &usart_instance, SERCOM3, &config_usart ) != STATUS_OK ) { }
	 usart_enable( &usart_instance );
 }

 /**********************************************************************
 * @fn					- configure_usart_callbacks
 * @brief				- Configure USART Callbacks for SAMD20J18
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
 void configure_usart_callbacks(void)
 {
	 usart_register_callback(&usart_instance, usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	 usart_register_callback(&usart_instance, usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	 usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	 usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
 }

  /**********************************************************************
 * @fn					- usart_read_callback
 * @brief				- Print Echo, read buffer, write buffer.
 *
 * @param[in]			- usart_module
 * @return				- void
 *
 * @note				- Interrupt Callback 
 **********************************************************************/
 void usart_read_callback( struct usart_module *const usart_module )
 {
	 UINT8 echoString[] = "\r\nEcho: ";
	 usart_write_buffer_wait(&usart_instance, echoString, sizeof(echoString));
	 usart_write_buffer_job( &usart_instance,(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH );
 }

   /**********************************************************************
 * @fn					- usart_write_callback
 * @brief				- Toggle PA14 (LED), print newline
 *
 * @param[in]			- usart_module
 * @return				- void
 *
 * @note				- Interrupt Callback
 **********************************************************************/
 void usart_write_callback( struct usart_module *const usart_module )
 {
	 port_pin_toggle_output_level( LED_0_PIN );
	 usart_write_buffer_wait(&usart_instance, newLine, sizeof(newLine));
 }

 /**********************************************************************
 * @fn					- usart_Hello
 * @brief				- print 'hello world' on terminal
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- called from main
 **********************************************************************/
  void usart_Hello(void)
 {
 	uint8_t string[] = "Hello World!\r\n";
 	usart_write_buffer_wait(&usart_instance, string, sizeof(string));
 }

  /**********************************************************************
 * @fn					- usart_Echo
 * @brief				- Perform an asynchronous read of the USART, 
 *                        which will fire the registered callback when characters are received.
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- called from main
 **********************************************************************/
  void usart_Echo(void)
 {
 	usart_read_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
	//TODO - Respond to CR, expand buffer
 }