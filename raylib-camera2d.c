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
#include "raylib-camera2d.h"
#include "raylib-utils.h"
#include "raylib-rectangle.h"
#include "raylib-vector2.h"


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

// PHP object handling

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

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = intern->camera2d.offset;

    RETURN_OBJ(&result->std);
}

PHP_METHOD(Camera2d, setOffset)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    zval *offset;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(offset)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpOffset = Z_VECTOR2_OBJ_P(offset);

    intern->camera2d.offset.x = phpOffset->vector2.x;
    intern->camera2d.offset.y = phpOffset->vector2.y;
}

PHP_METHOD(Camera2d, getTarget)
{
    php_raylib_camera2d_object *self = Z_CAMERA2D_OBJ_P(getThis());

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = self->camera2d.target;

    RETURN_OBJ(&result->std);
}

PHP_METHOD(Camera2d, setTarget)
{
    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(getThis());

    zval *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpTarget = Z_VECTOR2_OBJ_P(target);

    intern->camera2d.target = phpTarget->vector2;
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

    intern->camera2d.zoom = (float) zoom;
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