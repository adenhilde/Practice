// Addison Miranda

#include "player.h"

#define MIN 1    //define the min and max left and right
#define MAX 48

void init_player(Player *player) {
	player->x = 23; // width = 48, -2 for edges = 46, /2 = 23
	player->y = 12;
}

void move_left(Player *player) { //when move left called
	if (player->x > MIN) {  //if player x > min then move left
		player->x -= 1;
	}
}

void move_right(Player *player) {  //when move right called
	if (player->x < MAX) {  //if player x < max move right
		player->x += 1;
	}
}
