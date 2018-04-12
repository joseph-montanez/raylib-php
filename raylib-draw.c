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

//void DrawPixel(int posX, int posY, Color color);
PHP_METHOD(Draw, pixel)
{
    zend_long posX;
    zend_long posY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawPixel(zend_long_2int(posX), zend_long_2int(posY), php_array_to_color(color));
}

//void DrawPixelV(Vector2 position, Color color);
PHP_METHOD(Draw, pixelV)
{
    zval *position;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(position)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawPixelV(php_array_to_vector2(position), php_array_to_color(color));
}

//void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
PHP_METHOD(Draw, line)
{
    zend_long startPosX;
    zend_long startPosY;
    zend_long endPosX;
    zend_long endPosY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(startPosX)
            Z_PARAM_LONG(startPosY)
            Z_PARAM_LONG(endPosX)
            Z_PARAM_LONG(endPosY)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawLine(zend_long_2int(startPosX), zend_long_2int(startPosY), zend_long_2int(endPosX), zend_long_2int(endPosY), php_array_to_color(color));
}

//void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);
PHP_METHOD(Draw, lineV)
{
    zval *startPos;
    zval *endPos;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_ZVAL(startPos)
            Z_PARAM_ZVAL(endPos)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawLineV(php_array_to_vector2(startPos), php_array_to_vector2(endPos), php_array_to_color(color));
}

//void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
PHP_METHOD(Draw, lineEx)
{
    zval *startPos;
    zval *endPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(startPos)
            Z_PARAM_ZVAL(endPos)
            Z_PARAM_DOUBLE(thick)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawLineEx(php_array_to_vector2(startPos), php_array_to_vector2(endPos), (float) thick, php_array_to_color(color));
}

//void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);
PHP_METHOD(Draw, lineBezier)
{
    zval *startPos;
    zval *endPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(startPos)
            Z_PARAM_ZVAL(endPos)
            Z_PARAM_DOUBLE(thick)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawLineBezier(php_array_to_vector2(startPos), php_array_to_vector2(endPos), (float) thick, php_array_to_color(color));
}

//void DrawCircle(int centerX, int centerY, float radius, Color color);
PHP_METHOD(Draw, circle)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_LONG(centerX)
            Z_PARAM_LONG(centerY)
            Z_PARAM_DOUBLE(radius)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawCircle(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, php_array_to_color(color));
}

//void DrawCircle(Vector2 center, float radius, Color color);
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

//void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);
PHP_METHOD(Draw, circleGradient)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(centerX)
            Z_PARAM_LONG(centerY)
            Z_PARAM_DOUBLE(radius)
            Z_PARAM_ZVAL(color1)
            Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    DrawCircleGradient(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, php_array_to_color(color1),  php_array_to_color(color2));
}

//void DrawCircleLines(int centerX, int centerY, float radius, Color color);
PHP_METHOD(Draw, circleLines)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_LONG(centerX)
            Z_PARAM_LONG(centerY)
            Z_PARAM_DOUBLE(radius)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawCircleLines(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, php_array_to_color(color));
}

//void DrawRectangle(int posX, int posY, int width, int height, Color color);
PHP_METHOD(Draw, rectangle)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawRectangle(zend_long_2int(posX), zend_long_2int(posY), zend_long_2int(width), zend_long_2int(height), php_array_to_color(color));
}

//void DrawRectangleV(Vector2 position, Vector2 size, Color color);
PHP_METHOD(Draw, rectangleV)
{
    zval *position;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_ZVAL(position)
            Z_PARAM_ZVAL(size)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawRectangleV(php_array_to_vector2(position), php_array_to_vector2(size), php_array_to_color(color));
}

//void DrawRectangleRec(Rectangle rec, Color color);
PHP_METHOD(Draw, rectangleRec)
{
    zval *rec;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(rec)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawRectangleRec(php_array_to_rec(rec), php_array_to_color(color));
}

//void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);
PHP_METHOD(Draw, rectanglePro)
{
    zval *rec;
    zval *origin;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(rec)
            Z_PARAM_ZVAL(origin)
            Z_PARAM_DOUBLE(radius)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    DrawRectanglePro(php_array_to_rec(rec), php_array_to_vector2(origin), (float) radius, php_array_to_color(color));
}

//void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);
PHP_METHOD(Draw, rectangleGradientV)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
            Z_PARAM_ZVAL(color1)
            Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    DrawRectangleGradientV(zend_long_2int(posX), zend_long_2int(posY),  zend_long_2int(width),  zend_long_2int(height), php_array_to_color(color1), php_array_to_color(color2));
}

/*
 *
RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a vertical-gradient-filled rectangle
RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a horizontal-gradient-filled rectangle
RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);       // Draw a gradient-filled rectangle with custom vertex colors
RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
RLAPI void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);                              // Draw rectangle outline with extended parameters
RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle
RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline
RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a regular polygon (Vector version)
RLAPI void DrawPolyEx(Vector2 *points, int numPoints, Color color);                                      // Draw a closed polygon defined by points
RLAPI void DrawPolyExLines(Vector2 *points, int numPoints, Color color);                                 // Draw polygon lines
 */


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

        // Basic shapes drawing functions
        PHP_ME(Draw, pixel, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, pixelV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, line, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineEx, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineBezier, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circle, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleGradient, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleLines, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangle, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleRec, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectanglePro, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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