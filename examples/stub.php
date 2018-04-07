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

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard

/**
 * Detect if a key has been pressed once
 *
 * @param int $key
 *
 * @return bool
 */
function IsKeyPressed(int $key) : bool {}

/**
 * Detect if a key is being pressed
 *
 * @param int $key
 *
 * @return bool
 */
function IsKeyDown(int $key) : bool {}

/**
 * Detect if a key has been released once
 *
 * @param int $key
 *
 * @return bool
 */
function IsKeyReleased(int $key) : bool {}

/**
 * Detect if a key is NOT being pressed
 *
 * @param int $key
 *
 * @return bool
 */
function IsKeyUp(int $key) : bool {}

/**
 * Get latest key pressed
 *
 * @return int
 */
function GetKeyPressed() : int {}

/**
 * Set a custom key to exit program (default is ESC)
 *
 * @param int $key
 */
function SetExitKey(int $key) : void {}

// Input-related functions: gamepads

/**
 * Detect if a gamepad is available
 *
 * @param int $gamepad
 *
 * @return bool
 */
function IsGamepadAvailable(int $gamepad) : bool {}

/**
 * Check gamepad name (if available)
 *
 * @param int $gamepad
 * @param string $name
 *
 * @return bool
 */
function IsGamepadName(int $gamepad, string $name) : bool {}

/**
 * Return gamepad internal name id
 *
 * @param int $gamepad
 *
 * @return string
 */
function GetGamepadName(int $gamepad) : string {}

/**
 * Detect if a gamepad button has been pressed once
 *
 * @param int $gamepad
 * @param int $button
 *
 * @return bool
 */
function IsGamepadButtonPressed(int $gamepad, int $button) : bool {}

/**
 * Detect if a gamepad button is being pressed
 *
 * @param int $gamepad
 * @param int $button
 *
 * @return bool
 */
function IsGamepadButtonDown(int $gamepad, int $button) : bool {}

/**
 * Detect if a gamepad button has been released once
 *
 * @param int $gamepad
 * @param int $button
 *
 * @return bool
 */
function IsGamepadButtonReleased(int $gamepad, int $button) : bool {}

/**
 * Detect if a gamepad button is NOT being pressed
 *
 * @param int $gamepad
 * @param int $button
 *
 * @return bool
 */
function IsGamepadButtonUp(int $gamepad, int $button) : bool {}

/**
 * Get the last gamepad button pressed
 *
 * @return int
 */
function GetGamepadButtonPressed() : int {}

/**
 * Return gamepad axis count for a gamepad
 *
 * @param int $gamepad
 *
 * @return int
 */
function GetGamepadAxisCount(int $gamepad) : int {}

/**
 * Return axis movement value for a gamepad axis
 *
 * @param int $gamepad
 * @param int $axis
 *
 * @return float
 */
function GetGamepadAxisMovement(int $gamepad, int $axis) : float {}

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image/Texture2D data loading/unloading/saving functions

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


class Image {
    public function __construct(string $fileName) {}

    /**
     * Load texture from image data
     *
     * @return Texture
     */
    public function toTexture() : Texture {}

    /**
     * Image raw data
     *
     * @return array
     */
    public function data() : array {}

    /**
     * Image base width
     *
     * @return int
     */
    public function width() : int {}

    /**
     * Image base height
     *
     * @return int
     */
    public function height() : int {}

    /**
     * Image levels, 1 by default
     *
     * @return int
     */
    public function mipmaps() : int {}

    /**
     * Data format (PixelFormat type)
     *
     * @return int
     */
    public function format() : int {}

}

class Texture {
    public function __construct(string $fileName) {}

    /**
     * Texture base width
     *
     * @return int
     */
    public function width() : int {}

    /**
     * Texture base height
     *
     * @return int
     */
    public function height() : int {}

    /**
     * OpenGL texture id
     *
     * @return int
     */
    public function id() : int {}

    /**
     * Mipmap levels, 1 by default
     *
     * @return int
     */
    public function mipmaps() : int {}

    /**
     * Data format (PixelFormat type)
     *
     * @return int
     */
    public function format() : int {}
}