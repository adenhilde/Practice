// Addison Miranda

#include <stdlib.h>
#include "enemyBullet.h"

enemyBullet* enemyBullet_list = NULL; // Linked list header

void fire_enemyBullet(int x, int y) { // Enemy x, Enemy y
    //this creates a new bullet, and dynamically allocates the memory so that we don't waste memory
    enemyBullet* new_enemyBullet = (enemyBullet*)malloc(sizeof(enemyBullet));
	
    if (!new_enemyBullet) {
		return; //error checking for memory allociation failure
	}
	
	new_enemyBullet->x = x; //bullet gets enemy's x
	new_enemyBullet->y = y + 1; //bullet starts below the enemy by 1
    // add the bullet to the start of the linked list of bullets
	new_enemyBullet->next = enemyBullet_list;
    // now the bullet_list's address is new_bullet's address making it the first item
	enemyBullet_list = new_enemyBullet; 
}

void move_enemyBullets(void) {
	enemyBullet* current = enemyBullet_list;
	enemyBullet* prev = NULL;
    
    // Loops through all items in the linked list
	while (current) {
		current->y++; //move bullet down

		if (current->y > 13) {
			enemyBullet* temp = current;
	
			if (prev) {
				prev->next = current->next;
			}
			else {
				enemyBullet_list = current->next;
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

void cleanup_enemyBullets(void) { //this function is for cleaning up bullets at the end of the game
	enemyBullet* current = enemyBullet_list;
	while (current) {
		enemyBullet* temp = current;
		current = current->next;
		free(temp); //one by one each bullet is freed until all memory is returned
	}
 
	enemyBullet_list = NULL; //destroy bullet_list pointer
}
