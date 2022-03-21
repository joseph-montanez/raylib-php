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
/*#define NONLS           // All NLS defines and routines*/
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
#define VC_EXTRALEAN      // Maybe fix?
#define WIN32_LEAN_AND_MEAN // Maybe fix?

/* Type required before windows.h inclusion  */
typedef struct tagMSG* LPMSG;

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"


#include "color.h"

//------------------------------------------------------------------------------------------------------
//-- raylib Color PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_color_object_handlers;

static HashTable php_raylib_color_prop_handlers;

typedef zend_long (*raylib_color_read_unsigned_char_t)(php_raylib_color_object *obj);
typedef int (*raylib_color_write_unsigned_char_t)(php_raylib_color_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_color_update_intern(php_raylib_color_object *intern) {
}

void php_raylib_color_update_intern_reverse(php_raylib_color_object *intern) {
}
typedef struct _raylib_color_prop_handler {
    raylib_color_read_unsigned_char_t read_unsigned_char_func;
    raylib_color_write_unsigned_char_t write_unsigned_char_func;
} raylib_color_prop_handler;

static void php_raylib_color_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_color_read_unsigned_char_t read_unsigned_char_func,
                                                      raylib_color_write_unsigned_char_t write_unsigned_char_func) /* {{{ */
{
    raylib_color_prop_handler hnd;

    hnd.read_unsigned_char_func = read_unsigned_char_func;
    hnd.write_unsigned_char_func = write_unsigned_char_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_color_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_color_property_reader(php_raylib_color_object *obj, raylib_color_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_unsigned_char_func) {
        ZVAL_LONG(rv, hnd->read_unsigned_char_func(obj));
    }

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

static zval *php_raylib_color_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_color_object *obj;
    raylib_color_prop_handler *hnd;

    obj = php_raylib_color_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_unsigned_char_func) {
        hnd->write_unsigned_char_func(obj, value);
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

void php_raylib_color_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_color_object *intern = php_raylib_color_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_color_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_color_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_color_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_color_object), ce);

    intern->prop_handler = &php_raylib_color_prop_handlers;

    if (orig) {
        php_raylib_color_object *other = php_raylib_color_fetch_object(orig);

        intern->color = (Color) {
            .r = other->color.r,
            .g = other->color.g,
            .b = other->color.b,
            .a = other->color.a
        };
    } else {
        intern->color = (Color) {
            .r = 0,
            .g = 0,
            .b = 0,
            .a = 0
        };
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_color_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_color_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_color_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_color_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_color_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_color__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, r, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, g, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, b, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, a, IS_LONG, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Color, __construct)
{
    zend_long r;
    bool r_is_null = 1;

    zend_long g;
    bool g_is_null = 1;

    zend_long b;
    bool b_is_null = 1;

    zend_long a;
    bool a_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG_OR_NULL(r, r_is_null)
        Z_PARAM_LONG_OR_NULL(g, g_is_null)
        Z_PARAM_LONG_OR_NULL(b, b_is_null)
        Z_PARAM_LONG_OR_NULL(a, a_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *intern = Z_COLOR_OBJ_P(ZEND_THIS);

    if (r_is_null) {
        r = 0;
    }

    if (g_is_null) {
        g = 0;
    }

    if (b_is_null) {
        b = 0;
    }

    if (a_is_null) {
        a = 0;
    }



    intern->color = (Color) {
        .r = r,
        .g = g,
        .b = b,
        .a = a
    };
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_LIGHTGRAY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, LIGHTGRAY)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){200, 200, 200, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_GRAY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, GRAY)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){130, 130, 130, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_DARKGRAY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, DARKGRAY)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){80, 80, 80, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_YELLOW, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, YELLOW)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){253, 249, 0, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_GOLD, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, GOLD)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){255, 203, 0, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_ORANGE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, ORANGE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){255, 161, 0, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_PINK, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, PINK)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){255, 109, 194, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_RED, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, RED)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){230, 41, 55, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_MAROON, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, MAROON)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){190, 33, 55, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_GREEN, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, GREEN)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 228, 48, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_LIME, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, LIME)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 158, 47, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_DARKGREEN, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, DARKGREEN)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 117, 44, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_SKYBLUE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, SKYBLUE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){102, 191, 255, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_BLUE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, BLUE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 121, 241, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_DARKBLUE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, DARKBLUE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 82, 172, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_PURPLE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, PURPLE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){200, 122, 255, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_VIOLET, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, VIOLET)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){135, 60, 190, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_DARKPURPLE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, DARKPURPLE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){112, 31, 126, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_BEIGE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, BEIGE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){211, 176, 131, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_BROWN, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, BROWN)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){127, 106, 79, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_DARKBROWN, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, DARKBROWN)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){76, 63, 47, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_WHITE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, WHITE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){255, 255, 255, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_BLACK, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, BLACK)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 0, 0, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_BLANK, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, BLANK)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){0, 0, 0, 0};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_MAGENTA, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, MAGENTA)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){255, 0, 255, 255};

    RETURN_OBJ(&result->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_color_RAYWHITE, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, RAYWHITE)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color = (Color){245, 245, 245, 255};

    RETURN_OBJ(&result->std);
}

