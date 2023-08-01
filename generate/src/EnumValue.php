<?php

namespace Raylib\Parser;

class EnumValue
{
    public string $value;
    public string $name;
    public string $nameLower;
    public string $nameUpper;
    public string $description;


    public function __construct($name, $value, $description)
    {
        $this->value = $value;
        $this->name = $name;
        $this->nameLower = strtolower($name);
        $this->nameUpper = strtoupper($name);
        $this->description = $description;
    }
}