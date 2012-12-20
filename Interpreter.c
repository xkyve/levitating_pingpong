/*
 * Interpreter.c
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#include "Type.h"
#include "Interpreter.h"
#include "Communication.h"
#include "PWM_module.h"
#include "TASK_manager.h"
#include "ADC_module.h"

extern int16 target;

void interpret(uint8 *cmd)
{
    uint8 i, status = 0;
    uint16 param1 = 0, param2 = 0;

    if (cmd[0] == 'p')  //PWM Set (percentage)
    {
        if (cmd[1] == 'r')  //Raw
        {
            i = 2;
            while (cmd[i] != '\0')
            {
                param1 = (param1 * 10) + (cmd[i] - '0');
                i++;
            }

            pwm_set_raw(param1);
            serial_putstr((uint8 *) "OK\r\n");
            return;
        }

        i = 1;
        while (cmd[i] != '\0')
        {
            param1 = (param1 * 10) + (cmd[i] - '0');
            i++;
        }

        if (pwm_set_percent(param1))
            serial_putstr((uint8 *) "Invalid\r\n");
        else
            serial_putstr((uint8 *) "OK\r\n");
    }

    if (cmd[0] == 't')  //Task manager
    {
        param1 = cmd[1] - '0';  //task number

        if (cmd[2] == 'p')  //set period, then return
        {
            i = 3;
            while (cmd[i] != '\0')
            {
                param2 = (param2 * 10) + (cmd[i] - '0');
                i++;
            }

            if (task_set_period(param1, param2))
                serial_putstr((uint8 *) "Invalid\r\n");
            else
                serial_putstr((uint8 *) "OK\r\n");

            return;
        }

        param2 = cmd[2] - '0';

        if (param2 == 0)
            status = task_disable(param1);
        else
            status = task_enable(param1);

        if (status)
            serial_putstr((uint8 *) "Invalid\r\n");
        else
            serial_putstr((uint8 *) "OK\r\n");
    }

    if (cmd[0] == 'x')  //Set target distance
    {
        i = 1;
        while (cmd[i] != '\0')
        {
            param1 = (param1 * 10) + (cmd[i] - '0');
            i++;
        }

        serial_putc('K');
        target = param1;
    }
}
