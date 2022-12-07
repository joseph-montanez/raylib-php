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

#include "shader.h"
#include "materialmap.h"

#include "material.h"

//------------------------------------------------------------------------------------------------------
//-- raylib Material PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_material_object_handlers;

static HashTable php_raylib_material_prop_handlers;

typedef zend_object * (*raylib_material_read_shader_t)(php_raylib_material_object *obj);
typedef int (*raylib_material_write_shader_t)(php_raylib_material_object *obj,  zval *value);

typedef HashTable * (*raylib_material_read_materialmap_array_t)(php_raylib_material_object *obj);
typedef int (*raylib_material_write_materialmap_array_t)(php_raylib_material_object *obj,  zval *value);

typedef HashTable * (*raylib_material_read_float_array_t)(php_raylib_material_object *obj);
typedef int (*raylib_material_write_float_array_t)(php_raylib_material_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_material_update_intern(php_raylib_material_object *intern) {
    php_raylib_shader_object *shaderObject = Z_SHADER_OBJ_P(&intern->shader);
    intern->material.shader = shaderObject->shader;

    zval *maps_element;
    int maps_index;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&intern->maps), maps_element) {
        ZVAL_DEREF(maps_element);
        if ((Z_TYPE_P(maps_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(maps_element), php_raylib_materialmap_ce))) {
            php_raylib_materialmap_object *materialmap_obj =  Z_MATERIALMAP_OBJ_P(maps_element);
            intern->material.maps[maps_index] = materialmap_obj->materialmap;
        }

        maps_index++;
    } ZEND_HASH_FOREACH_END();

}

void php_raylib_material_update_intern_reverse(php_raylib_material_object *intern) {
    php_raylib_shader_object *shaderObject = Z_SHADER_OBJ_P(&intern->shader);
    shaderObject->shader = intern->material.shader;

    zval *maps_element;
    int maps_index;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&intern->maps), maps_element) {
        ZVAL_DEREF(maps_element);
        if ((Z_TYPE_P(maps_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(maps_element), php_raylib_materialmap_ce))) {
            php_raylib_materialmap_object *materialmap_obj =  Z_MATERIALMAP_OBJ_P(maps_element);
            intern->material.maps[maps_index] = materialmap_obj->materialmap;
        }

        maps_index++;
    } ZEND_HASH_FOREACH_END();

}
typedef struct _raylib_material_prop_handler {
    raylib_material_read_shader_t read_shader_func;
    raylib_material_write_shader_t write_shader_func;
    raylib_material_read_materialmap_array_t read_materialmap_array_func;
    raylib_material_write_materialmap_array_t write_materialmap_array_func;
    raylib_material_read_float_array_t read_float_array_func;
    raylib_material_write_float_array_t write_float_array_func;
} raylib_material_prop_handler;

