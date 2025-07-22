#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pokemon{     //define the Pokemon data type alias to:struct pokemon
  char name[30];
  int cp;
  struct pokemon* next;
} Pokemon;

//a 2D array with 10 pokemon names that are all less than 50 characters
char names[10][50]={ "pikachu", "magikarp", "eevee", "charmander", "squirtle", 
                     "vaporeon", "ditto", "jigglypuff", "hypno", "drowzee"};

//***********************************************************
//*  The printPokemon function expects a Pokemon pointer
//*  that is a pointer to the beginning of the linked list.
//*  It will print the pokemon info and then traverse the 
//*  until it reaches the end of the list.
//**********************************************************
void printPokemon(Pokemon* list){
  printf("Your Pokemon Are: \n****************\n");
  while(list != NULL){
    printf("Pokemon: %s cp:%d\n", (*list).name, (*list).cp);
    // list=(*list).next;  //or list->next
   list= list->next;
  }
  printf("\n");
}
//**********************************************************
//* releasePokemon
// 
//      does not work as intended sadly
//
Pokemon* releasePokemon(Pokemon* list, int monToRelease){
    Pokemon* newListFront = NULL;

    if (list == NULL){
        printf("Cannot release pokemon you do not have.\n");
        return list;
    } else {
        newListFront = list->next;
        printf("Releasing %s cp: %d\n", list->name, list->cp);
        free(list);
        return newListFront;
    }


}

//***********************************************************
//* addPokemon adds a new Pokemon object to the end of the list.
//* dynamic memory allocation is used. The name of the new 
//* Pokemon is randomly selected from the list.  The cp is
//* randomly selected (0-1999).
//***********************************************************
Pokemon* addPokemon(Pokemon* list){
  if(list== NULL){    //This will be the first Pokemon in the list
    list=malloc(sizeof(Pokemon));  //dynamically allocate memory for Pokemon
    strcpy(list->name, names[rand()%10]);
    list->cp=400;
    list->next=NULL;
    return list; 
  }
  else {  //Find the end of the list and add a new Pokemon
    int count =0;
    Pokemon* current = list;
// count the pokemon, if more than 5 
    while(current != NULL) {
        count++;
        current = current->next;
    }       
    if (count >= 5){
        printf("Sorry, you cannot hold more Pokemon. Maximum 5.\n");
        return list;
    }

    Pokemon* frontOfList=list;
    while(list->next != NULL){
      list=list->next;
    }
    list->next=malloc(sizeof(Pokemon));
    Pokemon* newPokemon=list->next;
    strcpy(newPokemon->name, names[rand()%10]);
    newPokemon->cp=rand()%2000;
    newPokemon->next=NULL;
    return frontOfList;
  }  
}

int main(){

  Pokemon* mine=NULL;
  int catch=1;
  int choice=-1;

  while(catch > 0){
    printf("Would you like to Catch a Pokemon, Release a Pokemon, or Exit? (0=exit,1=catch,2=release) ");
    scanf("%d", &catch);
    if(catch==1){
          mine=addPokemon(mine);
    }
    if(catch==2){
        printf("Which pokemon will you release? Pick a number 1-5;");
        scanf("%d", &choice);
        releasePokemon(mine, choice);
        }
    } 

    printPokemon(mine); 
  }
  //Note: the dynamically allocated memory should be release.
  //This step is left as an exercise.

    Pokemon* current=mine;

    while(current != NULL) {
        free(current);
        current = current->next;
    }       
  
  return 0;
}



