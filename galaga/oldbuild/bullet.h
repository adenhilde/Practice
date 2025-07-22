// Addison Miranda

#ifndef BULLET_H
#define BULLET_H

typedef struct Bullet {
	int x;
	int y;
	int contact;
	struct Bullet* next;
} Bullet;

extern Bullet* bullet_list; // Linked list header

void fire_bullet(int x, int y);
void move_bullets(void);
void cleanup_bullets(void);

#endif
