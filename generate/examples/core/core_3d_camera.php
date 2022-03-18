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

//gc_disable();

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

InitWindow($screenWidth, $screenHeight, "raylib [core] example - 3d camera first person");

// Define the camera to look into our 3d world (position, target, up vector)
$position4 = new Vector3(4.0, 2.0, 4.0);
$target = new Vector3(0.0, 1.8, 0.0);
$up = new Vector3(0.0, 1.0, 0.0);
$fovy = 60.0;
$projection = CAMERA_PERSPECTIVE;
$camera = new Camera3D($position4, $target, $up, $fovy, $projection);

SetCameraMode($camera, CAMERA_FIRST_PERSON); // Set a first person camera mode
printf("0: \$camera->position %f, %f, %f\n", $camera->position->x, $camera->position->y, $camera->position->z);
SetCameraMode($camera, CAMERA_FIRST_PERSON); // Set a first person camera mode
printf("0: \$camera->position %f, %f, %f\n", $camera->position->x, $camera->position->y, $camera->position->z);

SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second

UpdateCamera($camera);

echo "Done!\n";