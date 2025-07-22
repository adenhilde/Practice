#include <stdio.h>
#include "CourseMessage.h"

void printMessage(CourseMessage* m){
  printf("%s: %s\n", (*m).name, (*m).message);
}
