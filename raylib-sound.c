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
typedef struct tagMSG *LPMSG;

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"

#include "raylib-audiostream.h"

#include "raylib-sound.h"

//------------------------------------------------------------------------------------------------------
//-- raylib Sound PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_sound_object_handlers;

static HashTable php_raylib_sound_prop_handlers;

typedef zend_object * (*raylib_sound_read_audiostream_t)(php_raylib_sound_object *obj);
typedef int (*raylib_sound_write_audiostream_t)(php_raylib_sound_object *obj,  zval *value);

typedef zend_long (*raylib_sound_read_unsigned_int_t)(php_raylib_sound_object *obj);
typedef int (*raylib_sound_write_unsigned_int_t)(php_raylib_sound_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_sound_update_intern(php_raylib_sound_object *intern) {
    intern->sound.stream = intern->stream->audiostream;
}
typedef struct _raylib_sound_prop_handler {
    raylib_sound_read_audiostream_t read_audiostream_func;
    raylib_sound_write_audiostream_t write_audiostream_func;
    raylib_sound_read_unsigned_int_t read_unsigned_int_func;
    raylib_sound_write_unsigned_int_t write_unsigned_int_func;
} raylib_sound_prop_handler;

static void php_raylib_sound_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_sound_read_audiostream_t read_audiostream_func,
                                                      raylib_sound_write_audiostream_t write_audiostream_func,
                                                      raylib_sound_read_unsigned_int_t read_unsigned_int_func,
                                                      raylib_sound_write_unsigned_int_t write_unsigned_int_func) /* {{{ */
{
    raylib_sound_prop_handler hnd;

    hnd.read_audiostream_func = read_audiostream_func;
    hnd.write_audiostream_func = write_audiostream_func;
    hnd.read_unsigned_int_func = read_unsigned_int_func;
    hnd.write_unsigned_int_func = write_unsigned_int_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_sound_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_sound_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_sound_property_reader(php_raylib_sound_object *obj, raylib_sound_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_audiostream_func) {
        zend_object *ret = hnd->read_audiostream_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_unsigned_int_func) {
        ZVAL_LONG(rv, hnd->read_unsigned_int_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_sound_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_sound_object *obj;
    zval *retval = NULL;
    raylib_sound_prop_handler *hnd = NULL;

    obj = php_raylib_sound_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_sound_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_sound_object *obj;
    zval *retval = NULL;
    raylib_sound_prop_handler *hnd = NULL;

    obj = php_raylib_sound_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_sound_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_sound_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_sound_object *obj;
    raylib_sound_prop_handler *hnd;

    obj = php_raylib_sound_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_audiostream_func) {
        hnd->write_audiostream_func(obj, value);
    } else if (hnd && hnd->write_unsigned_int_func) {
        hnd->write_unsigned_int_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_sound_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_sound_object *obj;
    raylib_sound_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_sound_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_sound_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_sound_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_sound_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_sound_object *obj;
    HashTable *props;
    raylib_sound_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_sound_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_sound_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_sound_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_sound_object *intern = php_raylib_sound_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_sound_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_sound_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_sound_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_sound_object), ce);

    intern->prop_handler = &php_raylib_sound_prop_handlers;

    if (orig) {
        php_raylib_sound_object *other = php_raylib_sound_fetch_object(orig);

        zend_object *stream = php_raylib_audiostream_new_ex(php_raylib_audiostream_ce, &other->stream->std);

        php_raylib_audiostream_object *phpStream = php_raylib_audiostream_fetch_object(stream);

        intern->sound = (Sound) {
            .stream = (AudioStream) {
                .buffer = other->sound.stream.buffer,
                .sampleRate = other->sound.stream.sampleRate,
                .sampleSize = other->sound.stream.sampleSize,
                .channels = other->sound.stream.channels
            },
            .frameCount = other->sound.frameCount
        };

        intern->stream = phpStream;
    } else {
        zend_object *stream = php_raylib_audiostream_new_ex(php_raylib_audiostream_ce, NULL);

        php_raylib_audiostream_object *phpStream = php_raylib_audiostream_fetch_object(stream);

        intern->sound = (Sound) {
            .stream = (AudioStream) {
                .buffer = 0,
                .sampleRate = 0,
                .sampleSize = 0,
                .channels = 0
            },
            .frameCount = 0
        };
        intern->stream = phpStream;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_sound_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_sound_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_sound_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_sound_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_sound_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_sound__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, stream, raylib\\AudioStream, 1)
    ZEND_ARG_TYPE_MASK(0, frameCount, IS_LONG, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Sound, __construct)
{
    zend_object *stream = NULL;
    php_raylib_audiostream_object *phpStream;

    zend_long frameCount;
    bool frameCount_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(stream, php_raylib_audiostream_ce)
        Z_PARAM_LONG_OR_NULL(frameCount, frameCount_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *intern = Z_SOUND_OBJ_P(ZEND_THIS);

    if (stream == NULL) {
        stream = php_raylib_audiostream_new_ex(php_raylib_audiostream_ce, NULL);
    }

    if (frameCount_is_null) {
        frameCount = 0;
    }

    phpStream = php_raylib_audiostream_fetch_object(stream);

    intern->stream = phpStream;

    intern->sound = (Sound) {
        .stream = (AudioStream) {
            .buffer = phpStream->audiostream.buffer,
            .sampleRate = phpStream->audiostream.sampleRate,
            .sampleSize = phpStream->audiostream.sampleSize,
            .channels = phpStream->audiostream.channels
        },
        .frameCount = frameCount
    };
}

static zend_object * php_raylib_sound_get_stream(php_raylib_sound_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->stream->std);
    return &obj->stream->std;
}
/* }}} */

static zend_long php_raylib_sound_get_framecount(php_raylib_sound_object *obj) /* {{{ */
{
    return (zend_long) obj->sound.frameCount;
}
/* }}} */

static int php_raylib_sound_set_stream(php_raylib_sound_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(newval);
    GC_ADDREF(&phpStream->std);
    GC_DELREF(&obj->stream->std);
    obj->stream = phpStream;

    return ret;
}
/* }}} */

static int php_raylib_sound_set_framecount(php_raylib_sound_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->sound.frameCount = 0;
        return ret;
    }

    obj->sound.frameCount = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_sound_methods[] = {
        PHP_ME(Sound, __construct, arginfo_sound__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_sound_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_sound_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_sound_object_handlers.offset = XtOffsetOf(php_raylib_sound_object, std);
    php_raylib_sound_object_handlers.free_obj = &php_raylib_sound_free_storage;
    php_raylib_sound_object_handlers.clone_obj = php_raylib_sound_clone;

    // Props
    php_raylib_sound_object_handlers.get_property_ptr_ptr = php_raylib_sound_get_property_ptr_ptr;
    php_raylib_sound_object_handlers.get_gc               = php_raylib_sound_get_gc;
    php_raylib_sound_object_handlers.get_properties       = php_raylib_sound_get_properties;
    php_raylib_sound_object_handlers.read_property	     = php_raylib_sound_read_property;
    php_raylib_sound_object_handlers.write_property       = php_raylib_sound_write_property;
    php_raylib_sound_object_handlers.has_property	     = php_raylib_sound_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Sound", php_raylib_sound_methods);
    php_raylib_sound_ce = zend_register_internal_class(&ce);
    php_raylib_sound_ce->create_object = php_raylib_sound_new;

    // Props
    zend_hash_init(&php_raylib_sound_prop_handlers, 0, NULL, php_raylib_sound_free_prop_handler, 1);
    php_raylib_sound_register_prop_handler(&php_raylib_sound_prop_handlers, "stream", php_raylib_sound_get_stream, php_raylib_sound_set_stream, NULL, NULL);
    php_raylib_sound_register_prop_handler(&php_raylib_sound_prop_handlers, "framecount", NULL, NULL, php_raylib_sound_get_framecount, php_raylib_sound_set_framecount);
}
