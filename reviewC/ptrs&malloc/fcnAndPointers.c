// Aden Hilderbrand
// fncAndPointers.c
// 10.14.24

#include <stdio.h>

void addExtraCredit(int *g){
  *g = *g+1;
  printf("in addExtraCredit: grade=%d\n", *g);  
}

int main() {
  int x,gradeArray[5]={100, 75, 80, 90, 60};  
  int *ptr = gradeArray;

  printf("Grades are:\n");
  for(x=0; x<5; x++){
    addExtraCredit(&ptr[x]); 
    printf("in main: %d \n",ptr[x]);
  }
  
  printf("\n"); 
  return 0;
}
