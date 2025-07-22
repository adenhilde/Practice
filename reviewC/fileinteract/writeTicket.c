// Aden Hilderbrand
// writeTicket.c
// 12/3/24

#include <stdio.h>
#include <string.h>

void writeTicket(int flightNum, float flightTime, char *homePort, char *destPort){
    FILE *file;
    file = fopen("ticket_AH.txt", "w");

    if (file == NULL){
        printf("Error opening 'ticket_AH.txt'");
    } else {
        fprintf(file, "Flight Number: %d\tFlight Time: %.2f\nDeparture Airport: %s\nDestination Airport: %s\n\n", flightNum, flightTime, homePort, destPort);
        fclose(file);
    }
}

int main(){
    int flightNum;
    float flightDuration;

    char toss;
    char homePort[50];
    char destPort[50];

    printf("Enter flight number: ");
    scanf("%d", &flightNum);

    printf("Enter flight duration: ");
    scanf("%f", &flightDuration);

    printf("Enter departure airport: ");
// grab buffer character
    scanf("%c", &toss);

    fgets(homePort, 50, stdin);
    homePort[strcspn(homePort, "\n")] = '\0';
    
    printf("Enter destination airport: ");

    fgets(destPort, 50, stdin);
    destPort[strcspn(destPort, "\n")] = '\0';

    writeTicket(flightNum, flightDuration, homePort, destPort);

    return 0;
}

