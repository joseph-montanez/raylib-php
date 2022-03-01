<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Helper;
use Raylib\Parser\Struct;

class ObjectPropertyGetters
{
    /**
     * @param \Raylib\Parser\Struct[] $allStruct
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(array $allStruct, Struct $struct, array $input): array
    {
        foreach ($struct->fields as $field) {
            $phpReturnType = Helper::toPhpType($field);

            $input[] = 'static ' . $phpReturnType . ' php_raylib_' . $struct->nameLower . '_get_' . $field->nameLower . '(php_raylib_' . $struct->nameLower . '_object *obj) /* {{{ */';
            $input[] = '{';

            switch ($phpReturnType) {
                case 'zend_object *';
                    if ($field->isArray || $field->isPointer) {
                        $input[] = '    //TODO: Support for pointer and arrays';
                        $input[] = '    //GC_ADDREF(&obj->' . $field->nameLower . '->std);';
                        $input[] = '    //return &obj->' . $field->nameLower . '->std;';
                    } else {
                        $input[] = '    GC_ADDREF(&obj->' . $field->nameLower . '->std);';
                        $input[] = '    return &obj->' . $field->nameLower . '->std;';
                    }
                    break;
                case 'double';
                    $input[] = '    return (double) obj->' . $struct->nameLower . '.' . $field->name . ';';
                    break;
                case 'bool';
                    $input[] = '    return obj->' . $struct->nameLower . '.' . $field->name . ';';
                    break;
                case 'zend_long';
                    $input[] = '    return (zend_long) obj->' . $struct->nameLower . '.' . $field->name . ';';
                    break;
                case 'zend_string *';
                    $input[] = '    zend_string *result_str;';
                    if ($field->arrayCountNumber) {
                        $input[] = '    result_str = zend_string_init(obj->' . $struct->nameLower . '.' . $field->name . ', ' . $field->arrayCountNumber . ', 1);';
                    } else {
                        $input[] = '    result_str = zend_string_init(obj->' . $struct->nameLower . '.' . $field->name . ', strlen(obj->' . $struct->nameLower . '.' . $field->name . '), 1);';
                    }
                    $input[] = '    return result_str;';
                    break;
                case 'HashTable *';
                    // Should be easier to implement a hash table for floats and ints :)
                    $input[] = '    //TODO: Not yet supported';
                    break;
            }

            $input[] = '}';
            $input[] = '/* }}} */';
            $input[] = '';
        }


        return $input;
    }
}