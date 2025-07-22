/***********************
 * bitwise.c 
 * 9.18.24
 * Aden Hilderbrand
 * this program prompts a user for 2 numbers and asks if they want to do a 
 * bitwise or, bitwise and , or bitwise xor ,  then prints the answer
 * ********************/

// %b is used to print variables as binary, but for some reason this compiler does not support %b. after some research it sounds like some compilers do and some don't. so to solve this problem i will be skipping ahead and little bit and usea function that i found online to turn int values into binary

#include <stdio.h>

void printBinary(unsigned int n){
int bitPosition = sizeof(n) * 8 -1;
int i;

for(i = bitPosition;i>=0;i--){
	if(n & (1U << i)) { 
		putchar('1');

	}else {
		putchar('0');
	}
    }
    putchar('\n');
}

int main(){
// init var
int a,b , pick;

printf("Please enter TWO integers\nEnter a: ");
scanf("%d", &a);
printf("Enter b: ");
scanf("%d",&b);

printf("1 = bitwise OR\n2 = bitwise AND\n3 = bitwise XOR\n\nPlease type an option above: ");
scanf("%d", &pick);

switch(pick){
case 1:
	//do the bitwise or
	printf("a  = "); //print the binary value of a
	printBinary(a);
	
	printf("b  = "); //print the binary value of b
	printBinary(b);
	
	printf("a|b= ");
	printBinary(a|b);
	break;

case 2:
	//do the bitwise and
	printf("a  = "); //print the binary value of a
	printBinary(a);
	
	printf("b  = "); //print the binary value of b
	printBinary(b);
	
	printf("a&b= ");
	printBinary(a&b);
	break;

case 3:
	//do the bitwise XOR
	printf("a  = "); //print the binary value of a
	printBinary(a);
	
	printf("b  = "); //print the binary value of b
	printBinary(b);
	
	printf("a^b= ");
	printBinary(a^b);
	break;
		
default:
	printf("\nNot an option. Thanks for trying buddy");
	break;
}

return 0;
}
