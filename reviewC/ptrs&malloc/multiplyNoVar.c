// Aden Hilderbrand
// multiplyNoVar.c
// 10.14.24
// this program multiplies x by 2 without using variables
//  x or y

#include <stdio.h>

int main(){

  int x = 3;
  int* y = &x;
  int** z = &y;
//my code here

  **z *= 2;

//my code here
  printf("x*2= %d\n", x);
  return 0;
}
