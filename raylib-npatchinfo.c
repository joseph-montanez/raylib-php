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
#include "raylib-rectangle.h"
#include "raylib-npatchinfo.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib NPatchInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_npatchinfo_object_handlers;

static HashTable php_raylib_npatchinfo_prop_handlers;

typedef zend_long (*raylib_npatchinfo_read_int_t)(php_raylib_npatchinfo_object *obj);

typedef int (*raylib_npatchinfo_write_int_t)(php_raylib_npatchinfo_object *obj, zval *value);

typedef zval* (*raylib_npatchinfo_read_rectangle_object_t)(php_raylib_npatchinfo_object *obj);

typedef int (*raylib_npatchinfo_write_rectangle_object_t)(php_raylib_npatchinfo_object *obj, zval *value);

typedef struct _raylib_npatchinfo_prop_handler {
    raylib_npatchinfo_read_int_t read_int_func;
    raylib_npatchinfo_write_int_t write_int_func;
    raylib_npatchinfo_read_rectangle_object_t read_rectangle_func;
    raylib_npatchinfo_write_rectangle_object_t write_retangle_func;
} raylib_npatchinfo_prop_handler;
/* }}} */

static void php_raylib_npatchinfo_register_prop_handler(HashTable *prop_handler, char *name, raylib_npatchinfo_read_int_t read_int_func, raylib_npatchinfo_write_int_t write_int_func) /* {{{ */
{
    raylib_npatchinfo_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_rectangle_func = NULL;
    hnd.write_retangle_func = NULL;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_npatchinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_npatchinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}

static void php_raylib_npatchinfo_register_prop_handler_rectangle(HashTable *prop_handler, char *name, raylib_npatchinfo_read_rectangle_object_t read_rectangle_func, raylib_npatchinfo_write_rectangle_object_t write_retangle_func) /* {{{ */
{
    raylib_npatchinfo_prop_handler hnd;

    hnd.read_int_func = NULL;
    hnd.write_int_func = NULL;
    hnd.read_rectangle_func = read_rectangle_func;
    hnd.write_retangle_func = write_retangle_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_npatchinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_npatchinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_npatchinfo_property_reader(php_raylib_npatchinfo_object *obj, raylib_npatchinfo_prop_handler *hnd, zval *rv) /* {{{ */
{

    if (obj != NULL && hnd->read_int_func) {
        zend_long ret = 0;
        ret = hnd->read_int_func(obj);
        ZVAL_LONG(rv, (zend_long) ret);
    }
    if (obj != NULL && hnd->read_rectangle_func) {
        zval *ret;
        ret = hnd->read_rectangle_func(obj);

        php_raylib_rectangle_object *result = Z_RECTANGLE_OBJ_P(ret);
        ZVAL_OBJ(rv, &result->std);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }


    return rv;
}
/* }}} */

static zval *php_raylib_npatchinfo_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_npatchinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_NPATCHINFO_OBJ_P(object);

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

static zval *php_raylib_npatchinfo_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_npatchinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_NPATCHINFO_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib npatchinfo hnd not found");
    }

    if (hnd != NULL) {
        retval = php_raylib_npatchinfo_property_reader(obj, hnd, rv);
        if (retval == NULL) {
//            php_error_docref(NULL, E_WARNING, "Internal raylib npatchinfo retval is null");
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

/* {{{ php_raylib_npatchinfo_write_property(zval *object, zval *member, zval *value[, const zend_literal *key])
   Generic object property writer */
zval *php_raylib_npatchinfo_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    zval tmp_member;
    php_raylib_npatchinfo_object *obj;
    raylib_npatchinfo_prop_handler *hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        zend_string *str = zval_try_get_string_func(member);
        if (UNEXPECTED(!str)) {
            return value;
        }
        ZVAL_STR(&tmp_member, str);
        member = &tmp_member;
    }

    obj = Z_NPATCHINFO_OBJ_P(object);

    hnd = zend_hash_find_ptr(&php_raylib_npatchinfo_prop_handlers, Z_STR_P(member));

    if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    if (member == &tmp_member) {
        zval_ptr_dtor(member);
    }

    return value;
}
/* }}} */

