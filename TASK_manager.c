/*
 * TASK_manager.c
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#include "Type.h"
#include "TASK_manager.h"
#include "Communication.h"
#include "ADC_module.h"
#include "PWM_module.h"

void blast_startup(void)
{
    task_enable(0);     //Enable the ADC task
    task_disable(1);    //Disable this task
}

typedef struct _task_struct
{
    uint16 period;        //Period in milliseconds
    void (*name)(void);   //Name of the function to be called each period
    uint8 enable;         //Is this task enable at startup?
    uint16 counter;       //Internal counter used in the Timer1 interrupt routine
} task_struct;

task_struct task[NR_TASKS] =
{
  //{PERIOD, NAME, ENABLED?, COUNTER}

    {SAMPLE_TIME / TIMER_PERIOD, adc_start, 0, 0},    //Start ADC sampling periodically (currently at 20 ms)
    {1500 / TIMER_PERIOD, blast_startup, 1, 0}       //Blast the ball at startup, then activate the fuzzy algorithm and deactivate this task
};

uint8 task_enable(uint8 nr)
{
    if (nr < NR_TASKS)
    {
        task[nr].enable = 1;
        return 0;
    }

    return 1; //ERROR
}

uint8 task_disable(uint8 nr)
{
    if (nr < NR_TASKS)
    {
        task[nr].enable = 0;
        task[nr].counter = 0;
        return 0;
    }

    return 1; //ERROR
}

uint8 task_set_period(uint8 nr, uint16 period)
{
    if (nr < NR_TASKS)
    {
        task[nr].period = period;
        return 0;
    }

    return 1; //ERROR
}

/*
 * This function is called every TIMER_PERIOD milliseconds.
 */
void Timer1ACCR0ISRHandler(void)
{
    uint8 i;

    for (i = 0; i < NR_TASKS; i++)                  //for every task defined
        if (task[i].enable)                         //check if the task is enabled
        {
            task[i].counter++;                      //increment the task internal counter
            if (task[i].counter >= task[i].period)  //is it time to execute the task (counter is larger than the defined period)
            {
                task[i].counter = 0;                //reset the internal counter
                (*task[i].name)();                  //execute the task (pointer to function)
            }
        }
}
