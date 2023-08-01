<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Create / Clone Function
 */
class ObjectNew
{
    /**
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(Struct $struct, array $input): array
    {
        $input [] = 'zend_object *php_raylib_' . $struct->nameLower . '_new(zend_class_entry *class_type) /* {{{  */';
        $input [] = '{';
        $input [] = '    return php_raylib_' . $struct->nameLower . '_new_ex(class_type, NULL);';
        $input [] = '}';
        $input [] = '/* }}} */';
        $input [] = '';

        return $input;
    }
}