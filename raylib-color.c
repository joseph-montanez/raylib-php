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
#include "raylib-vector3.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Color PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_color_object_handlers;

static HashTable php_raylib_color_prop_handlers;

typedef unsigned char (*raylib_color_read_float_t)(php_raylib_color_object *obj);

typedef int (*raylib_color_write_float_t)(php_raylib_color_object *obj, zval *value);

typedef struct _raylib_color_prop_handler {
    raylib_color_read_float_t read_unsigned_char_func;
    raylib_color_write_float_t write_float_func;
} raylib_color_prop_handler;
/* }}} */


static void php_raylib_color_register_prop_handler(HashTable *prop_handler, char *name, raylib_color_read_float_t read_unsigned_char_func, raylib_color_write_float_t write_float_func) /* {{{ */
{
    raylib_color_prop_handler hnd;

    hnd.read_unsigned_char_func = read_unsigned_char_func;
    hnd.write_float_func = write_float_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_color_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_color_property_reader(php_raylib_color_object *obj, raylib_color_prop_handler *hnd, zval *rv) /* {{{ */
{
    zend_long ret = 0;

    if (obj != NULL && hnd->read_unsigned_char_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib color found");
        ret = hnd->read_unsigned_char_func(obj);
    } else {
        php_error_docref(NULL, E_WARNING, "Internal raylib color error returned");
    }

    ZVAL_LONG(rv, ret);

    return rv;
}
/* }}} */

static zval *php_raylib_color_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_color_object *obj;
    zval *retval = NULL;
    raylib_color_prop_handler *hnd = NULL;

    obj = php_raylib_color_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_color_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_color_object *obj;
    zval *retval = NULL;
    raylib_color_prop_handler *hnd = NULL;

    obj = php_raylib_color_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_color_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_color_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_color_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_color_object *obj;
    raylib_color_prop_handler *hnd;

    obj = php_raylib_color_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_color_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_color_object *obj;
    raylib_color_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_color_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_color_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    ret = Z_TYPE_P(value) != IS_NULL? 1 : 0;
                    zval_ptr_dtor(value);
                }
                break;
            }
                EMPTY_SWITCH_DEFAULT_CASE();
        }
    } else {
        ret = zend_std_has_property(object, name, has_set_exists, cache_slot);
    }

    return ret;
}
/* }}} */

static HashTable *php_raylib_color_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_color_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_color_object *obj;
    HashTable *props;
    raylib_color_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_color_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_color_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_color_free_storage(zend_object *object)
{
    php_raylib_color_object *intern = php_raylib_color_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_color_new(zend_class_entry *ce)
{
    php_raylib_color_object *intern;
    intern = (php_raylib_color_object*) ecalloc(1, sizeof(php_raylib_color_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_color_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_color_object_handlers;

    return &intern->std;
}

// PHP property handling

static unsigned char php_raylib_color_r(php_raylib_color_object *obj) /* {{{ */
{
    return (unsigned char) obj->color.r;
}
/* }}} */

static unsigned char php_raylib_color_g(php_raylib_color_object *obj) /* {{{ */
{
    return (unsigned char) obj->color.g;
}
/* }}} */

static unsigned char php_raylib_color_b(php_raylib_color_object *obj) /* {{{ */
{
    return (unsigned char) obj->color.b;
}
/* }}} */

static unsigned char php_raylib_color_a(php_raylib_color_object *obj) /* {{{ */
{
    return (unsigned char) obj->color.a;
}
/* }}} */



static int php_raylib_color_write_r(php_raylib_color_object *color_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        color_object->color.a = 0;
        return ret;
    }

    color_object->color.a = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_color_write_g(php_raylib_color_object *color_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        color_object->color.g = 0;
        return ret;
    }

    color_object->color.g = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */


static int php_raylib_color_write_b(php_raylib_color_object *color_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        color_object->color.b = 0;
        return ret;
    }

    color_object->color.b = (unsigned char) zval_get_long(newval);

    return ret;
}

static int php_raylib_color_write_a(php_raylib_color_object *color_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        color_object->color.a = 0;
        return ret;
    }

    color_object->color.a = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_color__construct, 0, 0, 4)
    ZEND_ARG_INFO(0, r)
    ZEND_ARG_INFO(0, b)
    ZEND_ARG_INFO(0, g)
    ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, __construct)
{
    zend_long r;
    zend_long g;
    zend_long b;
    zend_long a;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_LONG(r)
            Z_PARAM_LONG(g)
            Z_PARAM_LONG(b)
            Z_PARAM_LONG(a)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    intern->color = (Color) {
            .r = (unsigned char) r,
            .g = (unsigned char) g,
            .b = (unsigned char) b,
            .a = (unsigned char) a
    };
}

// Returns hexadecimal value for a Color
// RLAPI int ColorToInt(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_toInt, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, toInt)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    RETURN_LONG(ColorToInt(intern->color));
}

// Returns color normalized as float [0..1]
// RLAPI Vector4 ColorNormalize(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_normalize, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, normalize)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector4_ce);

    php_raylib_vector4_object *result = Z_VECTOR4_OBJ_P(obj);
    result->vector4 = ColorNormalize(intern->color);

    RETURN_OBJ(&result->std);
}

