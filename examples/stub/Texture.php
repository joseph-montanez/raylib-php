<?php

namespace raylib;

/**
 * Class Texture
 * @package raylib
 *
 * @property-read int $id      OpenGL texture id (unsigned)
 * @property-read int $width   Image base width
 * @property-read int $height  Image base height
 * @property-read int $mipmaps Image levels, 1 by default
 * @property-read int $format  Data format (PixelFormat type)
 */
class Texture
{
    const
        /**
         * @var int FILTER_POINT No filter, just pixel aproximation
         */
        FILTER_POINT = 0,
        /**
         * @var int FILTER_BILINEAR Linear filtering
         */
        FILTER_BILINEAR = 1,
        /**
         * @var int FILTER_TRILINEAR Trilinear filtering (linear with mipmaps)
         */
        FILTER_TRILINEAR = 2,
        /**
         * @var int FILTER_ANISOTROPIC_4X Anisotropic filtering 4x
         */
        FILTER_ANISOTROPIC_4X = 3,
        /**
         * @var int FILTER_ANISOTROPIC_8X Anisotropic filtering 8x
         */
        FILTER_ANISOTROPIC_8X = 4,
        /**
         * @var int FILTER_ANISOTROPIC_16X Anisotropic filtering 16x
         */
        FILTER_ANISOTROPIC_16X = 5;

    const
        /**
         * @var int WRAP_REPEAT Repeats texture in tiled mode
         */
        WRAP_REPEAT = 0,
        /**
         * @var int WRAP_CLAMP Clamps texture to edge pixel in tiled mode
         */
        WRAP_CLAMP = 1,
        /**
         * @var int WRAP_MIRROR_REPEAT Mirrors and repeats the texture in tiled mode
         */
        WRAP_MIRROR_REPEAT = 2,
        /**
         * @var int WRAP_MIRROR_CLAMP Mirrors and clamps to border the texture in tiled mode
         */
        WRAP_MIRROR_CLAMP = 3;

    public function __construct(string $fileName)
    {
    }

    //-- configuration functions

    /**
     * Generate GPU mipmaps for a texture
     *
     * {@internal RLAPI void GenTextureMipmaps(Texture2D *texture); }}
     *
     * @return void
     */
    public function genMipmaps(): void
    {
    }

    /**
     * Set texture scaling filter mode
     *
     * {@internal RLAPI void SetTextureFilter(Texture2D texture, int filterMode); }}
     *
     * @param int $filterMode
     *
     * @return void
     */
    public function setFilter(int $filterMode): void
    {
    }

    /**
     * Set texture wrapping mode
     *
     * {@internal RLAPI void SetTextureWrap(Texture2D texture, int wrapMode); }}
     *
     * @param int $wrapMode
     *
     * @return void
     */
    public function setWrap(int $wrapMode): void
    {
    }

    /**
     * Draw a Texture2D
     *
     * {@internal RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint); }}
     *
     * @param int           $posX
     * @param int           $posY
     * @param \raylib\Color $tint The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function draw(int $posX, int $posY, Color $tint): void
    {
    }

    /**
     * Draw a Texture2D with position defined as Vector2
     *
     * {@internal RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint); }}
     *
     * @param \raylib\Vector2 $position Where to draw the texture on screen
     * @param \raylib\Color   $tint     The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public function drawV(\raylib\Vector2 $position, Color $tint): void
    {
    }

    /**
     * Draw a Texture2D with extended parameters
     *
     * {@internal RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint); }}
     *
     * @param \raylib\Vector2 $position Vector2 array ['x' => 0, 'y' => 0]
     * @param float           $rotation
     * @param float           $scale
     * @param \raylib\Color   $tint     The color [red,blue,green,alpha] i.e [0,0,0,255]
     */
    public function drawEx(\raylib\Vector2 $position, float $rotation, float $scale, Color $tint): void
    {
    }

    /**
     * Draw a part of a texture defined by a rectangle
     *
     * {@internal RLAPI void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);}}
     *
     * @param \raylib\Rectangle $sourceRec Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Vector2   $position  Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Color     $tint
     */
    public function drawRec(\raylib\Rectangle $sourceRec, \raylib\Vector2 $position, Color $tint): void
    {
    }

    /**
     * Draw a part of a texture defined by a rectangle with 'pro' parameters
     *
     * {@internal  RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin
     * float rotation, Color tint); }}
     *
     * @param \raylib\Rectangle $sourceRec Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Rectangle $destRec   Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param \raylib\Vector2   $origin    Vector2 array ['x' => 0, 'y' => 0]
     * @param float             $rotation
     * @param \raylib\Color     $tint      The tint color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function drawPro(Rectangle $sourceRec, Rectangle $destRec, Vector2 $origin, float $rotation, Color $tint): void
    {
    }
}
