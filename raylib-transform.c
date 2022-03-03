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

        /* Type required before windows.h inclusion  */
        typedef struct tagMSG *LPMSG;

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"

#include "raylib-vector3.h"
#include "raylib-vector4.h"

#include "raylib-transform.h"

//------------------------------------------------------------------------------------------------------
//-- raylib Transform PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_transform_object_handlers;

static HashTable php_raylib_transform_prop_handlers;

typedef zend_object * (*raylib_transform_read_vector3_t)(php_raylib_transform_object *obj);
typedef int (*raylib_transform_write_vector3_t)(php_raylib_transform_object *obj,  zval *value);

typedef zend_object * (*raylib_transform_read_vector4_t)(php_raylib_transform_object *obj);
typedef int (*raylib_transform_write_vector4_t)(php_raylib_transform_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
static void php_raylib_transform_update_intern(php_raylib_transform_object *intern) {
    intern->transform.translation = intern->translation->vector3;
    intern->transform.rotation = intern->rotation->vector4;
    intern->transform.scale = intern->scale->vector3;
}
typedef struct _raylib_transform_prop_handler {
    raylib_transform_read_vector3_t read_vector3_func;
    raylib_transform_write_vector3_t write_vector3_func;
    raylib_transform_read_vector4_t read_vector4_func;
    raylib_transform_write_vector4_t write_vector4_func;
} raylib_transform_prop_handler;

static void php_raylib_transform_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_transform_read_vector3_t read_vector3_func,
                                                      raylib_transform_write_vector3_t write_vector3_func,
                                                      raylib_transform_read_vector4_t read_vector4_func,
                                                      raylib_transform_write_vector4_t write_vector4_func) /* {{{ */
{
    raylib_transform_prop_handler hnd;

    hnd.read_vector3_func = read_vector3_func;
    hnd.write_vector3_func = write_vector3_func;
    hnd.read_vector4_func = read_vector4_func;
    hnd.write_vector4_func = write_vector4_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_transform_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_transform_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_transform_property_reader(php_raylib_transform_object *obj, raylib_transform_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_vector3_func) {
        zend_object *ret = hnd->read_vector3_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_vector4_func) {
        zend_object *ret = hnd->read_vector4_func(obj);
        ZVAL_OBJ(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_transform_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_transform_object *obj;
    zval *retval = NULL;
    raylib_transform_prop_handler *hnd = NULL;

    obj = php_raylib_transform_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_transform_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_transform_object *obj;
    zval *retval = NULL;
    raylib_transform_prop_handler *hnd = NULL;

    obj = php_raylib_transform_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_transform_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_transform_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_transform_object *obj;
    raylib_transform_prop_handler *hnd;

    obj = php_raylib_transform_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_vector3_func) {
        hnd->write_vector3_func(obj, value);
    } else if (hnd && hnd->write_vector4_func) {
        hnd->write_vector4_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_transform_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_transform_object *obj;
    raylib_transform_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_transform_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_transform_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_transform_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_transform_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_transform_object *obj;
    HashTable *props;
    raylib_transform_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_transform_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_transform_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_transform_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_transform_object *intern = php_raylib_transform_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_transform_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_transform_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_transform_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_transform_object), ce);

    intern->prop_handler = &php_raylib_transform_prop_handlers;

    if (orig) {
        php_raylib_transform_object *other = php_raylib_transform_fetch_object(orig);

        zend_object *translation = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->translation->std);
        zend_object *rotation = php_raylib_vector4_new_ex(php_raylib_vector4_ce, &other->rotation->std);
        zend_object *scale = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->scale->std);

        php_raylib_vector3_object *phpTranslation = php_raylib_vector3_fetch_object(translation);
        php_raylib_vector4_object *phpRotation = php_raylib_vector4_fetch_object(rotation);
        php_raylib_vector3_object *phpScale = php_raylib_vector3_fetch_object(scale);

        intern->transform = (Transform) {
            .translation = (Vector3) {
                .x = other->transform.translation.x,
                .y = other->transform.translation.y,
                .z = other->transform.translation.z
            },
            .rotation = (Vector4) {
                .x = other->transform.rotation.x,
                .y = other->transform.rotation.y,
                .z = other->transform.rotation.z,
                .w = other->transform.rotation.w
            },
            .scale = (Vector3) {
                .x = other->transform.scale.x,
                .y = other->transform.scale.y,
                .z = other->transform.scale.z
            }
        };

        intern->translation = phpTranslation;
        intern->rotation = phpRotation;
        intern->scale = phpScale;
    } else {
        zend_object *translation = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *rotation = php_raylib_vector4_new_ex(php_raylib_vector4_ce, NULL);
        zend_object *scale = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);

        php_raylib_vector3_object *phpTranslation = php_raylib_vector3_fetch_object(translation);
        php_raylib_vector4_object *phpRotation = php_raylib_vector4_fetch_object(rotation);
        php_raylib_vector3_object *phpScale = php_raylib_vector3_fetch_object(scale);

        intern->transform = (Transform) {
            .translation = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            },
            .rotation = (Vector4) {
                .x = 0,
                .y = 0,
                .z = 0,
                .w = 0
            },
            .scale = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            }
        };
        intern->translation = phpTranslation;
        intern->rotation = phpRotation;
        intern->scale = phpScale;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_transform_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_transform_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_transform_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_transform_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_transform_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_transform__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, translation, raylib\\Vector3, 1)
    ZEND_ARG_OBJ_INFO(0, rotation, raylib\\Vector4, 1)
    ZEND_ARG_OBJ_INFO(0, scale, raylib\\Vector3, 1)
