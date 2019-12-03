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

 void config_IO_LEDS(void)
 {
	 struct port_config pin_conf;
	 port_get_config_defaults(&pin_conf);

	 pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	 port_pin_set_config(LED_PWR_GREEN_PIN, &pin_conf);
	 port_pin_set_output_level(LED_PWR_GREEN_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_PWR_RED_PIN, &pin_conf);
	 port_pin_set_output_level(LED_PWR_RED_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_MEAS_WHITE_PIN, &pin_conf);
	 port_pin_set_output_level(LED_MEAS_WHITE_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_STOP_RED_PIN, &pin_conf);
	 port_pin_set_output_level(LED_STOP_RED_PIN, LED_INACTIVE);
 }

void config_board(void)
{
 	/*Configure system tick to generate periodic interrupts */
 	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	config_led();
	config_IO_LEDS();
	delay_init();

	configure_usart();
	configure_usart_callbacks();

	configure_i2c_master();
	configure_i2c_callbacks();

	configure_extint_channel0();	configure_extint_Power();	configure_extint_Measure();	configure_extint_EStop();	configure_extint_callbacks();

	system_interrupt_enable_global();	//Enable Interrupts for callbacks
}

void configure_extint_channel0(void)
{
	struct extint_chan_conf config_extint_chan0;
	extint_chan_get_config_defaults(&config_extint_chan0);
	
	config_extint_chan0.gpio_pin = BUTTON_0_EIC_PIN;
	config_extint_chan0.gpio_pin_mux = BUTTON_0_EIC_MUX;
	config_extint_chan0.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_chan0.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan0);
}
void configure_extint_Power(void)
{
	struct extint_chan_conf config_extint_pwr;
	extint_chan_get_config_defaults(&config_extint_pwr);
	
	config_extint_pwr.gpio_pin = BUTTON_PWR_PIN;
	config_extint_pwr.gpio_pin_mux = BUTTON_PWR_EIC_MUX;
	config_extint_pwr.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_pwr.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_PWR_EIC_LINE, &config_extint_pwr);
}

void configure_extint_Measure(void)
{
	struct extint_chan_conf config_extint_meas;
	extint_chan_get_config_defaults(&config_extint_meas);
	
	config_extint_meas.gpio_pin = BUTTON_MEAS_PIN;
	config_extint_meas.gpio_pin_mux = BUTTON_MEAS_EIC_MUX;
	config_extint_meas.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_meas.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_MEAS_EIC_LINE, &config_extint_meas);
}

void configure_extint_EStop(void)
{
	struct extint_chan_conf config_extint_estop;
	extint_chan_get_config_defaults(&config_extint_estop);
	
	config_extint_estop.gpio_pin = BUTTON_ESTOP_PIN;
	config_extint_estop.gpio_pin_mux = BUTTON_ESTOP_EIC_MUX;
	config_extint_estop.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_estop.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_ESTOP_EIC_LINE, &config_extint_estop);
}

void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback, BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);

	extint_register_callback(extint_detection_callback_pwr, BUTTON_PWR_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_PWR_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);

	extint_register_callback(extint_detection_callback_meas, BUTTON_MEAS_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_MEAS_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);

	extint_register_callback(extint_detection_callback_estop, BUTTON_ESTOP_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_ESTOP_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
}

void extint_detection_callback(void)
{
	bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	button_pin_state = !button_pin_state;
	port_pin_set_output_level(LED_0_PIN, button_pin_state);
}

void extint_detection_callback_pwr(void)
{
	bool button_pin_state = port_pin_get_input_level(BUTTON_PWR_PIN);
	button_pin_state = !button_pin_state;
	port_pin_set_output_level(LED_PWR_RED_PIN, button_pin_state);
}

void extint_detection_callback_meas(void)
{
	bool button_pin_state = port_pin_get_input_level(BUTTON_MEAS_PIN);
	button_pin_state = !button_pin_state;
	port_pin_set_output_level(LED_MEAS_WHITE_PIN, button_pin_state);
}

void extint_detection_callback_estop(void)
{
	bool button_pin_state = port_pin_get_input_level(BUTTON_ESTOP_PIN);
	button_pin_state = !button_pin_state;
	port_pin_set_output_level(LED_STOP_RED_PIN, button_pin_state);
}