<?php


namespace raylib;


class Font
{
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

}
