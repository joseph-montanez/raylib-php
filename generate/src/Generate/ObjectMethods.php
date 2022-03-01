<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectMethods
{
    public function generate(Struct $struct, array $input): array
    {
        $input [] = 'const zend_function_entry php_raylib_' . $struct->nameLower . '_methods[] = {';
//        $input [] = '        PHP_ME(' . $struct->nameLower . ', __construct, arginfo_' . $struct->nameLower . '__construct, ZEND_ACC_PUBLIC)';
//        $input [] = '        PHP_ME(' . $struct->nameLower . ', getX, arginfo_' . $struct->nameLower . '_getX, ZEND_ACC_PUBLIC)';
//        $input [] = '        PHP_ME(' . $struct->nameLower . ', setX, arginfo_' . $struct->nameLower . '_setX, ZEND_ACC_PUBLIC)';
//        $input [] = '        PHP_ME(' . $struct->nameLower . ', getY, arginfo_' . $struct->nameLower . '_getY, ZEND_ACC_PUBLIC)';
//        $input [] = '        PHP_ME(' . $struct->nameLower . ', setY, arginfo_' . $struct->nameLower . '_setY, ZEND_ACC_PUBLIC)';
        $input [] = '        PHP_FE_END';
        $input [] = '};';

        return $input;
    }
}