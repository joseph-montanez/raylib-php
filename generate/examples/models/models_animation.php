<?php
/*******************************************************************************************
*
*   raylib [models] example - Load 3d model with animations and play them
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example contributed by Culacant (@culacant) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2023 Culacant (@culacant) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   NOTE: To export a model from blender, make sure it is not posed, the vertices need to be
*         in the same position as they would be in edit mode and the scale of your models is
*         set to 0. Scaling can be done from the export menu.
*
********************************************************************************************/


// Initialization
//--------------------------------------------------------------------------------------
use raylib\Camera3D;
use raylib\Color;
use raylib\Vector3;
use const raylib\CameraProjection\CAMERA_PERSPECTIVE;
use const raylib\MaterialMapIndex\MATERIAL_MAP_ALBEDO;
use const raylib\CameraMode\CAMERA_FIRST_PERSON;
use const raylib\KeyboardKey\KEY_SPACE;

$screenWidth = 800;
$screenHeight = 450;


$ray_white = Color::RAYWHITE();
$white = Color::WHITE();
$red = Color::RED();
$maroon = Color::MAROON();
$gray = Color::GRAY();

InitWindow($screenWidth, $screenHeight, "raylib [models] example - model animation");

// Define the camera to look into our 3d world
$camera = new Camera3D(
    new Vector3(10.0, 10.0, 10.0), // Camera position
    new Vector3(0.0, 0.0, 0.0),    // Camera looking at point
    new Vector3(0.0, 1.0, 0.0),    // Camera up vector (rotation towards target)
    45,                            // Camera field-of-view Y
    CAMERA_PERSPECTIVE             // Camera mode type
);

$model = LoadModel(__DIR__ . '/resources/models/iqm/guy.iqm');                    // Load the animated model mesh and basic data
$texture = LoadTexture( __DIR__ . '/resources/models/iqm/guytex.png');             // Load model texture and set material
var_dump($model->materials);
exit;
SetMaterialTexture($model->materials[0], MATERIAL_MAP_ALBEDO, $texture); // Set model material map texture

$position = new Vector3(0.0, 0.0, 0.0);            // Set model position

exit;

// Load animation data
$animsCount = 0;
echo 123;
$anims = LoadModelAnimations(__DIR__ . '/resources/models/iqm/guyanim.iqm', $animsCount);
var_dump('$animsCount', $animsCount);
$animFrameCounter = 0;

DisableCursor();                    // Catch cursor
SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())        // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera($camera, CAMERA_FIRST_PERSON);

    // Play animation when spacebar is held down
    if (IsKeyDown(KEY_SPACE))
    {
        $animFrameCounter++;
        UpdateModelAnimation($model, $anims[0], $animFrameCounter);
        if ($animFrameCounter >= $anims[0]->frameCount) $animFrameCounter = 0;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground($ray_white);

        BeginMode3D($camera);

            DrawModelEx($model, $position, new Vector3(1.0, 0.0, 0.0), -90.0, new Vector3 (1.0, 1.0, 1.0), $white);

            for ($i = 0; $i < $model->boneCount; $i++)
            {
                DrawCube($anims[0]->framePoses[$animFrameCounter][$i]->translation, 0.2, 0.2, 0.2, $red);
            }

            DrawGrid(10, 1.0);         // Draw a grid

        EndMode3D();

        DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, $maroon);
        DrawText("(c) Guy IQM 3D model by @culacant", $screenWidth - 200, $screenHeight - 20, 10, $gray);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadTexture($texture);                     // Unload texture
UnloadModelAnimations($anims, $animsCount);   // Unload model animations data
UnloadModel($model);                         // Unload model

CloseWindow();                  // Close window and OpenGL context
//--------------------------------------------------------------------------------------
