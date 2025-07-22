//Your name here
#include <stdio.h>
#include <string.h>
#include "CourseMessage.h"

int main(){
  CourseMessage m;
  
  printf("What is your name: ");
  scanf("%s", m.name);
  strcpy(m.message, "Projects Due Nov 20th");
  printMessage(&m);
  return 0;
}

