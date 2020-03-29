<?php

\raylib\Audio::initDevice();

$wave = new \raylib\Wave(__DIR__ . '/Ensoniq-ESQ-1-Bass-C2.wav');

$data = $wave->getDataArray();
var_dump($wave->getSampleCount(), $wave->getChannels(), count($data));

\raylib\Audio::closeDevice();
