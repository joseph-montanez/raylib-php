<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Free Storage - when its unset
 */
class ObjectStartup
{
    public function generate(Struct $struct, array $input): array
    {

        $input[] = 'void php_raylib_' . $struct->nameLower . '_startup(INIT_FUNC_ARGS)';
        $input[] = '{';
        $input[] = '    zend_class_entry ce;';
        $input[] = '';
        $input[] = '    memcpy(&php_raylib_' . $struct->nameLower . '_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.offset = XtOffsetOf(php_raylib_' . $struct->nameLower . '_object, std);';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.free_obj = &php_raylib_' . $struct->nameLower . '_free_storage;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.clone_obj = php_raylib_' . $struct->nameLower . '_clone;';
        $input[] = '';
        $input[] = '    // Props';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.get_property_ptr_ptr = php_raylib_' . $struct->nameLower . '_get_property_ptr_ptr;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.get_gc               = php_raylib_' . $struct->nameLower . '_get_gc;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.get_properties       = php_raylib_' . $struct->nameLower . '_get_properties;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.read_property	     = php_raylib_' . $struct->nameLower . '_read_property;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.write_property       = php_raylib_' . $struct->nameLower . '_write_property;';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object_handlers.has_property	     = php_raylib_' . $struct->nameLower . '_has_property;';
        $input[] = '';
        $input[] = '    // Init';
        $input[] = '    INIT_NS_CLASS_ENTRY(ce, "raylib", "' . $struct->name . '", php_raylib_' . $struct->nameLower . '_methods);';
        $input[] = '    php_raylib_' . $struct->nameLower . '_ce = zend_register_internal_class(&ce);';
        $input[] = '    php_raylib_' . $struct->nameLower . '_ce->create_object = php_raylib_' . $struct->nameLower . '_new;';
        $input[] = '';
        $input[] = '    // Props';
        $input[] = '    zend_hash_init(&php_raylib_' . $struct->nameLower . '_prop_handlers, 0, NULL, php_raylib_' . $struct->nameLower . '_free_prop_handler, 1);';

        foreach ($struct->fields as $field) {
            $params = [];
            foreach ($struct->fieldsByType() as $fieldType) {
                if ($field->typeName === $fieldType->typeName) {
                    $params[] = 'php_raylib_' . $struct->nameLower . '_get_' . $field->nameLower;
                    $params[] = 'php_raylib_' . $struct->nameLower . '_set_' . $field->nameLower;
                } else {
                    $params[] = 'NULL';
                    $params[] = 'NULL';
                }
            }

            $input[] = '    php_raylib_' . $struct->nameLower . '_register_prop_handler(&php_raylib_' . $struct->nameLower . '_prop_handlers, "' . $field->nameLower . '", ' . implode(', ', $params) . ');';
        }
        $input[] = '}';
        $input[] = '';

        return $input;
    }
}