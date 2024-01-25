#pragma once
#include "raylib.h"

// This is the header file for the main gameplay of the game, that is, the main game

// Here I will make a struct that holds the texture of a sprite, its vector position, its velocity,and the size of the texture
typedef struct
{
	// X Position
	float posx;

	// Y Position
	float posy;

	// The speed, we will change the x and y coordinates on the basis of this attribute
	float speed;

	// For the texture, we will take as argument the loaded texture, so that we can draw it
	Texture texture;

	// Now we will also Take in the area of the rectangle as the argument
	Rectangle figureDimension;
}Sprite; // We have named the struct as sprite

// The main function of the window
int thirdWindowMain(int);