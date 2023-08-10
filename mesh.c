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


#include "mesh.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_MESH_OBJECT_ID = 0;
static unsigned char RL_MESH_INIT = 0;
static const unsigned int RL_MESH_MAX_OBJECTS = 999999;

char* RL_Mesh_Hash_Id(char *str, size_t size) {
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

struct RL_Mesh* RL_Mesh_Create() {
    //-- Create the initial data structures
    if (RL_MESH_INIT == 0) {
        RL_Mesh_Object_List = (struct RL_Mesh**) malloc(0);
        RL_Mesh_Object_Map = hashmap_create();
        RL_MESH_INIT = 1;
    }

    //-- Create the container object
    struct RL_Mesh* object = (struct RL_Mesh*) malloc(sizeof(struct RL_Mesh));
    object->id = RL_MESH_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_Mesh_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = (Mesh) {0};
    object->type = RL_MESH_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Mesh_Object_List = (struct RL_Mesh**) realloc(RL_Mesh_Object_List, RL_MESH_OBJECT_ID * sizeof(struct RL_Mesh*));
    RL_Mesh_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Mesh_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Mesh_Delete(struct RL_Mesh* object, int index) {
    if (index < 0 || index >= RL_MESH_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Mesh_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Mesh_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Mesh_Object_List[index], &RL_Mesh_Object_List[index + 1], (RL_MESH_OBJECT_ID - index - 1) * sizeof(struct RL_Mesh *));

    // Decrement the count and resize the array
    RL_MESH_OBJECT_ID--;
    RL_Mesh_Object_List = (struct RL_Mesh **)realloc(RL_Mesh_Object_List, (RL_MESH_OBJECT_ID) * sizeof(struct RL_Mesh *));
}

void RL_Mesh_Free(struct RL_Mesh* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib Mesh PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_mesh_object_handlers;

static HashTable php_raylib_mesh_prop_handlers;

typedef zend_long (*raylib_mesh_read_int_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_int_t)(php_raylib_mesh_object *obj,  zval *value);

typedef HashTable * (*raylib_mesh_read_float_array_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_float_array_t)(php_raylib_mesh_object *obj,  zval *value);

typedef HashTable * (*raylib_mesh_read_unsigned_char_array_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_unsigned_char_array_t)(php_raylib_mesh_object *obj,  zval *value);

typedef HashTable * (*raylib_mesh_read_unsigned_short_array_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_unsigned_short_array_t)(php_raylib_mesh_object *obj,  zval *value);

typedef zend_long (*raylib_mesh_read_unsigned_int_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_unsigned_int_t)(php_raylib_mesh_object *obj,  zval *value);

typedef zend_long (*raylib_mesh_read_unsigned_int__t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_unsigned_int__t)(php_raylib_mesh_object *obj,  zval *value);

typedef struct _raylib_mesh_prop_handler {
    raylib_mesh_read_int_t read_int_func;
    raylib_mesh_write_int_t write_int_func;
    raylib_mesh_read_float_array_t read_float_array_func;
    raylib_mesh_write_float_array_t write_float_array_func;
    raylib_mesh_read_unsigned_char_array_t read_unsigned_char_array_func;
    raylib_mesh_write_unsigned_char_array_t write_unsigned_char_array_func;
    raylib_mesh_read_unsigned_short_array_t read_unsigned_short_array_func;
    raylib_mesh_write_unsigned_short_array_t write_unsigned_short_array_func;
    raylib_mesh_read_unsigned_int_t read_unsigned_int_func;
    raylib_mesh_write_unsigned_int_t write_unsigned_int_func;
    raylib_mesh_read_unsigned_int__t read_unsigned_int__func;
    raylib_mesh_write_unsigned_int__t write_unsigned_int__func;
} raylib_mesh_prop_handler;

static void php_raylib_mesh_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_mesh_read_int_t read_int_func,
                                                      raylib_mesh_write_int_t write_int_func,
                                                      raylib_mesh_read_float_array_t read_float_array_func,
                                                      raylib_mesh_write_float_array_t write_float_array_func,
                                                      raylib_mesh_read_unsigned_char_array_t read_unsigned_char_array_func,
                                                      raylib_mesh_write_unsigned_char_array_t write_unsigned_char_array_func,
                                                      raylib_mesh_read_unsigned_short_array_t read_unsigned_short_array_func,
                                                      raylib_mesh_write_unsigned_short_array_t write_unsigned_short_array_func,
                                                      raylib_mesh_read_unsigned_int_t read_unsigned_int_func,
                                                      raylib_mesh_write_unsigned_int_t write_unsigned_int_func,
                                                      raylib_mesh_read_unsigned_int__t read_unsigned_int__func,
                                                      raylib_mesh_write_unsigned_int__t write_unsigned_int__func) /* {{{ */
{
    raylib_mesh_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_float_array_func = read_float_array_func;
    hnd.write_float_array_func = write_float_array_func;
    hnd.read_unsigned_char_array_func = read_unsigned_char_array_func;
    hnd.write_unsigned_char_array_func = write_unsigned_char_array_func;
    hnd.read_unsigned_short_array_func = read_unsigned_short_array_func;
    hnd.write_unsigned_short_array_func = write_unsigned_short_array_func;
    hnd.read_unsigned_int_func = read_unsigned_int_func;
    hnd.write_unsigned_int_func = write_unsigned_int_func;
    hnd.read_unsigned_int__func = read_unsigned_int__func;
    hnd.write_unsigned_int__func = write_unsigned_int__func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_mesh_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_mesh_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_mesh_property_reader(php_raylib_mesh_object *obj, raylib_mesh_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }
    else if (obj != NULL && hnd->read_float_array_func) {
        ZVAL_ARR(rv, hnd->read_float_array_func(obj));
    }
    else if (obj != NULL && hnd->read_unsigned_char_array_func) {
        ZVAL_ARR(rv, hnd->read_unsigned_char_array_func(obj));
    }
    else if (obj != NULL && hnd->read_unsigned_short_array_func) {
        ZVAL_ARR(rv, hnd->read_unsigned_short_array_func(obj));
    }
    else if (obj != NULL && hnd->read_unsigned_int_func) {
        ZVAL_LONG(rv, hnd->read_unsigned_int_func(obj));
    }
    else if (obj != NULL && hnd->read_unsigned_int__func) {
        ZVAL_LONG(rv, hnd->read_unsigned_int__func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_mesh_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_mesh_object *obj;
    zval *retval = NULL;
    raylib_mesh_prop_handler *hnd = NULL;

    obj = php_raylib_mesh_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_mesh_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_mesh_object *obj;
    zval *retval = NULL;
    raylib_mesh_prop_handler *hnd = NULL;

    obj = php_raylib_mesh_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_mesh_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_mesh_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_mesh_object *obj;
    raylib_mesh_prop_handler *hnd;

    obj = php_raylib_mesh_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else if (hnd && hnd->write_float_array_func) {
        hnd->write_float_array_func(obj, value);
    } else if (hnd && hnd->write_unsigned_char_array_func) {
        hnd->write_unsigned_char_array_func(obj, value);
    } else if (hnd && hnd->write_unsigned_short_array_func) {
        hnd->write_unsigned_short_array_func(obj, value);
    } else if (hnd && hnd->write_unsigned_int_func) {
        hnd->write_unsigned_int_func(obj, value);
    } else if (hnd && hnd->write_unsigned_int__func) {
        hnd->write_unsigned_int__func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_mesh_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_mesh_object *obj;
    raylib_mesh_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_mesh_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_mesh_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_mesh_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_mesh_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_mesh_object *obj;
    HashTable *props;
    raylib_mesh_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_mesh_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_mesh_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_mesh_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_mesh_object *intern = php_raylib_mesh_fetch_object(object);

    intern->mesh->refCount--;
    if (intern->mesh->refCount < 1) {
        RL_Mesh_Free(intern->mesh);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_mesh_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_mesh_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_mesh_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_mesh_object), ce);

    intern->prop_handler = &php_raylib_mesh_prop_handlers;

    if (orig) {
        php_raylib_mesh_object *other = php_raylib_mesh_fetch_object(orig);

        *php_raylib_mesh_fetch_data(intern) = (Mesh) {
            .vertexCount = php_raylib_mesh_fetch_data(other)->vertexCount,
            .triangleCount = php_raylib_mesh_fetch_data(other)->triangleCount,
            .vaoId = php_raylib_mesh_fetch_data(other)->vaoId,
            .vboId = php_raylib_mesh_fetch_data(other)->vboId
        };
    } else {
        intern->mesh = RL_Mesh_Create();
        *php_raylib_mesh_fetch_data(intern) = (Mesh) {
            .vertexCount = 0,
            .triangleCount = 0,
            .vertices = 0,
            .texcoords = 0,
            .texcoords2 = 0,
            .normals = 0,
            .tangents = 0,
            .colors = 0,
            .indices = 0,
            .animVertices = 0,
            .animNormals = 0,
            .boneIds = 0,
            .boneWeights = 0,
            .vaoId = 0,
            .vboId = 0
        };

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_mesh_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_mesh_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_mesh_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_mesh_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_mesh_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_mesh__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, vertexCount, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, triangleCount, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, vertices, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, texcoords, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, texcoords2, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, normals, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, tangents, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, colors, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, indices, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, animVertices, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, animNormals, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, boneIds, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, boneWeights, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, vaoId, MAY_BE_LONG|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, vboId, MAY_BE_LONG|MAY_BE_NULL, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Mesh, __construct)
{
}

static zend_long php_raylib_mesh_get_vertexcount(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_mesh_fetch_data(obj)->vertexCount;
}
/* }}} */

static zend_long php_raylib_mesh_get_trianglecount(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_mesh_fetch_data(obj)->triangleCount;
}
/* }}} */

static HashTable * php_raylib_mesh_get_vertices(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zVertices;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zVertices, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->vertices != NULL) {
            add_next_index_double(&zVertices, objectData->vertices[i]);
        }
    }

    return Z_ARRVAL_P(&zVertices);
}
/* }}} */

static HashTable * php_raylib_mesh_get_texcoords(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zTexcoords;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zTexcoords, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->texcoords != NULL) {
            add_next_index_double(&zTexcoords, objectData->texcoords[i]);
        }
    }

    return Z_ARRVAL_P(&zTexcoords);
}
/* }}} */

static HashTable * php_raylib_mesh_get_texcoords2(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zTexcoords2;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zTexcoords2, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->texcoords2 != NULL) {
            add_next_index_double(&zTexcoords2, objectData->texcoords2[i]);
        }
    }

    return Z_ARRVAL_P(&zTexcoords2);
}
/* }}} */

