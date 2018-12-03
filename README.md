# raylib-php

PHP 7.x bindings for raylib, a simple and easy-to-use library to learn video games programming (www.raylib.com)

This is currently a work-in-progress and bindings are not complete and are likely to change. Progress of binding can be tracked via
[MAPPING.md](MAPPING.md)

# Example

![Texture Image Loading](img/textures-image-loading.png)

```php
<?php

use raylib\Color;
use raylib\Draw;
use raylib\Text;
use raylib\Timming;
use raylib\Window;

// Initialization
//--------------------------------------------------------------------------------------
$screenWidth  = 800;
$screenHeight = 450;
$lightGray    = new Color(245, 245, 245, 255);
$gray         = new Color(200, 200, 200, 255);

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

    Draw::clearBackground($lightGray);

    Text::draw("Congrats! You created your first window!", 190, 200, 20, $gray);

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

    php.exe -dextension=modules/php7raylib-2.0.0-dev.dll examples/textures/textures_image_loading.php