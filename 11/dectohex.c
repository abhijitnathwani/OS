#include<stdio.h>
#include<stdlib.h>
#include"Convert.h"
int dectohex() {
	unsigned int decimalNumber;
	printf("Enter any decimal number: ");
	scanf("%ud",&decimalNumber);
	printf("Equivalent hexadecimal number is: %X\n",decimalNumber);
	return 0;
}
