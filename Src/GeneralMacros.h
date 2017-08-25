#ifndef GENERAL_MACROS_H
#define GENERAL_MACROS_H

#define MAX(num1, num2) (num1 >= num2 ? num1 : num2)
#define MIN(num1, num2) (num1 >= num2 ? num2 : num1)
#define NUM_OF_ELEM(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


#endif