static int php_raylib_npatchinfo_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    zval tmp_member;
    raylib_npatchinfo_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_NPATCHINFO_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_npatchinfo_property_reader(obj, hnd, &tmp)) != NULL) {
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

static HashTable *php_raylib_npatchinfo_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_npatchinfo_get_properties(zval *object)/* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    HashTable *props;
    raylib_npatchinfo_prop_handler *hnd;
    zend_string *key;

    obj = Z_NPATCHINFO_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_npatchinfo_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_npatchinfo_free_storage(zend_object *object)
{
    php_raylib_npatchinfo_object *intern = php_raylib_npatchinfo_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_npatchinfo_new(zend_class_entry *ce)
{
    php_raylib_npatchinfo_object *intern;
    intern = (php_raylib_npatchinfo_object*) ecalloc(1, sizeof(php_raylib_npatchinfo_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_npatchinfo_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_npatchinfo_object_handlers;

    return &intern->std;
}

static zend_object * php_raylib_npatchinfo_clone(zval *zobject)
{
    zend_object *old_object;
    zend_object *new_object;

    old_object = Z_OBJ_P(zobject);
    new_object = php_raylib_npatchinfo_new(old_object->ce);

    // zend_objects_clone_members(new_object, old_object);

    php_raylib_npatchinfo_object *old_npatchinfo = php_raylib_npatchinfo_fetch_object(old_object);
    php_raylib_npatchinfo_object *new_npatchinfo = php_raylib_npatchinfo_fetch_object(new_object);
    new_npatchinfo->npatchinfo = old_npatchinfo->npatchinfo;

    return new_object;
}

// PHP property handling

static zval * php_raylib_npatchinfo_source_rec(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    zval *sourceRec = malloc(sizeof(zval));
    object_init_ex(sourceRec, php_raylib_rectangle_ce);

    php_raylib_rectangle_object *result = Z_RECTANGLE_OBJ_P(sourceRec);
    result->rectangle = obj->npatchinfo.source;

    return sourceRec;
}
/* }}} */

static zend_long php_raylib_npatchinfo_left(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.left;
}

static zend_long php_raylib_npatchinfo_top(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.top;
}

static zend_long php_raylib_npatchinfo_right(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.right;
}

static zend_long php_raylib_npatchinfo_bottom(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.bottom;
}

static zend_long php_raylib_npatchinfo_type(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.type;
}
/* }}} */



static int php_raylib_npatchinfo_write_source_rec(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_rectangle_object *phpSourceRec = Z_RECTANGLE_OBJ_P(newval);

    npatchinfo_object->npatchinfo.source = phpSourceRec->rectangle;

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_write_left(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        npatchinfo_object->npatchinfo.left = 0;
        return ret;
    }

    npatchinfo_object->npatchinfo.left = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_npatchinfo_write_top(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        npatchinfo_object->npatchinfo.top = 0;
        return ret;
    }

    npatchinfo_object->npatchinfo.top = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_npatchinfo_write_right(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        npatchinfo_object->npatchinfo.right = 0;
        return ret;
    }

    npatchinfo_object->npatchinfo.right = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_npatchinfo_write_bottom(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        npatchinfo_object->npatchinfo.bottom = 0;
        return ret;
    }

    npatchinfo_object->npatchinfo.bottom = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_npatchinfo_write_type(php_raylib_npatchinfo_object *npatchinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        npatchinfo_object->npatchinfo.type = 0;
        return ret;
    }

    npatchinfo_object->npatchinfo.type = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

// PHP object handling

PHP_METHOD(NPatchInfo, __construct)
{
    zval *sourceRec;
    zend_long left, top, right, bottom, type;

    ZEND_PARSE_PARAMETERS_START(6, 6)
            Z_PARAM_ZVAL(sourceRec)
            Z_PARAM_LONG(left)
            Z_PARAM_LONG(top)
            Z_PARAM_LONG(right)
            Z_PARAM_LONG(bottom)
            Z_PARAM_LONG(type)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpSourceRec = Z_RECTANGLE_OBJ_P(sourceRec);
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo = (NPatchInfo) {
            .source = phpSourceRec->rectangle,
            .left = (int) left,
            .top = (int) top,
            .right = (int) right,
            .bottom = (int) bottom,
            .type = (int) type,
    };

}

PHP_METHOD(NPatchInfo, getLeft)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->npatchinfo.left);
}

PHP_METHOD(NPatchInfo, setLeft)
{
    zend_long left;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(left)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.left = (int) left;
}

PHP_METHOD(NPatchInfo, getTop)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->npatchinfo.top);
}

PHP_METHOD(NPatchInfo, setTop)
{
    zend_long top;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(top)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.top = (int) top;
}

