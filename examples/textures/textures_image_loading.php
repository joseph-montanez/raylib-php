<?php

require_once __DIR__ . '/../raylib-colors.php';

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

raylib\InitWindow($screenWidth, $screenHeight, "raylib [textures] example - image loading");

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

$image = raylib\LoadImage(__DIR__  . '/resources/raylib_logo.png');     // Loaded in CPU memory (RAM)
$texture = raylib\LoadTextureFromImage($image);                         // Image converted to texture, GPU memory (VRAM)

raylib\UnloadImage($image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

$texture_x = $screenWidth / 2 - raylib\TextureGetWidth($texture) / 2;
$texture_y = $screenHeight / 2 - raylib\TextureGetHeight($texture) / 2;
//---------------------------------------------------------------------------------------

// Main game loop
while (!raylib\WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------


    // Draw
    //----------------------------------------------------------------------------------
    raylib\BeginDrawing();

    raylib\ClearBackground(raylib\RAYWHITE);

    raylib\DrawTexture($texture, $texture_x, $texture_y, raylib\WHITE);

    raylib\DrawText("this IS a texture loaded from an image!", 300, 370, 10, raylib\GRAY);


    raylib\EndDrawing();
    //----------------------------------------------------------------------------------

}

// De-Initialization
//--------------------------------------------------------------------------------------
raylib\CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------