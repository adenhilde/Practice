#include <stdio.h>
#include <string.h>

typedef struct basket_team{
  char name[20];
  char city[20];
  int season_points;
  struct basket_team* next;
} BTeam;

// create new BTeam object, find team with most points, copy their struct info to the champ object. print champ object at end
// also make sure there isnt multiple champs
void findChamp(BTeam* list){
    int maxPoints = 0;
    BTeam* champ = NULL;
    int multipleChamps = 0;

    while (list != NULL) {
        if (list->season_points > maxPoints){
            maxPoints = list->season_points;
            champ = list;
            multipleChamps = 0;
        } else if (list->season_points == maxPoints) {
            multipleChamps = 1;
        }
        list = list->next;
    }
    
    if(multipleChamps){
        printf("No champion.\n");
    } else if (champ != NULL){
        printf("Champion %s (%s)\n", champ->name, champ->city);
    } else {
        printf("No teams found.\n");
    }
}

void printTeams(BTeam* list){ 
  while(list != NULL){
    printf("Team Name: %s ", (*list).name);
    printf("City: %s ", (*list).city);
    printf("Season points: %d ", (*list).season_points);
    list=(*list).next;  //or list=list->next
    printf("\n");
  }
  printf("\n");
}

int main(){

  BTeam t4 ={"Bulls", "Chicago", 15, NULL};
  BTeam t3 ={"Lakers", "LA", 20, &t4};
  BTeam t2 ={"Spurs", "San Antonio", 25, &t3};
  BTeam t1 ={"Suns", "Phoenix", 30, &t2} ;


  printTeams(&t1);

  findChamp(&t1);
  return 0;
}



