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

#include "matrix.h"
#include "mesh.h"
#include "material.h"
#include "boneinfo.h"
#include "transform.h"

#include "model.h"

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

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_model_update_intern(php_raylib_model_object *intern) {
    intern->model.transform = intern->transform->matrix;
    //TODO: Support for pointers and arrays;
    //intern->model.meshes = intern->meshes->mesh;
    //TODO: Support for pointers and arrays;
    //intern->model.materials = intern->materials->material;
    //TODO: Support for pointers and arrays;
    //intern->model.bones = intern->bones->boneinfo;
    //TODO: Support for pointers and arrays;
    //intern->model.bindPose = intern->bindpose->transform;
}
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

        zend_object *transform = php_raylib_matrix_new_ex(php_raylib_matrix_ce, &other->transform->std);
        // meshes array not yet supported needs to generate a hash table!
        //zend_object *meshes = php_raylib_mesh_new_ex(php_raylib_mesh_ce, &other->meshes->std);
        // materials array not yet supported needs to generate a hash table!
        //zend_object *materials = php_raylib_material_new_ex(php_raylib_material_ce, &other->materials->std);
        // bones array not yet supported needs to generate a hash table!
        //zend_object *bones = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, &other->bones->std);
        // bindPose array not yet supported needs to generate a hash table!
        //zend_object *bindPose = php_raylib_transform_new_ex(php_raylib_transform_ce, &other->bindPose->std);

        php_raylib_matrix_object *phpTransform = php_raylib_matrix_fetch_object(transform);
        // meshes array not yet supported needs to generate a hash table!
        //php_raylib_mesh_object *phpMeshes = php_raylib_mesh_fetch_object(meshes);
        // materials array not yet supported needs to generate a hash table!
        //php_raylib_material_object *phpMaterials = php_raylib_material_fetch_object(materials);
        // bones array not yet supported needs to generate a hash table!
        //php_raylib_boneinfo_object *phpBones = php_raylib_boneinfo_fetch_object(bones);
        // bindPose array not yet supported needs to generate a hash table!
        //php_raylib_transform_object *phpBindPose = php_raylib_transform_fetch_object(bindPose);

        intern->model = (Model) {
            .transform = (Matrix) {
                .m0 = other->model.transform.m0,
                .m1 = other->model.transform.m1,
                .m2 = other->model.transform.m2,
                .m3 = other->model.transform.m3,
                .m4 = other->model.transform.m4,
                .m5 = other->model.transform.m5,
                .m6 = other->model.transform.m6,
                .m7 = other->model.transform.m7,
                .m8 = other->model.transform.m8,
                .m9 = other->model.transform.m9,
                .m10 = other->model.transform.m10,
                .m11 = other->model.transform.m11,
                .m12 = other->model.transform.m12,
                .m13 = other->model.transform.m13,
                .m14 = other->model.transform.m14,
                .m15 = other->model.transform.m15
            },
            .meshCount = other->model.meshCount,
            .materialCount = other->model.materialCount,
            .boneCount = other->model.boneCount,
        };

        intern->transform = phpTransform;
        //123TODO: support array and pointers
        //intern->meshes = phpMeshes;
        //123TODO: support array and pointers
        //intern->materials = phpMaterials;
        //123TODO: support array and pointers
        //intern->bones = phpBones;
        //123TODO: support array and pointers
        //intern->bindPose = phpBindPose;
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

        intern->model = (Model) {
            .transform = (Matrix) {
                .m0 = 0,
                .m1 = 0,
                .m2 = 0,
                .m3 = 0,
                .m4 = 0,
                .m5 = 0,
                .m6 = 0,
                .m7 = 0,
                .m8 = 0,
                .m9 = 0,
                .m10 = 0,
                .m11 = 0,
                .m12 = 0,
                .m13 = 0,
                .m14 = 0,
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
        intern->transform = phpTransform;
        // meshes array not yet supported needs to generate a hash table!
        //intern->meshes = phpMeshes;
        // materials array not yet supported needs to generate a hash table!
        //intern->materials = phpMaterials;
        // bones array not yet supported needs to generate a hash table!
        //intern->bones = phpBones;
        // bindPose array not yet supported needs to generate a hash table!
        //intern->bindPose = phpBindPose;
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_model__construct, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, transform, raylib\\Matrix, 1)
    ZEND_ARG_TYPE_MASK(0, meshCount, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, materialCount, IS_LONG, "0")
    ZEND_ARG_OBJ_INFO(0, meshes, raylib\\Mesh, 1)
    ZEND_ARG_OBJ_INFO(0, materials, raylib\\Material, 1)
    ZEND_ARG_TYPE_MASK(0, meshMaterial, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, boneCount, IS_LONG, "0")
    ZEND_ARG_OBJ_INFO(0, bones, raylib\\BoneInfo, 1)
    ZEND_ARG_OBJ_INFO(0, bindPose, raylib\\Transform, 1)
ZEND_END_ARG_INFO()
PHP_METHOD(Model, __construct)
{
}

static zend_object * php_raylib_model_get_transform(php_raylib_model_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->transform->std);
    return &obj->transform->std;
}
/* }}} */

static zend_long php_raylib_model_get_meshcount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) obj->model.meshCount;
}
/* }}} */

static zend_long php_raylib_model_get_materialcount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) obj->model.materialCount;
}
/* }}} */

static HashTable * php_raylib_model_get_meshes(php_raylib_model_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_model_get_materials(php_raylib_model_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_model_get_meshmaterial(php_raylib_model_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static zend_long php_raylib_model_get_bonecount(php_raylib_model_object *obj) /* {{{ */
{
    return (zend_long) obj->model.boneCount;
}
/* }}} */

static HashTable * php_raylib_model_get_bones(php_raylib_model_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_model_get_bindpose(php_raylib_model_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static int php_raylib_model_set_transform(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_matrix_object *phpTransform = Z_MATRIX_OBJ_P(newval);
    GC_ADDREF(&phpTransform->std);
    GC_DELREF(&obj->transform->std);
    obj->transform = phpTransform;

    return ret;
}
/* }}} */

static int php_raylib_model_set_meshcount(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->model.meshCount = 0;
        return ret;
    }

    obj->model.meshCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_model_set_materialcount(php_raylib_model_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->model.materialCount = 0;
        return ret;
    }

    obj->model.materialCount = (int) zval_get_long(newval);

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
        obj->model.boneCount = 0;
        return ret;
    }

    obj->model.boneCount = (int) zval_get_long(newval);

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
