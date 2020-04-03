<?php


namespace raylib;


class Font
{
    public int $baseSize;

    public int $charsCount;

    public Texture $texture;

    /**
     * @var \raylib\Rectangle[]
     */
    public array $recs;

    /**
     * @var \raylib\CharInfo[]
     */
    public array $chars;

    const
        /**
         * @var int FONT_DEFAULT Default font generation, anti-aliased
         */
        FONT_DEFAULT = 0,
        /**
         * @var int FONT_BITMAP Bitmap font generation, no anti-aliasing
         */
        FONT_BITMAP = 1,
        /**
         * @var int FONT_SDF SDF font generation, requires external shader
         */
        FONT_SDF = 2;

    /**
     * Load font from file into GPU memory (VRAM)
     *
     * @param string $fileName
     */
    public function __construct(string $fileName)
    {
    }

    /**
     * Creates a new Font
     *
     * @param int                 $baseSize
     * @param int                 $charsCount
     * @param \raylib\Texture     $texture
     * @param \raylib\Rectangle[] $recs
     * @param \raylib\CharInfo[]  $chars
     *
     * @return \raylib\Font
     */
    public static function fromRaw(int $baseSize, int $charsCount, Texture $texture, array $recs, array $chars): Font
    {
    }

    /**
     * Draw text using font and additional parameters
     *
     * {@internal RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);}}
     *
     * @param string          $text
     * @param \raylib\Vector2 $position
     * @param float           $fontSize
     * @param float           $spacing
     * @param \raylib\Color   $tint
     *
     *
     *
     * @return void
     */
    public static function draw(string $text, Vector2 $position, float $fontSize, float $spacing, Color $tint): void
    {
    }

    /**
     * Load font from file with extended parameters
     *
     * {@internal RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int charsCount);}}
     *
     * @param string $fileName
     * @param int    $fontSize
     * @param int    $fontChars
     * @param int    $charsCount
     *
     * @return \raylib\Font
     */
    public static function fromCustom(string $fileName, int $fontSize, ?int $fontChars, int $charsCount) : Font
    {
    }

    /**
     * Measure string size for Font
     *
     * {@internal RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);}}
     *
     * @param string $text
     * @param float  $fontSize
     * @param float  $spacing
     *
     * @return \raylib\Vector2
     */
    public static function measureText(string $text, float $fontSize, float $spacing) : Vector2
    {
    }
}
