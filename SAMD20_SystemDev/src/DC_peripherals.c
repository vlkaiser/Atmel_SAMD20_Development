/*
 * Peripherals.c
 *
 * Created: 11/14/2019 11:27:38 AM
 *  Author: VKaiser
 */ 

 #include "DC_peripherals.h"
 


 /** Configure LED0, turn it off*/
 void config_led(void)
 {
	 struct port_config pin_conf;
	 port_get_config_defaults(&pin_conf);

	 pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	 port_pin_set_config(LED_0_PIN, &pin_conf);
	 port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
 
}

void config_board(void)
{
 	/*Configure system tick to generate periodic interrupts */
 	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	config_led();
	delay_init();

	configure_usart();
	configure_usart_callbacks();

	configure_i2c_master();

	system_interrupt_enable_global();	//Enable Interrupts for callbacks


}