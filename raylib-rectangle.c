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