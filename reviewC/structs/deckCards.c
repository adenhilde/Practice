#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct card{
  char suit[10]; //hearts, spaces, clubs, or diamonds
  char rank[10]; //Ace, 2, 3, ... King
  int  value;    //ex. in BlackJack 2=2, Jack/Queen/King=10
};

int main(){
  int x, y, cardNum=0;
  char suits[4][10]={ "hearts", "spades", "clubs", "diamonds" };
  char rank[13][10]={ "ace", "2", "3", "4", "5", "6", "7", "8", "9", "10","jack", "queen", "king" };
  int value[13] = { 1,2,3,4,5,6,7,8,9,10,10,10,10};
  struct card deck[52];

  //create and print a deck of 52 cards
  for(x=0; x<4; ++x){
    for(y=0; y< 13; y++){
        strcpy(deck[cardNum].suit, suits[x]);
        strcpy(deck[cardNum].rank, rank[y]);
        deck[cardNum].value = value[y]; 
        printf("Card:%s of %s (%d)\n", deck[cardNum].rank, deck[cardNum].suit, deck[cardNum].value);
        cardNum++;
    }
  }

  //TO-DO - deal 2 cards to each player and print the name of the winner
    srand(time(NULL));  

    int i;    

    struct card player1[2], player2[2];
    for (i=0;i<2;i++){
        int cardIndex = rand() % 52;
        player1[i] = deck[cardIndex];
        deck[cardIndex] = deck[51];
        cardNum--;

        cardIndex = rand() % 51;
        player2[i] = deck[cardIndex];
        deck[cardIndex] = deck[50];
        cardNum--;
    }
// calculate scores

    int player1score = player1[0].value + player1[1].value;
    int player2score = player2[0].value + player2[1].value;

// print cards and scores

    printf("\nPlayer 1's cards: \n");
    for(i=0;i<2;i++){
        printf("%s of %s (%d)\n", player1[i].rank, player1[i].suit, player1[i].value);
    }
    printf("\nPlayer 1's score: %d\n", player1score);

    printf("\nPlayer 2's cards: \n");
    for(i=0;i<2;i++){
        printf("%s of %s (%d)\n", player2[i].rank, player2[i].suit, player2[i].value);
    }
    printf("\nPlayer 2's score: %d\n", player2score);

    if (player1score > player2score){
        printf("\nPlayer 1 wins!!\n");
    } else if (player2score > player1score){
        printf("\nPlayer 2 wins!!\n");
    } else
        printf("\nIt's a tie!!!!!!!!");

    return 0;
}















