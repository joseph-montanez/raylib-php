<?php

namespace raylib;

/**
 * Class Image
 * @package raylib
 *
 * @property-read int $width   Image base width
 * @property-read int $height  Image base height
 * @property-read int $mipmaps Image levels, 1 by default
 * @property-read int $format  Data format (PixelFormat type)
 */
class Image
{

    public function __construct(string $fileName)
    {
    }

    /**
     * Create an image from an array of pixels
     *
     * @param \raylib\Color[] $pixels Array of colors to load from
     * @param int             $width  The width of image
     * @param int             $height The height of image
     *
     * @return \raylib\Image
     */
    public static function fromColors(array $pixels, int $width, int $height): \raylib\Image
    {
    }

    /**
     * Create an image from an array of pixels
     *
     * @param \raylib\Image     $image The image to copy
     * @param \raylib\Rectangle $rec   The section of the image to copy from
     *
     * @return \raylib\Image
     */
    public static function fromImage(\raylib\Image $image, \raylib\Rectangle $rec): \raylib\Image
    {
    }

    /**
     * Load texture from image data
     *
     * @return Texture
     */
    public function toTexture(): Texture
    {
    }

    /**
     * Export image data to file
     *
     * @return void
     */
    public function export(string $fileName): void
    {
    }

    /**
     * Export image as code file defining an array of bytes
     *
     * @return void
     */
    public function exportAsCode(string $fileName): void
    {
    }

    /**
     * Image raw data
     *
     * @return array
     */
    public function data(): array
    {
    }

    /**
     * Create an image duplicate (useful for transformations)
     *
     * @return Image
     */
    public function copy(): Image
    {
    }

    /**
     * Convert image to POT (power-of-two)
     *
     * @return void
     */
    public function toPot(): void
    {
    }

    /**
     * Convert image data to desired format
     *
     * @param int $newFormat
     *
     * @return void
     */
    public function format(int $newFormat): void
    {
    }

    /**
     * Apply alpha mask to image
     *
     * @param Image $alphaMask
     *
     * @return void
     */
    public function alphaMask(Image $alphaMask): void
    {
    }

    /**
     * Clear alpha channel to desired color
     *
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param float $threshold
     *
     * @return void
     */
    public function alphaClear(array $color, float $threshold): void
    {
    }

    /**
     * Crop image depending on alpha value
     *
     * @param float $threshold
     *
     * @return void
     */
    public function alphaCrop(float $threshold): void
    {
    }

    /**
     * Premultiply alpha channel
     *
     * @return void
     */
    public function alphaPremultiply(): void
    {
    }

    /**
     * Crop an image to a defined rectangle
     *
     * @param array $crop Rectangle ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     */
    public function crop(array $crop): void
    {
    }

    /**
     * Resize and image (bilinear filtering)
     *
     * @param int $newWidth
     * @param int $newHeight
     *
     * @return void
     */
    public function resize(int $newWidth, int $newHeight): void
    {
    }

    /**
     * Resize and image (Nearest-Neighbor scaling algorithm)
     *
     * @param int $newWidth
     * @param int $newHeight
     *
     * @return void
     */
    public function resizeNN(int $newWidth, int $newHeight): void
    {
    }

    /**
     * Generate all mipmap levels for a provided image
     *
     * @return void
     */
    public function mipmaps(): void
    {
    }

    /**
     * Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
     *
     * @param int $rBpp
     * @param int $gBpp
     * @param int $bBpp
     * @param int $aBpp
     *
     * @return void
     */
    public function dither(int $rBpp, int $gBpp, int $bBpp, int $aBpp): void
    {
    }

    /**
     * Draw a source image within a destination image
     *
     * @param Image $dst
     * @param array $srcRec Source - Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $dstRec Destination - Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     */
    public function draw(Image $dst, array $srcRec, array $dstRec): void
    {
    }

