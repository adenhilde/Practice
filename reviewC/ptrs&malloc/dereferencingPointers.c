#include <stdio.h>

int main(){

 char z;
 char initial='H';
 char *c=&initial;          

 printf("c points to %c \n", *c);
 printf("initial is %c \n", initial);


 z=*c;
 printf("z=%c\n", z); 
 initial='A';
 printf("c points to %c \n", *c);
 printf("initial is %c \n", initial);

 *c=*c+1;
 printf("c points to %c \n", *c);
 printf("initial is %c \n", initial);

 return 0;
}
