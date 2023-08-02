<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectFreeStorage
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'void php_raylib_' . $struct->nameLower . '_free_storage(zend_object *object)/* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *intern = php_raylib_' . $struct->nameLower . '_fetch_object(object);';
        $input[] = '';

        $input[] = '    intern->' . $struct->nameLower . '->refCount--;';
        $input[] = '    if (intern->' . $struct->nameLower . '->refCount < 1) {';
        $input[] = '        RL_' . $struct->name . '_Free(intern->' . $struct->nameLower . ');';
        $input[] = '    }';
        $input[] = '';

        $input[] = '    zend_object_std_dtor(&intern->std);';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}
