// reverseArray.c
// Aden Hilderbrand
// 10.1.24

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int globalArray[10];
int reversedArray[10];

void reverseArray();
void fillArray();
void printArray(int a[]);
int searchArray(int a[], int size, int value);

void fillArray(){
  int i;
  for (i=0;i< sizeof(globalArray) / sizeof(globalArray[0]);i++){
    globalArray[i] = rand() % 9;
  }
}

void reverseArray(){
  int i;
  int size = sizeof(globalArray) / sizeof(globalArray[0]);
// size of total array divided by size of a single item tells us how many items we have
  int temp;
  for (i=0;i< size / 2;i++){
    reversedArray[i] = globalArray[10-i-1];
    reversedArray[10-i-1] = globalArray[i];
  
  }
}

void printArray(int a[]){
  int i;
  int size = sizeof(globalArray) / 4; // size of int = 4 
  for (i=0;i<size;i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}

int searchArray(int a[], int size, int value){
  int i;
  for (i=0;i<size;i++){
    if (a[i] == value)
	return i;
  }
  return -1;
}

int main(){
  srand(time(0));
  fillArray();
  printArray(globalArray);  
//reverse the array passing nothing
  reverseArray();
//print reverse array
  printArray(reversedArray);
 
// ask user what value they want to search for and return its index or -1 if not found
  
  int value;
  int choice=0;
  printf("What value will you search for?: ");
  scanf("%d", &value);

  int index = searchArray(globalArray, sizeof(globalArray)/4, value);
  if (index != -1) {
    printf("Value %d found at index %d.\n", value , index);
  } else {
    printf("Value %d not found in the array.\n", value);
  }
	
  printf("\nThanks for using the program");
  return 0;
}














