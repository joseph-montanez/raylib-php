<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

class ObjectPropertyReader
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static zval *php_raylib_' . $struct->nameLower . '_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *obj;';
        $input[] = '    zval *retval = NULL;';
        $input[] = '    raylib_' . $struct->nameLower . '_prop_handler *hnd = NULL;';
        $input[] = '';
        $input[] = '    obj = php_raylib_' . $struct->nameLower . '_fetch_object(object);';
        $input[] = '';
        $input[] = '    if (obj->prop_handler != NULL) {';
        $input[] = '        hnd = zend_hash_find_ptr(obj->prop_handler, name);';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    if (hnd) {';
        $input[] = '        retval = php_raylib_' . $struct->nameLower . '_property_reader(obj, hnd, rv);';
        $input[] = '    } else {';
        $input[] = '        retval = zend_std_read_property(object, name, type, cache_slot, rv);';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    return retval;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}