<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Func;
use Raylib\Parser\Generate\Zend\ArgBeginInfo;
use Raylib\Parser\Generate\Zend\ArgInfo;
use Raylib\Parser\Generate\Zend\ZParam;
use Raylib\Parser\Helper;
use Raylib\Parser\Struct;

class CFunction
{
    public function gerenate(Func $function, $input, $structs)
    {
        if ($function->returnType === 'const void'
            || $function->returnType === 'void *'
            || $function->returnType === 'const void *'
            || strstr($function->returnType, '*') !== false) {
            if ($function->returnType === 'char **') {

            } elseif ($function->name === 'LoadModelAnimations') {
                $function->manualCFile = __DIR__ . '/../../manual/LoadModelAnimations.c';
            } else {
                $function->unsupported = true;
                echo "Skipping " . $function->name . "\n";
                return $input;
            }
        }

        if (is_file($function->manualCFile)) {
            $input []= file_get_contents($function->manualCFile) . "\n";
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
            $ref        = Helper::isPrimitive($param->type) && $param->isRef;
            $refCount   += $ref ? 1 : 0;
            $argInfos[] = (new ArgInfo())
                ->passByRef($ref)
                ->name($param->name);
        }
        $argInfoBegin = (new ArgBeginInfo())
            ->name('arginfo_' . ($function->rename ?? $function->name))
            ->requiredNumArgs($function->paramCount)
            ->returnReference($refCount);
        foreach ($argInfos as $argInfo) {
            $argInfoBegin->add($argInfo);
        }
        $input   = array_merge($input, $argInfoBegin->build());
        $input[] = sprintf("PHP_FUNCTION(%s)", $function->rename ?? $function->name);
        $input[] = '{';
        foreach ($function->params as $param) {
            $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr(), $param->isRef);
            $input  = array_merge($input, $zParam->buildVariables('    '));
        }
        $input[] = '';
        if ($function->paramCount > 0) {
            $input[] = sprintf("    ZEND_PARSE_PARAMETERS_START(%d, %d)", $function->paramCount, $function->paramCount);
            foreach ($function->params as $param) {
                $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr(), $param->isRef);
                $input  = array_merge($input, $zParam->build('        '));
            }
            $input[] = '    ZEND_PARSE_PARAMETERS_END();';
            $input[] = '';
        } else {
            $input[] = '    ZEND_PARSE_PARAMETERS_NONE();';
            $input[] = '';
        }
        $hasDef = false;
        foreach ($function->params as $param) {
            $tr     = $param->getTr();
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
                    if ($param->isPrimitive) {
                        $input[] = strtr('        [nameLower]_array[[nameLower]_index] = [nameLower]_element;', $tr);
                    } else {
                        $input[] = strtr('        if ((Z_TYPE_P([nameLower]_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P([nameLower]_element), php_raylib_[typeLower]_ce))) {', $tr);
                        $input[] = strtr('            php_raylib_[typeLower]_object *[typeLower]_obj =  Z_[typeUpper]_OBJ_P([nameLower]_element);', $tr);
                        $input[] = strtr('            [nameLower]_array[[nameLower]_index] = *php_raylib_[typeLower]_fetch_data([typeLower]_obj);', $tr);
                        $input[] = strtr('        }', $tr);
                    }
                    $input[] = strtr('', $tr);
                    $input[] = strtr('        [nameLower]_index++;', $tr);
                    $input[] = strtr('    } ZEND_HASH_FOREACH_END();', $tr);
                } else {
                    $input[] = sprintf("    php_raylib_%s_object *php%s = Z_%s_OBJ_P(%s);", $param->typeLower, $param->nameUpperFirst, $param->typeUpper, $param->name);
                }
            } elseif (in_array($param->type, [
                'const char *',
                'char *',
            ])) {

            } elseif ($param->isRef) {
                $input[] = strtr("    [typeNoStar] [name]_in;", $tr);
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
                if ($param->isRef) {
                    $fnParams[] = strtr("&[name]_in", $tr);
                } elseif ($param->isArray) {
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
                    $fnParams[] = sprintf("%sphp_raylib_%s_fetch_data(php%s)", $param->isRef ? '' : '*', $param->typeLower, $param->nameUpperFirst);
                }
            } else {
            }
        }

        if ($function->returnType && $function->returnType !== 'void') {
            if (Helper::isBool($function->returnType)) {
                $input[] = sprintf("    RETURN_BOOL(%s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (Helper::isInt($function->returnType)) {
                $input[] = sprintf("    RETURN_LONG(%s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (Helper::isFloat($function->returnType)) {
                $input[] = sprintf("    RETURN_DOUBLE((double) %s(%s));", $function->name, implode(', ', $fnParams));
            } elseif (Helper::isString($function->returnType)) {
                if ($function->returnIsArray) {
                    $tr                            = [];
                    $tr['[returnArrayCountField]'] = $function->returnArrayCountField;
                    $tr['[function]']              = $function->name;
                    $tr['[returnType]']            = $function->returnType;
                    $tr['[params]']                = implode(', ', $fnParams);

                    $inParam = null;
                    foreach ($function->params as $param) {
                        if ($param->name === $function->returnArrayCountField) {
                            $inParam = $param;
                            break;
                        }
                    }

                    $input[] = strtr("    [returnType] result_value =  [function]([params]);", $tr);
                    $input[] = strtr("    // Assign back the in-parameter to the original tracked value", $tr);
                    $input[] = strtr("    ZEND_TRY_ASSIGN_REF_LONG([returnArrayCountField], [returnArrayCountField]_in);", $tr);
                    //ZVAL_STRING
                    $input[] = '';

                    $input[] = strtr("    HashTable *return_hash;", $tr);
                    $input[] = strtr("    ALLOC_HASHTABLE(return_hash);", $tr);
                    $input[] = strtr("    zend_hash_init(return_hash, [returnArrayCountField]_in, NULL, NULL, 0);", $tr);
                    $input[] = '';


                    $input[] = strtr("    for (int i = 0; i < [returnArrayCountField]_in; i++) {", $tr);
                    $input[] = strtr("        zval zv;", $tr);
//                    $input[] = strtr("        MAKE_STD_ZVAL(zv);", $tr);
//                    $input[] = strtr("        ZVAL_STRINGL(&zv, result_value[i], strlen(result_value[i]));", $tr);
                    $input[] = strtr("        ZVAL_STRING(&zv, result_value[i]);", $tr);
                    $input[] = strtr("        zend_hash_index_update(return_hash, i, &zv);", $tr);
                    $input[] = strtr("    }", $tr);
                    $input[] = '';
                    $input[] = strtr("    RETURN_ARR(return_hash);", $tr);
                } else {
                    $input[] = sprintf("    RETURN_STRING((char *) %s(%s));", $function->name, implode(', ', $fnParams));
                }
            } elseif (!Helper::isPrimitive($function->returnType)) {
                $input[] = sprintf("    %s originalResult = %s(%s);", $function->returnType, $function->name, implode(', ', $fnParams));
                $input[] = sprintf("    zend_object *result = php_raylib_%s_new_ex(php_raylib_%s_ce, NULL);", $function->returnTypeLower, $function->returnTypeLower);
                $input[] = sprintf("    php_raylib_%s_object *phpResult = php_raylib_%s_fetch_object(result);", $function->returnTypeLower, $function->returnTypeLower);
                $input[] = sprintf("    %s *%sData = php_raylib_%s_fetch_data(phpResult);", $function->returnType, $function->returnTypeLower, $function->returnTypeLower);
                $input[] = sprintf("    // Dereference %sData for assignment back to object", $function->returnTypeLower);
                $input[] = sprintf("    *%sData = originalResult;", $function->returnTypeLower);
                $input[] = '';

                //-- Fully populate the internal sub objects
                if ($function->isConstructor) {
                    /** @var Struct $matchedStruct */
                    $matchedStruct = null;
                    foreach ((array) $structs as $struct) {
                        if ($struct->name === $function->returnType) {
                            $matchedStruct = $struct;
                            break;
                        }
                    }

                    foreach ($matchedStruct->nonPrimitiveFields as $field) {
                        if ($field->isArray) {

                            $input[] = sprintf("    for (int i = 0; i < php_raylib_%s_fetch_data(phpResult)->%s; i++) {", $function->returnTypeLower, $field->arrayCountField);
//                            $input[] = sprintf("        zend_object *%sResult = php_raylib_%s_new_ex(php_raylib_model_ce, NULL);", $field->name, $field->typePlainLower);
//                            $input[] = sprintf("        add_next_index_object(&phpResult->%s, %sResult);",
//                                $field->name, $field->name);
//                            $input[] = sprintf("        // add_next_index_object(&phpResult->%s, php_raylib_%s_fetch_data(phpResult)->%s[i]);",
//                                $field->name, $function->returnTypeLower, $field->name);


                            $input []= '        // Create PHP Object holder of this data';
                            $input []= '        zend_object *' . $field->name . 'Result = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, NULL);';
                            $input []= '';
                            $input []= '        // Fetch the data inside the PHP Object';
                            $input []= '        php_raylib_' . $field->typePlainLower . '_object *p' . ucfirst($field->typePlainLower) . 'Object = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . 'Result);';
                            $input []= '        ' . $field->typePlain . ' *' . $field->typePlainLower . 'Element = php_raylib_' . $field->typePlainLower . '_fetch_data(p' . ucfirst($field->typePlainLower) . 'Object);';
                            $input []= '';
                            $input []= '        // Link this as a pointer, rather than copying data between each other';
                            $input []= '        p' . ucfirst($field->typePlainLower) . 'Object->' . $field->typePlainLower . '->type = RL_' . $field->typePlainUpper . '_IS_POINTER;';
                            $input []= '        p' . ucfirst($field->typePlainLower) . 'Object->' . $field->typePlainLower . '->data.p = &php_raylib_' . $function->returnTypeLower . '_fetch_data(phpResult)->' . $field->name . '[i];';
                            $input []= '';

                            $input []= '        // Go through each sub-object and assign values (references)';
                            /** @var Struct $struct */
                            foreach ((array) $structs as $struct) {
                                if ($struct->name === $field->typePlain) {
                                    foreach ($struct->nonPrimitiveFields as $typeField) {
                                        if ($typeField->isArray) {
                                            $maxStructArray = $typeField->arrayCountNumber > 0 ? $typeField->arrayCountNumber : '0 /* todo */';
                                            $input [] = '        for (int n = 0; n < ' . $maxStructArray . '; n++) {';
                                            $input [] = '            MaterialMap *' . lcfirst($typeField->typePlain) . ' = &p' . ucfirst($field->typePlainLower) . 'Object->' . $field->typePlainLower . '->data.p->' . $typeField->name . '[n];';
                                            $input [] = '';

                                            $input [] = '            // Create PHP Object holder of this data';
                                            $input [] = '            zend_object *' . lcfirst($typeField->typePlain) . 'Result = php_raylib_' . $typeField->typePlainLower . '_new_ex(php_raylib_' . $typeField->typePlainLower . '_ce, NULL);';
                                            $input [] = '            php_raylib_' . $typeField->typePlainLower . '_object *p' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object = php_raylib_' . $typeField->typePlainLower . '_fetch_object(' . lcfirst($typeField->typePlain) . 'Result);';
                                            $input [] = '';

                                            $input [] = '            p' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object->' . $typeField->typePlainLower . '->type = RL_' . $typeField->typePlainUpper . '_IS_POINTER;';
                                            $input [] = '            p' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object->' . $typeField->typePlainLower . '->data.p = ' . lcfirst($typeField->typePlain) . ';';
                                            $input [] = '';

                                            $input [] = '            /*';
                                            $input [] = '            * Need to also populate the following sub SUB objects';
                                            $input [] = '            * zval texture;';
                                            $input [] = '            * zval color;';
                                            $input [] = '            */';
                                            $input [] = '';


                                            $input [] = '            add_next_index_object(&p' . ucfirst($field->typePlainLower) . 'Object->maps, ' . lcfirst($typeField->typePlain) . 'Result);';

                                            $input [] = '        }';
                                        } else {
                                            $input []= '        php_raylib_' . $typeField->typePlainLower . '_object *php' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object = Z_' . $typeField->typePlainUpper . '_OBJ_P(&p' . ucfirst($field->typePlainLower) . 'Object->' . $typeField->name . ');';
                                            $input []= '        php' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object->' . $typeField->typePlainLower . '->type = RL_' . $typeField->typePlainUpper . '_IS_POINTER;';
                                            $input []= '        php' . ucfirst($field->typePlainLower) . ucfirst($typeField->nameLower) . 'Object->' . $typeField->typePlainLower . '->data.p = &p' . ucfirst($field->typePlainLower) . 'Object->' . $field->typePlainLower . '->data.p->' . $typeField->name . ';';
                                        }
                                        $input []= '';
                                    }

                                }
                            }

                            $input []= '        // Push element to PHP array which should just be an object that is also a data pointer,';
                            $input []= '        // if this is changed should update original data?';
                            $input []= '        add_next_index_object(&phpResult->' . $field->nameLower . ', ' . $field->name . 'Result);';

                            $input[] = '    }';
                        }
                        $input[] = '';
                    }

                    $input[] = '';
                }


                $input[] = '    RETURN_OBJ(&phpResult->std);';
            }
        } else {
            $input[] = '    ' . $function->name . '(' . implode(', ', $fnParams) . ');';
            $input[] = '';

        }

        $input[] = '}';
        $input[] = '';

        return $input;
    }

    public function buildParams(Func $function): array
    {
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
            }
        }

        return $fnParams;
    }
}
