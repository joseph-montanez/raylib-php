<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectMethods
{
    public function generate(Struct $struct, array $extras, array $input): array
    {
        $input [] = 'const zend_function_entry php_raylib_' . $struct->nameLower . '_methods[] = {';
        $input [] = '        PHP_ME(' . $struct->name . ', __construct, arginfo_' . $struct->nameLower . '__construct, ZEND_ACC_PUBLIC)';
        foreach ($extras as $extra) {
            $input [] = '        ' . $extra;
        }
        $input [] = '        PHP_FE_END';
        $input [] = '};';

        return $input;
    }
}