<?php

namespace raylib;


/**
 * Class Camera3D
 * @package raylib
 *
 * @property-read array $position
 * @property-read array $target
 * @property-read array $up
 * @property-read float $fovy
 * @property-read int $type
 */
class Camera3D
{
    const PERSPECTIVE = 0;
    const ORTHOGRAPHIC = 1;

}