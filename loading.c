#include "raylib.h"
#include "combined.h"
#include <stdlib.h>

// This is the function that will deal with the loading screen
// It does not return anything it is a void function
void loadingScreen(void)
{
	// This is the loading of the texture
	Texture2D firstTexture = textureLoader("Sprites/Screens/FirstScreen.png");

	// We will load the music here
	Music music = LoadMusicStream("Sounds/BackgroundSound/loadingBackgroundSound.mp3");

	// Lets play the music
	PlayMusicStream(music);

	// Until the user has pressed the enter key, we will continue to display the screen
	while(!IsKeyDown(KEY_ENTER))
	{
		// Lets update the music
		UpdateMusicStream(music);

		// Lets load the frames of the image
		BeginDrawing();

		// Clear the background
		ClearBackground(RAYWHITE);

		// Lets draw the main texture of the window
		DrawTexture(firstTexture, 0, 0, RAYWHITE);

		// The text for the credits for the program
		DrawText("Special Thanks to", 600, 20, 20, RED);
		DrawText("Sir Dr. Jaudat Mamoon", 560, 50, 20, RED);
		DrawText("Engr. Sir Aftab Farooq", 560, 80, 20,RED);


		// Lets render the text prompt for the user
		// We also call the colorChanger Function in the arguments to this function
		DrawText("Press Enter to start", 250, 350, 25, colorChanger(RED,BLACK));

		// End the drawing
		EndDrawing();
	}

	// Lets unload the music
	UnloadMusicStream(music);

	// Lets unload the texture
	UnloadTexture(firstTexture);
}