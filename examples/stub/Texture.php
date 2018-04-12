<?php

namespace raylib;

/**
 * Class Texture
 * @package raylib
 *
 * @property-read int $id OpenGL texture id (unsigned)
 * @property-read int $width Image base width
 * @property-read int $height Image base height
 * @property-read int $mipmaps Image levels, 1 by default
 * @property-read int $format Data format (PixelFormat type)
 */
class Texture {
    public function __construct(string $fileName) {}

    //-- configuration functions

    /**
     * Generate GPU mipmaps for a texture
     *
     * {@internal RLAPI void GenTextureMipmaps(Texture2D *texture); }}
     *
     * @return void
     */
    public function genMipmaps() : void {}

    /**
     * Set texture scaling filter mode
     *
     * {@internal RLAPI void SetTextureFilter(Texture2D texture, int filterMode); }}
     *
     * @param int $filterMode
     *
     * @return void
     */
    public function setFilter(int $filterMode) : void {}

    /**
     * Set texture wrapping mode
     *
     * {@internal RLAPI void SetTextureWrap(Texture2D texture, int wrapMode); }}
     *
     * @param int $wrapMode
     *
     * @return void
     */
    public function setWrap(int $wrapMode) : void {}

    /**
     * Draw a Texture2D
     *
     * {@internal RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint); }}
     *
     * @param int $posX
     * @param int $posY
     * @param array $tint The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function draw(int $posX, int $posY, array $tint) : void {}

    /**
     * Draw a Texture2D with position defined as Vector2
     *
     * {@internal RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint); }}
     *
     * @param array $position Vector2 array ['x' => 0, 'y' => 0]
     * @param array $tint     The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public function drawV(array $position, array $tint) : void {}

    /**
     * Draw a Texture2D with extended parameters
     *
     * {@internal RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint); }}
     *
     * @param array $position Vector2 array ['x' => 0, 'y' => 0]
     * @param float $rotation
     * @param float $scale
     * @param array $tint     The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public function drawEx(array $position, float $rotation, float $scale, array $tint) : void {}

    /**
     * Draw a part of a texture defined by a rectangle
     *
     * {@internal RLAPI void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);}}
     *
     * @param array $sourceRec Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $position  Vector2 array ['x' => 0, 'y' => 0]
     * @param array $tint
     */
    public function drawRec(array $sourceRec, array $position, array $tint) : void {}

    /**
     * Draw a part of a texture defined by a rectangle with 'pro' parameters
     *
     * {@internal  RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin
     * float rotation, Color tint); }}
     *
     * @param array $sourceRec Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $destRec   Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $origin    Vector2 array ['x' => 0, 'y' => 0]
     * @param float $rotation
     * @param array $tint      The tint color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function DrawTexturePro(array $sourceRec, array $destRec, array $origin, float $rotation, array $tint) : void {}
}