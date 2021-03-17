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
#include "raylib-vector2.h"
#include "raylib-ray.h"
#include "raylib-camera3d.h"
#include "raylib-utils.h"
#include "raylib-rectangle.h"
#include "raylib-matrix.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Camera3d PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_camera3d_object_handlers;

static HashTable php_raylib_camera3d_prop_handlers;

typedef double (*raylib_camera3d_read_float_t)(php_raylib_camera3d_object *obj);

typedef int (*raylib_camera3d_write_float_t)(php_raylib_camera3d_object *obj, zval *value);

typedef zend_object* (*raylib_camera3d_read_vector3_t)(php_raylib_camera3d_object *obj);

typedef int (*raylib_camera3d_write_vector3_t)(php_raylib_camera3d_object *obj, zval *value);

typedef zend_long (*raylib_camera3d_read_int_t)(php_raylib_camera3d_object *obj);

typedef int (*raylib_camera3d_write_int_t)(php_raylib_camera3d_object *obj, zval *value);

typedef struct _raylib_camera3d_prop_handler {
    raylib_camera3d_read_float_t read_float_func;
    raylib_camera3d_write_float_t write_float_func;
    raylib_camera3d_read_vector3_t read_vector3_func;
    raylib_camera3d_write_vector3_t write_vector3_func;
    raylib_camera3d_read_int_t read_int_func;
    raylib_camera3d_write_int_t write_int_func;
} raylib_camera3d_prop_handler;

/**
 * This will update
 * @param intern
 */
void php_raylib_camera3d_update_intern(php_raylib_camera3d_object *intern) {
    intern->camera3d.position = intern->position->vector3;
    intern->camera3d.target = intern->target->vector3;
    intern->camera3d.up = intern->up->vector3;
}

static void php_raylib_camera3d_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_camera3d_read_float_t read_float_func,
                                                      raylib_camera3d_write_float_t write_float_func,
                                                      raylib_camera3d_read_vector3_t read_vector3_func,
                                                      raylib_camera3d_write_vector3_t write_vector3_func,
                                                      raylib_camera3d_read_int_t read_int_func,
                                                      raylib_camera3d_write_int_t write_int_func) /* {{{ */
{
    raylib_camera3d_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    hnd.read_vector3_func = read_vector3_func;
    hnd.write_vector3_func = write_vector3_func;
    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_camera3d_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_camera3d_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_camera3d_property_reader(php_raylib_camera3d_object *obj, raylib_camera3d_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_vector3_func) {
        zend_object *ret = hnd->read_vector3_func(obj);
        ZVAL_OBJ(rv, ret);
    } else if (obj != NULL && hnd->read_float_func) {
        double ret = (double) hnd->read_float_func(obj);
        ZVAL_DOUBLE(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_camera3d_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_camera3d_object *obj;
    zval *retval = NULL;
    raylib_camera3d_prop_handler *hnd = NULL;

    obj = php_raylib_camera3d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_camera3d_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_camera3d_object *obj;
    zval *retval = NULL;
    raylib_camera3d_prop_handler *hnd = NULL;

    obj = php_raylib_camera3d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_camera3d_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_camera3d_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_camera3d_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_camera3d_object *obj;
    raylib_camera3d_prop_handler *hnd;

    obj = php_raylib_camera3d_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_vector3_func) {
        hnd->write_vector3_func(obj, value);
    } else if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_camera3d_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_camera3d_object *obj;
    raylib_camera3d_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_camera3d_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_camera3d_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_camera3d_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_camera3d_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_camera3d_object *obj;
    HashTable *props;
    raylib_camera3d_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_camera3d_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_camera3d_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_camera3d_free_storage(zend_object *object)
{
    php_raylib_camera3d_object *intern = php_raylib_camera3d_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}


zend_object * php_raylib_camera3d_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_camera3d_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_camera3d_object), ce);

    intern->prop_handler = &php_raylib_camera3d_prop_handlers;

    if (orig) {
        php_raylib_camera3d_object *other = php_raylib_camera3d_fetch_object(orig);

        zend_object *position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->position->std);
        zend_object *target = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->target->std);
        zend_object *up = php_raylib_vector3_new_ex(php_raylib_vector3_ce, &other->up->std);

        php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);
        php_raylib_vector3_object *phpTarget = php_raylib_vector3_fetch_object(target);
        php_raylib_vector3_object *phpUp = php_raylib_vector3_fetch_object(up);

        intern->camera3d = (Camera3D) {
                .position = (Vector3) {
                        .x = phpPosition->vector3.x,
                        .y = phpPosition->vector3.y,
                        .z = phpPosition->vector3.z
                },
                .target = (Vector3) {
                        .x = phpTarget->vector3.x,
                        .y = phpTarget->vector3.y,
                        .z = phpTarget->vector3.z
                },
                .up = (Vector3) {
                        .x = phpUp->vector3.x,
                        .y = phpUp->vector3.y,
                        .z = phpUp->vector3.z
                },
                .fovy = other->camera3d.fovy,
                .type = other->camera3d.type
        };
        intern->position = phpPosition;
        intern->target = phpTarget;
        intern->up = phpUp;
    } else {
        zend_object *position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *target = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *up = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);

        php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);
        php_raylib_vector3_object *phpTarget = php_raylib_vector3_fetch_object(target);
        php_raylib_vector3_object *phpUp = php_raylib_vector3_fetch_object(up);

        intern->camera3d = (Camera3D) {
                .position = (Vector3) {
                        .x = 0,
                        .y = 0,
                        .z = 0
                },
                .target = (Vector3) {
                        .x = 0,
                        .y = 0,
                        .z = 0
                },
                .up = (Vector3) {
                        .x = 0,
                        .y = 0,
                        .z = 0
                },
                .fovy = 0,
                .type = 1
        };
        intern->position = phpPosition;
        intern->target = phpTarget;
        intern->up = phpUp;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_camera3d_object_handlers;

    return &intern->std;
}

