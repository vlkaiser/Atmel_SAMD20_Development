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

void sensorRead(void);
void flashLED(void);

#endif /* MAIN_H_ */