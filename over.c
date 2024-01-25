#include <stdio.h>
#include "raylib.h"
#include "combined.h"

// Now this is the main function for the program
// It will run in a while loop and will initially be set to true
// It will ask the user whether he wants to replay, go back to main menu, or quit
// So it will return an integer
int promptUser(void)
{
	// Lets make a string of text and measure their widths and store them in a variable
	// We will use this variable to check for the collision of the mouse with the text
	char textValues[3][50] = {
		"1. Continue",
		"2. Go to Main Menu",
		"3. Exit"
	};


	// A variable to store the text width
	int textWidths[3];

	// Now to run a for loop in order to store the value of the text
	for (int i = 0; i < 3; i++)
		textWidths[i] = MeasureText(textValues[i], 20);

	while (!WindowShouldClose())
	{
		// We will make the mouse cursor the default one
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		// We will run a for loop to see whether the cursor is moving over the mouse positions or not 
		for (int i = 0; i < 3; i++)
		{
			// The rectangle to detect
			Rectangle rectText = { 325, 50 * (i + 3), textWidths[i], 20 };

			if (cursorHovering(rectText))
			{
				// If the user is hovering over the text we will make the cursor a pointing hand
				SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

				// Now to check whether the user has clicked the specific text he is hovering over
				if (clickedRectangle(rectText))
					// I chose 2 - i here because when user presses the 3rd the program should return 0
					return  (2 - i);
				// The program will return 1 for going to main menu else it will return 2
			}
		}
		// First we will draw the picture
		BeginDrawing();

		// Now we will clear the background to black
		ClearBackground(BLACK);

		// Now we will draw the text we want to display
		DrawText("GAME OVER!", 300, 100, 25, colorChanger(WHITE, RED));

		// Now we would give the user the options
		DrawText("1. Continue", 325, 150, 20, RED);
		DrawText("2. Go to Main Menu", 325, 200, 20, RED);
		DrawText("3. Exit", 325, 250, 20, RED);

		// Now we would finish the drawing
		EndDrawing();
	}
	// Now that the user has closed the window we will return 0
	return 0;
}