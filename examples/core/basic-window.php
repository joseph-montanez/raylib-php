<?php

//use raylib\Color;
use raylib\Draw;
use raylib\Text;
use raylib\Timming;
use raylib\Window;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;

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

    Draw::clearBackground([245, 245, 245, 255]);

    Text::draw("Congrats! You created your first window!", 190, 200, 20, [200, 200, 200, 255]);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------