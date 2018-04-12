<?php

namespace raylib;

/**
 * Class Draw
 * @package raylib
 */
class Draw {

    /**
     * Set background color (framebuffer clear color)
     * 
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     * 
     * @return void
     */
    public static function clearBackground(array $color) : void {}

    /**
     * Setup canvas (framebuffer) to start drawing
     *
     * @return void
     */
    public static function begin() : void {}

    /**
     * End canvas drawing and swap buffers (double buffering)
     */
    public static function end() : void {}

    /**
     * @param Camera2D $camera
     *
     * @return void
     */
    public static function begin2dMode(Camera2D $camera) : void {}
    
    /**
     * Ends 2D mode with custom camera
     *
     * @return void
     */
    public static function end2dMode() : void {}

    /**
     * Initializes 3D mode with custom camera (3D)
     * 
     * @param Camera $camera
     *
     * @return void
     */
    public static function begin3dMode(Camera $camera) : void {}

    /**
     * Ends 3D mode and returns to default 2D orthographic mode
     *
     * @return void
     */
    public static function end3dMode() : void {}

    /**
     * Initializes render texture for drawing
     * 
     * @param RenderTexture2D $target
     *
     * @return void
     */
    public static function beginTextureMode(RenderTexture2D $target) : void {}

    /**
     * Ends drawing to render texture
     *
     * @return void
     */
    public static function endTextureMode() : void {}

    /**
     * @param array $center
     * @param float $radius
     * @param array $color  The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public static function circleV(array $center, float $radius, array $color) : void {}

    /**
     * Draw a pixel
     *
     * @param int $posX
     * @param int $posY
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function pixel(int $posX, int $posY, array $color) : void {}

    /**
     * Draw a pixel (Vector version)
     *
     * @param array $position The position to place the pixel - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function pixelV(array $position, array $color) : void {}

    /**
     * Draw a line
     *
     * @param int $startPosX
     * @param int $startPosY
     * @param int $endPosX
     * @param int $endPosY
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function line(int $startPosX, int $startPosY, int $endPosX, int $endPosY, array $color) : void {}

    /**
     * Draw a line (Vector version)
     *
     * @param array $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $endPos The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function lineV(array $startPos, array $endPos, array $color) : void {}

    /**
     * Draw a line defining thickness
     *
     * @param array $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $endPos The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param float $thick
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function lineEx(array $startPos, array $endPos, float $thick, array $color) : void {}

    /**
     * Draw a line using cubic-bezier curves in-out
     *
     * @param array $startPos The start position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $endPos The end position of the line - Vector2 array ['x' => 0, 'y' => 0]
     * @param float $thick
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function lineBezier(array $startPos, array $endPos, float $thick, array $color) : void {}

    /**
     * Draw a color-filled circle
     *
     * @param int $centerX
     * @param int $centerY
     * @param float $radius
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circle(int $centerX, int $centerY, float $radius, array $color) : void {}

    /**
     * Draw a gradient-filled circle
     *
     * @param int $centerX
     * @param int $centerY
     * @param float $radius
     * @param array $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circleGradient(int $centerX, int $centerY, float $radius, array $color1, array $color2) : void {}

    /**
     * Draw circle outline
     *
     * @param int $centerX
     * @param int $centerY
     * @param float $radius
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function circleLines(int $centerX, int $centerY, float $radius, array $color) : void {}

    /**
     * Draw a color-filled rectangle
     *
     * @param int $posX
     * @param int $posY
     * @param int $width
     * @param int $height
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangle(int $posX, int $posY, int $width, int $height, array $color) : void {}

    /**
     * Draw a color-filled rectangle (Vector version)
     *
     * @param array $position The position to place the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $size The size of the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleV(array $position, array $size, array $color) : void {}

    /**
     * Draw a color-filled rectangle
     *
     * @param array $rec Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleRec(array $rec, array $color) : void {}

    /**
     * Draw a color-filled rectangle with pro parameters
     *
     * @param array $rec Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $origin The origin of the rectangle - Vector2 array ['x' => 0, 'y' => 0]
     * @param float $rotation
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectanglePro(array $rec, array $origin, float $rotation, array $color) : void {}

    /**
     * Draw a vertical-gradient-filled rectangle
     *
     * @param int $posX
     * @param int $posY
     * @param int $width
     * @param int $height
     * @param array $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientV(int $posX, int $posY, int $width, int $height, array $color1, array $color2) : void {}

    /**
     * Draw a horizontal-gradient-filled rectangle
     *
     * @param int $posX
     * @param int $posY
     * @param int $width
     * @param int $height
     * @param array $color1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $color2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientH(int $posX, int $posY, int $width, int $height, array $color1, array $color2) : void {}

    /**
     * Draw a gradient-filled rectangle with custom vertex colors
     *
     * @param array $rec Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $col1 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $col2 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $col3 The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $col4 The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleGradientEx(array $rec, array $col1, array $col2, array $col3, array $col4) : void {}

    /**
     * Draw rectangle outline
     *
     * @param int $posX
     * @param int $posY
     * @param int $width
     * @param int $height
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleLines(int $posX, int $posY, int $width, int $height, array $color) : void {}

    /**
     * Draw rectangle outline with extended parameters
     *
     * @param array $rec Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param int $lineThick
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function rectangleLinesEx(array $rec, int $lineThick, array $color) : void {}

    /**
     * Draw a color-filled triangle
     *
     * @param array $v1 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $v2 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $v3 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function triangle(array $v1, array $v2, array $v3, array $color) : void {}

    /**
     * Draw triangle outline
     *
     * @param array $v1 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $v2 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $v3 The position - Vector2 array ['x' => 0, 'y' => 0]
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function triangleLines(array $v1, array $v2, array $v3, array $color) : void {}

    /**
     * Draw a regular polygon (Vector version)
     *
     * @param array $center The center of the polygon - Vector2 array ['x' => 0, 'y' => 0]
     * @param int $sides
     * @param float $radius
     * @param float $rotation
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function poly(array $center, int $sides, float $radius, float $rotation, array $color) : void {}

    /**
     * Draw a closed polygon defined by points
     *
     * @param array $points The array of points - [Vector2 array ['x' => 0, 'y' => 0]]
     * @param int $numPoints
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function polyEx(array $points, int $numPoints, array $color) : void {}

    /**
     * Draw polygon lines
     *
     * @param array $points The array of points - [Vector2 array ['x' => 0, 'y' => 0]]
     * @param int $numPoints
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public static function polyExLines(array $points, int $numPoints, array $color) : void {}
}