/* {{{  */
zend_object *php_raylib_camera3d_new(zend_class_entry *class_type)
{
    return php_raylib_camera3d_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_camera3d_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_camera3d_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static zend_object * php_raylib_camera3d_position(php_raylib_camera3d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->position->std);
    return &obj->position->std;
}
/* }}} */

static zend_object * php_raylib_camera3d_target(php_raylib_camera3d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->target->std);
    return &obj->target->std;
}
/* }}} */

static zend_object * php_raylib_camera3d_up(php_raylib_camera3d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->up->std);
    return &obj->up->std;
}
/* }}} */

static double php_raylib_camera3d_fovy(php_raylib_camera3d_object *obj) /* {{{ */
{
    return (double) obj->camera3d.fovy;
}
/* }}} */

static zend_long php_raylib_camera3d_type(php_raylib_camera3d_object *obj) /* {{{ */
{
    return (zend_long) obj->camera3d.type;
}
/* }}} */

static int php_raylib_camera3d_write_position(php_raylib_camera3d_object *camera3d_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(newval);
    camera3d_object->position = phpPosition;

    return ret;
}
/* }}} */

static int php_raylib_camera3d_write_target(php_raylib_camera3d_object *ray_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *phpTarget = Z_VECTOR3_OBJ_P(newval);
    ray_object->target = phpTarget;

    return ret;
}
/* }}} */

static int php_raylib_camera3d_write_up(php_raylib_camera3d_object *ray_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *phpUp = Z_VECTOR3_OBJ_P(newval);
    ray_object->up = phpUp;

    return ret;
}
/* }}} */

