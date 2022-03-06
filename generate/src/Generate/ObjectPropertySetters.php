<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Helper;
use Raylib\Parser\Struct;

class ObjectPropertySetters
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
        foreach ($struct->fields as $field) {

            $phpReturnType = Helper::toPhpType($field);

            $input[] = 'static int php_raylib_' . $struct->nameLower . '_set_' . $field->nameLower . '(php_raylib_' . $struct->nameLower . '_object *obj, zval *newval) /* {{{ */';
            $input[] = '{';
            $input[] = '    int ret = SUCCESS;';
            $input[] = '';

            switch ($phpReturnType) {
                case 'zend_object *';
                    $input[] = '    if (Z_TYPE_P(newval) == IS_NULL) {';
                    $input[] = '        // Cannot set this to null...';
                    $input[] = '        return ret;';
                    $input[] = '    }';
                    $input[] = '';
                    $input[] = '    php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ' = Z_' . $field->typePlainUpper . '_OBJ_P(newval);';
                    $input[] = '    GC_ADDREF(&php' . ucfirst($field->name) . '->std);'; // Add ref to new variable
                    $input[] = '    GC_DELREF(&obj->' . $field->nameLower . '->std);'; // Release old variable
                    $input[] = '    obj->' . $field->nameLower . ' = php' . ucfirst($field->name) . ';';
                    break;
                case 'double';
                    $input[] = '    if (Z_TYPE_P(newval) == IS_NULL) {';
                    $input[] = '        obj->' . $struct->nameLower . '.' . $field->name . ' = 0;';
                    $input[] = '        return ret;';
                    $input[] = '    }';
                    $input[] = '';
                    $input[] = '    obj->' . $struct->nameLower . '.' . $field->name . ' = (' . $field->type . ') zval_get_double(newval);';
                    break;
                case 'zend_long';
                    $input[] = '    if (Z_TYPE_P(newval) == IS_NULL) {';
                    $input[] = '        obj->' . $struct->nameLower . '.' . $field->name . ' = 0;';
                    $input[] = '        return ret;';
                    $input[] = '    }';
                    $input[] = '';
                    $input[] = '    obj->' . $struct->nameLower . '.' . $field->name . ' = (' . $field->type . ') zval_get_long(newval);';
                    break;
                case 'zend_string *';
                    $input[] = '    zend_string *str = zval_get_string(newval);';
                    if ($field->arrayCountNumber) {
                        $input[] = '    strncpy(obj->' . $struct->nameLower . '.' . $field->name . ', ZSTR_VAL(str), ' . $field->arrayCountNumber . ');';
                    } else {
                        $input[] = '    obj->' . $struct->nameLower . '.' . $field->name . ' = ZSTR_VAL(str);';
                    }
                    $input[] = '    zend_string_release_ex(str, 0);';
                    break;
                case 'HashTable *';
                    $input[] = '    //TODO: Set Array Not yet supported';
                    break;
            }

            $input[] = '';
            $input[] = '    return ret;';

            $input[] = '}';
            $input[] = '/* }}} */';
            $input[] = '';
        }


        return $input;
    }
}