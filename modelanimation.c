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

#include "boneinfo.h"
#include "transform.h"

#include "modelanimation.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_MODELANIMATION_OBJECT_ID = 0;
static unsigned char RL_MODELANIMATION_INIT = 0;
static const unsigned int RL_MODELANIMATION_MAX_OBJECTS = 999999;

char* RL_ModelAnimation_Hash_Id(char *str, size_t size) {
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

struct RL_ModelAnimation* RL_ModelAnimation_Create() {
    //-- Create the initial data structures
    if (RL_MODELANIMATION_INIT == 0) {
        RL_ModelAnimation_Object_List = (struct RL_ModelAnimation**) malloc(0);
        RL_ModelAnimation_Object_Map = hashmap_create();
        RL_MODELANIMATION_INIT = 1;
    }

    //-- Create the container object
    struct RL_ModelAnimation* object = (struct RL_ModelAnimation*) malloc(sizeof(struct RL_ModelAnimation));
    object->id = RL_MODELANIMATION_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_ModelAnimation_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = (ModelAnimation) {0};
    object->type = RL_MODELANIMATION_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_ModelAnimation_Object_List = (struct RL_ModelAnimation**) realloc(RL_ModelAnimation_Object_List, RL_MODELANIMATION_OBJECT_ID * sizeof(struct RL_ModelAnimation*));
    RL_ModelAnimation_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_ModelAnimation_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_ModelAnimation_Delete(struct RL_ModelAnimation* object, int index) {
    if (index < 0 || index >= RL_MODELANIMATION_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_ModelAnimation_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_ModelAnimation_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_ModelAnimation_Object_List[index], &RL_ModelAnimation_Object_List[index + 1], (RL_MODELANIMATION_OBJECT_ID - index - 1) * sizeof(struct RL_ModelAnimation *));

    // Decrement the count and resize the array
    RL_MODELANIMATION_OBJECT_ID--;
    RL_ModelAnimation_Object_List = (struct RL_ModelAnimation **)realloc(RL_ModelAnimation_Object_List, (RL_MODELANIMATION_OBJECT_ID) * sizeof(struct RL_ModelAnimation *));
}

void RL_ModelAnimation_Free(struct RL_ModelAnimation* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib ModelAnimation PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_modelanimation_object_handlers;

static HashTable php_raylib_modelanimation_prop_handlers;

typedef zend_long (*raylib_modelanimation_read_int_t)(php_raylib_modelanimation_object *obj);
typedef int (*raylib_modelanimation_write_int_t)(php_raylib_modelanimation_object *obj,  zval *value);

typedef HashTable * (*raylib_modelanimation_read_boneinfo_array_t)(php_raylib_modelanimation_object *obj);
typedef int (*raylib_modelanimation_write_boneinfo_array_t)(php_raylib_modelanimation_object *obj,  zval *value);

typedef HashTable * (*raylib_modelanimation_read_transform_array_t)(php_raylib_modelanimation_object *obj);
typedef int (*raylib_modelanimation_write_transform_array_t)(php_raylib_modelanimation_object *obj,  zval *value);

typedef struct _raylib_modelanimation_prop_handler {
    raylib_modelanimation_read_int_t read_int_func;
    raylib_modelanimation_write_int_t write_int_func;
    raylib_modelanimation_read_boneinfo_array_t read_boneinfo_array_func;
    raylib_modelanimation_write_boneinfo_array_t write_boneinfo_array_func;
    raylib_modelanimation_read_transform_array_t read_transform_array_func;
    raylib_modelanimation_write_transform_array_t write_transform_array_func;
} raylib_modelanimation_prop_handler;

static void php_raylib_modelanimation_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_modelanimation_read_int_t read_int_func,
                                                      raylib_modelanimation_write_int_t write_int_func,
                                                      raylib_modelanimation_read_boneinfo_array_t read_boneinfo_array_func,
                                                      raylib_modelanimation_write_boneinfo_array_t write_boneinfo_array_func,
                                                      raylib_modelanimation_read_transform_array_t read_transform_array_func,
                                                      raylib_modelanimation_write_transform_array_t write_transform_array_func) /* {{{ */
{
    raylib_modelanimation_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_boneinfo_array_func = read_boneinfo_array_func;
    hnd.write_boneinfo_array_func = write_boneinfo_array_func;
    hnd.read_transform_array_func = read_transform_array_func;
    hnd.write_transform_array_func = write_transform_array_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_modelanimation_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_modelanimation_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_modelanimation_property_reader(php_raylib_modelanimation_object *obj, raylib_modelanimation_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }
    else if (obj != NULL && hnd->read_boneinfo_array_func) {
        HashTable *ret = hnd->read_boneinfo_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_transform_array_func) {
        HashTable *ret = hnd->read_transform_array_func(obj);
        ZVAL_ARR(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_modelanimation_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_modelanimation_object *obj;
    zval *retval = NULL;
    raylib_modelanimation_prop_handler *hnd = NULL;

    obj = php_raylib_modelanimation_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_modelanimation_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_modelanimation_object *obj;
    zval *retval = NULL;
    raylib_modelanimation_prop_handler *hnd = NULL;

    obj = php_raylib_modelanimation_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_modelanimation_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_modelanimation_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_modelanimation_object *obj;
    raylib_modelanimation_prop_handler *hnd;

    obj = php_raylib_modelanimation_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else if (hnd && hnd->write_boneinfo_array_func) {
        hnd->write_boneinfo_array_func(obj, value);
    } else if (hnd && hnd->write_transform_array_func) {
        hnd->write_transform_array_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_modelanimation_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_modelanimation_object *obj;
    raylib_modelanimation_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_modelanimation_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_modelanimation_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_modelanimation_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_modelanimation_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_modelanimation_object *obj;
    HashTable *props;
    raylib_modelanimation_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_modelanimation_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_modelanimation_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_modelanimation_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_modelanimation_object *intern = php_raylib_modelanimation_fetch_object(object);

    intern->modelanimation->refCount--;
    if (intern->modelanimation->refCount < 1) {
        RL_ModelAnimation_Free(intern->modelanimation);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_modelanimation_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_modelanimation_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_modelanimation_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_modelanimation_object), ce);

    intern->prop_handler = &php_raylib_modelanimation_prop_handlers;

    if (orig) {
        php_raylib_modelanimation_object *other = php_raylib_modelanimation_fetch_object(orig);

        // bones array not yet supported needs to generate a hash table!
        //zend_object *bones = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, &other->bones->std);
        // framePoses array not yet supported needs to generate a hash table!
        //zend_object *framePoses = php_raylib_transform_new_ex(php_raylib_transform_ce, &other->framePoses->std);

        // bones array not yet supported needs to generate a hash table!
        //php_raylib_boneinfo_object *phpBones = php_raylib_boneinfo_fetch_object(bones);
        // framePoses array not yet supported needs to generate a hash table!
        //php_raylib_transform_object *phpFramePoses = php_raylib_transform_fetch_object(framePoses);

        *php_raylib_modelanimation_fetch_data(intern) = (ModelAnimation) {
            .boneCount = php_raylib_modelanimation_fetch_data(other)->boneCount,
            .frameCount = php_raylib_modelanimation_fetch_data(other)->frameCount,
        };

        HashTable *bones_hash;
        ALLOC_HASHTABLE(bones_hash);
        zend_hash_init(bones_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->bones)), NULL, NULL, 0);
        zend_hash_copy(bones_hash, Z_ARRVAL_P(&other->bones), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->bones, bones_hash);

        HashTable *framePoses_hash;
        ALLOC_HASHTABLE(framePoses_hash);
        zend_hash_init(framePoses_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->frameposes)), NULL, NULL, 0);
        zend_hash_copy(framePoses_hash, Z_ARRVAL_P(&other->frameposes), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->frameposes, framePoses_hash);

    } else {
        // bones array not yet supported needs to generate a hash table!
        //zend_object *bones = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, NULL);
        // framePoses array not yet supported needs to generate a hash table!
        //zend_object *framePoses = php_raylib_transform_new_ex(php_raylib_transform_ce, NULL);

        // bones array not yet supported needs to generate a hash table!
        //php_raylib_boneinfo_object *phpBones = php_raylib_boneinfo_fetch_object(bones);
        // framePoses array not yet supported needs to generate a hash table!
        //php_raylib_transform_object *phpFramePoses = php_raylib_transform_fetch_object(framePoses);

        intern->modelanimation = RL_ModelAnimation_Create();
        *php_raylib_modelanimation_fetch_data(intern) = (ModelAnimation) {
            .boneCount = 0,
            .frameCount = 0,
            // .bones is an array and not yet supported via constructor
            // .framePoses is an array and not yet supported via constructor
        };

        HashTable *bones_hash;
        ALLOC_HASHTABLE(bones_hash);
        zend_hash_init(bones_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->bones, bones_hash);

        HashTable *framePoses_hash;
        ALLOC_HASHTABLE(framePoses_hash);
        zend_hash_init(framePoses_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->frameposes, framePoses_hash);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_modelanimation_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_modelanimation_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_modelanimation_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_modelanimation_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_modelanimation_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_modelanimation__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, boneCount, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, frameCount, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_OBJ_INFO(0, bones, raylib\\BoneInfo, 1)
    ZEND_ARG_OBJ_INFO(0, framePoses, raylib\\Transform, 1)
ZEND_END_ARG_INFO()
PHP_METHOD(ModelAnimation, __construct)
{
}

static zend_long php_raylib_modelanimation_get_bonecount(php_raylib_modelanimation_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_modelanimation_fetch_data(obj)->boneCount;
}
/* }}} */

static zend_long php_raylib_modelanimation_get_framecount(php_raylib_modelanimation_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_modelanimation_fetch_data(obj)->frameCount;
}
/* }}} */

static HashTable * php_raylib_modelanimation_get_bones(php_raylib_modelanimation_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->bones);
}
/* }}} */

static HashTable * php_raylib_modelanimation_get_frameposes(php_raylib_modelanimation_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->frameposes);
}
/* }}} */

