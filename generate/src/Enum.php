<?php

namespace Raylib\Parser;

use JetBrains\PhpStorm\Pure;

class Enum
{
    public string $name;
    public string $nameLower;
    public string $nameUpper;
    public string $description;

    /**
     * @var \Raylib\Parser\EnumValue[]
     */
    public array $values;

    /**
     * @param       $name
     * @param       $description
     * @param array $values
     */
    #[Pure] public function __construct($name, $description, array $values)
    {
        $this->name = $name;
        $this->nameLower = strtolower($name);
        $this->nameUpper = strtoupper($name);
        $this->description = $description;

        $this->values = [];
        /** @var array{name:string,value:string,description:string} $value */
        foreach ($values as $value) {
            $this->values[] = new EnumValue($value['name'], $value['value'], $value['description']);
        }

    }

}