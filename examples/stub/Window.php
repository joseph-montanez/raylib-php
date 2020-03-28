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
     * Check if raylib\Input\Key::ESCAPE pressed or Close icon pressed
     *
     * @return bool
     */
    public static function shouldClose() : bool {}

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
     * Check if window has been minimized (or lost focus)
     *
     * @return bool
     */
    public static function isMinimized() : bool {}

    /**
     * Check if window has been resized
     *
     * @return bool
     */
    public static function isWindowResized() : bool {}

    /**
     * Check if window is currently hidden
     *
     * @return bool
     */
    public static function isWindowHidden() : bool {}

    /**
     * Check if window is currently fullscreen
     *
     * @return bool
     */
    public static function isWindowFullscreen() : bool {}

    /**
     * Toggle fullscreen mode (only PLATFORM_DESKTOP)
     */
    public static function toggleFullscreen() {}

    /**
     * Toggle fullscreen mode (only PLATFORM_DESKTOP)
     */
    public static function unhideWindow() {}

    /**
     * Show the window
     */
    public static function hideWindow() {}

    /**
     * Hide the window
     *
     * @param \raylib\Image $image
     */
    public static function setIcon(\raylib\Image $image) {}

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
    public static function getScreenWidth() : int {}

    /**
     * Get current screen height
     *
     * @return int
     */
    public static function getScreenHeight() : int {}

    /**
     * Get number of connected monitors
     *
     * @return int
     */
    public static function getMonitorCount() : int {}

    /**
     * Get primary monitor width
     *
     * @param int $monitor
     *
     * @return int
     */
    public static function getMonitorWidth(int $monitor) : int {}

    /**
     * Get primary monitor height
     *
     * @param int $monitor
     *
     * @return int
     */
    public static function getMonitorHeight(int $monitor) : int {}

    /**
     * Get primary monitor physical width in millimetres
     *
     * @param int $monitor
     *
     * @return int
     */
    public static function getMonitorPhysicalWidth(int $monitor) : int {}

    /**
     * Get primary monitor physical height in millimetres
     *
     * @param int $monitor
     *
     * @return int
     */
    public static function getMonitorPhysicalHeight(int $monitor) : int {}

    /**
     * Get window position XY on monitor
     */
    public static function getWindowPosition() : \raylib\Vector2 {}

    /**
     * Get the human-readable, UTF-8 encoded name of the primary monitor
     *
     * @param int $monitor
     *
     * @return string
     */
    public static function getMonitorName(int $monitor) : string {}

    /**
     * Get clipboard text content
     *
     * @param int $monitor
     *
     * @return string
     */
    public static function getClipboardText(int $monitor) : string {}

    /**
     * Set clipboard text content
     *
     * @param string $text
     *
     * @return void
     */
    public static function setClipboardText(string $text) : void {}
}
