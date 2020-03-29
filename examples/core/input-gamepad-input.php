<?php

if (!extension_loaded('raylib')) {
    echo 'no raylib';
    exit;
}

use raylib\Color;
use raylib\Draw;
use raylib\Input\Gamepad;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;
use raylib\Texture;

const XBOX360_NAME_ID = "Xbox 360 Controller";
const PS3_NAME_ID = "PLAYSTATION(R)3 Controller";

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

raylib\SetConfigFlags(raylib\Flags\MSAA_4X_HINT);

$rayWhite = new Color(245, 245, 245, 255);
$lightGray = new Color(200, 200, 200, 255);
$darkGray = new Color(80, 80, 80, 255);
$maroon = new Color(190, 33, 55, 255);
$gray = new Color(130, 130, 130, 255);
$red = new Color(230, 41, 55, 255);
$blue = new Color(0, 121, 241, 255);
$gold = new Color(255, 203, 0, 255);
$lime = new Color(0, 158, 47, 255);
$darkBlue = new Color(0, 82, 172, 255);
$black = new Color(0, 0, 0, 255);
$violet = new Color(135, 60, 190, 255);
$pink = new Color(255, 109, 194, 255);

Window::init($screenWidth, $screenHeight, "raylib [core] example - gamepad input");

$texPs3Pad = new Texture(__DIR__ . "/resources/ps3.png");
$texXboxPad = new Texture(__DIR__ . "/resources/xbox.png");

$psControllerV1 = new Vector2(436, 168);
$psControllerV2 = new Vector2(436, 185);
$psControllerV3 = new Vector2(464, 177);

