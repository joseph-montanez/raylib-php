<?php

namespace raylib;


class Collision
{
    /**
     * Check if point is inside rectangle
     *
     * @param array $point The point to check - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $rec   The rectangle to check - Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     *
     * {@internal bool CheckCollisionPointRec(Vector2 point, Rectangle rec) }}
     *
     * @return bool
     */
    public static function checkPointRec(array $point, array $rec) : bool {}
}