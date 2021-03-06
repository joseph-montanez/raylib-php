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
#include "raylib-utils.h"
#include "raylib-collision.h"
#include "raylib-vector2.h"
#include "raylib-rectangle.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Collision PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_collision_object_handlers;

void php_raylib_collision_free_storage(zend_object *object)
{
    php_raylib_collision_object *intern = php_raylib_collision_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_collision_new(zend_class_entry *ce)
{
    php_raylib_collision_object *intern;
    intern = (php_raylib_collision_object*) ecalloc(1, sizeof(php_raylib_collision_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_collision_object_handlers;

    return &intern->std;
}

// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_collision__construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, __construct)
{
    php_raylib_collision_object *intern = Z_COLLISION_OBJ_P(ZEND_THIS);
}


// Check collision between two rectangles
// RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkRecs, 0, 0, 2)
    ZEND_ARG_INFO(0, rec1)
    ZEND_ARG_INFO(0, rec2)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkRecs)
{
    zval *rec1;
    zval *rec2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec1)
        Z_PARAM_ZVAL(rec2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRect1 = Z_RECTANGLE_OBJ_P(rec1);
    php_raylib_rectangle_object *phpRect2 = Z_RECTANGLE_OBJ_P(rec2);

    RETURN_BOOL(CheckCollisionRecs(phpRect1->rectangle, phpRect2->rectangle));
}

// Check collision between two circles
// RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkCircles, 0, 0, 4)
    ZEND_ARG_INFO(0, center1)
    ZEND_ARG_INFO(0, radius1)
    ZEND_ARG_INFO(0, center2)
    ZEND_ARG_INFO(0, radius2)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkCircles)
{
    zval *center1;
    double radius1;
    zval *center2;
    double radius2;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(center1)
        Z_PARAM_DOUBLE(radius1)
        Z_PARAM_ZVAL(center2)
        Z_PARAM_DOUBLE(radius2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter1 = Z_VECTOR2_OBJ_P(center1);
    php_raylib_vector2_object *phpCenter2 = Z_VECTOR2_OBJ_P(center2);

    RETURN_BOOL(CheckCollisionCircles(phpCenter1->vector2, (float) radius1, phpCenter2->vector2, (float) radius2));
}

// Check collision between circle and rectangle
// RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkCircleRec, 0, 0, 3)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkCircleRec)
{
    zval *center;
    double radius;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);

    RETURN_BOOL(CheckCollisionCircleRec(phpCenter->vector2, (float) radius, phpRec->rectangle));
}


// Check if point is inside rectangle
// RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkPointRec, 0, 0, 2)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkPointRec)
{
    zval *point;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(point)
            Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_rectangle_object *phpRect = Z_RECTANGLE_OBJ_P(rec);

    RETURN_BOOL(CheckCollisionPointRec(phpPoint->vector2, phpRect->rectangle));
}

// Get collision rectangle for two rectangles collision
// Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_getRec, 0, 0, 2)
    ZEND_ARG_INFO(0, rec1)
    ZEND_ARG_INFO(0, rec2)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, getRec)
{
    zval *rec1;
    zval *rec2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec1)
        Z_PARAM_ZVAL(rec2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec1 = Z_RECTANGLE_OBJ_P(rec1);
    php_raylib_rectangle_object *phpRec2 = Z_RECTANGLE_OBJ_P(rec2);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_rectangle_ce);

    php_raylib_rectangle_object *result = Z_RECTANGLE_OBJ_P(obj);
    result->rectangle = GetCollisionRec(phpRec1->rectangle, phpRec2->rectangle);

    result->rectangle;

    RETURN_OBJ(&result->std);
}



// Check if point is inside circle
// RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkPointCircle, 0, 0, 3)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkPointCircle)
{
    zval *point;
    zval *center;
    double radius;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);

    RETURN_BOOL(CheckCollisionPointCircle(phpPoint->vector2, phpCenter->vector2, (float) radius));
}

// Check if point is inside a triangle
// RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkPointTriangle, 0, 0, 4)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, p1)
    ZEND_ARG_INFO(0, p2)
    ZEND_ARG_INFO(0, p3)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkPointTriangle)
{
    zval *point;
    zval *p1;
    zval *p2;
    zval *p3;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(p1)
        Z_PARAM_ZVAL(p2)
        Z_PARAM_ZVAL(p3)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_vector2_object *phpP1 = Z_VECTOR2_OBJ_P(p1);
    php_raylib_vector2_object *phpP2 = Z_VECTOR2_OBJ_P(p2);
    php_raylib_vector2_object *phpP3 = Z_VECTOR2_OBJ_P(p3);

    RETURN_BOOL(CheckCollisionPointTriangle(phpPoint->vector2, phpP1->vector2, phpP2->vector2, phpP3->vector2));
}



// Check the collision between two lines defined by two points each, returns collision point by reference
// bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_collision_checkLines, 0, 0, 4)
    ZEND_ARG_INFO(0, startPos1)
    ZEND_ARG_INFO(0, endPos1)
    ZEND_ARG_INFO(0, startPos2)
    ZEND_ARG_INFO(0, endPos2)
    ZEND_ARG_INFO(0, collisionPoint)
ZEND_END_ARG_INFO()
PHP_METHOD(Collision, checkLines)
{
    zval *startPos1;
    zval *endPos1;
    zval *startPos2;
    zval *endPos2;
    zval *collisionPoint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(startPos1)
        Z_PARAM_ZVAL(endPos1)
        Z_PARAM_ZVAL(startPos2)
        Z_PARAM_ZVAL(endPos2)
        Z_PARAM_ZVAL(collisionPoint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos1      = Z_VECTOR2_OBJ_P(startPos1);
    php_raylib_vector2_object *phpEndPos1        = Z_VECTOR2_OBJ_P(endPos1);
    php_raylib_vector2_object *phpStartPos2      = Z_VECTOR2_OBJ_P(startPos2);
    php_raylib_vector2_object *phpEndPos2        = Z_VECTOR2_OBJ_P(endPos2);
    php_raylib_vector2_object *phpCollisionPoint = Z_VECTOR2_OBJ_P(collisionPoint);

    RETURN_BOOL(CheckCollisionLines(phpStartPos1->vector2, phpEndPos1->vector2, phpStartPos2->vector2, phpEndPos2->vector2, &phpCollisionPoint->vector2));
}


const zend_function_entry php_raylib_collision_methods[] = {
        PHP_ME(Collision, __construct       , arginfo_collision__construct        , ZEND_ACC_PUBLIC)
        PHP_ME(Collision, checkRecs         , arginfo_collision_checkRecs         , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkCircles      , arginfo_collision_checkCircles      , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkCircleRec    , arginfo_collision_checkCircleRec    , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, getRec            , arginfo_collision_getRec            , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkPointRec     , arginfo_collision_checkPointRec     , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkPointCircle  , arginfo_collision_checkPointCircle  , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkLines        , arginfo_collision_checkLines        , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Collision, checkPointTriangle, arginfo_collision_checkPointTriangle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_collision_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Collision", php_raylib_collision_methods);
    php_raylib_collision_ce = zend_register_internal_class(&ce);
    php_raylib_collision_ce->create_object = php_raylib_collision_new;

    memcpy(&php_raylib_collision_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_collision_object_handlers.offset = XtOffsetOf(php_raylib_collision_object, std);
    php_raylib_collision_object_handlers.free_obj = &php_raylib_collision_free_storage;
    php_raylib_collision_object_handlers.clone_obj = NULL;
}

