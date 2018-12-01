#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-camera2d.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Camera2d PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_camera2d_object_handlers;

void php_raylib_camera2d_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_camera2d_object *intern = php_raylib_camera2d_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_camera2d_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_camera2d_object *intern;
    intern = (php_raylib_camera2d_object*) ecalloc(1, sizeof(php_raylib_camera2d_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_camera2d_object_handlers;

    return &intern->std;
}

PHP_METHOD(Camera2d, __construct)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    intern->camera2d = (Camera2D) {
            .offset = (Vector2) {.x = 0, .y = 0},
            .target = (Vector2) {.x = 0, .y = 0},
            .rotation = 0.0f,
            .zoom = 1.0f
    };
}

PHP_METHOD(Camera2d, getOffset)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    array_init(return_value);
    add_assoc_double(return_value, "x", (double) intern->camera2d.offset.x);
    add_assoc_double(return_value, "y", (double) intern->camera2d.offset.y);
}

PHP_METHOD(Camera2d, setOffset)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    zval *offset;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(offset)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera2d.offset = php_array_to_vector2(offset);
}

PHP_METHOD(Camera2d, getTarget)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    array_init(return_value);
    add_assoc_double(return_value, "x", (double) intern->camera2d.target.x);
    add_assoc_double(return_value, "y", (double) intern->camera2d.target.y);
}

PHP_METHOD(Camera2d, setTarget)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    zval *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera2d.target = php_array_to_vector2(target);
}

PHP_METHOD(Camera2d, getRotation)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    RETURN_DOUBLE((double) intern->camera2d.rotation)
}

PHP_METHOD(Camera2d, setRotation)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    double rotation;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_DOUBLE(rotation)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera2d.rotation = (float) rotation;
}

PHP_METHOD(Camera2d, getZoom)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    RETURN_DOUBLE((double) intern->camera2d.zoom)
}

PHP_METHOD(Camera2d, setZoom)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    double zoom;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_DOUBLE(zoom)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera2d.rotation = (float) zoom;
}

const zend_function_entry php_raylib_camera2d_methods[] = {
        PHP_ME(Camera2d, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, getOffset, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, setOffset, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, getTarget, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, setTarget, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, getRotation, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, setRotation, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, getZoom, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera2d, setZoom, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void php_raylib_camera2d_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Camera2d", php_raylib_camera2d_methods);
    php_raylib_camera2d_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_camera2d_ce->create_object = php_raylib_camera2d_new;

    memcpy(&php_raylib_camera2d_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_camera2d_object_handlers.offset = XtOffsetOf(php_raylib_camera2d_object, std);
    php_raylib_camera2d_object_handlers.free_obj = &php_raylib_camera2d_free_storage;
    php_raylib_camera2d_object_handlers.clone_obj = NULL;
}

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA