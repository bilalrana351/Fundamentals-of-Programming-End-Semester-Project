#pragma once
#include "raylib.h"
#include <stdio.h>
#include "combined.h"
#include "iaf.h"

// To produce the bullets
Sprite bulletProducer(Sprite, Texture2D);

// To change the y-coordinarte
void yChanger(Sprite* bullets[]);

// To change the upper bounds
void upperBoundCheck(Sprite* bullets[]);

// To detect collision of the bullets
void planeBulletCollide(Sprite* bullets[], Sprite* planes[], Sound sound, int* score);

// To draw the bullets
void bulletDrawer(Sprite* bullets[]);

// To change the y value upward
void yValueUp(float*, float*);

// To limit things to one bullet at a time
int bulletToBeFired(void);

// A function to free up the memory allocated to the bullets
void freeBulletMemory(Sprite* bullets[]);