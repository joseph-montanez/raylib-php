//
// Created by Joseph Montanez on 2018-12-02.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-rectangle.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Rectangle PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_rectangle_object_handlers;

void php_raylib_rectangle_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_rectangle_object *intern = php_raylib_rectangle_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_rectangle_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_rectangle_object *intern;
    intern = (php_raylib_rectangle_object*) ecalloc(1, sizeof(php_raylib_rectangle_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_rectangle_object_handlers;

    zend_declare_property_double(ce, "x", strlen("x"), 0.1f, ZEND_ACC_PUBLIC);

    return &intern->std;
}

/* }}} */

// PHP object handling

PHP_METHOD(Rectangle, __construct)
{
    zval *x;
    zval *y;
    zval *width;
    zval *height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(x)
            Z_PARAM_ZVAL(y)
            Z_PARAM_ZVAL(width)
            Z_PARAM_ZVAL(height)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());

    intern->rectangle = (Rectangle) {
            .x = zend_double_2float(x),
            .y = zend_double_2float(y),
            .width = zend_double_2float(width),
            .height = zend_double_2float(height)
    };

}

PHP_METHOD(Rectangle, getX)
{
    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());
    RETURN_DOUBLE(intern->rectangle.x);
}

PHP_METHOD(Rectangle, setX)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());

    intern->rectangle.x = zend_double_2float(val);
}

PHP_METHOD(Rectangle, getY)
{
    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());
    RETURN_DOUBLE(intern->rectangle.y);
}

PHP_METHOD(Rectangle, setY)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());

    intern->rectangle.y = zend_double_2float(val);
}

PHP_METHOD(Rectangle, getWidth)
{
    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());
    RETURN_DOUBLE(intern->rectangle.width);
}

PHP_METHOD(Rectangle, setWidth)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());

    intern->rectangle.width = zend_double_2float(val);
}

PHP_METHOD(Rectangle, getHeight)
{
    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());
    RETURN_DOUBLE(intern->rectangle.height);
}

PHP_METHOD(Rectangle, setHeight)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *intern = Z_RECTANGLE_OBJ_P(getThis());

    intern->rectangle.height = zend_double_2float(val);
}

const zend_function_entry php_raylib_rectangle_methods[] = {
        PHP_ME(Rectangle, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, getX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, setX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, getY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, getWidth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, setWidth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, getHeight, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Rectangle, setHeight, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_rectangle_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Rectangle", php_raylib_rectangle_methods);
    php_raylib_rectangle_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_rectangle_ce->create_object = php_raylib_rectangle_new;

    memcpy(&php_raylib_rectangle_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_rectangle_object_handlers.offset = XtOffsetOf(php_raylib_rectangle_object, std);
    php_raylib_rectangle_object_handlers.free_obj = &php_raylib_rectangle_free_storage;
    php_raylib_rectangle_object_handlers.clone_obj = NULL;
}