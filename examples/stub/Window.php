<?php

namespace raylib;


/**
 * Class Window
 * @package raylib
 */
class Window {

    /**
     * Initialize window and OpenGL context
     *
     * @param int $width
     * @param int $height
     * @param string $title
     */
    public static function init(int $width, int $height, string $title) {}

    /**
     * Close window and unload OpenGL context
     */
    public static function close() {}

    /**
     * Check if window has been initialized successfully
     *
     * @return bool
     */
    public static function isReady() : bool {}

    /**
     * Check if raylib\Input\Key::ESCAPE pressed or Close icon pressed
     *
     * @return bool
     */
    public static function shouldClose() : bool {}

    /**
     * Check if window has been minimized (or lost focus)
     *
     * @return bool
     */
    public static function isMinimized() : bool {}


    /**
     * Toggle fullscreen mode (only PLATFORM_DESKTOP)
     */
    public static function toggleFullscreen() {}

    /**
     * Set icon for window (only PLATFORM_DESKTOP)
     *
     * @param resource $image
     */
    public static function setIcon($image) {}

    /**
     * Set title for window (only PLATFORM_DESKTOP)
     *
     * @param string $title
     */
    public static function setTitle(string $title) {}

    /**
     * Set window position on screen (only PLATFORM_DESKTOP)
     *
     * @param int $x
     * @param int $y
     */
    public static function setPosition(int $x, int $y) {}

    /**
     * Set monitor for the current window (fullscreen mode)
     *
     * @param int $monitor
     */
    public static function setMonitor(int $monitor) {}

    /**
     * Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
     *
     * @param int $width
     * @param int $height
     */
    public static function setMinSize(int $width, int $height) {}

    /**
     * Set window dimensions
     *
     * @since 1.9.7-dev
     */
    public static function setSize(int $width, int $height) {}

    /**
     * Get current screen width
     *
     * @return int
     */
    public static function GetScreenWidth() : int {}

    /**
     * Get current screen height
     *
     * @return int
     */
    public static function GetScreenHeight() : int {}
}