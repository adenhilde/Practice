// pointersAndMalloc.c
// Aden Hilderbrand
// 11.14.2024
// this program dynamically allocates memory for 3 pointers, prompts user for values to store at pointer locations, dereferences the pointers and prints to the screen, then frees the allocates memory.

#include <stdio.h>
#include <stdlib.h>

int main(){
// initialize pointers to be used
    int *ptrInt;
    char *ptrChar;
    float *ptrFloat;

// allocate memory that pointers use separately from initialization
    ptrInt = (int*)malloc(sizeof(int));
    ptrChar = (char*)malloc(sizeof(char));
    ptrFloat = (float*)malloc(sizeof(float));

// prompt user to fill values for pointers to point to
    printf("Enter an integer: ");
    scanf("%d", ptrInt);

    printf("Enter any character: ");
    scanf(" %c", ptrChar);

    printf("Enter a float: ");
    scanf("%f", ptrFloat);

// print values entered , utilizing the pointers
    printf("Int: %d    Char: %c     Float: %.2f\n", *ptrInt, *ptrChar, *ptrFloat);

// free allocated memory to avoid memory leaks
    free(ptrInt);
    free(ptrChar);
    free(ptrFloat);

    return 0;
}
