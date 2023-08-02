<?php

namespace Raylib\Parser\Generate\Zend;

class ArgInfo
{
    public ?bool $passByRef;
    public ?string $name;
    public ?string $typeHint;
    public ?bool $allowNull;
    public ?string $className;
    /**
     * @var string|null Can be something like this: MAY_BE_OBJECT|MAY_BE_STRING|MAY_BE_NULL
     */
    public ?string $typeMask;
    /**
     * @var string|null Can be "null", "[]", "0", everything is wrapped in a string
     */
    public ?string $defaultValue;
    public ?bool $isArray;
    public ?bool $isCallable;
    public ?bool $isVariadic;

    public function passByRef($val): static
    {
        $this->passByRef = $val;
        return $this;
    }

    public function name($val): static
    {
        $this->name = $val;
        return $this;
    }

    public function typeHint($val): static
    {
        $this->typeHint = $val;
        return $this;
    }

    public function allowNull($val): static
    {
        $this->allowNull = $val;
        return $this;
    }

    public function className($val): static
    {
        $this->className = $val;
        return $this;
    }

    public function typeMask($val): static
    {
        $this->typeMask = $val;
        return $this;
    }

    public function defaultValue($val): static
    {
        $this->defaultValue = $val;
        return $this;
    }

    public function isArray($val): static
    {
        $this->isArray = $val;
        return $this;
    }

    public function isCallable($val): static
    {
        $this->isCallable = $val;
        return $this;
    }

    public function isVariadic($val): static
    {
        $this->isVariadic = $val;
        return $this;
    }

    public function getDefaultValue()
    {
        if ($this->defaultValue === 'null') {
            return 'NULL';
        } elseif (is_numeric($this->defaultValue)
            || $this->defaultValue === '[]'
            || $this->defaultValue === 'static') {
            return '"' . $this->defaultValue . '"';
        } else {
            return '"' . str_replace('"', '\\"', $this->defaultValue) . '"';
        }
    }

    public function getPassByRef()
    {
        if (!$this->passByRef) {
            return 0;
        } else {
            return 1;
        }
    }

    public function build()
    {
        if (
            isset($this->passByRef)
            && isset($this->name)
            && isset($this->allowNull)
            && isset($this->isVariadic)
            && $this->isVariadic
        ) {
            return sprintf("ZEND_ARG_VARIADIC_OBJ_INFO(%s, %s, %s, %s)",
                $this->getPassByRef(), $this->name, $this->className, $this->allowNull
            );
        } elseif (
            isset($this->passByRef)
            && isset($this->name)
            && isset($this->allowNull)
            && isset($this->isCallable)
            && $this->isCallable
        ) {
            return sprintf("ZEND_ARG_CALLABLE_INFO(%s, %s, %s)",
                $this->getPassByRef(), $this->name, $this->allowNull
            );
        } elseif (
            isset($this->passByRef)
            && isset($this->name)
            && isset($this->allowNull)
            && isset($this->isArray)
            && $this->isArray
        ) {
            return sprintf("ZEND_ARG_ARRAY_INFO(%s, %s, %s)",
                $this->getPassByRef(), $this->name, $this->allowNull
            );
        } elseif (
            isset($this->passByRef)
            && isset($this->name)
            && isset($this->className)
            && isset($this->allowNull)
            && isset($this->defaultValue)
        ) {
            return sprintf("ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(%s, %s, %s, %s, %s)",
                $this->getPassByRef(), $this->name, $this->className, $this->allowNull, $this->getDefaultValue()
            );
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->className)
            && isset($this->allowNull)
        ) {
            return sprintf("ZEND_ARG_OBJ_INFO(%s, %s, %s, %s)", $this->getPassByRef(), $this->name, $this->className, $this->allowNull);
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->className)
            && isset($this->typeMask)
            && isset($this->defaultValue)
        ) {
            return sprintf("ZEND_ARG_OBJ_TYPE_MASK(%s, %s, %s, %s, %s)", $this->getPassByRef(), $this->name, $this->className, $this->typeMask, $this->getDefaultValue());
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->typeMask)
            && isset($this->defaultValue)
        ) {
            $mask = [$this->typeMask];
            if ($this->allowNull) {
                $mask []= 'MAY_BE_NULL';
            }
            return sprintf("ZEND_ARG_TYPE_MASK(%s, %s, %s, %s)", $this->getPassByRef(), $this->name, implode('|', $mask), $this->getDefaultValue());
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->typeHint)
            && isset($this->allowNull)
            && isset($this->defaultValue)
        ) {
            return sprintf("ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(%s, %s, %s, %s, %s)", $this->getPassByRef(), $this->name, $this->typeHint, $this->allowNull, $this->getDefaultValue());
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->typeHint)
            && isset($this->allowNull)
        ) {
            return sprintf("ZEND_ARG_TYPE_INFO(%s, %s, %s, %s)", $this->getPassByRef(), $this->name, $this->typeHint, $this->allowNull);
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->isVariadic)
            && $this->isVariadic
        ) {
            return sprintf("ZEND_ARG_VARIADIC_INFO(%s, %s)", $this->getPassByRef(), $this->name);
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
            && isset($this->defaultValue)
        ) {
            return sprintf("ZEND_ARG_INFO_WITH_DEFAULT_VALUE(%s, %s, %s)", $this->getPassByRef(), $this->name, $this->getDefaultValue());
        } elseif (
               isset($this->passByRef)
            && isset($this->name)
        ) {
            return sprintf("ZEND_ARG_INFO(%s, %s)", $this->getPassByRef(), $this->name);
        }
    }
}
