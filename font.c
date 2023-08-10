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
#include "rectangle.h"
#include "glyphinfo.h"

#include "font.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_FONT_OBJECT_ID = 0;
static unsigned char RL_FONT_INIT = 0;
static const unsigned int RL_FONT_MAX_OBJECTS = 999999;

char* RL_Font_Hash_Id(char *str, size_t size) {
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

struct RL_Font* RL_Font_Create() {
    //-- Create the initial data structures
    if (RL_FONT_INIT == 0) {
        RL_Font_Object_List = (struct RL_Font**) malloc(0);
        RL_Font_Object_Map = hashmap_create();
        RL_FONT_INIT = 1;
    }

    //-- Create the container object
    struct RL_Font* object = (struct RL_Font*) malloc(sizeof(struct RL_Font));
    object->id = RL_FONT_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_Font_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = (Font) {0};
    object->type = RL_FONT_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Font_Object_List = (struct RL_Font**) realloc(RL_Font_Object_List, RL_FONT_OBJECT_ID * sizeof(struct RL_Font*));
    RL_Font_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Font_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Font_Delete(struct RL_Font* object, int index) {
    if (index < 0 || index >= RL_FONT_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Font_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Font_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Font_Object_List[index], &RL_Font_Object_List[index + 1], (RL_FONT_OBJECT_ID - index - 1) * sizeof(struct RL_Font *));

    // Decrement the count and resize the array
    RL_FONT_OBJECT_ID--;
    RL_Font_Object_List = (struct RL_Font **)realloc(RL_Font_Object_List, (RL_FONT_OBJECT_ID) * sizeof(struct RL_Font *));
}

void RL_Font_Free(struct RL_Font* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib Font PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_font_object_handlers;

static HashTable php_raylib_font_prop_handlers;

typedef zend_long (*raylib_font_read_int_t)(php_raylib_font_object *obj);
typedef int (*raylib_font_write_int_t)(php_raylib_font_object *obj,  zval *value);

typedef zend_object * (*raylib_font_read_texture_t)(php_raylib_font_object *obj);
typedef int (*raylib_font_write_texture_t)(php_raylib_font_object *obj,  zval *value);

typedef HashTable * (*raylib_font_read_rectangle_array_t)(php_raylib_font_object *obj);
typedef int (*raylib_font_write_rectangle_array_t)(php_raylib_font_object *obj,  zval *value);

typedef HashTable * (*raylib_font_read_glyphinfo_array_t)(php_raylib_font_object *obj);
typedef int (*raylib_font_write_glyphinfo_array_t)(php_raylib_font_object *obj,  zval *value);

typedef struct _raylib_font_prop_handler {
    raylib_font_read_int_t read_int_func;
    raylib_font_write_int_t write_int_func;
    raylib_font_read_texture_t read_texture_func;
    raylib_font_write_texture_t write_texture_func;
    raylib_font_read_rectangle_array_t read_rectangle_array_func;
    raylib_font_write_rectangle_array_t write_rectangle_array_func;
    raylib_font_read_glyphinfo_array_t read_glyphinfo_array_func;
    raylib_font_write_glyphinfo_array_t write_glyphinfo_array_func;
} raylib_font_prop_handler;

static void php_raylib_font_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_font_read_int_t read_int_func,
                                                      raylib_font_write_int_t write_int_func,
                                                      raylib_font_read_texture_t read_texture_func,
                                                      raylib_font_write_texture_t write_texture_func,
                                                      raylib_font_read_rectangle_array_t read_rectangle_array_func,
                                                      raylib_font_write_rectangle_array_t write_rectangle_array_func,
                                                      raylib_font_read_glyphinfo_array_t read_glyphinfo_array_func,
                                                      raylib_font_write_glyphinfo_array_t write_glyphinfo_array_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_texture_func = read_texture_func;
    hnd.write_texture_func = write_texture_func;
    hnd.read_rectangle_array_func = read_rectangle_array_func;
    hnd.write_rectangle_array_func = write_rectangle_array_func;
    hnd.read_glyphinfo_array_func = read_glyphinfo_array_func;
    hnd.write_glyphinfo_array_func = write_glyphinfo_array_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_font_property_reader(php_raylib_font_object *obj, raylib_font_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }
    else if (obj != NULL && hnd->read_texture_func) {
        zend_object *ret = hnd->read_texture_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_rectangle_array_func) {
        HashTable *ret = hnd->read_rectangle_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_glyphinfo_array_func) {
        HashTable *ret = hnd->read_glyphinfo_array_func(obj);
        ZVAL_ARR(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_font_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_font_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_font_object *obj;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_font_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_font_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    raylib_font_prop_handler *hnd;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else if (hnd && hnd->write_texture_func) {
        hnd->write_texture_func(obj, value);
    } else if (hnd && hnd->write_rectangle_array_func) {
        hnd->write_rectangle_array_func(obj, value);
    } else if (hnd && hnd->write_glyphinfo_array_func) {
        hnd->write_glyphinfo_array_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_font_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    raylib_font_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_font_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_font_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_font_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_font_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_font_object *obj;
    HashTable *props;
    raylib_font_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_font_fetch_object(object);
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

void php_raylib_font_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_font_object *intern = php_raylib_font_fetch_object(object);

    intern->font->refCount--;
    if (intern->font->refCount < 1) {
        RL_Font_Free(intern->font);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_font_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_font_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_font_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_font_object), ce);

    intern->prop_handler = &php_raylib_font_prop_handlers;

    if (orig) {
        php_raylib_font_object *other = php_raylib_font_fetch_object(orig);

        php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(&other->texture);
        // recs array not yet supported needs to generate a hash table!
        //zend_object *recs = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, &other->recs->std);
        // glyphs array not yet supported needs to generate a hash table!
        //zend_object *glyphs = php_raylib_glyphinfo_new_ex(php_raylib_glyphinfo_ce, &other->glyphs->std);

        // recs array not yet supported needs to generate a hash table!
        //php_raylib_rectangle_object *phpRecs = php_raylib_rectangle_fetch_object(recs);
        // glyphs array not yet supported needs to generate a hash table!
        //php_raylib_glyphinfo_object *phpGlyphs = php_raylib_glyphinfo_fetch_object(glyphs);

        *php_raylib_font_fetch_data(intern) = (Font) {
            .baseSize = php_raylib_font_fetch_data(other)->baseSize,
            .glyphCount = php_raylib_font_fetch_data(other)->glyphCount,
            .glyphPadding = php_raylib_font_fetch_data(other)->glyphPadding,
            .texture = (Texture) {
                .id = php_raylib_font_fetch_data(other)->texture.id,
                .width = php_raylib_font_fetch_data(other)->texture.width,
                .height = php_raylib_font_fetch_data(other)->texture.height,
                .mipmaps = php_raylib_font_fetch_data(other)->texture.mipmaps,
                .format = php_raylib_font_fetch_data(other)->texture.format
            },
        };

        ZVAL_OBJ_COPY(&intern->texture, &phpTexture->std);

        HashTable *recs_hash;
        ALLOC_HASHTABLE(recs_hash);
        zend_hash_init(recs_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->recs)), NULL, NULL, 0);
        zend_hash_copy(recs_hash, Z_ARRVAL_P(&other->recs), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->recs, recs_hash);

        HashTable *glyphs_hash;
        ALLOC_HASHTABLE(glyphs_hash);
        zend_hash_init(glyphs_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->glyphs)), NULL, NULL, 0);
        zend_hash_copy(glyphs_hash, Z_ARRVAL_P(&other->glyphs), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->glyphs, glyphs_hash);

    } else {
        zend_object *texture = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
        // recs array not yet supported needs to generate a hash table!
        //zend_object *recs = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);
        // glyphs array not yet supported needs to generate a hash table!
        //zend_object *glyphs = php_raylib_glyphinfo_new_ex(php_raylib_glyphinfo_ce, NULL);

        php_raylib_texture_object *phpTexture = php_raylib_texture_fetch_object(texture);
        // recs array not yet supported needs to generate a hash table!
        //php_raylib_rectangle_object *phpRecs = php_raylib_rectangle_fetch_object(recs);
        // glyphs array not yet supported needs to generate a hash table!
        //php_raylib_glyphinfo_object *phpGlyphs = php_raylib_glyphinfo_fetch_object(glyphs);

        intern->font = RL_Font_Create();
        *php_raylib_font_fetch_data(intern) = (Font) {
            .baseSize = 0,
            .glyphCount = 0,
            .glyphPadding = 0,
            .texture = (Texture) {
                .id = 0,
                .width = 0,
                .height = 0,
                .mipmaps = 0,
                .format = 0
            },
            // .recs is an array and not yet supported via constructor
            // .glyphs is an array and not yet supported via constructor
        };

        ZVAL_OBJ_COPY(&intern->texture, &phpTexture->std);

        HashTable *recs_hash;
        ALLOC_HASHTABLE(recs_hash);
        zend_hash_init(recs_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->recs, recs_hash);

        HashTable *glyphs_hash;
        ALLOC_HASHTABLE(glyphs_hash);
        zend_hash_init(glyphs_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->glyphs, glyphs_hash);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_font_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_font_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_font_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_font_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_font_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_font__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
    *php_raylib_font_fetch_data(intern) = LoadFont(fileName->val);
}

static zend_long php_raylib_font_get_basesize(php_raylib_font_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_font_fetch_data(obj)->baseSize;
}
/* }}} */

static zend_long php_raylib_font_get_glyphcount(php_raylib_font_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_font_fetch_data(obj)->glyphCount;
}
/* }}} */

static zend_long php_raylib_font_get_glyphpadding(php_raylib_font_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_font_fetch_data(obj)->glyphPadding;
}
/* }}} */

static zend_object * php_raylib_font_get_texture(php_raylib_font_object *obj) /* {{{ */
{
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(&obj->texture);

    phpTexture->texture->refCount++;

    GC_ADDREF(&phpTexture->std);

    return &phpTexture->std;
}
/* }}} */

static HashTable * php_raylib_font_get_recs(php_raylib_font_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->recs);
}
/* }}} */

