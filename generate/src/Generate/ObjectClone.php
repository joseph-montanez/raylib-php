<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Create / Clone Function
 */
class ObjectClone
{
    /**
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(Struct $struct, array $input): array
    {
        $input [] = 'static zend_object *php_raylib_' . $struct->nameLower . '_clone(zend_object *old_object) /* {{{  */';
        $input [] = '{';
        $input [] = '    zend_object *new_object;';
        $input [] = '';
        $input [] = '    new_object = php_raylib_' . $struct->nameLower . '_new_ex(old_object->ce, old_object);';
        $input [] = '';
        $input [] = '    zend_objects_clone_members(new_object, old_object);';
        $input [] = '';
        $input [] = '    return new_object;';
        $input [] = '}';
        $input [] = '/* }}} */';
        $input [] = '';

        return $input;
    }
}