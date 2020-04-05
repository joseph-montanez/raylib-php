<?php

// Initialization
//--------------------------------------------------------------------------------------
use raylib\Color;
use raylib\Draw;
use raylib\Font;
use raylib\Input\Key;
use raylib\Input\Mouse;
use raylib\Text;
use raylib\Timming;
use raylib\Window;

$screenWidth = 800;
$screenHeight = 450;

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

Window::init($screenWidth, $screenHeight, "raylib [text] example - font filters");

$msg = "Loaded Font";

// NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

// TTF Font loading with custom generation parameters
$font = Font::fromCustom(__DIR__ . "/resources/KAISG.ttf", 96, 0, 0);

// Generate mipmap levels to use trilinear filtering
// NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
$font->texture->genMipmaps();


$fontSize = $font->baseSize;
$fontPosition = new \raylib\Vector2(40, $screenHeight / 2 - 80);
$textSize = new \raylib\Vector2(0, 0);

// Setup texture scaling filter
$font->texture->setFilter(\raylib\Texture::FILTER_POINT);
$currentFontFilter = 0;      // FILTER_POINT

Timming::setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    $fontSize += Mouse::getWheelMove() * 4.0;

    // Choose font texture filter method
    if (Key::isPressed(Key::ONE)) {
        $font->texture->setFilter(\raylib\Texture::FILTER_POINT);
        $currentFontFilter = 0;
    } else if (Key::isPressed(Key::TWO)) {
        $font->texture->setFilter(\raylib\Texture::FILTER_BILINEAR);
        $currentFontFilter = 1;
    } else if (Key::isPressed(Key::THREE)) {
        // NOTE: Trilinear filter won't be noticed on 2D drawing
        $font->texture->setFilter(\raylib\Texture::FILTER_TRILINEAR);
        $currentFontFilter = 2;
    }

    $textSize = $font->measureText($msg, $fontSize, 0); //MeasureTextEx(font, msg, fontSize, 0);

    if (Key::isDown(Key::LEFT)) {
        $fontPosition->x -= 10;
    } else if (Key::isDown(Key::RIGHT)) {
        $fontPosition->x += 10;
    }

    // Load a dropped TTF file dynamically (at current fontSize)
//    if (IsFileDropped()) {
//        int count = 0;
//            char ** droppedFiles = GetDroppedFiles(&count);
//
//            // NOTE: We only support first ttf file dropped
//            if (IsFileExtension(droppedFiles[0], ".ttf")) {
//                UnloadFont(font);
//                font = LoadFontEx(droppedFiles[0], fontSize, 0, 0);
//                ClearDroppedFiles();
//            }
//        }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    Draw::begin();

    Draw::clearBackground($rayWhite);

    Text::draw("Use mouse wheel to change font size", 20, 20, 10, $gray);
    Text::draw("Use KEY_RIGHT and KEY_LEFT to move text", 20, 40, 10, $gray);
    Text::draw("Use 1, 2, 3 to change texture filter", 20, 60, 10, $gray);
    Text::draw("Drop a new TTF font for dynamic loading", 20, 80, 10, $darkGray);

    $font->draw($msg, $fontPosition, $fontSize, 0, $black);

    // TODO: It seems texSize measurement is not accurate due to chars offsets...
    //DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

    Draw::rectangle(0, $screenHeight - 80, $screenWidth, 80, $lightGray);
    Text::draw(sprintf("Font size: %02.02f", $fontSize), 20, $screenHeight - 50, 10, $darkGray);
    Text::draw(sprintf("Text size: [%02.02f, %02.02f]", $textSize->x, $textSize->y), 20, $screenHeight - 30, 10, $darkGray);
    Text::draw("CURRENT TEXTURE FILTER:", 250, 400, 20, $gray);

    if ($currentFontFilter == 0) Text::draw("POINT", 570, 400, 20, $black);
    else if ($currentFontFilter == 1) Text::draw("BILINEAR", 570, 400, 20, $black);
    else if ($currentFontFilter == 2) Text::draw("TRILINEAR", 570, 400, 20, $black);

    Draw::end();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
//ClearDroppedFiles();        // Clear internal buffers
unset($font);                 // Font unloading
Window::close();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------
