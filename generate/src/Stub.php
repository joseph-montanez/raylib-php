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

            if ($struct->name === 'Color') {
                $colors = [
                    ['LIGHTGRAY', 200, 200, 200, 255],   // Light Gray
                    ['GRAY', 130, 130, 130, 255],   // Gray
                    ['DARKGRAY', 80, 80, 80, 255],      // Dark Gray
                    ['YELLOW', 253, 249, 0, 255],     // Yellow
                    ['GOLD', 255, 203, 0, 255],     // Gold
                    ['ORANGE', 255, 161, 0, 255],     // Orange
                    ['PINK', 255, 109, 194, 255],   // Pink
                    ['RED', 230, 41, 55, 255],     // Red
                    ['MAROON', 190, 33, 55, 255],     // Maroon
                    ['GREEN', 0, 228, 48, 255],      // Green
                    ['LIME', 0, 158, 47, 255],      // Lime
                    ['DARKGREEN', 0, 117, 44, 255],      // Dark Green
                    ['SKYBLUE', 102, 191, 255, 255],   // Sky Blue
                    ['BLUE', 0, 121, 241, 255],     // Blue
                    ['DARKBLUE', 0, 82, 172, 255],      // Dark Blue
                    ['PURPLE', 200, 122, 255, 255],   // Purple
                    ['VIOLET', 135, 60, 190, 255],    // Violet
                    ['DARKPURPLE', 112, 31, 126, 255],    // Dark Purple
                    ['BEIGE', 211, 176, 131, 255],   // Beige
                    ['BROWN', 127, 106, 79, 255],    // Brown
                    ['DARKBROWN', 76, 63, 47, 255],      // Dark Brown
                    ['WHITE', 255, 255, 255, 255],   // White
                    ['BLACK', 0, 0, 0, 255],         // Black
                    ['BLANK', 0, 0, 0, 0],           // Blank (Transparent)
                    ['MAGENTA', 255, 0, 255, 255],     // Magenta
                    ['RAYWHITE', 245, 245, 245, 255],   // My own White (raylib logo)
                ];

                foreach ($colors as $color) {
                    $input[] = '        public static function ' . $color[0] . '(): Color { return new Color(); }';
                }
            }


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
                elseif ($param->type && $param->isRef) {
                    if (Helper::isString($param->type)) {
                        $paramType = 'string';
                    }
                    elseif (Helper::isArray($param->type)) {
                        $paramType = 'array';
                    }
                    elseif (Helper::isBool($param->type)) {
                        $paramType = 'bool';
                    }
                    elseif (Helper::isInt($param->type)) {
                        $paramType = 'int';
                    }
                    elseif (Helper::isFloat($param->type)) {
                        $paramType = 'float';
                    }
                    elseif (!Helper::isPrimitive($param->type)) {
                        $paramType = '\\raylib\\' . trim(str_replace('*', '', $param->type));
                    }
                    $paramType .= ' &';
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

                $params[] = str_replace('& $', '&$', $paramType . ' $' . $param->name);
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
                if ($function->returnIsArray) {
                    $returnType = 'array'; // appending [] is not yet supported in PHP :(
                    $returnValue = 'return [];';
                }
            }

            $input[] = '/*';
            $input[] = ' * ' . $function->description;
            $input[] = ' *';
            foreach ($params as $param) {
                $input[] = ' * @param ' . $param;
            }

            if ($function->returnType && !Helper::isPrimitive($function->returnType) && $function->returnIsArray) {
                $input[] = ' * @return \\raylib\\' . trim(str_replace('*', '', $function->returnType)) . '[]';
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
