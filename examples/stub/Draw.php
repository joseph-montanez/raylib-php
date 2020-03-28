<?php

namespace raylib;

/**
 * Class Draw
 * @package raylib
 */
class Draw
{

    /**
     * Set background color (framebuffer clear color)
     *
     * @param \raylib\Color $color The color
     *
     * @return void
     */
    public static function clearBackground(Color $color): void
    {
    }

    /**
     * Setup canvas (framebuffer) to start drawing
     *
     * @return void
     */
    public static function begin(): void
    {
    }

    /**
     * End canvas drawing and swap buffers (double buffering)
     */
    public static function end(): void
    {
    }

    /**
     * @param Camera2D $camera3d
     *
     * @return void
     */
    public static function beginMode2d(Camera2D $camera3d): void
    {
    }

    /**
     * Ends 2D mode with custom camera3d
     *
     * @return void
     */
    public static function endMode2d(): void
    {
    }

    /**
     * Initializes 3D mode with custom camera3d (3D)
     *
     * @param Camera3D $camera3d
     *
     * @return void
     */
    public static function beginMode3d(Camera3D $camera3d): void
    {
    }

    /**
     * Ends 3D mode and returns to default 2D orthographic mode
     *
     * @return void
     */
    public static function endMode3d(): void
    {
    }

    /**
     * Begin scissor mode (define screen area for following drawing)
     *
     * @param int $x
     * @param int $y
     * @param int $width
     * @param int $height
     *
     * @return void
     */
    public static function beginScissorMode(int $x, int $y, int $width, int $height): void
    {
    }

    /**
     * End scissor mode
     *
     * @return void
     */
    public static function endScissorMode(): void
    {
    }

    /**
     * @param Vector2       $center
     * @param float         $radius
     * @param \raylib\Color $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public static function circleV(Vector2 $center, float $radius, Color $color): void
    {
    }

    /**
     * Draw a pixel
     *
     * @param int           $posX
     * @param int           $posY
     * @param \raylib\Color $color The color
     *
     * @return void
     */
    public static function pixel(int $posX, int $posY, Color $color): void
    {
    }

    /**
     * Draw a pixel (Vector version)
     *
     * @param array         $position The position to place the pixel - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color $color    The color
     *
     * @return void
     */
    public static function pixelV(array $position, Color $color): void
    {
    }

    /**
     * Draw a line
     *
     * @param int           $startPosX
     * @param int           $startPosY
     * @param int           $endPosX
     * @param int           $endPosY
     * @param \raylib\Color $color The color
     *
     * @return void
     */
    public static function line(int $startPosX, int $startPosY, int $endPosX, int $endPosY, Color $color): void
    {
    }

    /**
     * Draw a line (Vector version)
     *
     * @param Vector2       $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param Vector2       $endPos   The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color $color    The color
     *
     * @return void
     */
    public static function lineV(Vector2 $startPos, Vector2 $endPos, Color $color): void
    {
    }

