/*
 * Interpreter.h
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

/*
 * The following commands are valid and all must end with carriage return ('\r'):
 *
 *   --PWM
 *   "p50"    - sets the PWM to 50% (or any other value between 0-100)
 *   "pr500"  - sets the PWM in raw values
 *
 *   --TASK enable/disable (2 digits are required)
 *   "t00"  - disables the task that has the number 0 assigned to it
 *   "t01"  - enables the task that has the number 0 assigned to it
 *
 *   --TASK set period
 *   "t0p100" - sets the period of task number 0 to (100 * TIMER_PERIOD) milliseconds
 *   "t1p5"   - sets the period of task number 1 to (  5 * TIMER_PERIOD) milliseconds
 *
 *   --Target distance
 *   "x110"  - sets the target distance to 110 millimeters
 */
void interpret(uint8 *cmd);

#endif /* INTERPRETER_H_ */
