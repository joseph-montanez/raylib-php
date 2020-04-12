<?php

$image = new \raylib\Image(__DIR__ . '/../textures/resources/raylib_logo.png');
$pixelColors = $image->getData();
var_dump(count($pixelColors));

foreach ($pixelColors as $color) {
    echo implode(', ', [$color->r, $color->g, $color->b, $color->a]), PHP_EOL;
}