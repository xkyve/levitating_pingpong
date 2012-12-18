/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

#include "Type.h"
#include "Communication.h"
#include "Interpreter.h"
#include "ADC_module.h"
#include "PWM_module.h"
#include "fuzzy.h"

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

extern int16 target;

uint8 cmd[CMD_SIZE];        //In this buffer will be stored the command read from serial communication with the PC
uint8 btnState = 1;         //The button state
int16 target;               //Target distance

/*
 * LED functions. Mainly used to signal if the fuzzy regulator is activated.
 */
void led_toggle();
void led_on();
void led_off();

/*
 * Button handler routine.
 * [Debugging purposes]
 */
void Port1ISRHandler(void)
{
	P1IFG &= ~BIT3;              //Clear P1.3 IFG
	btnState = !btnState;

	if (btnState)
		led_on();
	else
		led_off();
}

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
	int16   current_distance;  //Will hold the distance read from the sensor in millimeters
	uint16  fuzzy_output;      //Will hold the next PWM value

	int16 error = 0;           //current error
	int16 prev_error = 0;      //previous error
	int16 delta = 0;           //variation of error

	CSL_init();                //Activate Grace-generated configuration

    /*
     * Other initializations.
     */
    led_on();
    pwm_set_percent(100);    //Blast the ping-pong ball at start of the program
    target = 110;            //Target distance (in millimeters)

    while (1)
    {
    	if (!read_cmd(cmd))                //If commands are waiting to be executed
    	{
    		interpret(cmd);                //Interpret and execute those commands
    	}

    	if (regulatorFlag)                 //If ADC has done sampling execute regulator algorithm
    	{
    		//serial_put_signal((uint8 *) "d", get_distance(adc_get_last_result(0)));

    		/*
    		 * Enable fuzzy controller only if the button state is set to 1 (default is 1).
    		 * Press the pushbutton P1.3 to disable it.
    		 */
    		if (btnState)
    		{
				current_distance = get_distance(adc_get_last_result(0));

				error = target - current_distance;

				/*
				 * "delta" is measured in centimeters per second.
				 * The multiplication by 5 is there because 100 / 20 = 5.
				 * 20 is the sample period (in milliseconds).
				 * 100 means that we want the output to be expressed in centimeters.
				 * If we wanted to measure it in millimeters, we would've multiplied by 50 because 1000 / 20 = 50.
				 */
				delta = (error - prev_error) * 5;

				fuzzy_output = fuzzy_controller(error, delta);
				pwm_set_raw(fuzzy_output);

				prev_error = error;
    		}

    		regulatorFlag = 0;             //Signal the end of regulator algorithm execution
    	}
    }
}

void led_toggle()
{
	P1OUT ^= BIT0;
}

void led_on()
{
	P1OUT |= BIT0;
}

void led_off()
{
	P1OUT &= ~BIT0;
}
