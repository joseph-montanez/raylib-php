<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectStruct
{
    public function generate(array $structsByType, Struct $struct, array $input): array
    {
        $input[] = 'typedef struct _php_raylib_' . $struct->nameLower . '_object {';
        $input[] = '    ' . $struct->name . ' ' . $struct->nameLower . ';';
        $input[] = '    HashTable *prop_handler;';

        //-- External Object Fields
        // These are the pointers in the struct
        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                if ($field->typePlainLower === 'raudiobuffer') {
                    $input[] = '// NO idea what to do with rAudioBuffer';
                    $input[] = '//php_raylib_' . $field->typePlainLower . '_object *' . $field->nameLower . ';';
                } else {
                    $input[] = 'php_raylib_' . $field->typePlainLower . '_object *' . $field->nameLower . ';';
                }
            } elseif ($structsByType[$field->typePlain]->isAlias) {
                $aliasStruct = $structsByType[$structsByType[$field->type]->alias];
                $input[]     = '    php_raylib_' . $aliasStruct->nameLower . '_object *' . $field->nameLower . ';';
            } else {
                $input[] = '    php_raylib_' . $field->typePlainLower . '_object *' . $field->nameLower . ';';
            }
        }
        //-- zend_object MUST be at the end of the struct to work correctly
        $input[] = '    zend_object std;';
        $input[] = '} php_raylib_' . $struct->nameLower . '_object;';
        $input[] = '';

        return $input;
    }
}