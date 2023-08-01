<?php
/*******************************************************************************************
*
*   raylib [models] example - Models loading
*
*   raylib supports multiple models file formats:
*
*     - OBJ  > Text file format. Must include vertex position-texcoords-normals information,
*              if files references some .mtl materials file, it will be loaded (or try to).
*     - GLTF > Text/binary file format. Includes lot of information and it could
*              also reference external files, raylib will try loading mesh and materials data.
*     - IQM  > Binary file format. Includes mesh vertex data but also animation data,
*              raylib can load .iqm animations.
*     - VOX  > Binary file format. MagikaVoxel mesh format:
*              https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
*
*   This example has been created using raylib 4.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014-2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

// Initialization
//--------------------------------------------------------------------------------------
use raylib\Camera3D;
use raylib\Color;
use raylib\Vector3;
use const raylib\CameraMode\CAMERA_FREE;
use const raylib\CameraProjection\CAMERA_PERSPECTIVE;
use const raylib\MaterialMapIndex\MATERIAL_MAP_ALBEDO;
use const raylib\MouseButton\MOUSE_BUTTON_LEFT;

$screenWidth  = 800;
$screenHeight = 450;

InitWindow($screenWidth, $screenHeight, "raylib [models] example - models loading");

// Define the $camera to look into our 3d world
$position = new Vector3(50.0, 50.0, 50.0); // Camera position
$target = new Vector3(0.0, 10.0, 0.0);     // Camera looking at point
$up = new Vector3(0.0, 1.0, 0.0);          // Camera up vector (rotation towards target)
$fovy = 45.0;                                // Camera field-of-view Y
$projection = CAMERA_PERSPECTIVE;                   // Camera mode type
$camera = new Camera3D($position, $target, $up, $fovy, $projection);

$model = LoadModel("resources/models/obj/castle.obj");                 // Load model
$texture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture
SetMaterialTexture($model->materials[0], MATERIAL_MAP_ALBEDO, $texture);

$position = new Vector3(0.0, 0.0, 0.0);                    // Set model position

$bounds = GetMeshBoundingBox($model->meshes[0]);   // Set model bounds

// NOTE: bounds are calculated from the original size of the model,
// if model is scaled on drawing, bounds must be also scaled

SetCameraMode($camera, CAMERA_FREE);     // Set a free $camera mode

$selected = false;          // Selected object flag

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera($camera);

    // Load new models/textures on drag&drop
    if (IsFileDropped())
    {
        $count = 0;
        $droppedFiles = GetDroppedFiles($count);

        if ($count === 1) // Only support one file dropped
        {
            if (IsFileExtension($droppedFiles[0], ".obj") ||
                IsFileExtension($droppedFiles[0], ".gltf") ||
                IsFileExtension($droppedFiles[0], ".glb") ||
                IsFileExtension($droppedFiles[0], ".vox") ||
                IsFileExtension($droppedFiles[0], ".iqm"))       // Model file formats supported
            {
                UnloadModel($model);                     // Unload previous model
                $model = LoadModel($droppedFiles[0]);     // Load new model
                SetMaterialTexture($model->materials[0], MATERIAL_MAP_ALBEDO, $texture);

                $bounds = GetMeshBoundingBox($model->meshes[0]);

                // TODO: Move $camera position from target enough distance to visualize model properly
            }
            else if (str_ends_with($droppedFiles[0], ".png"))  // Texture file formats supported
            {
                // Unload current model texture and load new one
                UnloadTexture($texture);
                $texture = LoadTexture($droppedFiles[0]);
                SetMaterialTexture($model->materials[0], MATERIAL_MAP_ALBEDO, $texture);
            }
        }

        ClearDroppedFiles();    // Clear internal buffers
    }

    // Select model on mouse click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        // Check collision between ray and box
        if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), $camera), $bounds)->hit) $selected = !$selected;
        else $selected = false;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(Color::RAYWHITE());

        BeginMode3D($camera);

            DrawModel($model, $position, 1.0, Color::WHITE());        // Draw 3d model with texture

            DrawGrid(20, 10.0);         // Draw a grid

            if ($selected) DrawBoundingBox($bounds, Color::GREEN());   // Draw selection box

        EndMode3D();

        DrawText("Drag & drop model to load mesh/texture.", 10, GetScreenHeight() - 20, 10, Color::DARKGRAY());
        if ($selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, Color::GREEN());

        DrawText("(c) Castle 3D model by Alberto Cano", $screenWidth - 200, $screenHeight - 20, 10, Color::GRAY());

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadTexture($texture);     // Unload texture
UnloadModel($model);         // Unload model

CloseWindow();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------