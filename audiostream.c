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


#include "audiostream.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_AUDIOSTREAM_OBJECT_ID = 0;
static unsigned char RL_AUDIOSTREAM_INIT = 0;
static const unsigned int RL_AUDIOSTREAM_MAX_OBJECTS = 999999;

char* RL_AudioStream_Hash_Id(char *str, size_t size) {
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

struct RL_AudioStream* RL_AudioStream_Create() {
    //-- Create the initial data structures
    if (RL_AUDIOSTREAM_INIT == 0) {
        RL_AudioStream_Object_List = (struct RL_AudioStream**) malloc(0);
        RL_AudioStream_Object_Map = hashmap_create();
        RL_AUDIOSTREAM_INIT = 1;
    }

    //-- Create the container object
    struct RL_AudioStream* object = (struct RL_AudioStream*) malloc(sizeof(struct RL_AudioStream));
    object->id = RL_AUDIOSTREAM_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_AudioStream_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = ( AudioStream) {};
    object->type = RL_AUDIOSTREAM_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_AudioStream_Object_List = (struct RL_AudioStream**) realloc(RL_AudioStream_Object_List, RL_AUDIOSTREAM_OBJECT_ID * sizeof(struct RL_AudioStream*));
    RL_AudioStream_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_AudioStream_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_AudioStream_Delete(struct RL_AudioStream* object, int index) {
    if (index < 0 || index >= RL_AUDIOSTREAM_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_AudioStream_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_AudioStream_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_AudioStream_Object_List[index], &RL_AudioStream_Object_List[index + 1], (RL_AUDIOSTREAM_OBJECT_ID - index - 1) * sizeof(struct RL_AudioStream *));

    // Decrement the count and resize the array
    RL_AUDIOSTREAM_OBJECT_ID--;
    RL_AudioStream_Object_List = (struct RL_AudioStream **)realloc(RL_AudioStream_Object_List, (RL_AUDIOSTREAM_OBJECT_ID) * sizeof(struct RL_AudioStream *));
}

void RL_AudioStream_Free(struct RL_AudioStream* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib AudioStream PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_audiostream_object_handlers;

static HashTable php_raylib_audiostream_prop_handlers;

typedef HashTable * (*raylib_audiostream_read_raudiobuffer_array_t)(php_raylib_audiostream_object *obj);
typedef int (*raylib_audiostream_write_raudiobuffer_array_t)(php_raylib_audiostream_object *obj,  zval *value);

typedef zend_object * (*raylib_audiostream_read_raudioprocessor__t)(php_raylib_audiostream_object *obj);
typedef int (*raylib_audiostream_write_raudioprocessor__t)(php_raylib_audiostream_object *obj,  zval *value);

typedef zend_long (*raylib_audiostream_read_unsigned_int_t)(php_raylib_audiostream_object *obj);
typedef int (*raylib_audiostream_write_unsigned_int_t)(php_raylib_audiostream_object *obj,  zval *value);

typedef struct _raylib_audiostream_prop_handler {
    raylib_audiostream_read_raudiobuffer_array_t read_raudiobuffer_array_func;
    raylib_audiostream_write_raudiobuffer_array_t write_raudiobuffer_array_func;
    raylib_audiostream_read_raudioprocessor__t read_raudioprocessor__func;
    raylib_audiostream_write_raudioprocessor__t write_raudioprocessor__func;
    raylib_audiostream_read_unsigned_int_t read_unsigned_int_func;
    raylib_audiostream_write_unsigned_int_t write_unsigned_int_func;
} raylib_audiostream_prop_handler;

static void php_raylib_audiostream_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_audiostream_read_raudiobuffer_array_t read_raudiobuffer_array_func,
                                                      raylib_audiostream_write_raudiobuffer_array_t write_raudiobuffer_array_func,
                                                      raylib_audiostream_read_raudioprocessor__t read_raudioprocessor__func,
                                                      raylib_audiostream_write_raudioprocessor__t write_raudioprocessor__func,
                                                      raylib_audiostream_read_unsigned_int_t read_unsigned_int_func,
                                                      raylib_audiostream_write_unsigned_int_t write_unsigned_int_func) /* {{{ */
{
    raylib_audiostream_prop_handler hnd;

    hnd.read_raudiobuffer_array_func = read_raudiobuffer_array_func;
    hnd.write_raudiobuffer_array_func = write_raudiobuffer_array_func;
    hnd.read_raudioprocessor__func = read_raudioprocessor__func;
    hnd.write_raudioprocessor__func = write_raudioprocessor__func;
    hnd.read_unsigned_int_func = read_unsigned_int_func;
    hnd.write_unsigned_int_func = write_unsigned_int_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_audiostream_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_audiostream_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_audiostream_property_reader(php_raylib_audiostream_object *obj, raylib_audiostream_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_raudiobuffer_array_func) {
        HashTable *ret = hnd->read_raudiobuffer_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_raudioprocessor__func) {
        zend_object *ret = hnd->read_raudioprocessor__func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_unsigned_int_func) {
        ZVAL_LONG(rv, hnd->read_unsigned_int_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_audiostream_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_audiostream_object *obj;
    zval *retval = NULL;
    raylib_audiostream_prop_handler *hnd = NULL;

    obj = php_raylib_audiostream_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_audiostream_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_audiostream_object *obj;
    zval *retval = NULL;
    raylib_audiostream_prop_handler *hnd = NULL;

    obj = php_raylib_audiostream_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_audiostream_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_audiostream_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_audiostream_object *obj;
    raylib_audiostream_prop_handler *hnd;

    obj = php_raylib_audiostream_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_raudiobuffer_array_func) {
        hnd->write_raudiobuffer_array_func(obj, value);
    } else if (hnd && hnd->write_raudioprocessor__func) {
        hnd->write_raudioprocessor__func(obj, value);
    } else if (hnd && hnd->write_unsigned_int_func) {
        hnd->write_unsigned_int_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_audiostream_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_audiostream_object *obj;
    raylib_audiostream_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_audiostream_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_audiostream_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_audiostream_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_audiostream_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_audiostream_object *obj;
    HashTable *props;
    raylib_audiostream_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_audiostream_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_audiostream_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_audiostream_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_audiostream_object *intern = php_raylib_audiostream_fetch_object(object);

    intern->audiostream->refCount--;
    if (intern->audiostream->refCount < 1) {
        RL_AudioStream_Free(intern->audiostream);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_audiostream_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_audiostream_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_audiostream_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_audiostream_object), ce);

    intern->prop_handler = &php_raylib_audiostream_prop_handlers;

    if (orig) {
        php_raylib_audiostream_object *other = php_raylib_audiostream_fetch_object(orig);

        // buffer array not yet supported needs to generate a hash table!
        //zend_object *buffer = php_raylib_raudiobuffer_new_ex(php_raylib_raudiobuffer_ce, &other->buffer->std);
        // processor array not yet supported needs to generate a hash table!
        //zend_object *processor = php_raylib_raudioprocessor_new_ex(php_raylib_raudioprocessor_ce, &other->processor->std);

        // buffer array not yet supported needs to generate a hash table!
        //php_raylib_raudiobuffer_object *phpBuffer = php_raylib_raudiobuffer_fetch_object(buffer);
        // processor array not yet supported needs to generate a hash table!
        //php_raylib_raudioprocessor_object *phpProcessor = php_raylib_raudioprocessor_fetch_object(processor);

        *php_raylib_audiostream_fetch_data(intern) = (AudioStream) {
            .sampleRate = php_raylib_audiostream_fetch_data(other)->sampleRate,
            .sampleSize = php_raylib_audiostream_fetch_data(other)->sampleSize,
            .channels = php_raylib_audiostream_fetch_data(other)->channels
        };

        HashTable *processor_hash;
        ALLOC_HASHTABLE(processor_hash);
        zend_hash_init(processor_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->processor)), NULL, NULL, 0);
        zend_hash_copy(processor_hash, Z_ARRVAL_P(&other->processor), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->processor, processor_hash);

    } else {
        // buffer array not yet supported needs to generate a hash table!
        //zend_object *buffer = php_raylib_raudiobuffer_new_ex(php_raylib_raudiobuffer_ce, NULL);
        // processor array not yet supported needs to generate a hash table!
        //zend_object *processor = php_raylib_raudioprocessor_new_ex(php_raylib_raudioprocessor_ce, NULL);

        // buffer array not yet supported needs to generate a hash table!
        //php_raylib_raudiobuffer_object *phpBuffer = php_raylib_raudiobuffer_fetch_object(buffer);
        // processor array not yet supported needs to generate a hash table!
        //php_raylib_raudioprocessor_object *phpProcessor = php_raylib_raudioprocessor_fetch_object(processor);

        intern->audiostream = RL_AudioStream_Create();
        *php_raylib_audiostream_fetch_data(intern) = (AudioStream) {
            // .buffer is an array and not yet supported via constructor
            // .processor is an array and not yet supported via constructor
            .sampleRate = 0,
            .sampleSize = 0,
            .channels = 0
        };

        HashTable *processor_hash;
        ALLOC_HASHTABLE(processor_hash);
        zend_hash_init(processor_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->processor, processor_hash);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_audiostream_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_audiostream_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_audiostream_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_audiostream_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_audiostream_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_audiostream__construct, 0, 0, 3)
    ZEND_ARG_INFO(0, sampleRate)
    ZEND_ARG_INFO(0, sampleSize)
    ZEND_ARG_INFO(0, channels)
ZEND_END_ARG_INFO()
PHP_METHOD(AudioStream, __construct)
{
}

static HashTable * php_raylib_audiostream_get_buffer(php_raylib_audiostream_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->buffer);
}
/* }}} */

static zend_object * php_raylib_audiostream_get_processor(php_raylib_audiostream_object *obj) /* {{{ */
{
    //TODO: Support for pointer and arrays
    //GC_ADDREF(&obj->processor->std);
    //return &obj->processor->std;
}
/* }}} */

static zend_long php_raylib_audiostream_get_samplerate(php_raylib_audiostream_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_audiostream_fetch_data(obj)->sampleRate;
}
/* }}} */

static zend_long php_raylib_audiostream_get_samplesize(php_raylib_audiostream_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_audiostream_fetch_data(obj)->sampleSize;
}
/* }}} */

static zend_long php_raylib_audiostream_get_channels(php_raylib_audiostream_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_audiostream_fetch_data(obj)->channels;
}
/* }}} */

static int php_raylib_audiostream_set_buffer(php_raylib_audiostream_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_audiostream_set_processor(php_raylib_audiostream_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    obj->processor = *newval;

    return ret;
}
/* }}} */

static int php_raylib_audiostream_set_samplerate(php_raylib_audiostream_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_audiostream_fetch_data(obj)->sampleRate = 0;
        return ret;
    }

    php_raylib_audiostream_fetch_data(obj)->sampleRate = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_audiostream_set_samplesize(php_raylib_audiostream_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_audiostream_fetch_data(obj)->sampleSize = 0;
        return ret;
    }

    php_raylib_audiostream_fetch_data(obj)->sampleSize = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_audiostream_set_channels(php_raylib_audiostream_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_audiostream_fetch_data(obj)->channels = 0;
        return ret;
    }

    php_raylib_audiostream_fetch_data(obj)->channels = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_audiostream_methods[] = {
        PHP_ME(AudioStream, __construct, arginfo_audiostream__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_audiostream_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_audiostream_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_audiostream_object_handlers.offset = XtOffsetOf(php_raylib_audiostream_object, std);
    php_raylib_audiostream_object_handlers.free_obj = &php_raylib_audiostream_free_storage;
    php_raylib_audiostream_object_handlers.clone_obj = php_raylib_audiostream_clone;

    // Props
    php_raylib_audiostream_object_handlers.get_property_ptr_ptr = php_raylib_audiostream_get_property_ptr_ptr;
    php_raylib_audiostream_object_handlers.get_gc               = php_raylib_audiostream_get_gc;
    php_raylib_audiostream_object_handlers.get_properties       = php_raylib_audiostream_get_properties;
    php_raylib_audiostream_object_handlers.read_property	     = php_raylib_audiostream_read_property;
    php_raylib_audiostream_object_handlers.write_property       = php_raylib_audiostream_write_property;
    php_raylib_audiostream_object_handlers.has_property	     = php_raylib_audiostream_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "AudioStream", php_raylib_audiostream_methods);
    php_raylib_audiostream_ce = zend_register_internal_class(&ce);
    php_raylib_audiostream_ce->create_object = php_raylib_audiostream_new;

    // Props
    zend_hash_init(&php_raylib_audiostream_prop_handlers, 0, NULL, php_raylib_audiostream_free_prop_handler, 1);
    php_raylib_audiostream_register_prop_handler(&php_raylib_audiostream_prop_handlers, "buffer", php_raylib_audiostream_get_buffer, php_raylib_audiostream_set_buffer, NULL, NULL, NULL, NULL);
    php_raylib_audiostream_register_prop_handler(&php_raylib_audiostream_prop_handlers, "processor", NULL, NULL, php_raylib_audiostream_get_processor, php_raylib_audiostream_set_processor, NULL, NULL);
    php_raylib_audiostream_register_prop_handler(&php_raylib_audiostream_prop_handlers, "sampleRate", NULL, NULL, NULL, NULL, php_raylib_audiostream_get_samplerate, php_raylib_audiostream_set_samplerate);
    php_raylib_audiostream_register_prop_handler(&php_raylib_audiostream_prop_handlers, "sampleSize", NULL, NULL, NULL, NULL, php_raylib_audiostream_get_samplesize, php_raylib_audiostream_set_samplesize);
    php_raylib_audiostream_register_prop_handler(&php_raylib_audiostream_prop_handlers, "channels", NULL, NULL, NULL, NULL, php_raylib_audiostream_get_channels, php_raylib_audiostream_set_channels);
}
