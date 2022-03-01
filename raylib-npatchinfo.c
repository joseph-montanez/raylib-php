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

#include "raylib-rectangle.h"

#include "raylib-npatchinfo.h"

//------------------------------------------------------------------------------------------------------
//-- raylib NPatchInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_npatchinfo_object_handlers;

static HashTable php_raylib_npatchinfo_prop_handlers;

typedef zend_object * (*raylib_npatchinfo_read_rectangle_t)(php_raylib_npatchinfo_object *obj);
typedef int (*raylib_npatchinfo_write_rectangle_t)(php_raylib_npatchinfo_object *obj,  zval *value);

typedef zend_long (*raylib_npatchinfo_read_int_t)(php_raylib_npatchinfo_object *obj);
typedef int (*raylib_npatchinfo_write_int_t)(php_raylib_npatchinfo_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
static void php_raylib_npatchinfo_update_intern(php_raylib_npatchinfo_object *intern) {
    intern->npatchinfo.source = intern->source->rectangle;
}
typedef struct _raylib_npatchinfo_prop_handler {
    raylib_npatchinfo_read_rectangle_t read_rectangle_func;
    raylib_npatchinfo_write_rectangle_t write_rectangle_func;
    raylib_npatchinfo_read_int_t read_int_func;
    raylib_npatchinfo_write_int_t write_int_func;
} raylib_npatchinfo_prop_handler;

static void php_raylib_npatchinfo_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_npatchinfo_read_rectangle_t read_rectangle_func,
                                                      raylib_npatchinfo_write_rectangle_t write_rectangle_func,
                                                      raylib_npatchinfo_read_int_t read_int_func,
                                                      raylib_npatchinfo_write_int_t write_int_func) /* {{{ */
{
    raylib_npatchinfo_prop_handler hnd;

    hnd.read_rectangle_func = read_rectangle_func;
    hnd.write_rectangle_func = write_rectangle_func;
    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_npatchinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_npatchinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_npatchinfo_property_reader(php_raylib_npatchinfo_object *obj, raylib_npatchinfo_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_rectangle_func) {
        zend_object *ret = hnd->read_rectangle_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_npatchinfo_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    zval *retval = NULL;
    raylib_npatchinfo_prop_handler *hnd = NULL;

    obj = php_raylib_npatchinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_npatchinfo_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    zval *retval = NULL;
    raylib_npatchinfo_prop_handler *hnd = NULL;

    obj = php_raylib_npatchinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_npatchinfo_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_npatchinfo_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    raylib_npatchinfo_prop_handler *hnd;

    obj = php_raylib_npatchinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_rectangle_func) {
        hnd->write_rectangle_func(obj, value);
    } else if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_npatchinfo_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    raylib_npatchinfo_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_npatchinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_npatchinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_npatchinfo_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_npatchinfo_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_npatchinfo_object *obj;
    HashTable *props;
    raylib_npatchinfo_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_npatchinfo_fetch_object(object);
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

void php_raylib_npatchinfo_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_npatchinfo_object *intern = php_raylib_npatchinfo_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_npatchinfo_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_npatchinfo_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_npatchinfo_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_npatchinfo_object), ce);

    intern->prop_handler = &php_raylib_npatchinfo_prop_handlers;

    if (orig) {
        php_raylib_npatchinfo_object *other = php_raylib_npatchinfo_fetch_object(orig);

        zend_object *source = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, &other->source->std);

        php_raylib_rectangle_object *phpSource = php_raylib_rectangle_fetch_object(source);

        intern->npatchinfo = (NPatchInfo) {
            .source = (Rectangle) {
                .x = other->npatchinfo.source.x,
                .y = other->npatchinfo.source.y,
                .width = other->npatchinfo.source.width,
                .height = other->npatchinfo.source.height
            },
            .left = other->npatchinfo.left,
            .top = other->npatchinfo.top,
            .right = other->npatchinfo.right,
            .bottom = other->npatchinfo.bottom,
            .layout = other->npatchinfo.layout
        };

        intern->source = phpSource;
    } else {
        zend_object *source = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);

        php_raylib_rectangle_object *phpSource = php_raylib_rectangle_fetch_object(source);

        intern->npatchinfo = (NPatchInfo) {
            .source = (Rectangle) {
                .x = 0,
                .y = 0,
                .width = 0,
                .height = 0
            },
            .left = 0,
            .top = 0,
            .right = 0,
            .bottom = 0,
            .layout = 0
        };
        intern->source = phpSource;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_npatchinfo_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_npatchinfo_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_npatchinfo_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_npatchinfo_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_npatchinfo_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

