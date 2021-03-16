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
#include "zend.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-draw.h"
#include "raylib-utils.h"
#include "raylib-vector2.h"
#include "raylib-camera2d.h"
#include "raylib-camera3d.h"
#include "raylib-color.h"
#include "raylib-rectangle.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Draw PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_draw_object_handlers;

void php_raylib_draw_free_storage(zend_object *object)
{
    php_raylib_draw_object *intern = php_raylib_draw_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_draw_new(zend_class_entry *ce)
{
    php_raylib_draw_object *intern;
    intern = (php_raylib_draw_object*) ecalloc(1, sizeof(php_raylib_draw_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_draw_object_handlers;

    return &intern->std;
}

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw__construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, __construct)
{
    php_raylib_draw_object *intern = Z_DRAW_OBJ_P(ZEND_THIS);
}

//void ClearBackground(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_clearBackground, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_begin, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, begin)
{
    BeginDrawing();
}

//void EndDrawing(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_end, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, end)
{
    EndDrawing();
}

//void Begin2dMode(Camera2D camera3d);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_beginMode2d, 0, 0, 1)
    ZEND_ARG_INFO(0, camera2d)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, beginMode2d)
{
    zval *camera2d;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_OBJECT(camera2d)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(camera2d);
    php_raylib_camera2d_update_intern(intern);

    BeginMode2D(intern->camera2d);
}

//void End2dMode(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_endMode2d, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, endMode2d)
{
    EndMode2D();
}

//void Begin3dMode(Camera camera3d);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_beginMode3d, 0, 0, 1)
    ZEND_ARG_INFO(0, camera3d)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_endMode3d, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, endMode3d)
{
    EndMode3D();
}

//void RLAPI void BeginScissorMode(int x, int y, int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_beginScissorMode, 0, 0, 4)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, beginScissorMode)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    BeginScissorMode((int) x, (int) y, (int) width, (int) height);
}

//RLAPI void EndScissorMode(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_endScissorMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, endScissorMode)
{
    EndScissorMode();
}

//void DrawPixel(int posX, int posY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_pixel, 0, 0, 3)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawPixel((int) posX, (int) posY, phpColor->color);
}

//void DrawPixelV(Vector2 position, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_pixelV, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_line, 0, 0, 5)
    ZEND_ARG_INFO(0, startPosX)
    ZEND_ARG_INFO(0, startPosY)
    ZEND_ARG_INFO(0, endPosX)
    ZEND_ARG_INFO(0, endPosX)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawLine((int) startPosX, (int) startPosY, (int) endPosX, (int) endPosY, phpColor->color);
}

//void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_lineV, 0, 0, 3)
    ZEND_ARG_INFO(0, startPosX)
    ZEND_ARG_INFO(0, startPosY)
    ZEND_ARG_INFO(0, endPosX)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_lineEx, 0, 0, 4)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_lineBezier, 0, 0, 4)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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


// Draw lines sequence
// RLAPI void DrawLineStrip(Vector2 *points, int numPoints, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_lineStrip, 0, 0, 2)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, lineStrip)
{
    zval *points;
    zval *color;
    HashTable *pointsArr;
    zval *zv;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(points)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    pointsArr = Z_ARRVAL_P(points);


    int numPoints = zend_hash_num_elements(pointsArr);
    Vector2 *pointsP = (Vector2 *)safe_emalloc(numPoints, sizeof(Vector2), 0);

    int n = 0;
    ZEND_HASH_FOREACH_VAL(pointsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_vector2_object *obj = Z_VECTOR2_OBJ_P(zv);
            pointsP[n] = obj->vector2;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineStrip(pointsP, numPoints, phpColor->color);
}

//void DrawCircle(int centerX, int centerY, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circle, 0, 0, 4)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawCircle((int) centerX, (int) centerY, (float) radius, phpColor->color);
}

