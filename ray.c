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

#include "vector3.h"

#include "ray.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_RAY_OBJECT_ID = 0;
static unsigned char RL_RAY_INIT = 0;
static const unsigned int RL_RAY_MAX_OBJECTS = 999999;

char* RL_Ray_Hash_Id(char *str, size_t size) {
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

struct RL_Ray* RL_Ray_Create() {
    //-- Create the initial data structures
    if (RL_RAY_INIT == 0) {
        RL_Ray_Object_List = (struct RL_Ray**) malloc(0);
        RL_Ray_Object_Map = hashmap_create();
        RL_RAY_INIT = 1;
    }

    //-- Create the container object
    struct RL_Ray* object = (struct RL_Ray*) malloc(sizeof(struct RL_Ray));
    object->id = RL_RAY_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_Ray_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Ray_Object_List = (struct RL_Ray**) realloc(RL_Ray_Object_List, RL_RAY_OBJECT_ID * sizeof(struct RL_Ray*));
    RL_Ray_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Ray_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Ray_Delete(struct RL_Ray* object, int index) {
    if (index < 0 || index >= RL_RAY_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Ray_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Ray_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Ray_Object_List[index], &RL_Ray_Object_List[index + 1], (RL_RAY_OBJECT_ID - index - 1) * sizeof(struct RL_Ray *));

    // Decrement the count and resize the array
    RL_RAY_OBJECT_ID--;
    RL_Ray_Object_List = (struct RL_Ray **)realloc(RL_Ray_Object_List, (RL_RAY_OBJECT_ID) * sizeof(struct RL_Ray *));
}

void RL_Ray_Free(struct RL_Ray* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib Ray PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_ray_object_handlers;

static HashTable php_raylib_ray_prop_handlers;

typedef zend_object * (*raylib_ray_read_vector3_t)(php_raylib_ray_object *obj);
typedef int (*raylib_ray_write_vector3_t)(php_raylib_ray_object *obj,  zval *value);

typedef struct _raylib_ray_prop_handler {
    raylib_ray_read_vector3_t read_vector3_func;
    raylib_ray_write_vector3_t write_vector3_func;
} raylib_ray_prop_handler;

static void php_raylib_ray_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_ray_read_vector3_t read_vector3_func,
                                                      raylib_ray_write_vector3_t write_vector3_func) /* {{{ */
{
    raylib_ray_prop_handler hnd;

    hnd.read_vector3_func = read_vector3_func;
    hnd.write_vector3_func = write_vector3_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_ray_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_ray_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_ray_property_reader(php_raylib_ray_object *obj, raylib_ray_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_vector3_func) {
        zend_object *ret = hnd->read_vector3_func(obj);
        ZVAL_OBJ(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_ray_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_ray_object *obj;
    zval *retval = NULL;
    raylib_ray_prop_handler *hnd = NULL;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_ray_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_ray_object *obj;
    zval *retval = NULL;
    raylib_ray_prop_handler *hnd = NULL;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_ray_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_ray_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_ray_object *obj;
    raylib_ray_prop_handler *hnd;

    obj = php_raylib_ray_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_vector3_func) {
        hnd->write_vector3_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_ray_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_ray_object *obj;
    raylib_ray_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_ray_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_ray_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_ray_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_ray_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_ray_object *obj;
    HashTable *props;
    raylib_ray_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_ray_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_ray_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_ray_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_ray_object *intern = php_raylib_ray_fetch_object(object);

    intern->ray->refCount--;
    if (intern->ray->refCount < 1) {
        RL_Ray_Free(intern->ray);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_ray_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_ray_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_ray_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_ray_object), ce);

    intern->prop_handler = &php_raylib_ray_prop_handlers;

    if (orig) {
        php_raylib_ray_object *other = php_raylib_ray_fetch_object(orig);

        php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(&other->position);
        php_raylib_vector3_object *phpDirection = Z_VECTOR3_OBJ_P(&other->direction);


        intern->ray->data = (Ray) {
            .position = (Vector3) {
                .x = other->ray->data.position.x,
                .y = other->ray->data.position.y,
                .z = other->ray->data.position.z
            },
            .direction = (Vector3) {
                .x = other->ray->data.direction.x,
                .y = other->ray->data.direction.y,
                .z = other->ray->data.direction.z
            }
        };

        ZVAL_OBJ_COPY(&intern->position, &phpPosition->std);

        ZVAL_OBJ_COPY(&intern->direction, &phpDirection->std);

    } else {
        zend_object *position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
        zend_object *direction = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);

        php_raylib_vector3_object *phpPosition = php_raylib_vector3_fetch_object(position);
        php_raylib_vector3_object *phpDirection = php_raylib_vector3_fetch_object(direction);

        intern->ray = RL_Ray_Create();
        intern->ray->data = (Ray) {
            .position = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            },
            .direction = (Vector3) {
                .x = 0,
                .y = 0,
                .z = 0
            }
        };

        ZVAL_OBJ_COPY(&intern->position, &phpPosition->std);

        ZVAL_OBJ_COPY(&intern->direction, &phpDirection->std);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_ray_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_ray_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_ray_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_ray_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_ray_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_ray__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, position, raylib\\Vector3, 1)
    ZEND_ARG_OBJ_INFO(0, direction, raylib\\Vector3, 1)
ZEND_END_ARG_INFO()
PHP_METHOD(Ray, __construct)
{
    zend_object *position = NULL;
    php_raylib_vector3_object *phpPosition;

    zend_object *direction = NULL;
    php_raylib_vector3_object *phpDirection;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(position, php_raylib_vector3_ce)
        Z_PARAM_OBJ_OF_CLASS_OR_NULL(direction, php_raylib_vector3_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *intern = Z_RAY_OBJ_P(ZEND_THIS);

    if (position == NULL) {
        position = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    if (direction == NULL) {
        direction = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    }

    phpPosition = php_raylib_vector3_fetch_object(position);
    phpDirection = php_raylib_vector3_fetch_object(direction);

    ZVAL_OBJ_COPY(&intern->position, &phpPosition->std);
    ZVAL_OBJ_COPY(&intern->direction, &phpDirection->std);

    intern->ray->data = (Ray) {
        .position = (Vector3) {
            .x = phpPosition->vector3->data.x,
            .y = phpPosition->vector3->data.y,
            .z = phpPosition->vector3->data.z
        },
        .direction = (Vector3) {
            .x = phpDirection->vector3->data.x,
            .y = phpDirection->vector3->data.y,
            .z = phpDirection->vector3->data.z
        }
    };
}

static zend_object * php_raylib_ray_get_position(php_raylib_ray_object *obj) /* {{{ */
{
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(&obj->position);

    phpPosition->vector3->refCount++;

    GC_ADDREF(&phpPosition->std);

    return &phpPosition->std;
}
/* }}} */

static zend_object * php_raylib_ray_get_direction(php_raylib_ray_object *obj) /* {{{ */
{
    php_raylib_vector3_object *phpDirection = Z_VECTOR3_OBJ_P(&obj->direction);

    phpDirection->vector3->refCount++;

    GC_ADDREF(&phpDirection->std);

    return &phpDirection->std;
}
/* }}} */

static int php_raylib_ray_set_position(php_raylib_ray_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *rl_vector3 = Z_VECTOR3_OBJ_P(newval);
    rl_vector3->vector3->refCount++;

    obj->position = *newval;

    return ret;
}
/* }}} */

static int php_raylib_ray_set_direction(php_raylib_ray_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector3_object *rl_vector3 = Z_VECTOR3_OBJ_P(newval);
    rl_vector3->vector3->refCount++;

    obj->direction = *newval;

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_ray_methods[] = {
        PHP_ME(Ray, __construct, arginfo_ray__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_ray_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_ray_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_ray_object_handlers.offset = XtOffsetOf(php_raylib_ray_object, std);
    php_raylib_ray_object_handlers.free_obj = &php_raylib_ray_free_storage;
    php_raylib_ray_object_handlers.clone_obj = php_raylib_ray_clone;

    // Props
    php_raylib_ray_object_handlers.get_property_ptr_ptr = php_raylib_ray_get_property_ptr_ptr;
    php_raylib_ray_object_handlers.get_gc               = php_raylib_ray_get_gc;
    php_raylib_ray_object_handlers.get_properties       = php_raylib_ray_get_properties;
    php_raylib_ray_object_handlers.read_property	     = php_raylib_ray_read_property;
    php_raylib_ray_object_handlers.write_property       = php_raylib_ray_write_property;
    php_raylib_ray_object_handlers.has_property	     = php_raylib_ray_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Ray", php_raylib_ray_methods);
    php_raylib_ray_ce = zend_register_internal_class(&ce);
    php_raylib_ray_ce->create_object = php_raylib_ray_new;

    // Props
    zend_hash_init(&php_raylib_ray_prop_handlers, 0, NULL, php_raylib_ray_free_prop_handler, 1);
    php_raylib_ray_register_prop_handler(&php_raylib_ray_prop_handlers, "position", php_raylib_ray_get_position, php_raylib_ray_set_position);
    php_raylib_ray_register_prop_handler(&php_raylib_ray_prop_handlers, "direction", php_raylib_ray_get_direction, php_raylib_ray_set_direction);
}
