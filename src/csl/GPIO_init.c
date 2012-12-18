/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/Data/_DevTools/Code Composer/grace_1_10_04_36/packages/ti/mcu/msp430/csl/gpio/GPIO_init.xdt
 */

#include <msp430.h>

/*
 *  ======== GPIO_init ========
 *  Initialize MSP430 General Purpose Input Output Ports
 */
void GPIO_init(void)
{
    /* Port 1 Output Register */
    P1OUT = BIT3;

    /* Port 1 Port Select Register */
    P1SEL = BIT1 + BIT2 + BIT6;

    /* Port 1 Port Select 2 Register */
    P1SEL2 = BIT1 + BIT2;

    /* Port 1 Direction Register */
    P1DIR = BIT0 + BIT6;

    /* Port 1 Resistor Enable Register */
    P1REN = BIT3;

    /* Port 1 Interrupt Edge Select Register */
    P1IES = 0;

    /* Port 1 Interrupt Flag Register */
    P1IFG = 0;

    /* Port 1 Interrupt Enable Register */
    P1IE = BIT3;

    /* Port 2 Interrupt Edge Select Register */
    P2IES = 0;

    /* Port 2 Interrupt Flag Register */
    P2IFG = 0;

    /* Port 3 Output Register */
    P3OUT = 0;

    /* Port 3 Port Select Register */
    P3SEL = BIT0;

    /* Port 3 Direction Register */
    P3DIR = BIT0;

}
