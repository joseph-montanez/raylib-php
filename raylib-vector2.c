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
#include "raylib-utils.h"


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
        ret = hnd->read_float_func(obj);
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

/* {{{ php_raylib_vector2_write_property(zval *object, zend_string *member, zval *value[, const zend_literal *key])
   Generic object property writer */
zval *php_raylib_vector2_write_property(zval *object, zend_string *member, zval *value, void **cache_slot)
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

static int php_raylib_vector2_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_vector2_object *obj;
    zval tmp_member;
    raylib_vector2_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_VECTOR2_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_vector2_property_reader(obj, hnd, &tmp)) != NULL) {
            if (type == 1) {
                retval = zend_is_true(&tmp);
            } else if (type == 0) {
                retval = (Z_TYPE(tmp) != IS_NULL);
            }
        }

        zval_ptr_dtor(&tmp);
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->has_property(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static HashTable *php_raylib_vector2_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_vector2_get_properties(zval *object)/* {{{ */
{
    php_raylib_vector2_object *obj;
    HashTable *props;
    raylib_vector2_prop_handler *hnd;
    zend_string *key;

    obj = Z_VECTOR2_OBJ_P(object);
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

zend_object * php_raylib_vector2_new(zend_class_entry *ce)
{
    php_raylib_vector2_object *intern;
    intern = (php_raylib_vector2_object*) ecalloc(1, sizeof(php_raylib_vector2_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_vector2_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_vector2_object_handlers;

    return &intern->std;
}

static zend_object *php_raylib_vector2_clone(zval *zobject)
{
    zend_object *old_object;
    zend_object *new_object;

    old_object = Z_OBJ_P(zobject);
    new_object = php_raylib_vector2_new(old_object->ce);

    // zend_objects_clone_members(new_object, old_object);

    php_raylib_vector2_object *old_vector2 = php_raylib_vector2_fetch_object(old_object);
    php_raylib_vector2_object *new_vector2 = php_raylib_vector2_fetch_object(new_object);
    new_vector2->vector2 = old_vector2->vector2;

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

//    php_error_docref(NULL, E_WARNING, "'%f': no value set", zval_get_double(newval));


    vector2_object->vector2.y = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

// PHP object handling

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

PHP_METHOD(Vector2, getX)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector2.x);
}

PHP_METHOD(Vector2, setX)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);

    intern->vector2.x = zend_double_2float(val);
}

PHP_METHOD(Vector2, getY)
{
    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->vector2.y);
}

PHP_METHOD(Vector2, setY)
{
    zval *val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *intern = Z_VECTOR2_OBJ_P(ZEND_THIS);

    intern->vector2.y = zend_double_2float(val);
}

const zend_function_entry php_raylib_vector2_methods[] = {
        PHP_ME(Vector2, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setX, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, getY, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Vector2, setY, NULL, ZEND_ACC_PUBLIC)
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