// Draw a piece of a circle
// RLAPI void DrawCircleSector(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circleSector, 0, 0, 6)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, circleSector)
{
    zval *center;
    double radius;
    zend_long startAngle;
    zend_long endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(startAngle)
        Z_PARAM_LONG(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleSector(phpCenter->vector2, (float) radius, (int) startAngle, (int) endAngle, (int) segments, phpColor->color);
}


// Draw circle sector outline
// RLAPI void DrawCircleSectorLines(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circleSectorLines, 0, 0, 6)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, circleSectorLines)
{
    zval *center;
    double radius;
    zend_long startAngle;
    zend_long endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(startAngle)
        Z_PARAM_LONG(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleSectorLines(phpCenter->vector2, (float) radius, (int) startAngle, (int) endAngle, (int) segments, phpColor->color);
}

//void DrawCircle(Vector2 center, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circleV, 0, 0, 3)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circleGradient, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawCircleGradient((int) centerX, (int) centerY, (float) radius, phpColor1->color, phpColor2->color);
}

//void DrawCircleLines(int centerX, int centerY, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_circleLines, 0, 0, 4)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawCircleLines((int) centerX, (int) centerY, (float) radius, phpColor->color);
}

// Draw ellipse
// RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_ellipse, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radiusH)
    ZEND_ARG_INFO(0, radiusV)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, ellipse)
{
    zend_long centerX;
    zend_long centerY;
    double radiusH;
    double radiusV;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(centerX)
            Z_PARAM_LONG(centerY)
            Z_PARAM_DOUBLE(radiusH)
            Z_PARAM_DOUBLE(radiusV)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawEllipse((int) centerX, (int) centerY, (float) radiusH, (float) radiusV, phpColor->color);
}

// Draw ellipse outline
// RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_ellipseLines, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radiusH)
    ZEND_ARG_INFO(0, radiusV)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, ellipseLines)
{
    zend_long centerX;
    zend_long centerY;
    double radiusH;
    double radiusV;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(centerX)
            Z_PARAM_LONG(centerY)
            Z_PARAM_DOUBLE(radiusH)
            Z_PARAM_DOUBLE(radiusV)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawEllipseLines((int) centerX, (int) centerY, (float) radiusH, (float) radiusV, phpColor->color);
}

// Draw ring
// RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_ring, 0, 0, 7)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, innerRadius)
    ZEND_ARG_INFO(0, outerRadius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, ring)
{
    zval *center;
    double innerRadius;
    double outerRadius;
    zend_long startAngle;
    zend_long endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(7, 7)
            Z_PARAM_ZVAL(center)
            Z_PARAM_DOUBLE(innerRadius)
            Z_PARAM_DOUBLE(outerRadius)
            Z_PARAM_LONG(startAngle)
            Z_PARAM_LONG(endAngle)
            Z_PARAM_LONG(segments)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);

    DrawRing(phpCenter->vector2, (float) innerRadius, (float) outerRadius, (int) startAngle, (int) endAngle, (int) segments, phpColor->color);
}

// Draw ring
// RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_ringLines, 0, 0, 7)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, innerRadius)
    ZEND_ARG_INFO(0, outerRadius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, ringLines)
{
    zval *center;
    double innerRadius;
    double outerRadius;
    zend_long startAngle;
    zend_long endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(7, 7)
            Z_PARAM_ZVAL(center)
            Z_PARAM_DOUBLE(innerRadius)
            Z_PARAM_DOUBLE(outerRadius)
            Z_PARAM_LONG(startAngle)
            Z_PARAM_LONG(endAngle)
            Z_PARAM_LONG(segments)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);

    DrawRingLines(phpCenter->vector2, (float) innerRadius, (float) outerRadius, (int) startAngle, (int) endAngle, (int) segments, phpColor->color);
}


//void DrawRectangle(int posX, int posY, int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangle, 0, 0, 5)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawRectangle((int) posX, (int) posY, (int) width, (int) height, phpColor->color);
}

//void DrawRectangleV(Vector2 position, Vector2 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleV, 0, 0, 3)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleRec, 0, 0, 2)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectanglePro, 0, 0, 4)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectanglePro(phpRec->rectangle, phpOrigin->vector2, (float) radius, phpColor->color);
}

// Draw a vertical-gradient-filled rectangle
// RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleGradientV, 0, 0, 6)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleGradientV)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
            Z_PARAM_ZVAL(color1)
            Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawRectangleGradientV((int) posX, (int) posY,  (int) width,  (int) height, phpColor1->color, phpColor2->color);
}

// Draw a horizontal-gradient-filled rectangle
// RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleGradientH, 0, 0, 6)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleGradientH)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
            Z_PARAM_ZVAL(color1)
            Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawRectangleGradientH((int) posX, (int) posY,  (int) width,  (int) height, phpColor1->color, phpColor2->color);
}

