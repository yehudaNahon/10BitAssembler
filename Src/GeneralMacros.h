#ifndef GENERAL_MACROS_H
#define GENERAL_MACROS_H

/*return the bigest value of them to*/
#define MAX(num1, num2) (num1 >= num2 ? num1 : num2)

/*return the minimu, value of the 2 nums*/
#define MIN(num1, num2) (num1 >= num2 ? num2 : num1)

/*return the number of elements of a staticly allocated array*/
#define NUM_OF_ELEM(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


#endif