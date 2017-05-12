#include <stdio.h> 
#include <string.h>  
   

int octtobin() {  
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
    
    printf("Binary Number = %ld\n", binaryNumber);
     
    return 0;
} 
