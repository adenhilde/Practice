// Aden Hilderbrand
// matrixManip.c
// 10.21.24
// This program prints a multidimensional array as a matrix
// And then adds that matrix into another matrix

#include<stdio.h>

#define ROWS 3
#define COLS 3

int i,j;

void addArrays(int a1[ROWS][COLS], int a2[ROWS][COLS], int result[ROWS][COLS]) {
	for (i=0;i<ROWS;i++){
		for (j=0;j<COLS;j++){
			result[i][j] = a1[i][j] + a2[i][j];
		}
	}
}

void printArray(int a[ROWS][COLS]) {
	for (i=0;i<ROWS;i++){
		for (j=0;j<COLS;j++){
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}

}

int main(){
// init matrices
  int matrix[ROWS][COLS]= { 
	{1, 5, 6},
	{0, 1, 0},
	{2, -2, 3}
  };
  int identity[ROWS][COLS]= {
	{1, 0, 0}, 
	{0, 1, 0}, 
	{0, 0, 1}
  };
  
  int result[ROWS][COLS];

  printf("\n");
  printArray(matrix);
  printf("\n\t +\n\n");   

  printArray(identity);
  printf("\n\t =\n\n");

  addArrays(matrix, identity, result);
  printArray(result);

  return 0;
}