ZEND_END_ARG_INFO()
PHP_METHOD(Transform, __construct)
{
    zend_object *translation = NULL;
    php_raylib_vector3_object *phpTranslation;

    zend_object *rotation = NULL;
    php_raylib_vector4_object *phpRotation;

    zend_object *scale = NULL;
    php_raylib_vector3_object *phpScale;

    ZEND_PARSE_PARAMETERS_START(0, 3)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(translation, php_raylib_vector3_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(rotation, php_raylib_vector4_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(scale, php_raylib_vector3_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_transform_object *intern = Z_TRANSFORM_OBJ_P(ZEND_THIS);

    if (translation == NULL) {
        translation = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (rotation == NULL) {
        rotation = php_raylib_vector4_new_ex(php_raylib_vector4_ce, NULL);
    }

    if (scale == NULL) {
        scale = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    phpTranslation = php_raylib_vector3_fetch_object(translation);
    phpRotation = php_raylib_vector4_fetch_object(rotation);
    phpScale = php_raylib_vector3_fetch_object(scale);

    intern->translation = phpTranslation;
    intern->rotation = phpRotation;
    intern->scale = phpScale;

    intern->transform = (Transform) {
        .translation = (Vector3) {
            .x = phpTranslation->vector3.x,
            .y = phpTranslation->vector3.y,
            .z = phpTranslation->vector3.z
        },
        .rotation = (Vector4) {
            .x = phpRotation->vector4.x,
            .y = phpRotation->vector4.y,
            .z = phpRotation->vector4.z,
            .w = phpRotation->vector4.w
        },
        .scale = (Vector3) {
            .x = phpScale->vector3.x,
            .y = phpScale->vector3.y,
            .z = phpScale->vector3.z
        }
    };
}

static zend_object * php_raylib_transform_get_translation(php_raylib_transform_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->translation->std);
    return &obj->translation->std;
}
/* }}} */

static zend_object * php_raylib_transform_get_rotation(php_raylib_transform_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->rotation->std);
    return &obj->rotation->std;
}
/* }}} */

static zend_object * php_raylib_transform_get_scale(php_raylib_transform_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->scale->std);
    return &obj->scale->std;
}
/* }}} */

static int php_raylib_transform_set_translation(php_raylib_transform_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_vector3_object *phpTranslation = Z_VECTOR3_OBJ_P(newval);
//    obj->translation = phpTranslation;

    return ret;
}
/* }}} */

static int php_raylib_transform_set_rotation(php_raylib_transform_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_vector4_object *phpRotation = Z_VECTOR4_OBJ_P(newval);
//    obj->rotation = phpRotation;

    return ret;
}
/* }}} */

static int php_raylib_transform_set_scale(php_raylib_transform_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_vector3_object *phpScale = Z_VECTOR3_OBJ_P(newval);
//    obj->scale = phpScale;

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_transform_methods[] = {
        PHP_ME(Transform, __construct, arginfo_transform__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_transform_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_transform_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_transform_object_handlers.offset = XtOffsetOf(php_raylib_transform_object, std);
    php_raylib_transform_object_handlers.free_obj = &php_raylib_transform_free_storage;
    php_raylib_transform_object_handlers.clone_obj = php_raylib_transform_clone;

    // Props
    php_raylib_transform_object_handlers.get_property_ptr_ptr = php_raylib_transform_get_property_ptr_ptr;
    php_raylib_transform_object_handlers.get_gc               = php_raylib_transform_get_gc;
    php_raylib_transform_object_handlers.get_properties       = php_raylib_transform_get_properties;
    php_raylib_transform_object_handlers.read_property	     = php_raylib_transform_read_property;
    php_raylib_transform_object_handlers.write_property       = php_raylib_transform_write_property;
    php_raylib_transform_object_handlers.has_property	     = php_raylib_transform_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Transform", php_raylib_transform_methods);
    php_raylib_transform_ce = zend_register_internal_class(&ce);
    php_raylib_transform_ce->create_object = php_raylib_transform_new;

    // Props
    zend_hash_init(&php_raylib_transform_prop_handlers, 0, NULL, php_raylib_transform_free_prop_handler, 1);
    php_raylib_transform_register_prop_handler(&php_raylib_transform_prop_handlers, "translation", php_raylib_transform_get_translation, php_raylib_transform_set_translation, NULL, NULL);
    php_raylib_transform_register_prop_handler(&php_raylib_transform_prop_handlers, "rotation", NULL, NULL, php_raylib_transform_get_rotation, php_raylib_transform_set_rotation);
    php_raylib_transform_register_prop_handler(&php_raylib_transform_prop_handlers, "scale", php_raylib_transform_get_scale, php_raylib_transform_set_scale, NULL, NULL);
}
