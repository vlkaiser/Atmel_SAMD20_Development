/*
 * main.h
 *
 * Created: 11/14/2019 11:20:46 AM
 *  Author: VKaiser
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <asf.h>

#include "user_board.h"
#include "DC_deftypes.h"
#include "DC_peripherals.h"
#include "DC_SERCOM.h"
#include "stdio.h"
#include "string.h"

void sensorRead(uint8_t* rd_buf);
void flashLED(void);
void writeBufferOut(uint8_t* data);

#endif /* MAIN_H_ */