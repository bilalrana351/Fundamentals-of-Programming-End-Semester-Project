#include "choice.h"
#include "raylib.h"
#include "combined.h"

// This is the header file that will deal with the chocies thing

// Lets define the second image renderer function
// This function will return 0 if the user does not click anything and closed the window itself
// Else this fucntion can return 1,2,3,4,5,6 depending upon whcih sprite the user clicked
int secondImage(void)
{
	// Lets load the textures into the GPU memory
	Texture2D texture = textureLoader("Sprites/Screens/secondScreenTest.png");

	// Lets write the code to intitalize the upper rectangles
	Rectangle upperRectangles[5];

	// Now for the lower rectangles
	Rectangle lowerRectangles[5];

	// Lets load the music
	Music music = LoadMusicStream("Sounds/BackgroundSound/loadingBackgroundSound.mp3");

	// Lets play the music
	PlayMusicStream(music);

	for (int i = 0; i < 5; i++)
	{
		upperRectangles[i].x = i * 150 + 25;
		upperRectangles[i].y = 200;
		upperRectangles[i].width = 150;
		upperRectangles[i].height = 120;
		lowerRectangles[i].x = i * 150 + 25;
		lowerRectangles[i].y = 320;
		lowerRectangles[i].width = 150;
		lowerRectangles[i].height = 90;
	}

	// When we start the second screen it automatically selects the value based on the previous mouse click
	// This is a variable that will make sure that the input is check only after the first second of loading
	int buffer = 0;

	// Now for the actual rendering, we will stop if the user presses on the desired part
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		// We want to check whether the cursor is hovering over the combined rectangle so we pass in coordinates of the combined rectangle
		Rectangle combinedRectangle = { 25,200,750,210 };

		// Now lets change the cursor style to a pointer if the user hovers over the rectangles
		mouseChanging(combinedRectangle);

		// We will check only when the buffer has reached 60
		if (buffer++ > 60)
		{
			// Lets run a loop to determine if a recta5ngle has been clicked by the user
			for (int i = 0; i < 5; i++)
			{
				// Check if user has clicked that rectangle or not
				if (clickedRectangle(upperRectangles[i]) || clickedRectangle(lowerRectangles[i]))
				{
					// Lets unload the music
					UnloadMusicStream(music);

					// Lets unload the texture
					UnloadTexture(texture);

					// Return the sprite number that was clicked
					return i + 1;
				}
			}
		}

		// Lets begin drawing
		BeginDrawing();

		// Lets clear the background
		ClearBackground(RAYWHITE);

		// For the texture
		DrawTexture(texture, 0, 0, WHITE);

		// Lets Write the Text for the GUI
		DrawText("Select your plane and hop on!", 250, 100, 20, colorChanger(RED, WHITE));

		// To print the rectangles, we only need their borders
		for (int i = 0; i < 5; i++)
		{
			DrawRectangleLinesEx(upperRectangles[i], 2, RED);
			DrawRectangleLinesEx(lowerRectangles[i], 2, RED);
		}

		// Lets end the drawing
		EndDrawing();
	}

	UnloadMusicStream(music);

	// This is the end of this frame if the user does not click on any sprite
	// So we unload the texture
	UnloadTexture(texture);

	// Now we return 0
	return 0;
}