PHP_METHOD(NPatchInfo, getRight)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->npatchinfo.right);
}

PHP_METHOD(NPatchInfo, setRight)
{
    zend_long right;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(right)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.right = (int) right;
}

PHP_METHOD(NPatchInfo, getBottom)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->npatchinfo.bottom);
}

PHP_METHOD(NPatchInfo, setBottom)
{
    zend_long bottom;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(bottom)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.bottom = (int) bottom;
}

PHP_METHOD(NPatchInfo, getType)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->npatchinfo.type);
}

PHP_METHOD(NPatchInfo, setType)
{
    zend_long type;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(type)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.left = (int) type;
}

PHP_METHOD(NPatchInfo, getSourceRec)
{
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_rectangle_ce);
    
    php_raylib_rectangle_object *result = Z_RECTANGLE_OBJ_P(obj);
    result->rectangle = intern->npatchinfo.source;

    RETURN_OBJ(&result->std);
}

PHP_METHOD(NPatchInfo, setSourceRec)
{
    zval *sourceRec;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(sourceRec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpSourceRec = Z_RECTANGLE_OBJ_P(sourceRec);
    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    intern->npatchinfo.source = phpSourceRec->rectangle;
}


const zend_function_entry php_raylib_npatchinfo_methods[] = {
        PHP_ME(NPatchInfo, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getLeft, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setLeft, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getTop, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setTop, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getRight, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setRight, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getBottom, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setBottom, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getType, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setType, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, getSourceRec, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(NPatchInfo, setSourceRec, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_npatchinfo_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

/* {{{ REGISTER_RAYLIB_NPATCHINFO_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_NPATCHINFO_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_npatchinfo_ce, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */
// Extension class startup

void php_raylib_npatchinfo_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_npatchinfo_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_npatchinfo_object_handlers.offset    = XtOffsetOf(php_raylib_npatchinfo_object, std);
    php_raylib_npatchinfo_object_handlers.free_obj  = &php_raylib_npatchinfo_free_storage;
    php_raylib_npatchinfo_object_handlers.clone_obj = php_raylib_npatchinfo_clone;

    // Props
    php_raylib_npatchinfo_object_handlers.get_property_ptr_ptr = php_raylib_npatchinfo_get_property_ptr_ptr;
    php_raylib_npatchinfo_object_handlers.get_gc               = php_raylib_npatchinfo_get_gc;
    php_raylib_npatchinfo_object_handlers.get_properties       = php_raylib_npatchinfo_get_properties;
    php_raylib_npatchinfo_object_handlers.read_property	       = php_raylib_npatchinfo_read_property;
    php_raylib_npatchinfo_object_handlers.write_property       = php_raylib_npatchinfo_write_property;
    php_raylib_npatchinfo_object_handlers.has_property	       = php_raylib_npatchinfo_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "NPatchInfo", php_raylib_npatchinfo_methods);
    php_raylib_npatchinfo_ce = zend_register_internal_class(&ce);
    php_raylib_npatchinfo_ce->create_object = php_raylib_npatchinfo_new;

    // Props
    zend_hash_init(&php_raylib_npatchinfo_prop_handlers, 0, NULL, php_raylib_npatchinfo_free_prop_handler, 1);
    php_raylib_npatchinfo_register_prop_handler_rectangle(&php_raylib_npatchinfo_prop_handlers, "sourceRec", php_raylib_npatchinfo_source_rec, php_raylib_npatchinfo_write_source_rec);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "left", php_raylib_npatchinfo_left, php_raylib_npatchinfo_write_left);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "top", php_raylib_npatchinfo_top, php_raylib_npatchinfo_write_top);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "right", php_raylib_npatchinfo_right, php_raylib_npatchinfo_write_right);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "bottom", php_raylib_npatchinfo_bottom, php_raylib_npatchinfo_write_bottom);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "type", php_raylib_npatchinfo_type, php_raylib_npatchinfo_write_type);

    // Types
    REGISTER_RAYLIB_NPATCHINFO_CLASS_CONST_LONG("NPT_9PATCH", NPT_9PATCH);
    REGISTER_RAYLIB_NPATCHINFO_CLASS_CONST_LONG("NPT_3PATCH_VERTICAL", NPT_3PATCH_VERTICAL);
    REGISTER_RAYLIB_NPATCHINFO_CLASS_CONST_LONG("NPT_3PATCH_HORIZONTAL", NPT_3PATCH_HORIZONTAL);
}