static HashTable * php_raylib_mesh_get_normals(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zNormals;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zNormals, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->normals != NULL) {
            add_next_index_double(&zNormals, objectData->normals[i]);
        }
    }

    return Z_ARRVAL_P(&zNormals);
}
/* }}} */

static HashTable * php_raylib_mesh_get_tangents(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zTangents;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zTangents, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->tangents != NULL) {
            add_next_index_double(&zTangents, objectData->tangents[i]);
        }
    }

    return Z_ARRVAL_P(&zTangents);
}
/* }}} */

static HashTable * php_raylib_mesh_get_colors(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like unsigned char * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zColors;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zColors, objectData->vertexCount);

    // populate the array with unsignedchar
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->colors != NULL) {
            add_next_index_double(&zColors, objectData->colors[i]);
        }
    }

    return Z_ARRVAL_P(&zColors);
}
/* }}} */

static HashTable * php_raylib_mesh_get_indices(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like unsigned short * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zIndices;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zIndices, objectData->vertexCount);

    // populate the array with unsignedshort
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->indices != NULL) {
            add_next_index_double(&zIndices, objectData->indices[i]);
        }
    }

    return Z_ARRVAL_P(&zIndices);
}
/* }}} */

static HashTable * php_raylib_mesh_get_animvertices(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zAnimVertices;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zAnimVertices, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->animVertices != NULL) {
            add_next_index_double(&zAnimVertices, objectData->animVertices[i]);
        }
    }

    return Z_ARRVAL_P(&zAnimVertices);
}
/* }}} */

