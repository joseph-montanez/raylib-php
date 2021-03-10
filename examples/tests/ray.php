<?php

if (!extension_loaded('raylib')) {
    echo 'no raylib';
    exit;
}

$position = new \raylib\Vector3(1,2,3);
$direction = new \raylib\Vector3(4,5,6);

echo 123;
$ray = new \raylib\Ray($position, $direction);
echo 456, PHP_EOL;
var_dump($ray);
