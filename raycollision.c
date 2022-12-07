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

#include "vector3.h"

#include "raycollision.h"

//------------------------------------------------------------------------------------------------------
//-- raylib RayCollision PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_raycollision_object_handlers;

static HashTable php_raylib_raycollision_prop_handlers;

typedef bool (*raylib_raycollision_read_bool_t)(php_raylib_raycollision_object *obj);
typedef int (*raylib_raycollision_write_bool_t)(php_raylib_raycollision_object *obj,  zval *value);

typedef double (*raylib_raycollision_read_float_t)(php_raylib_raycollision_object *obj);
typedef int (*raylib_raycollision_write_float_t)(php_raylib_raycollision_object *obj,  zval *value);

typedef zend_object * (*raylib_raycollision_read_vector3_t)(php_raylib_raycollision_object *obj);
typedef int (*raylib_raycollision_write_vector3_t)(php_raylib_raycollision_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_raycollision_update_intern(php_raylib_raycollision_object *intern) {
    php_raylib_vector3_object *pointObject = Z_VECTOR3_OBJ_P(&intern->point);
    intern->raycollision.point = pointObject->vector3;

    php_raylib_vector3_object *normalObject = Z_VECTOR3_OBJ_P(&intern->normal);
    intern->raycollision.normal = normalObject->vector3;

}

void php_raylib_raycollision_update_intern_reverse(php_raylib_raycollision_object *intern) {
    php_raylib_vector3_object *pointObject = Z_VECTOR3_OBJ_P(&intern->point);
    pointObject->vector3 = intern->raycollision.point;

    php_raylib_vector3_object *normalObject = Z_VECTOR3_OBJ_P(&intern->normal);
    normalObject->vector3 = intern->raycollision.normal;

}
typedef struct _raylib_raycollision_prop_handler {
    raylib_raycollision_read_bool_t read_bool_func;
    raylib_raycollision_write_bool_t write_bool_func;
    raylib_raycollision_read_float_t read_float_func;
    raylib_raycollision_write_float_t write_float_func;
    raylib_raycollision_read_vector3_t read_vector3_func;
    raylib_raycollision_write_vector3_t write_vector3_func;
} raylib_raycollision_prop_handler;

static void php_raylib_raycollision_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_raycollision_read_bool_t read_bool_func,
                                                      raylib_raycollision_write_bool_t write_bool_func,
                                                      raylib_raycollision_read_float_t read_float_func,
                                                      raylib_raycollision_write_float_t write_float_func,
                                                      raylib_raycollision_read_vector3_t read_vector3_func,
                                                      raylib_raycollision_write_vector3_t write_vector3_func) /* {{{ */
{
    raylib_raycollision_prop_handler hnd;

    hnd.read_bool_func = read_bool_func;
    hnd.write_bool_func = write_bool_func;
    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    hnd.read_vector3_func = read_vector3_func;
    hnd.write_vector3_func = write_vector3_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_raycollision_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_raycollision_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_raycollision_property_reader(php_raylib_raycollision_object *obj, raylib_raycollision_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_bool_func) {
    }
    else if (obj != NULL && hnd->read_float_func) {
        ZVAL_DOUBLE(rv, hnd->read_float_func(obj));
    }
    else if (obj != NULL && hnd->read_vector3_func) {
        zend_object *ret = hnd->read_vector3_func(obj);
        ZVAL_OBJ(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_raycollision_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_raycollision_object *obj;
    zval *retval = NULL;
    raylib_raycollision_prop_handler *hnd = NULL;

    obj = php_raylib_raycollision_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_raycollision_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_raycollision_object *obj;
    zval *retval = NULL;
    raylib_raycollision_prop_handler *hnd = NULL;

    obj = php_raylib_raycollision_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_raycollision_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_raycollision_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_raycollision_object *obj;
    raylib_raycollision_prop_handler *hnd;

    obj = php_raylib_raycollision_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_bool_func) {
        hnd->write_bool_func(obj, value);
    } else if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else if (hnd && hnd->write_vector3_func) {
        hnd->write_vector3_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_raycollision_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_raycollision_object *obj;
    raylib_raycollision_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_raycollision_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_raycollision_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_raycollision_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_raycollision_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_raycollision_object *obj;
    HashTable *props;
    raylib_raycollision_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_raycollision_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_raycollision_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_raycollision_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_raycollision_object *intern = php_raylib_raycollision_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_raycollision_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_raycollision_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_raycollision_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_raycollision_object), ce);

    intern->prop_handler = &php_raylib_raycollision_prop_handlers;

    if (orig) {
        php_raylib_raycollision_object *other = php_raylib_raycollision_fetch_object(orig);

        php_raylib_vector3_object *phpPoint = Z_VECTOR3_OBJ_P(&other->point);
        php_raylib_vector3_object *phpNormal = Z_VECTOR3_OBJ_P(&other->normal);


        intern->raycollision = (RayCollision) {
            .hit = other->raycollision.hit,
            .distance = other->raycollision.distance,
            .point = (Vector3) {
                .x = other->raycollision.point.x,
                .y = other->raycollision.point.y,
                .z = other->raycollision.point.z
            },
            .normal = (Vector3) {
                .x = other->raycollision.normal.x,
                .y = other->raycollision.normal.y,
                .z = other->raycollision.normal.z
            }
        };

        ZVAL_OBJ_COPY(&intern->point, &phpPoint->std);

        ZVAL_OBJ_COPY(&intern->normal, &phpNormal->std);

    } else {
        zend_object *point = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *normal = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);

        php_raylib_vector3_object *phpPoint = php_raylib_vector3_fetch_object(point);
        php_raylib_vector3_object *phpNormal = php_raylib_vector3_fetch_object(normal);

        intern->raycollision = (RayCollision) {
            .hit = 0,
            .distance = 0,
            .point = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            },
            .normal = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            }
        };

        ZVAL_OBJ_COPY(&intern->point, &phpPoint->std);

        ZVAL_OBJ_COPY(&intern->normal, &phpNormal->std);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_raycollision_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_raycollision_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_raycollision_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_raycollision_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_raycollision_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_raycollision__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, hit, _IS_BOOL, "1")
    ZEND_ARG_TYPE_MASK(0, distance, IS_DOUBLE, "0")
    ZEND_ARG_OBJ_INFO(0, point, raylib\\Vector3, 1)
    ZEND_ARG_OBJ_INFO(0, normal, raylib\\Vector3, 1)
