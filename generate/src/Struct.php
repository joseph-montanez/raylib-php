<?php

namespace Raylib\Parser;

class Struct
{
    public string $name;
    public string $nameLower;
    public string $nameUpper;
    public string $description;
    /**
     * @var \Raylib\Parser\Field[]
     */
    public array $fields;
    /**
     * @var \Raylib\Parser\Field[]
     */
    public array $nonPrimitiveFields;
    public int $totalFields;
    public string $alias;
    public bool $isAlias;
    public string|null $constructorFunction;

    /**
     * @param array                                              $aliases
     * @param array{name:string,description:string,fields:array,constructorFunction:string|null} $structInfo
     */
    public function __construct(array $aliases, array $structInfo)
    {
        $this->name = $structInfo['name'];
        $this->nameLower = strtolower($structInfo['name']);
        $this->nameUpper = strtoupper($structInfo['name']);
        $this->description = $structInfo['description'];
        $this->constructorFunction = $structInfo['constructorFunction'] ?? null;

        $this->fields = [];
        /** @var array{type:string,name:string,description:string,isArray:bool|null,arrayCountField:string|null} $fieldInfo */
        foreach ($structInfo['fields'] as $fieldInfo) {
            $typePlain = str_replace(['*', ' '], '', $fieldInfo['type']);

            //-- Look to see if this is an alias and if so, change the type now so the existing doesn't need to keep
            // looking up type alias
            $aliasReferenceType = null;
            foreach ($aliases as $aliasKey => $aliasTypes) {
                foreach ($aliasTypes as $aliasType) {
//                    var_dump($typePlain === $aliasType, $typePlain, $aliasType);
                    if ($typePlain === $aliasType) {
                        $aliasReferenceType = $aliasKey;
                        break;
                    }
                }
                if ($aliasReferenceType !== null) {
                    break;
                }
            }
//            var_dump($aliasReferenceType, $typePlain);

            // Create field - with adjusted type
            $correctedType = str_replace($typePlain, $aliasReferenceType !== null ? $aliasReferenceType : $typePlain, $fieldInfo['type']);
            $field = new Field(
                $correctedType,
                $fieldInfo['name'],
                $fieldInfo['description'],
                $fieldInfo['isArray'] ?? false,
                $fieldInfo['arrayCountField'] ?? null,
                $fieldInfo['arrayCountEnum'] ?? null,
                $fieldInfo['arrayCountNumber'] ?? null
            );

            $this->fields[] = $field;
        }

        $this->totalFields = count($this->fields);

        $this->alias = '';
        $this->isAlias = false;
    }

    /**
     * @return \Raylib\Parser\Field[]
     */
    public function fieldsByType(): array
    {
        $types = [];
        foreach ($this->fields as $field) {
            $types[$field->typeName] = $field;
        }

        return $types;
    }

    /**
     * @return \Raylib\Parser\Field[]
     */
    public function nonPrimitiveFields(): array
    {
        if (empty($this->nonPrimitiveFields)) {
            $this->nonPrimitiveFields = [];
            foreach ($this->fields as $field) {
                if ($field->isPrimitive) {
                    continue;
                }

                $this->nonPrimitiveFields[] = $field;
            }
        }

        return $this->nonPrimitiveFields;
    }
}
