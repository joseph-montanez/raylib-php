<?php

namespace raylib;

/**
 * Class Timming
 * @package raylib
 */
class Timming
{
    /**
     * Set target FPS (maximum)
     *
     * {@internal void SetTargetFPS(int fps); }}
     *
     * @param int $fps
     *
     * @return void
     */
    public static function setTargetFPS(int $fps) : void {}

    /**
     * Returns current FPS
     *
     * {@internal int GetFPS(void); }}
     *
     * @return int
     */
    public static function getFPS() : int {}

    /**
     * Returns time in seconds for last frame drawn
     *
     * {@internal float GetFrameTime(void); }}
     *
     * @return float
     */
    public static function getFrameTime() : float {}

    /**
     * Returns elapsed time in seconds since InitWindow()
     *
     * {@internal double GetTime(void); }}
     *
     * @return float
     */
    public static function getTime() : float {}
}