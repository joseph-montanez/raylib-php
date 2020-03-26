<?php

namespace raylib;


class Collision
{

//    // Basic shapes collision detection functions
//    RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           // Check collision between two rectangles
//    RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        // Check collision between two circles
//    RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         // Check collision between circle and rectangle
//    RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         // Get collision rectangle for two rectangles collision
//    RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         // Check if point is inside rectangle
//    RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       // Check if point is inside circle
//    RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               // Check if point is inside a triangle


    /**
     * Check collision between two rectangles
     *
     * @param \raylib\Rectangle $rec1 The rectangle to check
     * @param \raylib\Rectangle $rec2 The rectangle to check
     *
     * {@internal RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2); }}
     *
     * @return bool
     */
    public static function checkRecs(Rectangle $rec1, Rectangle $rec2): bool
    {
    }

    /**
     * Check collision between two circles
     *
     * @param \raylib\Vector2 $center1
     * @param float   $radius1
     * @param \raylib\Vector2 $center2
     * @param float   $radius2
     *
     * {@internal RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2); }}
     *
     * @return bool
     */
    public static function checkCircles(Vector2 $center1, float $radius1, Vector2 $center2, float $radius2): bool
    {
    }

    /**
     * Check collision between circle and rectangle
     *
     * {@internal RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec); }}
     *
     * @param \raylib\Vector2   $center
     * @param float             $radius
     * @param \raylib\Rectangle $rec
     *
     * @return bool
     */
    public static function checkCircleRec(Vector2 $center, float $radius, Rectangle $rec): bool
    {
    }

    /**
     * Check if point is inside rectangle
     *
     * @param array $point The point to check
     * @param array $rec   The rectangle to check
     *
     * {@internal RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec) }}
     *
     * @return bool
     */
    public static function checkPointRec(Vector2 $point, Rectangle $rec): bool
    {
    }
}
