/*
 * TASK_manager.h
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#define TIMER_PERIOD 10   //milliseconds (interrupt at each 10 milliseconds)
#define NR_TASKS      2   //number of tasks

/*
 * IMPORTANT: Task numbering starts from 0.
 */

/*
 * Enables the task to run periodically.
 * Returns 1 on error, 0 otherwise.
 */
uint8 task_enable(uint8 nr);

/*
 * Disables the task and resets the counter of the task.
 * Returns 1 on error, 0 otherwise.
 */
uint8 task_disable(uint8 nr);

/*
 * Set the task period in milliseconds.
 * Returns 1 on error, 0 otherwise.
 */
uint8 task_set_period(uint8 nr, uint16 period);

#endif /* TASK_MANAGER_H_ */
