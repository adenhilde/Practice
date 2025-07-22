/*
Authors:
    Holden Glass
    Aden Hilderbrand
    Addison Miranda
    Pol Monso Marza
Versions:

Resources:

*/



/******************************************************************************************************************/
/* Includes/Defines/Globals ***************************************************************************************/
/******************************************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <time.h>

#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemyBullet.h"
#include "bug.h"
#include "log.h"
#include "Score.h"

#define ROWS 13 //define the size of the gamefield
#define COLS 54
#define MAX_SPAWN(x) (int)(7 * (x) - 1) //second number is number to change for difficulty

int i;
int gameRunning = 0;  //this is 1 when the game is running
int menuRunning = 0;
int gameExit = 0; // Whether the program needs to exit

pthread_mutex_t lock;  //this basically initializes a lock so that multiple threads don't race for the same resources



/******************************************************************************************************************/
/* Function Prototypes ********************************************************************************************/
/******************************************************************************************************************/



void initializeRandomSeed();

int difficultyOfGame (int difficulty, int gameProgress);

void print_array(char lines[ROWS][COLS]);

void clearScreen();

void initTermios(int echo);  //this initiates termios in the input.c/input.h files, and passes echo

void resetTermios(void); //this resets termios

void *input_handler(void *arg);

void gameEnd(long int *difficulty, int *frame, int *gameProgress, int *spawnFrequency, int bugSpawnMap[91], int *bug_id, Player *player);

int galagaMenu();

void reset_score();



/******************************************************************************************************************/
/* Main ***********************************************************************************************************/
/******************************************************************************************************************/



