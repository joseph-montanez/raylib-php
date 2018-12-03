//
// Created by Joseph Montanez on 2018-12-02.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-vector3.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Vector3 PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vector3_object_handlers;

void php_raylib_vector3_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_vector3_object *intern = php_raylib_vector3_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_vector3_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_vector3_object *intern;
    intern = (php_raylib_vector3_object*) ecalloc(1, sizeof(php_raylib_vector3_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_vector3_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Vector3, __construct)
{
    zval *x;
    zval *y;
    zval *z;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_ZVAL(x)
            Z_PARAM_ZVAL(y)
            Z_PARAM_ZVAL(z)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());

    intern->vector3 = (Vector3) {
            .x = zend_double_2float(x),
            .y = zend_double_2float(y),
            .z = zend_double_2float(z)
    };

}

PHP_METHOD(Vector3, getX)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector3.x);
}

PHP_METHOD(Vector3, setX)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());

    intern->vector3.x = zend_double_2float(val);
}

PHP_METHOD(Vector3, getY)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector3.y);
}

PHP_METHOD(Vector3, setY)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());

    intern->vector3.y = zend_double_2float(val);
}


PHP_METHOD(Vector3, getZ)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());
    RETURN_DOUBLE(intern->vector3.z);
}

PHP_METHOD(Vector3, setZ)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(getThis());

    intern->vector3.z = zend_double_2float(val);
}

const zend_function_entry php_raylib_vector3_methods[] = {
        PHP_ME(Vector3, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getZ, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setZ, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_vector3_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Vector3", php_raylib_vector3_methods);
    php_raylib_vector3_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_vector3_ce->create_object = php_raylib_vector3_new;

    memcpy(&php_raylib_vector3_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vector3_object_handlers.offset = XtOffsetOf(php_raylib_vector3_object, std);
    php_raylib_vector3_object_handlers.free_obj = &php_raylib_vector3_free_storage;
    php_raylib_vector3_object_handlers.clone_obj = NULL;
}
