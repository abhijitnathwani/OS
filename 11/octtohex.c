#include <stdio.h> 
#include <string.h>  
#include "Convert.h"
   
char *strrev();
int octtohex() {  
    int octalDigitToBinary[8] = {0, 1, 10, 11, 100, 101, 110, 111};  
    int hexDigitToBinary[16] = {0, 1, 10, 11, 100, 101, 110, 111, 1000,
      1001, 1010, 1011, 1100, 1101, 1110, 1111};    
    char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
      '9', 'A', 'B', 'C', 'D', 'E', 'F'};
 char hexadecimalNumber[30];
    long long octalNumber, binaryNumber = 0, position;  
    int digit, fourDigit, i;  
       
    /* Take an Octal Number as input from user */ 
    printf("Enter an Octal Number\n");  
    scanf("%ld", &octalNumber); 
   
    position = 1;  
    /* Finds Binary of the octal number */ 
    while(octalNumber != 0) {
        digit = octalNumber % 10;
        binaryNumber = (octalDigitToBinary[digit]*position)+binaryNumber;  
        octalNumber /= 10;  
        position *= 1000;  
    }
    /* Now convert Binary number to hexadecimal */
    position = 0;
    while(binaryNumber != 0){
        fourDigit = binaryNumber%10000;
        for(i = 0; i < 16; i++){
            if(hexDigitToBinary[i] == fourDigit){
                hexadecimalNumber[position] = hexDigits[i];
                break;
            }
        }
 
        position++;
        binaryNumber /= 10000; 
    }
    hexadecimalNumber[position] = '\0';
    //strrev(hexadecimalNumber);
    printf("HexaDecimal Number = %s\n", strrev(hexadecimalNumber));
     
    return 0;
} 
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}