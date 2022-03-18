<?php

/*******************************************************************************************
 *
 *   raylib [core] example - 3d camera first person
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/


use raylib\Camera3D;
use raylib\Color;
use raylib\Vector2;
use raylib\Vector3;
use const raylib\CameraMode\CAMERA_FIRST_PERSON;
use const raylib\CameraProjection\CAMERA_PERSPECTIVE;

const MAX_COLUMNS = 20;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;
$black = Color::BLACK();
$dark_gray = Color::DARKGRAY();
$blue = Color::BLUE();
$sky_blue = Color::SKYBLUE();
$light_gray = Color::LIGHTGRAY();
$lime = Color::LIME();
$ray_white = Color::RAYWHITE();
$gold = Color::GOLD();
$maroon = Color::MAROON();

InitWindow($screenWidth, $screenHeight, "raylib [core] example - 3d camera first person");

// Define the camera to look into our 3d world (position, target, up vector)
$position = new Vector3(4.0, 2.0, 4.0);
$target = new Vector3(0.0, 1.8, 0.0);
$up = new Vector3(0.0, 1.0, 0.0);
$fovy = 60.0;
$projection = CAMERA_PERSPECTIVE;
$camera = new Camera3D($position, $target, $up, $fovy, $projection);

// Generates some random columns
/** @var float[] $heights */
$heights   = [];
/** @var \raylib\Vector3[] $positions */
$positions = [];
/** @var \raylib\Color[] $colors */
$colors = [];

for ($i = 0; $i < MAX_COLUMNS; $i++)
{
    $heights[$i] = (float)GetRandomValue(1, 12);
    $positions[$i] = new Vector3 ((float)GetRandomValue(-15, 15), $heights[$i]/2.0, (float)GetRandomValue(-15, 15));
    printf("0: \$positions[\$i] %f, %f, %f\n", $positions[$i]->x, $positions[$i]->y, $positions[$i]->z);
    $colors[$i] = new Color(GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255);

}

SetCameraMode($camera, CAMERA_FIRST_PERSON); // Set a first person camera mode

SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

$centerPos = new Vector3(0.0, 0.0, 0.0);
$size = new Vector2(32.0, 32.0);
$position = new Vector3(-16.0, 2.5, 0.0);
$position1 = new Vector3(16.0, 2.5, 0.0);
$position2 = new Vector3(0.0, 2.5, 16.0);
// Main game loop
while (!WindowShouldClose())                // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera($camera);                  // Update camera
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground($ray_white);

        BeginMode3D($camera);

            DrawPlane($centerPos, $size, $light_gray);                                  // Draw ground
            DrawCube($position, 1.0, 5.0, 32.0, $blue);                                 // Draw a blue wall
            DrawCube($position1, 1.0, 5.0, 32.0, $lime);                                // Draw a green wall
            DrawCube($position2, 32.0, 5.0, 1.0, $gold);                                // Draw a yellow wall

            // Draw some cubes around
            for ($i = 0; $i < MAX_COLUMNS; $i++)
            {
                DrawCube($positions[$i], 2.0, $heights[$i], 2.0, $colors[$i]);
                DrawCubeWires($positions[$i], 2.0, $heights[$i], 2.0, $maroon);
            }

        EndMode3D();

        DrawRectangle( 10, 10, 220, 70, Fade($sky_blue, 0.5));
        DrawRectangleLines( 10, 10, 220, 70, $blue);

        DrawText("First person camera default controls:", 20, 20, 10,  $black);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, $dark_gray);
        DrawText(time(), 40, 60, 10,  $dark_gray);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
