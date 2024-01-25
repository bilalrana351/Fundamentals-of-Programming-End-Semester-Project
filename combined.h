#pragma once
#include "raylib.h"
#include "gameplay.h"


// This is a function that will change the color of a text
Color colorChanger(Color, Color);

// To detect whether cursor is hovering over an area or not
int cursorHovering(Rectangle);

// A function to detect whether the user has clicked a rectangle or not
int clickedRectangle(Rectangle);

// A function that loads in the texture given a path
Texture2D textureLoader(const char*);

// A function that returns a sprite object with the specified values
Sprite spriteMaker(float, float, float, Texture2D);

// A function that changes the coordinates
void isKeyPressed(float*, float*, float*);

// This is a function to determine whether the sprite is touching the side or not
void userPlaneIsTouching(float*, float*, float*, Rectangle);

// This is a function that determines whether a boundary has been hit or not
int hitBoundary(float, float, Rectangle);

// A function to load the PAF planes
Texture2D PAFPlaneLoader(int);

// A function to change the cursor shape when hovering
void mouseChanging(Rectangle);

// To check how the game is over, or is it over at all
int checkHowOver(Sprite* IAFPlanes, Sprite PAFPlane);