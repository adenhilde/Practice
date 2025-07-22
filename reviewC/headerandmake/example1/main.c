#include <stdio.h>

extern float waterBoilingPoint;
float convertCtoF(float c);

int main(){
  float tempC, tempF;
  printf("Enter temp in C: ");
  scanf("%f", &tempC);
  tempF = convertCtoF(tempC);
  printf("%.1f C is %.1f F\n", tempC, tempF);
  printf("Boiling point of water is %.1f\n", waterBoilingPoint);
  return 0;  
}