static HashTable * php_raylib_mesh_get_animnormals(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zAnimNormals;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zAnimNormals, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->animNormals != NULL) {
            add_next_index_double(&zAnimNormals, objectData->animNormals[i]);
        }
    }

    return Z_ARRVAL_P(&zAnimNormals);
}
/* }}} */

static HashTable * php_raylib_mesh_get_boneids(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like unsigned char * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zBoneIds;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zBoneIds, objectData->vertexCount);

    // populate the array with unsignedchar
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->boneIds != NULL) {
            add_next_index_double(&zBoneIds, objectData->boneIds[i]);
        }
    }

    return Z_ARRVAL_P(&zBoneIds);
}
/* }}} */

static HashTable * php_raylib_mesh_get_boneweights(php_raylib_mesh_object *obj) /* {{{ */
{
    // Direct access to c primitives like float * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zBoneWeights;
    unsigned int i;
    Mesh *objectData = php_raylib_mesh_fetch_data(obj);

    // Initialize Array
    array_init_size(&zBoneWeights, objectData->vertexCount);

    // populate the array with float
    for (i = 0; i < objectData->vertexCount; i++) {
        if (objectData != NULL && objectData->boneWeights != NULL) {
            add_next_index_double(&zBoneWeights, objectData->boneWeights[i]);
        }
    }

    return Z_ARRVAL_P(&zBoneWeights);
}
/* }}} */

