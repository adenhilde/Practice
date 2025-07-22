// Aden Hilderbrand
// intSwap.c
// 10.14.24
// This program contains a function that swaps 2 integers using pointers

#include<stdio.h>

void swap(int *a , int *b){
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

int main(){
  int x =1 , y =2;
  printf("Pre swap: x = %d , y = %d\n", x , y);
  swap(&x,&y); // pass the addresses, not the variables
  printf("Post swap: x = %d , y = %d\n", x , y);

  return 0;
}
