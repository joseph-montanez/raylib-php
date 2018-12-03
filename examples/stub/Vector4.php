<?php

namespace raylib;

/**
 * Class Vector4
 * Color type, RGBA (32bit)
 * @package raylib
 *
 * @property-read float $x        Red - Unsigned max 255
 * @property-read float $y        Green - Unsigned max 255
 * @property-read float $z        Blue - Unsigned max 255
 * @property-read float $w        Alpha - Unsigned max 255
 */
class Vector4
{
    /**
     * Color constructor.
     *
     * @param float $x Red
     * @param float $y Green
     * @param float $z Blue
     * @param float $w Alpha
     */
    public function __construct(float $x, float $y, float $z, float $w) {}
}