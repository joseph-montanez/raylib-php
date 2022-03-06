<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Func;
use Raylib\Parser\Generate\Zend\ArgBeginInfo;
use Raylib\Parser\Generate\Zend\ArgInfo;
use Raylib\Parser\Generate\Zend\ZParam;
use Raylib\Parser\Helper;

class CFunction
{
    public function gerenate(Func $function, $input)
    {
        if ($function->returnType === 'const void'
            || $function->returnType === 'void *'
            || $function->returnType === 'const void *'
            || strstr($function->returnType, '*') !== false) {
            $function->unsupported = true;
            return $input;
        }
        $params = [];
        /** @var \Raylib\Parser\Param $param */
        foreach ($function->params as $param) {
            if ($param->type === 'const void *'
                || $param->type === 'unsigned char *') {
                $function->unsupported = true;
                return $input;
            }
            $params[] = $param->type . ' ' . $param->name;
        }

        $input[]  = '// ' . $function->description;
        $input[]  = sprintf("// RLAPI %s %s(%s);",
            $function->returnType, $function->name, implode(', ', $params)
        );
        $argInfos = [];
        $refCount = 0;
        foreach ($function->params as $param) {
            $refCount   += $param->isRef ? 1 : 0;
            $argInfos[] = (new ArgInfo())
                    ->passByRef($param->isRef)
                    ->name($param->name);
        }
        $argInfoBegin = (new ArgBeginInfo())
            ->name('arginfo_' . ($function->rename ?? $function->name))
            ->requiredNumArgs($function->paramCount)
            ->returnReference($refCount);
        foreach ($argInfos as $argInfo) {
            $argInfoBegin->add($argInfo);
        }
        $input = array_merge($input, $argInfoBegin->build());
        $input[] = sprintf("PHP_FUNCTION(%s)", $function->rename ?? $function->name);
        $input[] = '{';
        foreach ($function->params as $param) {
            $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr());
            $input = array_merge($input, $zParam->buildVariables('    '));
        }
        $input[] = '';
        if ($function->paramCount > 0) {
            $input[] = sprintf("    ZEND_PARSE_PARAMETERS_START(%d, %d)", $function->paramCount, $function->paramCount);
            foreach ($function->params as $param) {
                $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr());
                $input = array_merge($input, $zParam->build('        '));
            }
            $input[] = '    ZEND_PARSE_PARAMETERS_END();';
            $input[] = '';
        }
        $hasDef = false;
        foreach ($function->params as $param) {
            $tr = $param->getTr();
            $hasDef = true;
            if (!Helper::isPrimitive($param->type)) {
                if ($param->isArray) {
                    $input[] = strtr("    zval *[nameLower]_element;", $tr);
                    $input[] = strtr("    int [nameLower]_index;", $tr);
                    $input[] = strtr("    HashTable *[nameLower]_hash = Z_ARRVAL_P([name]);", $tr);
                    $input[] = strtr("    SEPARATE_ARRAY([name]);", $tr);
                    $input[] = strtr("    int [nameLower]_count = zend_hash_num_elements([nameLower]_hash);", $tr);
                    $input[] = strtr("    [type] [nameLower]_array = safe_emalloc(sizeof([type]), [nameLower]_count, 0);", $tr);

                    $input[] = strtr('    ZEND_HASH_FOREACH_VAL([nameLower]_hash, [nameLower]_element) {', $tr);
                    $input[] = strtr('        ZVAL_DEREF([nameLower]_element);', $tr);
                    $input[] = strtr('        if ((Z_TYPE_P([nameLower]_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P([nameLower]_element), php_raylib_[typeLower]_ce))) {', $tr);
                    $input[] = strtr('            php_raylib_[typeLower]_object *[typeLower]_obj =  Z_[typeUpper]_OBJ_P([nameLower]_element);', $tr);
                    $input[] = strtr('            [nameLower]_array[[nameLower]_index] = [typeLower]_obj->[typeLower];', $tr);
                    $input[] = strtr('        }', $tr);
                    $input[] = strtr('', $tr);
                    $input[] = strtr('        [nameLower]_index++;', $tr);
                    $input[] = strtr('    } ZEND_HASH_FOREACH_END();', $tr);
                } else {
                    $input[] = sprintf("    php_raylib_%s_object *php%s = Z_%s_OBJ_P(%s);", $param->typeLower, $param->nameUpperFirst, $param->typeUpper, $param->name);
                    //-- Update the camera property internal props
                    // This is not optimal, but will do for now...
//                    if (in_array($param->typeLower, ['camera2d', 'camera3d'])) {
                        $input[] = strtr('    php_raylib_[typeLower]_update_intern(php[nameUpperFirst]);', $tr);
//                    }
                }
            } elseif (in_array($param->type, [
                'const char *',
                'char *',
            ])) {

            } elseif ($param->isArray) {
                $input[] = strtr("    zval *[nameLower]_element;", $tr);
                $input[] = strtr("    int [nameLower]_index;", $tr);
                $input[] = strtr("    HashTable *[nameLower]_hash = Z_ARRVAL_P([name]);", $tr);
                $input[] = strtr("    SEPARATE_ARRAY([name]);", $tr);
                $input[] = strtr("    int [nameLower]_count = zend_hash_num_elements([nameLower]_hash);", $tr);
                $input[] = strtr("    [typeNonConst] [nameLower]_array = safe_emalloc(sizeof([typeNonConst]), [nameLower]_count, 0);", $tr);

                $input[] = strtr('    ZEND_HASH_FOREACH_VAL([nameLower]_hash, [nameLower]_element) {', $tr);
                $input[] = strtr('        ZVAL_DEREF([nameLower]_element);', $tr);
                $input[] = strtr('        if (Z_TYPE_P([nameLower]_element) == IS_LONG) {', $tr);
                $input[] = strtr('            [nameLower]_array[[nameLower]_index] = ([typeNoStar]) Z_LVAL_P([nameLower]_element);', $tr);
                $input[] = strtr('        }', $tr);
                $input[] = strtr('', $tr);
                $input[] = strtr('        [nameLower]_index++;', $tr);
                $input[] = strtr('    } ZEND_HASH_FOREACH_END();', $tr);
            }
        }
        if ($hasDef) {
            $input[] = '';
        }

        $fnParams = [];
        foreach ($function->params as $param) {
            $tr = $param->getTr();

            if (Helper::isString($param->type)) {
                $fnParams[] = sprintf("%s->val", $param->name);
            } elseif (Helper::isInt($param->type)) {
                if ($param->isArray) {
                    $fnParams[] = strtr("[nameLower]_array", $tr);
                } else {
                    $fnParams[] = sprintf("(%s <= INT_MAX) ? (int) ((zend_long) %s) : -1", $param->name, $param->name);
                }
            } elseif (Helper::isFloat($param->type)) {
                $fnParams[] = strtr("([type]) [name]", $tr);
            } elseif (Helper::isBool($param->type)) {
                $fnParams[] = strtr("[name]", $tr);
            } elseif (!Helper::isPrimitive($param->type)) {
                if ($param->isArray) {
                    $fnParams[] = strtr("[nameLower]_array", $tr);
                } else {
                    $fnParams[] = sprintf("%sphp%s->%s", $param->isRef ? '&' : '', $param->nameUpperFirst, $param->typeLower);
                }
            } else {
//                var_dump([
//                    'name' => $param->name,
//                    'type' => $param->type,
//                ]);
            }
        }

        if ($function->returnType && $function->returnType !== 'void') {
            if (Helper::isBool($function->returnType)) {
                $input[] = sprintf("    RETURN_BOOL(%s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (Helper::isInt($function->returnType)) {
                $input[] = sprintf("    RETURN_LONG(%s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (Helper::isFloat($function->returnType)) {
                $input[] = sprintf("    RETURN_DOUBLE((double) %s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (!Helper::isPrimitive($function->returnType)) {
                $input[] = sprintf("    %s originalResult = %s(%s);", $function->returnType, $function->name, implode(', ', $fnParams));
                $input[] = sprintf("    zend_object *result = php_raylib_%s_new_ex(php_raylib_%s_ce, NULL);", $function->returnTypeLower, $function->returnTypeLower);
                $input[] = sprintf("    php_raylib_%s_object *phpResult = php_raylib_%s_fetch_object(result);", $function->returnTypeLower, $function->returnTypeLower);
                $input[] = sprintf("    phpResult->%s = originalResult;", $function->returnTypeLower);
                $input[] = '';
                $input[] = sprintf("    RETURN_OBJ(&phpResult->std);", $function->name, implode(', ', $fnParams));
            }
        } else {
            $input[] = '    ' . $function->name . '(' . implode(', ', $fnParams) . ');';
        }

        $input[] = '}';
        $input[] = '';

        return $input;
    }

}