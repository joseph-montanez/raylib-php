<?php

/*******************************************************************************************
*
*   raylib [audio] example - Sound loading and playing
*
*   Example originally created with raylib 1.1, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

use raylib\Color;
use const raylib\KeyboardKey\KEY_SPACE;
use const raylib\KeyboardKey\KEY_ENTER;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

InitWindow($screenWidth, $screenHeight, 'raylib [audio] example - sound loading and playing');

InitAudioDevice();                  // Initialize audio device

$fxWav = LoadSound(__DIR__ . '/resources/sound.wav');         // Load WAV audio file
$fxOgg = LoadSound(__DIR__ . '/resources/target.ogg');        // Load OGG audio file

$raywhite = Color::RAYWHITE();
$lightgray = Color::LIGHTGRAY();

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_SPACE)) PlaySound($fxWav);      // Play WAV sound
    if (IsKeyPressed(KEY_ENTER)) PlaySound($fxOgg);      // Play OGG sound
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground($raywhite);

        DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, $lightgray);
        DrawText("Press ENTER to PLAY the OGG sound!", 200, 220, 20, $lightgray);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadSound($fxWav);     // Unload sound data
UnloadSound($fxOgg);     // Unload sound data

CloseAudioDevice();     // Close audio device

CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

CloseWindow();          // Close window and OpenGL context
//--------------------------------------------------------------------------------------
