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


#include "mesh.h"

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

typedef HashTable * (*raylib_mesh_read_unsigned_int_array_t)(php_raylib_mesh_object *obj);
typedef int (*raylib_mesh_write_unsigned_int_array_t)(php_raylib_mesh_object *obj,  zval *value);

/**
 * This is used to update internal object references
 * @param intern
 */
void php_raylib_mesh_update_intern(php_raylib_mesh_object *intern) {
}
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
    raylib_mesh_read_unsigned_int_array_t read_unsigned_int_array_func;
    raylib_mesh_write_unsigned_int_array_t write_unsigned_int_array_func;
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
                                                      raylib_mesh_read_unsigned_int_array_t read_unsigned_int_array_func,
                                                      raylib_mesh_write_unsigned_int_array_t write_unsigned_int_array_func) /* {{{ */
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
    hnd.read_unsigned_int_array_func = read_unsigned_int_array_func;
    hnd.write_unsigned_int_array_func = write_unsigned_int_array_func;

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
    else if (obj != NULL && hnd->read_unsigned_int_array_func) {
        ZVAL_ARR(rv, hnd->read_unsigned_int_array_func(obj));
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
    } else if (hnd && hnd->write_unsigned_int_array_func) {
        hnd->write_unsigned_int_array_func(obj, value);
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

        intern->mesh = (Mesh) {
            .vertexCount = other->mesh.vertexCount,
            .triangleCount = other->mesh.triangleCount,
            .vaoId = other->mesh.vaoId,
        };
    } else {
        intern->mesh = (Mesh) {
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
    ZEND_ARG_TYPE_MASK(0, vertexCount, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, triangleCount, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, vertices, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, texcoords, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, texcoords2, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, normals, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, tangents, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, colors, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, indices, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, animVertices, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, animNormals, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, boneIds, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, boneWeights, IS_DOUBLE, "0")
    ZEND_ARG_TYPE_MASK(0, vaoId, IS_LONG, "0")
    ZEND_ARG_TYPE_MASK(0, vboId, IS_LONG, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Mesh, __construct)
{
}

static zend_long php_raylib_mesh_get_vertexcount(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) obj->mesh.vertexCount;
}
/* }}} */

static zend_long php_raylib_mesh_get_trianglecount(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) obj->mesh.triangleCount;
}
/* }}} */

static HashTable * php_raylib_mesh_get_vertices(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_texcoords(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_texcoords2(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_normals(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_tangents(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_colors(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_indices(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_animvertices(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_animnormals(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_boneids(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static HashTable * php_raylib_mesh_get_boneweights(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static zend_long php_raylib_mesh_get_vaoid(php_raylib_mesh_object *obj) /* {{{ */
{
    return (zend_long) obj->mesh.vaoId;
}
/* }}} */

static HashTable * php_raylib_mesh_get_vboid(php_raylib_mesh_object *obj) /* {{{ */
{
    //TODO: Not yet supported
}
/* }}} */

static int php_raylib_mesh_set_vertexcount(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->mesh.vertexCount = 0;
        return ret;
    }

    obj->mesh.vertexCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_trianglecount(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->mesh.triangleCount = 0;
        return ret;
    }

    obj->mesh.triangleCount = (int) zval_get_long(newval);

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
        obj->mesh.vaoId = 0;
        return ret;
    }

    obj->mesh.vaoId = (unsigned int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_mesh_set_vboid(php_raylib_mesh_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    //TODO: Set Array Not yet supported

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
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vertexcount", php_raylib_mesh_get_vertexcount, php_raylib_mesh_set_vertexcount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "trianglecount", php_raylib_mesh_get_trianglecount, php_raylib_mesh_set_trianglecount, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vertices", NULL, NULL, php_raylib_mesh_get_vertices, php_raylib_mesh_set_vertices, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "texcoords", NULL, NULL, php_raylib_mesh_get_texcoords, php_raylib_mesh_set_texcoords, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "texcoords2", NULL, NULL, php_raylib_mesh_get_texcoords2, php_raylib_mesh_set_texcoords2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "normals", NULL, NULL, php_raylib_mesh_get_normals, php_raylib_mesh_set_normals, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "tangents", NULL, NULL, php_raylib_mesh_get_tangents, php_raylib_mesh_set_tangents, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "colors", NULL, NULL, NULL, NULL, php_raylib_mesh_get_colors, php_raylib_mesh_set_colors, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "indices", NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_indices, php_raylib_mesh_set_indices, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "animvertices", NULL, NULL, php_raylib_mesh_get_animvertices, php_raylib_mesh_set_animvertices, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "animnormals", NULL, NULL, php_raylib_mesh_get_animnormals, php_raylib_mesh_set_animnormals, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "boneids", NULL, NULL, NULL, NULL, php_raylib_mesh_get_boneids, php_raylib_mesh_set_boneids, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "boneweights", NULL, NULL, php_raylib_mesh_get_boneweights, php_raylib_mesh_set_boneweights, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vaoid", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_vaoid, php_raylib_mesh_set_vaoid, NULL, NULL);
    php_raylib_mesh_register_prop_handler(&php_raylib_mesh_prop_handlers, "vboid", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, php_raylib_mesh_get_vboid, php_raylib_mesh_set_vboid);
}
