//
// Created by Joseph Montanez on 4/7/18.
//
#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowDraw ShowDrawWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-draw.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Draw PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_draw_object_handlers;

void php_raylib_draw_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_draw_object *intern = php_raylib_draw_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_draw_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_draw_object *intern;
    intern = (php_raylib_draw_object*) ecalloc(1, sizeof(php_raylib_draw_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_draw_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Draw, __construct)
{
    php_raylib_draw_object *intern = Z_DRAW_OBJ_P(getThis());
}

//void ClearBackground(Color color);
PHP_METHOD(Draw, clearBackground)
{
    zval *ar;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(ar)
    ZEND_PARSE_PARAMETERS_END();

    ClearBackground(php_array_to_color(ar));
}

//void BeginDrawing(void);
PHP_METHOD(Draw, begin)
{
    BeginDrawing();
}

//void EndDrawing(void);
PHP_METHOD(Draw, end)
{
    EndDrawing();
}

//void Begin2dMode(Camera2D camera);
PHP_METHOD(Draw, begin2dMode)
{
    // TODO
}

//void End2dMode(void);
PHP_METHOD(Draw, end2dMode)
{
    End2dMode();
}

//void Begin3dMode(Camera camera);
PHP_METHOD(Draw, begin3dMode)
{
    // TODO
}

//void end3dMode(void);
PHP_METHOD(Draw, end3dMode)
{
    End3dMode();
}

//void BeginTextureMode(RenderTexture2D target);
PHP_METHOD(Draw, beginTextureMode)
{
    // TODO
}

//void end3dMode(void);
PHP_METHOD(Draw, endTextureMode)
{
    EndTextureMode();
}

//void DrawCircleV(Vector2 center, float radius, Color color);
PHP_METHOD(Draw, circleV)
{
    zval *center;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_ZVAL(center)
            Z_PARAM_DOUBLE(radius)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawCircleV(php_array_to_vector2(center), (float) radius, php_array_to_color(color));
}


const zend_function_entry php_raylib_draw_methods[] = {
        PHP_ME(Draw, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Draw, clearBackground, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, begin, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, end, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, begin2dMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, end2dMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, begin3dMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, end3dMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, beginTextureMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endTextureMode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_draw_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Draw", php_raylib_draw_methods);
    php_raylib_draw_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_draw_ce->create_object = php_raylib_draw_new;

    memcpy(&php_raylib_draw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_draw_object_handlers.offset = XtOffsetOf(php_raylib_draw_object, std);
    php_raylib_draw_object_handlers.free_obj = &php_raylib_draw_free_storage;
    php_raylib_draw_object_handlers.clone_obj = NULL;
}


#undef Rectangle
#undef CloseWindow
#undef ShowDraw
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA