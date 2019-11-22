/*
 * SERCOM.c
 *
 * Created: 11/14/2019 12:13:27 PM
 *  Author: VKaiser
 */ 
 #include "DC_SERCOM.h"



/* Timeout counter. */
uint16_t timeout = 0;

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
 }//configure_usart

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
 }//configure_usart_callbacks

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
 }//usart_read_callback

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
 }//usart_write_callback

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
	int len = sizeof(string);
 	usart_write_buffer_wait(&usart_instance, string, len);
 }//usart_Hello

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
 }//usart_Echo

 /**********************************************************************
 * @fn					- configure_i2c_master
 * @brief				- Set up the I2C Master Module
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
  void configure_i2c_master(void)
 {
	 /* Initialize config structure and software module. */
	 i2c_master_get_config_defaults(&config_i2c_master);

	 /* Change buffer timeout to something longer. */
	 config_i2c_master.buffer_timeout = 10000;

	 /* Initialize and enable device with config. */
	 // SERCOM0 PAD[0] PA08 - SDA
	 // SERCOM0 PAD[1] PA09 - SCL
	 //i2c_master_init(&i2c_master_instance, SERCOM0, &config_i2c_master);
	 //config_i2c_master.pinmux_pad0    = PINMUX_PA08C_SERCOM0_PAD0;
	 //config_i2c_master.pinmux_pad1    = PINMUX_PA09C_SERCOM0_PAD1;

	//Xplained Pro board has one I2C shared between the 3 EXTn	- SERCOM2 PAD[0] and PAD[1] identified as PA08 and PA09
	//Therefore....
	 config_i2c_master.pinmux_pad0    = PINMUX_PA08D_SERCOM2_PAD0;
	 config_i2c_master.pinmux_pad1    = PINMUX_PA09D_SERCOM2_PAD1;
	
	 i2c_master_init(&i2c_master_instance, SERCOM2, &config_i2c_master);	 	
	 i2c_master_enable(&i2c_master_instance);

 }// configure_i2c_master

 /**********************************************************************
 * @fn					- configure_i2c_callbacks
 * @brief				- Write buffer to slave until success.
 *
 * @param[in]			- 
 *
 * @return				- void
 *
 * @note				- called from main
 **********************************************************************/
 void configure_i2c_callbacks(void)
{
	/* Register callback function. */

	i2c_master_register_callback(&i2c_master_instance, i2c_write_complete_callback,
			I2C_MASTER_CALLBACK_WRITE_COMPLETE);

	i2c_master_enable_callback(&i2c_master_instance,
			I2C_MASTER_CALLBACK_WRITE_COMPLETE);

}
//configure_i2c_callbacks

 /**********************************************************************
 * @fn					- i2c_Write
 * @brief				- Write buffer to slave until success.
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len)
 {

	// Merge Device Register and data to TX
 	uint8_t merged_packet[len + 1];
 	merged_packet[0] = reg_addr;
 	
 	for(uint16_t i = 0; i < len; i++)
 	merged_packet[i + 1] = write_buffer[i];

	write_packet.address = i2c_addr;
	write_packet.data = merged_packet;
	write_packet.data_length = len + 1;
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;

	while (i2c_master_write_packet_wait(&i2c_master_instance, &write_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
		return -1;
			break;
		}
	}

	return 0;
 } //i2c_Write

  /**********************************************************************
 * @fn					- i2c_Read
 * @brief				- Read from slave until success.
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};						
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len)
 {
	//Write to Address, Register
	read_packet.address = i2c_addr;
	read_packet.data = &reg_addr;
	read_packet.data_length = 1;
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;
	
	while (i2c_master_write_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	// Read from Address, register
	read_packet.data = read_buffer;
	read_packet.data_length = len;

	while (i2c_master_read_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK)
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	return 0;

 }// i2c_Read
 
/**********************************************************************
 * @fn					- i2c_write_complete_callback
 * @brief				- Read write to slave until success.
 *
 * @param[in]			- struct i2c_master_module
 * @param[in]			-  *const module					
 * @param[in]			- 
 *
 * @return				- void
 *
 * @note				- called from main
 **********************************************************************/ 
 void i2c_write_complete_callback(struct i2c_master_module *const module)
{
	/* Initiate new packet read */
	i2c_master_read_packet_job(&i2c_master_instance,&read_packet);
}
// i2c_write_complete_callback
 