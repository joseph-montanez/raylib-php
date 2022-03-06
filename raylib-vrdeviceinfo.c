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


#include "raylib-vrdeviceinfo.h"

//------------------------------------------------------------------------------------------------------
//-- raylib VrDeviceInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_vrdeviceinfo_object_handlers;

static HashTable php_raylib_vrdeviceinfo_prop_handlers;

typedef zend_long (*raylib_vrdeviceinfo_read_int_t)(php_raylib_vrdeviceinfo_object *obj);
typedef int (*raylib_vrdeviceinfo_write_int_t)(php_raylib_vrdeviceinfo_object *obj,  zval *value);

typedef double (*raylib_vrdeviceinfo_read_float_t)(php_raylib_vrdeviceinfo_object *obj);
typedef int (*raylib_vrdeviceinfo_write_float_t)(php_raylib_vrdeviceinfo_object *obj,  zval *value);

typedef HashTable * (*raylib_vrdeviceinfo_read_float_array_t)(php_raylib_vrdeviceinfo_object *obj);
typedef int (*raylib_vrdeviceinfo_write_float_array_t)(php_raylib_vrdeviceinfo_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_vrdeviceinfo_update_intern(php_raylib_vrdeviceinfo_object *intern) {
}
typedef struct _raylib_vrdeviceinfo_prop_handler {
    raylib_vrdeviceinfo_read_int_t read_int_func;
    raylib_vrdeviceinfo_write_int_t write_int_func;
    raylib_vrdeviceinfo_read_float_t read_float_func;
    raylib_vrdeviceinfo_write_float_t write_float_func;
    raylib_vrdeviceinfo_read_float_array_t read_float_array_func;
    raylib_vrdeviceinfo_write_float_array_t write_float_array_func;
} raylib_vrdeviceinfo_prop_handler;

static void php_raylib_vrdeviceinfo_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_vrdeviceinfo_read_int_t read_int_func,
                                                      raylib_vrdeviceinfo_write_int_t write_int_func,
                                                      raylib_vrdeviceinfo_read_float_t read_float_func,
                                                      raylib_vrdeviceinfo_write_float_t write_float_func,
                                                      raylib_vrdeviceinfo_read_float_array_t read_float_array_func,
                                                      raylib_vrdeviceinfo_write_float_array_t write_float_array_func) /* {{{ */
{
    raylib_vrdeviceinfo_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    hnd.read_float_array_func = read_float_array_func;
    hnd.write_float_array_func = write_float_array_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_vrdeviceinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_vrdeviceinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_vrdeviceinfo_property_reader(php_raylib_vrdeviceinfo_object *obj, raylib_vrdeviceinfo_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }
    else if (obj != NULL && hnd->read_float_func) {
        ZVAL_DOUBLE(rv, hnd->read_float_func(obj));
    }
    else if (obj != NULL && hnd->read_float_array_func) {
        ZVAL_ARR(rv, hnd->read_float_array_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_vrdeviceinfo_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_vrdeviceinfo_object *obj;
    zval *retval = NULL;
    raylib_vrdeviceinfo_prop_handler *hnd = NULL;

    obj = php_raylib_vrdeviceinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_vrdeviceinfo_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_vrdeviceinfo_object *obj;
    zval *retval = NULL;
    raylib_vrdeviceinfo_prop_handler *hnd = NULL;

    obj = php_raylib_vrdeviceinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_vrdeviceinfo_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_vrdeviceinfo_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_vrdeviceinfo_object *obj;
    raylib_vrdeviceinfo_prop_handler *hnd;

    obj = php_raylib_vrdeviceinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else if (hnd && hnd->write_float_array_func) {
        hnd->write_float_array_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_vrdeviceinfo_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_vrdeviceinfo_object *obj;
    raylib_vrdeviceinfo_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_vrdeviceinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_vrdeviceinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_vrdeviceinfo_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_vrdeviceinfo_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_vrdeviceinfo_object *obj;
    HashTable *props;
    raylib_vrdeviceinfo_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_vrdeviceinfo_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_vrdeviceinfo_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_vrdeviceinfo_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_vrdeviceinfo_object *intern = php_raylib_vrdeviceinfo_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_vrdeviceinfo_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_vrdeviceinfo_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_vrdeviceinfo_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_vrdeviceinfo_object), ce);

    intern->prop_handler = &php_raylib_vrdeviceinfo_prop_handlers;

    if (orig) {
        php_raylib_vrdeviceinfo_object *other = php_raylib_vrdeviceinfo_fetch_object(orig);

        intern->vrdeviceinfo = (VrDeviceInfo) {
            .hResolution = other->vrdeviceinfo.hResolution,
            .vResolution = other->vrdeviceinfo.vResolution,
            .hScreenSize = other->vrdeviceinfo.hScreenSize,
            .vScreenSize = other->vrdeviceinfo.vScreenSize,
            .vScreenCenter = other->vrdeviceinfo.vScreenCenter,
            .eyeToScreenDistance = other->vrdeviceinfo.eyeToScreenDistance,
            .lensSeparationDistance = other->vrdeviceinfo.lensSeparationDistance,
            .interpupillaryDistance = other->vrdeviceinfo.interpupillaryDistance,
//            .lensDistortionValues = other->vrdeviceinfo.lensDistortionValues,
//            .chromaAbCorrection = other->vrdeviceinfo.chromaAbCorrection
        };
    } else {
        intern->vrdeviceinfo = (VrDeviceInfo) {
            .hResolution = 0,
            .vResolution = 0,
            .hScreenSize = 0,
            .vScreenSize = 0,
            .vScreenCenter = 0,
            .eyeToScreenDistance = 0,
            .lensSeparationDistance = 0,
            .interpupillaryDistance = 0,
            .lensDistortionValues = 0,
            .chromaAbCorrection = 0
        };
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_vrdeviceinfo_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_vrdeviceinfo_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_vrdeviceinfo_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_vrdeviceinfo_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_vrdeviceinfo_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_vrdeviceinfo__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, hResolution, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, vResolution, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, hScreenSize, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, vScreenSize, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, vScreenCenter, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, eyeToScreenDistance, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, lensSeparationDistance, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, interpupillaryDistance, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, lensDistortionValues, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, chromaAbCorrection, IS_DOUBLE, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(VrDeviceInfo, __construct)
{
}

static zend_long php_raylib_vrdeviceinfo_get_hresolution(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->vrdeviceinfo.hResolution;
}
/* }}} */

static zend_long php_raylib_vrdeviceinfo_get_vresolution(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->vrdeviceinfo.vResolution;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_hscreensize(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.hScreenSize;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_vscreensize(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.vScreenSize;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_vscreencenter(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.vScreenCenter;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_eyetoscreendistance(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.eyeToScreenDistance;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_lensseparationdistance(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.lensSeparationDistance;
}
/* }}} */

static double php_raylib_vrdeviceinfo_get_interpupillarydistance(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    return (double) obj->vrdeviceinfo.interpupillaryDistance;
}
/* }}} */

static HashTable * php_raylib_vrdeviceinfo_get_lensdistortionvalues(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_vrdeviceinfo_get_chromaabcorrection(php_raylib_vrdeviceinfo_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_hresolution(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.hResolution = 0;
        return ret;
    }

    obj->vrdeviceinfo.hResolution = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_vresolution(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.vResolution = 0;
        return ret;
    }

    obj->vrdeviceinfo.vResolution = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_hscreensize(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.hScreenSize = 0;
        return ret;
    }

    obj->vrdeviceinfo.hScreenSize = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_vscreensize(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.vScreenSize = 0;
        return ret;
    }

    obj->vrdeviceinfo.vScreenSize = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_vscreencenter(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.vScreenCenter = 0;
        return ret;
    }

    obj->vrdeviceinfo.vScreenCenter = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_eyetoscreendistance(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.eyeToScreenDistance = 0;
        return ret;
    }

    obj->vrdeviceinfo.eyeToScreenDistance = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_lensseparationdistance(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.lensSeparationDistance = 0;
        return ret;
    }

    obj->vrdeviceinfo.lensSeparationDistance = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_interpupillarydistance(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->vrdeviceinfo.interpupillaryDistance = 0;
        return ret;
    }

    obj->vrdeviceinfo.interpupillaryDistance = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_lensdistortionvalues(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_vrdeviceinfo_set_chromaabcorrection(php_raylib_vrdeviceinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_vrdeviceinfo_methods[] = {
        PHP_ME(VrDeviceInfo, __construct, arginfo_vrdeviceinfo__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_vrdeviceinfo_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_vrdeviceinfo_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_vrdeviceinfo_object_handlers.offset = XtOffsetOf(php_raylib_vrdeviceinfo_object, std);
    php_raylib_vrdeviceinfo_object_handlers.free_obj = &php_raylib_vrdeviceinfo_free_storage;
    php_raylib_vrdeviceinfo_object_handlers.clone_obj = php_raylib_vrdeviceinfo_clone;

    // Props
    php_raylib_vrdeviceinfo_object_handlers.get_property_ptr_ptr = php_raylib_vrdeviceinfo_get_property_ptr_ptr;
    php_raylib_vrdeviceinfo_object_handlers.get_gc               = php_raylib_vrdeviceinfo_get_gc;
    php_raylib_vrdeviceinfo_object_handlers.get_properties       = php_raylib_vrdeviceinfo_get_properties;
    php_raylib_vrdeviceinfo_object_handlers.read_property	     = php_raylib_vrdeviceinfo_read_property;
    php_raylib_vrdeviceinfo_object_handlers.write_property       = php_raylib_vrdeviceinfo_write_property;
    php_raylib_vrdeviceinfo_object_handlers.has_property	     = php_raylib_vrdeviceinfo_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "VrDeviceInfo", php_raylib_vrdeviceinfo_methods);
    php_raylib_vrdeviceinfo_ce = zend_register_internal_class(&ce);
    php_raylib_vrdeviceinfo_ce->create_object = php_raylib_vrdeviceinfo_new;

    // Props
    zend_hash_init(&php_raylib_vrdeviceinfo_prop_handlers, 0, NULL, php_raylib_vrdeviceinfo_free_prop_handler, 1);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "hresolution", php_raylib_vrdeviceinfo_get_hresolution, php_raylib_vrdeviceinfo_set_hresolution, NULL, NULL, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "vresolution", php_raylib_vrdeviceinfo_get_vresolution, php_raylib_vrdeviceinfo_set_vresolution, NULL, NULL, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "hscreensize", NULL, NULL, php_raylib_vrdeviceinfo_get_hscreensize, php_raylib_vrdeviceinfo_set_hscreensize, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "vscreensize", NULL, NULL, php_raylib_vrdeviceinfo_get_vscreensize, php_raylib_vrdeviceinfo_set_vscreensize, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "vscreencenter", NULL, NULL, php_raylib_vrdeviceinfo_get_vscreencenter, php_raylib_vrdeviceinfo_set_vscreencenter, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "eyetoscreendistance", NULL, NULL, php_raylib_vrdeviceinfo_get_eyetoscreendistance, php_raylib_vrdeviceinfo_set_eyetoscreendistance, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "lensseparationdistance", NULL, NULL, php_raylib_vrdeviceinfo_get_lensseparationdistance, php_raylib_vrdeviceinfo_set_lensseparationdistance, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "interpupillarydistance", NULL, NULL, php_raylib_vrdeviceinfo_get_interpupillarydistance, php_raylib_vrdeviceinfo_set_interpupillarydistance, NULL, NULL);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "lensdistortionvalues", NULL, NULL, NULL, NULL, php_raylib_vrdeviceinfo_get_lensdistortionvalues, php_raylib_vrdeviceinfo_set_lensdistortionvalues);
    php_raylib_vrdeviceinfo_register_prop_handler(&php_raylib_vrdeviceinfo_prop_handlers, "chromaabcorrection", NULL, NULL, NULL, NULL, php_raylib_vrdeviceinfo_get_chromaabcorrection, php_raylib_vrdeviceinfo_set_chromaabcorrection);
}
