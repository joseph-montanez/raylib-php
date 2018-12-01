<?php

require_once __DIR__ . '/../raylib-colors.php';

use raylib\Camera2D;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Input\Mouse;
use raylib\Text;
use raylib\Timming;
use raylib\Window;
use const raylib\BLACK;
use const raylib\BLUE;
use const raylib\DARKGRAY;
use const raylib\GREEN;
use const raylib\RAYWHITE;
use const raylib\RED;
use const raylib\SKYBLUE;

define('MAX_BUILDINGS', 100);

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;

Window::init($screenWidth, $screenHeight, "raylib [core] example - 2d camera");

$player      = ['x' => 400, 'y' => 280, 'width' => 40, 'height' => 40];
$buildings   = array_fill(0, MAX_BUILDINGS, ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]);
$buildColors = array_fill(0, MAX_BUILDINGS, [0, 0, 0, 255]);

$spacing = 0;

for ($i = 0; $i < MAX_BUILDINGS; $i++) {
    $buildings[$i]['width']  = rand(50, 200);
    $buildings[$i]['height'] = rand(100, 800);
    $buildings[$i]['y']      = $screenHeight - 130 - $buildings[$i]['height'];
    $buildings[$i]['x']      = -6000 + $spacing;

    $spacing += $buildings[$i]['width'];

    $buildColors[$i] = [rand(200, 240), rand(200, 240), rand(200, 250), 255];
}

$camera = new Camera2D();
$camera->setOffset(['x' => 0, 'y' => 0]);

$camera->setTarget(['x' => $player['x'] + 20, 'y' => $player['y'] + 20]);
$camera->setOffset(['x' => 0, 'y' => 0]);
$camera->setRotation(0.0);
$camera->setZoom(1.0);

Timming::setTargetFPS(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (Key::isDown(Key::RIGHT)) {
        $player['x'] += 2;              // Player movement
        $offset      = $camera->getOffset();
        $offset['x'] -= 2;       // Camera displacement with player movement
        $camera->setOffset($offset);
    } else if (Key::isDown(Key::LEFT)) {
        $player['x']  -= 2;              // Player movement
        $offset1      = $camera->getOffset();
        $offset1['x'] += 2;       // Camera displacement with player movement
        $camera->setOffset($offset1);
    }

    // Camera target follows player
    $camera->setTarget(['x' => $player['x'] + 20, 'y' => $player['y'] + 20]);

    // Camera rotation controls
    if (Key::isDown(Key::A)) {
        $camera->setRotation($camera->getRotation() - 1);
    } else if (Key::isDown(Key::S)) {
        $camera->setRotation($camera->getRotation() + 1);
    }

    // Limit camera rotation to 80 degrees (-40 to 40)
    if ($camera->getRotation() > 40) {
        $camera->setRotation(40);
    } else if ($camera->getRotation() < -40) {
        $camera->setRotation(-40);
    }

    // Camera zoom controls
    $camera->setZoom(Mouse::getWheelMove() * 0.05);

    if ($camera->zoom > 3.0) {
        $camera->setZoom(3.0);
    } else if ($camera->zoom < 0.1) {
        $camera->setZoom(0.1);
    }

    // Camera reset (zoom and rotation)
    if (Key::isDown(Key::R)) {
        $camera->setZoom(1);
        $camera->setRotation(0);
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground(RAYWHITE);

    Draw::beginMode2d($camera);

    Draw::rectangle(-6000, 320, 13000, 8000, DARKGRAY);

    for ($i = 0; $i < MAX_BUILDINGS; $i++) {
        Draw::rectangleRec($buildings[$i], $buildColors[$i]);
    }

    Draw::rectangleRec($player, RED);

    Draw::rectangle($camera->getTarget()['x'], -500, 1, $screenHeight * 4, GREEN);
    Draw::rectangle(-500, $camera->getTarget()['y'], $screenWidth * 4, 1, GREEN);

    Draw::endMode2d();

    Text::draw("SCREEN AREA", 640, 10, 20, RED);

    Draw::rectangle(0, 0, $screenWidth, 5, RED);
    Draw::rectangle(0, 5, 5, $screenHeight - 10, RED);
    Draw::rectangle($screenWidth - 5, 5, 5, $screenHeight - 10, RED);
    Draw::rectangle(0, $screenHeight - 5, $screenWidth, 5, RED);

    Draw::rectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.5));
    Draw::rectangleLines(10, 10, 250, 113, BLUE);

    Text::draw("Free 2d camera controls:", 20, 20, 10, BLACK);
    Text::draw("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
    Text::draw("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
    Text::draw("- A / S to Rotate", 40, 80, 10, DARKGRAY);
    Text::draw("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

