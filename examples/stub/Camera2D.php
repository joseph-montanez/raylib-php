<?php

namespace raylib;


/**
 * Class Camera2D
 * @package raylib
 *
 * @property-read array $offset   Camera offset (displacement from target) - Vector2 ['x' => 0, 'y' => 0]
 * @property-read array $target   Camera target (rotation and zoom origin) - Vector2 ['x' => 0, 'y' => 0]
 * @property-read float $rotation Camera rotation in degrees
 * @property-read float $zoom     Camera zoom (scaling), should be 1.0f by default
 */
class Camera2D
{
    /**
     * @return \raylib\Vector2 Camera offset (displacement from target) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function getOffset() : Vector2 {}

    /**
     * @param \raylib\Vector2 $offset Camera offset (displacement from target) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function setOffset(Vector2 $offset) : void {}

    /**
     * @return \raylib\Vector2 Camera target (rotation and zoom origin) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function getTarget() : Vector2 {}

    /**
     * @param \raylib\Vector2 $target Camera target (rotation and zoom origin) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function setTarget(Vector2 $target) : void {}

    /**
     * @return float
     */
    public function getRotation() : float {}

    /**
     * @param float $rotation
     */
    public function setRotation(float $rotation) : void {}

    /**
     * @return float
     */
    public function getZoom() : float {}

    /**
     * @param float $zoom
     */
    public function setZoom(float $zoom) : void {}
}