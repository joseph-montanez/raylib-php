<?php

use raylib\Vector3;
use raylib\Camera3D;

$vector = new Vector3(1, 2, 3);

$camera = new Camera3D(new Vector3(0.0, 10.0, 10.0), new Vector3(0.0, 0.0, 0.0), new Vector3(0.0, 1.0, 0.0), 45.0, 0);
$camera->position = $vector;
$camera->position->x++;

var_dump($camera->position);
echo "unset\n";
unset($camera->position);
echo "dump\n";
var_dump($camera->position);


// $nex_v2 = $camera->getPosition();
// $nex_v2->x++;
// $camera->setPosition($nex_v2);
// $nex_v2->y = 3;