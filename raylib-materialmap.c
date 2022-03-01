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

#include "raylib-texture.h"
#include "raylib-color.h"

#include "raylib-materialmap.h"

//------------------------------------------------------------------------------------------------------
//-- raylib MaterialMap PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_materialmap_object_handlers;

static HashTable php_raylib_materialmap_prop_handlers;

typedef zend_object * (*raylib_materialmap_read_texture_t)(php_raylib_materialmap_object *obj);
typedef int (*raylib_materialmap_write_texture_t)(php_raylib_materialmap_object *obj,  zval *value);

typedef zend_object * (*raylib_materialmap_read_color_t)(php_raylib_materialmap_object *obj);
typedef int (*raylib_materialmap_write_color_t)(php_raylib_materialmap_object *obj,  zval *value);

typedef double (*raylib_materialmap_read_float_t)(php_raylib_materialmap_object *obj);
typedef int (*raylib_materialmap_write_float_t)(php_raylib_materialmap_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
static void php_raylib_materialmap_update_intern(php_raylib_materialmap_object *intern) {
    intern->materialmap.texture = intern->texture->texture;
    intern->materialmap.color = intern->color->color;
}
typedef struct _raylib_materialmap_prop_handler {
    raylib_materialmap_read_texture_t read_texture_func;
    raylib_materialmap_write_texture_t write_texture_func;
    raylib_materialmap_read_color_t read_color_func;
    raylib_materialmap_write_color_t write_color_func;
    raylib_materialmap_read_float_t read_float_func;
    raylib_materialmap_write_float_t write_float_func;
} raylib_materialmap_prop_handler;

static void php_raylib_materialmap_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_materialmap_read_texture_t read_texture_func,
                                                      raylib_materialmap_write_texture_t write_texture_func,
                                                      raylib_materialmap_read_color_t read_color_func,
                                                      raylib_materialmap_write_color_t write_color_func,
                                                      raylib_materialmap_read_float_t read_float_func,
                                                      raylib_materialmap_write_float_t write_float_func) /* {{{ */
{
    raylib_materialmap_prop_handler hnd;

    hnd.read_texture_func = read_texture_func;
    hnd.write_texture_func = write_texture_func;
    hnd.read_color_func = read_color_func;
    hnd.write_color_func = write_color_func;
    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_materialmap_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_materialmap_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_materialmap_property_reader(php_raylib_materialmap_object *obj, raylib_materialmap_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_texture_func) {
        zend_object *ret = hnd->read_texture_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_color_func) {
        zend_object *ret = hnd->read_color_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_float_func) {
        ZVAL_DOUBLE(rv, hnd->read_float_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_materialmap_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_materialmap_object *obj;
    zval *retval = NULL;
    raylib_materialmap_prop_handler *hnd = NULL;

    obj = php_raylib_materialmap_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_materialmap_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_materialmap_object *obj;
    zval *retval = NULL;
    raylib_materialmap_prop_handler *hnd = NULL;

    obj = php_raylib_materialmap_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_materialmap_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_materialmap_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_materialmap_object *obj;
    raylib_materialmap_prop_handler *hnd;

    obj = php_raylib_materialmap_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_texture_func) {
        hnd->write_texture_func(obj, value);
    } else if (hnd && hnd->write_color_func) {
        hnd->write_color_func(obj, value);
    } else if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_materialmap_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_materialmap_object *obj;
    raylib_materialmap_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_materialmap_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_materialmap_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_materialmap_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_materialmap_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_materialmap_object *obj;
    HashTable *props;
    raylib_materialmap_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_materialmap_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_materialmap_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_materialmap_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_materialmap_object *intern = php_raylib_materialmap_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_materialmap_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_materialmap_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_materialmap_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_materialmap_object), ce);

    intern->prop_handler = &php_raylib_materialmap_prop_handlers;

    if (orig) {
        php_raylib_materialmap_object *other = php_raylib_materialmap_fetch_object(orig);

        zend_object *texture = php_raylib_texture_new_ex(php_raylib_texture_ce, &other->texture->std);
        zend_object *color = php_raylib_color_new_ex(php_raylib_color_ce, &other->color->std);

        php_raylib_texture_object *phpTexture = php_raylib_texture_fetch_object(texture);
        php_raylib_color_object *phpColor = php_raylib_color_fetch_object(color);

        intern->materialmap = (MaterialMap) {
            .texture = (Texture) {
                .id = other->materialmap.texture.id,
                .width = other->materialmap.texture.width,
                .height = other->materialmap.texture.height,
                .mipmaps = other->materialmap.texture.mipmaps,
                .format = other->materialmap.texture.format
            },
            .color = (Color) {
                .r = other->materialmap.color.r,
                .g = other->materialmap.color.g,
                .b = other->materialmap.color.b,
                .a = other->materialmap.color.a
            },
            .value = other->materialmap.value
        };

        intern->texture = phpTexture;
        intern->color = phpColor;
    } else {
        zend_object *texture = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
        zend_object *color = php_raylib_color_new_ex(php_raylib_color_ce, NULL);

        php_raylib_texture_object *phpTexture = php_raylib_texture_fetch_object(texture);
        php_raylib_color_object *phpColor = php_raylib_color_fetch_object(color);

        intern->materialmap = (MaterialMap) {
            .texture = (Texture) {
                .id = 0,
                .width = 0,
                .height = 0,
                .mipmaps = 0,
                .format = 0
            },
            .color = (Color) {
                .r = 0,
                .g = 0,
                .b = 0,
                .a = 0
            },
            .value = 0
        };
        intern->texture = phpTexture;
        intern->color = phpColor;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_materialmap_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_materialmap_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_materialmap_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_materialmap_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_materialmap_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

static zend_object * php_raylib_materialmap_get_texture(php_raylib_materialmap_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->texture->std);
    return &obj->texture->std;
}
/* }}} */

