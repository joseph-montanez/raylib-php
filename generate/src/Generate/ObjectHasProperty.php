<?php

namespace Raylib\Parser\Generate;

use Raylib\Parser\Struct;

/**
 * Generates PHP Object Property Check - i.e property_exists()
 */
class ObjectHasProperty
{
    public function generate(Struct $struct, array $input): array
    {
        $input[] = 'static int php_raylib_' . $struct->nameLower . '_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */';
        $input[] = '{';
        $input[] = '    php_raylib_' . $struct->nameLower . '_object *obj;';
        $input[] = '    raylib_' . $struct->nameLower . '_prop_handler *hnd = NULL;';
        $input[] = '    int ret = 0;';
        $input[] = '';
        $input[] = '    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {';
        $input[] = '        switch (has_set_exists) {';
        $input[] = '            case ZEND_PROPERTY_EXISTS:';
        $input[] = '                ret = 1;';
        $input[] = '                break;';
        $input[] = '            case ZEND_PROPERTY_NOT_EMPTY: {';
        $input[] = '                zval rv;';
        $input[] = '                zval *value = php_raylib_' . $struct->nameLower . '_read_property(object, name, BP_VAR_IS, cache_slot, &rv);';
        $input[] = '                if (value != &EG(uninitialized_zval)) {';
        $input[] = '                    convert_to_boolean(value);';
        $input[] = '                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;';
        $input[] = '                }';
        $input[] = '                break;';
        $input[] = '            }';
        $input[] = '            case ZEND_PROPERTY_ISSET: {';
        $input[] = '                zval rv;';
        $input[] = '                zval *value = php_raylib_' . $struct->nameLower . '_read_property(object, name, BP_VAR_IS, cache_slot, &rv);';
        $input[] = '                if (value != &EG(uninitialized_zval)) {';
        $input[] = '                    ret = Z_TYPE_P(value) != IS_NULL? 1 : 0;';
        $input[] = '                    zval_ptr_dtor(value);';
        $input[] = '                }';
        $input[] = '                break;';
        $input[] = '            }';
        $input[] = '                EMPTY_SWITCH_DEFAULT_CASE();';
        $input[] = '        }';
        $input[] = '    } else {';
        $input[] = '        ret = zend_std_has_property(object, name, has_set_exists, cache_slot);';
        $input[] = '    }';
        $input[] = '';
        $input[] = '    return ret;';
        $input[] = '}';
        $input[] = '/* }}} */';
        $input[] = '';

        return $input;
    }
}