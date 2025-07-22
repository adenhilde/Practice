// hw7_p2_AdenHilderbrand.c
// Aden Hilderbrand
// 10.14.24
// This program attempts to decrypt a caesar cipher

#include<stdio.h>
#include<string.h>

decrypt(char *str){
  int i;
  int j;
  char newStr[100];
  int len = strlen(str);
  for(i=-5;i<=5;i++){
// shift all string elements by 'i'
	for (j=0;j < len;j++){
		char c = str[j];
		newStr[j] = ((c - 'a' + i) % 26 + 26) % 26 + 'a';
// read in string element, shift by 'i' # positions	
// read new char into newStr[j] 
// repeat until out of characters
		
	}
	newStr[j] = '\0';
	printf("For shift of  %d, decrypted word is %s\n", i, newStr);
  }

}

int main(){
  char string[1];

  while (1) {

	printf("Enter the encrypted word (STOP to quit): ");
	scanf("%s", &string);
	printf("%s\n", string);
// end condition 
	if (strcmp(string, "STOP") == 0)
		return 0;
	
	decrypt(string);	
  } 
  return 0;
}
