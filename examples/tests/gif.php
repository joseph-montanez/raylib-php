<?php

if (!extension_loaded('raylib')) {
    echo 'no raylib';
    exit;
}

$frames = 0;
$image = \raylib\Image::fromAnim(__DIR__ . '/why.gif', $frames);

var_dump($frames);
