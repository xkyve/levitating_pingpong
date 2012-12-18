/*
 * Communication.h
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define CMD_SIZE 24
#define END_CHAR '\r'

/*
 * Used with MegunoLink plotting program for the PC.
 */
void serial_put_signal(uint8 *signalName, int32 value);

/*
 * Returns - 1 when no command is received.
 *         - 0 otherwise
 *
 * The command will be saved in the parameter "cmd".
 */
uint8 read_cmd(uint8 *cmd);

/*
 * Send a character through serial.
 */
void serial_putc(uint8 ch);

/*
 * Output a number as characters.
 */
void serial_putnr(int32 nr);

/*
 * Send a string through serial.
 */
void serial_putstr(uint8 *str);

#endif /* COMMUNICATION_H_ */
