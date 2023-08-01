<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Get Garbage Collector? Needed if has properties is available on the object
 */
class ObjectGetGarbageCollector
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static HashTable *php_raylib_' . $struct->nameLower . '_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */';
        $input[] = '{';
        $input[] = '    *gc_data = NULL;';
        $input[] = '    *gc_data_count = 0;';
        $input[] = '    return zend_std_get_properties(object);';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}