// Addison Miranda
// Holden Glass

#include <stdlib.h>
#include "bug.h"

Bug* bug_list = NULL; // Linked list header

int startingPositionX[13] = {6,33,8,8,21,26,3,37,33,21,20,39,14};
int startingPositionY[13] = {8,5,5,6,7,3,3,8,6,5,2,3,3};

int bugPathX1[33] = { //left side x
	1,2,3,4,5,6,6,7,8,9,9,10,11,12,13,14,14,13,12,11,10,10,9,8,9,10,11,12,13,14,15,16,17
};

int bugPathY1[33] = { //left side y
	0,0,0,0,1,1,2,3,4,4,5,5,5,5,4,3,2,1,1,2,2,3,4,5,6,6,6,6,5,5,5,6,5
};

int bugPathX2[26] = { //right side x
	48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,32,33,34,35,35,34,33,32,31
};

int bugPathY2[26] = { //right side y
	0,1,2,3,3,3,2,2,3,4,5,5,5,4,4,3,3,2,1,1,2,3,4,4,5,5
};

void spawn_bug(int id) {
	Bug* new_bug = (Bug*)malloc(sizeof(Bug)); //this creates a new bug, and dynamically allocates the memory so that we don't waste memory
	if (!new_bug) {
		return; //error checking for memory allociation failure
	}

	int startPosition, fly_pattern;

	if (id % 14 < 7 && id < 63) {
		startPosition = 0;
	}
	else if (id % 14 >= 7 && id < 63) {
		startPosition = 1;
	}
	else {
		startPosition = rand() % 2;
	}

	if (id % 28 < 14 && id < 56) {
		fly_pattern = 0;
	}
	else if (id % 28 >= 14 && id < 56) {
		fly_pattern = 1;
	}
	else {
		fly_pattern = rand() % 2;
	}

	new_bug->x = 0;
	new_bug->y = 0;
	new_bug->bug_id = id;
	new_bug->bug_spawn = startPosition;
	new_bug->bug_fly_pattern = fly_pattern;
	new_bug->bug_spawn_counter = 0;
	new_bug->stage = 0;
	new_bug->next = bug_list; // add the bug to the start of the linked list of bugs
	bug_list = new_bug; //now the bug_list's address is new_bug's address, effectively making new_bug the head of the linked list referred to by bug_list
}

void move_bugs(int x, int* bugSpawnMap) { //return the bug that got deleted
	Bug* current = bug_list;
	int destinationX;
	int destinationY;

	while (current) { //movement about to get real fucky
		switch (current->stage) {
			case 0:
				if(current->bug_spawn == 0) { //left side
					if (current->bug_fly_pattern == 0) { //left pattern
						if(current->bug_spawn_counter == 33) {
							current->stage = 1;
							break;
						}
						current->x = bugPathX1[current->bug_spawn_counter];
						current->y = bugPathY1[current->bug_spawn_counter];
						current->bug_spawn_counter++;
					}
					if (current->bug_fly_pattern == 1) { //right pattern
						if(current->bug_spawn_counter == 26) {
							current->stage = 1;
							break;
						}
						current->x = 49 - bugPathX2[current->bug_spawn_counter];
						current->y = bugPathY2[current->bug_spawn_counter];
						current->bug_spawn_counter++;
					}
				}
				if(current->bug_spawn == 1) { //right side
					if (current->bug_fly_pattern == 0) { //left pattern
						if(current->bug_spawn_counter == 33) {
							current->stage = 1;
							break;
						}
						current->x = 49 - bugPathX1[current->bug_spawn_counter];
						current->y = bugPathY1[current->bug_spawn_counter];
						current->bug_spawn_counter++;
					}
					if (current->bug_fly_pattern == 1) { //right pattern
						if(current->bug_spawn_counter == 26) {
							current->stage = 1;
							break;
						}
						current->x = bugPathX2[current->bug_spawn_counter];
						current->y = bugPathY2[current->bug_spawn_counter];
						current->bug_spawn_counter++;
					}
				}

				break;
			case 1:
				destinationX  = startingPositionX[(int)(current->bug_id / 7)] + (current->bug_id % 7);
				destinationY = startingPositionY[(int)(current->bug_id / 7)];
				if (destinationX < current->x) {
					current->x--;
				}
				else if (destinationX > current->x) {
					current->x++;
				}
				if (destinationY < current->y) {
					current->y--;
				}
				else if (destinationY > current->y) {
					current->y++;
				}

				if (destinationY == current->y && destinationX == current->x) {
					current->stage = 2;
				}
				break;
			case 2:
				current->bug_spawn_counter++;
				if(current->bug_spawn_counter == 100) { 
					current->stage = 3; //so that I can test
				}
				break;
			case 3:
				current->bug_spawn_counter++;
				current->y++;
				if (x < current->x) {
					current->x--;
				}
				else if (x > current->x) {
					current->x++;
				}
				break;
		}
		
		if (current->y > 13) {
            bugSpawnMap[current->bug_id] = 0;
			current = kill_bug(current->bug_id);
		}
		else {
			current = current->next;
		}
	}
}

Bug* kill_bug(int id) {
	Bug* current = bug_list;
	Bug* prev = NULL;
	
	while (current) {
		if (current->bug_id == id) {
			Bug* temp = current;

			if (prev) {
				prev->next = current->next;
			}
			else {
				bug_list = current->next;
			}
			
			current = current->next;
			free(temp);
            break;
		}
		else {
			prev = current;
			current = current->next;
		}
	}

    return current;
}

void cleanup_bugs(void) { //this function is for cleaning up bugs at the end of the game
	Bug* current = bug_list;
	while (current) {
		Bug* temp = current;
		current = current->next;
		free(temp); //one by one each bug is freed until all memory is returned
	}
	bug_list = NULL; //destroy bug_list pointer
}
