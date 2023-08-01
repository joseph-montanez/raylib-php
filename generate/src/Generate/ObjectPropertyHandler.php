<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Helper;
use Raylib\Parser\Struct;

class ObjectPropertyHandler
{
    /**
     * @param \Raylib\Parser\Struct[] $structsByType
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(array $structsByType, Struct $struct, array $input)
    {
        $input[] = 'static void php_raylib_' . $struct->nameLower . '_register_prop_handler(HashTable *prop_handler, char *name,';
        $fieldParamHandlers = [];
        $fieldParamAssignments = [];
        $structName = str_replace(['*', ' '], '', $struct->nameLower);
        $structName = str_replace('__', '_', $structName);

        foreach ($struct->fieldsByType() as $type) {
            $fieldName = $type->fieldName;
            $fieldName = str_replace(['*', ' '], '', $fieldName);
            $fieldName = str_replace('__', '_', $fieldName);

            $fieldParamHandlers[] = '                                                      raylib_' . $structName . '_read_' . $fieldName . '_t read_' . $fieldName . '_func';
            $fieldParamHandlers[] = '                                                      raylib_' . $structName . '_write_' . $fieldName . '_t write_' . $fieldName . '_func';

            $fieldParamAssignments[] = '    hnd.read_' . $fieldName . '_func = read_' . $fieldName . '_func;';
            $fieldParamAssignments[] = '    hnd.write_' . $fieldName . '_func = write_' . $fieldName . '_func;';
        }
        $input[] = implode(",\n", $fieldParamHandlers) . ') /* {{{ */';
        $input[] = '{';
        $input[] = '    raylib_' . $struct->nameLower . '_prop_handler hnd;';
        $input[] = '';
        $input[] = implode("\n", $fieldParamAssignments);
        $input[] = '';
        $input[] = '    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_' . $struct->nameLower . '_prop_handler));';
        $input[] = '';
        $input[] = '    /* Register for reflection */';
        $input[] = '    zend_declare_property_null(php_raylib_' . $struct->nameLower . '_ce, name, strlen(name), ZEND_ACC_PUBLIC);';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        //-- Property Reader
        //-- This looks at the property type and passes it to the corresponding reader function and returns the value
        $input[] = 'static zval *php_raylib_' . $structName . '_property_reader(php_raylib_' . $structName . '_object *obj, raylib_' . $structName . '_prop_handler *hnd, zval *rv) /* {{{ */';
        $input[] = '{';

        $statements = [];
        foreach ($struct->fieldsByType() as $type) {
            $fieldName = $type->fieldName;
            $fieldName = str_replace(['*', ' '], '', $fieldName);
            $fieldName = str_replace('__', '_', $fieldName);

            $statement = [];

            $statement[] = '(obj != NULL && hnd->read_' . $fieldName . '_func) {';
            if (!$type->isPrimitive) {
                if ($type->isArray) {
                    $statement[] = '        HashTable *ret = hnd->read_' . $fieldName . '_func(obj);';
                    $statement[] = '        ZVAL_ARR(rv, ret);';
                } else {
                    $statement[] = '        zend_object *ret = hnd->read_' . $fieldName . '_func(obj);';
                    $statement[] = '        ZVAL_OBJ(rv, ret);';
                }
            } elseif (Helper::isFloat($type->type)) {
                if ($type->isArray) {
                    $statement[] = '        ZVAL_ARR(rv, hnd->read_' . $fieldName . '_func(obj));';
                } else {
                    $statement[] = '        ZVAL_DOUBLE(rv, hnd->read_' . $fieldName . '_func(obj));';
                }
            } elseif (Helper::isInt($type->type)) {
                if ($type->isArray) {
                    $statement[] = '        ZVAL_ARR(rv, hnd->read_' . $fieldName . '_func(obj));';
                } else {
                    $statement[] = '        ZVAL_LONG(rv, hnd->read_' . $fieldName . '_func(obj));';
                }
            }
            $statement[] = '    }';


            $statements[] = implode("\n", $statement);
            /*
             * {
                php_error_docref(NULL, E_WARNING, "Internal raylib color error returned");
            }
             */
        }
        $input[] = '    if ' . implode("\n    else if ", $statements);
        $input[] = '';
        $input[] = '    return rv;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}