int main() {
    createLog();
    mlog("C library header files loaded successfully");
    mlog("Galaga header files loaded successfuly");
    mlog("Definitions successful");
    mlog("Global variables successful");
    mlog("Functions loaded");
    
    initializeRandomSeed();
    
	pthread_t input_thread; //declares variable input_thread
	Player player; //initialize struct player
 
	init_player(&player); //call the constructer method
	
	pthread_mutex_init(&lock, NULL); //initializes lock for mutex, necessary for mutex use
	initTermios(0);   //initialize termios
     
    //create a thread with input_thread, input_handler as the function, and the player struct
	pthread_create(&input_thread, NULL, input_handler, &player);
	
	int frame = 0; //initialize a variable frame so we can change the rate different things move
	long int difficulty =  7; //this determines how often bugs spawn in
	int gameProgress = 1;
     
    //this initializes a variable that allows for spawn frequency of the bugs
	int spawnFrequency = MAX_SPAWN(difficultyOfGame(difficulty, gameProgress));

	int bugSpawnMap[91]; //create a map of spawned in bugs
	for (i = 0; i < 91; i++) {  //initiate every bug to 0 (not spawned in)
		bugSpawnMap[i] = 0;
	}
	int bug_id = rand() % 13 * 7; //this is the first bug_id, it will be updated based on where in the array it is
     
    mlog("Variable initialization complete");

	galagaMenu();
	
	clearScreen();
     
    mlog("Game running");

	while(gameRunning) {
        //this actually locks the variable lock, so that it has exclusive access. Seems redundant to me, but i'm following the documentation so idk
		pthread_mutex_lock(&lock);

		char intro[ROWS][COLS]={  //cleans the playable area clean every time
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H",
			"H                                                H"};

		clearScreen();
        
        // This is to control framerate so I can easily adjust it. Checks every 3 frames
		if (frame % 3 == 0) {
            int spawnLimit = MAX_SPAWN(difficultyOfGame(difficulty, gameProgress));
            // spawnLimit > 0: Difficulty > 0, meaning the game is less than 7 min
		    if (spawnLimit > 0 && (0 <= spawnFrequency % spawnLimit) && (spawnFrequency % spawnLimit < 13)) {
                int totalBugsSpawned = 0;
                    
                // Finds the next available spot to start spawning bugs
                // totalBugsSpawned != 91 : checks to make sure all bugs haven't spawned
                if (bug_id < 0 || bug_id > 90) bug_id = 0;
                while (bugSpawnMap[bug_id] == 1 && totalBugsSpawned != 91) {
                    totalBugsSpawned++;
  				    bug_id++;

                    // Loops to the start of the bugList if it's at the end
      				if(bug_id > 90) {
     					bug_id = 0;
         			}
     			}
                
                // Spawns bugs
     			if (totalBugsSpawned < 90) {
    				spawn_bug(bug_id);
         			bugSpawnMap[bug_id] = 1;
         		}
      		}
     
            // Moves the bugs
            move_bugs(player.x, bugSpawnMap);
             
	        spawnFrequency++;
		}
        
        // Move the bullets
		if (frame % 2 == 0) {
			move_bullets();
		}
		
		Bug* current_bug = bug_list;
        Bullet* current_bullet = bullet_list;
        int hit = 0;
        
        // Check for bug-bullet collisions
		while (current_bug != NULL) {
			current_bullet = bullet_list;
			while (current_bullet != NULL) {
				if(current_bug->y == current_bullet->y && current_bug->x == current_bullet->x) {
                    // Log a bug death
                    float numArr[] = {current_bug->bug_id};
                    fmlog("Killed bug (bug_id: %d)", numArr, 1);
                    
                    // Kill the bug
					bugSpawnMap[current_bug->bug_id] = 0;
					current_bug = kill_bug(current_bug->bug_id);
                    
                    // Set the bullet into explostion mode and add the score
                    current_bullet->contact = 1;
                    intro[current_bullet->y][current_bullet->x] = 'x';
                    add_score(10);
                    
                    hit = 1;
				}
            
				current_bullet = current_bullet->next;
                if (hit) break;
			}
            
            if (hit) {
                hit = 0;
                continue;
            }
            
            // Did the bug hit the player
			if (current_bug->x == player.x && current_bug->y == player.y) {
				gameRunning = 0;
				gameEnd(&difficulty, &frame, &gameProgress, &spawnFrequency, bugSpawnMap, &bug_id, &player);
                initializeRandomSeed();
                break;
			}
            
			current_bug = current_bug->next;
		}
        
		current_bug = bug_list;
        
        // Place the bug symbol on the map (intro)
		while (current_bug != NULL) {
            // Double check the bug is on the screen
            if (current_bug->x > 0 && current_bug->x < COLS - 1) {
                if (current_bug->y >= 0 && current_bug->y < ROWS) {
                    // The symbol depends on what the bug_id is
                    if (current_bug->bug_id < 21) {
        				intro[current_bug->y][current_bug->x] = 'M';
        			}
        			else if (current_bug->bug_id < 42) {
        				intro[current_bug->y][current_bug->x] = 'T';
        			}
        			else if (current_bug->bug_id < 70) {
        				intro[current_bug->y][current_bug->x] = 'Y';
        			}
        			else {
        				intro[current_bug->y][current_bug->x] = 'V';
        			}
                }
            }
			
			current_bug = current_bug->next;
		}
        
		current_bullet = bullet_list;
        // Place the bullet on the map (intro)
        // Updates the explosion animation
		while (current_bullet != NULL) {
			if (current_bullet->contact == 1) {
				intro[current_bullet->y-1][current_bullet->x-1] = '\\';
				intro[current_bullet->y-1][current_bullet->x] = '|';
				intro[current_bullet->y-1][current_bullet->x+1] = '/';
				intro[current_bullet->y][current_bullet->x-1] = '>';
				intro[current_bullet->y][current_bullet->x] = 'X';
				intro[current_bullet->y][current_bullet->x+1] = '<';
				intro[current_bullet->y+1][current_bullet->x-1] = '/';
				intro[current_bullet->y+1][current_bullet->x] = '|';
				intro[current_bullet->y+1][current_bullet->x+1] = '\\';
				current_bullet->contact = 2;
			}

			else if (current_bullet->y >= 0 && current_bullet->y < ROWS) {
			    intro[current_bullet->y][current_bullet->x] = '.';
			}
        
			current_bullet = current_bullet->next;
		}
        
        // Fires bullets
        // Fire rate increases as the difficulty increases
        if (gameProgress % MAX_SPAWN(difficulty) == 0) {
            int spot;
            // Pick a random bug that is spawned in
            while (1) {
                spot = rand() % 92;
                if (bugSpawnMap[spot] == 1) break;
            }
            
            // Find that bug
            current_bug = bug_list;
            while (current_bug != NULL) {
                if (current_bug->bug_id == spot) {
                    // Have that bug fire a bullet
                    fire_enemyBullet(current_bug->x, current_bug->y+1);
                    break;
                }
                current_bug = current_bug->next;
            }
        }
        
        // Move the enemyBullets
        if (frame % 2 == 0) {
            move_enemyBullets();
        }
        
        // Place the enemy bullets on the map (intro)
        enemyBullet* current_EB = enemyBullet_list;
        while (current_EB != NULL && gameRunning == 1) {
            // Did the bullet hit the player
            if (current_EB->x == player.x && current_EB->y == player.y) {
                gameRunning = 0;
                gameEnd(&difficulty, &frame, &gameProgress, &spawnFrequency, bugSpawnMap, &bug_id, &player);
                initializeRandomSeed();
                break;
            }
            else {
                intro[current_EB->y][current_EB->x] = '!';
            }
            
            current_EB = current_EB->next;
        }
        
        //places character model at player[x] player[y]
		intro[player.y][player.x] = '^';
		print_array(intro); 
		frame++;
		gameProgress++;

        //resets frames at 48 because 48 is easily divisible by many numbers, allowing many options for many speeds
		if(frame > 47) {
			frame = 0;
		}
        
        //same thing but for spawn frequency
		if(spawnFrequency > MAX_SPAWN(difficultyOfGame(difficulty, gameProgress)) + 1) {
			spawnFrequency = 1;
		}

		pthread_mutex_unlock(&lock); //this unlocks the mutex lock
	}
 
    mlog("End of main");
	
    pthread_join(input_thread, NULL); //these three lines reset all terminal settings
    mlog("Threads rejoined");

	cleanup_bullets(); //free all of the bullet memory
    cleanup_enemyBullets(); // Free all enemyBullet memory
	resetTermios(); //resets termios
	pthread_mutex_destroy(&lock); //destroys the lock
    
    mlog("Cleanup complete\n\nBye bye!");
    
    clearScreen();

	return 0;
}



