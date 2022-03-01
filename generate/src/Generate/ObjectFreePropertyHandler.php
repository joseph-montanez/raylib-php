<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectFreePropertyHandler
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static void php_raylib_' . $struct->nameLower . '_free_prop_handler(zval *el) /* {{{ */';
        $input[] = '{';
        $input[] = '    pefree(Z_PTR_P(el), 1);';
        $input[] = '} /* }}} */';
        $input[] = '';

        return $input;
    }
}