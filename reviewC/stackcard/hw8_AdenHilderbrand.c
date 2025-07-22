// Aden Hilderbrand
// hw8_AdenHilderbrand.c
// 12/5/24

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARDS 10

typedef struct cards{
    int cards[MAX_CARDS];
    int top; 
} CARDS;

void push(CARDS* s, int card){
    int num;
    if (s->top == MAX_CARDS - 1){
        printf ("hand is full\n");
    }
    else {
        (*s).top++;
        (*s).cards[(*s).top] = card;
    }
}

int pop (CARDS* s){
    int c;
    if ((*s).top == -1)
        printf ("stack empty\n");
    else{
       c = (*s).cards[(*s).top];
      (*s).top--;
    }
    return c;
}

void display(CARDS* s){
    int i;
    for (i = (*s).top; i >= 0; i--) {
        printf ("%d\n", (*s).cards[i]);
    }
    printf ("\n");
}

void createGame( CARDS* player, CARDS* cpu){
    int i;
    for ( i= 0; i<MAX_CARDS; i++) {
        push(player, rand()%10+1);
        push(cpu, rand()%10+1);
     }
}

int main (){
    int player_card, cpu_card, choice, rounds = 0;
    
    CARDS player;
    CARDS cpu;
    
    srand(time(NULL));    
    player.top = -1;
    cpu.top = -1;
    
    createGame(&player, &cpu);
    
    printf ("\n The player cards are: \n");
    display (&player);
    
    printf ("\n The cpu cards are: \n");
    display (&cpu);
    
    while (player.top != -1 && cpu.top != -1){
        rounds++;
    
        printf ("      1    -->   PLAY               \n");
        printf ("      2    -->   EXIT              \n");
        printf ("PRESS 1 TO PLAY OR 2 TO EXIT\n");
        scanf    ("%d", &choice);
        
        switch (choice){
        case 1:
            player_card=pop(&player);
            printf ("\n player played: %d\n", player_card);
            cpu_card=pop(&cpu);
            printf ("\n cpu  played: %d\n", cpu_card);
            
            if (player_card>cpu_card) {
                 push(&player, cpu_card);
                 push(&player, player_card);
            } else if(cpu_card>player_card) {
                 push(&cpu, player_card);
                 push(&cpu, cpu_card);
            }
            
            printf ("\n The player cards are: \n");
            display(&player);
        
            printf ("\n The cpu cards are: \n");
            display(&cpu);
            break;
        
        case 2:
            return 0;
      }
    }
   
   if (player.top == -1 && cpu.top == -1)
printf("TIE GAME\n");
   else if (player.top == -1)
printf("CPU WON!\n");
   else if (cpu.top == -1)
        printf("PLAYER WON!\n");
    
    printf("Game lasted %d rounds\n", rounds);
    return 0;
}