static zend_object * php_raylib_materialmap_get_color(php_raylib_materialmap_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->color->std);
    return &obj->color->std;
}
/* }}} */

static double php_raylib_materialmap_get_value(php_raylib_materialmap_object *obj) /* {{{ */
{
    return (double) obj->materialmap.value;
}
/* }}} */

static int php_raylib_materialmap_set_texture(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(newval);
//    obj->texture = phpTexture;

    return ret;
}
/* }}} */

static int php_raylib_materialmap_set_color(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

//TODO: not supported ?
//    if (Z_TYPE_P(newval) == IS_NULL) {
//        // Cannot set this to null...
//        return ret;
//    }
//
//    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(newval);
//    obj->color = phpColor;

    return ret;
}
/* }}} */

static int php_raylib_materialmap_set_value(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->materialmap.value = 0;
        return ret;
    }

    obj->materialmap.value = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_materialmap_methods[] = {
        PHP_FE_END
};
void php_raylib_materialmap_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_materialmap_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_materialmap_object_handlers.offset = XtOffsetOf(php_raylib_materialmap_object, std);
    php_raylib_materialmap_object_handlers.free_obj = &php_raylib_materialmap_free_storage;
    php_raylib_materialmap_object_handlers.clone_obj = php_raylib_materialmap_clone;

    // Props
    php_raylib_materialmap_object_handlers.get_property_ptr_ptr = php_raylib_materialmap_get_property_ptr_ptr;
    php_raylib_materialmap_object_handlers.get_gc               = php_raylib_materialmap_get_gc;
    php_raylib_materialmap_object_handlers.get_properties       = php_raylib_materialmap_get_properties;
    php_raylib_materialmap_object_handlers.read_property	     = php_raylib_materialmap_read_property;
    php_raylib_materialmap_object_handlers.write_property       = php_raylib_materialmap_write_property;
    php_raylib_materialmap_object_handlers.has_property	     = php_raylib_materialmap_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "materialmap", php_raylib_materialmap_methods);
    php_raylib_materialmap_ce = zend_register_internal_class(&ce);
    php_raylib_materialmap_ce->create_object = php_raylib_materialmap_new;

    // Props
    zend_hash_init(&php_raylib_materialmap_prop_handlers, 0, NULL, php_raylib_materialmap_free_prop_handler, 1);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "texture", php_raylib_materialmap_get_texture, php_raylib_materialmap_set_texture, NULL, NULL, NULL, NULL);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "color", NULL, NULL, php_raylib_materialmap_get_color, php_raylib_materialmap_set_color, NULL, NULL);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "value", NULL, NULL, NULL, NULL, php_raylib_materialmap_get_value, php_raylib_materialmap_set_value);
}