/******************************************************************************************************************/
/* Functions ******************************************************************************************************/
/******************************************************************************************************************/



void initializeRandomSeed() {
    // Created the random seed so the bugspawning is different each time
	srand(time(0));
}

int difficultyOfGame (int difficulty, int gameProgress) {
	if (difficulty > 1){
        // Decrements difficulty by 1 every 1333 times the while loop runs
		if (gameProgress % 1333 == 0) {
			difficulty--;
		}
	}
    
    // Returns difficulty. The lower the number, the more difficult
	return (int)difficulty;
}

void print_array(char lines[ROWS][COLS]) { //this function prints the gamefield
	int x, y;
	for (x=0; x< ROWS; x++){
		for (y = 0; y < COLS; y++) {
			char ch = lines[x][y];
			if (ch == '^') {
				printf("\33[1;94m%c\033[0m", ch); //bright blue player
			}
			else if (ch == '.' || ch == '!') {
				printf("\33[1;91m%c\033[0m", ch); //red bullets
			}
			else if (ch == 'M') {
				printf("\33[1;92m%c\033[0m", ch); //green enemies
			}
			else if (ch == 'T') {
				printf("\33[1;95m%c\033[0m", ch); //purple enemies
			}
			else if (ch == 'Y') {
				printf("\33[1;96m%c\033[0m", ch); //cyan enemies
			}
			else if (ch == 'V') {
				printf("\33[1;93m%c\033[0m", ch); //yellow enemies
			}
			else if (ch == 'x' || ch == 'X' || ch == '<' || ch == '>' || ch == '/' || ch == '\\' || ch == '|') {
				printf("\33[1;31m%c\033[0m", ch); //red enemies
			}
			else {
				printf("%c", ch);
			}
		}
    
		printf("\n");
	}
    
    printf("\n\nCurrent Score: %d\n", get_score());
}

void clearScreen() {  //this simply clears the screen and sleeps the program
    usleep(45000);
    printf("\033[2J\033[H");
}

void *input_handler(void *arg) { //this block gets inputs
	Player *player = (Player *)arg; //initialize the player struct
	char c; //this is the input char
    
	while (1) {
		c = getchar();

		if (menuRunning && c == ' ') {
			menuRunning = 0;
			gameRunning = 1;
		}

		else if (gameRunning) {
			//left arrow is "\e[D" right is "\e[C", '\e' is 27 in ascii, so it checks if the first char is '\e'
            if (c == 27) {
                //get next char, this skips the '['
				getchar();
            
                //checks for 'D' or 'C' to see if its a left or right arrow click
				switch (getchar()) {
					case 'D':
						move_left(player);
						break;
					case 'C':
						move_right(player);
						break;
				}
			}
			else if (c == ' ') {
				fire_bullet(player->x, player->y);
			}
		}
    
        // Quits the game any time q is pressed
        if (c == 'q') {
            gameRunning = 0;
            menuRunning = 0;
            gameExit = 1;
            return NULL;
        }
	}
}

