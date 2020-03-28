<?php

use raylib\Window;

Window::init($screenWidth, $screenHeight, "raylib [textures] example - bunnymark");

// Load bunny texture
$texBunny = new \raylib\Texture(__DIR__ . "/resources/wabbit_alpha.png");

$vec = new \raylib\Vector2(10, 10);

$rec = new \raylib\Rectangle(10, 20, 100, 200);
$rec->x += 1;
$rec->y += 1;
$rec->width += 1;
$rec->height += 1;
var_dump($vec->x, $texBunny, $rec);
