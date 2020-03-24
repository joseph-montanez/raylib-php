<?php

if (!extension_loaded('raylib')) {
    echo 'no raylib';
    exit;
}

use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;
use raylib\Input\Mouse;


// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;
$rayWhite     = new Color(245, 245, 245, 255);
$lightGray     = new Color(200, 200, 200, 255);
$maroon       = new Color(190, 33, 55, 255);
$gray         = new Color(130, 130, 130, 255);
$darkBlue     = new Color(0, 82, 172, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - input mouse wheel");

$ballPositionY = $screenHeight / 2 - 40;
$scrollSpeed = 4;

Timming::setTargetFps(60);       // Set target frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    $ballPositionY -= Mouse::getWheelMove() * $scrollSpeed;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();
        Draw::clearBackground($rayWhite);
        Draw::rectangle($screenWidth / 2 - 40, $ballPositionY, 80, 80, $maroon);
        Text::draw("Use mouse wheel to move the cube up and down!", 10, 10, 20, $gray);
        Text::draw(sprintf("Box position Y: %03i", $boxPositionY), 10, 40, 20, $lightGray);
    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
