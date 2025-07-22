// countMoney.c
// Aden Hilderbrand
// 11.6.24
// This program receives # of dollars & cents and prints the money in a 
// understandable format

#include<stdio.h>

typedef struct{
    int dollars;
    int cents;
} Money;

Money getMoney() {
    Money m = {0,0};
    do {
        printf("How many dollars do you have?: ");
        if (scanf("%d", &m.dollars) != 1 || m.dollars < 0) {
            printf("Invalid input for dollars.\n");
            while (getchar() != '\n');
        }
    } while (m.dollars < 0);

    do {
        printf("How many cents do you have?: ");
        if (scanf("%d", &m.cents) != 1 || m.cents < 0) {
            printf("Invalid input for cents.\n");
            while (getchar() != '\n');
        }
    } while (m.cents < 0);
    return m;
}

void printMoney(Money* m){
    m->dollars += m->cents / 100;
// division adds only the amount of dollars in cents to m.dollars
    printf("You have: $%d.%02d\n", m->dollars, (m->cents % 100));
// modulus removes the dollars we accounted for and prints only the change under a dollar
}

void addMoney(Money* m){
    int moneyToAdd=0;
    printf("How many dollars would you like to add to your account?: ");
    scanf("%d", &moneyToAdd);
    
    m->dollars += moneyToAdd;
}

void minusMoney(Money* m){
    int moneyToMinus=0;
    printf("How many dollars would you like to subtract from your account?: ");
    scanf("%d", &moneyToMinus);

    m->dollars -= moneyToMinus;
}

int main(){
    Money money = getMoney();
    
    addMoney(&money);

    minusMoney(&money);

    printMoney(&money);

    return 0;
}
