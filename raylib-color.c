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
#include "raylib-color.h"
#include "raylib-utils.h"
#include "raylib-vector4.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Color PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_color_object_handlers;

void php_raylib_color_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_color_object *intern = php_raylib_color_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_color_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_color_object *intern;
    intern = (php_raylib_color_object*) ecalloc(1, sizeof(php_raylib_color_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_color_object_handlers;

    return &intern->std;
}

zval *php_raylib_color_raywhite()
{
    zval *return_value;

    Color raywhite = RAYWHITE;

    array_init_size(return_value, 4);
    add_index_long(return_value, 0, raywhite.r);
    add_index_long(return_value, 1, raywhite.b);
    add_index_long(return_value, 2, raywhite.g);
    add_index_long(return_value, 3, raywhite.a);

    return return_value;
}

// PHP object handling
PHP_METHOD(Color, __construct)
{
    zend_long r = 0;
    zend_long g = 0;
    zend_long b = 0;
    zend_long a = 0;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_LONG(r)
            Z_PARAM_LONG(g)
            Z_PARAM_LONG(b)
            Z_PARAM_LONG(a)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());

    intern->color = (Color) {
            .r = (unsigned char) r,
            .g = (unsigned char) g,
            .b = (unsigned char) b,
            .a = (unsigned char) a
    };
}

PHP_METHOD(Color, toInt)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(color);

    RETURN_LONG(ColorToInt(intern->color));
}

PHP_METHOD(Color, normalize)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(color);

//    zval *obj = malloc(sizeof(zval));
//    object_init_ex(obj, php_raylib_vector4_ce);
//
//    php_raylib_vector4_object *result = Z_VECTOR4_OBJ_P(obj);
//    result->vector4 = ColorNormalize(intern->color);
//
//    RETURN_OBJ(&result->std);
}

PHP_METHOD(Color, fade)
{
    zval *color;
    double fade;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(color)
            Z_PARAM_DOUBLE(fade)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(color);

//
//    zval *obj = malloc(sizeof(zval));
//    object_init_ex(obj, php_raylib_color_ce);
//
//    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
//    result->color = Fade(intern->color, (float) fade);
//
//    RETURN_OBJ(&result->std);
}

PHP_METHOD(Color, getAlpha)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());
    RETURN_DOUBLE(intern->color.a);
}

PHP_METHOD(Color, setAlpha)
{
    zval *alpha;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(alpha)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());

    intern->color.a = zend_double_2float(alpha);
}

PHP_METHOD(Color, getRed)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());
    RETURN_DOUBLE(intern->color.r);
}

PHP_METHOD(Color, setRed)
{
    zval *red;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(red)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());

    intern->color.r = zend_double_2float(red);
}

PHP_METHOD(Color, getGreen)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());
    RETURN_DOUBLE(intern->color.g);
}

PHP_METHOD(Color, setGreen)
{
    zval *green;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(green)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());

    intern->color.g = zend_double_2float(green);
}

PHP_METHOD(Color, getBlue)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());
    RETURN_DOUBLE(intern->color.b);
}

PHP_METHOD(Color, setBlue)
{
    zval *blue;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(blue)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());

    intern->color.b = zend_double_2float(blue);
}

/*
 *     // Color-related functions
    int ColorToInt(Color color);                                            // Returns hexadecimal value for a Color
    Vector4 ColorNormalize(Color color);                                    // Returns color normalized as float [0..1]
    Vector3 ColorToHSV(Color color);                                        // Returns HSV values for a Color
    Color GetColor(int hexValue);                                           // Returns a Color struct from hexadecimal value
    Color Fade(Color color, float alpha);                                   // Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
 */

const zend_function_entry php_raylib_color_methods[] = {
        PHP_ME(Color, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, toInt, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, normalize, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
//        PHP_ME(Color, toHSV, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
//        PHP_ME(Color, getColor, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, fade, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, setAlpha, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getAlpha, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setRed, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getRed, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setGreen, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getGreen, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setBlue, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getBlue, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_color_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Color", php_raylib_color_methods);
    php_raylib_color_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_color_ce->create_object = php_raylib_color_new;

    memcpy(&php_raylib_color_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_color_object_handlers.offset = XtOffsetOf(php_raylib_color_object, std);
    php_raylib_color_object_handlers.free_obj = &php_raylib_color_free_storage;
    php_raylib_color_object_handlers.clone_obj = NULL;

}
//zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_STATIC);