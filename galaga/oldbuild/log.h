// Holden Glass

#ifndef LOG_H
#define LOG_H

void setTime();
void createLog();
void ffmlog(char* message, float* numArr, int numArrLen, char charArr[10][100], int charArrLen);
void fmlog(char* message, float* numArr, int numArrLen);
void mlog(char* message);

#endif