ZEND_END_ARG_INFO()
PHP_METHOD(RayCollision, __construct)
{
    bool hit;
    bool hit_is_null = 1;

    double distance;
    bool distance_is_null = 1;

    zend_object *point = NULL;
    php_raylib_vector3_object *phpPoint;

    zend_object *normal = NULL;
    php_raylib_vector3_object *phpNormal;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL_OR_NULL(hit, hit_is_null)
        Z_PARAM_DOUBLE_OR_NULL(distance, distance_is_null)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(point, php_raylib_vector3_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(normal, php_raylib_vector3_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_raycollision_object *intern = Z_RAYCOLLISION_OBJ_P(ZEND_THIS);

    if (hit_is_null) {
        hit = false;
    }

    if (distance_is_null) {
        distance = 0.0f;
    }

    if (point == NULL) {
        point = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (normal == NULL) {
        normal = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    phpPoint = php_raylib_vector3_fetch_object(point);
    phpNormal = php_raylib_vector3_fetch_object(normal);

    ZVAL_OBJ_COPY(&intern->point, &phpPoint->std);
    ZVAL_OBJ_COPY(&intern->normal, &phpNormal->std);

    intern->raycollision = (RayCollision) {
        .hit = hit,
        .distance = distance,
        .point = (Vector3) {
            .x = phpPoint->vector3.x,
            .y = phpPoint->vector3.y,
            .z = phpPoint->vector3.z
        },
        .normal = (Vector3) {
            .x = phpNormal->vector3.x,
            .y = phpNormal->vector3.y,
            .z = phpNormal->vector3.z
        }
    };
}

static bool php_raylib_raycollision_get_hit(php_raylib_raycollision_object *obj) /* {{{ */
{
    return obj->raycollision.hit;
}
/* }}} */

static double php_raylib_raycollision_get_distance(php_raylib_raycollision_object *obj) /* {{{ */
{
    return (double) obj->raycollision.distance;
}
/* }}} */

static zend_object * php_raylib_raycollision_get_point(php_raylib_raycollision_object *obj) /* {{{ */
{
    php_raylib_vector3_object *phpPoint = Z_VECTOR3_OBJ_P(&obj->point);

    GC_ADDREF(&phpPoint->std);
    return &phpPoint->std;
}
/* }}} */

static zend_object * php_raylib_raycollision_get_normal(php_raylib_raycollision_object *obj) /* {{{ */
{
    php_raylib_vector3_object *phpNormal = Z_VECTOR3_OBJ_P(&obj->normal);

    GC_ADDREF(&phpNormal->std);
    return &phpNormal->std;
}
/* }}} */

static int php_raylib_raycollision_set_hit(php_raylib_raycollision_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;


    return ret;
}
/* }}} */

static int php_raylib_raycollision_set_distance(php_raylib_raycollision_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->raycollision.distance = 0;
        return ret;
    }

    obj->raycollision.distance = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_raycollision_set_point(php_raylib_raycollision_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    obj->point = *newval;

    return ret;
}
/* }}} */

static int php_raylib_raycollision_set_normal(php_raylib_raycollision_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    obj->normal = *newval;

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_raycollision_methods[] = {
        PHP_ME(RayCollision, __construct, arginfo_raycollision__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_raycollision_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_raycollision_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_raycollision_object_handlers.offset = XtOffsetOf(php_raylib_raycollision_object, std);
    php_raylib_raycollision_object_handlers.free_obj = &php_raylib_raycollision_free_storage;
    php_raylib_raycollision_object_handlers.clone_obj = php_raylib_raycollision_clone;

    // Props
    php_raylib_raycollision_object_handlers.get_property_ptr_ptr = php_raylib_raycollision_get_property_ptr_ptr;
    php_raylib_raycollision_object_handlers.get_gc               = php_raylib_raycollision_get_gc;
    php_raylib_raycollision_object_handlers.get_properties       = php_raylib_raycollision_get_properties;
    php_raylib_raycollision_object_handlers.read_property	     = php_raylib_raycollision_read_property;
    php_raylib_raycollision_object_handlers.write_property       = php_raylib_raycollision_write_property;
    php_raylib_raycollision_object_handlers.has_property	     = php_raylib_raycollision_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "RayCollision", php_raylib_raycollision_methods);
    php_raylib_raycollision_ce = zend_register_internal_class(&ce);
    php_raylib_raycollision_ce->create_object = php_raylib_raycollision_new;

    // Props
    zend_hash_init(&php_raylib_raycollision_prop_handlers, 0, NULL, php_raylib_raycollision_free_prop_handler, 1);
    php_raylib_raycollision_register_prop_handler(&php_raylib_raycollision_prop_handlers, "hit", php_raylib_raycollision_get_hit, php_raylib_raycollision_set_hit, NULL, NULL, NULL, NULL);
    php_raylib_raycollision_register_prop_handler(&php_raylib_raycollision_prop_handlers, "distance", NULL, NULL, php_raylib_raycollision_get_distance, php_raylib_raycollision_set_distance, NULL, NULL);
    php_raylib_raycollision_register_prop_handler(&php_raylib_raycollision_prop_handlers, "point", NULL, NULL, NULL, NULL, php_raylib_raycollision_get_point, php_raylib_raycollision_set_point);
    php_raylib_raycollision_register_prop_handler(&php_raylib_raycollision_prop_handlers, "normal", NULL, NULL, NULL, NULL, php_raylib_raycollision_get_normal, php_raylib_raycollision_set_normal);
}
