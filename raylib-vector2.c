//
// Created by Joseph Montanez on 2018-12-02.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-vector2.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Vector2 PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vector2_object_handlers;

void php_raylib_vector2_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_vector2_object *intern = php_raylib_vector2_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_vector2_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_vector2_object *intern;
    intern = (php_raylib_vector2_object*) ecalloc(1, sizeof(php_raylib_vector2_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_vector2_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Vector2, __construct)
{
    zval *x;
    zval *y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(x)
            Z_PARAM_ZVAL(y)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(getThis());

    intern->vector2 = (Vector2) {
            .x = zend_double_2float(x),
            .y = zend_double_2float(y)
    };

}

PHP_METHOD(Vector2, getX)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector2.x);
}

PHP_METHOD(Vector2, setX)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(getThis());

    intern->vector2.x = zend_double_2float(val);
}

PHP_METHOD(Vector2, getY)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector2.y);
}

PHP_METHOD(Vector2, setY)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(getThis());

    intern->vector2.y = zend_double_2float(val);
}

const zend_function_entry php_raylib_vector2_methods[] = {
        PHP_ME(Vector2, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_vector2_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Vector2", php_raylib_vector2_methods);
    php_raylib_vector2_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_vector2_ce->create_object = php_raylib_vector2_new;

    memcpy(&php_raylib_vector2_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vector2_object_handlers.offset = XtOffsetOf(php_raylib_vector2_object, std);
    php_raylib_vector2_object_handlers.free_obj = &php_raylib_vector2_free_storage;
    php_raylib_vector2_object_handlers.clone_obj = NULL;
}