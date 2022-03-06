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
typedef struct tagMSG *LPMSG;

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"

#include "raylib-vector2.h"

#include "raylib-camera2d.h"

//------------------------------------------------------------------------------------------------------
//-- raylib Camera2D PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_camera2d_object_handlers;

static HashTable php_raylib_camera2d_prop_handlers;

typedef zend_object * (*raylib_camera2d_read_vector2_t)(php_raylib_camera2d_object *obj);
typedef int (*raylib_camera2d_write_vector2_t)(php_raylib_camera2d_object *obj,  zval *value);

typedef double (*raylib_camera2d_read_float_t)(php_raylib_camera2d_object *obj);
typedef int (*raylib_camera2d_write_float_t)(php_raylib_camera2d_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_camera2d_update_intern(php_raylib_camera2d_object *intern) {
    intern->camera2d.offset = intern->offset->vector2;
    intern->camera2d.target = intern->target->vector2;
}
typedef struct _raylib_camera2d_prop_handler {
    raylib_camera2d_read_vector2_t read_vector2_func;
    raylib_camera2d_write_vector2_t write_vector2_func;
    raylib_camera2d_read_float_t read_float_func;
    raylib_camera2d_write_float_t write_float_func;
} raylib_camera2d_prop_handler;

static void php_raylib_camera2d_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_camera2d_read_vector2_t read_vector2_func,
                                                      raylib_camera2d_write_vector2_t write_vector2_func,
                                                      raylib_camera2d_read_float_t read_float_func,
                                                      raylib_camera2d_write_float_t write_float_func) /* {{{ */
{
    raylib_camera2d_prop_handler hnd;

    hnd.read_vector2_func = read_vector2_func;
    hnd.write_vector2_func = write_vector2_func;
    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_camera2d_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_camera2d_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_camera2d_property_reader(php_raylib_camera2d_object *obj, raylib_camera2d_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_vector2_func) {
        zend_object *ret = hnd->read_vector2_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_float_func) {
        ZVAL_DOUBLE(rv, hnd->read_float_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_camera2d_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_camera2d_object *obj;
    zval *retval = NULL;
    raylib_camera2d_prop_handler *hnd = NULL;

    obj = php_raylib_camera2d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_camera2d_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_camera2d_object *obj;
    zval *retval = NULL;
    raylib_camera2d_prop_handler *hnd = NULL;

    obj = php_raylib_camera2d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_camera2d_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_camera2d_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_camera2d_object *obj;
    raylib_camera2d_prop_handler *hnd;

    obj = php_raylib_camera2d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_vector2_func) {
        hnd->write_vector2_func(obj, value);
    } else if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_camera2d_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_camera2d_object *obj;
    raylib_camera2d_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_camera2d_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_camera2d_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_camera2d_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_camera2d_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_camera2d_object *obj;
    HashTable *props;
    raylib_camera2d_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_camera2d_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_camera2d_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_camera2d_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_camera2d_object *intern = php_raylib_camera2d_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_camera2d_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_camera2d_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_camera2d_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_camera2d_object), ce);

    intern->prop_handler = &php_raylib_camera2d_prop_handlers;

    if (orig) {
        php_raylib_camera2d_object *other = php_raylib_camera2d_fetch_object(orig);

        zend_object *offset = php_raylib_vector2_new_ex(php_raylib_vector2_ce, &other->offset->std);
        zend_object *target = php_raylib_vector2_new_ex(php_raylib_vector2_ce, &other->target->std);

        php_raylib_vector2_object *phpOffset = php_raylib_vector2_fetch_object(offset);
        php_raylib_vector2_object *phpTarget = php_raylib_vector2_fetch_object(target);

        intern->camera2d = (Camera2D) {
            .offset = (Vector2) {
                .x = other->camera2d.offset.x,
                .y = other->camera2d.offset.y
            },
            .target = (Vector2) {
                .x = other->camera2d.target.x,
                .y = other->camera2d.target.y
            },
            .rotation = other->camera2d.rotation,
            .zoom = other->camera2d.zoom
        };

        intern->offset = phpOffset;
        intern->target = phpTarget;
    } else {
        zend_object *offset = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
        zend_object *target = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);

        php_raylib_vector2_object *phpOffset = php_raylib_vector2_fetch_object(offset);
        php_raylib_vector2_object *phpTarget = php_raylib_vector2_fetch_object(target);

        intern->camera2d = (Camera2D) {
            .offset = (Vector2) {
                .x = 0,
                .y = 0
            },
            .target = (Vector2) {
                .x = 0,
                .y = 0
            },
            .rotation = 0,
            .zoom = 0
        };
        intern->offset = phpOffset;
        intern->target = phpTarget;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_camera2d_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_camera2d_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_camera2d_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_camera2d_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_camera2d_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_camera2d__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, offset, raylib\\Vector2, 1)
    ZEND_ARG_OBJ_INFO(0, target, raylib\\Vector2, 1)
    ZEND_ARG_TYPE_MASK(0, rotation, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, zoom, IS_DOUBLE, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Camera2D, __construct)
{
    zend_object *offset = NULL;
    php_raylib_vector2_object *phpOffset;

    zend_object *target = NULL;
    php_raylib_vector2_object *phpTarget;

    double rotation;
    bool rotation_is_null = 1;

    double zoom;
    bool zoom_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(offset, php_raylib_vector2_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(target, php_raylib_vector2_ce)
        Z_PARAM_DOUBLE_OR_NULL(rotation, rotation_is_null)
        Z_PARAM_DOUBLE_OR_NULL(zoom, zoom_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera2d_object *intern = Z_CAMERA2D_OBJ_P(ZEND_THIS);

    if (offset == NULL) {
        offset = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    }

    if (target == NULL) {
        target = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    }

    if (rotation_is_null) {
        rotation = 0.0f;
    }

    if (zoom_is_null) {
        zoom = 0.0f;
    }

    phpOffset = php_raylib_vector2_fetch_object(offset);
    phpTarget = php_raylib_vector2_fetch_object(target);

    intern->offset = phpOffset;
    intern->target = phpTarget;

    intern->camera2d = (Camera2D) {
        .offset = (Vector2) {
            .x = phpOffset->vector2.x,
            .y = phpOffset->vector2.y
        },
        .target = (Vector2) {
            .x = phpTarget->vector2.x,
            .y = phpTarget->vector2.y
        },
        .rotation = rotation,
        .zoom = zoom
    };
}

static zend_object * php_raylib_camera2d_get_offset(php_raylib_camera2d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->offset->std);
    return &obj->offset->std;
}
/* }}} */

static zend_object * php_raylib_camera2d_get_target(php_raylib_camera2d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->target->std);
    return &obj->target->std;
}
/* }}} */

