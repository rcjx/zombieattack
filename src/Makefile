OBJS = Object.o SpatialHash.o Bullet.o Entity.o Enemy.o Player.o Main.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -lsfml-audio -lsfml-graphics -lsfml-system -I../include
LFLAGS = -Wall $(DEBUG) -lsfml-audio -lsfml-graphics -lsfml-system -I../include

SHELL = /bin/sh

.SUFFIXES: 
.SUFFIXES: .cc .cpp .h .o

zombie.bin : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o zombie.bin

Object.o : Object.cpp 
	$(CC) $(CFLAGS) Object.cpp

SpatialHash.o : SpatialHash.cpp 
	$(CC) $(CFLAGS) SpatialHash.cpp

Bullet.o : Bullet.cpp 
	$(CC) $(CFLAGS) Bullet.cpp

Entity.o : Entity.cpp 
	$(CC) $(CFLAGS) Entity.cpp

Enemy.o : Enemy.cpp 
	$(CC) $(CFLAGS) Enemy.cpp

Player.o : Player.cpp 
	$(CC) $(CFLAGS) Player.cpp

Main.o : Main.cc 
	$(CC) $(CFLAGS) Main.cc

clean:
	rm *.o *.bin
