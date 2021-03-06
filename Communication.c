/*
 * Communication.c
 *
 *  Created on: Nov 22, 2012
 *      Author: pascga2
 */
#include <msp430.h>
#include "Type.h"
#include "Communication.h"

uint8 cmd_buffer[CMD_SIZE];
uint8 index_p = 0;
uint8 cmd_recv = 0;

uint8 digit[10];

void serial_put_signal(uint8 *signalName, int32 value)
{
    serial_putc('{');

    serial_putstr(signalName);
    serial_putstr((uint8 *) ",T,");
    serial_putnr(value);

    serial_putc('}');
}

void serial_putc(uint8 ch)
{
    while (!(IFG2 & UCA0TXIFG));  //Poll TXIFG to until set
    UCA0TXBUF = ch;               //Put the character in the transmission buffer
}

void serial_putstr(uint8 *str)
{
    uint8 i;

    i = 0;

    //send characters until the end of the string has been reached
    while (str[i] != '\0')
    {
        serial_putc(str[i]);
        i++;
    }
}

void serial_putnr(int32 nr)
{
    uint8 i = 0;

    if (nr < 0)  //negative number?
    {
        serial_putc('-');
        nr = -nr;
    }

    if (nr < 10) //only one digit to output?
    {
        serial_putc(nr + '0');
        return;
    }

    //store each digit of the number in an array
    while (nr > 0)
    {
        digit[i] = nr % 10;
        nr = nr / 10;
        i++;
    }

    //output each digit from the array on serial communication
    while (i > 0)
    {
        i--;
        serial_putc(digit[i] + '0');
    }
}

/*
 * Copy the command stored in the buffer to another character array.
 * Clear the command received flag to signal that another command can be received on serial.
 */
uint8 read_cmd(uint8 *cmd)
{
    uint8 i;

    if (cmd_recv == 0) return 1;

    for (i = 0; i < index_p; i++)
    {
        cmd[i] = cmd_buffer[i];
    }
    cmd[index_p] = '\0';

    index_p = 0;
    cmd_recv = 0;

    return 0;
}

void USCIA0RXISRHandler(void)
{
    uint8 ch;
    ch = UCA0RXBUF;

    //serial_putc(ch);

    if (cmd_recv == 0)       //check if no commands are pending
    {
        if (ch != END_CHAR)  //has a full command been received?
        {
            cmd_buffer[index_p] = ch;
            index_p++;
        }
        else
        {
            cmd_buffer[index_p] = '\0';
            cmd_recv = 1;
        }
    }
}
