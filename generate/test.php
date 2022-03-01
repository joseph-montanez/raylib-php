<?php

use raylib\Color;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;

$lightGray    = new Color(245, 245, 245, 255);
//-- Constructors not yet implemented
$lightGray->r = 245;
$lightGray->g = 245;
$lightGray->b = 245;
$lightGray->a = 255;

$gray         = new Color(200, 200, 200, 255);
//-- Constructors not yet implemented
$gray->r = 200;
$gray->g = 200;
$gray->b = 200;
$gray->a = 255;

InitWindow($screenWidth, $screenHeight, "raylib [core] example - basic window");

SetTargetFPS(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground($lightGray);

    DrawText("Congrats! You created your first window!", 190, 200, 20, $gray);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------