#include<stdio.h>
#include"Convert.h"
int dectooct() {
	long int decimalNumber,quotient;
	int binaryNumber[100],i=1,j;
	printf("Enter any decimal number: ");
	scanf("%ld",&decimalNumber);
	quotient = decimalNumber;
	while(quotient!=0) {
		binaryNumber[i++]= quotient % 8;
		quotient = quotient / 8;
	}
	printf("Equivalent octal value of decimal number %ld :  ",decimalNumber);
	for (j = i -1 ;j> 0;j--)
	         printf("%d",binaryNumber[j]);
	return 0;
}
