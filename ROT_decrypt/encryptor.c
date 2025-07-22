// Aden Hilderbrand 
// 9.24.24
// encryptor.c
// program uses rot13 to encrypt the string 'Hello World'

#include<stdio.h>

int main(){
// init var
char phrase[] = "boomerang";
int i=0;
while (phrase[i] != '\0'){
	char c = phrase[i];
	if(c >= 'a' && c <= 'z'){
		c = ((c - 'a' + 13) % 26) + 'a';		
	}
	else if (c >= 'A' && c <= 'Z'){
		c = ((c -'A' + 13) % 26) + 'A';
	}
	phrase[i] = c;
	i++;
}
printf("3ncryp73d: %s\n", phrase);
return 0;
}
