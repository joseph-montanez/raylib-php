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
                $input[] = '        zend_object *' . $field->name . ' = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, &other->' . $field->name . '->std);';
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


        $input[] = '        intern->' . $struct->nameLower . ' = (' . $struct->name . ') {';

        foreach ($struct->fields as $i => $field) {
            $delimiter = $i + 1 >= $struct->totalFields ? '' : ',';

            if (!$field->isPrimitive) {
                if ($field->isArray || $field->isPointer) {
                    $input[] = '            // .' . $field->name . ' is an array and not yet supported via constructor';
                } else {
                    $input[] = '            .' . $field->name . ' = (' . $field->type . ') {';

                    $subStruct = $structsByType[$field->typePlain];

                    foreach ($subStruct->fields ?? [] as $n => $subField) {
                        $delimiter2 = $n + 1 >= $subStruct->totalFields ? '' : ',';
//                        $ref = $subField->isArray ? '->' : '.';
                        $ref = '.';
                        $input[] = '                .' . $subField->name . ' = other->' . $struct->nameLower . '.' . $field->name . $ref . $subField->name . $delimiter2;
                    }
                    $input[] = '            }' . $delimiter;
                }
            } else {
                if ($field->isArray) {
                    $input[] = '//            .' . $field->name . ' = other->' . $struct->nameLower . '.' . $field->name . $delimiter;
                } else {
                    $input[] = '            .' . $field->name . ' = other->' . $struct->nameLower . '.' . $field->name . $delimiter;
                }
            }
        }
        $input[] = '        };';


        foreach ($struct->fields as $i => $field) {
            if ($field->isPrimitive && str_starts_with($field->type, 'char') && $field->isArray && $field->arrayCountNumber > 0) {
                $input[] = '        strncpy(intern->' . $struct->nameLower . '.' . $field->name . ', other->' . $struct->nameLower . '.' . $field->name . ', ' . $field->arrayCountNumber . ');';
            }
        }


        if (count($struct->nonPrimitiveFields()) > 0) {
            $input[] = '';
        }
        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        //TODO: support array and pointers';
                $input[] = '        //intern->' . $field->name . ' = php' . ucfirst($field->name) . ';';
            } else {
                $input[] = '        intern->' . $field->name . ' = php' . ucfirst($field->name) . ';';
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

        $input[] = '        intern->' . $struct->nameLower . ' = (' . $struct->name . ') {';

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
//        $input[] = '';

        foreach ($struct->nonPrimitiveFields() as $field) {
            if ($field->isArray || $field->isPointer) {
                $input[] = '        // ' . $field->name . ' array not yet supported needs to generate a hash table!';
                $input[] = '        //intern->' . $field->name . ' = php' . ucfirst($field->name) . ';';
            } else {
                $input[] = '        intern->' . $field->name . ' = php' . ucfirst($field->name) . ';';
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