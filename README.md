#raylib-php

PHP 7.x bindings for raylib, a simple and easy-to-use library to learn videogames programming (www.raylib.com)

This is currently a work-in-progress and bindings are not complete.

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