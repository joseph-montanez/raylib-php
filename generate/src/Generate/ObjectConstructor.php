<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Generate\Zend\ArgBeginInfo;
use Raylib\Parser\Generate\Zend\ArgInfo;
use Raylib\Parser\Generate\Zend\ZParam;
use Raylib\Parser\Helper;
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
        $input[]       = '// PHP object handling';
        $constructorFn = null;
        if ($struct->constructorFunction) {
            foreach ($functions as $function) {
                if ($function->name === $struct->constructorFunction) {
                    $constructorFn = $function;
                    break;
                }
            }
        }

        $argInfoBegin = new ArgBeginInfo();
        if ($constructorFn) {
            $argInfoBegin->name('arginfo_' . $struct->nameLower . '__construct')
                ->requiredNumArgs($constructorFn->paramCount)
                ->returnReference(0);
            /** @var \Raylib\Parser\Param $param */
            foreach ($constructorFn->params as $param) {
                $argInfo = new ArgInfo();
                $argInfo->name($param->name)
                    ->passByRef(false);
                $argInfoBegin->add($argInfo);
            }
        } else {
            $argInfoBegin->name('arginfo_' . $struct->nameLower . '__construct')
                ->requiredNumArgs(0)
                ->returnReference(0);
            foreach ($struct->fields as $field) {
                $argInfo = new ArgInfo();
                $argInfo->allowNull(true)
                    ->passByRef(false)
                    ->name($field->name);
                if ($field->isPrimitive) {
                    if (Helper::isFloat($field->type)) {
                        $argInfo->typeMask('IS_DOUBLE')->defaultValue(0.00);
                    } elseif (Helper::isInt($field->type)) {
                        $argInfo->typeMask('IS_LONG')->defaultValue(0);
                    } elseif (Helper::isString($field->type)) {
                        $argInfo->typeMask('IS_STRING')->defaultValue('');
                    } elseif (Helper::isBool($field->type)) {
                        $argInfo->typeMask('_IS_BOOL')->defaultValue(1);
                    }
                } else {
                    $argInfo->className('raylib\\\\' . $field->typePlain);
                }

                $argInfoBegin->add($argInfo);
            }
        }

        $input = array_merge($input, $argInfoBegin->build());

        $input[] = 'PHP_METHOD(' . $struct->name . ', __construct)';
        $input[] = '{';

        if (in_array($struct->name, ['AudioStream', 'Wave', 'Model', 'ModelAnimation', 'VrDeviceInfo', 'Music', 'VrStereoConfig', 'Material', 'Mesh', 'Shader', 'BoneInfo'])) {
            $input[] = '}';
            $input[] = '';

            return $input;
        }

        if ($constructorFn) {
            foreach ($constructorFn->params as $param) {
                $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr(), $param->isRef);
                $input = array_merge($input, $zParam->buildVariables('    '));
            }
            $input[] = '';
            $input[] = sprintf("    ZEND_PARSE_PARAMETERS_START(%d, %d)", $constructorFn->paramCount, $constructorFn->paramCount);
            foreach ($constructorFn->params as $param) {
                $zParam = new ZParam($param->name, $param->type, $param->isArray, $param->getTr(), $param->isRef);
                $input = array_merge($input, $zParam->build('        '));
            }
            $input[] = '    ZEND_PARSE_PARAMETERS_END();';
            $input[] = '';
            $input[] = '';
            $input[] = '    php_raylib_' . $struct->nameLower . '_object *intern = Z_' . $struct->nameUpper . '_OBJ_P(ZEND_THIS);';
            $input[] = '    intern->' . $struct->nameLower . ' = ' . $constructorFn->name . '(' . implode(',', (new CFunction())->buildParams($constructorFn)) . ');';
        } else {
            foreach ($struct->fields as $field) {
                if ($field->isPrimitive) {
                    $zParam = new ZParam($field->name, $field->type, $field->isArray, $field->getTr(), $field->isRef ?? false);
                    $input = array_merge($input, $zParam->buildVariables('    '));

                    if ($field->name === 'colors') {
                        var_dump($field);
                    }
                    $input[] = '    bool ' . $field->name . '_is_null = 1;';
                } else {
                    $input[] = '    zend_object *' . $field->name . ' = NULL;';
                    $input[] = '    php_raylib_' . $field->typePlainLower . '_object *php' . ucfirst($field->name) . ';';
                }
                $input[] = '';
            }

            $input[] = '    ZEND_PARSE_PARAMETERS_START(0, ' . $struct->totalFields . ')';
            $input[] = '        Z_PARAM_OPTIONAL';
            foreach ($struct->fields as $field) {
                if ($field->isPrimitive) {
                    if (Helper::isFloat($field->type)) {
                        if ($field->isArray) {
                            $input[] = '        Z_PARAM_ARRAY_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        } else {
                            $input[] = '        Z_PARAM_DOUBLE_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        }
                    } elseif (Helper::isInt($field->type)) {
                        if ($field->isArray) {
                            $input[] = '        Z_PARAM_ARRAY_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        } else {
                            $input[] = '        Z_PARAM_LONG_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        }
                    } elseif (Helper::isString($field->type)) {
                        if ($field->isArray) {
                            $input[] = '        Z_PARAM_ARRAY_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        } else {
                            $input[] = '        Z_PARAM_STRING_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        }
                    } elseif (Helper::isBool($field->type)) {
                        if ($field->isArray) {
                            $input[] = '        Z_PARAM_ARRAY_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        } else {
                            $input[] = '        Z_PARAM_BOOL_OR_NULL(' . $field->name . ', ' . $field->name . '_is_null)';
                        }
                    }
                    // Z_PARAM_ARRAY_OR_NULL(options)
                } else {
                    $input[] = '        Z_PARAM_OBJ_OF_CLASS_OR_NULL(' . $field->name . ', php_raylib_' . $field->typePlainLower . '_ce)';
                }
            }
            $input[] = '    ZEND_PARSE_PARAMETERS_END();';
            $input[] = '';
            $input[] = '    php_raylib_' . $struct->nameLower . '_object *intern = Z_' . $struct->nameUpper . '_OBJ_P(ZEND_THIS);';
            $input[] = '';


            foreach ($struct->fields as $field) {
                if ($field->isPrimitive) {
                    $input[] = '    if (' . $field->name . '_is_null) {';
                    if (Helper::isFloat($field->type)) {
                        $input[] = '        ' . $field->name . ' = 0.0f;';
                    } elseif (Helper::isInt($field->type)) {
                        $input[] = '        ' . $field->name . ' = 0;';
                    } elseif (Helper::isString($field->type)) {
                        $input[] = '        ' . $field->name . ' = zend_string_safe_alloc(1, 3, 0, 0);';
                    } elseif (Helper::isBool($field->type)) {
                        $input[] = '        ' . $field->name . ' = false;';
                    }
                    $input[] = '    }';
                } else {
                    $input[] = '    if (' . $field->name . ' == NULL) {';
                    $input[] = '        ' . $field->name . ' = php_raylib_' . $field->typePlainLower . '_new_ex(php_raylib_' . $field->typePlainLower . '_ce, NULL);';
                    $input[] = '    }';
                }
                $input[] = '';
            }

            foreach ($struct->nonPrimitiveFields() as $field) {
                $input[] = '    php' . ucfirst($field->name) . ' = php_raylib_' . $field->typePlainLower . '_fetch_object(' . $field->name . ');';
            }
            $input[] = '';

            foreach ($struct->nonPrimitiveFields() as $field) {
                $input[] = '    ZVAL_OBJ_COPY(&intern->' . $field->name . ', &php' . ucfirst($field->name) . '->std);';
            }
            $input[] = '';

            $input[] = '    intern->' . $struct->nameLower . ' = (' . $struct->name . ') {';

            foreach ($struct->fields as $i => $field) {
                $delimiter = $i + 1 >= $struct->totalFields ? '' : ',';

                if (!$field->isPrimitive) {
                    if ($field->isArray || $field->isPointer) {
                        $input[] = '        // .' . $field->name . ' is an array and not yet supported via constructor';
                    } else {
                        $input[] = '        .' . $field->name . ' = (' . $field->type . ') {';

                        $subStruct = $structsByType[$field->typePlain];

                        foreach ($subStruct->fields as $n => $subField) {
                            $delimiter2 = $n + 1 >= $subStruct->totalFields ? '' : ',';
                            $input[] = '            .' . $subField->name . ' = php' . ucfirst($field->name) . '->' . $field->typePlainLower . '.' . $subField->name . $delimiter2;
                        }
                        $input[] = '        }' . $delimiter;
                    }
                } else {
                    $input[] = '        .' . $field->name . ' = ' . $field->name . $delimiter;
                }
            }
            $input[] = '    };';
        }


        $input[] = '}';
        $input[] = '';

        return $input;
    }

    public function generateColor(array $color, mixed $input)
    {
        $cStr = file_get_contents(__DIR__ . '/../../manual/color.c');
        $input[] = strtr($cStr, [
            '[colorName]' => $color[0],
            '[r]' => $color[1],
            '[g]' => $color[2],
            '[b]' => $color[3],
            '[a]' => $color[4],
        ]);

        return $input;
    }
}
