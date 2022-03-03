<?php

namespace Raylib\Parser;

class Helper
{
    public static function isArray(string $type): bool
    {
        $isPrimitive = self::isPrimitive($type);
        $starCount   = substr_count($type, '*');

        if (!$isPrimitive && $starCount > 1) {
            return true;
        } else if (!$isPrimitive && $starCount === 1) {
            return false;
        } else if ($isPrimitive && $starCount === 1) {
            return true;
        } else {
            return false;
        }
    }

    public static function isPointer(string $type): bool
    {
        $isPrimitive = self::isPrimitive($type);
        $starCount   = substr_count($type, '*');

        if (!$isPrimitive && $starCount > 1) {
            return false;
        } else if (!$isPrimitive && $starCount === 1) {
            return true;
        } else if ($isPrimitive && $starCount === 1) {
            return false;
        } else {
            return false;
        }
    }

    public static function isPrimitive(string $type): bool
    {
        return (
            str_starts_with($type, 'int') ||
            str_starts_with($type, 'long') ||
            str_starts_with($type, 'unsigned') ||
            str_starts_with($type, 'const unsigned') ||
            str_starts_with($type, 'float') ||
            str_starts_with($type, 'double') ||
            str_starts_with($type, 'const char') ||
            str_starts_with($type, 'char') ||
            str_starts_with($type, 'void') ||
            str_starts_with($type, 'bool')
        );
    }

    public static function isFloat(string $type): bool
    {
        return str_starts_with($type, 'float') || str_starts_with($type, 'double');
    }

    public static function isInt(string $type): bool
    {
        return str_starts_with($type, 'int')
            || str_starts_with($type, 'short')
            || str_starts_with($type, 'long')
            || str_starts_with($type, 'unsigned short')
            || str_starts_with($type, 'unsigned int')
            || str_starts_with($type, 'const unsigned char')
            || str_starts_with($type, 'unsigned char');

    }

    public static function isString(string $type): bool
    {
        return str_starts_with($type, 'char')
            || str_starts_with($type, 'const char');

    }

    public static function toPhpType(Field $field)
    {
        if (Helper::isFloat($field->type) && !($field->isArray || $field->isPointer)) {
            $phpType = 'double';
        } elseif (Helper::isInt($field->type) && !($field->isArray || $field->isPointer)) {
            $phpType = 'zend_long';
        } elseif (Helper::isString($field->type)) {
            $phpType = 'zend_string *';
        } elseif ($field->isArray) {
            $phpType = 'HashTable *';
        } elseif ($field->type === 'bool') {
            $phpType = 'bool';
        } else {
            $phpType = 'zend_object *';
        }

        return $phpType;
    }

    public static function isBool(string $type)
    {
        return str_starts_with($type, 'bool');
    }

    public static function replaceAlias(array $aliases, string $type): string {

        $typePlain = trim(str_replace(['*'], '', $type));
        $parts     = explode('[', $typePlain);
        $typePlain = array_shift($parts);


        $aliasReferenceType = null;
        foreach ($aliases as $aliasKey => $aliasTypes) {
            foreach ($aliasTypes as $aliasType) {
                if ($aliasType === $typePlain) {
                    $aliasReferenceType = $aliasKey;
                }
            }
        }

        if ($aliasReferenceType) {
            return str_replace($typePlain, $aliasReferenceType, $type);
        }

        return $type;
    }
}