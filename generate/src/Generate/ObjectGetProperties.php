<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Get Properties
 */
class ObjectGetProperties
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static HashTable *php_raylib_' . $struct->nameLower . '_get_properties(zend_object *object)/* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *obj;';
        $input[] = '    HashTable *props;';
        $input[] = '    raylib_' . $struct->nameLower . '_prop_handler *hnd;';
        $input[] = '    zend_string *key;';
        $input[] = '';
        $input[] = '    obj = php_raylib_' . $struct->nameLower . '_fetch_object(object);';
        $input[] = '    props = zend_std_get_properties(object);';
        $input[] = '';
        $input[] = '    if (obj->prop_handler == NULL) {';
        $input[] = '        return NULL;';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {';
        $input[] = '    zval *ret, val;';
        $input[] = '        ret = php_raylib_' . $struct->nameLower . '_property_reader(obj, hnd, &val);';
        $input[] = '        if (ret == NULL) {';
        $input[] = '            ret = &EG(uninitialized_zval);';
        $input[] = '        }';
        $input[] = '        zend_hash_update(props, key, ret);';
        $input[] = '    } ZEND_HASH_FOREACH_END();';
        $input[] = '';
        $input[] = '    return props;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}