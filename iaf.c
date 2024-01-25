#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "combined.h"

// A function that is called at the start of the program to create an IAF Plane Sprite
int Timer(float time)
{
	// It records the FPS
	static int frames;

	// To negate the effect of FPS
	int value = (int)(time * 60.0);

	// If the fps reaches the time to call it will call this function
	return !(frames++ % (value)) ? 1 : 0;
}

// A function that creates an IAF Plane Sprite
// It will also need to check for all the Potential collisions with IAF Planes
Sprite IAFSpriteGen(Texture2D textures[], Sprite* Sprites[])
{

	// An object with max speed of 100, lowest of 20
	Sprite potentialSpawn = spriteMaker(rand() % 100 + 250, rand() % 650 + 75, 0, textures[rand() % 6]);

	// It is generated at any random place, but between the limits
	// We will also keep on generating it until we arrive at a place where it does not 
	while (genIAFPlaneCollided(Sprites, &potentialSpawn))
		potentialSpawn = spriteMaker(rand() % 100 + 250, rand() % 650 + 75, 0, textures[rand() % 6]);
	return potentialSpawn;
}

// A function that increments the y value of the IAF sprites
void yValueChanger(float* speed, float* y)
{
	*y += *speed / 60;
}

// A function that eliminates an IAF Sprite when it hits the lower wall
// It also takes as argument the pointer to the IAF Sprites list so that we may see are there collisions?
// Collisions with the wall
void isHitChecker(Sprite* spriteToCheck[])
{
	// This for loop will check for all the sprites if they are not null
	for (int i = 0; i < 100; i++)
		if (spriteToCheck[i] != NULL)
			if (hitBoundary(spriteToCheck[i]->posx, spriteToCheck[i]->posy, spriteToCheck[i]->figureDimension) == 4)
				// It has indeed hit the lower boundary so we make it NULL
				spriteToCheck[i] = NULL;
}

// A function that checks for collision with the IAF Planes
int genIAFPlaneCollided(Sprite* IAFSprites[], Sprite* IAFSprite)
{
	// A variable that will check for the collision, and initially set to false
	bool collided = false;

	// Now we will loop over all the sprites that have been generated and are not null
	for (int i = 0; i < 100; i++)
	{
		// We will check only if it is not equal to the actual sprite or is not null
		if (IAFSprites[i] != IAFSprite && IAFSprites[i] != NULL)
		{
			Rectangle pos1 = { IAFSprites[i]->posx,IAFSprites[i]->posy,IAFSprites[i]->figureDimension.width,IAFSprites[i]->figureDimension.height };
			Rectangle pos2 = { IAFSprite->posx,IAFSprite->posy,IAFSprite->figureDimension.width,IAFSprite->figureDimension.height };
			collided = CheckCollisionRecs(pos1,pos2);
			// If collided is one we will return true
			if (collided)
				return 1;
		}
	}

	// Eventually after no collision we we will return 0
	return 0;
}

// Now this is a function to draw all the IAF Planes on the screen
void IAFPlanesDraw(Sprite* IAFSprites[])
{
	// We will loop over all the sprites
	for (int i = 0; i < 100; i++)
		// If the sprites are not equal to NULL we will draw them
		if (IAFSprites[i] != NULL)
			// Now we will draw that texture
			DrawTextureV(IAFSprites[i]->texture, (Vector2) { IAFSprites[i]->posx, IAFSprites[i]->posy }, WHITE);
}

// This is another function that will change the y-coordinate of all the occuring IAF Sprites
void yValueChangerIAFAll(Sprite* IAFSprites[])
{
	// Loop over all the IAF Sprites
	for (int i = 0; i < 100; i++)
		// Check if that is not equal to NULL
		if (IAFSprites[i] != NULL)
			// Change the speed by calling the function
			yValueChanger(&IAFSprites[i]->speed, &IAFSprites[i]->posy);
}

// To free the memory
void freeIAFMemory(Sprite* IAFSprites[])
{
	for (int i = 0; i < 100; i++)
		// We will free only if it is not equal to null
		if (IAFSprites[i] != NULL)
			free(IAFSprites[i]);
}

// Now this function will terminate the game as soon as the PAF Plane hits the IAF Plane
int isGameOver(Sprite* IAFSprites[], Sprite PAFSprite)
{
	// Now to loop over all
	for (int i = 0; i < 100; i++)
	{
		// Check if the sprite is not equal to null
		if (IAFSprites[i] != NULL)
		{
			// Now to check for collision

			// We make the two rectangles
			Rectangle rect1 = { PAFSprite.posx,PAFSprite.posy,PAFSprite.figureDimension.width,PAFSprite.figureDimension.height };
			Rectangle rect2 = { IAFSprites[i]->posx,IAFSprites[i]->posy,IAFSprites[i]->figureDimension.width,IAFSprites[i]->figureDimension.height };

			// Now to check for collision
			if (CheckCollisionRecs(rect1, rect2))
				// Return one if there is collision
				return 1;
		}
	}
	// At the end we know that there is no collision so we return 0
	return 0;
}