static int php_raylib_camera3d_write_fovy(php_raylib_camera3d_object *camera3d_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        camera3d_object->camera3d.fovy = 0;
        return ret;
    }

    camera3d_object->camera3d.fovy = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_camera3d_write_type(php_raylib_camera3d_object *camera3d_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        camera3d_object->camera3d.type = 0;
        return ret;
    }

    camera3d_object->camera3d.type = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d__construct, 0, 0, 0)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, up)
    ZEND_ARG_INFO(0, fovy)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, __construct)
{
    zend_object *position = NULL;
    php_raylib_vector3_object *phpPosition;

    zend_object *target = NULL;
    php_raylib_vector3_object *phpTarget;

    zend_object *up = NULL;
    php_raylib_vector3_object *phpUp;

    double fovy;
    bool fovy_is_null = 1;

    zend_long type;
    bool type_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(position, php_raylib_vector3_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(target, php_raylib_vector3_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(up, php_raylib_vector3_ce)
        Z_PARAM_DOUBLE_OR_NULL(fovy, fovy_is_null)
        Z_PARAM_LONG_OR_NULL(type, type_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);


    if (position == NULL) {
        position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (target == NULL) {
        target = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (up == NULL) {
        up = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (fovy_is_null) {
        fovy = 0.0f;
    }

    if (type_is_null) {
        type = 0;
    }

    phpPosition = php_raylib_vector3_fetch_object(position);
    phpTarget = php_raylib_vector3_fetch_object(target);
    phpUp = php_raylib_vector3_fetch_object(up);

    intern->position = phpPosition;
    intern->target = phpTarget;
    intern->up = phpUp;

    intern->camera3d = (Camera3D) {
            .position = (Vector3) {.x = phpPosition->vector3.x, .y = phpPosition->vector3.y, .z = phpPosition->vector3.z},
            .target = (Vector3) {.x = phpTarget->vector3.x, .y = phpTarget->vector3.y, .z = phpTarget->vector3.z},
            .up = (Vector3) {.x = phpUp->vector3.x,     .y = phpUp->vector3.y,     .z = phpUp->vector3.z},
            .fovy = fovy,
            .type = type
    };
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getPosition, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getPosition)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    RETURN_OBJ(&intern->position->std);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_setPosition, 0, 0, 1)
    ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, setPosition)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    zval *position;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(position)
    ZEND_PARSE_PARAMETERS_END();
    
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    
    intern->camera3d.position.x = phpPosition->vector3.x;
    intern->camera3d.position.y = phpPosition->vector3.y;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getTarget, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getTarget)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    RETURN_OBJ(&intern->target->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_setTarget, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, setTarget)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    zval *target;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();
    
    php_raylib_vector3_object *phpTarget = Z_VECTOR3_OBJ_P(target);
    
    intern->camera3d.target = phpTarget->vector3;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getUp, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getUp)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    RETURN_OBJ(&intern->up->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_setUp, 0, 0, 1)
    ZEND_ARG_INFO(0, up)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, setUp)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    zval *up;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(up)
    ZEND_PARSE_PARAMETERS_END();
    
    php_raylib_vector3_object *phpUp = Z_VECTOR3_OBJ_P(up);
    
    intern->camera3d.up = phpUp->vector3;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getFovy, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getFovy)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    RETURN_DOUBLE((double) intern->camera3d.fovy);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_setFovy, 0, 0, 1)
    ZEND_ARG_INFO(0, fovy)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, setFovy)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);
    
    double fovy;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(fovy)
    ZEND_PARSE_PARAMETERS_END();
    
    intern->camera3d.fovy = (float) fovy;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getType, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getType)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    RETURN_DOUBLE((double) intern->camera3d.type);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_setType, 0, 0, 1)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, setType)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    double type;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_DOUBLE(type)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera3d.type = (float) type;
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getMouseRay, 0, 0, 1)
    ZEND_ARG_INFO(0, mousePosition)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getMouseRay)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    zend_object *mousePosition;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJ_OF_CLASS(mousePosition, php_raylib_vector2_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpMousePosition = php_raylib_vector2_fetch_object(mousePosition);

    Ray ray = GetMouseRay(phpMousePosition->vector2, intern->camera3d);

    zend_object *rayObj = php_raylib_ray_new_ex(php_raylib_ray_ce, NULL);
    php_raylib_ray_object *phpRay = php_raylib_ray_fetch_object(rayObj);
    phpRay->ray = ray;
    phpRay->position->vector3 = ray.position;
    phpRay->direction->vector3 = ray.direction;

    RETURN_OBJ(&phpRay->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getMatrix, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getMatrix)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    Matrix matrix = GetCameraMatrix(intern->camera3d);

    zend_object *matrixObj = php_raylib_matrix_new_ex(php_raylib_matrix_ce, NULL);
    php_raylib_matrix_object *phpMatrix = php_raylib_matrix_fetch_object(matrixObj);
    phpMatrix->matrix = matrix;

    RETURN_OBJ(&phpMatrix->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getWorldToScreen, 0, 0, 1)
    ZEND_ARG_INFO(0, mousePosition)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getWorldToScreen)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    zend_object *position;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJ_OF_CLASS(position, php_raylib_vector3_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);

    Vector2 result = GetWorldToScreen(phpPosition->vector3, intern->camera3d);

    zend_object *vector2Obj = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpVector2 = php_raylib_vector2_fetch_object(vector2Obj);
    phpVector2->vector2 = result;

    RETURN_OBJ(&phpVector2->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_camera3d_getWorldToScreenEx, 0, 0, 3)
    ZEND_ARG_INFO(0, mousePosition)
