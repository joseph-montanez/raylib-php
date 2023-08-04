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
        $input[] = '    struct RL_' . $struct->name . ' *' . $struct->nameLower . ';';
        $input[] = '    HashTable *prop_handler;';

        //-- External Object Fields
        // These are the pointers in the struct
        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                if ($field->typePlainLower === 'raudiobuffer') {
                    $input[] = '// NO idea what to do with rAudioBuffer';
                    $input[] = '//php_raylib_' . $field->typePlainLower . '_object *' . $field->nameLower . ';';
                } else {
//                    if ($field->arrayCountNumber > 0) {
//                        $input[] = '    zval ' . $field->nameLower . '[' . $field->arrayCountNumber . '];';
//                    } else {
                        $input[] = '    zval ' . $field->nameLower . ';';
//                    }
                }
            } else {
                $input[] = '    zval ' . $field->nameLower . ';';
            }
        }

        foreach ($struct->fields as $field) {
            if ($field->isPrimitive && $field->isArray) {
                $input[] = '    // Cannot support primitive data structure like ' . $field->type . ' (an array) as zval';
                $input[] = '    // zval ' . $field->nameLower . ';';
            }
        }

        //-- zend_object MUST be at the end of the struct to work correctly
        $input[] = '    zend_object std;';
        $input[] = '} php_raylib_' . $struct->nameLower . '_object;';
        $input[] = '';

        return $input;
    }
}
