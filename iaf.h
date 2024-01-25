#pragma once
#include "combined.h"
#include "raylib.h"

// A function to call the function to spawn an IAF Sprite
Sprite IAFSpriteGen(Texture2D textures[], Sprite* Sprites[]);

// A function to change the y value of the IAF sprite
void yValueChanger(float*, float*);

// A function to eliminate an IAF Sprite when it hits the wall
void isHitChecker(Sprite*);

// The function to time the time at which the function should be called
int Timer(float);

// A function that increments y values of IAF Sprites
void yValueChanger(float*, float*);

// A function elminating an IAF Sprite when it hits the lower boundary
void isHitChecker(Sprite* spriteToCheck[]);

// A function to determine when two generated PAF Planes collide
int genIAFPlaneCollided(Sprite* IAFSprites[], Sprite*);

// A function to draw the IAF Sprites
void IAFPlanesDraw(Sprite* IAFSprites[]);

// A function to change the y value of all the IAF Planes
void yValueChangerIAFAll(Sprite* IAFSprites[]);

// A function to free up the IAF Memory
void freeIAFMemory(Sprite* IAFSprites[]);

// To check whether the game is over or not
int isGameOver(Sprite* IAFSprites[], Sprite PAFSprite);