static double php_raylib_camera2d_get_rotation(php_raylib_camera2d_object *obj) /* {{{ */
{
    return (double) obj->camera2d.rotation;
}
/* }}} */

static double php_raylib_camera2d_get_zoom(php_raylib_camera2d_object *obj) /* {{{ */
{
    return (double) obj->camera2d.zoom;
}
/* }}} */

static int php_raylib_camera2d_set_offset(php_raylib_camera2d_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector2_object *phpOffset = Z_VECTOR2_OBJ_P(newval);
    GC_ADDREF(&phpOffset->std);
    GC_DELREF(&obj->offset->std);
    obj->offset = phpOffset;

    return ret;
}
/* }}} */

static int php_raylib_camera2d_set_target(php_raylib_camera2d_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector2_object *phpTarget = Z_VECTOR2_OBJ_P(newval);
    GC_ADDREF(&phpTarget->std);
    GC_DELREF(&obj->target->std);
    obj->target = phpTarget;

    return ret;
}
/* }}} */

static int php_raylib_camera2d_set_rotation(php_raylib_camera2d_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->camera2d.rotation = 0;
        return ret;
    }

    obj->camera2d.rotation = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_camera2d_set_zoom(php_raylib_camera2d_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->camera2d.zoom = 0;
        return ret;
    }

    obj->camera2d.zoom = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_camera2d_methods[] = {
        PHP_ME(Camera2D, __construct, arginfo_camera2d__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_camera2d_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_camera2d_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_camera2d_object_handlers.offset = XtOffsetOf(php_raylib_camera2d_object, std);
    php_raylib_camera2d_object_handlers.free_obj = &php_raylib_camera2d_free_storage;
    php_raylib_camera2d_object_handlers.clone_obj = php_raylib_camera2d_clone;

    // Props
    php_raylib_camera2d_object_handlers.get_property_ptr_ptr = php_raylib_camera2d_get_property_ptr_ptr;
    php_raylib_camera2d_object_handlers.get_gc               = php_raylib_camera2d_get_gc;
    php_raylib_camera2d_object_handlers.get_properties       = php_raylib_camera2d_get_properties;
    php_raylib_camera2d_object_handlers.read_property	     = php_raylib_camera2d_read_property;
    php_raylib_camera2d_object_handlers.write_property       = php_raylib_camera2d_write_property;
    php_raylib_camera2d_object_handlers.has_property	     = php_raylib_camera2d_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Camera2D", php_raylib_camera2d_methods);
    php_raylib_camera2d_ce = zend_register_internal_class(&ce);
    php_raylib_camera2d_ce->create_object = php_raylib_camera2d_new;

    // Props
    zend_hash_init(&php_raylib_camera2d_prop_handlers, 0, NULL, php_raylib_camera2d_free_prop_handler, 1);
    php_raylib_camera2d_register_prop_handler(&php_raylib_camera2d_prop_handlers, "offset", php_raylib_camera2d_get_offset, php_raylib_camera2d_set_offset, NULL, NULL);
    php_raylib_camera2d_register_prop_handler(&php_raylib_camera2d_prop_handlers, "target", php_raylib_camera2d_get_target, php_raylib_camera2d_set_target, NULL, NULL);
    php_raylib_camera2d_register_prop_handler(&php_raylib_camera2d_prop_handlers, "rotation", NULL, NULL, php_raylib_camera2d_get_rotation, php_raylib_camera2d_set_rotation);
    php_raylib_camera2d_register_prop_handler(&php_raylib_camera2d_prop_handlers, "zoom", NULL, NULL, php_raylib_camera2d_get_zoom, php_raylib_camera2d_set_zoom);
}
