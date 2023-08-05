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

#include "matrix.h"
#include "mesh.h"
#include "material.h"
#include "boneinfo.h"
#include "transform.h"

#include "model.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_MODEL_OBJECT_ID = 0;
static unsigned char RL_MODEL_INIT = 0;
static const unsigned int RL_MODEL_MAX_OBJECTS = 999999;

char* RL_Model_Hash_Id(char *str, size_t size) {
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

struct RL_Model* RL_Model_Create() {
    //-- Create the initial data structures
    if (RL_MODEL_INIT == 0) {
        RL_Model_Object_List = (struct RL_Model**) malloc(0);
        RL_Model_Object_Map = hashmap_create();
        RL_MODEL_INIT = 1;
    }

    //-- Create the container object
    struct RL_Model* object = (struct RL_Model*) malloc(sizeof(struct RL_Model));
    object->id = RL_MODEL_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_Model_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->data.v = ( Model) {};
    object->type = RL_MODEL_IS_VALUE;
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Model_Object_List = (struct RL_Model**) realloc(RL_Model_Object_List, RL_MODEL_OBJECT_ID * sizeof(struct RL_Model*));
    RL_Model_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Model_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Model_Delete(struct RL_Model* object, int index) {
    if (index < 0 || index >= RL_MODEL_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Model_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Model_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Model_Object_List[index], &RL_Model_Object_List[index + 1], (RL_MODEL_OBJECT_ID - index - 1) * sizeof(struct RL_Model *));

    // Decrement the count and resize the array
    RL_MODEL_OBJECT_ID--;
    RL_Model_Object_List = (struct RL_Model **)realloc(RL_Model_Object_List, (RL_MODEL_OBJECT_ID) * sizeof(struct RL_Model *));
}

void RL_Model_Free(struct RL_Model* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib Model PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_model_object_handlers;

static HashTable php_raylib_model_prop_handlers;

typedef zend_object * (*raylib_model_read_matrix_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_matrix_t)(php_raylib_model_object *obj,  zval *value);

typedef zend_long (*raylib_model_read_int_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_int_t)(php_raylib_model_object *obj,  zval *value);

typedef HashTable * (*raylib_model_read_mesh_array_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_mesh_array_t)(php_raylib_model_object *obj,  zval *value);

typedef HashTable * (*raylib_model_read_material_array_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_material_array_t)(php_raylib_model_object *obj,  zval *value);

typedef HashTable * (*raylib_model_read_int_array_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_int_array_t)(php_raylib_model_object *obj,  zval *value);

typedef HashTable * (*raylib_model_read_boneinfo_array_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_boneinfo_array_t)(php_raylib_model_object *obj,  zval *value);

typedef HashTable * (*raylib_model_read_transform_array_t)(php_raylib_model_object *obj);
typedef int (*raylib_model_write_transform_array_t)(php_raylib_model_object *obj,  zval *value);

typedef struct _raylib_model_prop_handler {
    raylib_model_read_matrix_t read_matrix_func;
    raylib_model_write_matrix_t write_matrix_func;
    raylib_model_read_int_t read_int_func;
    raylib_model_write_int_t write_int_func;
    raylib_model_read_mesh_array_t read_mesh_array_func;
    raylib_model_write_mesh_array_t write_mesh_array_func;
    raylib_model_read_material_array_t read_material_array_func;
    raylib_model_write_material_array_t write_material_array_func;
    raylib_model_read_int_array_t read_int_array_func;
    raylib_model_write_int_array_t write_int_array_func;
    raylib_model_read_boneinfo_array_t read_boneinfo_array_func;
    raylib_model_write_boneinfo_array_t write_boneinfo_array_func;
    raylib_model_read_transform_array_t read_transform_array_func;
    raylib_model_write_transform_array_t write_transform_array_func;
} raylib_model_prop_handler;

static void php_raylib_model_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_model_read_matrix_t read_matrix_func,
                                                      raylib_model_write_matrix_t write_matrix_func,
                                                      raylib_model_read_int_t read_int_func,
                                                      raylib_model_write_int_t write_int_func,
                                                      raylib_model_read_mesh_array_t read_mesh_array_func,
                                                      raylib_model_write_mesh_array_t write_mesh_array_func,
                                                      raylib_model_read_material_array_t read_material_array_func,
                                                      raylib_model_write_material_array_t write_material_array_func,
                                                      raylib_model_read_int_array_t read_int_array_func,
                                                      raylib_model_write_int_array_t write_int_array_func,
                                                      raylib_model_read_boneinfo_array_t read_boneinfo_array_func,
                                                      raylib_model_write_boneinfo_array_t write_boneinfo_array_func,
                                                      raylib_model_read_transform_array_t read_transform_array_func,
                                                      raylib_model_write_transform_array_t write_transform_array_func) /* {{{ */
{
    raylib_model_prop_handler hnd;

    hnd.read_matrix_func = read_matrix_func;
    hnd.write_matrix_func = write_matrix_func;
    hnd.read_int_func = read_int_func;
    hnd.write_int_func = write_int_func;
    hnd.read_mesh_array_func = read_mesh_array_func;
    hnd.write_mesh_array_func = write_mesh_array_func;
    hnd.read_material_array_func = read_material_array_func;
    hnd.write_material_array_func = write_material_array_func;
    hnd.read_int_array_func = read_int_array_func;
    hnd.write_int_array_func = write_int_array_func;
    hnd.read_boneinfo_array_func = read_boneinfo_array_func;
    hnd.write_boneinfo_array_func = write_boneinfo_array_func;
    hnd.read_transform_array_func = read_transform_array_func;
    hnd.write_transform_array_func = write_transform_array_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_model_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_model_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_model_property_reader(php_raylib_model_object *obj, raylib_model_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_matrix_func) {
        zend_object *ret = hnd->read_matrix_func(obj);
        ZVAL_OBJ(rv, ret);
    }
    else if (obj != NULL && hnd->read_int_func) {
        ZVAL_LONG(rv, hnd->read_int_func(obj));
    }
    else if (obj != NULL && hnd->read_mesh_array_func) {
        HashTable *ret = hnd->read_mesh_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_material_array_func) {
        HashTable *ret = hnd->read_material_array_func(obj);
        ZVAL_ARR(rv, ret);
    }
    else if (obj != NULL && hnd->read_int_array_func) {
        ZVAL_ARR(rv, hnd->read_int_array_func(obj));
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

static zval *php_raylib_model_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_model_object *obj;
    zval *retval = NULL;
    raylib_model_prop_handler *hnd = NULL;

    obj = php_raylib_model_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_model_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_model_object *obj;
    zval *retval = NULL;
    raylib_model_prop_handler *hnd = NULL;

    obj = php_raylib_model_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_model_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_model_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_model_object *obj;
    raylib_model_prop_handler *hnd;

    obj = php_raylib_model_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_matrix_func) {
        hnd->write_matrix_func(obj, value);
    } else if (hnd && hnd->write_int_func) {
        hnd->write_int_func(obj, value);
    } else if (hnd && hnd->write_mesh_array_func) {
        hnd->write_mesh_array_func(obj, value);
    } else if (hnd && hnd->write_material_array_func) {
        hnd->write_material_array_func(obj, value);
    } else if (hnd && hnd->write_int_array_func) {
        hnd->write_int_array_func(obj, value);
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

static int php_raylib_model_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_model_object *obj;
    raylib_model_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_model_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_model_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_model_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_model_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_model_object *obj;
    HashTable *props;
    raylib_model_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_model_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_model_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_model_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_model_object *intern = php_raylib_model_fetch_object(object);

    intern->model->refCount--;
    if (intern->model->refCount < 1) {
        RL_Model_Free(intern->model);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_model_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_model_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_model_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_model_object), ce);

    intern->prop_handler = &php_raylib_model_prop_handlers;

    if (orig) {
        php_raylib_model_object *other = php_raylib_model_fetch_object(orig);

        php_raylib_matrix_object *phpTransform = Z_MATRIX_OBJ_P(&other->transform);
        // meshes array not yet supported needs to generate a hash table!
        //zend_object *meshes = php_raylib_mesh_new_ex(php_raylib_mesh_ce, &other->meshes->std);
        // materials array not yet supported needs to generate a hash table!
        //zend_object *materials = php_raylib_material_new_ex(php_raylib_material_ce, &other->materials->std);
        // bones array not yet supported needs to generate a hash table!
        //zend_object *bones = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, &other->bones->std);
        // bindPose array not yet supported needs to generate a hash table!
        //zend_object *bindPose = php_raylib_transform_new_ex(php_raylib_transform_ce, &other->bindPose->std);

        // meshes array not yet supported needs to generate a hash table!
        //php_raylib_mesh_object *phpMeshes = php_raylib_mesh_fetch_object(meshes);
        // materials array not yet supported needs to generate a hash table!
        //php_raylib_material_object *phpMaterials = php_raylib_material_fetch_object(materials);
        // bones array not yet supported needs to generate a hash table!
        //php_raylib_boneinfo_object *phpBones = php_raylib_boneinfo_fetch_object(bones);
        // bindPose array not yet supported needs to generate a hash table!
        //php_raylib_transform_object *phpBindPose = php_raylib_transform_fetch_object(bindPose);

        *php_raylib_model_fetch_data(intern) = (Model) {
            .transform = (Matrix) {
                .m0 = php_raylib_model_fetch_data(other)->transform.m0,
                .m4 = php_raylib_model_fetch_data(other)->transform.m4,
                .m8 = php_raylib_model_fetch_data(other)->transform.m8,
                .m12 = php_raylib_model_fetch_data(other)->transform.m12,
                .m1 = php_raylib_model_fetch_data(other)->transform.m1,
                .m5 = php_raylib_model_fetch_data(other)->transform.m5,
                .m9 = php_raylib_model_fetch_data(other)->transform.m9,
                .m13 = php_raylib_model_fetch_data(other)->transform.m13,
                .m2 = php_raylib_model_fetch_data(other)->transform.m2,
                .m6 = php_raylib_model_fetch_data(other)->transform.m6,
                .m10 = php_raylib_model_fetch_data(other)->transform.m10,
                .m14 = php_raylib_model_fetch_data(other)->transform.m14,
                .m3 = php_raylib_model_fetch_data(other)->transform.m3,
                .m7 = php_raylib_model_fetch_data(other)->transform.m7,
                .m11 = php_raylib_model_fetch_data(other)->transform.m11,
                .m15 = php_raylib_model_fetch_data(other)->transform.m15
            },
            .meshCount = php_raylib_model_fetch_data(other)->meshCount,
            .materialCount = php_raylib_model_fetch_data(other)->materialCount,
            .boneCount = php_raylib_model_fetch_data(other)->boneCount,
        };

        ZVAL_OBJ_COPY(&intern->transform, &phpTransform->std);

        HashTable *meshes_hash;
        ALLOC_HASHTABLE(meshes_hash);
        zend_hash_init(meshes_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->meshes)), NULL, NULL, 0);
        zend_hash_copy(meshes_hash, Z_ARRVAL_P(&other->meshes), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->meshes, meshes_hash);

        HashTable *materials_hash;
        ALLOC_HASHTABLE(materials_hash);
        zend_hash_init(materials_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->materials)), NULL, NULL, 0);
        zend_hash_copy(materials_hash, Z_ARRVAL_P(&other->materials), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->materials, materials_hash);

        HashTable *bones_hash;
        ALLOC_HASHTABLE(bones_hash);
        zend_hash_init(bones_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->bones)), NULL, NULL, 0);
        zend_hash_copy(bones_hash, Z_ARRVAL_P(&other->bones), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->bones, bones_hash);

        HashTable *bindPose_hash;
        ALLOC_HASHTABLE(bindPose_hash);
        zend_hash_init(bindPose_hash, zend_hash_num_elements(Z_ARRVAL_P(&other->bindpose)), NULL, NULL, 0);
        zend_hash_copy(bindPose_hash, Z_ARRVAL_P(&other->bindpose), (copy_ctor_func_t) zval_add_ref);
        ZVAL_ARR(&intern->bindpose, bindPose_hash);

    } else {
        zend_object *transform = php_raylib_matrix_new_ex(php_raylib_matrix_ce, NULL);
        // meshes array not yet supported needs to generate a hash table!
        //zend_object *meshes = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
        // materials array not yet supported needs to generate a hash table!
        //zend_object *materials = php_raylib_material_new_ex(php_raylib_material_ce, NULL);
        // bones array not yet supported needs to generate a hash table!
        //zend_object *bones = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, NULL);
        // bindPose array not yet supported needs to generate a hash table!
        //zend_object *bindPose = php_raylib_transform_new_ex(php_raylib_transform_ce, NULL);

        php_raylib_matrix_object *phpTransform = php_raylib_matrix_fetch_object(transform);
        // meshes array not yet supported needs to generate a hash table!
        //php_raylib_mesh_object *phpMeshes = php_raylib_mesh_fetch_object(meshes);
        // materials array not yet supported needs to generate a hash table!
        //php_raylib_material_object *phpMaterials = php_raylib_material_fetch_object(materials);
        // bones array not yet supported needs to generate a hash table!
        //php_raylib_boneinfo_object *phpBones = php_raylib_boneinfo_fetch_object(bones);
        // bindPose array not yet supported needs to generate a hash table!
        //php_raylib_transform_object *phpBindPose = php_raylib_transform_fetch_object(bindPose);

        intern->model = RL_Model_Create();
        *php_raylib_model_fetch_data(intern) = (Model) {
            .transform = (Matrix) {
                .m0 = 0,
                .m4 = 0,
                .m8 = 0,
                .m12 = 0,
                .m1 = 0,
                .m5 = 0,
                .m9 = 0,
                .m13 = 0,
                .m2 = 0,
                .m6 = 0,
                .m10 = 0,
                .m14 = 0,
                .m3 = 0,
                .m7 = 0,
                .m11 = 0,
                .m15 = 0
            },
            .meshCount = 0,
            .materialCount = 0,
            // .meshes is an array and not yet supported via constructor
            // .materials is an array and not yet supported via constructor
            .meshMaterial = 0,
            .boneCount = 0,
            // .bones is an array and not yet supported via constructor
            // .bindPose is an array and not yet supported via constructor
        };

        ZVAL_OBJ_COPY(&intern->transform, &phpTransform->std);

        HashTable *meshes_hash;
        ALLOC_HASHTABLE(meshes_hash);
        zend_hash_init(meshes_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->meshes, meshes_hash);

        HashTable *materials_hash;
        ALLOC_HASHTABLE(materials_hash);
        zend_hash_init(materials_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->materials, materials_hash);

        HashTable *bones_hash;
        ALLOC_HASHTABLE(bones_hash);
        zend_hash_init(bones_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->bones, bones_hash);

        HashTable *bindPose_hash;
        ALLOC_HASHTABLE(bindPose_hash);
        zend_hash_init(bindPose_hash, 0, NULL, NULL, 0);
        ZVAL_ARR(&intern->bindpose, bindPose_hash);

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_model_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_model_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_model_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_model_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_model_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_model__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Model, __construct)
{
}

