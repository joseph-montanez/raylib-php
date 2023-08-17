<?php
/*******************************************************************************************
*
*   raylib [models] example - Cubicmap loading and drawing
*
*   This example has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


// Initialization
//--------------------------------------------------------------------------------------
use raylib\Camera3D;
use raylib\Color;
use raylib\Material;
use raylib\MaterialMap;
use raylib\Vector2;
use raylib\Vector3;
use const raylib\CameraMode\CAMERA_ORBITAL;
use const raylib\MaterialMapIndex\MATERIAL_MAP_ALBEDO;

$screenWidth = 800;
$screenHeight = 450;

$ray_white = Color::RAYWHITE();
$white = Color::WHITE();
$green = Color::GREEN();
$gray = Color::GRAY();

InitWindow($screenWidth, $screenHeight, "raylib [models] example - cubesmap loading and drawing");

// Define the camera to look into our 3d world
$camera = new Camera3D(new Vector3(16.0, 14.0, 16.0), new Vector3(0.0, 0.0, 0.0), new Vector3(0.0, 1.0, 0.0), 45.0, 0);

$image = LoadImage(__DIR__ . '/resources/cubicmap.png');      // Load cubicmap image (RAM)
$cubicmap = LoadTextureFromImage($image);       // Convert image to texture to display (VRAM)

$mesh = GenMeshCubicmap($image, new Vector3(1.0, 1.0, 1.0));
$model = LoadModelFromMesh($mesh);

// NOTE: By default each cube is mapped to one part of texture atlas
$texture = LoadTexture(__DIR__ . '/resources/cubicmap_atlas.png');     // Load map texture
$model->materials[0]->maps[MATERIAL_MAP_ALBEDO]->texture = $texture;    // Set map diffuse texture

$mapPosition = new Vector3(-16.0, 0.0, -8.0);          // Set model position

UnloadImage($image);     // Unload cubesmap image from RAM, already uploaded to VRAM

SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())            // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera($camera, CAMERA_ORBITAL);              // Update camera
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
        ClearBackground($ray_white);

        BeginMode3D($camera);
            DrawModel($model, $mapPosition, 1.0, $white);
        EndMode3D();

        DrawTextureEx($cubicmap, new Vector2($screenWidth - $cubicmap->width * 4.0 - 20, 20.0), 0.0, 4.0, $white);
        DrawRectangleLines($screenWidth - $cubicmap->width * 4 - 20, 20, $cubicmap->width * 4, $cubicmap->height * 4, $green);

        DrawText("cubicmap image used to", 658, 90, 10, $gray);
        DrawText("generate map 3d model", 658, 104, 10, $gray);

        DrawFPS(10, 10);
    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadTexture($cubicmap);    // Unload cubicmap texture
UnloadTexture($texture);     // Unload map texture
UnloadModel($model);         // Unload map model

CloseWindow();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------
