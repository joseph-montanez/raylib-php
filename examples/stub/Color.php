<?php

namespace raylib;

/**
 * Class Color
 * Color type, RGBA (32bit)
 * @package raylib
 *
 * @property-read int $r        Red - Unsigned max 255
 * @property-read int $g        Green - Unsigned max 255
 * @property-read int $b        Blue - Unsigned max 255
 * @property-read int $a        Alpha - Unsigned max 255
 */
class Color
{
    /**
     * Returns hexadecimal value for a Color
     *
     * @param \raylib\Color $color
     *
     * @return int
     */
    public static function toInt(Color $color) : int {}

    /**
     * Returns color normalized as float [0..1]
     *
     * @param \raylib\Color $color
     *
     * @return \raylib\Vector4
     */
    public static function normalize(Color $color) : Vector4 {}

    /**
     * Returns HSV values for a Color
     *
     * @param \raylib\Color $color
     *
     * @return \raylib\Vector3
     */
    public static function toHSV(Color $color) : Vector3 {}

    /**
     * Returns a Color object from hexadecimal value
     *
     * @param int $hexValue
     *
     * @return \raylib\Color
     */
    public static function getColor(int $hexValue) : Color {}

    /**
     * Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
     *
     * @param \raylib\Color $color
     * @param float         $alpha
     *
     * @return \raylib\Color
     */
    public static function fade(Color $color, float $alpha) : Color {}
}