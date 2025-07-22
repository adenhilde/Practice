game: main.o player.o input.o bug.o bullet.o enemyBullet.o log.o Score.o
	gcc main.o player.o input.o bug.o bullet.o enemyBullet.o log.o Score.o -o game -lpthread

main.o: main.c player.h input.h bug.h bullet.h enemyBullet.h log.h Score.h
	gcc -c main.c

player.o: player.c player.h
	gcc -c player.c

input.o: input.c input.h
	gcc -c input.c

bug.o: bug.c bug.h
	gcc -c bug.c

bullet.o: bullet.c bullet.h bug.h
	gcc -c bullet.c

enemyBullet.o: enemyBullet.c enemyBullet.h
	gcc -c enemyBullet.c

log.o: log.c log.h
	gcc -c log.c

Score.o: Score.c Score.h
	gcc -c Score.c

gameDB: main.c player.c input.c bug.c bullet.c enemyBullet.c log.c Score.c
	gcc -Wall -g main.c player.c input.c bug.c bullet.c enemyBullet.c log.c Score.c -o gameDB -lpthread -lmcheck

clean:
	rm -i *.o game

clear:
	rm *.o game gameDB