// Draw a gradient-filled rectangle with custom vertex colors
// RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleGradientEx, 0, 0, 5)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
    ZEND_ARG_INFO(0, color3)
    ZEND_ARG_INFO(0, color4)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleGradientEx)
{
    zval *rec;
    zval *color1;
    zval *color2;
    zval *color3;
    zval *color4;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_ZVAL(rec)
            Z_PARAM_ZVAL(color1)
            Z_PARAM_ZVAL(color2)
            Z_PARAM_ZVAL(color3)
            Z_PARAM_ZVAL(color4)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);
    php_raylib_color_object *phpColor3 = Z_COLOR_OBJ_P(color3);
    php_raylib_color_object *phpColor4 = Z_COLOR_OBJ_P(color4);

    DrawRectangleGradientEx(phpRec->rectangle, phpColor1->color, phpColor2->color, phpColor3->color, phpColor4->color);
}

// Draw rectangle outline
//RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleLines, 0, 0, 5)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
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

    DrawRectangleLines((int) posX, (int) posY,  (int) width, (int) height, phpColor->color);
}

// Draw rectangle outline with extended parameters
//RLAPI void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleLinesEx, 0, 0, 3)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, lineThick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleLinesEx)
{
    zval *rec;
    zend_long lineThick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_LONG(lineThick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleLinesEx(phpRec->rectangle, (int) lineThick, phpColor->color);
}

// Draw rectangle with rounded edges
// RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleRounded, 0, 0, 4)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, roundness)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleRounded)
{
    zval *rec;
    double roundness;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_DOUBLE(roundness)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRounded(phpRec->rectangle, (float) roundness, (int) segments, phpColor->color);
}

// Draw rectangle with rounded edges outline
// RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_rectangleRoundedLines, 0, 0, 5)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, roundness)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, lineThick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, rectangleRoundedLines)
{
    zval *rec;
    double roundness;
    zend_long segments;
    zend_long lineThick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_DOUBLE(roundness)
        Z_PARAM_LONG(segments)
        Z_PARAM_LONG(lineThick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRoundedLines(phpRec->rectangle, (float) roundness, (int) segments, (int) lineThick, phpColor->color);
}

// Draw a color-filled triangle
//RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_triangle, 0, 0, 4)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
    ZEND_ARG_INFO(0, v3)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, triangle)
{
    zval *v1;
    zval *v2;
    zval *v3;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(v1)
        Z_PARAM_ZVAL(v2)
        Z_PARAM_ZVAL(v3)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpV1 = Z_VECTOR2_OBJ_P(v1);
    php_raylib_vector2_object *phpV2 = Z_VECTOR2_OBJ_P(v2);
    php_raylib_vector2_object *phpV3 = Z_VECTOR2_OBJ_P(v3);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangle(phpV1->vector2, phpV2->vector2, phpV3->vector2, phpColor->color);
}

// Draw triangle outline (vertex in counter-clockwise order!)
// RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_triangleLines, 0, 0, 4)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
    ZEND_ARG_INFO(0, v3)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, triangleLines)
{
    zval *v1;
    zval *v2;
    zval *v3;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(v1)
        Z_PARAM_ZVAL(v2)
        Z_PARAM_ZVAL(v3)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpV1 = Z_VECTOR2_OBJ_P(v1);
    php_raylib_vector2_object *phpV2 = Z_VECTOR2_OBJ_P(v2);
    php_raylib_vector2_object *phpV3 = Z_VECTOR2_OBJ_P(v3);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleLines(phpV1->vector2, phpV2->vector2, phpV3->vector2, phpColor->color);
}

