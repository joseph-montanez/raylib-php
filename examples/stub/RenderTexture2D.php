<?php

namespace raylib;


/**
 * Class RenderTexture2D
 * @package raylib
 *
 * @property-read int     $id      OpenGL Framebuffer Object (FBO) id
 * @property-read Texture $texture Color buffer attachment texture
 * @property-read Texture $depth   Depth buffer attachment texture
 */
class RenderTexture2D
{
    /**
     * Load texture for rendering (framebuffer)
     *
     * @param int $width
     * @param int $height
     */
    public function __construct(int $width, int $height)
    {

    }

    /**
     * Initializes render texture for drawing
     *
     * @return void
     */
    public static function begin(): void
    {
    }

    /**
     * Ends drawing to render texture
     *
     * @return void
     */
    public static function end(): void
    {
    }
}
