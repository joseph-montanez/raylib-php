<?php

namespace raylib;

/**
 * Class CharInfo
 * @package raylib
 *
 * @property-read int           $value      Character value (Unicode)
 * @property-read \raylib\Image $image      Character rectangle in sprite font - Rectangle array ['x' => 0, 'y' => 0,
 *                'width' => 0, 'height' => 0]
 * @property-read int           $offsetX    Character offset X when drawing
 * @property-read int           $offsetY    Character offset Y when drawing
 * @property-read int           $advanceX   Character advance position X
 */
class CharInfo
{
    /**
     * CharInfo constructor.
     *
     * @param int           $value
     * @param int           $offsetX
     * @param int           $offsetY
     * @param int           $advanceX
     * @param \raylib\Image $image
     */
    public function __construct(int $value, int $offsetX, int $offsetY, int $advanceX, \raylib\Image $image)
    {
    }

    /**
     * Load font data for further use
     *
     * @param string $fileName
     * @param int    $fontSize
     * @param int[]  $fontChars
     * @param int    $type Which font type to load, \raylib\Font::FONT_DEFAULT, \raylib\Font::FONT_BITMAP or \raylib\Font::FONT_SDF
     *
     * @return \raylib\CharInfo
     */
    public static function fromFontData(string $fileName, int $fontSize, array $fontChars, int $type) : \raylib\CharInfo
    {
    }

}
