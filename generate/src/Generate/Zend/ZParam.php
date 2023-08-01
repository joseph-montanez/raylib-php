<?php

namespace Raylib\Parser\Generate\Zend;

use JetBrains\PhpStorm\Pure;
use Raylib\Parser\Helper;

class ZParam
{
    public string $name;
    public string $type;
    public bool $isArray;
    public array $tr;
    public bool $isRef;

    #[Pure] public function __construct($name, $type, $isArray, array $tr, $isRef)
    {
        $this->tr      = $tr;
        $this->name    = $name;
        $this->type    = $type;
        $this->isArray = $isArray;
        $this->isRef   = $isRef;
    }

    #[Pure] public function build($spacer = ''): array
    {
        $input = [];

        if (Helper::isString($this->type)) {
            $input[] = sprintf("%sZ_PARAM_STR(%s)", $spacer, $this->name);
        } elseif (Helper::isInt($this->type)) {
            if ($this->isRef) {
                $input[] = sprintf("%sZ_PARAM_ZVAL(%s)", $spacer, $this->name);
            } elseif($this->isArray) {
                $input[] = sprintf("%sZ_PARAM_ARRAY(%s)", $spacer, $this->name);
            } else {
                $input[] = sprintf("%sZ_PARAM_LONG(%s)", $spacer, $this->name);
            }
        } elseif (Helper::isFloat($this->type)) {
            if ($this->isRef) {
                $input[] = sprintf("%sZ_PARAM_ZVAL(%s)", $spacer, $this->name);
            } elseif($this->isArray) {
                $input[] = sprintf("%sZ_PARAM_ARRAY(%s)", $spacer, $this->name);
            } else {
                $input[] = sprintf("%sZ_PARAM_DOUBLE(%s)", $spacer, $this->name);
            }
        } elseif (Helper::isBool($this->type)) {
            $input[] = sprintf("%sZ_PARAM_BOOL(%s)", $spacer, $this->name);
        } elseif (!Helper::isPrimitive($this->type)) {
            if ($this->isArray) {
                $input[] = sprintf("%sZ_PARAM_ARRAY(%s)", $spacer, $this->name);
            } else {
                $input[] = sprintf("%sZ_PARAM_ZVAL(%s)", $spacer, $this->name);
            }
        }

        return $input;
    }

    #[Pure] public function buildVariables($spacer = ''): array
    {
        $tr             = $this->tr;
        $tr['[spacer]'] = $spacer;

        $input = [];

        if (Helper::isString($this->type)) {
            $input[] = strtr("[spacer]zend_string *[name];", $tr);
        } elseif (Helper::isInt($this->type)) {
            if ($this->isArray || $this->isRef) {
                $input[] = strtr("[spacer]zval *[name];", $tr);
            } else {
                $input[] = strtr("[spacer]zend_long [name];", $tr);
            }
        } elseif (Helper::isFloat($this->type)) {
            if ($this->isArray || $this->isRef) {
                $input[] = strtr("[spacer]zval *[name];", $tr);
            } else {
                $input[] = strtr("[spacer]double [name];", $tr);
            }
        } elseif (Helper::isBool($this->type)) {
            $input[] = strtr("[spacer]bool [name];", $tr);
        } elseif (!Helper::isPrimitive($this->type)) {
            $input[] = strtr("[spacer]zval *[name];", $tr);
        }

        return $input;
    }
}