    /**
     * Draw a line defining thickness
     *
     * @param Vector2       $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param Vector2       $endPos   The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param float         $thick
     * @param \raylib\Color $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function lineEx(Vector2 $startPos, Vector2 $endPos, float $thick, Color $color): void
    {
    }

    /**
     * Draw a line using cubic-bezier curves in-out
     *
     * @param Vector2       $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param Vector2       $endPos   The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param float         $thick
     * @param \raylib\Color $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function lineBezier(Vector2 $startPos, Vector2 $endPos, float $thick, Color $color): void
    {
    }

    /**
     * Draw a color-filled circle
     *
     * @param int           $centerX
     * @param int           $centerY
     * @param float         $radius
     * @param \raylib\Color $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circle(int $centerX, int $centerY, float $radius, Color $color): void
    {
    }

    /**
     * Draw a gradient-filled circle
     *
     * @param int           $centerX
     * @param int           $centerY
     * @param float         $radius
     * @param \raylib\Color $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circleGradient(int $centerX, int $centerY, float $radius, Color $color1, Color $color2): void
    {
    }

    /**
     * Draw circle outline
     *
     * @param int           $centerX
     * @param int           $centerY
     * @param float         $radius
     * @param \raylib\Color $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circleLines(int $centerX, int $centerY, float $radius, Color $color): void
    {
    }

    /**
     * Draw a color-filled rectangle
     *
     * @param int           $posX
     * @param int           $posY
     * @param int           $width
     * @param int           $height
     * @param \raylib\Color $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangle(int $posX, int $posY, int $width, int $height, Color $color): void
    {
    }

    /**
     * Draw a color-filled rectangle (Vector version)
     *
     * @param \raylib\Vector2 $position The position to place the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Vector2 $size     The size of the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color   $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleV(Vector2 $position, Vector2 $size, Color $color): void
    {
    }

    /**
     * Draw a color-filled rectangle
     *
     * @param \raylib\Rectangle $rec   Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Color     $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleRec(Rectangle $rec, Color $color): void
    {
    }

    /**
     * Draw a color-filled rectangle with pro parameters
     *
     * @param \raylib\Rectangle $rec    Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Vector2   $origin The origin of the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param float             $rotation
     * @param \raylib\Color     $color  The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectanglePro(Rectangle $rec, Vector2 $origin, float $rotation, Color $color): void
    {
    }

    /**
     * Draw a vertical-gradient-filled rectangle
     *
     * @param int           $posX
     * @param int           $posY
     * @param int           $width
     * @param int           $height
     * @param \raylib\Color $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientV(int $posX, int $posY, int $width, int $height, Color $color1, Color $color2): void
    {
    }

    /**
     * Draw a horizontal-gradient-filled rectangle
     *
     * @param int           $posX
     * @param int           $posY
     * @param int           $width
     * @param int           $height
     * @param \raylib\Color $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientH(int $posX, int $posY, int $width, int $height, Color $color1, Color $color2): void
    {
    }

    /**
     * Draw a gradient-filled rectangle with custom vertex colors
     *
     * @param \raylib\Rectangle $rec  Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Color     $col1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color     $col2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color     $col3 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param \raylib\Color     $col4 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientEx(Rectangle $rec, Color $col1, Color $col2, Color $col3, Color $col4): void
    {
    }

    /**
     * Draw rectangle outline
     *
     * @param int   $posX
     * @param int   $posY
     * @param int   $width
     * @param int   $height
     * @param Color $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleLines(int $posX, int $posY, int $width, int $height, Color $color): void
    {
    }

    /**
     * Draw rectangle outline with extended parameters
     *
     * @param \raylib\Rectangle $rec   Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param int               $lineThick
     * @param \raylib\Color     $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleLinesEx(Rectangle $rec, int $lineThick, Color $color): void
    {
    }

    /**
     * Draw a color-filled triangle
     *
     * @param \raylib\Vector2 $v1    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Vector2 $v2    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Vector2 $v3    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color   $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function triangle(Vector2 $v1, Vector2 $v2, Vector2 $v3, Color $color): void
    {
    }

    /**
     * Draw triangle outline
     *
     * @param \raylib\Vector2 $v1    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Vector2 $v2    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Vector2 $v3    The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color   $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function triangleLines(Vector2 $v1, Vector2 $v2, Vector2 $v3, Color $color): void
    {
    }

    /**
     * Draw a regular polygon (Vector version)
     *
     * @param \raylib\Vector2 $center The center of the polygon - Vector2 array ['x' => 0, 'y' => 0]
     * @param int             $sides
     * @param float           $radius
     * @param float           $rotation
     * @param \raylib\Color   $color  The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function poly(Vector2 $center, int $sides, float $radius, float $rotation, Color $color): void
    {
    }

    /**
     * Draw a closed polygon defined by points
     *
     * @param \raylib\Vector2[] $points The array of points - [Vector2 array ['x' => 0, 'y' => 0]]
     * @param int               $numPoints
     * @param \raylib\Color     $color  The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function polyEx(array $points, int $numPoints, Color $color): void
    {
    }

    /**
     * Draw polygon lines
     *
     * @param \raylib\Vector2[] $points The array of points - [Vector2 array ['x' => 0, 'y' => 0]]
     * @param int               $numPoints
     * @param \raylib\Color     $color  The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function polyExLines(array $points, int $numPoints, Color $color): void
    {
    }
}
