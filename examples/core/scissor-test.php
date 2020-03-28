<?php
/*******************************************************************************************
*
*   raylib [core] example - Scissor test
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by Chris Dill (@MysteriousSpace) and reviewed by Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2019 Chris Dill (@MysteriousSpace)
*
********************************************************************************************/

// Initialization
//--------------------------------------------------------------------------------------
use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Input\Mouse;
use raylib\Text;
use raylib\Timming;
use raylib\Window;

$screenWidth = 800;
$screenHeight = 450;

$rayWhite = new Color(245, 245, 245, 255);
$lightGray = new Color(200, 200, 200, 255);
$red = new Color(230, 41, 55, 255);
$black = new Color(0, 0, 0, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - scissor test");

$scissorArea = new \raylib\Rectangle(0, 0, 300, 300);
$scissorMode = true;

Timming::setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (Key::isPressed(Key::S)) $scissorMode = !$scissorMode;

    // Centre the scissor area around the mouse position
    $scissorArea->x = Mouse::getX() - $scissorArea->width / 2;
    $scissorArea->y = Mouse::getY() - $scissorArea->height / 2;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground($rayWhite);

    if ($scissorMode) Draw::beginScissorMode($scissorArea->x, $scissorArea->y, $scissorArea->width, $scissorArea->height);

    // Draw full screen rectangle and some text
    // NOTE: Only part defined by scissor area will be rendered
    Draw::rectangle(0, 0, Window::getScreenWidth(), Window::getScreenHeight(), $red);
    Text::draw("Move the mouse around to reveal this text!", 190, 200, 20, $lightGray);

    if ($scissorMode) Draw::endScissorMode();

    Draw::rectangleLinesEx($scissorArea, 1, $black);
    Text::draw("Press S to toggle scissor test", 10, 10, 20, $black);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

