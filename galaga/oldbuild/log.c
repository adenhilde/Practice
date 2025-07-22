// Holden Glass

#include "log.h"
#include <stdio.h>
#include <time.h>

#define SIZE 50
#define LOG "log.txt"

// Time struct so each entry can have a time attached to it
struct tm* logTime;

// Sets the time struct to the current time
void setTime() {
    time_t rawtime;
    time(&rawtime);
    logTime = localtime(&rawtime);
}

// Initializes the log file
void createLog() {
    // Clear the log file
    FILE* f = fopen(LOG, "w");
    
    // Get the text formatted time
    setTime();
    char myTime[SIZE];
    strftime(myTime, sizeof(myTime), "%d/%m/%Y %X %Z", logTime);
    
    // Print the header to the log file
    fprintf(f, "*************************************************************************************************\n");
    fprintf(f, "************************************     Beginning of Log    ************************************\n");
    fprintf(f, "************************************       Log created       ************************************\n");
    fprintf(f, "************************************ %s ************************************\n", myTime);
    fprintf(f, "*************************************************************************************************\n");
    
    fclose(f);
}

// ffmlog = fully formatted make log
// A message with character and number formatting
void ffmlog(char* message, float* numArr, int numArrLen, char charArr[10][100], int charArrLen) {
    FILE* f = fopen(LOG, "a");
    
    // Get the text formatted time
    setTime();
    char myTime[SIZE];
    strftime(myTime, sizeof(myTime), "%d/%m/%Y %X %Z", logTime);
    fprintf(f, "%s: ", myTime);
    
    int numArrIndex = 0;
    int charArrIndex = 0;
    
    // Loop through the message character by character
    // If the identifier is d, f, c, or s, it prints the values given in numArr and charArr
    // Other wise it prints % with the associated character
    while (*message != '\0') {
        if (*message == '%') { // There could be a formatted value
            message++;
            if (*message == 'd') { // int
                if (numArrIndex < numArrLen) fprintf(f, "%.0f", numArr[numArrIndex]);
                else printf("%%%c", *message);
                numArrIndex++;
            }
            else if(*message == 'f') { // float: only prints 2 digits
                if (numArrIndex < numArrLen) fprintf(f, "%.2f", numArr[numArrIndex]);
                else printf("%%%c", *message);
                numArrIndex++;
            }
            else if(*message == 'c' || *message == 's') { // character or string
                if (charArrIndex < charArrLen) fprintf(f, "%s", charArr[charArrIndex]);
                else printf("%%%c", *message);
                charArrIndex++;
            }
            else printf("%%%c", *message);
        }
        else if (*message == '\\') { // Escape character
            message++;
            if (*message == 'n') fprintf(f, "\n"); // Newline character
            else printf("\\%c", *message);
        }
        else fprintf(f, "%c", *message);
        message++;
    }    
    
    fprintf(f, "\n");
    fclose(f);
}

// fmlog = formated make log
// A message with just number formatting
void fmlog(char* message, float* numArr, int numArrLen) {
    char charArr[10][100];
    ffmlog(message, numArr, numArrLen, charArr, 0);
}

// mlog = make log
// Just a message with no formatting
void mlog(char* message) {
    float numArr[1];
    fmlog(message, numArr, 0);
}