static zend_long php_raylib_color_get_r(php_raylib_color_object *obj) /* {{{ */
{
    return (zend_long) obj->color.r;
}
/* }}} */

static zend_long php_raylib_color_get_g(php_raylib_color_object *obj) /* {{{ */
{
    return (zend_long) obj->color.g;
}
/* }}} */

static zend_long php_raylib_color_get_b(php_raylib_color_object *obj) /* {{{ */
{
    return (zend_long) obj->color.b;
}
/* }}} */

static zend_long php_raylib_color_get_a(php_raylib_color_object *obj) /* {{{ */
{
    return (zend_long) obj->color.a;
}
/* }}} */

static int php_raylib_color_set_r(php_raylib_color_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->color.r = 0;
        return ret;
    }

    obj->color.r = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_color_set_g(php_raylib_color_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->color.g = 0;
        return ret;
    }

    obj->color.g = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_color_set_b(php_raylib_color_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->color.b = 0;
        return ret;
    }

    obj->color.b = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_color_set_a(php_raylib_color_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->color.a = 0;
        return ret;
    }

    obj->color.a = (unsigned char) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_color_methods[] = {
        PHP_ME(Color, __construct, arginfo_color__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Color, LIGHTGRAY, arginfo_color_LIGHTGRAY, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, GRAY, arginfo_color_GRAY, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, DARKGRAY, arginfo_color_DARKGRAY, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, YELLOW, arginfo_color_YELLOW, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, GOLD, arginfo_color_GOLD, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, ORANGE, arginfo_color_ORANGE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, PINK, arginfo_color_PINK, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, RED, arginfo_color_RED, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, MAROON, arginfo_color_MAROON, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, GREEN, arginfo_color_GREEN, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, LIME, arginfo_color_LIME, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, DARKGREEN, arginfo_color_DARKGREEN, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, SKYBLUE, arginfo_color_SKYBLUE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, BLUE, arginfo_color_BLUE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, DARKBLUE, arginfo_color_DARKBLUE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, PURPLE, arginfo_color_PURPLE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, VIOLET, arginfo_color_VIOLET, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, DARKPURPLE, arginfo_color_DARKPURPLE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, BEIGE, arginfo_color_BEIGE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, BROWN, arginfo_color_BROWN, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, DARKBROWN, arginfo_color_DARKBROWN, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, WHITE, arginfo_color_WHITE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, BLACK, arginfo_color_BLACK, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, BLANK, arginfo_color_BLANK, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, MAGENTA, arginfo_color_MAGENTA, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Color, RAYWHITE, arginfo_color_RAYWHITE, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};
void php_raylib_color_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_color_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_color_object_handlers.offset = XtOffsetOf(php_raylib_color_object, std);
    php_raylib_color_object_handlers.free_obj = &php_raylib_color_free_storage;
    php_raylib_color_object_handlers.clone_obj = php_raylib_color_clone;

    // Props
    php_raylib_color_object_handlers.get_property_ptr_ptr = php_raylib_color_get_property_ptr_ptr;
    php_raylib_color_object_handlers.get_gc               = php_raylib_color_get_gc;
    php_raylib_color_object_handlers.get_properties       = php_raylib_color_get_properties;
    php_raylib_color_object_handlers.read_property	     = php_raylib_color_read_property;
    php_raylib_color_object_handlers.write_property       = php_raylib_color_write_property;
    php_raylib_color_object_handlers.has_property	     = php_raylib_color_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Color", php_raylib_color_methods);
    php_raylib_color_ce = zend_register_internal_class(&ce);
    php_raylib_color_ce->create_object = php_raylib_color_new;

    // Props
    zend_hash_init(&php_raylib_color_prop_handlers, 0, NULL, php_raylib_color_free_prop_handler, 1);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "r", php_raylib_color_get_r, php_raylib_color_set_r);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "g", php_raylib_color_get_g, php_raylib_color_set_g);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "b", php_raylib_color_get_b, php_raylib_color_set_b);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "a", php_raylib_color_get_a, php_raylib_color_set_a);
}
