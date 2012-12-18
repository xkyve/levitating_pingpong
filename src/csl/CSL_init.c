/*
 *  ======== CSL_init.c ========
 *  DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN
 */
 
/* external peripheral initialization functions */
extern void GPIO_init(void);
extern void BCSplus_init(void);
extern void ADC10_init(void);
extern void USCI_A0_init(void);
extern void Timer0_A3_init(void);
extern void System_init(void);
extern void Timer1_A3_init(void);
extern void WDTplus_init(void);

#include <msp430.h>

/* verify that the MSP430 headers included support the code that's generated */
#if defined(__TI_COMPILER_VERSION__)
  /* pragma required to suppress TI warning that #warning is unrecognized */
  #pragma diag_suppress 11
#endif
#if __MSP430_HEADER_VERSION__ < 1062
  #if defined(__TI_COMPILER_VERSION__)
    #warn The MSP430 headers included may be incompatible with the generated source files.  If the value of __MSP430_HEADER_VERSION__, declared by msp430.h, is less than 1062, please update your version of the msp430 headers.
  #elif defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__)
    #warning The MSP430 headers included may be incompatible with the generated source files.  If the value of __MSP430_HEADER_VERSION__, declared by msp430.h, is less than 1062, please update your version of the msp430 headers.
  #else
    /* if we can't just warn, resort to ANSI C's #error */
    #error The MSP430 headers included may be incompatible with the generated source files.  If the value of __MSP430_HEADER_VERSION__, declared by msp430.h, is less than 1062, please update your version of the msp430 headers.
  #endif
#endif
#if defined(__TI_COMPILER_VERSION__)
  /* pragma required to restore TI warnings about unrecognized directives */
  #pragma diag_default 11
#endif

/*
 *  ======== CSL_init =========
 *  Initialize all configured CSL peripherals
 */
void CSL_init(void)
{
    /* Stop watchdog timer from timing out during initial start-up. */
    WDTCTL = WDTPW + WDTHOLD;

    /* initialize Config for the MSP430 GPIO */
    GPIO_init();

    /* initialize Config for the MSP430 2xx family clock systems (BCS) */
    BCSplus_init();

    /* initialize Config for the MSP430 10-bit Analog to Digital Converter (ADC) */
    ADC10_init();

    /* initialize Config for the MSP430 USCI_A0 */
    USCI_A0_init();

    /* initialize Config for the MSP430 A3 Timer0 */
    Timer0_A3_init();

    /* initialize Config for the MSP430 System Registers */
    System_init();

    /* initialize Config for the MSP430 A3 Timer0 */
    Timer1_A3_init();

    /* initialize Config for the MSP430 WDT+ */
    WDTplus_init();

}

/*
 *  ======== Interrupt Function Definitions ========
 */

/* Interrupt Function Prototypes */
extern void Port1ISRHandler(void);
extern void ADC10ISRHandler(void);
extern void USCIA0RXISRHandler(void);

extern void Timer1ACCR0ISRHandler(void);


/*
 *  ======== PORT1 Interrupt Service Routine ========
 */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void)
{


	/* Port 1 Interrupt Handler */
	Port1ISRHandler();

	/* No change in operating mode on exit */
}


/*
 *  ======== ADC10 Interrupt Service Routine ========
 */
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR_HOOK(void)
{


	/* ADC10 Interrupt Handler */
	ADC10ISRHandler();

	/* No change in operating mode on exit */
}




/*
 *  ======== USCI A0/B0 RX Interrupt Handler Generation ========
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void)
{
	/* USCI_A0 Receive Interrupt Handler */
	USCIA0RXISRHandler();

	/* No change in operating mode on exit */
}

/*
 *  ======== Timer1_A3 Interrupt Service Routine ======== 
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{

	/* Capture Compare Register 0 ISR Hook Function Name */
	Timer1ACCR0ISRHandler();

	/* No change in operating mode on exit */
}


