// Including the necessary libraries
#include "raylib.h"
#include "combined.h"
#include "iaf.h"
#include "bullets.h"
#include <stdlib.h>

// --------------------------------------------------------------------------------------------------
// This is the main display for the 3rd image
// This will return an integer, to show how the game ended
int thirdWindowMain(int prevValue)
{
	// This variable will keep track of the score
	int score = 0;

	// Lets Load the Music for the hit
	Sound hitSound = LoadSound("Sounds/ScoringSound/Scoring.mp3");
	
	// Texture of the main image
	Texture2D mainTexture = textureLoader("Sprites/Screens/thirdScreen.png");

	// Now lets make the sprite for the specified PAF Plane, and load its texture with the PAFPlaneLoader Function
	Sprite PAFPlane = spriteMaker(75, 200, 200, PAFPlaneLoader(prevValue));

	// Lets make a list of IAF Textures that we want to load
	Texture2D IAFTextures[6];

	// Lets make a list of IAF Planes Paths that we want to load
	const char path[6][50] = {
		"Sprites/IAFPlanes/Top/JaguarTop.png",
		"Sprites/IAFPlanes/Top/Mig21Top.png",
		"Sprites/IAFPlanes/Top/Mirage2000Top.png",
		"Sprites/IAFPlanes/Top/RafaleTop.png",
		"Sprites/IAFPlanes/Top/SU30MKITop.png",
		"Sprites/IAFPlanes/Top/TejasTop.png"
	};

	// Now to unload all the paths and assign the value to a sprite
	for (int i = 0; i < 6; i++)
		IAFTextures[i] = textureLoader(path[i]);

	// This will be an IAF Sprites Values
	Sprite* indianSprites[100];

	// Initialize the values with NULL
	for (int i = 0; i < 100; i++)
		indianSprites[i] = NULL;

	// Now we will keep a counter that will be updated everytime a new sprite is generated
	int planeSpriteNo = 0;

	// Now to unload the bullet texture
	Texture2D BulletTexture = textureLoader("Sprites/Bullets/Bullet.png");

	// Declare the bullets sprite
	Sprite* bullets[120];

	// Initialize this to NULL
	for (int i = 0; i < 120; i++)
		bullets[i] = NULL;

	// This is a counter that will be updated everytime a bullet is generated
	int bulletNo = 0;

	// Now for the main window
	// Currently I have made it like this but it can be changed to include a different condition for termination
	// Maybe like a fatal crash between two enemy planes or a bullet from the enemy
	while (!checkHowOver(indianSprites,PAFPlane))
	{
		// Here we will load an indian sprite after the specified time
		if (Timer(1)) {
			// Lets allocate the memory for the indian sprites (if memory at that time is not null)
			if (indianSprites[planeSpriteNo % 100] == NULL)
				indianSprites[planeSpriteNo % 100] = malloc(sizeof(Sprite));

			// Lets store the value returned by this function in the instance of indianSprites
			*indianSprites[planeSpriteNo % 100] = IAFSpriteGen(IAFTextures,indianSprites);

			// Lets increment the sprite number
			planeSpriteNo++;
		}

		// This function will load an bullet when the user presses space
		if (bulletToBeFired()) {
			// We will allocate new memory only if the bullet at that time is NULL
			if (bullets[bulletNo % 120] == NULL)
				bullets[bulletNo % 120] = malloc(sizeof(Sprite));

			// Now we will generate a new sprite
			*bullets[bulletNo % 120] = bulletProducer(PAFPlane, BulletTexture);

			// Lets increment the bullet number
			bulletNo++;
		}
		
		// This function will now increase the value of the IAF Sprites' y coordinate
		yValueChangerIAFAll(indianSprites);

		// This function will check for hits on the IAF Planes
		isHitChecker(indianSprites);

		// This function will increase y values of the bullets
		yChanger(bullets);

		// This function will check the hit status of the bullet
		upperBoundCheck(bullets);

		// I will now call the function that will determine which key is pressed and change the x and y value respectively
		isKeyPressed(&PAFPlane.posx, &PAFPlane.posy, &PAFPlane.speed);

		// After this I will see whether the sprite is touching the side or not
		userPlaneIsTouching(&PAFPlane.posx, &PAFPlane.posy, &PAFPlane.speed, PAFPlane.figureDimension);

		// Now to check the state of the collision of the plane and bulley
		planeBulletCollide(bullets, indianSprites,hitSound,&score);

		// Lets write the score on the side
		// We declare a variable to store the value
		char scoreStr[32];

		// To plugin the variable
		sprintf_s(scoreStr, sizeof(scoreStr), "Score %d", score);

		// Begin the drawing process
		BeginDrawing();

		// Clear the previous background
		ClearBackground(RAYWHITE);

		// Draw the main texture
		DrawTexture(mainTexture, 0, 0, WHITE);

		// Draw the PAF Plane Sprite
		DrawTextureV(PAFPlane.texture, (Vector2) { PAFPlane.posx, PAFPlane.posy }, WHITE);

		// Now lets draw the IAF Planes
		IAFPlanesDraw(indianSprites);

		// Lets draw the bullets
		bulletDrawer(bullets);

		// Now we will draw the text
		DrawText(scoreStr, 700, 100, 20, RED);
				
		// End the Drawing
		EndDrawing();
	}

	// We will store the value of the way the game ended in another variable
	// The function is called her as we are going to free the sprites below
	int howGameEnded = checkHowOver(indianSprites, PAFPlane);

	// Unload the textures
	UnloadTexture(PAFPlane.texture);
	UnloadTexture(mainTexture);
	UnloadTexture(BulletTexture);
	for (int i = 0; i < 6; i++)
		UnloadTexture(IAFTextures[i]);

	// Now lets also free the memory that we allocated at the start
	freeBulletMemory(bullets);
	freeIAFMemory(indianSprites);

	// Remember to close the audio files and the textures that you laoded here after the loop
	// Unload the audiofile
	UnloadSound(hitSound);

	// Return the value of how the game ended
	return howGameEnded;
}