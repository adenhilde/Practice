// Addison Miranda

#include <stdlib.h>
#include "bullet.h"

Bullet* bullet_list = NULL; // Linked list header

void fire_bullet(int x, int y) { //params are from player's x and y
    //this creates a new bullet, and dynamically allocates the memory so that we don't waste memory
	Bullet* new_bullet = (Bullet*)malloc(sizeof(Bullet));

	if (!new_bullet) {
		return; //error checking for memory allociation failure
	}
	
	new_bullet->x = x; //bullet gets player's x
	new_bullet->y = y - 1; //bullet starts above the player by 1
	new_bullet->contact = 0;
    // add the bullet to the start of the linked list of bullets
	new_bullet->next = bullet_list;
    //now the bullet_list's address is new_bullet's address making it the start of the linked list
	bullet_list = new_bullet;
}

void move_bullets(void) {
	Bullet* current = bullet_list;
	Bullet* prev = NULL;

    // Loop through all the bullets
	while (current) {
		if (current->contact == 2) {
			current->y = 0;
		}

		current->y--; //move bullet up

		if (current->y < 0) {
			Bullet* temp = current;
	
			if (prev) {
				prev->next = current->next;
			}
			else {
				bullet_list = current->next;
			}
			
			current = current->next;
			free(temp);
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// This function is for cleaning up bullets at the end of the game
void cleanup_bullets(void) {
	Bullet* current = bullet_list;
 
	while (current) {
		Bullet* temp = current;
		current = current->next;
		free(temp);
	}
 
	bullet_list = NULL; //destroy bullet_list pointer
}
