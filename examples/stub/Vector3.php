<?php

namespace raylib;

/**
 * Class Vector3
 * Color type, RGBA (32bit)
 * @package raylib
 *
 * @property-read float $x        Red - Unsigned max 255
 * @property-read float $y        Green - Unsigned max 255
 * @property-read float $z        Blue - Unsigned max 255
 */
class Vector3
{
    /**
     * Color constructor.
     *
     * @param float $x Red
     * @param float $y Green
     * @param float $z Blue
     */
    public function __construct(float $x, float $y, float $z) {}
}