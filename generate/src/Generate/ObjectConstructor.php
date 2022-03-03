<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Generate\Zend\ArgBeginInfo;
use Raylib\Parser\Generate\Zend\ArgInfo;
use Raylib\Parser\Struct;

/**
 * Generates PHP Object Create / Clone Function
 */
class ObjectConstructor
{
    /**
     * @param \Raylib\Parser\Func[]   $functions
     * @param \Raylib\Parser\Struct[] $structsByType
     * @param \Raylib\Parser\Struct   $struct
     * @param array                   $input
     *
     * @return array
     */
    public function generate(array $functions, array $structsByType, Struct $struct, array $input): array
    {
        $input[] = '// PHP object handling';
        $constrcutorFn = null;
        if ($struct->constructorFunction) {
            foreach ($functions as $function) {
                if ($function->name === $struct->constructorFunction) {
                    $constrcutorFn = $function;
                    break;
                }
            }
        }

        $argInfoBegin = new ArgBeginInfo();
        if ($constrcutorFn) {
            /** @var \Raylib\Parser\Param $param */
            foreach ($constrcutorFn->params as $param) {
                $argInfo = new ArgInfo();
                $argInfo->name($param->name);
                $argInfoBegin->add($argInfo);
            }

        } else {
            $argInfoBegin->name('arginfo_' . $struct->nameLower . '__construct')
                ->requiredNumArgs(0)
                ->returnReference(0);
        }
        $input[] = $argInfoBegin->build();
        
        $input[] = 'PHP_METHOD(' . $struct->name . ', __construct)';
        $input[] = '{';
        //-- Add magic here
        $input[] = '}';
        $input[] = '';

        return $input;
    }
}