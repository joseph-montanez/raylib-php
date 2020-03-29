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
#include "raylib-image.h"
#include "raylib-charinfo.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib CharInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_charinfo_object_handlers;

static HashTable php_raylib_charinfo_prop_handlers;

typedef double (*raylib_charinfo_read_float_t)(php_raylib_charinfo_object *obj);

typedef int (*raylib_charinfo_write_float_t)(php_raylib_charinfo_object *obj, zval *value);

typedef struct _raylib_charinfo_prop_handler {
    raylib_charinfo_read_float_t read_float_func;
    raylib_charinfo_write_float_t write_float_func;
} raylib_charinfo_prop_handler;
/* }}} */

static void php_raylib_charinfo_register_prop_handler(HashTable *prop_handler, char *name, raylib_charinfo_read_float_t read_float_func, raylib_charinfo_write_float_t write_float_func) /* {{{ */
{
    raylib_charinfo_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_charinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_charinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_charinfo_property_reader(php_raylib_charinfo_object *obj, raylib_charinfo_prop_handler *hnd, zval *rv) /* {{{ */
{
    double ret = 0;

    if (obj != NULL && hnd->read_float_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib charinfo found");
        ret = hnd->read_float_func(obj);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }

    ZVAL_DOUBLE(rv, (double) ret);

    return rv;
}
/* }}} */

static zval *php_raylib_charinfo_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_charinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_CHARINFO_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd == NULL) {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_charinfo_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_charinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_CHARINFO_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib charinfo hnd not found");
    }

    if (hnd != NULL) {
        retval = php_raylib_charinfo_property_reader(obj, hnd, rv);
        if (retval == NULL) {
//            php_error_docref(NULL, E_WARNING, "Internal raylib charinfo retval is null");
            retval = &EG(uninitialized_zval);
        }
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_charinfo_write_property(zval *object, zval *member, zval *value[, const zend_literal *key])
   Generic object property writer */
zval *php_raylib_charinfo_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    zval tmp_member;
    php_raylib_charinfo_object *obj;
    raylib_charinfo_prop_handler *hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        zend_string *str = zval_try_get_string_func(member);
        if (UNEXPECTED(!str)) {
            return value;
        }
        ZVAL_STR(&tmp_member, str);
        member = &tmp_member;
    }

    obj = Z_CHARINFO_OBJ_P(object);

    hnd = zend_hash_find_ptr(&php_raylib_charinfo_prop_handlers, Z_STR_P(member));

    if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    if (member == &tmp_member) {
        zval_ptr_dtor(member);
    }

    return value;
}
/* }}} */

static int php_raylib_charinfo_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    zval tmp_member;
    raylib_charinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_CHARINFO_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_charinfo_property_reader(obj, hnd, &tmp)) != NULL) {
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

static HashTable *php_raylib_charinfo_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_charinfo_get_properties(zval *object)/* {{{ */
{
    php_raylib_charinfo_object *obj;
    HashTable *props;
    raylib_charinfo_prop_handler *hnd;
    zend_string *key;

    obj = Z_CHARINFO_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_charinfo_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_charinfo_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_charinfo_object *intern = php_raylib_charinfo_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_charinfo_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_charinfo_object *intern;
    intern = (php_raylib_charinfo_object*) ecalloc(1, sizeof(php_raylib_charinfo_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_charinfo_prop_handlers;

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_charinfo_object_handlers;

    return &intern->std;
}

static zend_object *php_raylib_charinfo_clone(zval *zobject)
{
    zend_object *old_object;
    zend_object *new_object;

    old_object = Z_OBJ_P(zobject);
    new_object = php_raylib_charinfo_new(old_object->ce);

    // zend_objects_clone_members(new_object, old_object);

    php_raylib_charinfo_object *old_charinfo = php_raylib_charinfo_fetch_object(old_object);
    php_raylib_charinfo_object *new_charinfo = php_raylib_charinfo_fetch_object(new_object);
    new_charinfo->charinfo = old_charinfo->charinfo;

    return new_object;
}

// PHP property handling

static double php_raylib_charinfo_x(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (double) 0; //obj->charinfo.value;
}
/* }}} */

static double php_raylib_charinfo_y(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (double) 0; // obj->charinfo.offsetX;
}
/* }}} */



static int php_raylib_charinfo_write_x(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        //charinfo_object->charinfo.x = 0;
        return ret;
    }

    //charinfo_object->charinfo.x = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_charinfo_write_y(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        //charinfo_object->charinfo.y = 0;
        return ret;
    }

//    php_error_docref(NULL, E_WARNING, "'%f': no value set", zval_get_double(newval));


    //charinfo_object->charinfo.y = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

// PHP object handling

PHP_METHOD(CharInfo, __construct)
{
    zend_long value, offsetX, offsetY, advanceX;
    zval *image;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(value)
            Z_PARAM_LONG(offsetX)
            Z_PARAM_LONG(offsetY)
            Z_PARAM_LONG(advanceX)
            Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(ZEND_THIS);

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo = (CharInfo) {
            .value = (int) value,
            .offsetX = (int) offsetX,
            .offsetY = (int) offsetY,
            .advanceX = (int) advanceX,
            .image = phpImage->image,
    };

}

//PHP_METHOD(CharInfo, getX)
//{
//    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->charinfo.x);
//}
//
//PHP_METHOD(CharInfo, setX)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
//
//    intern->charinfo.x = zend_double_2float(val);
//}
//
//PHP_METHOD(CharInfo, getY)
//{
//    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->charinfo.y);
//}
//
//PHP_METHOD(CharInfo, setY)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
//
//    intern->charinfo.y = zend_double_2float(val);
//}

const zend_function_entry php_raylib_charinfo_methods[] = {
        PHP_ME(CharInfo, __construct, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(CharInfo, getX, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(CharInfo, setX, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(CharInfo, getY, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(CharInfo, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_charinfo_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_charinfo_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_charinfo_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_charinfo_object_handlers.offset = XtOffsetOf(php_raylib_charinfo_object, std);
    php_raylib_charinfo_object_handlers.free_obj = &php_raylib_charinfo_free_storage;
    php_raylib_charinfo_object_handlers.clone_obj = php_raylib_charinfo_clone;

    // Props
    php_raylib_charinfo_object_handlers.get_property_ptr_ptr = php_raylib_charinfo_get_property_ptr_ptr;
    php_raylib_charinfo_object_handlers.get_gc               = php_raylib_charinfo_get_gc;
    php_raylib_charinfo_object_handlers.get_properties       = php_raylib_charinfo_get_properties;
    php_raylib_charinfo_object_handlers.read_property	    = php_raylib_charinfo_read_property;
    php_raylib_charinfo_object_handlers.write_property       = php_raylib_charinfo_write_property;
    php_raylib_charinfo_object_handlers.has_property	        = php_raylib_charinfo_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "CharInfo", php_raylib_charinfo_methods);
    php_raylib_charinfo_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_charinfo_ce->create_object = php_raylib_charinfo_new;

    // Props
    zend_hash_init(&php_raylib_charinfo_prop_handlers, 0, NULL, php_raylib_charinfo_free_prop_handler, 1);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "x", php_raylib_charinfo_x, php_raylib_charinfo_write_x);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "y", php_raylib_charinfo_y, php_raylib_charinfo_write_y);
}