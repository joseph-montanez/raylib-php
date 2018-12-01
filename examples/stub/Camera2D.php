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
     * @return array Camera offset (displacement from target) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function getOffset() : array {}

    /**
     * @param array $offset Camera offset (displacement from target) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function setOffset(array $offset) : void {}

    /**
     * @return array Camera target (rotation and zoom origin) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function getTarget() : array {}

    /**
     * @param array $target Camera target (rotation and zoom origin) - Vector2 ['x' => 0, 'y' => 0]
     */
    public function setTarget(array $target) : void {}

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