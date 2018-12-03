<?php

use raylib\Camera2D;
use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Input\Mouse;
use raylib\Rectangle;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;

define('MAX_BUILDINGS', 100);

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;
$skyblue      = new Color(102, 191, 255, 255);
$raywhite     = new Color(245, 245, 245, 255);
$darkgray     = new Color(80, 80, 80, 255);
$red          = new Color(230, 41, 55, 255);
$green        = new Color(0, 228, 48, 255);
$blue         = new Color(0, 121, 241, 255);
$black        = new Color(0, 0, 0, 255);
$target       = new Vector2(0, 0);

Window::init($screenWidth, $screenHeight, "raylib [core] example - 2d camera");

$player      = new Rectangle(400, 280, 40, 40);
$buildings   = array_fill(0, MAX_BUILDINGS, ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]);
$buildColors = array_fill(0, MAX_BUILDINGS, [0, 0, 0, 255]);

$spacing = 0;

for ($i = 0; $i < MAX_BUILDINGS; $i++) {
    $height = rand(100, 800);
    $width  = rand(50, 200);

    $buildings[$i] = new Rectangle($width, $height, $screenHeight - 130 - $height, -6000 + $spacing);

    $spacing += $width;

    $buildColors[$i] = new Color(rand(200, 240), rand(200, 240), rand(200, 250), 255);
}

$camera = new Camera2D();
$camera->setOffset(new Vector2(0 ,0));
$camera->setTarget(new Vector2($player->getX() + 20 ,$player->getY() + 20));
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
    $target->setX($player->getX() + 20);
    $target->setY($player->getY() + 20);
    $camera->setTarget($target);

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

    if ($camera->getZoom() > 3.0) {
        $camera->setZoom(3.0);
    } else if ($camera->getZoom() < 0.1) {
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

    Draw::clearBackground($raywhite);

    Draw::beginMode2d($camera);

    Draw::rectangle(-6000, 320, 13000, 8000, $darkgray);

    for ($i = 0; $i < MAX_BUILDINGS; $i++) {
        Draw::rectangleRec($buildings[$i], $buildColors[$i]);
    }

    Draw::rectangleRec($player, $red);

    Draw::rectangle($camera->getTarget()->getX(), -500, 1, $screenHeight * 4, $green);
    Draw::rectangle(-500, $camera->getTarget()->getY(), $screenWidth * 4, 1, $green);

    Draw::endMode2d();

    Text::draw("SCREEN AREA", 640, 10, 20, $red);

    Draw::rectangle(0, 0, $screenWidth, 5, $red);
    Draw::rectangle(0, 5, 5, $screenHeight - 10, $red);
    Draw::rectangle($screenWidth - 5, 5, 5, $screenHeight - 10, $red);
    Draw::rectangle(0, $screenHeight - 5, $screenWidth, 5, $red);

    Draw::rectangle(10, 10, 250, 113, Color::fade($skyblue, 0.5));
    Draw::rectangleLines(10, 10, 250, 113, $blue);

    Text::draw("Free 2d camera3d controls:", 20, 20, 10, $black);
    Text::draw("- Right/Left to move Offset", 40, 40, 10, $darkgray);
    Text::draw("- Mouse Wheel to Zoom in-out", 40, 60, 10, $darkgray);
    Text::draw("- A / S to Rotate", 40, 80, 10, $darkgray);
    Text::draw("- R to reset Zoom and Rotation", 40, 100, 10, $darkgray);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

