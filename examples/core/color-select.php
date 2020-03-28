<?php

use raylib\Collision;
use raylib\Color;
use raylib\Draw;
use raylib\Input\Mouse;
use raylib\Rectangle;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;

$screenWidth  = 800;
$screenHeight = 450;
$raywhite = new Color(245, 245, 245, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - color selection (collision detection)");

/**
 * List of colors to pull from
 *
 * @var \raylib\Color[] $colors
 */
$colors = [
    new Color(80, 80, 80, 255),
    new Color(190, 33, 55, 255),
    new Color(255, 161, 0, 255),
    new Color(0, 117, 44, 255),
    new Color(0, 82, 172, 255),
    new Color(112, 31, 126, 255),
    new Color(76, 63, 47, 255),
    new Color(130, 130, 130, 255),
    new Color(230, 41, 55, 255),
    new Color(255, 203, 0, 255),
    new Color(0, 158, 47, 255),
    new Color(0, 121, 241, 255),
    new Color(135, 60, 190, 255),
    new Color(127, 106, 79, 255),
    new Color(200, 200, 200, 255),
    new Color(255, 109, 194, 255),
    new Color(253, 249, 0, 255),
    new Color(0, 228, 48, 255),
    new Color(102, 191, 255, 255),
    new Color(200, 122, 255, 255),
    new Color(211, 176, 131, 255),
];

/**
 * List of rectangles to render
 *
 * @var \raylib\Rectangle[] $colorsRecs
 */
$colorsRecs = [];

// Fills colorsRecs data (for every rectangle)
for ($i = 0; $i < 21; $i++) {
    $x      = 20 + 100 * (int)($i % 7) + 10 * (int)($i % 7);
    $y      = 60 + 100 * (int)($i / 7) + 10 * (int)($i / 7);
    $width  = 100;
    $height = 100;

    $colorsRecs[$i] = new Rectangle($x, $y, $width, $height);
}

/**
 * List of selected boxes
 *
 * @var bool[] $selected
 **/
$selected = array_fill(0, 21, false);  // Selected rectangles indicator

$mousePoint = new Vector2(0, 0);

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
        if (Collision::checkPointRec($mousePoint, $colorsRecs[$i])) {
            $colors[$i]->setAlpha(120);

            if (Mouse::isButtonPressed(Mouse::LEFT_BUTTON)) {
                $selected[$i] = !$selected[$i];
            }
        } else {
            $colors[$i]->setAlpha(255);
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground($raywhite);

    for ($i = 0; $i < 21; $i++)    // Draw all rectangles
    {
        Draw::rectangleRec($colorsRecs[$i], $colors[$i]);

        // Draw four rectangles around selected rectangle
        if ($selected[$i]) {
            Draw::rectangle($colorsRecs[$i]->x, $colorsRecs[$i]->y, 100, 10, $raywhite);        // Square top rectangle
            Draw::rectangle($colorsRecs[$i]->x, $colorsRecs[$i]->y, 10, 100, $raywhite);        // Square left rectangle
            Draw::rectangle($colorsRecs[$i]->x + 90, $colorsRecs[$i]->y, 10, 100, $raywhite);   // Square right rectangle
            Draw::rectangle($colorsRecs[$i]->x, $colorsRecs[$i]->y + 90, 100, 10, $raywhite);   // Square bottom rectangle
        }
    }

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();                // Close window and OpenGL context
//--------------------------------------------------------------------------------------