    /**
     * Draw rectangle within an image
     *
     * @param array $position Vector2 array ['x' => 0, 'y' => 0]
     * @param array $rec      Rectangle array ['x' => 0, 'y' => 0, 'width' => 0, 'height' => 0]
     * @param array $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function drawRectangle(array $position, array $rec, array $color): void
    {
    }

    /**
     * Draw text (default font) within an image (destination)
     *
     * {@internal RLAPI void ImageDrawText(Image *dst, Vector2 position, const char *text, int fontSize, Color color); }}
     *
     * @param \raylib\Vector2 $position The position to place the text - Vector2 array ['x' => 0, 'y' => 0]
     * @param string          $text     The text to draw on the image
     * @param int             $fontSize The font size of the text
     * @param \raylib\Color   $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function drawText(Vector2 $position, string $text, int $fontSize, Color $color): void
    {
    }

    /**
     * Draw text (custom sprite font) within an image (destination)
     *
     * {@internal RLAPI void ImageDrawTextEx(Image *dst, Vector2 position, Font font, const char *text, float fontSize, float spacing, Color color); }}
     *
     * @param \raylib\Vector2 $position The position to place the text - Vector2 array ['x' => 0, 'y' => 0]
     * @param \raylib\Font    $font
     * @param string          $text
     * @param float           $fontSize
     * @param int             $spacing
     * @param \raylib\Color   $color    The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function drawTextEx(Vector2 $position, Font $font, string $text, float $fontSize, int $spacing, Color $color): void
    {
    }

    /**
     * Draw text (default font) within an image (destination)
     *
     * {@internal RLAPI Image ImageText(const char *text, int fontSize, Color color);}}
     *
     * @param string        $text     The text to draw on the image
     * @param int           $fontSize The font size of the text
     * @param \raylib\Color $color    The color
     *
     * @return void
     */
    public static function fromDefaultFont(string $text, int $fontSize, Color $color): void
    {
    }

    /**
     * Draw text (custom sprite font) within an image (destination)
     *
     * Image ImageTextEx(SpriteFont font, const char *text, float fontSize, int spacing, Color tint);
     *
     * @param \raylib\Font  $font
     * @param string        $text
     * @param float         $fontSize
     * @param int           $spacing
     * @param \raylib\Color $color The color
     *
     * @return void
     */
    public static function fromFont(Font $font, string $text, float $fontSize, int $spacing, Color $color): void
    {
    }


    /**
     * Flip image vertically
     *
     * @return void
     */
    public function flipVertical(): void
    {
    }

    /**
     * Flip image horizontally
     *
     * @return void
     */
    public function flipHorizontal(): void
    {
    }

    /**
     * Modify image color: tint
     *
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return void
     */
    public function colorTint(array $color): void
    {
    }

    /**
     * Modify image color: invert
     *
     * @return void
     */
    public function colorInvert(): void
    {
    }

    /**
     * Modify image color: grayscale
     *
     * @return void
     */
    public function colorGrayscale(): void
    {
    }

    /**
     * Modify image color: contrast (-100 to 100)
     *
     * @param float $contrast Between -100 to 100
     *
     * @return void
     */
    public function colorContrast(float $contrast): void
    {
    }

    /**
     * Modify image color: brightness (-255 to 255)
     *
     * @param int $brightness Between -255 to 255
     *
     * @return void
     */
    public function colorBrightness(int $brightness): void
    {
    }

    /**
     * Generate image: plain color
     *
     * @param int   $width
     * @param int   $height
     * @param array $color The color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return Image
     */
    public static function genImageColor(int $width, int $height, array $color): Image
    {
    }

    /**
     * Generate image: vertical gradient
     *
     * @param int   $width
     * @param int   $height
     * @param array $top    The top gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $bottom The bottom gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return Image
     */
    public static function genImageGradientV(int $width, int $height, array $top, array $bottom): Image
    {
    }

    /**
     * @param int   $width
     * @param int   $height
     * @param array $left  The left gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $right The right gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return Image
     */
    public static function genImageGradientH(int $width, int $height, array $left, array $right): Image
    {
    }

    /**
     * Generate image: radial gradient
     *
     * @param int   $width
     * @param int   $height
     * @param float $density
     * @param array $inner The inner gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $outer The outer gradient color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return Image
     */
    public static function genImageGradientRadial(int $width, int $height, float $density, array $inner, array $outer): Image
    {
    }

    /**
     * Generate a checkered image
     *
     * @param int   $width
     * @param int   $height
     * @param int   $checksX How many checkers along the x-axis
     * @param int   $checksY How many checkers along the y-axis
     * @param array $col1    The primary checker color [red,blue,green,alpha] i.e [0,0,0,255]
     * @param array $col2    The secondary checker color [red,blue,green,alpha] i.e [0,0,0,255]
     *
     * @return Image
     */
    public static function genImageChecked(int $width, int $height, int $checksX, int $checksY, array $col1, array $col2): Image
    {
    }

    /**
     * Generate image: white noise
     *
     * @param int   $width
     * @param int   $height
     * @param float $factor
     *
     * @return Image
     */
    public static function genImageWhiteNoise(int $width, int $height, float $factor): Image
    {
    }

    /**
     * Generate image: perlin noise
     *
     * @param int   $width
     * @param int   $height
     * @param int   $offsetX
     * @param int   $offsetY
     * @param float $scale
     *
     * @return Image
     */
    public static function genImagePerlinNoise(int $width, int $height, int $offsetX, int $offsetY, float $scale): Image
    {
    }

    /**
     * @param int $width
     * @param int $height
     * @param int $tileSize
     *
     * @return Image
     */
    public static function genImageCellular(int $width, int $height, int $tileSize): Image
    {
    }

}
