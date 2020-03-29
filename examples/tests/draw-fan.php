<?php

if (!extension_loaded('raylib')) {
    echo 'no raylib';
    exit;
}

use raylib\Color;
use raylib\Draw;
use raylib\Text;
use raylib\Timming;
use raylib\Window;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;
$lightGray    = new Color(245, 245, 245, 255);
$gray         = new Color(200, 200, 200, 255);
$red         = new Color(255, 0, 0, 255);

/**
 * @var $points \raylib\Vector2[]
 **/
$points = [];

for($angle = 0.0; $angle < (2.0*3.14); $angle += (3.14/24.0)) {
    // Calculate x and y position of the next vertex
    $x = 100 + 50.0 * sin($angle);
    $y = 100 + 50.0 * cos($angle);

    // Specify the next vertex for the triangle fan
    $points[] = new \raylib\Vector2($x, $y);
}

/**
 * @var $stripPoints \raylib\Vector2[]
 **/
$stripPoints = [
    new \raylib\Vector2(20, 100),
    new \raylib\Vector2(100, 300),
    new \raylib\Vector2(500, 50),
    new \raylib\Vector2(500, 450),
    new \raylib\Vector2(600, 320)
];

Window::init($screenWidth, $screenHeight, "raylib [core] example - basic window");

Timming::setTargetFps(60);
//--------------------------------------------------------------------------------------

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

    Draw::clearBackground($lightGray);

    Draw::triangleStrip($stripPoints, $red);

    Draw::triangleFan($points, $gray);

    Text::draw("Congrats! You created your first window!", 190, 200, 20, $gray);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