// Returns color from normalized values [0..1]
// RLAPI Color ColorFromNormalized(Vector4 normalized);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_fromNormalized, 0, 0, 1)
    ZEND_ARG_INFO(0, normalized)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, fromNormalized)
{
    zval *normalized;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(normalized)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *phpNormalized = Z_VECTOR4_OBJ_P(normalized);

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = ColorFromNormalized(phpNormalized->vector4);

    RETURN_OBJ(&result->std);
}

// Returns HSV values for a Color
// RLAPI Vector3 ColorToHSV(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_toHSV, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, toHSV)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector3_ce);

    php_raylib_vector3_object *result = Z_VECTOR3_OBJ_P(obj);
    result->vector3 = ColorToHSV(intern->color);

    RETURN_OBJ(&result->std);
}

// Returns a Color from HSV values
// RLAPI Color ColorFromHSV(Vector3 hsv);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_fromHSV, 0, 0, 3)
    ZEND_ARG_INFO(0, hue)
    ZEND_ARG_INFO(0, saturation)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, fromHSV)
{
    double hue;
    double saturation;
    double value;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_DOUBLE(hue)
            Z_PARAM_DOUBLE(saturation)
            Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = ColorFromHSV((float) hue, (float) saturation, (float) value);

    RETURN_OBJ(&result->std);
}

// Returns a Color struct from hexadecimal value
// RLAPI Color GetColor(int hexValue);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_fromInt, 0, 0, 1)
    ZEND_ARG_INFO(0, hexValue)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, fromInt)
{
    zend_long hexValue;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(hexValue)
    ZEND_PARSE_PARAMETERS_END();

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = GetColor((int) hexValue);

    RETURN_OBJ(&result->std);
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
// RLAPI Color Fade(Color color, float alpha);
ZEND_BEGIN_ARG_INFO_EX(arginfo_color_fade, 0, 0, 1)
    ZEND_ARG_INFO(0, fade)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, fade)
{
    double fade;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_DOUBLE(fade)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = Fade(intern->color, (float) fade);

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_getAlpha, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, getAlpha)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->color.a);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_setAlpha, 0, 0, 1)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, setAlpha)
{
    zend_long alpha;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(alpha)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    intern->color.a = (unsigned char) alpha;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_getRed, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, getRed)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->color.r);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_setRed, 0, 0, 1)
    ZEND_ARG_INFO(0, red)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, setRed)
{
    zend_long red;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(red)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    intern->color.r = (unsigned char) red;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_getGreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, getGreen)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->color.g);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_setGreen, 0, 0, 1)
    ZEND_ARG_INFO(0, green)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, setGreen)
{
    zend_long green;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(green)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    intern->color.g = (unsigned char) green;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_getBlue, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, getBlue)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->color.b);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_setBlue, 0, 0, 1)
    ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, setBlue)
{
    zend_long blue;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(blue)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    intern->color.b = (unsigned char) blue;
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
        PHP_ME(Color, __construct   , arginfo_color__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Color, toInt         , arginfo_color_toInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, fromInt       , arginfo_color_fromInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, normalize     , arginfo_color_normalize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, fromNormalized, arginfo_color_fromNormalized, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, toHSV         , arginfo_color_toHSV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, fromHSV       , arginfo_color_fromHSV, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, fade          , arginfo_color_fade, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setAlpha      , arginfo_color_setAlpha, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getAlpha      , arginfo_color_getAlpha, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setRed        , arginfo_color_setRed, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getRed        , arginfo_color_getRed, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setGreen      , arginfo_color_setGreen, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getGreen      , arginfo_color_getGreen, ZEND_ACC_PUBLIC)
        PHP_ME(Color, setBlue       , arginfo_color_setBlue, ZEND_ACC_PUBLIC)
        PHP_ME(Color, getBlue       , arginfo_color_getBlue, ZEND_ACC_PUBLIC)
        PHP_FE_END
};


static void php_raylib_color_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_color_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_color_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_color_object_handlers.offset = XtOffsetOf(php_raylib_color_object, std);
    php_raylib_color_object_handlers.free_obj = &php_raylib_color_free_storage;
    php_raylib_color_object_handlers.clone_obj = NULL;

    // Props Handlers
    php_raylib_color_object_handlers.get_property_ptr_ptr = php_raylib_color_get_property_ptr_ptr;
    php_raylib_color_object_handlers.get_gc               = php_raylib_color_get_gc;
    php_raylib_color_object_handlers.get_properties       = php_raylib_color_get_properties;
    php_raylib_color_object_handlers.read_property	      = php_raylib_color_read_property;
    php_raylib_color_object_handlers.write_property       = php_raylib_color_write_property;
    php_raylib_color_object_handlers.has_property	      = php_raylib_color_has_property;

    INIT_NS_CLASS_ENTRY(ce, "raylib", "Color", php_raylib_color_methods);
    php_raylib_color_ce = zend_register_internal_class(&ce);
    php_raylib_color_ce->create_object = php_raylib_color_new;

    // Object Props
    zend_hash_init(&php_raylib_color_prop_handlers, 0, NULL, php_raylib_color_free_prop_handler, 1);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "r", php_raylib_color_r, php_raylib_color_write_r);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "g", php_raylib_color_g, php_raylib_color_write_g);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "b", php_raylib_color_b, php_raylib_color_write_b);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "a", php_raylib_color_a, php_raylib_color_write_a);

}
//zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_STATIC);