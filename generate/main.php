<?php

require_once __DIR__ . '/vendor/autoload.php';

$parser = new \Raylib\Parser\Parser();

$parser->load(__DIR__ . '/raylib_api.json');

$parser->generateStructs();