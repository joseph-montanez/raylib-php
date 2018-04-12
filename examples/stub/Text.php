<?php

namespace raylib;


class Text
{

    /**
     * Shows current FPS
     *
     * @param int $posX
     * @param int $posY
     *
     * {@internal void DrawFPS(int posX, int posY); }}
     */
    public static function drawFps(int $posX, int $posY) : void {}

    /**
     * Draw text (using default font)
     *
     * @param string $text
     * @param int    $posX
     * @param int    $posY
     * @param int    $fontSize
     * @param array  $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * {@internal void DrawText(const char *text, int posX, int posY, int fontSize, Color color); }}
     */
    public static function draw(string $text, int $posX, int $posY, int $fontSize, array $color) : void {}

    /**
     * Measure string width for default font
     *
     * @param string $text
     * @param int    $fontSize
     *
     * {@internal int MeasureText(const char *text, int fontSize); }}
     *
     * @return int
     */
    public static function measure(string $text, int $fontSize) : int {}
}