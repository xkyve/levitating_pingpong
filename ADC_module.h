/*
 * ADC_module.h
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#ifndef ADC_MODULE_H_
#define ADC_MODULE_H_

#define SAMPLE_TIME          20   //(milliseconds sample time for ADC)
#define ADC_REF            3558   //Reference voltage (in millivolts)

extern uint8 regulatorFlag;       //Located in main.c. This variable specifies if a sampling of the ADC has finished.

/*
 * ADC Start Conversion - Software trigger.
 */
void adc_start(void);

/*
 * This function will return the distance read from the sensor
 * in millimeters. The parameter "value" ranges from 0 - 1023.
 */
uint16 get_distance(uint16 value);

/*
 * Get last read value from the ADC.
 * If "opt" equals zero then this function returns values in the range of 0 - 1023,
 * otherwise it returns values in millivolts, from 0 - ADC_REF (voltage)
 */
uint16 adc_get_last_result(uint8 opt);

/*
 * Get the value in millivolts.
 * Parameter "data" ranges from 0 to 1023.
 * This function is used in "adc_get_last_result" and "adc_get_avg_result" functions.
 */
uint16 voltage(uint16 data);

#endif /* ADC_MODULE_H_ */
