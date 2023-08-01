<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

class ObjectGetPropertyPointerPointer
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
        // To be honest no idea what this does but its needed
        $input[] = 'static zval *php_raylib_' . $struct->nameLower . '_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */';
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
        $input[] = '    if (hnd == NULL) {';
        $input[] = '        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    return retval;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}