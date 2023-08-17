# raylib-php

PHP 8.x bindings for RayLib, a simple and easy-to-use library to learn video g

This is currently a work-in-progress and bindings are not complete and are likely to change.

- raylib.h - See [Not yet implemented](#not-yet-implemented)
- raymath.h - TODO Extra mathy stuff
- raygui.h - TODO API for drawing GUI
- physac.h - TODO More complex collision detection, more than built-in collision detection

## Other PHP RayLib Bindings

- [PHP Raylib FFI](https://github.com/nawarian/raylib-ffi) - Uses PHP's built-in FFI (Foreign Function Interface) to
  connect directly to the shared RayLib.dll/.so file. This will be slower than a native binding.

## Isn't PHP A Terrible Choice For Games?

Here are some common misconceptions:

- **PHP has no multi-threading**. There are native PHP extensions to enable this, pThreads and now a easier way to tackle this issue Parallel - https://github.com/krakjoe/parallel
- **PHP is too slow**. Since PHP 7 a lot of things have gotten faster, so it can outperform Python and NodeJS in some area. PHP 8 now include JIT and provides even more performance.
- **Object Oriented Programming in PHP is horrible**. Since PHP 5.4+ you get a lot of feature parity and since PHP 7 you now get type checking.
- **Garbage Collection IS ... GARBAGE** - Until PHP 7.3 this was true. Running PHP in a tight loop for hours/days on end would hit a point where PHP could spend more time doing GC than anything else. This has been greatly improved.
- **PHP Has No Code Reload** - Well not built-in. But, any language with `eval` can have code reloading. With that said I have code reloading using [SoftMocks](https://github.com/badoo/soft-mocks), but there is also a native PHP extension [Runkit7](https://github.com/runkit7/runkit7).
  ![Code Reload](img/hot-reload.gif)

## Example

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

InitWindow($screenWidth, $screenHeight, "raylib [core] example - basic window");

SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())        // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();

    ClearBackground($lightGray);

    DrawText("Congrats! You created your first window!", 190, 200, 20, $gray);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
```

## Autocomplete

Classes and method calls are available via a stub repository. Its contains all the classes and methods so you get information on everything and anything implemented.

![IDE Autocomplete](img/autocomplete.png)

Install via composer:

    composer require joseph-montanez/raylib-php-stub

More information on the stubs can be found here at the repository [RayLib-PHP-Stubs](https://github.com/joseph-montanez/RayLib-PHP-Stubs)

## License

raylib-php is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

*Copyright (c) 2017 Joseph Montanez ([@joseph-montanez](https://twitter.com/shabb_jm))*

## Binary Releases

[Windows PHP Extension DLL](https://github.com/joseph-montanez/raylib-php/releases)

## API Differences

Raylib-PHP closely follows the RayLib's C-API with a few exceptions due to clashing function names:

- ImageCopy is renamed to rlImageCopy due to collision with GDI
- ImageCrop is renamed to rlImageCrop due to collision with GDI
- Raylib static colors i.e RAYWHITE are renamed to raylib\Color::RAYWHITE()

## API Limitation

The PHP RayLib implementation has two glaring limitations.

- Not all object properties are read and write, for example `/raylib/Image::width` is a read-only property but `/raylib/Vector2::x` is a read/write property. When you want to alter a property that is read-only there should be method calls such as `/raylib/Image::resize()` that will adjust the properties for you.
- All RayLib object assignment i.e `$player->position = $position` will **not copy** the variable but instead **link** the property. So if you want to copy the data instead, you need to use PHP's clone feature `clone` i.e `$player->position = clone $position`.

## How To Build PHP Extension

Windows is by far the hardest platform to support and build for. Please use the binaries for Windows instead unless you want to commit fixes to this repo.

### Linux

#### Ubuntu 19.10+

    sudo apt-get install -y libx11-dev xorg-dev

#### Build

    phpize
    ./configure
    make

#### Mac OS

    brew install raylib@4.5.0

Unfortunately, macOS Brew via `brew install php@8.2` installs the non thread safe (nts) version which if you want to use 
parallels the multi-threaded extension for php, you will need to compile and install PHP manually.

    git clone https://github.com/php/php-src.git
    git checkout php-8.2.8
    ./buildconf --force
    ./configure --enable-zts --with-iconv=$(brew --prefix libiconv) --enable-opcache
    make
    sudo make install

#### Build

    phpize
    ./configure
    make

### Windows

Windows requires compiling with PHP sources (Currently Visual Studio 2019 needed), you will still get a .dll in the end.

You will need to also compile RayLib as well. At the time writing I am using Visual Studio 2019 compiler, since PHP 8 requires this. Once compiled paste the following files:

(Please note your Raylib and PHP paths may be different)

**Static Libs**

    C:\src\raylib-4.5.0\projects\VS2022\build\raylib\bin\x64\raylib.lib -> C:\php-sdk\phpdev\vc16\x64\deps\lib\raylib.lib

**GLFW Includes**

    C:\src\raylib-4.5.0\src\external\glfw\include\GLFW\glfw3.h -> C:\php-sdk\phpmaster\vc16\x64\deps\include\GLFW\glfw3.h
    C:\src\raylib-4.5.0\src\external\glfw\include\GLFW\glfw3native.h -> C:\php-sdk\phpmaster\vc16\x64\deps\include\GLFW\glfw3native.h

**RayLib Includes**

    C:\src\raylib-4.5.0\cmake-build-debug\src\raudio.h -> C:\php-sdk\phpmaster\vc15\x64\deps\include\raudio.h
    C:\src\raylib-4.5.0\cmake-build-debug\src\raylib.h -> C:\php-sdk\phpmaster\vc15\x64\deps\include\raylib.h
    C:\src\raylib-4.5.0\cmake-build-debug\src\raymath.h -> C:\php-sdk\phpmaster\vc15\x64\deps\include\raymath.h
    C:\src\raylib-4.5.0\cmake-build-debug\src\rlgl.h -> C:\php-sdk\phpmaster\vc15\x64\deps\include\rlgl.h

Once you have PHP & Raylib setup you can then compile the extension

    %comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    cd C:/php-sdk
    phpsdk-vs16-x64.bat
    cd phpdev\vs16\x64\raylib-php
    ..\php-8.2.8-devel-vs16-x64-ts\phpize.bat
    configure
    nmake

## How To Run raylib PHP Extension

### MacOS & Linux

    php -dextension=modules/raylib.so examples/textures/textures_image_loading.php

### Windows

    php-win.exe -dextension=x64/Release_TS/php_raylib.dll examples/textures/textures_image_loading.php


## Not Yet Implemented

These are methods that may be able to work later on with more development. For example callbacks are generally not 
supported yet, but can be later.

 - GetRenderWidth
 - GetRenderHeight
 - TraceLog
 - SetTraceLogCallback
 - SetSaveFileDataCallback
 - SetLoadFileTextCallback
 - SetSaveFileTextCallback
 - SetLoadFileDataCallback
 - SaveFileData
 - MemFree
 - SetWindowOpacity
 - GetPixelColor
 - SetPixelColor
 - GenImageFontAtlas
 - UpdateMeshBuffer
 - SetShaderValue
 - SetShaderValueV
 - UpdateTexture
 - UpdateTextureRec
 - UpdateSound
 - UpdateAudioStream
 - SetAudioStreamCallback
 - AttachAudioStreamProcessor
 - DetachAudioStreamProcessor
 - AttachAudioMixedProcessor
 - DetachAudioMixedProcessor


## Benchmarks

Using the Bunnymark textures 100,000 max, 144 frames per second. Any language / extension that hits 85 FPS is the limit
of the GPU of the test machine. All run with "Apple" for **kind** (M1/M2) native architect.

M1 Mac Mini - 16GB RAM - macOS Ventura 13.4.1

 - **Compiled** - Must be compiled to a binary to run the application
 - **Dynamic** - Can be interpreted for immediately running the application

| Language                            | Typed    | Extension                | FPS    | Memory | CPU  | GPU |
|-------------------------------------|----------|--------------------------|--------|--------|------|-----|
| C (CMake Release)                   | compiled | Native                   | 85 FPS | 47 MB  | 64%  | 90% |
| Zig 0.11.0 (ReleaseFast) (Arena)    | compiled | raylib.zig               | 85 FPS | 54 MB  | 60%  | 90% |
| Rust (Release)                      | compiled | bitten2up/raylib-rs      | 85 FPS | 48 MB  | 67%  | 90% |
| Go 2.20 (Release)                   | compiled | gen2brain/raylib-go      | 85 FPS | 55 MB  | 73%  | 90% |
| C# 11 .Net 7                        | compiled | raylib-cs                | 85 FPS | 68 MB  | 75%  | 90% |
| Nim 2.0 (Release)                   | compiled | planetis-m/naylib        | 75 FPS | 49 MB  | 70%  | 90% |
| Haxe 4.3.1 (no-debug, HXCPP_ARM64)* | compiled | raylib-haxe              | 47 FPS | 128 MB | 87%  | 66% |
| NodeJS 20                           | dynamic  | node-raylib              | 44 FPS | 134 MB | 100% | 80% |
| PHP 8.2 (Jit)                       | dynamic  | raylib-php               | 41 FPS | 257 MB | 100% | 60% |
| PHP 8.2                             | dynamic  | raylib-php               | 27 FPS | 242 MB | 100% | 57% |
| Python 3.11**                       | dynamic  | raylib-python-cffi       | 10 FPS | 100 MB | 100% | 35% |
| Lua (LuaJIT 2.1.0-beta3) (-O2)***   | dynamic  | TSnake41/raylib-lua      | 5 FPS  | 113 MB | 100% | 31% |

1) ***Raylib-Haxe** does not compile out of the box and fixes are to run.

2) ****Python - raylib-python-cffi** Uses FFI which is slower than a ctypes integration

3) *****TSnake41/raylib-lua** Does not currently compile on Arm64 (M1/M2) out of the box, and JIT isn't working as expected on this platform as it should be faster.