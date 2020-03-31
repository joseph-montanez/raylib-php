<?php
$fontChars = [
    ord("A"),
    ord("B"),
    ord("C"),
    ord("D"),
];

$charinfos = \raylib\CharInfo::fromFontData(__DIR__ . '/pixantiqua.ttf', 12, $fontChars, \raylib\Font::FONT_DEFAULT);

foreach ($charinfos as $n => $charinfo) {
    $charinfo->image->export(__DIR__ . '/' . chr($fontChars[$n]) . '-out.png');
}
