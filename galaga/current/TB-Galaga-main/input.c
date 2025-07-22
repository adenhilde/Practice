#include <termios.h>
#include <unistd.h>
#include "input.h"

static struct termios old, new; //create old and new to store settings so they can be reset

void initTermios(int echo) {
	tcgetattr(0, &old);     //store the current settings to old
	new = old;              //assign old to new so we can edit new settings
	new.c_lflag &= ~ICANON; //disable cannonical mode via a bitwise function
	
    // Cannonical mode waits for a user to hit enter to take an input
    // This allows it to take functions asynchronously from the rest of the program
    
    // this part of the code makes it so that when you type an input it doesn't appear on screen
	if (echo) {
		new.c_lflag |= ECHO; //enable echo via bitwise function 
	}
	else {
		new.c_lflag &= ~ECHO; //disable echo via bitwise function
	}

	tcsetattr(0, TCSANOW, &new); //apply the settings we just configured to variable "new"
}

void resetTermios(void) {
	tcsetattr(0, TCSANOW, &old); //apply original settings we stored to variable "old"
}
