#include "raylib.h"
#include "combined.h"
#include "gameplay.h"
#include "iaf.h"
#include <stdlib.h>

Color colorChanger(Color color1, Color color2)
{
	static Color curColorValue;
	static int counter;
	static int curColor;
	if (!(counter++ % 60))
		curColorValue = ((curColor++ % 2) ? color1 : color2);
	return curColorValue;
}

// Lets write a conditional to detect whether the cursor is hovering over a specific portion or not
int cursorHovering(Rectangle mouseDimensions)
{
	return ((CheckCollisionPointRec(GetMousePosition(), mouseDimensions)) ? 1 : 0);
}

// I will write a function that detects what rectangle has been clicked by the user
int clickedRectangle(Rectangle rectDimensions)
{
	if (cursorHovering(rectDimensions) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return 1;
	else
		return 0;
}

// Here I am defining a function that loads in a sprite based on its path provided, and returns its texture
Texture2D textureLoader(const char* path)
{
	// Load the image of the texture
	Image image = LoadImage(path);

	// Load the texture
	Texture2D texture = LoadTextureFromImage(image);

	// Now unload the image, we do not need it anymore
	UnloadImage(image);

	// Lets return the texture
	return texture;
}

// Now lets define a function that creates the object (so to speak) of the sprite mentioned
Sprite spriteMaker(float initialVelocity, float initialX, float initialY, Texture2D texture)
{
	// Declare the sprite
	Sprite sprite;

	// Declare its x position
	sprite.posx = initialX;

	// Declare its y position
	sprite.posy = initialY;

	// Declare its speed
	sprite.speed = initialVelocity;

	// Declare its position
	sprite.texture = texture;

	// Make the dimensions of the figure
	sprite.figureDimension = (Rectangle){ 0,0,texture.width,texture.height };

	// Return the sprite
	return sprite;
}

// Now I will write a function that will be called to check whether a key is being pressed or not
// This will be used to determine which coordinates will change
// I will pass the value by reference so that any change is reflected in the variable
void isKeyPressed(float* x, float* y, float* velocity)
{
	// Now to detect whether the left key is pressed or not 
	*x -= (IsKeyDown(KEY_LEFT)) ? *velocity / 20 : 0;

	// Now to detect whether the right key is pressed or not
	*x += (IsKeyDown(KEY_RIGHT)) ? *velocity / 20 : 0;

	// Now to detect whether the up key is pressed or not
	*y -= (IsKeyDown(KEY_UP)) ? *velocity / 20 : 0;

	// Now to detect whether the down key is pressed or not
	*y += (IsKeyDown(KEY_DOWN)) ? *velocity / 20 : 0;
}

// Now I will write a function that detects whether the plane is colliding with the boundaries or not
// The function will not return anything just see whether the plane is touching the boundary or not
// The x,y are positions of the plane at that time, and the rectangle dimensions of the plane
void userPlaneIsTouching(float* x, float* y, float* velocity,Rectangle rectangle)
{
	// Sees the type of boundary hit
	int whichBoundaryHit = hitBoundary(*x, *y, rectangle);

	// First I want to check whether the x position is less than or equal to zero
	// If so I will make it 10
	*x += (whichBoundaryHit == 1) ? *velocity/20 : 0;

	// Now, if the x position plus its dimensio5n is touching the screen dimension(which is 800 in this case)
	// I will make it 720
	*x -= (whichBoundaryHit == 2) ? *velocity/20 : 0;

	// Now if the y position is less than zero I will make it 10
	*y += (whichBoundaryHit == 3) ? *velocity/20 : 0;

	// Now if the y position plus the dimension is touching the screen dimension(which is 450 in this case)
	// I will decrease the x coordinate
	*y -= (whichBoundaryHit == 4) ? *velocity/20 : 0;
}

// This is another function which will probably not be used in the program but can be used to determine whether something has hit a boundary
int hitBoundary(float x, float y, Rectangle rectangle)
{
	// Checks whether the left boundary is hit
	if (0 >= x)
		return 1;
	
	// Checks whether the right boundary is hit
	else if (x + rectangle.width>= 800)
		return 2;

	// Checks whether the upper boundary is hit
	else if (y <= 0)
		return 3;

	// Checks whether the lower boundary is hit
	else if (y + rectangle.height >= 450)
		return 4;

	// Returns 0 if no boundary is hit
	else
		return 0;
}

//------------------------------------------------------------------------------------------------------------
// This is a function that takes as argument the integer value returned by the second loading screen
// It then processes that integer value so as to decide which sprite it should load
Texture2D PAFPlaneLoader(int prevValue)
{
	// We use a switch case to decide which image to load
	switch (prevValue)
	{
		// We will open the JF-17 Sprite
	case 1:
		return textureLoader("Sprites/PAFPlanes/Top/JF17ThunderTop.png");

		// We will open the J10C Sprite
	case 2:
		return textureLoader("Sprites/PAFPlanes/Top/J10CTop.png");

		// We will open the F7PG Sprite
	case 3:
		return textureLoader("Sprites/PAFPlanes/Top/F7PGTop.png");

		// We will open the F16 Sprite
	case 4:
		return textureLoader("Sprites/PAFPlanes/Top/F16Top.png");

		// We will open the Mirage 5 Sprite
	case 5:
		return textureLoader("Sprites/PAFPlanes/Top/Mirage5Top.png");
	}
}

// Function to change the Mouse cursor when hovering over a place
void mouseChanging(Rectangle rectangle)
{
	SetMouseCursor(cursorHovering(rectangle) ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);
}

// To check whether the game is over or not
int checkHowOver(Sprite* IAFPlanes, Sprite PAFPlane)
{
	// If this block is executed it means that the window has not been closed and game is not over
	if (!WindowShouldClose() && !isGameOver(IAFPlanes, PAFPlane))
		return 0;
	// This block means that the window was not closed but the game was over by the usual means
	else if (!WindowShouldClose())
		return 1;
	// This block means that the game is still going on but the user has closed the window
	else
		return 2;
}