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

#include "rectangle.h"

#include "npatchinfo.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_NPATCHINFO_OBJECT_ID = 0;
static unsigned char RL_NPATCHINFO_INIT = 0;
static const unsigned int RL_NPATCHINFO_MAX_OBJECTS = 999999;

char* RL_NPatchInfo_Hash_Id(char *str, size_t size) {
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

struct RL_NPatchInfo* RL_NPatchInfo_Create() {
    //-- Create the initial data structures
    if (RL_NPATCHINFO_INIT == 0) {
        RL_NPatchInfo_Object_List = (struct RL_NPatchInfo**) malloc(0);
        RL_NPatchInfo_Object_Map = hashmap_create();
        RL_NPATCHINFO_INIT = 1;
    }

    //-- Create the container object
    struct RL_NPatchInfo* object = (struct RL_NPatchInfo*) malloc(sizeof(struct RL_NPatchInfo));
    object->id = RL_NPATCHINFO_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_NPatchInfo_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_NPatchInfo_Object_List = (struct RL_NPatchInfo**) realloc(RL_NPatchInfo_Object_List, RL_NPATCHINFO_OBJECT_ID * sizeof(struct RL_NPatchInfo*));
    RL_NPatchInfo_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_NPatchInfo_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_NPatchInfo_Delete(struct RL_NPatchInfo* object, int index) {
    if (index < 0 || index >= RL_NPATCHINFO_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_NPatchInfo_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_NPatchInfo_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_NPatchInfo_Object_List[index], &RL_NPatchInfo_Object_List[index + 1], (RL_NPATCHINFO_OBJECT_ID - index - 1) * sizeof(struct RL_NPatchInfo *));

    // Decrement the count and resize the array
    RL_NPATCHINFO_OBJECT_ID--;
    RL_NPatchInfo_Object_List = (struct RL_NPatchInfo **)realloc(RL_NPatchInfo_Object_List, (RL_NPATCHINFO_OBJECT_ID) * sizeof(struct RL_NPatchInfo *));
}

void RL_NPatchInfo_Free(struct RL_NPatchInfo* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib NPatchInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_npatchinfo_object_handlers;

static HashTable php_raylib_npatchinfo_prop_handlers;

typedef zend_object * (*raylib_npatchinfo_read_rectangle_t)(php_raylib_npatchinfo_object *obj);
typedef int (*raylib_npatchinfo_write_rectangle_t)(php_raylib_npatchinfo_object *obj,  zval *value);

typedef zend_long (*raylib_npatchinfo_read_int_t)(php_raylib_npatchinfo_object *obj);
typedef int (*raylib_npatchinfo_write_int_t)(php_raylib_npatchinfo_object *obj,  zval *value);

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

    intern->npatchinfo->refCount--;
    if (intern->npatchinfo->refCount < 1) {
        RL_NPatchInfo_Free(intern->npatchinfo);
    }

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

        php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(&other->source);


        intern->npatchinfo->data = (NPatchInfo) {
            .source = (Rectangle) {
                .x = other->npatchinfo->data.source.x,
                .y = other->npatchinfo->data.source.y,
                .width = other->npatchinfo->data.source.width,
                .height = other->npatchinfo->data.source.height
            },
            .left = other->npatchinfo->data.left,
            .top = other->npatchinfo->data.top,
            .right = other->npatchinfo->data.right,
            .bottom = other->npatchinfo->data.bottom,
            .layout = other->npatchinfo->data.layout
        };

        ZVAL_OBJ_COPY(&intern->source, &phpSource->std);

    } else {
        zend_object *source = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);

        php_raylib_rectangle_object *phpSource = php_raylib_rectangle_fetch_object(source);

        intern->npatchinfo = RL_NPatchInfo_Create();
        intern->npatchinfo->data = (NPatchInfo) {
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

        ZVAL_OBJ_COPY(&intern->source, &phpSource->std);

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

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_npatchinfo__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, source, raylib\\Rectangle, 1)
    ZEND_ARG_TYPE_MASK(0, left, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, top, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, right, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, bottom, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, layout, MAY_BE_LONG|MAY_BE_NULL, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(NPatchInfo, __construct)
{
    zend_object *source = NULL;
    php_raylib_rectangle_object *phpSource;

    zend_long left;
    bool left_is_null = 1;

    zend_long top;
    bool top_is_null = 1;

    zend_long right;
    bool right_is_null = 1;

    zend_long bottom;
    bool bottom_is_null = 1;

    zend_long layout;
    bool layout_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 6)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(source, php_raylib_rectangle_ce)
        Z_PARAM_LONG_OR_NULL(left, left_is_null)
        Z_PARAM_LONG_OR_NULL(top, top_is_null)
        Z_PARAM_LONG_OR_NULL(right, right_is_null)
        Z_PARAM_LONG_OR_NULL(bottom, bottom_is_null)
        Z_PARAM_LONG_OR_NULL(layout, layout_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_npatchinfo_object *intern = Z_NPATCHINFO_OBJ_P(ZEND_THIS);

    if (source == NULL) {
        source = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);
    }

    if (left_is_null) {
        left = 0;
    }

    if (top_is_null) {
        top = 0;
    }

    if (right_is_null) {
        right = 0;
    }

    if (bottom_is_null) {
        bottom = 0;
    }

    if (layout_is_null) {
        layout = 0;
    }

    phpSource = php_raylib_rectangle_fetch_object(source);

    ZVAL_OBJ_COPY(&intern->source, &phpSource->std);

    intern->npatchinfo->data = (NPatchInfo) {
        .source = (Rectangle) {
            .x = phpSource->rectangle->data.x,
            .y = phpSource->rectangle->data.y,
            .width = phpSource->rectangle->data.width,
            .height = phpSource->rectangle->data.height
        },
        .left = (int) left,
        .top = (int) top,
        .right = (int) right,
        .bottom = (int) bottom,
        .layout = (int) layout
    };
}

static zend_object * php_raylib_npatchinfo_get_source(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(&obj->source);

    phpSource->rectangle->refCount++;

    GC_ADDREF(&phpSource->std);

    return &phpSource->std;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_left(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo->data.left;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_top(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo->data.top;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_right(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo->data.right;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_bottom(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo->data.bottom;
}
/* }}} */

static zend_long php_raylib_npatchinfo_get_layout(php_raylib_npatchinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->npatchinfo->data.layout;
}
/* }}} */

static int php_raylib_npatchinfo_set_source(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_rectangle_object *rl_rectangle = Z_RECTANGLE_OBJ_P(newval);
    rl_rectangle->rectangle->refCount++;

    obj->source = *newval;

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_left(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo->data.left = 0;
        return ret;
    }

    obj->npatchinfo->data.left = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_top(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo->data.top = 0;
        return ret;
    }

    obj->npatchinfo->data.top = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_right(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo->data.right = 0;
        return ret;
    }

    obj->npatchinfo->data.right = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_bottom(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo->data.bottom = 0;
        return ret;
    }

    obj->npatchinfo->data.bottom = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_npatchinfo_set_layout(php_raylib_npatchinfo_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->npatchinfo->data.layout = 0;
        return ret;
    }

    obj->npatchinfo->data.layout = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_npatchinfo_methods[] = {
        PHP_ME(NPatchInfo, __construct, arginfo_npatchinfo__construct, ZEND_ACC_PUBLIC)
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
    INIT_NS_CLASS_ENTRY(ce, "raylib", "NPatchInfo", php_raylib_npatchinfo_methods);
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
