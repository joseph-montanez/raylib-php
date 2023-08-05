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
                    // php_raylib_vector3_object *rl_vector3 = Z_VECTOR3_OBJ_P(newval);
                    if ($field->typePlainLower !== 'raudioprocessor') {
                        $input[] = '    php_raylib_' . $field->typePlainLower . '_object *rl_' . $field->typePlainLower . ' = Z_' . $field->typePlainUpper . '_OBJ_P(newval);';
                        $input[] = '    rl_' . $field->typePlainLower . '->' . $field->typePlainLower . '->refCount++;';
                        $input[] = '';
                    }
                    $input[] = '    obj->' . $field->nameLower . ' = *newval;';
                    break;
                case 'double';
                    $input[] = '    if (Z_TYPE_P(newval) == IS_NULL) {';
                    $input[] = '        php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ' = 0;';
                    $input[] = '        return ret;';
                    $input[] = '    }';
                    $input[] = '';
                    $input[] = '    php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ' = (' . $field->type . ') zval_get_double(newval);';
                    break;
                case 'zend_long';
                    $input[] = '    if (Z_TYPE_P(newval) == IS_NULL) {';
                    $input[] = '        php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ' = 0;';
                    $input[] = '        return ret;';
                    $input[] = '    }';
                    $input[] = '';
                    $input[] = '    php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ' = (' . $field->type . ') zval_get_long(newval);';
                    break;
                case 'zend_string *';
                    $input[] = '    zend_string *str = zval_get_string(newval);';
                    if ($field->arrayCountNumber) {
                        $input[] = '    strncpy(php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ', ZSTR_VAL(str), ' . $field->arrayCountNumber . ');';
                    } else {
                        $input[] = '   php_raylib_' . $struct->nameLower . '_fetch_data(obj)->' . $field->name . ' = ZSTR_VAL(str);';
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
