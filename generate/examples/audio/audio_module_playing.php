<?php

/*******************************************************************************************
 *
 *   raylib [audio] example - Module playing (streaming)
 *
 *   This example has been created using raylib 1.5 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2016 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

use raylib\Color;
use raylib\Vector2;
use const raylib\ConfigFlags\FLAG_MSAA_4X_HINT;
use const raylib\KeyboardKey\KEY_DOWN;
use const raylib\KeyboardKey\KEY_P;
use const raylib\KeyboardKey\KEY_SPACE;
use const raylib\KeyboardKey\KEY_UP;

const MAX_CIRCLES = 64;

class CircleWave {
    public Vector2 $position;
    public float $radius;
    public float $alpha;
    public float $speed;
    public Color $color;
}


// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

SetConfigFlags(FLAG_MSAA_4X_HINT);  // NOTE: Try to enable MSAA 4X

InitWindow($screenWidth, $screenHeight, "raylib [audio] example - module playing (streaming)");

InitAudioDevice();                  // Initialize audio device

/** @var Color[] $colors */
$colors = [Color::ORANGE(), Color::RED(), Color::GOLD(), Color::LIME(), Color::BLUE(), Color::VIOLET(), Color::BROWN(), Color::LIGHTGRAY(), Color::PINK(),
           Color::YELLOW(), Color::GREEN(), Color::SKYBLUE(), Color::PURPLE(), Color::BEIGE()];

// Creates ome circles for visual effect
/** @var CircleWave[] $circles */
$circles = [];

for ($i = MAX_CIRCLES - 1; $i >= 0; $i--)
{
    $circles[$i] = new CircleWave();
    $circles[$i]->position = new Vector2();

    $circles[$i]->alpha = 0.0;
    $circles[$i]->radius = (float)rand(10, 40);
    $circles[$i]->position->x = (float)rand((int)$circles[$i]->radius, (int)($screenWidth - $circles[$i]->radius));
    $circles[$i]->position->y = (float)rand((int)$circles[$i]->radius, (int)($screenHeight - $circles[$i]->radius));
    $circles[$i]->speed = (float)rand(1, 100)/2000.0;
    $circles[$i]->color = $colors[rand(0, 13)];
}

$music = LoadMusicStream(__DIR__ . '/resources/mini1111.xm');
$music->looping = false;
$pitch = 1.0;

PlayMusicStream($music);

$timePlayed = 0.0;
$pause = false;

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream($music);      // Update music buffer with new stream data

    // Restart music playing (stop and play)
    if (IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream($music);
        PlayMusicStream($music);
    }

    // Pause/Resume music playing
    if (IsKeyPressed(KEY_P))
    {
        $pause = !$pause;

        if ($pause) PauseMusicStream($music);
        else ResumeMusicStream($music);
    }

    if (IsKeyDown(KEY_DOWN)) $pitch -= 0.01;
    else if (IsKeyDown(KEY_UP)) $pitch += 0.01;

    SetMusicPitch($music, $pitch);

    // Get timePlayed scaled to bar dimensions
    $timePlayed = GetMusicTimePlayed($music)/GetMusicTimeLength($music)*($screenWidth - 40);

    // Color circles animation
    for ($i = MAX_CIRCLES - 1; ($i >= 0) && !$pause; $i--)
    {
        $circles[$i]->alpha += $circles[$i]->speed;
        $circles[$i]->radius += $circles[$i]->speed*10.0;

        if ($circles[$i]->alpha > 1.0) $circles[$i]->speed *= -1;

        if ($circles[$i]->alpha <= 0.0)
        {
            $circles[$i]->alpha = 0.0;
            $circles[$i]->radius = (float)rand(10, 40);
            $circles[$i]->position->x = (float)rand((int)$circles[$i]->radius, (int)($screenWidth - $circles[$i]->radius));
            $circles[$i]->position->y = (float)rand((int)$circles[$i]->radius, (int)($screenHeight - $circles[$i]->radius));
            $circles[$i]->color = $colors[rand(0, 13)];
            $circles[$i]->speed = (float)rand(1, 100)/2000.0;
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(Color::RAYWHITE());

        for ($i = MAX_CIRCLES - 1; $i >= 0; $i--)
        {
            DrawCircleV($circles[$i]->position, $circles[$i]->radius, Fade($circles[$i]->color, $circles[$i]->alpha));
        }

        // Draw time bar
        DrawRectangle(20, $screenHeight - 20 - 12, $screenWidth - 40, 12, Color::LIGHTGRAY());
        DrawRectangle(20, $screenHeight - 20 - 12, (int)$timePlayed, 12, Color::MAROON());
        DrawRectangleLines(20, $screenHeight - 20 - 12, $screenWidth - 40, 12, Color::GRAY());

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadMusicStream($music);          // Unload music stream buffers from RAM

CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

CloseWindow();          // Close window and OpenGL context
//--------------------------------------------------------------------------------------
