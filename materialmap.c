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
#include "include/hashmap.h"

#ifdef PHP_WIN32
    #include <Wincrypt.h>
#endif

#include "texture.h"
#include "color.h"

#include "materialmap.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_MATERIALMAP_OBJECT_ID = 0;
static unsigned char RL_MATERIALMAP_INIT = 0;
static const unsigned int RL_MATERIALMAP_MAX_OBJECTS = 999999;

char* RL_MaterialMap_Hash_Id(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charset_size = sizeof(charset) - 1;
    for (size_t i = 0; i < size - 1; i++) {
#ifdef PHP_WIN32
        // On Windows, use CryptGenRandom to generate random bytes
        HCRYPTPROV hCryptProv;
        if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
            fprintf(stderr, "CryptAcquireContext failed (%lu)\n", GetLastError());
            return NULL;
        }
        if (!CryptGenRandom(hCryptProv, 1, (BYTE *)&str[i])) {
            fprintf(stderr, "CryptGenRandom failed (%lu)\n", GetLastError());
            return NULL;
        }
        CryptReleaseContext(hCryptProv, 0);
#else
        // On other platforms, use arc4random to generate random bytes
        str[i] = charset[arc4random_uniform(charset_size)];
#endif
    }
    str[size-1] = '\0';
    return str;
}

struct RL_MaterialMap* RL_MaterialMap_Create() {
    //-- Create the initial data structures
    if (RL_MATERIALMAP_INIT == 0) {
        RL_MaterialMap_Object_List = (struct RL_MaterialMap**) malloc(0);
        RL_MaterialMap_Object_Map = hashmap_create();
        RL_MATERIALMAP_INIT = 1;
    }

    //-- Create the container object
    struct RL_MaterialMap* object = (struct RL_MaterialMap*) malloc(sizeof(struct RL_MaterialMap));
    object->id = RL_MATERIALMAP_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_MaterialMap_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = (MaterialMap) {0};
    object->type = RL_MATERIALMAP_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_MaterialMap_Object_List = (struct RL_MaterialMap**) realloc(RL_MaterialMap_Object_List, RL_MATERIALMAP_OBJECT_ID * sizeof(struct RL_MaterialMap*));
    RL_MaterialMap_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_MaterialMap_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_MaterialMap_Delete(struct RL_MaterialMap* object, int index) {
    if (index < 0 || index >= RL_MATERIALMAP_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_MaterialMap_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_MaterialMap_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_MaterialMap_Object_List[index], &RL_MaterialMap_Object_List[index + 1], (RL_MATERIALMAP_OBJECT_ID - index - 1) * sizeof(struct RL_MaterialMap *));

    // Decrement the count and resize the array
    RL_MATERIALMAP_OBJECT_ID--;
    RL_MaterialMap_Object_List = (struct RL_MaterialMap **)realloc(RL_MaterialMap_Object_List, (RL_MATERIALMAP_OBJECT_ID) * sizeof(struct RL_MaterialMap *));
}

void RL_MaterialMap_Free(struct RL_MaterialMap* object) {
    free(object);
}

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

    intern->materialmap->refCount--;
    if (intern->materialmap->refCount < 1) {
        RL_MaterialMap_Free(intern->materialmap);
    }

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

        php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(&other->texture);
        php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(&other->color);


        *php_raylib_materialmap_fetch_data(intern) = (MaterialMap) {
            .texture = (Texture) {
                .id = php_raylib_materialmap_fetch_data(other)->texture.id,
                .width = php_raylib_materialmap_fetch_data(other)->texture.width,
                .height = php_raylib_materialmap_fetch_data(other)->texture.height,
                .mipmaps = php_raylib_materialmap_fetch_data(other)->texture.mipmaps,
                .format = php_raylib_materialmap_fetch_data(other)->texture.format
            },
            .color = (Color) {
                .r = php_raylib_materialmap_fetch_data(other)->color.r,
                .g = php_raylib_materialmap_fetch_data(other)->color.g,
                .b = php_raylib_materialmap_fetch_data(other)->color.b,
                .a = php_raylib_materialmap_fetch_data(other)->color.a
            },
            .value = php_raylib_materialmap_fetch_data(other)->value
        };

        ZVAL_OBJ_COPY(&intern->texture, &phpTexture->std);

