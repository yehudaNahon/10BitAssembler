#include "BaseConverter.h"


int DecimalBaseConverter(int &number, uint8_t base)
{
	int temp = 0;
	
	while(number != 0)
	{
		if(number < base)
		{
			temp += number;
			return true;
		}
		else
		{
			temp = temp* 10 + o_number % base;
			o_number /= base;
		}	

	}

	return temp;
}



