#include <stdio.h>
#include "Convert.h"

int main()
{
	int iChoice;
	do{
		printf("1.Decimal to binary\n2.Decimal to Hexadecimal\n3.Decimal to Octal\n\
			4. Octal to Decimal\n5. Octal to Binary\n6. Octal to Hexadecimal\n\
			7. Hexadecimal to Decimal\n100.Exit\n");

		scanf("%d",&iChoice);
		switch(iChoice){
			case 1:
				dectobin();
				break;
			case 2:
				dectohex();
				break;
			case 3:
				dectooct();
				break;
			case 4:
				octtodec();
				break;
			case 5:
				octtobin();
				break;
			case 6:
				octtohex();
				break;
			case 7:
				hextodec();
				break;
			case 8: 
				break;
			default:
				printf("enter valid choice \n");

		}
	}while(iChoice!=100);
return 0;
}
