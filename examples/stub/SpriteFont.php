<?php

namespace raylib;

/**
 * Class SpriteFont
 * @package raylib
 *
 * @property-read Texture  $texture    Font texture
 * @property-read int      $baseSize   Base size (default chars height)
 * @property-read int      $charsCount Base size (default chars height)
 * @property-read CharInfo $chars      Characters info data
 */
class SpriteFont
{

    /**
     * Load SpriteFont from file into GPU memory (VRAM)
     *
     * SpriteFont constructor.
     *
     * @param string $fileName
     */
    public function __construct(string $fileName) {}

    /**
     * Measure string size for SpriteFont
     *
     * @param string $text
     * @param float $fontSize
     * @param int $spacing
     *
     * @return array Returns Vector2 ['x' => 0, 'y' => 0]
     */
    public function measure(string $text, float $fontSize, int $spacing) : array {}

    /**
     * Returns index position for a unicode character on sprite font
     *
     * @param int $character
     *
     * @return int
     */
    public function getGlyphIndex(int $character) : int {}

    /**
     * Get the default SpriteFont
     *
     * @return SpriteFont
     */
    public function getDefaultFont() : SpriteFont {}
}