        ZVAL_OBJ_COPY(&intern->color, &phpColor->std);

    } else {
        zend_object *texture = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
        zend_object *color = php_raylib_color_new_ex(php_raylib_color_ce, NULL);

        php_raylib_texture_object *phpTexture = php_raylib_texture_fetch_object(texture);
        php_raylib_color_object *phpColor = php_raylib_color_fetch_object(color);

        intern->materialmap = RL_MaterialMap_Create();
        *php_raylib_materialmap_fetch_data(intern) = (MaterialMap) {
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

        ZVAL_OBJ_COPY(&intern->texture, &phpTexture->std);

        ZVAL_OBJ_COPY(&intern->color, &phpColor->std);

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

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_materialmap__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, texture, raylib\\Texture, 1)
    ZEND_ARG_OBJ_INFO(0, color, raylib\\Color, 1)
    ZEND_ARG_TYPE_MASK(0, value, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(MaterialMap, __construct)
{
    zend_object *texture = NULL;
    php_raylib_texture_object *phpTexture;

    zend_object *color = NULL;
    php_raylib_color_object *phpColor;

    double value;
    bool value_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 3)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(texture, php_raylib_texture_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(color, php_raylib_color_ce)
        Z_PARAM_DOUBLE_OR_NULL(value, value_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_materialmap_object *intern = Z_MATERIALMAP_OBJ_P(ZEND_THIS);

    if (texture == NULL) {
        texture = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
    }

    if (color == NULL) {
        color = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    }

    if (value_is_null) {
        value = 0.0f;
    }

    phpTexture = php_raylib_texture_fetch_object(texture);
    phpColor = php_raylib_color_fetch_object(color);

    ZVAL_OBJ_COPY(&intern->texture, &phpTexture->std);
    ZVAL_OBJ_COPY(&intern->color, &phpColor->std);

    *php_raylib_materialmap_fetch_data(intern) = (MaterialMap) {
        .texture = (Texture) {
            .id = php_raylib_texture_fetch_data(phpTexture)->id,
            .width = php_raylib_texture_fetch_data(phpTexture)->width,
            .height = php_raylib_texture_fetch_data(phpTexture)->height,
            .mipmaps = php_raylib_texture_fetch_data(phpTexture)->mipmaps,
            .format = php_raylib_texture_fetch_data(phpTexture)->format
        },
        .color = (Color) {
            .r = php_raylib_color_fetch_data(phpColor)->r,
            .g = php_raylib_color_fetch_data(phpColor)->g,
            .b = php_raylib_color_fetch_data(phpColor)->b,
            .a = php_raylib_color_fetch_data(phpColor)->a
        },
        .value = (float) value
    };
}

static zend_object * php_raylib_materialmap_get_texture(php_raylib_materialmap_object *obj) /* {{{ */
{
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(&obj->texture);

    phpTexture->texture->refCount++;

    GC_ADDREF(&phpTexture->std);

    return &phpTexture->std;
}
/* }}} */

static zend_object * php_raylib_materialmap_get_color(php_raylib_materialmap_object *obj) /* {{{ */
{
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(&obj->color);

    phpColor->color->refCount++;

    GC_ADDREF(&phpColor->std);

    return &phpColor->std;
}
/* }}} */

static double php_raylib_materialmap_get_value(php_raylib_materialmap_object *obj) /* {{{ */
{
    return (double) php_raylib_materialmap_fetch_data(obj)->value;
}
/* }}} */

static int php_raylib_materialmap_set_texture(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_texture_object *rl_texture = Z_TEXTURE_OBJ_P(newval);
    rl_texture->texture->refCount++;

    php_raylib_materialmap_fetch_data(obj)->texture = *php_raylib_texture_fetch_data(rl_texture);

    obj->texture = *newval;

    return ret;
}
/* }}} */

static int php_raylib_materialmap_set_color(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_color_object *rl_color = Z_COLOR_OBJ_P(newval);
    rl_color->color->refCount++;

    obj->color = *newval;

    return ret;
}
/* }}} */

static int php_raylib_materialmap_set_value(php_raylib_materialmap_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_materialmap_fetch_data(obj)->value = 0;
        return ret;
    }

    php_raylib_materialmap_fetch_data(obj)->value = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_materialmap_methods[] = {
        PHP_ME(MaterialMap, __construct, arginfo_materialmap__construct, ZEND_ACC_PUBLIC)
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
    INIT_NS_CLASS_ENTRY(ce, "raylib", "MaterialMap", php_raylib_materialmap_methods);
    php_raylib_materialmap_ce = zend_register_internal_class(&ce);
    php_raylib_materialmap_ce->create_object = php_raylib_materialmap_new;

    // Props
    zend_hash_init(&php_raylib_materialmap_prop_handlers, 0, NULL, php_raylib_materialmap_free_prop_handler, 1);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "texture", php_raylib_materialmap_get_texture, php_raylib_materialmap_set_texture, NULL, NULL, NULL, NULL);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "color", NULL, NULL, php_raylib_materialmap_get_color, php_raylib_materialmap_set_color, NULL, NULL);
    php_raylib_materialmap_register_prop_handler(&php_raylib_materialmap_prop_handlers, "value", NULL, NULL, NULL, NULL, php_raylib_materialmap_get_value, php_raylib_materialmap_set_value);
}
