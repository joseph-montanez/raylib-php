//
// Created by Joseph Montanez on 2018-12-01.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-vector4.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Vector4 PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vector4_object_handlers;

void php_raylib_vector4_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_vector4_object *intern = php_raylib_vector4_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_vector4_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_vector4_object *intern;
    intern = (php_raylib_vector4_object*) ecalloc(1, sizeof(php_raylib_vector4_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_vector4_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Vector4, __construct)
{
    zval *x;
    zval *y;
    zval *z;
    zval *w;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(x)
            Z_PARAM_ZVAL(y)
            Z_PARAM_ZVAL(z)
            Z_PARAM_ZVAL(w)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());

    intern->vector4 = (Vector4) {
            .x = zend_double_2float(x),
            .y = zend_double_2float(y),
            .z = zend_double_2float(z),
            .w = zend_double_2float(w)
    };

}

PHP_METHOD(Vector4, getX)
{
    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector4.x);
}

PHP_METHOD(Vector4, setX)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());

    intern->vector4.x = zend_double_2float(val);
}

PHP_METHOD(Vector4, getY)
{
    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector4.y);
}

PHP_METHOD(Vector4, setY)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());

    intern->vector4.y = zend_double_2float(val);
}


PHP_METHOD(Vector4, getZ)
{
    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector4.z);
}

PHP_METHOD(Vector4, setZ)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());

    intern->vector4.z = zend_double_2float(val);
}


PHP_METHOD(Vector4, getW)
{
    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector4.w);
}

PHP_METHOD(Vector4, setW)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *intern = Z_VECTOR4_OBJ_P(getThis());

    intern->vector4.w = zend_double_2float(val);
}

const zend_function_entry php_raylib_vector4_methods[] = {
        PHP_ME(Vector4, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, getX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, setX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, getY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, getZ, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, setZ, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, getW, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector4, setW, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_vector4_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Vector4", php_raylib_vector4_methods);
    php_raylib_vector4_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_vector4_ce->create_object = php_raylib_vector4_new;

    memcpy(&php_raylib_vector4_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vector4_object_handlers.offset = XtOffsetOf(php_raylib_vector4_object, std);
    php_raylib_vector4_object_handlers.free_obj = &php_raylib_vector4_free_storage;
    php_raylib_vector4_object_handlers.clone_obj = NULL;
}
