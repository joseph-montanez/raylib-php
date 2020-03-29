<?php
/*******************************************************************************************
 *
 *   raylib - sample game: floppy
 *
 *   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
 *
 *   This game has been created using raylib v1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

use raylib\Collision;
use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Rectangle;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
const MAX_TUBES = 100;
const FLOPPY_RADIUS = 24;
const TUBES_WIDTH = 80;

$rayWhite = new Color(245, 245, 245, 255);
$lightGray = new Color(200, 200, 200, 255);
$darkGray = new Color(80, 80, 80, 255);
$maroon = new Color(190, 33, 55, 255);
$gray = new Color(130, 130, 130, 255);
$red = new Color(230, 41, 55, 255);
$blue = new Color(0, 121, 241, 255);
$white = new Color(255, 255, 255, 255);
$gold = new Color(255, 203, 0, 255);
$lime = new Color(0, 158, 47, 255);
$darkBlue = new Color(0, 82, 172, 255);
$black = new Color(0, 0, 0, 255);
$violet = new Color(135, 60, 190, 255);
$pink = new Color(255, 109, 194, 255);

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
class Floppy
{
    public Vector2 $position;
    public int $radius;
    public Color $color;
}

class Tubes
{
    public Rectangle $rec;
    public Color $color;
    public bool $active;
}

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

$gameOver = false;
$pause = false;
$score = 0;
$hiScore = 0;
$t = time();

$floppy = new Floppy();
//$floppy->position = new Rectangle(0,0, 0, 0);
/**
 * @var Tubes[]
 */
$tubes = [];
/**
 * @var \raylib\Vector2[]
 */
$tubesPos = [];

$tubesSpeedX = 0;
$superfx = false;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
// Initialization
//---------------------------------------------------------

raylib\SetConfigFlags(raylib\Flags\VSYNC_HINT);
Window::init($screenWidth, $screenHeight, "sample game: floppy");

InitGame();

Timming::setTargetFps(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update and Draw
    //----------------------------------------------------------------------------------
    UpdateDrawFrame();
    //----------------------------------------------------------------------------------


}
// De-Initialization
//--------------------------------------------------------------------------------------
UnloadGame();         // Unload loaded data (textures, sounds, models...)

Window::close();         // Close window and OpenGL context
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
function InitGame()
{
    global $floppy, $tubesSpeedX, $screenHeight, $tubesPos, $tubes, $score, $gameOver, $superfx, $pause;

    $floppy->radius = FLOPPY_RADIUS;
    $floppy->position = new Vector2(80, $screenHeight / 2 - $floppy->radius);
    $tubesSpeedX = 2;

    for ($i = 0; $i < MAX_TUBES; $i++) {
        $tubesPos[$i] = new Vector2(400 + 280 * $i, -rand(0, 120));
    }
    for ($i = 0; $i < MAX_TUBES * 2; $i += 2) {
        if (!isset($tubes[$i])) {
            $tubes[$i] = new Tubes();
        }
        if (!isset($tubes[$i + 1])) {
            $tubes[$i + 1] = new Tubes();
        }
        if (!isset($tubes[$i / 2])) {
            $tubes[$i / 2] = new Tubes();
        }
    }

    for ($i = 0; $i < MAX_TUBES * 2; $i += 2) {
        $tubes[$i]->rec = new Rectangle(
            $tubesPos[$i / 2]->getX(),
            $tubesPos[$i / 2]->getY(),
            TUBES_WIDTH,
            255
        );

        $tubes[$i + 1]->rec = new Rectangle(
            $tubesPos[$i / 2]->getX(),
            600 + $tubesPos[$i / 2]->getY() - 255,
            TUBES_WIDTH,
            255
        );

        $tubes[$i / 2]->active = true;
    }

    $score = 0;

    $gameOver = false;
    $superfx = false;
    $pause = false;

}