static HashTable * php_raylib_font_get_glyphs(php_raylib_font_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->glyphs);
}
/* }}} */

static int php_raylib_font_set_basesize(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_font_fetch_data(obj)->baseSize = 0;
        return ret;
    }

    php_raylib_font_fetch_data(obj)->baseSize = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_set_glyphcount(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_font_fetch_data(obj)->glyphCount = 0;
        return ret;
    }

    php_raylib_font_fetch_data(obj)->glyphCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_set_glyphpadding(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_font_fetch_data(obj)->glyphPadding = 0;
        return ret;
    }

    php_raylib_font_fetch_data(obj)->glyphPadding = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_set_texture(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_texture_object *rl_texture = Z_TEXTURE_OBJ_P(newval);
    rl_texture->texture->refCount++;

    obj->texture = *newval;

    return ret;
}
/* }}} */

static int php_raylib_font_set_recs(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_font_set_glyphs(php_raylib_font_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_font_methods[] = {
        PHP_ME(Font, __construct, arginfo_font__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
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
    php_raylib_font_ce = zend_register_internal_class(&ce);
    php_raylib_font_ce->create_object = php_raylib_font_new;

    // Props
    zend_hash_init(&php_raylib_font_prop_handlers, 0, NULL, php_raylib_font_free_prop_handler, 1);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "baseSize", php_raylib_font_get_basesize, php_raylib_font_set_basesize, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "glyphCount", php_raylib_font_get_glyphcount, php_raylib_font_set_glyphcount, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "glyphPadding", php_raylib_font_get_glyphpadding, php_raylib_font_set_glyphpadding, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "texture", NULL, NULL, php_raylib_font_get_texture, php_raylib_font_set_texture, NULL, NULL, NULL, NULL);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "recs", NULL, NULL, NULL, NULL, php_raylib_font_get_recs, php_raylib_font_set_recs, NULL, NULL);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "glyphs", NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_font_get_glyphs, php_raylib_font_set_glyphs);
}
