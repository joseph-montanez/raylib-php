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
#include "raylib-vector3.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Vector3 PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vector3_object_handlers;

static HashTable php_raylib_vector3_prop_handlers;

typedef double (*raylib_vector3_read_float_t)(php_raylib_vector3_object *obj);

typedef int (*raylib_vector3_write_float_t)(php_raylib_vector3_object *obj, zval *value);

typedef struct _raylib_vector3_prop_handler {
    raylib_vector3_read_float_t read_float_func;
    raylib_vector3_write_float_t write_float_func;
} raylib_vector3_prop_handler;
/* }}} */

static void php_raylib_vector3_register_prop_handler(HashTable *prop_handler, char *name, raylib_vector3_read_float_t read_float_func, raylib_vector3_write_float_t write_float_func) /* {{{ */
{
    raylib_vector3_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_vector3_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_vector3_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_vector3_property_reader(php_raylib_vector3_object *obj, raylib_vector3_prop_handler *hnd, zval *rv) /* {{{ */
{
    double ret = 0;

    if (obj != NULL && hnd->read_float_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vector3 found");
        ret = hnd->read_float_func(obj);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }

    ZVAL_DOUBLE(rv, (double) ret);

    return rv;
}
/* }}} */

static zval *php_raylib_vector3_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_vector3_object *obj;
    zval *retval = NULL;
    raylib_vector3_prop_handler *hnd = NULL;

    obj = php_raylib_vector3_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_vector3_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_vector3_object *obj;
    zval *retval = NULL;
    raylib_vector3_prop_handler *hnd = NULL;

    obj = php_raylib_vector3_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_vector3_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_vector3_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_vector3_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_vector3_object *obj;
    raylib_vector3_prop_handler *hnd;

    obj = php_raylib_vector3_fetch_object(object);

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

static int php_raylib_vector3_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_vector3_object *obj;
    raylib_vector3_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_vector3_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_vector3_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_vector3_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_vector3_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_vector3_object *obj;
    HashTable *props;
    raylib_vector3_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_vector3_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_vector3_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_vector3_free_storage(zend_object *object)
{
    php_raylib_vector3_object *intern = php_raylib_vector3_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}


zend_object * php_raylib_vector3_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_vector3_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_vector3_object), ce);

    intern->prop_handler = &php_raylib_vector3_prop_handlers;

    if (orig) {
        php_raylib_vector3_object *other = php_raylib_vector3_fetch_object(orig);
        intern->vector3 = (Vector3) {
                .x = other->vector3.x,
                .y = other->vector3.y,
                .z = other->vector3.z
        };
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_vector3_object_handlers;

    return &intern->std;
}


/* {{{  */
static zend_object *php_raylib_vector3_new(zend_class_entry *class_type)
{
    return php_raylib_vector3_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_vector3_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_vector3_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static double php_raylib_vector3_x(php_raylib_vector3_object *obj) /* {{{ */
{
    return (double) obj->vector3.x;
}
/* }}} */

static double php_raylib_vector3_y(php_raylib_vector3_object *obj) /* {{{ */
{
    return (double) obj->vector3.y;
}
/* }}} */

static double php_raylib_vector3_z(php_raylib_vector3_object *obj) /* {{{ */
{
    return (double) obj->vector3.z;
}
/* }}} */

static int php_raylib_vector3_write_x(php_raylib_vector3_object *vector3_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        vector3_object->vector3.x = 0;
        return ret;
    }

    vector3_object->vector3.x = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vector3_write_y(php_raylib_vector3_object *vector3_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        vector3_object->vector3.y = 0;
        return ret;
    }

    vector3_object->vector3.y = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vector3_write_z(php_raylib_vector3_object *vector3_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        vector3_object->vector3.z = 0;
        return ret;
    }

    vector3_object->vector3.z = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3__construct, 0, 0, 3)
                ZEND_ARG_INFO(0, x)
                ZEND_ARG_INFO(0, y)
                ZEND_ARG_INFO(0, z)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, __construct)
{
    double x;
    double y;
    double z;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);

    intern->vector3 = (Vector3) {
        .x = (float) x,
        .y = (float) y,
        .z = (float) z
    };

}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_getX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, getX)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector3.x);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_setX, 0, 0, 1)
                ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, setX)
{
    double x;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(x)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);

    intern->vector3.x = (float) x;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_getY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, getY)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector3.y);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_setY, 0, 0, 1)
                ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, setY)
{
    double y;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);

    intern->vector3.y = (float) y;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_getZ, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, getZ)
{
    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector3.z);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_setZ, 0, 0, 1)
                ZEND_ARG_INFO(0, z)
ZEND_END_ARG_INFO()
PHP_METHOD(Vector3, setZ)
{
    double z;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *intern = Z_VECTOR3_OBJ_P(ZEND_THIS);

    intern->vector3.z = (float) z;
}

const zend_function_entry php_raylib_vector3_methods[] = {
        PHP_ME(Vector3, __construct, arginfo_vector3__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getX, arginfo_vector3_getX, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setX, arginfo_vector3_setX, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getY, arginfo_vector3_getY, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setY, arginfo_vector3_setY, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, getZ, arginfo_vector3_getZ, ZEND_ACC_PUBLIC)
        PHP_ME(Vector3, setZ, arginfo_vector3_setZ, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_vector3_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_vector3_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_vector3_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vector3_object_handlers.offset = XtOffsetOf(php_raylib_vector3_object, std);
    php_raylib_vector3_object_handlers.free_obj = &php_raylib_vector3_free_storage;
    php_raylib_vector3_object_handlers.clone_obj = php_raylib_vector3_clone;

    // Props
    php_raylib_vector3_object_handlers.get_property_ptr_ptr = php_raylib_vector3_get_property_ptr_ptr;
    php_raylib_vector3_object_handlers.get_gc               = php_raylib_vector3_get_gc;
    php_raylib_vector3_object_handlers.get_properties       = php_raylib_vector3_get_properties;
    php_raylib_vector3_object_handlers.read_property	    = php_raylib_vector3_read_property;
    php_raylib_vector3_object_handlers.write_property       = php_raylib_vector3_write_property;
    php_raylib_vector3_object_handlers.has_property	        = php_raylib_vector3_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Vector3", php_raylib_vector3_methods);
    php_raylib_vector3_ce = zend_register_internal_class(&ce);
    php_raylib_vector3_ce->create_object = php_raylib_vector3_new;

    // Props
    zend_hash_init(&php_raylib_vector3_prop_handlers, 0, NULL, php_raylib_vector3_free_prop_handler, 1);
    php_raylib_vector3_register_prop_handler(&php_raylib_vector3_prop_handlers, "x", php_raylib_vector3_x, php_raylib_vector3_write_x);
    php_raylib_vector3_register_prop_handler(&php_raylib_vector3_prop_handlers, "y", php_raylib_vector3_y, php_raylib_vector3_write_y);
    php_raylib_vector3_register_prop_handler(&php_raylib_vector3_prop_handlers, "z", php_raylib_vector3_z, php_raylib_vector3_write_z);
}