static zend_object * php_raylib_npatchinfo_get_source(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->source->std);
    return &obj->source->std;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_left(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.left;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_top(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.top;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_right(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.right;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_bottom(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.bottom;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_layout(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo.layout;
}
/* }}} */

static int php_raylib_npatchinfo_set_source(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(newval);
//    obj->source = phpSource;

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_left(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo.left = 0;
        return ret;
    }

    obj->npatchinfo.left = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_top(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo.top = 0;
        return ret;
    }

    obj->npatchinfo.top = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_right(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo.right = 0;
        return ret;
    }

    obj->npatchinfo.right = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_bottom(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo.bottom = 0;
        return ret;
    }

    obj->npatchinfo.bottom = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_layout(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo.layout = 0;
        return ret;
    }

    obj->npatchinfo.layout = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_npatchinfo_methods[] = {
        PHP_FE_END
};
void php_raylib_npatchinfo_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_npatchinfo_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_npatchinfo_object_handlers.offset = XtOffsetOf(php_raylib_npatchinfo_object, std);
    php_raylib_npatchinfo_object_handlers.free_obj = &php_raylib_npatchinfo_free_storage;
    php_raylib_npatchinfo_object_handlers.clone_obj = php_raylib_npatchinfo_clone;

    // Props
    php_raylib_npatchinfo_object_handlers.get_property_ptr_ptr = php_raylib_npatchinfo_get_property_ptr_ptr;
    php_raylib_npatchinfo_object_handlers.get_gc               = php_raylib_npatchinfo_get_gc;
    php_raylib_npatchinfo_object_handlers.get_properties       = php_raylib_npatchinfo_get_properties;
    php_raylib_npatchinfo_object_handlers.read_property	     = php_raylib_npatchinfo_read_property;
    php_raylib_npatchinfo_object_handlers.write_property       = php_raylib_npatchinfo_write_property;
    php_raylib_npatchinfo_object_handlers.has_property	     = php_raylib_npatchinfo_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "npatchinfo", php_raylib_npatchinfo_methods);
    php_raylib_npatchinfo_ce = zend_register_internal_class(&ce);
    php_raylib_npatchinfo_ce->create_object = php_raylib_npatchinfo_new;

    // Props
    zend_hash_init(&php_raylib_npatchinfo_prop_handlers, 0, NULL, php_raylib_npatchinfo_free_prop_handler, 1);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "source", php_raylib_npatchinfo_get_source, php_raylib_npatchinfo_set_source, NULL, NULL);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "left", NULL, NULL, php_raylib_npatchinfo_get_left, php_raylib_npatchinfo_set_left);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "top", NULL, NULL, php_raylib_npatchinfo_get_top, php_raylib_npatchinfo_set_top);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "right", NULL, NULL, php_raylib_npatchinfo_get_right, php_raylib_npatchinfo_set_right);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "bottom", NULL, NULL, php_raylib_npatchinfo_get_bottom, php_raylib_npatchinfo_set_bottom);
    php_raylib_npatchinfo_register_prop_handler(&php_raylib_npatchinfo_prop_handlers, "layout", NULL, NULL, php_raylib_npatchinfo_get_layout, php_raylib_npatchinfo_set_layout);
}