// Draw a triangle fan defined by points (first vertex is the center)
// RLAPI void DrawTriangleFan(Vector2 *points, int numPoints, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_triangleFan, 0, 0, 2)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, triangleFan)
{
    zval *points;
    zval *color;
    HashTable *pointsArr;
    zval *zv;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(points)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    pointsArr = Z_ARRVAL_P(points);

    int numPoints = zend_hash_num_elements(pointsArr);
    Vector2 *pointsP = (Vector2 *)safe_emalloc(numPoints, sizeof(Vector2), 0);

    int n = 0;
    ZEND_HASH_FOREACH_VAL(pointsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_vector2_object *obj = Z_VECTOR2_OBJ_P(zv);
            pointsP[n] = obj->vector2;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleFan(pointsP, numPoints, phpColor->color);
}

// Draw a triangle strip defined by points
// RLAPI void DrawTriangleStrip(Vector2 *points, int pointsCount, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_triangleStrip, 0, 0, 2)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, triangleStrip)
{
    zval *points;
    zval *color;
    HashTable *pointsArr;
    zval *zv;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(points)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    pointsArr = Z_ARRVAL_P(points);

    int numPoints = zend_hash_num_elements(pointsArr);
    Vector2 *pointsP = (Vector2 *)safe_emalloc(numPoints, sizeof(Vector2), 0);

    int n = 0;
    ZEND_HASH_FOREACH_VAL(pointsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_vector2_object *obj = Z_VECTOR2_OBJ_P(zv);
            pointsP[n] = obj->vector2;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleStrip(pointsP, numPoints, phpColor->color);
}


// Draw a regular polygon (Vector version)
// RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_poly, 0, 0, 5)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, poly)
{
    zval *center;
    zend_long sides;
    double radius;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPoly(phpCenter->vector2, (int) radius, (float) radius, (float) rotation, phpColor->color);
}

// Draw a polygon outline of n sides
// RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_draw_polyLines, 0, 0, 5)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Draw, polyLines)
{
    zval *center;
    zend_long sides;
    double radius;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPolyLines(phpCenter->vector2, (int) radius, (float) radius, (float) rotation, phpColor->color);
}


const zend_function_entry php_raylib_draw_methods[] = {
        PHP_ME(Draw, __construct     , arginfo_draw__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Draw, clearBackground , arginfo_draw_clearBackground, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, begin           , arginfo_draw_begin, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, end             , arginfo_draw_end, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, beginMode2d     , arginfo_draw_beginMode2d, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endMode2d       , arginfo_draw_endMode2d, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, beginMode3d     , arginfo_draw_beginMode3d, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endMode3d       , arginfo_draw_endMode3d, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, beginScissorMode, arginfo_draw_beginScissorMode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, endScissorMode  , arginfo_draw_endScissorMode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

        // Basic shapes drawing functions
        PHP_ME(Draw, pixel                , arginfo_draw_pixel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, pixelV               , arginfo_draw_pixelV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, line                 , arginfo_draw_line, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineV                , arginfo_draw_lineV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineEx               , arginfo_draw_lineEx, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineBezier           , arginfo_draw_lineBezier, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circle               , arginfo_draw_circle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleSector         , arginfo_draw_circleSector, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleSectorLines    , arginfo_draw_circleSectorLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleGradient       , arginfo_draw_circleGradient, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleV              , arginfo_draw_circleV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, circleLines          , arginfo_draw_circleLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, ellipse              , arginfo_draw_ellipse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, ellipseLines         , arginfo_draw_ellipseLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, ring                 , arginfo_draw_ring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, ringLines            , arginfo_draw_ringLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangle            , arginfo_draw_rectangle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleV           , arginfo_draw_rectangleV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleRec         , arginfo_draw_rectangleRec, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectanglePro         , arginfo_draw_rectanglePro, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleGradientV   , arginfo_draw_rectangleGradientV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleGradientH   , arginfo_draw_rectangleGradientH, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleGradientEx  , arginfo_draw_rectangleGradientEx, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleLines       , arginfo_draw_rectangleLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleLinesEx     , arginfo_draw_rectangleLinesEx, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleRounded     , arginfo_draw_rectangleRounded, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, rectangleRoundedLines, arginfo_draw_rectangleRoundedLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, lineStrip            , arginfo_draw_lineStrip, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, triangle             , arginfo_draw_triangle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, triangleLines        , arginfo_draw_triangleLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, triangleFan          , arginfo_draw_triangleFan, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, triangleStrip        , arginfo_draw_triangleStrip, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, poly                 , arginfo_draw_poly, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Draw, polyLines            , arginfo_draw_polyLines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_draw_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Draw", php_raylib_draw_methods);
    php_raylib_draw_ce = zend_register_internal_class(&ce);
    php_raylib_draw_ce->create_object = php_raylib_draw_new;

    memcpy(&php_raylib_draw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_draw_object_handlers.offset = XtOffsetOf(php_raylib_draw_object, std);
    php_raylib_draw_object_handlers.free_obj = &php_raylib_draw_free_storage;
    php_raylib_draw_object_handlers.clone_obj = NULL;
}