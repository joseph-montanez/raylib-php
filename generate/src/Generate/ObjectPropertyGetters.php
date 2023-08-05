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
                        $input[] = '    php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = Z_' . $field->typePlainUpper . '_OBJ_P(&obj->' . $field->nameLower . ');';
                        $input[] = '';
                        $input[] = '    php' . ucfirst($field->name) . '->' . $field->typePlainLower . '->refCount++;';
                        $input[] = '';
                        $input[] = '    GC_ADDREF(&php' . ucfirst($field->name) . '->std);';
                        $input[] = '';
                        $input[] = '    return &php' . ucfirst($field->name) . '->std;';
                    }
                    break;
                case 'double';
                    $input[] = '    return (double) php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ';';
                    break;
                case 'bool';
                    $input[] = '    return php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ';';
                    break;
                case 'zend_long';
                    $input[] = '    return (zend_long) php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ';';
                    break;
                case 'zend_string *';
                    $input[] = '    zend_string *result_str;';
                    if ($field->arrayCountNumber) {
                        $input[] = '    result_str = zend_string_init(php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ', ' . $field->arrayCountNumber . ', 1);';
                    } else {
                        $input[] = '    result_str = zend_string_init(php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ', strlen(php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . '), 1);';
                    }
                    $input[] = '    return result_str;';
                    break;
                case 'HashTable *';
                    // Should be easier to implement a hash table for floats and ints :)
                    if ($field->type === 'void *') {
                        $input[] = '    // TODO';
                        break;
                    }
                    if ($field->isPrimitive) {
                        $input[] = '    // Direct access to c primitives like ' . $field->type . ' is not possible with';
                        $input[] = '    // PHP arrays, need to copy on the fly';
                        $input[] = '';

                        $input[] = '    // Create zval to hold array';
                        $input[] = '    zval z' . ucfirst($field->name) . ';';
                        $input[] = '    unsigned int i;';
                        $input[] = '    ' . $struct->name. ' *objectData = php_raylib_' . $struct->nameLower . '_fetch_data(obj);';
                        $input[] = '';

                        $input[] = '    // Initialize Array';
                        if ($field->arrayCountNumber) {
                            $input[] = '    array_init_size(&z' . ucfirst($field->name) . ', ' . $field->arrayCountNumber . ');';
                        } else {
                            $input[] = '    array_init_size(&z' . ucfirst($field->name) . ', objectData->' . $field->arrayCountField . ');';
                        }
                        $input[] = '';

                        $input[] = '    // populate the array with ' . $field->typePlain;
                        if ($field->arrayCountNumber) {
                            $input[] = '    for (i = 0; i < ' . $field->arrayCountNumber . '; i++) {';
                        } else {
                            $input[] = '    for (i = 0; i < objectData->' . $field->arrayCountField . '; i++) {';
                        }

                        $input[] = '        if (objectData != NULL && objectData->' . $field->name . ' != NULL) {';
                        $input[] = '            add_next_index_double(&z' . ucfirst($field->name) . ', objectData->' . $field->name . '[i]);';
                        $input[] = '        }';
                        $input[] = '    }';
                        $input[] = '';

                        $input[] = '    return Z_ARRVAL_P(&z' . ucfirst($field->name) . ');';
                    } else {
                        $input[] = '    return Z_ARRVAL_P(&obj->' . $field->nameLower . ');';
                    }
                    break;
            }

            $input[] = '}';
            $input[] = '/* }}} */';
            $input[] = '';
        }


        return $input;
    }
}
