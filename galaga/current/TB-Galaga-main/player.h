#ifndef PLAYER_H
#define PLAYER_H

typedef struct {  //create struct for player with x and y coordinates
	int x;
	int y;
} Player;

void init_player(Player *player);
void move_left(Player *player);
void move_right(Player *player);

#endif
