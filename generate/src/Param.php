<?php

namespace Raylib\Parser;

class Param
{
    public string $name;
    public string $nameLower;
    public string $nameUpper;
    public string $nameUpperFirst;
    public string $type;
    public string $typeUpper;
    public string $typeLower;
    public string $typeUpperFirst;
    public bool $isArray;
    public bool $isPrimitive;
    public bool $isRef;
    public string|null $arrayCountField;
    public string|null $arrayCountEnum;
    public string|null $arrayCountNumber;

    /**
     * @param array{name:string,type:string,isRef:bool,isArray:bool,arrayCountField:string|null,arrayCountEnum:string|null,arrayCountNumber:string|null} $paramInfo
     */
    public function __construct(array $paramInfo)
    {
        $this->name = $paramInfo['name'];
        $this->type = $paramInfo['type'];
        $this->isRef = $paramInfo['isRef'] ?? false;
        $this->typeLower = trim(str_replace('*', '', strtolower($paramInfo['type'])));
        $this->typeUpper = trim(str_replace('*', '', strtoupper($paramInfo['type'])));
        $this->typeUpperFirst = ucfirst($paramInfo['type']);
        $this->nameUpperFirst = ucfirst($paramInfo['name']);
        $this->nameLower = strtolower($paramInfo['name']);
        $this->nameUpper = strtoupper($paramInfo['name']);
        $this->isArray = Helper::isArray($this->type);
        $this->isPrimitive = Helper::isPrimitive($this->type);

        if ($paramInfo['isArray'] ?? false) {
            $this->isArray = $paramInfo['isArray'];
        }
        if ($paramInfo['arrayCountField'] ?? null) {
            $this->arrayCountField = $paramInfo['arrayCountField'];
        }
        if ($paramInfo['arrayCountEnum'] ?? null) {
            $this->arrayCountEnum = $paramInfo['arrayCountEnum'];
        }
        if ($paramInfo['arrayCountNumber'] ?? null) {
            $this->arrayCountNumber = $paramInfo['arrayCountNumber'];
        }

    }

    public function getTr()
    {
        return [
            '[type]'           => $this->type,
            '[typeNonConst]'   => trim(str_replace('const', '', $this->type)),
            '[typeNoStar]'     => trim(str_replace('*', '', $this->type)),
            '[typeLower]'      => $this->typeLower,
            '[typeUpper]'      => $this->typeUpper,
            '[name]'           => $this->name,
            '[nameLower]'      => $this->nameLower,
            '[nameUpperFirst]' => $this->nameUpperFirst,
        ];
    }
}