Timming::setTargetFps(60);       // Set target frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // ...
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();
    Draw::clearBackground($rayWhite);

    if (GamePad::isAvailable(Gamepad::PLAYER1)) {
        Text::draw(sprintf("GP1: %s", Gamepad::getName(Gamepad::PLAYER1)), 10, 10, 10, $black);

        if (stristr(Gamepad::getName(Gamepad::PLAYER1), 'xbox')) {
            $texXboxPad->draw(0, 0, $darkGray);

            // Draw buttons: xbox home
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE)) {
                Draw::circle(394, 89, 19, $red);
            }

            // Draw buttons: basic
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE_RIGHT)) {
                Draw::circle(436, 150, 9, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE_LEFT)) {
                Draw::circle(352, 150, 9, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_LEFT)) {
                Draw::circle(501, 151, 15, $blue);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_DOWN)) {
                Draw::circle(536, 187, 15, $lime);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_RIGHT)) {
                Draw::circle(572, 151, 15, $maroon);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_UP)) {
                Draw::circle(536, 115, 15, $gold);
            }

            // Draw buttons: d-pad
            Draw::rectangle(317, 202, 19, 71, $black);
            Draw::rectangle(293, 228, 69, 19, $black);
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_UP)) {
                Draw::rectangle(317, 202, 19, 26, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_DOWN)) {
                Draw::rectangle(317, 202 + 45, 19, 26, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_LEFT)) {
                Draw::rectangle(292, 228, 25, 19, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_RIGHT)) {
                Draw::rectangle(292 + 44, 228, 26, 19, $red);
            }
            // Draw buttons: left-right back
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_TRIGGER_1)) Draw::circle(259, 61, 20, $red);
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_TRIGGER_1)) Draw::circle(536, 61, 20, $red);

            // Draw axis: left joystick
            Draw::circle(259, 152, 39, $black);
            Draw::circle(259, 152, 34, $lightGray);
            Draw::circle(259 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_X) * 20),
                152 - (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_Y) * 20), 25, $black);

            // Draw axis: right joystick
            Draw::circle(461, 237, 38, $black);
            Draw::circle(461, 237, 33, $lightGray);
            Draw::circle(461 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_X) * 20),
                237 - (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_Y) * 20), 25, $black);

            // Draw axis: left-right triggers
            Draw::rectangle(170, 30, 15, 70, $gray);
            Draw::rectangle(604, 30, 15, 70, $gray);
            Draw::rectangle(170, 30, 15, (((1.0 + Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_TRIGGER)) / 2.0) * 70), $red);
            Draw::rectangle(604, 30, 15, (((1.0 + Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_TRIGGER)) / 2.0) * 70), $red);

        } elseif (stristr(Gamepad::getName(Gamepad::PLAYER1), 'playstation')) {
            $texPs3Pad->draw(0, 0, $gray);

            // Draw buttons: ps
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE)) Draw::circle(396, 222, 13, $red);

            // Draw buttons: basic
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE_LEFT)) {
                Draw::rectangle(328, 170, 32, 13, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_MIDDLE_RIGHT)) {
                Draw::triangle($psControllerV1, $psControllerV2, $psControllerV3, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_UP)) {
                Draw::circle(557, 144, 13, $lime);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_RIGHT)) {
                Draw::circle(586, 173, 13, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_DOWN)) {
                Draw::circle(557, 203, 13, $violet);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_FACE_LEFT)) {
                Draw::circle(527, 173, 13, $pink);
            }

            // Draw buttons: d-pad
            Draw::rectangle(225, 132, 24, 84, $black);
            Draw::rectangle(195, 161, 84, 25, $black);
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_UP)) {
                Draw::rectangle(225, 132, 24, 29, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_DOWN)) {
                Draw::rectangle(225, 132 + 54, 24, 30, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_LEFT)) {
                Draw::rectangle(195, 161, 30, 25, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_FACE_RIGHT)) {
                Draw::rectangle(195 + 54, 161, 30, 25, $red);
            }

            // Draw buttons: left-right back buttons
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_LEFT_TRIGGER_1)) {
                Draw::circle(239, 82, 20, $red);
            }
            if (GamePad::isButtonDown(Gamepad::PLAYER1, Gamepad::BUTTON_RIGHT_TRIGGER_1)) {
                Draw::circle(557, 82, 20, $red);
            }

            // Draw axis: left joystick
            Draw::circle(319, 255, 35, $black);
            Draw::circle(319, 255, 31, $lightGray);
            Draw::circle(319 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_X) * 20),
                255 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_Y) * 20), 25, $black);

            // Draw axis: right joystick
            Draw::circle(475, 255, 35, $black);
            Draw::circle(475, 255, 31, $lightGray);
            Draw::circle(475 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_X) * 20),
                255 + (Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_Y) * 20), 25, $black);

            // Draw axis: left-right triggers
            Draw::rectangle(169, 48, 15, 70, $gray);
            Draw::rectangle(611, 48, 15, 70, $gray);
            Draw::rectangle(169, 48, 15, (((1.0 - Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_LEFT_TRIGGER)) / 2.0) * 70), $red);
            Draw::rectangle(611, 48, 15, (((1.0 - Gamepad::getAxisMovement(Gamepad::PLAYER1, Gamepad::AXIS_RIGHT_TRIGGER)) / 2.0) * 70), $red);
        } else {
            Text::draw("GP1: NOT DETECTED", 280, 180, 20, $gray);

            // TODO: Draw generic gamepad
        }

        Text::draw(sprintf("DETECTED AXIS [%i]:", Gamepad::getAxisCount(Gamepad::PLAYER1)), 10, 50, 10, $maroon);

        for ($i = 0; $i < Gamepad::getAxisCount(Gamepad::PLAYER1); $i++) {
            Text::draw(sprintf("AXIS %i: %.02f", $i, Gamepad::getAxisMovement(Gamepad::PLAYER1, $i)), 20, 70 + 20 * $i, 10, $darkGray);
        }

        if (Gamepad::getButtonPressed() != -1) {
            Text::draw(sprintf("DETECTED BUTTON: %i", Gamepad::getButtonPressed()), 10, 430, 10, $red);
        } else {
            Text::draw("DETECTED BUTTON: NONE", 10, 430, 10, $gray);
        }
    } else {
        Text::draw("GP1: NOT DETECTED", 10, 10, 10, $gray);

        $texXboxPad->draw(0, 0, $lightGray);
    }

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
