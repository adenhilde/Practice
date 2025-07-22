// 4 functions in the file including main

#include<stdio.h>
#include<unistd.h>

#define ROWS 10
#define COLS 20

void print_array(char lines[ROWS][COLS]){
// takes 1 input argument
  int x,j;
  for (x=0; x< ROWS; x++){
    for(j=0;j<COLS;j++){
      putchar(lines[x][j]);
    }
    putchar('\n');
  }

}

void clearScreen(){
// takes 0 input arguments
  sleep(1);
  printf("\e[2J\e[H");
}

void changeColor(int color){
// takes 1 input argument
  if(color==1){
    printf(" \e[1;31m");  //bold red font
  }
  else if(color==2){
    printf(" \e[1;34m");  //bold blue font
  }
  else if(color==3){
    printf(" \e[1;32m");  //bold green font
  }
  else{
    printf("\e[0m\n");
  }
}

void initialize(char intro[ROWS][COLS]){
  int i,j;
  for (j=0;j<COLS;j++){
    intro[0][j] = '*';
    intro[ROWS-1][j] = '*';
  }
  
  for(i=1; i < ROWS - 1; i++){
    intro[i][0] = '*';
    intro[i][COLS - 1] = '*';
    for (j=1;j<COLS - 1;j++){
      intro[i][j] = ' ';
    }
  }
}
// each function returns void / nothing

int main(){

  char intro[ROWS][COLS]; 
  initialize(intro);

  int y,x;    
  clearScreen();
  print_array(intro);

  for(y=1; y< (ROWS-1); y++){   
    clearScreen();
    intro[y][y]='x';
    intro[ROWS - y - 1][y]='o';
    print_array(intro); 
    changeColor((y%3)+1);   
  } 

  changeColor(4);

  return 0;
}


