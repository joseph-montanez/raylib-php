<?php

/*******************************************************************************************
*
*   raylib [textures] example - Bunnymark
*
*   Example originally created with raylib 1.6, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

use raylib\Color;
use raylib\Vector2;
use const raylib\MouseButton\MOUSE_BUTTON_LEFT;

const MAX_BUNNIES = 50000;    // 50K bunnies limit

// This is the maximum amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
const MAX_BATCH_ELEMENTS =  8192; // Not supported in PHP

class Bunny {
    public null|Vector2 $position;
    public null|Color $color;

    public function __construct(public Vector2 $speed) {
    }
}

$screenWidth = 800;
$screenHeight = 450;

$maroon = Color::MAROON();
$green = Color::GREEN();
$black = Color::BLACK();
$ray_white = Color::RAYWHITE();

InitWindow($screenWidth, $screenHeight, "raylib [textures] example - bunnymark");

// Load bunny texture
$texBunny = LoadTexture(__DIR__ . '/resources/wabbit_alpha.png');

/** @var Bunny[] $bunnies */
$bunnies = [];    // Bunnies array
for ($i = 0; $i < MAX_BUNNIES; $i++) {
    $bunnies[] = new Bunny(new Vector2());
}

$bunniesCount = 0;           // Bunnies counter

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose()) {    // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // Create more bunnies
        for ($i = 0; $i < 100; $i++) {
            if ($bunniesCount < MAX_BUNNIES)
            {
                $bunnies[$bunniesCount]->position = GetMousePosition();
                $bunnies[$bunniesCount]->speed->x = (float)rand(-250, 250)/60.0;
                $bunnies[$bunniesCount]->speed->y = (float)rand(-250, 250)/60.0;
                $bunnies[$bunniesCount]->color = new Color(rand(50, 240), rand(80, 240), rand(100, 240), 255);
                $bunniesCount++;
            }
        }
    }

    // Update bunnies
    for ($i = 0; $i < $bunniesCount; $i++)
    {
        $bunnies[$i]->position->x += $bunnies[$i]->speed->x;
        $bunnies[$i]->position->y += $bunnies[$i]->speed->y;

        if ((($bunnies[$i]->position->x + $texBunny->width/2) > GetScreenWidth()) ||
            (($bunnies[$i]->position->x + $texBunny->width/2) < 0)) $bunnies[$i]->speed->x *= -1;
        if ((($bunnies[$i]->position->y + $texBunny->height/2) > GetScreenHeight()) ||
            (($bunnies[$i]->position->y + $texBunny->height/2 - 40) < 0)) $bunnies[$i]->speed->y *= -1;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground($ray_white);

        for ($i = 0; $i < $bunniesCount; $i++)
        {
            // NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
            // a draw call is launched and buffer starts being filled again;
            // before issuing a draw call, updated vertex data from internal CPU buffer is send to GPU...
            // Process of sending data is costly and it could happen that GPU data has not been completely
            // processed for drawing while new data is tried to be sent (updating current in-use buffers)
            // it could generates a stall and consequently a frame drop, limiting the number of drawn bunnies
            DrawTexture($texBunny, (int) $bunnies[$i]->position->x, (int) $bunnies[$i]->position->y, $bunnies[$i]->color);
        }

        DrawRectangle(0, 0, $screenWidth, 40, $black);
        DrawText(sprintf("bunnies: %d", $bunniesCount), 120, 10, 20, $green);
        DrawText(sprintf("batched draw calls: %d", 1 + $bunniesCount/MAX_BATCH_ELEMENTS), 320, 10, 20, $maroon);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
unset($bunnies);              // Unload bunnies data array

UnloadTexture($texBunny);    // Unload bunny texture

CloseWindow();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------
