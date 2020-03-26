<?php

namespace raylib;

/**
 * Class Wave
 * Handle .wav files
 * @package raylib
 *
 */
class Audio
{
    /**
     *
     */
    public function __construct()
    {
    }

    /**
     * Initialize audio device and context
     */
    public static function initDevice(): void
    {
    }

    /**
     * Close the audio device and context
     */
    public static function closeDevice(): void
    {
    }

    /**
     * Check if audio device has been initialized successfully
     */
    public static function isDeviceReady(): void
    {
    }

    /**
     * Set master volume (listener)
     *
     * @param float $volume - A valid between 0.0 and 1.0 to reduce volume
     */
    public static function setMasterVolume(float $volume): void
    {
    }
}
