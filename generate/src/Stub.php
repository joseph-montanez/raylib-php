<?php

namespace Raylib\Parser;

class Stub
{
    /*
     *
     */
    public function generate(array $functions, array $structs, array $enums)
    {
        $input = ['<?php', ''];

        /** @var \Raylib\Parser\Struct $struct */
        foreach ($structs as $struct) {
            if ($struct->isAlias) { continue; }
            $input[] = 'namespace raylib {';
            $input[] = '    class ' . $struct->name . ' {';

            /** @var \Raylib\Parser\Field $field */
            foreach ($struct->fields as $field) {
                if ($field->type === 'rAudioBuffer *') {
                    continue;
                }
                $fieldType = '';
                if ($field->type && Helper::isString($field->type)) {
                    $fieldType = 'string';
                }
                elseif ($field->type && Helper::isArray($field->type)) {
                    $fieldType = 'array';
                }
                elseif ($field->type && Helper::isBool($field->type)) {
                    $fieldType = 'bool';
                }
                elseif ($field->type && Helper::isInt($field->type)) {
                    $fieldType = 'int';
                }
                elseif ($field->type && Helper::isFloat($field->type)) {
                    $fieldType = 'float';
                }
                elseif ($field->type && !Helper::isPrimitive($field->type)) {
                    $fieldType = '\\raylib\\' . trim(str_replace('*', '', $field->type));
                }

                $input[] = '        public ' . $fieldType . ' $' . $field->name . ';';
            }

            $input[] = '        public function __construct() { }';
            $input[] = '    }';
            $input[] = '}';
            $input[] = '';
        }

        /** @var \Raylib\Parser\Enum $enum */
        foreach ($enums as $enum) {
            $input[] = 'namespace raylib\\' . $enum->name . ' {';

            /** @var \Raylib\Parser\EnumValue $value */
            foreach ($enum->values as $value) {
                $input[] = '    const ' . $value->name . ' = ' . $value->value . ';';
            }

            $input[] = '}';
            $input[] = '';
        }


        $input[] = 'namespace {';
        /** @var \Raylib\Parser\Func $function */
        foreach ($functions as $function) {
            if ($function->unsupported) {
                continue;
            }
            $params = [];
            /** @var \Raylib\Parser\Param $param */
            foreach ($function->params as $param) {
                $paramType = '';
                if ($param->type && Helper::isString($param->type)) {
                    $paramType = 'string';
                }
                elseif ($param->type && Helper::isArray($param->type)) {
                    $paramType = 'array';
                }
                elseif ($param->type && Helper::isBool($param->type)) {
                    $paramType = 'bool';
                }
                elseif ($param->type && Helper::isInt($param->type)) {
                    $paramType = 'int';
                }
                elseif ($param->type && Helper::isFloat($param->type)) {
                    $paramType = 'float';
                }
                elseif ($param->type && !Helper::isPrimitive($param->type)) {
                    $paramType = '\\raylib\\' . trim(str_replace('*', '', $param->type));
                }

                $params[] = $paramType . ' $' . $param->name;
            }

            $returnType = 'void';

            $returnValue = '';
            if ($function->returnType && Helper::isString($function->returnType)) {
                $returnType = 'string';
                $returnValue = 'return "";';
            }
            elseif ($function->returnType && Helper::isArray($function->returnType)) {
                $returnType = 'array';
                $returnValue = 'return [];';
            }
            elseif ($function->returnType && Helper::isBool($function->returnType)) {
                $returnType = 'bool';
                $returnValue = 'return false;';
            }
            elseif ($function->returnType && Helper::isInt($function->returnType)) {
                $returnType = 'int';
                $returnValue = 'return 0;';
            }
            elseif ($function->returnType && Helper::isFloat($function->returnType)) {
                $returnType = 'float';
                $returnValue = 'return 0.00;';
            }
            elseif ($function->returnType && !Helper::isPrimitive($function->returnType)) {
                $returnType = '\\raylib\\' . trim(str_replace('*', '', $function->returnType));
                $returnValue = 'return new '  . $returnType . ';';
            }

            $input[] = '/*';
            $input[] = ' * ' . $function->description;
            $input[] = ' *';
            foreach ($params as $param) {
                $input[] = ' * @param ' . $param;
            }
            $input[] = ' *';
            $input[] = ' */';
            $input[] = 'function ' . $function->name . '(' . implode(', ', $params) . '): ' . $returnType . ' { ' . $returnValue . ' }';
            $input[] = '';
        }
        $input[] = '}';
        $input[] = '';
        file_put_contents(__DIR__ . '/../stubs/raylib.php', implode(PHP_EOL, $input));
    }

}