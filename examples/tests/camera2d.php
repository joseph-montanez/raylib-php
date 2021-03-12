<?php
$camera = new \raylib\Camera2d();

$camera->target->x = 5;
$camera->target->y = 6;

var_dump($camera->target);