void gameEnd(long int *difficulty, int *frame, int *gameProgress, int *spawnFrequency, int bugSpawnMap[91], int *bug_id, Player *player) {
    // Plays after the game has ended, displaying the end screen and options for continuing
    const char* galagaArt = 
	    "\e[0;97m ::::::::      :::     ::::    ::::  ::::::::::       ::::::::  :::     ::: :::::::::: :::::::::  \n"
	    "\e[0;96m:+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:             :+:    :+: :+:     :+: :+:        :+:    :+: \n"
	    "\e[0;96m+:+         +:+   +:+  +:+ +:+:+ +:+ +:+             +:+    +:+ +:+     +:+ +:+        +:+    +:+ \n"
	    "\e[0;94m:#:        +#++:++#++: +#+  +:+  +#+ +#++:++#        +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  \n"
	    "\e[0;94m+#+   +#+# +#+     +#+ +#+       +#+ +#+             +#+    +#+  +#+   +#+  +#+        +#+    +#+ \n"
	    "\e[0;95m#+#    #+# #+#     #+# #+#       #+# #+#             #+#    #+#   #+#+#+#   #+#        #+#    #+# \n"
	    "\e[0;95m ########  ###     ### ###       ### ##########       ########      ###     ########## ###    ### \n\0";

	clearScreen();
	
    // Check/Save the score from the previous game
	load_highest_score();
  	check();
  	save_score();
	
    // Print out galagaArt line by line
	for (i = 0; i < strlen(galagaArt); i++) {
		usleep(1500);
		printf("%c", *(galagaArt + i));
	}

	menuRunning = 1;
	int menuCounter = 1;
	
	clearScreen();
    
    // Prints the scores and flashes menu options
	while(menuRunning == 1) {
		usleep(45000);
		clearScreen();
		printf("%s\n", galagaArt);
		menuCounter++;
    
		if (menuCounter > 14) {
			menuCounter = 1;
		}
    
		if ((menuCounter % 14 < 8)) {
    		printf("\n\n");
    		printf("                                [Space to play again, q to quit!]\n\n");
		}
        else {
            printf("\n\n\n\n");
        }
        printf("                                            best score: %d \x1b[0m   \n", get_highest_score());
        printf("                                           \e[0;95m current score: %d \x1b[0m\n", get_score());
	}
 
    menuRunning = 0;
    gameRunning = 0;
    
    // reset game for next attempt  
    clearScreen();
    
    cleanup_bugs();
    cleanup_bullets();
    cleanup_enemyBullets();
    
    reset_score();
    
    init_player(player);
    for (i=0;i<91;i++){
      bugSpawnMap[i] = 0;
    }
    *spawnFrequency = MAX_SPAWN(difficultyOfGame(*difficulty, *gameProgress));
    *bug_id = rand() % (13 * 7);

    *frame = 0;
    *gameProgress = 1;
    *difficulty = 7;
    
    if (!gameExit) galagaMenu();
    clearScreen();
}


int galagaMenu() {
    // Displays the menu art and waits for user input to start the game
	const char* galagaArt = 
	    "\e[0;97m ::::::::      :::     :::            :::      ::::::::      :::           ::::    ::::  ::::::::::: ::::    ::: ::::::::::: \n"
	    "\e[0;96m:+:    :+:   :+: :+:   :+:          :+: :+:   :+:    :+:   :+: :+:         +:+:+: :+:+:+     :+:     :+:+:   :+:     :+:     \n"
	    "\e[0;96m+:+         +:+   +:+  +:+         +:+   +:+  +:+         +:+   +:+        +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+     \n"
	    "\e[0;94m:#:        +#++:++#++: +#+        +#++:++#++: :#:        +#++:++#++:       +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+     \n"
	    "\e[0;94m+#+   +#+# +#+     +#+ +#+        +#+     +#+ +#+   +#+# +#+     +#+       +#+       +#+     +#+     +#+  +#+#+#     +#+     \n"
	    "\e[0;95m+#+    #+# #+#     #+# #+#        #+#     #+# #+#    #+# #+#     #+#       #+#       #+#     #+#     #+#   #+#+#     #+#     \n"
	    "\e[0;95m ########  ###     ### ########## ###     ###  ########  ###     ###       ###       ### ########### ###    #### ########### \n\0";

	clearScreen();
	
    // Prints galagaArt line by line until it is all on the screen
	for (i = 0; i < strlen(galagaArt); i++) {
		usleep(1500);
		printf("%c", *(galagaArt + i));
	}

	menuRunning = 1;
	int menuCounter = 1;
    
    // Flashes the menu options on the screen
	while(menuRunning) {
		usleep(45000);
		clearScreen();
		printf("%s\n", galagaArt);
		menuCounter++;
    
		if (menuCounter > 14) {
			menuCounter = 1;
		}
    
		if ((menuCounter % 14 < 8)) {
    		printf("\n\n");
    		printf("                                                   [Press Space to start, q to quit!]\n");
		}
		
	}

	return 0;
}