// Update game (one frame)
function UpdateGame()
{
    global $floppy, $tubesSpeedX, $tubesPos, $tubes, $score, $gameOver, $superfx, $pause, $hiScore, $time;

    if (time() - $time > 1) {
        echo "FPS: ", Timming::getFps(), PHP_EOL;
        $time = time();
    }

    if (!$gameOver) {
        if (Key::isPressed(Key::P)) {
            $pause = !$pause;
        }

        if (!$pause) {
            for ($i = 0; $i < MAX_TUBES; $i++) {
                $tubesPos[$i]->setX($tubesPos[$i]->getX() - $tubesSpeedX);
            }

            for ($i = 0; $i < MAX_TUBES * 2; $i += 2) {
                $tubes[$i]->rec->setX($tubesPos[$i / 2]->getX());
                $tubes[$i + 1]->rec->setX($tubesPos[$i / 2]->getX());
            }

            if (Key::isDown(Key::SPACE) && !$gameOver) {
                $floppy->position->setY($floppy->position->getY() - 3);
            } else {
                $floppy->position->setY($floppy->position->getY() + 1);
            }

            // Check Collisions
            for ($i = 0; $i < MAX_TUBES * 2; $i++) {
                if (Collision::checkCircleRec($floppy->position, $floppy->radius, $tubes[$i]->rec)) {
                    $gameOver = true;
                    $pause = false;
                } else if (($tubesPos[$i / 2]->getX() < $floppy->position->getX()) && $tubes[$i / 2]->active && !$gameOver) {
                    $score += 100;
                    $tubes[$i / 2]->active = false;

                    $superfx = true;

                    if ($score > $hiScore) {
                        $hiScore = $score;
                    }
                }
            }
        }
    } else {
        if (Key::isPressed(Key::ENTER)) {
            InitGame();
            $gameOver = false;
        }
    }
}

// Draw game (one frame)
function DrawGame()
{
    global $floppy, $screenHeight, $screenWidth, $tubes, $score, $gameOver, $superfx, $pause, $rayWhite, $gray, $white, $lightGray, $darkGray, $hiScore;

    Draw::begin();

    Draw::clearBackground($rayWhite);

    if (!$gameOver) {
        Draw::circle($floppy->position->getX(), $floppy->position->getY(), $floppy->radius, $darkGray);

        // Draw tubes
        for ($i = 0; $i < MAX_TUBES; $i++) {
            Draw::rectangle($tubes[$i * 2]->rec->getX(), $tubes[$i * 2]->rec->getY(), $tubes[$i * 2]->rec->getWidth(), $tubes[$i * 2]->rec->getHeight(), $gray);
            Draw::rectangle($tubes[$i * 2 + 1]->rec->getX(), $tubes[$i * 2 + 1]->rec->getY(), $tubes[$i * 2 + 1]->rec->getWidth(), $tubes[$i * 2 + 1]->rec->getHeight(), $gray);
        }

        // Draw flashing fx (one frame only)
        if ($superfx) {
            Draw::rectangle(0, 0, $screenWidth, $screenHeight, $white);
            $superfx = false;
        }

        Text::draw(sprintf("SCORE: %04d", $score), 20, 20, 40, $gray);
        Text::draw(sprintf("HI-SCORE: %04d", $hiScore), 20, 70, 20, $lightGray);

        if ($pause) {
            Text::draw("GAME PAUSED", $screenWidth / 2 - Text::measure("GAME PAUSED", 40) / 2, $screenHeight / 2 - 40, 40, $gray);
        }
    } else {
        Text::draw("PRESS [ENTER] TO PLAY AGAIN", Window::getScreenWidth() / 2 - Text::measure("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, Window::getScreenHeight() / 2 - 50, 20, $gray);
    }

    Draw::end();
}

// Unload game variables
function UnloadGame()
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
function UpdateDrawFrame()
{
    UpdateGame();
    DrawGame();
}
