#raylib-php

PHP 7.x bindings for raylib, a simple and easy-to-use library to learn videogames programming (www.raylib.com)

This is currently a work-in-progress and bindings are not complete and are likely to change.

# Example

```php
<?php

require_once __DIR__ . '/../raylib-colors.php';

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

raylib\InitWindow($screenWidth, $screenHeight, "raylib [textures] example - image loading");

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

$image = new raylib\Image(__DIR__  . '/resources/raylib_logo.png');     // Loaded in CPU memory (RAM)
$texture = $image->toTexture();                                         // Image converted to texture, GPU memory (VRAM)

unset($image);    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

$texture_x = $screenWidth / 2 - $texture->width() / 2;
$texture_y = $screenHeight / 2 - $texture->height() / 2;
//---------------------------------------------------------------------------------------

// Main game loop
while (!raylib\WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------


    // Draw
    //----------------------------------------------------------------------------------
    raylib\BeginDrawing();

    raylib\ClearBackground(raylib\RAYWHITE);

    $texture->draw($texture_x, $texture_y, raylib\WHITE);

    raylib\DrawText("this IS a texture loaded from an image!", 300, 370, 10, raylib\GRAY);


    raylib\EndDrawing();
    //----------------------------------------------------------------------------------

}

// De-Initialization
//--------------------------------------------------------------------------------------
raylib\CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
```

# License

raylib-php is licensed under an unmodified zlib/libpng license, which is an OSI-certified, 
BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
	
*Copyright (c) 2017 Joseph Montanez ([@joseph-montanez](https://twitter.com/shabb_jm))*

## How To Build PHP Extension


### MacOS & Linux

    phpize
    ./configure
    make

## How To Run raylib PHP Extension

### MacOS & Linux

    php -dextension=modules/raylib.so examples/textures/textures_image_loading.php