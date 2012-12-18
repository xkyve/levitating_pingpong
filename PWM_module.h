/*
 * PWM_module.h
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#ifndef PWM_MODULE_H_
#define PWM_MODULE_H_

/*
 * Set PWM duty cycle in raw values.
 * Ranges from 0 to the value of the TA0CCR0. (example: from 0 to 800 for 20 kHz PWM signal)
 * TA0CCR0, Timer_A Capture/Compare Register 0
 */
void pwm_set_raw(int16 value);

/*
 * Set PWM duty cycle in percentage.
 * Returns 1 on error (values over 100), 0 otherwise.
 */
uint8 pwm_set_percent(uint8 value);

#endif /* PWM_MODULE_H_ */
