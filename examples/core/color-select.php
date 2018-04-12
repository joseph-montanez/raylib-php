<?php

require_once __DIR__ . '/../raylib-colors.php';

use raylib\Collision;
use raylib\Draw;
use raylib\Input\Mouse;
use raylib\Timming;
use raylib\Window;
use const raylib\RAYWHITE;
use const raylib\BEIGE;
use const raylib\BLUE;
use const raylib\BROWN;
use const raylib\DARKBLUE;
use const raylib\DARKBROWN;
use const raylib\DARKGRAY;
use const raylib\DARKGREEN;
use const raylib\DARKPURPLE;
use const raylib\GOLD;
use const raylib\GRAY;
use const raylib\GREEN;
use const raylib\LIGHTGRAY;
use const raylib\LIME;
use const raylib\MAROON;
use const raylib\ORANGE;
use const raylib\PINK;
use const raylib\PURPLE;
use const raylib\RED;
use const raylib\SKYBLUE;
use const raylib\VIOLET;
use const raylib\YELLOW;

$screenWidth  = 800;
$screenHeight = 450;

Window::init($screenWidth, $screenHeight, "raylib [core] example - color selection (collision detection)");

$colors = [
    DARKGRAY,
    MAROON,
    ORANGE,
    DARKGREEN,
    DARKBLUE,
    DARKPURPLE,
    DARKBROWN,
    GRAY,
    RED,
    GOLD,
    LIME,
    BLUE,
    VIOLET,
    BROWN,
    LIGHTGRAY,
    PINK,
    YELLOW,
    GREEN,
    SKYBLUE,
    PURPLE,
    BEIGE
];

$colors_recs = [];

// Fills colorsRecs data (for every rectangle)
for ($i = 0; $i < 21; $i++)
{
    $colorsRecs[$i]['x']      = 20 + 100 * ($i % 7) + 10 * ($i % 7);
    $colorsRecs[$i]['y']      = 60 + 100 * ($i / 7) + 10 * ($i / 7);
    $colorsRecs[$i]['width']  = 100;
    $colorsRecs[$i]['height'] = 100;
}

$selected[21] = array_fill(0, 21, false);  // Selected rectangles indicator

$mousePoint = ['x' => 0, 'y' => 0];

Timming::setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    $mousePoint = Mouse::getPosition();

    for ($i = 0; $i < 21; $i++)    // Iterate along all the rectangles
    {
        if (Collision::checkPointRec($mousePoint, $colorsRecs[$i]))
        {
            $colors[$i]['a'] = 120;

            if (Mouse::isButtonPressed(Mouse::LEFT_BUTTON)) { $selected[$i] = !$selected[$i]; }
        }
        else { $colors[$i]['a'] = 255; }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

        Draw::clearBackground(RAYWHITE);

        for ($i = 0; $i < 21; $i++)    // Draw all rectangles
        {
            Draw::rectangleRec($colorsRecs[$i], $colors[$i]);

            // Draw four rectangles around selected rectangle
            if ($selected[$i])
            {
                Draw::rectangle($colorsRecs[$i]['x'], $colorsRecs[$i]['y'], 100, 10, RAYWHITE);        // Square top rectangle
                Draw::rectangle($colorsRecs[$i]['x'], $colorsRecs[$i]['y'], 10, 100, RAYWHITE);        // Square left rectangle
                Draw::rectangle($colorsRecs[$i]['x'] + 90, $colorsRecs[$i]['y'], 10, 100, RAYWHITE);   // Square right rectangle
                Draw::rectangle($colorsRecs[$i]['x'], $colorsRecs[$i]['y'] + 90, 100, 10, RAYWHITE);   // Square bottom rectangle
            }
        }

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();                // Close window and OpenGL context
//--------------------------------------------------------------------------------------
