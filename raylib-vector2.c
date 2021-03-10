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
#include "raylib-vector2.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Vector2 PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vector2_object_handlers;

static HashTable php_raylib_vector2_prop_handlers;

typedef double (*raylib_vector2_read_float_t)(php_raylib_vector2_object *obj);

typedef int (*raylib_vector2_write_float_t)(php_raylib_vector2_object *obj, zval *value);

typedef struct _raylib_vector2_prop_handler {
    raylib_vector2_read_float_t read_float_func;
    raylib_vector2_write_float_t write_float_func;
} raylib_vector2_prop_handler;
/* }}} */

static void php_raylib_vector2_register_prop_handler(HashTable *prop_handler, char *name, raylib_vector2_read_float_t read_float_func, raylib_vector2_write_float_t write_float_func) /* {{{ */
{
    raylib_vector2_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_vector2_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_vector2_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_vector2_property_reader(php_raylib_vector2_object *obj, raylib_vector2_prop_handler *hnd, zval *rv) /* {{{ */
{
    double ret = 0;

    if (obj != NULL && hnd->read_float_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vector2 found");
        ret = hnd->read_float_func(obj);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }

    ZVAL_DOUBLE(rv, (double) ret);

    return rv;
}
/* }}} */

static zval *php_raylib_vector2_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_vector2_object *obj;
    zval *retval = NULL;
    raylib_vector2_prop_handler *hnd = NULL;

    obj = php_raylib_vector2_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_vector2_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_vector2_object *obj;
    zval *retval = NULL;
    raylib_vector2_prop_handler *hnd = NULL;

    obj = php_raylib_vector2_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_vector2_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_vector2_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_vector2_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_vector2_object *obj;
    raylib_vector2_prop_handler *hnd;

    obj = php_raylib_vector2_fetch_object(object);

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

static int php_raylib_vector2_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_vector2_object *obj;
    raylib_vector2_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_vector2_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_vector2_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_vector2_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_vector2_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_vector2_object *obj;
    HashTable *props;
    raylib_vector2_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_vector2_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_vector2_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_vector2_free_storage(zend_object *object)
{
    php_raylib_vector2_object *intern = php_raylib_vector2_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}


zend_object * php_raylib_vector2_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_vector2_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_vector2_object), ce);

    intern->prop_handler = &php_raylib_vector2_prop_handlers;

    if (orig) {
        php_raylib_vector2_object *other = php_raylib_vector2_fetch_object(orig);
        intern->vector2 = (Vector2) {
                .x = other->vector2.x,
                .y = other->vector2.y
        };
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_vector2_object_handlers;

    return &intern->std;
}


/* {{{  */
static zend_object *php_raylib_vector2_new(zend_class_entry *class_type)
{
    return php_raylib_vector2_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_vector2_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_vector2_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static double php_raylib_vector2_x(php_raylib_vector2_object *obj) /* {{{ */
{
    return (double) obj->vector2.x;
}
/* }}} */

static double php_raylib_vector2_y(php_raylib_vector2_object *obj) /* {{{ */
{
    return (double) obj->vector2.y;
}
/* }}} */

static int php_raylib_vector2_write_x(php_raylib_vector2_object *vector2_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        vector2_object->vector2.x = 0;
        return ret;
    }

    vector2_object->vector2.x = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vector2_write_y(php_raylib_vector2_object *vector2_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        vector2_object->vector2.y = 0;
        return ret;
    }

    vector2_object->vector2.y = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2__construct, 0, 0, 2)
                ZEND_ARG_INFO(0, x)
                ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector2, __construct)
{
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);

    intern->vector2 = (Vector2) {
        .x = (float) x,
        .y = (float) y
    };

}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2_getX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector2, getX)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector2.x);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2_setX, 0, 0, 1)
                ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector2, setX)
{
    double x;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(x)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);

    intern->vector2.x = (float) x;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2_getY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector2, getY)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector2.y);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2_setY, 0, 0, 1)
                ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector2, setY)
{
    double y;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);

    intern->vector2.y = (float) y;
}

const zend_function_entry php_raylib_vector2_methods[] = {
        PHP_ME(Vector2, __construct, arginfo_vector2__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getX, arginfo_vector2_getX, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setX, arginfo_vector2_setX, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getY, arginfo_vector2_getY, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setY, arginfo_vector2_setY, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_vector2_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_vector2_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_vector2_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vector2_object_handlers.offset = XtOffsetOf(php_raylib_vector2_object, std);
    php_raylib_vector2_object_handlers.free_obj = &php_raylib_vector2_free_storage;
    php_raylib_vector2_object_handlers.clone_obj = php_raylib_vector2_clone;

    // Props
    php_raylib_vector2_object_handlers.get_property_ptr_ptr = php_raylib_vector2_get_property_ptr_ptr;
    php_raylib_vector2_object_handlers.get_gc               = php_raylib_vector2_get_gc;
    php_raylib_vector2_object_handlers.get_properties       = php_raylib_vector2_get_properties;
    php_raylib_vector2_object_handlers.read_property	    = php_raylib_vector2_read_property;
    php_raylib_vector2_object_handlers.write_property       = php_raylib_vector2_write_property;
    php_raylib_vector2_object_handlers.has_property	        = php_raylib_vector2_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Vector2", php_raylib_vector2_methods);
    php_raylib_vector2_ce = zend_register_internal_class(&ce);
    php_raylib_vector2_ce->create_object = php_raylib_vector2_new;

    // Props
    zend_hash_init(&php_raylib_vector2_prop_handlers, 0, NULL, php_raylib_vector2_free_prop_handler, 1);
    php_raylib_vector2_register_prop_handler(&php_raylib_vector2_prop_handlers, "x", php_raylib_vector2_x, php_raylib_vector2_write_x);
    php_raylib_vector2_register_prop_handler(&php_raylib_vector2_prop_handlers, "y", php_raylib_vector2_y, php_raylib_vector2_write_y);
}