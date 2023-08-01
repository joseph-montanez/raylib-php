<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

class ObjectPropertyWriter
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static zval *php_raylib_' . $struct->nameLower . '_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *obj;';
        $input[] = '    raylib_' . $struct->nameLower . '_prop_handler *hnd;';
        $input[] = '';
        $input[] = '    obj = php_raylib_' . $struct->nameLower . '_fetch_object(object);';
        $input[] = '';
        $input[] = '    if (obj->prop_handler != NULL) {';
        $input[] = '        hnd = zend_hash_find_ptr(obj->prop_handler, member);';
        $input[] = '    }';
        $input[] = '';

        $stmts = [];
        foreach ($struct->fieldsByType() as $field) {
            $stmt = [];
            $stmt[] = 'if (hnd && hnd->write_' . $field->typeName . '_func) {';
            $stmt[] = '        hnd->write_' . $field->typeName . '_func(obj, value);';
            $stmt[] = '    }';

            $stmts[] = implode("\n", $stmt);
        }
        $input[] = '    ' . implode(" else ", $stmts). ' else {';
        $input[] = '        value = zend_std_write_property(object, member, value, cache_slot);';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    return value;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}