// Addison Miranda

#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

typedef struct enemyBullet {
	int x;
	int y;
	struct enemyBullet* next;
} enemyBullet;

extern enemyBullet* enemyBullet_list; // Linked list header

void fire_enemyBullet(int x, int y);
void move_enemyBullets(void);
void cleanup_enemyBullets(void);

#endif
