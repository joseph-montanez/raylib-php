<?php

namespace Raylib\Parser\Generate\Zend;

class ArgBeginInfo
{
    public ?bool $isTentativeReturnType;
    public ?int $requiredNumArgs;
    public ?string $name;
    public ?bool $returnReference;
    public ?bool $allowNull;
    public ?string $className;
    /**
     * @var string|null Can be something like this: MAY_BE_FALSE
     */
    public ?string $type;

    public function isTentativeReturnType($val): static
    {
        $this->isTentativeReturnType = $val;
        return $this;
    }

    public function requiredNumArgs($val): static
    {
        $this->requiredNumArgs = $val;
        return $this;
    }

    public function returnReference($val): static
    {
        $this->returnReference = $val;
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

    public function build()
    {
        if (
            isset($this->passByRef)
            && isset($this->name)
            && isset($this->allowNull)
            && isset($this->isVariadic)
            && $this->isVariadic
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(name, class_name, allow_null) \
            return sprintf("ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(%s, %s, %d)",
                $this->name, $this->className, $this->allowNull
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
            && isset($this->isTentativeReturnType)
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX2(name, return_reference, required_num_args, type, is_tentative_return_type) \
            return sprintf("ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(%s, %d, %d, %s, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type, $this->isTentativeReturnType
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type) \
            return sprintf("ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(%s, %d, %d, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
            && isset($this->isTentativeReturnType)
        ) {
            #define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type) \
            return sprintf("ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_MASK_EX(%s, %d, %d, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->className)
            && isset($this->type)
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) \
            return sprintf("ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(%s, %d, %d, %s, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->className, $this->type
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->className)
            && isset($this->type)
            && isset($this->isTentativeReturnType)
        ) {
            #define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) \
            return sprintf("ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(%s, %d, %d, %s, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->className, $this->type
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
            && isset($this->isTentativeReturnType)
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX2(name, return_reference, required_num_args, type, allow_null, is_tentative_return_type) \
            return sprintf(
                "ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX2(%s, %d, %d, %s, %d, %s)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type, $this->allowNull, $this->isTentativeReturnType
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
            && isset($this->allowNull)
        ) {
            #define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
            return sprintf(
                "ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(%s, %d, %d, %s, %d)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type, $this->allowNull
            );
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
            && isset($this->type)
            && isset($this->allowNull)
            && isset($this->isTentativeReturnType)
        ) {
            #define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
            return sprintf(
                "ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(%s, %d, %d, %s, %d)",
                $this->name, $this->returnReference, $this->requiredNumArgs, $this->type, $this->allowNull
            );
        } elseif (
            isset($this->name)
            && isset($this->type)
            && isset($this->allowNull)
        ) {
            return sprintf("ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(%s, %s, %d)", $this->name, $this->type, $this->allowNull);
        } elseif (
            isset($this->name)
            && isset($this->returnReference)
            && isset($this->requiredNumArgs)
        ) {
            return sprintf("ZEND_BEGIN_ARG_INFO_EX(%s, 0, %d, %d)", $this->name, $this->returnReference, $this->requiredNumArgs);
        } elseif (isset($this->name)) {
            return sprintf("ZEND_BEGIN_ARG_INFO(%s, 0)", $this->name);
        }
    }
}


#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX2(name, return_reference, required_num_args, class_name, allow_null, is_tentative_return_type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(name, class_name, allow_null) \
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX2(name, return_reference, required_num_args, type, is_tentative_return_type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type) \
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX2(name, return_reference, required_num_args, class_name, type, is_tentative_return_type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) \
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX2(name, return_reference, required_num_args, type, allow_null, is_tentative_return_type) \
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(name, type, allow_null) \
#define ZEND_BEGIN_ARG_INFO_EX(name, _unused, return_reference, required_num_args)	\
#define ZEND_BEGIN_ARG_INFO(name, _unused)	\
