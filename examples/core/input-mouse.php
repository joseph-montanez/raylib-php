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
$darkGray     = new Color(80, 80, 80, 255);
$maroon       = new Color(190, 33, 55, 255);
$lime         = new Color(0, 158, 47, 255);
$darkBlue     = new Color(0, 82, 172, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - mouse input");

$ballPosition = new Vector2(-100, -100);
$ballColor = $darkBlue;

Timming::setTargetFps(60);       // Set target frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    $ballPosition = Mouse::getPosition();

    if (Mouse::isButtonPressed(Mouse::LEFT_BUTTON)) { $ballColor = $maroon; }
    elseif (Mouse::isButtonPressed(Mouse::MIDDLE_BUTTON)) { $ballColor = $lime; }
    elseif (Mouse::isButtonPressed(Mouse::RIGHT_BUTTON)) { $ballColor = $darkBlue; }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();
        Draw::clearBackground($rayWhite);
        Draw::circleV($ballPosition, 40, $ballColor);
        Text::draw("move the ball with arrow keys", 10, 10, 20, $darkGray);
    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
