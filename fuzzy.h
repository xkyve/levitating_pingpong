/*
 * fuzzy.h
 *
 *  Created on: 09.12.2012
 *      Author: pascga2
 */

#ifndef FUZZY_H_
#define FUZZY_H_

/*
 * Takes as input the error (target distance - current distance)
 * and outputs the next PWM raw value.
 */
uint16 fuzzy_controller(int16 input1, int16 input2);

#endif /* FUZZY_H_ */
