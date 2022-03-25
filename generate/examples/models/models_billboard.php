<?php

// Initialization
//--------------------------------------------------------------------------------------
use raylib\Camera3D;
use raylib\Color;
use raylib\Vector3;
use const raylib\CameraMode\CAMERA_ORBITAL;
use const raylib\CameraProjection\CAMERA_PERSPECTIVE;

$screenWidth = 800;
$screenHeight = 450;

InitWindow($screenWidth, $screenHeight, "raylib [models] example - drawing billboards");

// Define the camera to look into our 3d world

$position = new Vector3(5.0, 4.0, 5.0);
$target = new Vector3(0.0, 2.0, 0.0);
$up = new Vector3(0.0, 1.0, 0.0);
$fovy = 45.0;
$projection = CAMERA_PERSPECTIVE;
$camera = new Camera3D();

$bill = LoadTexture(__DIR__ . '/resources/billboard.png');     // Our texture billboard
$billPosition = new Vector3(0.0, 2.0, 0.0);                    // Position where draw billboard

SetCameraMode($camera, CAMERA_ORBITAL);  // Set an orbital camera mode

SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())            // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera($camera);              // Update camera
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(Color::RAYWHITE());

        BeginMode3D($camera);

            DrawGrid(10, 1.0);        // Draw a grid

            DrawBillboard($camera, $bill, $billPosition, 2.0, Color::WHITE());

        EndMode3D();

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadTexture($bill);        // Unload texture

CloseWindow();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------