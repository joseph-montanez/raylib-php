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
#include "raylib-ray.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Ray PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_ray_object_handlers;

static HashTable php_raylib_ray_prop_handlers;

typedef zend_object* (*raylib_ray_read_vector3_object_t)(php_raylib_ray_object *obj);

typedef int (*raylib_ray_write_vector3_object_t)(php_raylib_ray_object *obj, zval *value);

typedef struct _raylib_ray_prop_handler {
    raylib_ray_read_vector3_object_t read_vector3_func;
    raylib_ray_write_vector3_object_t write_vector3_func;
} raylib_ray_prop_handler;
/* }}} */

static void php_raylib_ray_register_prop_handler(HashTable *prop_handler, char *name, raylib_ray_read_vector3_object_t read_vector3_func, raylib_ray_write_vector3_object_t write_vector3_func) /* {{{ */
{
    raylib_ray_prop_handler hnd;

    hnd.read_vector3_func = read_vector3_func;
    hnd.write_vector3_func = write_vector3_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_ray_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_ray_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_ray_property_reader(php_raylib_ray_object *obj, raylib_ray_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_vector3_func) {
        zend_object *ret = hnd->read_vector3_func(obj);
        ZVAL_OBJ(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_ray_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_ray_object *obj;
    zval *retval = NULL;
    raylib_ray_prop_handler *hnd = NULL;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_ray_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_ray_object *obj;
    zval *retval = NULL;
    raylib_ray_prop_handler *hnd = NULL;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_ray_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_ray_write_property(zend_object *object, zend_string *name, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_ray_write_property(zend_object *object, zend_string *name, zval *value, void **cache_slot)
{
    php_raylib_ray_object *obj;
    raylib_ray_prop_handler *hnd;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        hnd->write_vector3_func(obj, value);
    } else {
        value = zend_std_write_property(object, name, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_ray_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_ray_object *obj;
    raylib_ray_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_ray_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_ray_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_ray_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_ray_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_ray_object *obj;
    HashTable *props;
    raylib_ray_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_ray_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_ray_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_ray_free_storage(zend_object *object)
{
    php_raylib_ray_object *intern = php_raylib_ray_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_ray_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_ray_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_ray_object), ce);

    intern->prop_handler = &php_raylib_ray_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    if (orig) {
        php_raylib_ray_object *other = php_raylib_ray_fetch_object(orig);

        zend_object *position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->position->std);
        zend_object *direction = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->direction->std);

        php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);
        php_raylib_vector3_object *phpDirection = php_raylib_vector3_fetch_object(direction);

        intern->ray = (Ray) {
                .position = (Vector3) {
                        .x = other->position->vector3.x,
                        .y = other->position->vector3.y,
                        .z = other->position->vector3.z
                },
                .direction = (Vector3) {
                        .x = other->direction->vector3.x,
                        .y = other->direction->vector3.y,
                        .z = other->direction->vector3.z
                }
        };
        intern->position = phpPosition;
        intern->direction = phpDirection;
    } else {
        zend_object *position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *direction = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);

        php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);
        php_raylib_vector3_object *phpDirection = php_raylib_vector3_fetch_object(direction);

        intern->position = phpPosition;
        intern->direction = phpDirection;
    }

    intern->std.handlers = &php_raylib_ray_object_handlers;

    return &intern->std;
}

/* {{{  */
static zend_object *php_raylib_ray_new(zend_class_entry *class_type)
{
    return php_raylib_ray_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_ray_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_ray_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static zend_object * php_raylib_ray_direction(php_raylib_ray_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->direction->std);
    return &obj->direction->std;
}

static zend_object * php_raylib_ray_position(php_raylib_ray_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->position->std);
    return &obj->position->std;
}
/* }}} */


static int php_raylib_ray_write_direction(php_raylib_ray_object *ray_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *phpDirection = Z_VECTOR3_OBJ_P(newval);
    ray_object->direction = phpDirection;

    return ret;
}
/* }}} */

static int php_raylib_ray_write_position(php_raylib_ray_object *ray_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(newval);
    ray_object->position = phpPosition;

    return ret;
}
/* }}} */

// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_ray__construct, 0, 0, 2)
                ZEND_ARG_INFO(0, position)
                ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, __construct)
{
    zval *position;
    zval *direction;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(position)
            Z_PARAM_ZVAL(direction)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpDirection = Z_VECTOR3_OBJ_P(direction);

    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);

    intern->position = phpPosition;
    intern->direction = phpDirection;
    intern->ray = (Ray) {
            .position = phpPosition->vector3,
            .direction = phpDirection->vector3,
    };

}

ZEND_BEGIN_ARG_INFO_EX(arginfo_ray_getPosition, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, getPosition)
{
    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);

    RETURN_OBJ(&intern->position->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_ray_setPosition, 0, 0, 1)
                ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, setPosition)
{
    zval *position;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(position)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);

    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);

    intern->ray.position = phpPosition->vector3;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_ray_getDirection, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, getDirection)
{
    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);

    RETURN_OBJ(&intern->direction->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_ray_setDirection, 0, 0, 1)
                ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, setDirection)
{
    zval *direction;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(direction)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpDirection = Z_VECTOR3_OBJ_P(direction);

    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);
    intern->direction = phpDirection;

    intern->ray.direction = phpDirection->vector3;
}


const zend_function_entry php_raylib_ray_methods[] = {
        PHP_ME(Ray, __construct, arginfo_ray__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Ray, getPosition, arginfo_ray_getPosition, ZEND_ACC_PUBLIC)
        PHP_ME(Ray, setPosition, arginfo_ray_setPosition, ZEND_ACC_PUBLIC)
        PHP_ME(Ray, getDirection, arginfo_ray_getDirection, ZEND_ACC_PUBLIC)
        PHP_ME(Ray, setDirection, arginfo_ray_setDirection, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_ray_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_ray_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_ray_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_ray_object_handlers.offset    = XtOffsetOf(php_raylib_ray_object, std);
    php_raylib_ray_object_handlers.free_obj  = &php_raylib_ray_free_storage;
    php_raylib_ray_object_handlers.clone_obj = php_raylib_ray_clone;

    // Props
    php_raylib_ray_object_handlers.get_property_ptr_ptr = php_raylib_ray_get_property_ptr_ptr;
    php_raylib_ray_object_handlers.get_gc               = php_raylib_ray_get_gc;
    php_raylib_ray_object_handlers.get_properties       = php_raylib_ray_get_properties;
    php_raylib_ray_object_handlers.read_property	    = php_raylib_ray_read_property;
    php_raylib_ray_object_handlers.write_property       = php_raylib_ray_write_property;
    php_raylib_ray_object_handlers.has_property	        = php_raylib_ray_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Ray", php_raylib_ray_methods);
    php_raylib_ray_ce = zend_register_internal_class(&ce);
    php_raylib_ray_ce->create_object = php_raylib_ray_new;

    // Props
    zend_hash_init(&php_raylib_ray_prop_handlers, 0, NULL, php_raylib_ray_free_prop_handler, 1);
    php_raylib_ray_register_prop_handler(&php_raylib_ray_prop_handlers, "position", php_raylib_ray_position, php_raylib_ray_write_position);
    php_raylib_ray_register_prop_handler(&php_raylib_ray_prop_handlers, "direction", php_raylib_ray_direction, php_raylib_ray_write_direction);
}