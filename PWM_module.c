/*
 * PWM_module.c
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#include <msp430.h>

#include "Type.h"
#include "PWM_module.h"
#include "Communication.h"

void pwm_set_raw(int16 value)
{
	int16 upper_limit;

	upper_limit = TA0CCR0;

	if (value > upper_limit) value = upper_limit;
	if (value < 0) value = 0;

	TA0CCR1 = value;
}

uint8 pwm_set_percent(uint8 value)
{
	uint16 upper_limit;
	uint32 new_value;

	if (value > 100) return 1;

	upper_limit = TA0CCR0;

	new_value = (uint32) value * (uint32) upper_limit;
	new_value /= 100;

	pwm_set_raw(new_value);

	return 0;
}
