#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "loading.h"
#include "choice.h"
#include "gameplay.h"
#include "iaf.h"
#include "over.h"
#include <time.h>

// This is the start of the main function
int main()
{
	// This is the screen width maintained to 800 pixels
	const int screenWidth = 800;

	// This is the screen height maintained to 450 pixels
	const int screenHeight = 450;

	// This is the start of the window
	InitWindow(screenWidth, screenHeight, "Game Window");

	// We will also load the audio
	InitAudioDevice();

	// This is the target FPS for the Whole Game, I have done it equal to 60
	SetTargetFPS(60);
	
	// This is the rendering for the first screen, it stops as soon as you press enter
	loadingScreen();

	// This will randomize the seed function
	srand(time(NULL));

	// This is a while loop, I will break it based on specific values
	while (1)
	{
		// Now after this we write code for the rendering of the second screen
		int secondScreenVal = secondImage();

		// This is the variable that will record whether the game was closed by the usual means or window was closed
		// By default it is set to 1
		int howGameClosed = 1;

		// This is the variable that will store what the user wants after game is over
		// Initially it is set to 2, because 2 means try again
		int userChoice = 2;

		// In case the second screen does return some value other than zero we would apss it as argument to the third function
		// Else we would not execute this block
		if (secondScreenVal)
		{
			while (userChoice != 1)
			{
				// A one here shows that the game was over by usual means and 2 means it was done by closing the window
				howGameClosed = thirdWindowMain(secondScreenVal);
		
				// If it is equal to 2 we will return the program
				if (howGameClosed == 2)
				{
					CloseAudioDevice();
					CloseWindow();
					return 0;
				}
				else
				{
					// Else we will prompt the user to give his response
					userChoice = promptUser();

					// If he enters 0 we will return 0 to the program
					if (!userChoice)
					{
						CloseAudioDevice();
						CloseWindow();
						return 0;
					}
				}
			}
		}
		// User closed the window so we return 0
		else
		{
			CloseAudioDevice();
			CloseWindow();
			return 0;
		}
	}
}