static int php_raylib_modelanimation_set_bonecount(php_raylib_modelanimation_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_modelanimation_fetch_data(obj)->boneCount = 0;
        return ret;
    }

    php_raylib_modelanimation_fetch_data(obj)->boneCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_modelanimation_set_framecount(php_raylib_modelanimation_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_modelanimation_fetch_data(obj)->frameCount = 0;
        return ret;
    }

    php_raylib_modelanimation_fetch_data(obj)->frameCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_modelanimation_set_bones(php_raylib_modelanimation_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_modelanimation_set_frameposes(php_raylib_modelanimation_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_modelanimation_methods[] = {
        PHP_ME(ModelAnimation, __construct, arginfo_modelanimation__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_modelanimation_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_modelanimation_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_modelanimation_object_handlers.offset = XtOffsetOf(php_raylib_modelanimation_object, std);
    php_raylib_modelanimation_object_handlers.free_obj = &php_raylib_modelanimation_free_storage;
    php_raylib_modelanimation_object_handlers.clone_obj = php_raylib_modelanimation_clone;

    // Props
    php_raylib_modelanimation_object_handlers.get_property_ptr_ptr = php_raylib_modelanimation_get_property_ptr_ptr;
    php_raylib_modelanimation_object_handlers.get_gc               = php_raylib_modelanimation_get_gc;
    php_raylib_modelanimation_object_handlers.get_properties       = php_raylib_modelanimation_get_properties;
    php_raylib_modelanimation_object_handlers.read_property	     = php_raylib_modelanimation_read_property;
    php_raylib_modelanimation_object_handlers.write_property       = php_raylib_modelanimation_write_property;
    php_raylib_modelanimation_object_handlers.has_property	     = php_raylib_modelanimation_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "ModelAnimation", php_raylib_modelanimation_methods);
    php_raylib_modelanimation_ce = zend_register_internal_class(&ce);
    php_raylib_modelanimation_ce->create_object = php_raylib_modelanimation_new;

    // Props
    zend_hash_init(&php_raylib_modelanimation_prop_handlers, 0, NULL, php_raylib_modelanimation_free_prop_handler, 1);
    php_raylib_modelanimation_register_prop_handler(&php_raylib_modelanimation_prop_handlers, "boneCount", php_raylib_modelanimation_get_bonecount, php_raylib_modelanimation_set_bonecount, NULL, NULL, NULL, NULL);
    php_raylib_modelanimation_register_prop_handler(&php_raylib_modelanimation_prop_handlers, "frameCount", php_raylib_modelanimation_get_framecount, php_raylib_modelanimation_set_framecount, NULL, NULL, NULL, NULL);
    php_raylib_modelanimation_register_prop_handler(&php_raylib_modelanimation_prop_handlers, "bones", NULL, NULL, php_raylib_modelanimation_get_bones, php_raylib_modelanimation_set_bones, NULL, NULL);
    php_raylib_modelanimation_register_prop_handler(&php_raylib_modelanimation_prop_handlers, "framePoses", NULL, NULL, NULL, NULL, php_raylib_modelanimation_get_frameposes, php_raylib_modelanimation_set_frameposes);
}
