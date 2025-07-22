#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct cake{
  char icingFlavor[20];
  char cakeFlavor[20];
  int layers; 
};

void printCake(struct cake c){
  printf("%d layer %s cake with %s icing.\n", c.layers,
         c.cakeFlavor, c.icingFlavor); 
}

int main(){
  struct cake birthdayCake;
  struct cake cupCake;
  struct cake cakes4Party[15];  //array of cakes
  int x;
 
  //You can populate individual struct fields with hard coded values
  strcpy(birthdayCake.icingFlavor, "chocolate");
  strcpy(birthdayCake.cakeFlavor, "chocolate");
  birthdayCake.layers=2;

  //You can populate individual struct fields with user input
  printf("What flavor is the icing? ");
  scanf("%s", cupCake.icingFlavor);
  printf("What flavor is the cake? ");
  scanf("%s", cupCake.cakeFlavor);
  printf("How many layers is the cake? ");
  scanf("%d", &cupCake.layers);

  //populating cake fields in an array
  int layers;
  srand(time(NULL));
  for(x=0; x< 15; x++){
    strcpy(cakes4Party[x].icingFlavor, "vanilla");
    strcpy(cakes4Party[x].cakeFlavor, "strawberry");
    layers=rand()%4+1;
    cakes4Party[x].layers=layers;
  } 

  //printing cake fields
  printf("**************************************\n");
  printf("Your cakes are .....\n");  
  printCake(birthdayCake);
  printCake(cupCake);
  for(x=0; x<15; x++){
    printCake(cakes4Party[x]);
  } 
  return 0;
}

