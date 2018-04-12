//
// Created by Joseph Montanez on 4/8/18.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowText ShowTextWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-utils.h"
#include "raylib-collision.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Collision PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_collision_object_handlers;

void php_raylib_collision_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_collision_object *intern = php_raylib_collision_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_collision_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_collision_object *intern;
    intern = (php_raylib_collision_object*) ecalloc(1, sizeof(php_raylib_collision_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_collision_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Collision, __construct)
{
    php_raylib_collision_object *intern = Z_COLLISION_OBJ_P(getThis());
}

//bool CheckCollisionPointRec(Vector2 point, Rectangle rec)
PHP_METHOD(Collision, checkPointRec)
{
    zval *point;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ARRAY(point)
            Z_PARAM_ARRAY(rec)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(CheckCollisionPointRec(php_array_to_vector2(point), php_array_to_rec(rec)));
}


const zend_function_entry php_raylib_collision_methods[] = {
        PHP_ME(Collision, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Collision, checkPointRec, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_collision_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Collision", php_raylib_collision_methods);
    php_raylib_collision_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_collision_ce->create_object = php_raylib_collision_new;

    memcpy(&php_raylib_collision_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_collision_object_handlers.offset = XtOffsetOf(php_raylib_collision_object, std);
    php_raylib_collision_object_handlers.free_obj = &php_raylib_collision_free_storage;
    php_raylib_collision_object_handlers.clone_obj = NULL;
}

#undef Rectangle
#undef CloseWindow
#undef ShowText
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA

