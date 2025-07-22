#ifndef BUG_H
#define BUG_H

typedef struct Bug {
	int x;
	int y;
	int bug_id;
	int bug_spawn;
	int bug_fly_pattern;
	int bug_spawn_counter;
	int stage;
	int bug_alive;
	struct Bug* next;
} Bug;

extern Bug* bug_list; // Linked list header

extern int startingPositionX[];
extern int startingPositionY[];
extern int bugPathX1[];
extern int bugPathY1[];
extern int bugPathX2[];
extern int bugPathY2[];

void initializeRandomSeed();
void spawn_bug(int id);
void move_bugs(int x, int* bugSpawnMap);
Bug* kill_bug(int id);
void cleanup_bugs(void);

#endif