static zend_object * php_raylib_model_get_transform(php_raylib_model_object *obj) /* {{{ */
{
    php_raylib_matrix_object *phpTransform = Z_MATRIX_OBJ_P(&obj->transform);

    phpTransform->matrix->refCount++;

    GC_ADDREF(&phpTransform->std);

    return &phpTransform->std;
}
/* }}} */

static zend_long php_raylib_model_get_meshcount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_model_fetch_data(obj)->meshCount;
}
/* }}} */

static zend_long php_raylib_model_get_materialcount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_model_fetch_data(obj)->materialCount;
}
/* }}} */

static HashTable * php_raylib_model_get_meshes(php_raylib_model_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->meshes);
}
/* }}} */

static HashTable * php_raylib_model_get_materials(php_raylib_model_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->materials);
}
/* }}} */

static HashTable * php_raylib_model_get_meshmaterial(php_raylib_model_object *obj) /* {{{ */
{
    // Direct access to c primitives like int * is not possible with
    // PHP arrays, need to copy on the fly

    // Create zval to hold array
    zval zMeshMaterial;
    unsigned int i;
    Model *objectData = php_raylib_model_fetch_data(obj);

    // Initialize Array
    array_init_size(&zMeshMaterial, objectData->materialCount);

    // populate the array with int
    for (i = 0; i < objectData->materialCount; i++) {
        if (objectData != NULL && objectData->meshMaterial != NULL) {
            add_next_index_double(&zMeshMaterial, objectData->meshMaterial[i]);
        }
    }

    return Z_ARRVAL_P(&zMeshMaterial);
}
/* }}} */

