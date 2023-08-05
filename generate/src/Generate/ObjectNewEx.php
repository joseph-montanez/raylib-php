<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Create / Clone Function
 */
class ObjectNewEx
{
    /**
     * @param \Raylib\Parser\Struct[] $structsByType
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(array $structsByType, Struct $struct, array $input): array
    {

        $input[] = 'zend_object * php_raylib_' . $struct->nameLower . '_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *intern;';
        $input[] = '';
        $input[] = '    intern = zend_object_alloc(sizeof(php_raylib_' . $struct->nameLower . '_object), ce);';
        $input[] = '';
        $input[] = '    intern->prop_handler = &php_raylib_' . $struct->nameLower . '_prop_handlers;';
        $input[] = '';
        $input[] = '    if (orig) {';
        $input[] = '        php_raylib_' . $struct->nameLower . '_object *other = php_raylib_' . $struct->nameLower . '_fetch_object(orig);';
        $input[] = '';

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
                $input[] = '        //zend_object *' . $field->name . ' = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, &other->' . $field->name . '->std);';
            } else {
                $input[] = '        php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = Z_' . $field->typePlainUpper . '_OBJ_P(&other->' . $field->name . ');';
            }
        }
        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
                $input[] = '        //php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . ');';
            } else {
//                $input[] = '        php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . ');';
            }
        }
        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }

        $input[] = '        *php_raylib_' . $struct->nameLower . '_fetch_data(intern) = (' . $struct->name . ') {';

        $hasFields = false;
        foreach ($struct->fields as $i => $field) {
            $delimiter = $i + 1 >= $struct->totalFields ? '' : ',';

            if (!$field->isPrimitive) {
                if ($field->isArray || $field->isPointer) {
//                    $input[] = '            // .' . $field->name . ' is an array and not yet supported via constructor';
                } else {
                    $hasFields = true;

                    $input[] = '            .' . $field->name . ' = (' . $field->type . ') {';

                    $subStruct = $structsByType[$field->typePlain];

                    foreach ($subStruct->fields ?? [] as $n => $subField) {
                        $delimiter2 = $n + 1 >= $subStruct->totalFields ? '' : ',';
//                        $ref = $subField->isArray ? '->' : '.';
                        $ref = '.';
                        $input[] = '                .' . $subField->name . ' = php_raylib_' . $struct->nameLower . '_fetch_data(other)->' . $field->name . $ref . $subField->name . $delimiter2;
                    }
                    $input[] = '            }' . $delimiter;
                }
            } else {
                if ($field->isArray) {
                    //-- This is ignored for now as `memcpy` is used below to copy fields over
                } else {
                    $hasFields = true;
                    $input[] = '            .' . $field->name . ' = php_raylib_' . $struct->nameLower . '_fetch_data(other)->' . $field->name . $delimiter;
                }
            }
        }
        $input[] = '        };';
        if (!$hasFields) {
            array_pop($input);
            array_pop($input);

            $input[] = '        intern->' . $struct->nameLower . ' = RL_' . $struct->name . '_Create();';
            $input[] = '';
        }


        foreach ($struct->fields as $i => $field) {
            if ($field->isPrimitive && str_starts_with($field->type, 'char') && $field->isArray && $field->arrayCountNumber > 0) {
                $input[] = '        strncpy(php_raylib_' . $struct->nameLower . '_fetch_data(intern)->' . $field->name . ',  php_raylib_' . $struct->nameLower . '_fetch_data(other)->' . $field->name . ', ' . $field->arrayCountNumber . ');';
            }
            elseif ($field->isPrimitive && $field->isArray && $field->arrayCountNumber > 0) {
                $input[] = '        memcpy(php_raylib_' . $struct->nameLower . '_fetch_data(intern)->' . $field->name . ', php_raylib_' . $struct->nameLower . '_fetch_data(other)->' . $field->name . ', sizeof(' . $field->typePlain . ') * ' . $field->arrayCountNumber . ');';
            }
        }


        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }
        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($struct->name === 'AudioStream' && $field->name === 'buffer') { continue; }
            if ($field->isArray || $field->isPointer) {
                $input[] = '        HashTable *' . $field->name . '_hash;';
                $input[] = '        ALLOC_HASHTABLE(' . $field->name . '_hash);';
                $input[] = '        zend_hash_init(' . $field->name . '_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->' . $field->nameLower . ')), NULL, NULL, 0);';
                $input[] = '        zend_hash_copy(' . $field->name . '_hash, Z_ARRVAL_P(&other->' . $field->nameLower . '), (copy_ctor_func_t) zval_add_ref);';
                $input[] = '        ZVAL_ARR(&intern->' . $field->nameLower . ', ' . $field->name . '_hash);';
                $input[] = '';
            } else {
                $input[] = '        ZVAL_OBJ_COPY(&intern->' . $field->name . ', &php' . ucfirst($field->name) . '->std);';
                $input[] = '';
            }

        }
        $input[] = '    } else {';

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
                $input[] = '        //zend_object *' . $field->name . ' = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, NULL);';
            } else {
                $input[] = '        zend_object *' . $field->name . ' = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, NULL);';
            }
        }
        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
                $input[] = '        //php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . ');';
            } else {
                $input[] = '        php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . ');';
            }
        }
        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }

        $input[] = '        intern->' . $struct->nameLower . ' = RL_' . $struct->name . '_Create();';
        $input[] = '        *php_raylib_' . $struct->nameLower . '_fetch_data(intern) = (' . $struct->name . ') {';

        foreach ($struct->fields as $i => $field) {
            $delimiter = $i + 1 >= $struct->totalFields ? '' : ',';

            if (!$field->isPrimitive) {
                if ($field->isArray || $field->isPointer) {
                    $input[] = '            // .' . $field->name . ' is an array and not yet supported via constructor';
                } else {
                    $input[] = '            .' . $field->name . ' = (' . $field->type . ') {';

                    $subStruct = $structsByType[$field->typePlain];

                    foreach ($subStruct->fields as $n => $subField) {
                        $delimiter2 = $n + 1 >= $subStruct->totalFields ? '' : ',';
                        $input[] = '                .' . $subField->name . ' = 0' . $delimiter2;
                    }
                    $input[] = '            }' . $delimiter;
                }
            } else {
                $input[] = '            .' . $field->name . ' = 0' . $delimiter;
            }
        }
        $input[] = '        };';
        $input[] = '';

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($struct->name === 'AudioStream' && $field->name === 'buffer') { continue; }
            if ($field->isArray || $field->isPointer) {
                /*
                    HashTable *return_hash;
                    ALLOC_HASHTABLE(return_hash);
                    zend_hash_init(return_hash, count_in, NULL, NULL, 0);
                    ZVAL_ARR(&tmp, arr);
                 */
                $input[] = '        HashTable *' . $field->name . '_hash;';
                $input[] = '        ALLOC_HASHTABLE(' . $field->name . '_hash);';
                $input[] = '        zend_hash_init(' . $field->name . '_hash, 0, NULL, NULL, 0);';
                $input[] = '        ZVAL_ARR(&intern->' . $field->nameLower . ', ' . $field->name . '_hash);';
                $input[] = '';
//                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
//                $input[] = '        //intern->' . $field->name . ' = php' . ucfirst($field->name) . ';';
            } else {
                $input[] = '        ZVAL_OBJ_COPY(&intern->' . $field->name . ', &php' . ucfirst($field->name) . '->std);';
                $input[] = '';
            }

        }
        $input[] = '    }';
        $input[] = '';
        $input[] = '    zend_object_std_init(&intern->std, ce);';
        $input[] = '    object_properties_init(&intern->std, ce);';
        $input[] = '    intern->std.handlers = &php_raylib_' . $struct->nameLower . '_object_handlers;';
        $input[] = '';
        $input[] = '    return &intern->std;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input [] = '';

        return $input;
    }
}
