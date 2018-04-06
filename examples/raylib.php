<?php
// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

raylib\InitWindow($screenWidth, $screenHeight, "raylib [core] example - basic window");

$windowIcon = raylib\LoadImage(__DIR__  . '/raylib_logo.png');
$logo = raylib\LoadTexture(__DIR__  . '/raylib_logo.png');
$logoCenterX = $screenWidth / 2 - (128 / 2);
$white = [255, 255, 255, 255];
$raywhite = [245, 245, 245, 255];
$lightgray = [200, 200, 200, 255];

raylib\SetTargetFPS(60);
raylib\SetWindowIcon($windowIcon);
//--------------------------------------------------------------------------------------

// Main game loop
while (!raylib\WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
    $fps = raylib\GetFPS();


    // Draw
    //----------------------------------------------------------------------------------
    raylib\BeginDrawing();

        raylib\ClearBackground($raywhite);

        raylib\DrawTexture($logo, rand($logoCenterX - 10, $logoCenterX + 10), rand(40, 50), $white);
        raylib\DrawText("Congrats! You created your first window! - $fps", 190, 200, 20, $lightgray);
        raylib\DrawFPS(10, 10);



    raylib\EndDrawing();
    //----------------------------------------------------------------------------------

}

// De-Initialization
//--------------------------------------------------------------------------------------
raylib\CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------