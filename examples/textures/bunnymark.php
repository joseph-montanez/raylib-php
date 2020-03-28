<?php

use raylib\Color;
use raylib\Draw;
use raylib\Input\Mouse;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;

/*******************************************************************************************
 *
 *   raylib [textures] example - Bunnymark
 *
 *   This example has been created using raylib 1.6 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
const MAX_BUNNIES = 50000;    // 50K bunnies limit

// This is the maximum amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
const MAX_BATCH_ELEMENTS = 8192;

class Bunny
{
    public Vector2 $position;
    public Vector2 $speed;
    public Color $color;
}

$rayWhite = new Color(245, 245, 245, 255);
$lightGray = new Color(200, 200, 200, 255);
$darkGray = new Color(80, 80, 80, 255);
$maroon = new Color(190, 33, 55, 255);
$green        = new Color(0, 228, 48, 255);
$gray = new Color(130, 130, 130, 255);
$red = new Color(230, 41, 55, 255);
$blue = new Color(0, 121, 241, 255);
$gold = new Color(255, 203, 0, 255);
$lime = new Color(0, 158, 47, 255);
$darkBlue = new Color(0, 82, 172, 255);
$black = new Color(0, 0, 0, 255);
$violet = new Color(135, 60, 190, 255);
$pink = new Color(255, 109, 194, 255);

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

Window::init($screenWidth, $screenHeight, "raylib [textures] example - bunnymark");

// Load bunny texture
$texBunny = new \raylib\Texture(__DIR__ . "/resources/wabbit_alpha.png");
$texWidth = $texBunny->width / 2;
$texHeight = $texBunny->height / 2;

/**
 * @var $bunniesCount Vector2[]
 */
$bunnies = [];

$bunniesCount = 0;           // Bunnies counter

Timming::setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (Mouse::isButtonDown(Mouse::LEFT_BUTTON)) {
        // Create more bunnies
        for ($i = 0; $i < 100; $i++) {
            if ($bunniesCount < MAX_BUNNIES) {
                $bunny = new Bunny();
                $bunny->position = clone Mouse::getPosition();
                $bunny->speed = new Vector2((float)rand(-250, 250) / 60.0, (float)rand(-250, 250) / 60.0);
                $bunny->color = new Color(rand(50, 240),
                    rand(80, 240),
                    rand(100, 240), 255);

                $bunnies[$bunniesCount] = $bunny;

                $bunniesCount++;
            }
        }
    }

    $screenWidth = Window::getScreenWidth();
    $screenHeight = Window::getScreenHeight();
    // Update bunnies
    for ($i = 0; $i < $bunniesCount; $i++) {
        $bunny = $bunnies[$i];

        $bunny->position->x += $bunny->speed->x;
        $bunny->position->y += $bunny->speed->y;

        if ((($bunny->position->x + $texBunny->width / 2) > Window::getScreenWidth()) ||
            (($bunny->position->x + $texBunny->width / 2) < 0)) $bunny->speed->x *= -1;
        if ((($bunny->position->y + $texBunny->height / 2) > Window::getScreenHeight()) ||
            (($bunny->position->y + $texBunny->height / 2 - 40) < 0)) $bunny->speed->y *= -1;
    }
    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground($rayWhite);

    for ($i = 0; $i < $bunniesCount; $i++) {
        $bunny = $bunnies[$i];
        // NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
        // a draw call is launched and buffer starts being filled again;
        // before issuing a draw call, updated vertex data from internal CPU buffer is send to GPU...
        // Process of sending data is costly and it could happen that GPU data has not been completely
        // processed for drawing while new data is tried to be sent (updating current in-use buffers)
        // it could generates a stall and consequently a frame drop, limiting the number of drawn bunnies
        $texBunny->drawV($bunny->position, $bunny->color);
    }

    Draw::Rectangle(0, 0, $screenWidth, 40, $black);
    Text::draw(sprintf("bunnies: %d", $bunniesCount), 120, 10, 20, $green);
    Text::draw(sprintf("batched draw calls: %d", 1 + $bunniesCount / MAX_BATCH_ELEMENTS), 320, 10, 20, $maroon);

    Text::drawFps(10, 10);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------