ZEND_END_ARG_INFO()
PHP_METHOD(Camera3d, getWorldToScreenEx)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    zend_object *position;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJ_OF_CLASS(position, php_raylib_vector3_ce)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);

    Vector2 result = GetWorldToScreenEx(phpPosition->vector3, intern->camera3d, (int) width, (int) height);

    zend_object *vector2Obj = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpVector2 = php_raylib_vector2_fetch_object(vector2Obj);
    phpVector2->vector2 = result;

    RETURN_OBJ(&phpVector2->std);
}


const zend_function_entry php_raylib_camera3d_methods[] = {
        PHP_ME(Camera3d, __construct       , arginfo_camera3d__construct        , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getPosition       , arginfo_camera3d_getPosition       , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, setPosition       , arginfo_camera3d_setPosition       , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getTarget         , arginfo_camera3d_getTarget         , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, setTarget         , arginfo_camera3d_setTarget         , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getFovy           , arginfo_camera3d_getFovy           , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, setFovy           , arginfo_camera3d_setFovy           , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getType           , arginfo_camera3d_getType           , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, setType           , arginfo_camera3d_setType           , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getMouseRay       , arginfo_camera3d_getMouseRay       , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getMatrix         , arginfo_camera3d_getMatrix         , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getWorldToScreen  , arginfo_camera3d_getWorldToScreen  , ZEND_ACC_PUBLIC)
        PHP_ME(Camera3d, getWorldToScreenEx, arginfo_camera3d_getWorldToScreenEx, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_camera3d_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

void php_raylib_camera3d_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_camera3d_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_camera3d_object_handlers.offset = XtOffsetOf(php_raylib_camera3d_object, std);
    php_raylib_camera3d_object_handlers.free_obj = &php_raylib_camera3d_free_storage;
    php_raylib_camera3d_object_handlers.clone_obj = php_raylib_camera3d_clone;

    // Props
    php_raylib_camera3d_object_handlers.get_property_ptr_ptr = php_raylib_camera3d_get_property_ptr_ptr;
    php_raylib_camera3d_object_handlers.get_gc               = php_raylib_camera3d_get_gc;
    php_raylib_camera3d_object_handlers.get_properties       = php_raylib_camera3d_get_properties;
    php_raylib_camera3d_object_handlers.read_property	     = php_raylib_camera3d_read_property;
    php_raylib_camera3d_object_handlers.write_property       = php_raylib_camera3d_write_property;
    php_raylib_camera3d_object_handlers.has_property	     = php_raylib_camera3d_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Camera3d", php_raylib_camera3d_methods);
    php_raylib_camera3d_ce = zend_register_internal_class(&ce);
    php_raylib_camera3d_ce->create_object = php_raylib_camera3d_new;

    // Props
    zend_hash_init(&php_raylib_camera3d_prop_handlers, 0, NULL, php_raylib_camera3d_free_prop_handler, 1);
    php_raylib_camera3d_register_prop_handler(&php_raylib_camera3d_prop_handlers, "position", NULL, NULL, php_raylib_camera3d_position, php_raylib_camera3d_write_position, NULL, NULL);
    php_raylib_camera3d_register_prop_handler(&php_raylib_camera3d_prop_handlers, "target", NULL, NULL, php_raylib_camera3d_target, php_raylib_camera3d_write_target, NULL, NULL);
    php_raylib_camera3d_register_prop_handler(&php_raylib_camera3d_prop_handlers, "up", NULL, NULL, php_raylib_camera3d_up, php_raylib_camera3d_write_up, NULL, NULL);
    php_raylib_camera3d_register_prop_handler(&php_raylib_camera3d_prop_handlers, "fovy", php_raylib_camera3d_fovy, php_raylib_camera3d_write_fovy, NULL, NULL, NULL, NULL);
    php_raylib_camera3d_register_prop_handler(&php_raylib_camera3d_prop_handlers, "type", NULL, NULL, NULL, NULL, php_raylib_camera3d_type, php_raylib_camera3d_write_type);
}