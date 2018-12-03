<?php

use raylib\Color;
use raylib\Text;
use raylib\Draw;
use raylib\Image;
use raylib\Window;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;
$raywhite = new Color(245, 245, 245, 255);
$white = new Color(255, 255, 255, 255);
$gray     = new Color(130, 130, 130, 255);

Window::init($screenWidth, $screenHeight, "raylib [textures] example - image loading");

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

$image = new Image(__DIR__  . '/resources/raylib_logo.png');    // Loaded in CPU memory (RAM)
$texture = $image->toTexture();                                 // Image converted to texture, GPU memory (VRAM)

unset($image);    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

$texture_x = $screenWidth / 2 - $texture->width / 2;
$texture_y = $screenHeight / 2 - $texture->height / 2;
//---------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------


    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground($raywhite);

    $texture->draw($texture_x, $texture_y, $white);

    Text::draw("this IS a texture loaded from an image!", 300, 370, 10, $gray);


    Draw::end();
    //----------------------------------------------------------------------------------

}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------