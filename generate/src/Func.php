<?php

namespace Raylib\Parser;

use JetBrains\PhpStorm\Pure;

class Func
{
    public string $name;
    public null|string $rename;
    public string $nameLower;
    public string $nameUpper;
    public string $description;
    public string $returnType;
    public string $returnTypeLower;
    public string $returnTypeUpper;
    /**
     * @var \Raylib\Parser\Param[]
     */
    public array $params;
    public int $paramCount;
    public bool $returnIsArray;
    public bool $returnIsPrimitive;
    public bool $unsupported = false;
    public string $returnArrayCountField;
    public string $manualCFile;


    /**
     * @param array{name:string,description:string,returnType:string,params:array,rename:string|null} $functionInfo
     */
    #[Pure] public function __construct(array $aliases, array $functionInfo)
    {
        $this->rename     = $functionInfo['rename'] ?? null;
        $this->name       = $functionInfo['name'];
        $this->returnType = Helper::replaceAlias($aliases, $functionInfo['returnType']);

        $this->nameLower = strtolower($functionInfo['name']);
        $this->nameUpper = strtoupper($functionInfo['name']);

        $this->returnTypeLower = strtolower($this->returnType);
        $this->returnTypeUpper = strtoupper($this->returnType);

        $this->description = $functionInfo['description'] ?? '';

        $this->params = [];
        /** @var array{name:string,type:string} $paramInfo */
        foreach ($functionInfo['params'] ?? [] as $paramInfo) {
            $paramInfo['type'] = Helper::replaceAlias($aliases, $paramInfo['type']);

            $param = new Param($paramInfo);

            $this->params[] = $param;
        }
        $this->paramCount = count($this->params);

        $this->returnIsArray         = $functionInfo['isArray'] ?? Helper::isArray($this->returnType);
        $this->returnArrayCountField = $functionInfo['arrayCountField'] ?? '';
        $this->returnIsPrimitive     = Helper::isPrimitive($this->returnType);
        $this->manualCFile           = '';
    }
}