static zend_long php_raylib_model_get_bonecount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) php_raylib_model_fetch_data(obj)->boneCount;
}
/* }}} */

static HashTable * php_raylib_model_get_bones(php_raylib_model_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->bones);
}
/* }}} */

static HashTable * php_raylib_model_get_bindpose(php_raylib_model_object *obj) /* {{{ */
{
    return Z_ARRVAL_P(&obj->bindpose);
}
/* }}} */

static int php_raylib_model_set_transform(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_matrix_object *rl_matrix = Z_MATRIX_OBJ_P(newval);
    rl_matrix->matrix->refCount++;

    obj->transform = *newval;

    return ret;
}
/* }}} */

static int php_raylib_model_set_meshcount(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_model_fetch_data(obj)->meshCount = 0;
        return ret;
    }

    php_raylib_model_fetch_data(obj)->meshCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_model_set_materialcount(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_model_fetch_data(obj)->materialCount = 0;
        return ret;
    }

    php_raylib_model_fetch_data(obj)->materialCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_model_set_meshes(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_model_set_materials(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_model_set_meshmaterial(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_model_set_bonecount(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        php_raylib_model_fetch_data(obj)->boneCount = 0;
        return ret;
    }

    php_raylib_model_fetch_data(obj)->boneCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_model_set_bones(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

static int php_raylib_model_set_bindpose(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_model_methods[] = {
        PHP_ME(Model, __construct, arginfo_model__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_model_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_model_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_model_object_handlers.offset = XtOffsetOf(php_raylib_model_object, std);
    php_raylib_model_object_handlers.free_obj = &php_raylib_model_free_storage;
    php_raylib_model_object_handlers.clone_obj = php_raylib_model_clone;

    // Props
    php_raylib_model_object_handlers.get_property_ptr_ptr = php_raylib_model_get_property_ptr_ptr;
    php_raylib_model_object_handlers.get_gc               = php_raylib_model_get_gc;
    php_raylib_model_object_handlers.get_properties       = php_raylib_model_get_properties;
    php_raylib_model_object_handlers.read_property	     = php_raylib_model_read_property;
    php_raylib_model_object_handlers.write_property       = php_raylib_model_write_property;
    php_raylib_model_object_handlers.has_property	     = php_raylib_model_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Model", php_raylib_model_methods);
    php_raylib_model_ce = zend_register_internal_class(&ce);
    php_raylib_model_ce->create_object = php_raylib_model_new;

    // Props
    zend_hash_init(&php_raylib_model_prop_handlers, 0, NULL, php_raylib_model_free_prop_handler, 1);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "transform", php_raylib_model_get_transform, php_raylib_model_set_transform, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "meshcount", NULL, NULL, php_raylib_model_get_meshcount, php_raylib_model_set_meshcount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "materialcount", NULL, NULL, php_raylib_model_get_materialcount, php_raylib_model_set_materialcount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "meshes", NULL, NULL, NULL, NULL, php_raylib_model_get_meshes, php_raylib_model_set_meshes, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "materials", NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_model_get_materials, php_raylib_model_set_materials, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "meshmaterial", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_model_get_meshmaterial, php_raylib_model_set_meshmaterial, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "bonecount", NULL, NULL, php_raylib_model_get_bonecount, php_raylib_model_set_bonecount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "bones", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_model_get_bones, php_raylib_model_set_bones, NULL, NULL);
    php_raylib_model_register_prop_handler(&php_raylib_model_prop_handlers, "bindpose", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_model_get_bindpose, php_raylib_model_set_bindpose);
}
