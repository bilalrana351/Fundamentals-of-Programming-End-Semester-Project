#include <stdio.h>
#include "raylib.h"
#include "combined.h"
#include "iaf.h"


// Another function that would change the y value but in the neagtive more
void yValueUp(float* speed, float* y)
{
	*y -= *speed / 60;
}

// This is the function to generate a new bullet when user presses space
Sprite bulletProducer(Sprite PlanePosition,Texture2D BulletTexture)
{
	// For the x coordinate of the bullet (to make sure it goes from the center of the plane)
	float x = PlanePosition.posx + PlanePosition.figureDimension.width / 2;

	// For the y coordinate of the bullet
	float y = PlanePosition.posy;
	
	return spriteMaker(200, x, y, BulletTexture);
}

// This function will update the y-coordinate of all the bullets
void yChanger(Sprite* bullets[])
{
	float speed = 200;
	// Loop over all the bullets
	for (int i = 0; i < 120; i++)
		// Check if bullet was equal to NULL, if not change its y value
		if (bullets[i] != NULL)
		{	
			yValueUp(&bullets[i]->speed, &bullets[i]->posy);// Changing the y value of the bullets
		}
}

// This function will check whether the bullets have hit the upper bound or not
// If they have it will automatically make it NULL
void upperBoundCheck(Sprite* bullets[])
{
	// We will loop over the bullets
	for(int i = 0; i < 120; i++)
		// First we will see whether the pointer is not null, only then we would proceed
		if(bullets[i] != NULL)
			// Now to check whether it has hit the boundary
			if (hitBoundary(bullets[i]->posx, bullets[i]->posy, bullets[i]->figureDimension) == 3)
				// It has hit the boundary, so we will make this NULL
				bullets[i] = NULL;
}

// Now to detect the collision between the planes and the bullets, if so we would make this one NULL
void planeBulletCollide(Sprite* bullets[], Sprite* planes[], Sound sound, int* score)
{
	// Loop over bullets
	for (int i = 0; i < 120; i++)
	{
		// Only check if bullets are NULL
		if (bullets[i] != NULL)
		{
			// Loop over the planes now
			for (int j = 0; j < 100; j++)
			{
				// Check if they are equal to null
				if (planes[j] != NULL)
				{
					// Check for their collisions, by making two different rectangles
					Rectangle rectPlane = { planes[j]->posx,planes[j]->posy,planes[j]->figureDimension.width,planes[j]->figureDimension.height };
					
					// For the rectangles of the bullet
					Rectangle rectBullet = { bullets[i]->posx,bullets[i]->posy,bullets[i]->figureDimension.width,bullets[i]->figureDimension.height };

					// Now to check for the collision of the two
					if(CheckCollisionRecs(rectBullet,rectPlane))
					{
						//In case of yes we would make the plane pointer null
						planes[j] = NULL;

						// We will also update the score
						*score += 1;

						// We will also play the sound
						PlaySound(sound);
					}
				}
			}
		}
	}
}

// This is the function that would draw the bullets
void bulletDrawer(Sprite* bullets[])
{
	// Loop over the bullets
	for (int i = 0; i < 120; i++)
	{
		if (bullets[i] != NULL)
		{
			// The vector for the position of the bullet
			Vector2 bulletPost = { bullets[i]->posx,bullets[i]->posy };

			// Lets draw the texture now
			DrawTextureV(bullets[i]->texture, bulletPost, WHITE);
		}
	}
}

// This function will make sure that one bullet is fired per second
int bulletToBeFired(void)
{
	static int clicks;
	if (IsKeyDown(KEY_SPACE))
	{
		clicks++;
		if (!(clicks % 7))
			return 1;
	}
	return 0;
}

// A function to free up the memory of the bullets
void freeBulletMemory(Sprite* bullets[])
{
	for (int i = 0; i < 120; i++)
	{
		// We will deallocate the memory only if it is not equal to NULL
		if (bullets[i] != NULL)
			free(bullets[i]);
	}
}