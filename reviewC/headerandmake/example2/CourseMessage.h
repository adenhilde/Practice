#pragma once

typedef struct coursemessage {
    char name[100];
    char message[500];
} CourseMessage;


void printMessage(CourseMessage* m);

