<?php
$fontChars = [
    ord("A"),
    ord("B"),
    ord("C"),
    ord("D"),
];

$glyphInfos = \raylib\GlyphInfo::fromFontData(__DIR__ . '/pixantiqua.ttf', 12, $fontChars, \raylib\Font::FONT_DEFAULT);

foreach ($glyphInfos as $n => $glyphInfo) {
    $glyphInfo->image->export(__DIR__ . '/' . chr($fontChars[$n]) . '-out.png');
}
