/*
 * fuzzy.c
 *
 *  Created on: 09.12.2012
 *      Author: pascga2
 */

#include "type.h"
#include "fuzzy.h"

/* =========================================================== */

#define NR_RULES    25  //Number of rules for the inference machine
#define NR_SIGNALS  3   //2 Inputs + 1 Output

#define NR_MF_IN1   5   //Number of membership functions for the input1 function (error)
#define NR_MF_IN2   5   //Number of membership functions for the input2 function (variation of error)
#define NR_MF_OUT   5   //Number of membership functions for the output function

/* =========================================================== */
/*          START OF FUZZY PARAMETER CONFIGURATION             */

/*
 * Trapezoid structure. Membership function.
 *      b ______ c
 *       /      \
 *      /        \
 *  ___/          \___
 *    a             d
 */
typedef struct _trap_mf
{
    /* a < b <= c < d */
    int16 a;
    int16 b;
    int16 c;
    int16 d;
} trap_mf;

/*
 * Input 1 - Error = target_distance - current_distance
 *
 * Relative distance of the ball from the goal or target. (measured in millimeters)
 */
enum input1_terms {NEG_FAR, NEG_CLOSE, ZERO, POS_CLOSE, POS_FAR};
trap_mf in1_mf[NR_MF_IN1] =
{
/*  {   a,    b,   c,   d},   */

    {-260, -250, -80, -40},   //NEG_FAR      - Negative far
    { -70,  -40, -25,  -5},   //NEG_CLOSE    - Negative close
    { -20,  -10,  10,  20},   //ZERO         - Zero - target distance reached
    {   5,   25,  40,  70},   //POS_CLOSE    - Positive close
    {  40,   80, 250, 260}    //POS_FAR      - Positive fast
};

/*
 * Input 2 - Delta Error or Derivative of the Error = (current_error - previous_error) / period of measurement
 *
 * Speed of the ball relative to the goal or target. (measured in centimeters per second)
 */
enum input2_terms {NEG_FAST, NEG_SLOW, ZERO_SPEED, POS_SLOW, POS_FAST};
trap_mf in2_mf[NR_MF_IN2] =
{
/*  {   a,    b,   c,   d},   */

    {-110, -100, -12,  -8},    //NEG_FAST    - Negative fast
    { -12,   -8,  -5,  -2},    //NEG_SLOW    - Negative slow
    {  -4,   -2,   2,   4},    //ZERO_SPEED  - Zero speed
    {   2,    5,   8,  12},    //POS_SLOW    - Positive slow
    {   8,   12, 100, 110}     //POS_FAST    - Positive fast
};

/*
 * Output function of raw PWM values.
 * Due to the unlinear characteristic of the motor driver transistor,
 * there is no need to configure the duty cycle from 0% to 100%. Only a small
 * interval is required.
 *
 * PWM percentage in %   = {   37.5%,  43.75%,    50%,  56.25%,    62.5%}
 */
enum        output_terms   {NEG_HIGH, NEG_LOW, MEDIUM, POS_LOW, POS_HIGH};
uint16 out_mf[NR_MF_OUT] = {     300,     350,    400,     450,      500};


/*
 * Knowledge databse (rules).
 *
 * Example for the first rule:
 *   IF error (relative distance) IS negative far AND delta error (speed) IS negative fast THEN
 *      output IS positive high.
 * 
 * This means that if the ball is far away from our goal and the ball is also dropping very fast,
 * then we must set the fan speed to the highest speed configured (which is positive high).
 */
uint8 rules[NR_RULES][NR_SIGNALS] =
{
/*  {Input1,     Input2,      Output  }  */

    {NEG_FAR,    NEG_FAST,    POS_HIGH},
    {NEG_FAR,    NEG_SLOW,    POS_HIGH},
    {NEG_FAR,    ZERO_SPEED,  POS_HIGH},
    {NEG_FAR,    POS_SLOW,    POS_LOW },
    {NEG_FAR,    POS_FAST,    MEDIUM  },

    {NEG_CLOSE,  NEG_FAST,    POS_HIGH},
    {NEG_CLOSE,  NEG_SLOW,    POS_HIGH},
    {NEG_CLOSE,  ZERO_SPEED,  POS_LOW },
    {NEG_CLOSE,  POS_SLOW,    MEDIUM  },
    {NEG_CLOSE,  POS_FAST,    NEG_LOW },

    {ZERO,       NEG_FAST,    POS_HIGH},
    {ZERO,       NEG_SLOW,    POS_LOW },
    {ZERO,       ZERO_SPEED,  MEDIUM  },
    {ZERO,       POS_SLOW,    NEG_LOW },
    {ZERO,       POS_FAST,    NEG_HIGH},

    {POS_CLOSE,  NEG_FAST,    POS_LOW },
    {POS_CLOSE,  NEG_SLOW,    MEDIUM  },
    {POS_CLOSE,  ZERO_SPEED,  NEG_LOW },
    {POS_CLOSE,  POS_SLOW,    NEG_HIGH},
    {POS_CLOSE,  POS_FAST,    NEG_HIGH},

    {POS_FAR,    NEG_FAST,    MEDIUM  },
    {POS_FAR,    NEG_SLOW,    NEG_LOW },
    {POS_FAR,    ZERO_SPEED,  NEG_HIGH},
    {POS_FAR,    POS_SLOW,    NEG_HIGH},
    {POS_FAR,    POS_FAST,    NEG_HIGH}
};

/*           END OF FUZZY PARAMETER CONFIGURATION              */
/* =========================================================== */

/*
 * Calculate the minimum between "a" and "b" variables.
 */
int16 min(int16 a, int16 b)
{
    if (a > b) return b;
    return a;
}

/*
 * Map membership functions.
 */
uint8 map_mf(int16 input, trap_mf *tp)
{
    uint16 truth_value;

    if ( (input <= tp->a) || (input >= tp->d) )  //outside the membership function
        return 0;

    if ( (input >= tp->b) && (input <= tp->c) )  //peak of the membership function
        return 100;

    if ( (input > tp->a) && (input < tp->b) )    //1st case (on the rising edge of the trapeze)
        truth_value = ((input - tp->a) * 100) / (tp->b - tp->a);

    if ( (input > tp->c) && (input < tp->d) )    //2nd case (on the falling edge of the trapeze)
        truth_value = ((tp->d - input) * 100) / (tp->d - tp->c);

    return (uint8) truth_value;
}

/*
 * Fuzzy controller algorithm.
 * Takes two parameters - the two inputs: relative error and relative speed.
 */
uint16 fuzzy_controller(int16 input1, int16 input2)
{
    uint8 i;
    uint8 temp;

    uint32 x = 0;
    uint32 y = 0;

    //for each rule in the knowledge base
    for (i = 0; i < NR_RULES; i++)
    {
    	//calculate the minimum between the membership for each input signal
        temp = min ( map_mf(input1, &in1_mf[rules[i][0]]), map_mf(input2, &in2_mf[rules[i][1]]) );

        x += temp * out_mf[rules[i][2]];
        y += temp;
    }

    if (y != 0)               //avoid division by zero
        return x / y;         //weighted average output

    return out_mf[POS_HIGH];  //if input is out of range
}

/* =========================================================== */
