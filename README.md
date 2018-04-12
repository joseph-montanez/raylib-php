# raylib-php

PHP 7.x bindings for raylib, a simple and easy-to-use library to learn videogames programming (www.raylib.com)

This is currently a work-in-progress and bindings are not complete and are likely to change.

# Example

```php
<?php

use raylib\Text;
use raylib\Draw;
use raylib\Image;
use raylib\Window;

require_once __DIR__ . '/../raylib-colors.php';

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

Window::init($screenWidth, $screenHeight, "raylib [textures] example - image loading");

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

$image = new Image(__DIR__  . '/resources/raylib_logo.png');    // Loaded in CPU memory (RAM)
$texture = $image->toTexture();                                 // Image converted to texture, GPU memory (VRAM)

unset($image);    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

$texture_x = $screenWidth / 2 - $texture->width / 2;
$texture_y = $screenHeight / 2 - $texture->height / 2;
//---------------------------------------------------------------------------------------

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

    Draw::clearBackground(raylib\RAYWHITE);

    $texture->draw($texture_x, $texture_y, raylib\WHITE);

    Text::draw("this IS a texture loaded from an image!", 300, 370, 10, raylib\GRAY);


    Draw::end();
    //----------------------------------------------------------------------------------

}

// De-Initialization
//--------------------------------------------------------------------------------------
Window::close();        // Close window and OpenGL context
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

### Windows

Windows requires compiling with PHP sources, you will still get a .dll in the end.

    cmake clean
    buildconf --force
    configure --enable-raylib
    nmake

## How To Run raylib PHP Extension

### MacOS & Linux

    php -dextension=modules/raylib.so examples/textures/textures_image_loading.php

### Windows

    php.exe -dextension=modules/php7raylib-1.9.4-dev.dll examples/textures/textures_image_loading.php