static zend_long php_raylib_mesh_get_vaoid(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_mesh_fetch_data(obj)->vaoId;
}
/* }}} */

static zend_long php_raylib_mesh_get_vboid(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_mesh_fetch_data(obj)->vboId;
}
/* }}} */

static int php_raylib_mesh_set_vertexcount(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_mesh_fetch_data(obj)->vertexCount = 0;
        return ret;
    }

    php_raylib_mesh_fetch_data(obj)->vertexCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_trianglecount(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_mesh_fetch_data(obj)->triangleCount = 0;
        return ret;
    }

    php_raylib_mesh_fetch_data(obj)->triangleCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_vertices(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_texcoords(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_texcoords2(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_normals(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_tangents(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_colors(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_indices(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_animvertices(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_animnormals(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_boneids(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_boneweights(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_vaoid(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_mesh_fetch_data(obj)->vaoId = 0;
        return ret;
    }

    php_raylib_mesh_fetch_data(obj)->vaoId = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_vboid(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_mesh_fetch_data(obj)->vboId = 0;
        return ret;
    }

    php_raylib_mesh_fetch_data(obj)->vboId = (unsigned int *) zval_get_long(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_mesh_methods[] = {
        PHP_ME(Mesh, __construct, arginfo_mesh__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_mesh_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_mesh_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_mesh_object_handlers.offset = XtOffsetOf(php_raylib_mesh_object, std);
    php_raylib_mesh_object_handlers.free_obj = &php_raylib_mesh_free_storage;
    php_raylib_mesh_object_handlers.clone_obj = php_raylib_mesh_clone;

    // Props
    php_raylib_mesh_object_handlers.get_property_ptr_ptr = php_raylib_mesh_get_property_ptr_ptr;
    php_raylib_mesh_object_handlers.get_gc               = php_raylib_mesh_get_gc;
    php_raylib_mesh_object_handlers.get_properties       = php_raylib_mesh_get_properties;
    php_raylib_mesh_object_handlers.read_property	     = php_raylib_mesh_read_property;
    php_raylib_mesh_object_handlers.write_property       = php_raylib_mesh_write_property;
    php_raylib_mesh_object_handlers.has_property	     = php_raylib_mesh_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Mesh", php_raylib_mesh_methods);
    php_raylib_mesh_ce = zend_register_internal_class(&ce);
    php_raylib_mesh_ce->create_object = php_raylib_mesh_new;

    // Props
    zend_hash_init(&php_raylib_mesh_prop_handlers, 0, NULL, php_raylib_mesh_free_prop_handler, 1);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vertexCount", php_raylib_mesh_get_vertexcount, php_raylib_mesh_set_vertexcount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "triangleCount", php_raylib_mesh_get_trianglecount, php_raylib_mesh_set_trianglecount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vertices", NULL, NULL, php_raylib_mesh_get_vertices, php_raylib_mesh_set_vertices, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "texcoords", NULL, NULL, php_raylib_mesh_get_texcoords, php_raylib_mesh_set_texcoords, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "texcoords2", NULL, NULL, php_raylib_mesh_get_texcoords2, php_raylib_mesh_set_texcoords2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "normals", NULL, NULL, php_raylib_mesh_get_normals, php_raylib_mesh_set_normals, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "tangents", NULL, NULL, php_raylib_mesh_get_tangents, php_raylib_mesh_set_tangents, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "colors", NULL, NULL, NULL, NULL, php_raylib_mesh_get_colors, php_raylib_mesh_set_colors, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "indices", NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_indices, php_raylib_mesh_set_indices, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "animVertices", NULL, NULL, php_raylib_mesh_get_animvertices, php_raylib_mesh_set_animvertices, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "animNormals", NULL, NULL, php_raylib_mesh_get_animnormals, php_raylib_mesh_set_animnormals, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "boneIds", NULL, NULL, NULL, NULL, php_raylib_mesh_get_boneids, php_raylib_mesh_set_boneids, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "boneWeights", NULL, NULL, php_raylib_mesh_get_boneweights, php_raylib_mesh_set_boneweights, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vaoId", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_vaoid, php_raylib_mesh_set_vaoid, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vboId", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_vboid, php_raylib_mesh_set_vboid);
}
