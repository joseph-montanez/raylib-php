<?php

use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;


// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;
$bgColor      = new Color(245, 245, 245, 255);
$txtColor     = new Color(130, 130, 130, 255);
$ballColor    = new Color(190, 33, 55, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - keyboard input");

$ballPosition = new Vector2($screenWidth / 2, $screenHeight / 2);

Timming::setTargetFps(60);       // Set target frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (Key::isDown(Key::RIGHT)) {
        $ballPosition->setX($ballPosition->getX() + 0.8);
    }
    if (Key::isDown(Key::LEFT)) {
        $ballPosition->setX($ballPosition->getX() - 0.8);
    }
    if (Key::isDown(Key::UP)) {
        $ballPosition->setY($ballPosition->getY() - 0.8);
    }
    if (Key::isDown(Key::DOWN)) {
        $ballPosition->setY($ballPosition->getY() + 0.8);
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();
    Draw::clearBackground($bgColor);
    Text::draw("move the ball with arrow keys", 10, 10, 20, $txtColor);
    Draw::circleV($ballPosition, 50, $ballColor);
    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
