<?php

// Initialization
//--------------------------------------------------------------------------------------
use raylib\BoundingBox;
use raylib\Camera3D;
use raylib\Color;
use raylib\Vector3;
use const raylib\KeyboardKey\KEY_DOWN;
use const raylib\KeyboardKey\KEY_LEFT;
use const raylib\KeyboardKey\KEY_RIGHT;
use const raylib\KeyboardKey\KEY_UP;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

InitWindow($screenWidth, $screenHeight, "raylib [models] example - box collisions");

// Define the camera to look into our 3d world
$camera = new Camera3D(new Vector3(0.0, 10.0, 10.0), new Vector3(0.0, 0.0, 0.0), new Vector3(0.0, 1.0, 0.0), 45.0, 0);

$playerPosition = new Vector3(0.0, 1.0, 2.0);
$playerSize = new Vector3(1.0, 2.0, 1.0);
$playerColor = Color::GREEN();

$enemyBoxPos = new Vector3(-4.0, 1.0, 0.0);
$enemyBoxSize = new Vector3(2.0, 2.0, 2.0);

$enemySpherePos = new Vector3(4.0, 0.0, 0.0);
$enemySphereSize = 1.5;

$collision = false;

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------

    // Move player
    if (IsKeyDown(KEY_RIGHT)) $playerPosition->x += 0.2;
    else if (IsKeyDown(KEY_LEFT)) $playerPosition->x -= 0.2;
    else if (IsKeyDown(KEY_DOWN)) $playerPosition->z += 0.2;
    else if (IsKeyDown(KEY_UP)) $playerPosition->z -= 0.2;

    $collision = false;

    // Check collisions player vs enemy-box
    if (CheckCollisionBoxes(
        new BoundingBox(new Vector3($playerPosition->x - $playerSize->x/2,
                                 $playerPosition->y - $playerSize->y/2,
                                 $playerPosition->z - $playerSize->z/2 ),
                      new Vector3($playerPosition->x + $playerSize->x/2,
                                 $playerPosition->y + $playerSize->y/2,
                                 $playerPosition->z + $playerSize->z/2 )),
        new BoundingBox(new Vector3($enemyBoxPos->x - $enemyBoxSize->x/2,
                                 $enemyBoxPos->y - $enemyBoxSize->y/2,
                                 $enemyBoxPos->z - $enemyBoxSize->z/2 ),
                      new Vector3($enemyBoxPos->x + $enemyBoxSize->x/2,
                                 $enemyBoxPos->y + $enemyBoxSize->y/2,
                                 $enemyBoxPos->z + $enemyBoxSize->z/2 )))) $collision = true;

    // Check collisions player vs enemy-sphere
    if (CheckCollisionBoxSphere(
        new BoundingBox(new Vector3($playerPosition->x - $playerSize->x/2,
                                 $playerPosition->y - $playerSize->y/2,
                                 $playerPosition->z - $playerSize->z/2),
                      new Vector3($playerPosition->x + $playerSize->x/2,
                                 $playerPosition->y + $playerSize->y/2,
                                 $playerPosition->z + $playerSize->z/2 )),
        $enemySpherePos, $enemySphereSize)) $collision = true;

    if ($collision) $playerColor = Color::RED();
    else $playerColor = Color::GREEN();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(Color::RAYWHITE());

        BeginMode3D($camera);

            // Draw  enemy-box
            DrawCube( $enemyBoxPos,  $enemyBoxSize->x,  $enemyBoxSize->y,  $enemyBoxSize->z, Color::GRAY());
            DrawCubeWires( $enemyBoxPos,  $enemyBoxSize->x,  $enemyBoxSize->y,  $enemyBoxSize->z, Color::DARKGRAY());

            // Draw  enemy-sphere
            DrawSphere( $enemySpherePos,  $enemySphereSize, Color::GRAY());
            DrawSphereWires( $enemySpherePos,  $enemySphereSize, 16, 16, Color::DARKGRAY());

            // Draw player
            DrawCubeV($playerPosition, $playerSize, $playerColor);

            DrawGrid(10, 1.0);        // Draw a grid

        EndMode3D();

        DrawText("Move player with cursors to collide", 220, 40, 20, Color::GRAY());

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------