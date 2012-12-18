#include <stdio.h>

#include "type.h"
#include "fuzzy.h"

/* =========================================================== */

#define NR_RULES    25  //Number of rules for the inference machine
#define NR_SIGNALS  3   //2 Inputs + 1 Output

#define NR_MF_IN1   5   //Number of membership functions for the input1 function (error)
#define NR_MF_IN2   5   //Number of membership functions for the input2 function (variation of error)
#define NR_MF_OUT   5   //Number of membership functions for the output function

/* =========================================================== */

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
 * Relative distance.
 */
enum input1_terms {NEG_FAR, NEG_CLOSE, ZERO, POS_CLOSE, POS_FAR};
trap_mf in1_mf[NR_MF_IN1] =
{
    {-260, -250, -80, -40},   //NEG_FAR
    { -70,  -40, -25,  -5},   //NEG_CLOSE
    { -20,  -10,  10,  20},   //ZERO
    {   5,   25,  40,  70},   //POS_CLOSE
    {  40,   80, 250, 260}    //POS_FAR
};

/*
 * Derivative of error (delta error).
 */
enum input2_terms {NEG_FAST, NEG_SLOW, ZERO_SPEED, POS_SLOW, POS_FAST};
trap_mf in2_mf[NR_MF_IN2] =
{
    {-110, -100, -12,  -8},    //NEG_FAST
    { -12,   -8,  -5,  -2},    //NEG_SLOW
    {  -4,   -2,   2,   4},    //ZERO_SPEED
    {   2,    5,   8,  12},    //POS_SLOW
    {   8,   12, 100, 110}     //POS_FAST
};

/*
 * Output function of raw PWM values.
 */
  enum      output_terms   {NEG_HIGH, NEG_LOW, MEDIUM, POS_LOW, POS_HIGH};
uint16 out_mf[NR_MF_OUT] = {     300,     350,    400,     450,      500};

uint8 rules[NR_RULES][NR_SIGNALS] =
{
    {NEG_FAR, NEG_FAST, POS_HIGH},    //IF "error" is NEG_FAR and "delta(error)" is NEG_FAST then "output" is POS_HIGH
    {NEG_FAR, NEG_SLOW, POS_HIGH},    //...
    {NEG_FAR, ZERO_SPEED, POS_HIGH},
    {NEG_FAR, POS_SLOW, POS_LOW},
    {NEG_FAR, POS_FAST, MEDIUM},

    {NEG_CLOSE, NEG_FAST, POS_HIGH},
    {NEG_CLOSE, NEG_SLOW, POS_HIGH},
    {NEG_CLOSE, ZERO_SPEED, POS_LOW},
    {NEG_CLOSE, POS_SLOW, MEDIUM},
    {NEG_CLOSE, POS_FAST, NEG_LOW},

    {ZERO, NEG_FAST, POS_HIGH},
    {ZERO, NEG_SLOW, POS_LOW},
    {ZERO, ZERO_SPEED, MEDIUM},
    {ZERO, POS_SLOW, NEG_LOW},
    {ZERO, POS_FAST, NEG_HIGH},

    {POS_CLOSE, NEG_FAST, POS_LOW},
    {POS_CLOSE, NEG_SLOW, MEDIUM},
    {POS_CLOSE, ZERO_SPEED, NEG_LOW},
    {POS_CLOSE, POS_SLOW, NEG_HIGH},
    {POS_CLOSE, POS_FAST, NEG_HIGH},

    {POS_FAR, NEG_FAST, MEDIUM},
    {POS_FAR, NEG_SLOW, NEG_LOW},
    {POS_FAR, ZERO_SPEED, NEG_HIGH},
    {POS_FAR, POS_SLOW, NEG_HIGH},
    {POS_FAR, POS_FAST, NEG_HIGH}
};

/* =========================================================== */

/*
 * Calculate the minimum between "a" and "b" variables.
 */
int16 min(int16 a, int16 b)
{
    if (a > b)
        return b;
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

uint16 fuzzy_controller(int16 input1, int16 input2)
{
    uint8 i;
    uint8 temp;

    uint32 x = 0;
    uint32 y = 0;

    //for each rule
    for (i = 0; i < NR_RULES; i++)
    {
        temp = min ( map_mf(input1, &in1_mf[rules[i][0]]), map_mf(input2, &in2_mf[rules[i][1]]) );

        x += temp * out_mf[rules[i][2]];
        y += temp;
    }

    if (y != 0) //avoid division by zero
        return x / y;  //weighted average output

    return out_mf[POS_HIGH];  //if input is out of range
}

/* =========================================================== */