static void php_raylib_material_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_material_read_shader_t read_shader_func,
                                                      raylib_material_write_shader_t write_shader_func,
                                                      raylib_material_read_materialmap_array_t read_materialmap_array_func,
                                                      raylib_material_write_materialmap_array_t write_materialmap_array_func,
                                                      raylib_material_read_float_array_t read_float_array_func,
                                                      raylib_material_write_float_array_t write_float_array_func) /* {{{ */
{
    raylib_material_prop_handler hnd;

    hnd.read_shader_func = read_shader_func;
    hnd.write_shader_func = write_shader_func;
    hnd.read_materialmap_array_func = read_materialmap_array_func;
    hnd.write_materialmap_array_func = write_materialmap_array_func;
    hnd.read_float_array_func = read_float_array_func;
    hnd.write_float_array_func = write_float_array_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_material_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_material_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_material_property_reader(php_raylib_material_object *obj, raylib_material_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_shader_func) {
        zend_object *ret = hnd->read_shader_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_materialmap_array_func) {
        HashTable *ret = hnd->read_materialmap_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_float_array_func) {
        ZVAL_ARR(rv, hnd->read_float_array_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_material_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_material_object *obj;
    zval *retval = NULL;
    raylib_material_prop_handler *hnd = NULL;

    obj = php_raylib_material_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_material_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_material_object *obj;
    zval *retval = NULL;
    raylib_material_prop_handler *hnd = NULL;

    obj = php_raylib_material_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_material_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_material_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_material_object *obj;
    raylib_material_prop_handler *hnd;

    obj = php_raylib_material_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_shader_func) {
        hnd->write_shader_func(obj, value);
    } else if (hnd && hnd->write_materialmap_array_func) {
        hnd->write_materialmap_array_func(obj, value);
    } else if (hnd && hnd->write_float_array_func) {
        hnd->write_float_array_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_material_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_material_object *obj;
    raylib_material_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_material_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_material_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_material_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_material_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_material_object *obj;
    HashTable *props;
    raylib_material_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_material_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_material_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_material_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_material_object *intern = php_raylib_material_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_material_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_material_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_material_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_material_object), ce);

    intern->prop_handler = &php_raylib_material_prop_handlers;

    if (orig) {
        php_raylib_material_object *other = php_raylib_material_fetch_object(orig);

        php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(&other->shader);
        // maps array not yet supported needs to generate a hash table!
        //zend_object *maps = php_raylib_materialmap_new_ex(php_raylib_materialmap_ce, &other->maps->std);

        // maps array not yet supported needs to generate a hash table!
        //php_raylib_materialmap_object *phpMaps = php_raylib_materialmap_fetch_object(maps);

        intern->material = (Material) {
            .shader = (Shader) {
                .id = other->material.shader.id,
                .locs = other->material.shader.locs
            },
        };
        memcpy(intern->material.params, other->material.params, sizeof intern->material.params);

        ZVAL_OBJ_COPY(&intern->shader, &phpShader->std);

        HashTable *maps_hash;
        ALLOC_HASHTABLE(maps_hash);
        zend_hash_init(maps_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->maps)), NULL, NULL, 0);
        zend_hash_copy(maps_hash, Z_ARRVAL_P(&other->maps), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->maps, maps_hash);

    } else {
        zend_object *shader = php_raylib_shader_new_ex(php_raylib_shader_ce, NULL);
        // maps array not yet supported needs to generate a hash table!
        //zend_object *maps = php_raylib_materialmap_new_ex(php_raylib_materialmap_ce, NULL);

        php_raylib_shader_object *phpShader = php_raylib_shader_fetch_object(shader);
        // maps array not yet supported needs to generate a hash table!
        //php_raylib_materialmap_object *phpMaps = php_raylib_materialmap_fetch_object(maps);

        intern->material = (Material) {
            .shader = (Shader) {
                .id = 0,
                .locs = 0
            },
            // .maps is an array and not yet supported via constructor
            .params = 0
        };

        ZVAL_OBJ_COPY(&intern->shader, &phpShader->std);

        HashTable *maps_hash;
        ALLOC_HASHTABLE(maps_hash);
        zend_hash_init(maps_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->maps, maps_hash);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_material_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_material_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_material_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_material_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_material_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_material__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, shader, raylib\\Shader, 1)
    ZEND_ARG_OBJ_INFO(0, maps, raylib\\MaterialMap, 1)
    ZEND_ARG_TYPE_MASK(0, params, IS_DOUBLE, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Material, __construct)
{
}

static zend_object * php_raylib_material_get_shader(php_raylib_material_object *obj) /* {{{ */
{
    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(&obj->shader);

    GC_ADDREF(&phpShader->std);
    return &phpShader->std;
}
/* }}} */

static HashTable * php_raylib_material_get_maps(php_raylib_material_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_material_get_params(php_raylib_material_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static int php_raylib_material_set_shader(php_raylib_material_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    obj->shader = *newval;

    return ret;
}
/* }}} */

static int php_raylib_material_set_maps(php_raylib_material_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_material_set_params(php_raylib_material_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_material_methods[] = {
        PHP_ME(Material, __construct, arginfo_material__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_material_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_material_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_material_object_handlers.offset = XtOffsetOf(php_raylib_material_object, std);
    php_raylib_material_object_handlers.free_obj = &php_raylib_material_free_storage;
    php_raylib_material_object_handlers.clone_obj = php_raylib_material_clone;

    // Props
    php_raylib_material_object_handlers.get_property_ptr_ptr = php_raylib_material_get_property_ptr_ptr;
    php_raylib_material_object_handlers.get_gc               = php_raylib_material_get_gc;
    php_raylib_material_object_handlers.get_properties       = php_raylib_material_get_properties;
    php_raylib_material_object_handlers.read_property	     = php_raylib_material_read_property;
    php_raylib_material_object_handlers.write_property       = php_raylib_material_write_property;
    php_raylib_material_object_handlers.has_property	     = php_raylib_material_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Material", php_raylib_material_methods);
    php_raylib_material_ce = zend_register_internal_class(&ce);
    php_raylib_material_ce->create_object = php_raylib_material_new;

    // Props
    zend_hash_init(&php_raylib_material_prop_handlers, 0, NULL, php_raylib_material_free_prop_handler, 1);
    php_raylib_material_register_prop_handler(&php_raylib_material_prop_handlers, "shader", php_raylib_material_get_shader, php_raylib_material_set_shader, NULL, NULL, NULL, NULL);
    php_raylib_material_register_prop_handler(&php_raylib_material_prop_handlers, "maps", NULL, NULL, php_raylib_material_get_maps, php_raylib_material_set_maps, NULL, NULL);
    php_raylib_material_register_prop_handler(&php_raylib_material_prop_handlers, "params", NULL, NULL, NULL, NULL, php_raylib_material_get_params, php_raylib_material_set_params);
}
