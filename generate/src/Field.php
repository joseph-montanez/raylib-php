<?php

namespace Raylib\Parser;

class Field
{
    public string $type;
    public string $name;
    public string $nameLower;
    public string $nameUpper;
    public string $description;
    public bool $isArray;
    public bool $isPointer;
    public bool $isPrimitive;
    public string $typeName;
    public string $fieldName;
    public string $typePlain;
    public string $typePlainLower;
    public string $typePlainUpper;
    public string|null $arrayCountField;
    public string|null $arrayCountEnum;
    public string|null $arrayCountNumber;

    public function __construct($type, $name, $description,
                                $isArray = false,
                                $arrayCountField = null,
                                $arrayCountEnum = null,
                                $arrayCountNumber = null)
    {
        $this->type = $type;

        $this->name = $name;
        $parts      = explode('[', $this->name);
        $this->name = array_shift($parts);

        $this->nameLower        = strtolower($this->name);
        $this->nameUpper        = strtoupper($this->name);
        $this->description      = $description;
        $this->isArray          = $isArray;
        $this->arrayCountField  = $arrayCountField;
        $this->arrayCountEnum   = $arrayCountEnum;
        $this->arrayCountNumber = $arrayCountNumber;
        $this->isPointer        = Helper::isPointer($this->type);
        $this->isPrimitive      = Helper::isPrimitive($this->type);

        $this->typePlain = str_replace(['*', ' '], '', $this->type);
        $parts           = explode('[', $this->typePlain);
        $this->typePlain = array_shift($parts);

        $this->typePlainLower = strtolower($this->typePlain);
        $this->typePlainUpper = strtoupper($this->typePlain);
        $this->typeName       = str_replace([' ', '*', '__'], ['_', '', '_'], $this->isArray ? strtolower($this->type) . '_array' : strtolower($this->type));
        $this->fieldName      = str_replace([' ', '*'], ['_', ''], $this->typeName);
    }

    public function getTr()
    {
        return [
            '[type]'         => $this->type,
            '[typeNonConst]' => trim(str_replace('const', '', $this->type)),
            '[typeNoStar]'   => trim(str_replace('*', '', $this->type)),
            '[typeLower]'    => $this->typePlainLower,
            '[typeUpper]'    => $this->typePlainUpper,
            '[name]'         => $this->name,
            '[nameLower]'    => $this->nameLower,
        ];
    }
}