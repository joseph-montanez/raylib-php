/* If defined, the following flags inhibit definition of the indicated items.*/
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include "php.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-draw.h"
#include "raylib-utils.h"
#include "raylib-camera2d.h"
#include "raylib-camera3d.h"
#include "raylib-color.h"
#include "raylib-vector2.h"
#include "raylib-rectangle.h"


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
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(color);

    ClearBackground(intern->color);
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

//void Begin2dMode(Camera2D camera3d);
PHP_METHOD(Draw, beginMode2d)
{
    zval *camera2d;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_OBJECT(camera2d)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(camera2d);

    BeginMode2D(intern->camera2d);
}

//void End2dMode(void);
PHP_METHOD(Draw, endMode2d)
{
    EndMode2D();
}

//void Begin3dMode(Camera camera3d);
PHP_METHOD(Draw, beginMode3d)
{
    zval *camera3d;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_OBJECT(camera3d)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(camera3d);

    BeginMode3D(intern->camera3d);
}

//void End3dMode(void);
PHP_METHOD(Draw, endMode3d)
{
    EndMode3D();
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


    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPixel(zend_long_2int(posX), zend_long_2int(posY), phpColor->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);

    DrawPixelV(phpPosition->vector2, phpColor->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLine(zend_long_2int(startPosX), zend_long_2int(startPosY), zend_long_2int(endPosX), zend_long_2int(endPosY), phpColor->color);
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

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineV(phpStartPos->vector2, phpEndPos->vector2, phpColor->color);
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

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineEx(phpStartPos->vector2, phpEndPos->vector2, (float) thick, phpColor->color);
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

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineBezier(phpStartPos->vector2, phpEndPos->vector2, (float) thick, phpColor->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircle(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, phpColor->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);

    DrawCircleV(phpCenter->vector2, (float) radius, phpColor->color);
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

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawCircleGradient(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, phpColor1->color, phpColor2->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleLines(zend_long_2int(centerX), zend_long_2int(centerY), (float) radius, phpColor->color);
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangle(zend_long_2int(posX), zend_long_2int(posY), zend_long_2int(width), zend_long_2int(height), phpColor->color);
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

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleV(phpPosition->vector2, phpSize->vector2, phpColor->color);
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

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRec(phpRec->rectangle, phpColor->color);
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

//RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
PHP_METHOD(Draw, rectangleLines)
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

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleLines(zend_long_2int(posX), zend_long_2int(posY),  zend_long_2int(width),  zend_long_2int(height), phpColor->color);
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
        PHP_ME(Draw, beginMode2d, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endMode2d, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, beginMode3d, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endMode3d, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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
        PHP_ME(Draw, rectangleLines, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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