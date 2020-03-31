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
#include "raylib-font.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Font PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_font_object_handlers;

static HashTable php_raylib_font_prop_handlers;

typedef double (*raylib_font_read_float_t)(php_raylib_font_object *obj);

typedef int (*raylib_font_write_float_t)(php_raylib_font_object *obj, zval *value);

typedef struct _raylib_font_prop_handler {
    raylib_font_read_float_t read_float_func;
    raylib_font_write_float_t write_float_func;
} raylib_font_prop_handler;
/* }}} */

static void php_raylib_font_register_prop_handler(HashTable *prop_handler, char *name, raylib_font_read_float_t read_float_func, raylib_font_write_float_t write_float_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_font_property_reader(php_raylib_font_object *obj, raylib_font_prop_handler *hnd, zval *rv) /* {{{ */
{
    double ret = 0;

    if (obj != NULL && hnd->read_float_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib font found");
        ret = hnd->read_float_func(obj);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }

    ZVAL_DOUBLE(rv, (double) ret);

    return rv;
}
/* }}} */

static zval *php_raylib_font_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_FONT_OBJ_P(object);

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

static zval *php_raylib_font_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_font_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_FONT_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib font hnd not found");
    }

    if (hnd != NULL) {
        retval = php_raylib_font_property_reader(obj, hnd, rv);
        if (retval == NULL) {
//            php_error_docref(NULL, E_WARNING, "Internal raylib font retval is null");
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

/* {{{ php_raylib_font_write_property(zval *object, zval *member, zval *value[, const zend_literal *key])
   Generic object property writer */
zval *php_raylib_font_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    zval tmp_member;
    php_raylib_font_object *obj;
    raylib_font_prop_handler *hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        zend_string *str = zval_try_get_string_func(member);
        if (UNEXPECTED(!str)) {
            return value;
        }
        ZVAL_STR(&tmp_member, str);
        member = &tmp_member;
    }

    obj = Z_FONT_OBJ_P(object);

    hnd = zend_hash_find_ptr(&php_raylib_font_prop_handlers, Z_STR_P(member));

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

static int php_raylib_font_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    zval tmp_member;
    raylib_font_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_FONT_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_font_property_reader(obj, hnd, &tmp)) != NULL) {
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

static HashTable *php_raylib_font_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_font_get_properties(zval *object)/* {{{ */
{
    php_raylib_font_object *obj;
    HashTable *props;
    raylib_font_prop_handler *hnd;
    zend_string *key;

    obj = Z_FONT_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_font_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_font_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_font_object *intern = php_raylib_font_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_font_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_font_object *intern;
    intern = (php_raylib_font_object*) ecalloc(1, sizeof(php_raylib_font_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_font_prop_handlers;

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_font_object_handlers;

    return &intern->std;
}

static zend_object *php_raylib_font_clone(zval *zobject)
{
    zend_object *old_object;
    zend_object *new_object;

    old_object = Z_OBJ_P(zobject);
    new_object = php_raylib_font_new(old_object->ce);

    // zend_objects_clone_members(new_object, old_object);

    php_raylib_font_object *old_font = php_raylib_font_fetch_object(old_object);
    php_raylib_font_object *new_font = php_raylib_font_fetch_object(new_object);
    new_font->font = old_font->font;

    return new_object;
}

// PHP property handling

static double php_raylib_font_x(php_raylib_font_object *obj) /* {{{ */
{
    return 0;// (double) obj->font.x;
}
/* }}} */

static double php_raylib_font_y(php_raylib_font_object *obj) /* {{{ */
{
    return 0; // (double) obj->font.y;
}
/* }}} */



static int php_raylib_font_write_x(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
//        font_object->font.x = 0;
        return ret;
    }

//    font_object->font.x = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_write_y(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
//        font_object->font.y = 0;
        return ret;
    }

//    php_error_docref(NULL, E_WARNING, "'%f': no value set", zval_get_double(newval));


//    font_object->font.y = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

/* {{{ REGISTER_RAYLIB_CHARINFO_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_FONT_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_font_ce, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling

PHP_METHOD(Font, __construct)
{
    zend_long baseSize;
    zend_long charsCount;
//    zval *texture;
//    zval *recs;
//    zval *chars;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(baseSize)
            Z_PARAM_LONG(charsCount)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);

//    intern->font = (Font) {
//            .baseSize = zend_double_2float(x),
//            .charsCount = zend_double_2float(y)
//    };

}

//PHP_METHOD(Font, getX)
//{
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->font.x);
//}

//PHP_METHOD(Font, setX)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//
//    intern->font.x = zend_double_2float(val);
//}
//
//PHP_METHOD(Font, getY)
//{
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->font.y);
//}
//
//PHP_METHOD(Font, setY)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//
//    intern->font.y = zend_double_2float(val);
//}

const zend_function_entry php_raylib_font_methods[] = {
        PHP_ME(Font, __construct, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getX, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setX, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getY, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setY, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_font_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_font_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_font_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_font_object_handlers.offset = XtOffsetOf(php_raylib_font_object, std);
    php_raylib_font_object_handlers.free_obj = &php_raylib_font_free_storage;
    php_raylib_font_object_handlers.clone_obj = php_raylib_font_clone;

    // Props
    php_raylib_font_object_handlers.get_property_ptr_ptr = php_raylib_font_get_property_ptr_ptr;
    php_raylib_font_object_handlers.get_gc               = php_raylib_font_get_gc;
    php_raylib_font_object_handlers.get_properties       = php_raylib_font_get_properties;
    php_raylib_font_object_handlers.read_property	     = php_raylib_font_read_property;
    php_raylib_font_object_handlers.write_property       = php_raylib_font_write_property;
    php_raylib_font_object_handlers.has_property	     = php_raylib_font_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Font", php_raylib_font_methods);
    php_raylib_font_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_font_ce->create_object = php_raylib_font_new;

    // Props
    zend_hash_init(&php_raylib_font_prop_handlers, 0, NULL, php_raylib_font_free_prop_handler, 1);
//    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "x", php_raylib_font_x, php_raylib_font_write_x);
//    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "y", php_raylib_font_y, php_raylib_font_write_y);


    // Types
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_DEFAULT", FONT_DEFAULT);
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_BITMAP", FONT_BITMAP);
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_SDF", FONT_SDF);
}