<?php

namespace raylib;

/**
 * This is a stub for PHP IDEs, enabling auto-complete and introspection. DO NOT include this file.
 */

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

// Window-related functions

/**
 * Initialize window and OpenGL context
 *
 * @param int $width
 * @param int $height
 * @param string $title
 */
function InitWindow(int $width, int $height, string $title) {}

/**
 * Close window and unload OpenGL context
 */
function CloseWindow() {}

/**
 * Check if window has been initialized successfully
 *
 * @return bool
 */
function IsWindowReady() : bool {}

/**
 * Check if raylib\key\ESCAPE pressed or Close icon pressed
 *
 * @return bool
 */
function WindowShouldClose() : bool {}

/**
 * Check if window has been minimized (or lost focus)
 *
 * @return bool
 */
function IsWindowMinimized() : bool {}


/**
 * Toggle fullscreen mode (only PLATFORM_DESKTOP)
 */
function ToggleFullscreen() {}

/**
 * Set icon for window (only PLATFORM_DESKTOP)
 *
 * @param resource $image
 */
function SetWindowIcon($image) {}

/**
 * Set title for window (only PLATFORM_DESKTOP)
 *
 * @param string $title
 */
function SetWindowTitle(string $title) {}

/**
 * Set window position on screen (only PLATFORM_DESKTOP)
 *
 * @param int $x
 * @param int $y
 */
function SetWindowPosition(int $x, int $y) {}

/**
 * Set monitor for the current window (fullscreen mode)
 *
 * @param int $monitor
 */
function SetWindowMonitor(int $monitor) {}

/**
 * Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
 *
 * @param int $width
 * @param int $height
 */
function SetWindowMinSize(int $width, int $height) {}

/**
 * Set window dimensions
 */
function SetWindowSize(int $width, int $height) {}

/**
 * Get current screen width
 *
 * @return int
 */
function GetScreenWidth() : int {}

/**
 * Get current screen height
 *
 * @return int
 */
function GetScreenHeight() : int {}

/**
 * Load image from file into CPU memory (RAM)
 *
 * @param string $fileName
 *
 * @return resource
 */
function LoadImage(string $fileName) {}


// Drawing-related functions

/**
 * Set background color (framebuffer clear color)
 *
 * @param array $color
 */
function ClearBackground(array $color) {}

/**
 * Setup canvas (framebuffer) to start drawing
 */
function BeginDrawing() {}

/**
 * End canvas drawing and swap buffers (double buffering)
 */
function EndDrawing() {}



/**
 * Load texture from image data
 *
 * @param resource $image
 *
 * @return resource
 */
function LoadTextureFromImage($image) {}

/**
 * Unload image from CPU memory (RAM)
 *
 * @param resource $image
 */
function UnloadImage($image) {}

/**
 * Unload texture from GPU memory (VRAM)
 *
 * @param resource $texture
 */
function UnloadTexture($texture) {}


/**
 * Draw a Texture2D
 *
 * @param resource $texture
 * @param int $posX
 * @param int $posY
 * @param array $tint
 */
function DrawTexture($texture, int $posX, int $posY, $tint) {}


/**
 * Get width of texture
 *
 * @param resource $texture
 *
 * @return int
 */
function TextureGetWidth($texture) : int {}

/**
 * Get height of texture
 *
 * @param resource $texture
 *
 * @return int
 */
function TextureGetHeight($texture) : int {}

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// Text drawing functions

/**
 * Draw text (using default font)
 *
 * @param string $text
 * @param int $posX
 * @param int $posY
 * @param int $fontSize
 * @param array $color
 */
function DrawText(string $text, int $posX, int $posY, int $fontSize, array $color) {}