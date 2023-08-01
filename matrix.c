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


#include "matrix.h"

//-- Custom RayLib Struct Containers
static unsigned int RL_MATRIX_OBJECT_ID = 0;
static unsigned char RL_MATRIX_INIT = 0;
static const unsigned int RL_MATRIX_MAX_OBJECTS = 999999;

char* RL_Matrix_Hash_Id(char *str, size_t size) {
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

struct RL_Matrix* RL_Matrix_Create() {
    //-- Create the initial data structures
    if (RL_MATRIX_INIT == 0) {
        RL_Matrix_Object_List = (struct RL_Matrix**) malloc(0);
        RL_Matrix_Object_Map = hashmap_create();
        RL_MATRIX_INIT = 1;
    }

    //-- Create the container object
    struct RL_Matrix* object = (struct RL_Matrix*) malloc(sizeof(struct RL_Matrix));
    object->id = RL_MATRIX_OBJECT_ID++;
    object->guid = calloc(33, sizeof(char));
    object->guid = RL_Matrix_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Matrix_Object_List = (struct RL_Matrix**) realloc(RL_Matrix_Object_List, RL_MATRIX_OBJECT_ID * sizeof(struct RL_Matrix*));
    RL_Matrix_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Matrix_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Matrix_Delete(struct RL_Matrix* object, int index) {
    if (index < 0 || index >= RL_MATRIX_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Matrix_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Matrix_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Matrix_Object_List[index], &RL_Matrix_Object_List[index + 1], (RL_MATRIX_OBJECT_ID - index - 1) * sizeof(struct RL_Matrix *));

    // Decrement the count and resize the array
    RL_MATRIX_OBJECT_ID--;
    RL_Matrix_Object_List = (struct RL_Matrix **)realloc(RL_Matrix_Object_List, (RL_MATRIX_OBJECT_ID) * sizeof(struct RL_Matrix *));
}

void RL_Matrix_Free(struct RL_Matrix* object) {
    free(object);
}

//------------------------------------------------------------------------------------------------------
//-- raylib Matrix PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_matrix_object_handlers;

static HashTable php_raylib_matrix_prop_handlers;

typedef double (*raylib_matrix_read_float_t)(php_raylib_matrix_object *obj);
typedef int (*raylib_matrix_write_float_t)(php_raylib_matrix_object *obj,  zval *value);

typedef struct _raylib_matrix_prop_handler {
    raylib_matrix_read_float_t read_float_func;
    raylib_matrix_write_float_t write_float_func;
} raylib_matrix_prop_handler;

static void php_raylib_matrix_register_prop_handler(HashTable *prop_handler, char *name,
                                                      raylib_matrix_read_float_t read_float_func,
                                                      raylib_matrix_write_float_t write_float_func) /* {{{ */
{
    raylib_matrix_prop_handler hnd;

    hnd.read_float_func = read_float_func;
    hnd.write_float_func = write_float_func;

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_matrix_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_matrix_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_matrix_property_reader(php_raylib_matrix_object *obj, raylib_matrix_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_float_func) {
        ZVAL_DOUBLE(rv, hnd->read_float_func(obj));
    }

    return rv;
}
/* }}} */

static zval *php_raylib_matrix_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_matrix_object *obj;
    zval *retval = NULL;
    raylib_matrix_prop_handler *hnd = NULL;

    obj = php_raylib_matrix_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_matrix_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_matrix_object *obj;
    zval *retval = NULL;
    raylib_matrix_prop_handler *hnd = NULL;

    obj = php_raylib_matrix_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_matrix_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_matrix_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) /* {{{ */
{
    php_raylib_matrix_object *obj;
    raylib_matrix_prop_handler *hnd;

    obj = php_raylib_matrix_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_float_func) {
        hnd->write_float_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_matrix_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_matrix_object *obj;
    raylib_matrix_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_matrix_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_matrix_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_matrix_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_matrix_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_matrix_object *obj;
    HashTable *props;
    raylib_matrix_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_matrix_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
    zval *ret, val;
        ret = php_raylib_matrix_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_matrix_free_storage(zend_object *object)/* {{{ */
{
    php_raylib_matrix_object *intern = php_raylib_matrix_fetch_object(object);

    intern->matrix->refCount--;
    if (intern->matrix->refCount < 1) {
        RL_Matrix_Free(intern->matrix);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

static void php_raylib_matrix_free_prop_handler(zval *el) /* {{{ */
{
    pefree(Z_PTR_P(el), 1);
} /* }}} */

zend_object * php_raylib_matrix_new_ex(zend_class_entry *ce, zend_object *orig)/* {{{ */
{
    php_raylib_matrix_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_matrix_object), ce);

    intern->prop_handler = &php_raylib_matrix_prop_handlers;

    if (orig) {
        php_raylib_matrix_object *other = php_raylib_matrix_fetch_object(orig);

        intern->matrix->data = (Matrix) {
            .m0 = other->matrix->data.m0,
            .m4 = other->matrix->data.m4,
            .m8 = other->matrix->data.m8,
            .m12 = other->matrix->data.m12,
            .m1 = other->matrix->data.m1,
            .m5 = other->matrix->data.m5,
            .m9 = other->matrix->data.m9,
            .m13 = other->matrix->data.m13,
            .m2 = other->matrix->data.m2,
            .m6 = other->matrix->data.m6,
            .m10 = other->matrix->data.m10,
            .m14 = other->matrix->data.m14,
            .m3 = other->matrix->data.m3,
            .m7 = other->matrix->data.m7,
            .m11 = other->matrix->data.m11,
            .m15 = other->matrix->data.m15
        };
    } else {
        intern->matrix = RL_Matrix_Create();
        intern->matrix->data = (Matrix) {
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
        };

    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_matrix_object_handlers;

    return &intern->std;
}
/* }}} */

zend_object *php_raylib_matrix_new(zend_class_entry *class_type) /* {{{  */
{
    return php_raylib_matrix_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_matrix_clone(zend_object *old_object) /* {{{  */
{
    zend_object *new_object;

    new_object = php_raylib_matrix_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix__construct, 0, 0, 0)
    ZEND_ARG_TYPE_MASK(0, m0, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m4, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m8, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m12, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m1, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m5, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m9, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m13, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m2, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m6, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m10, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m14, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m3, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m7, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m11, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
    ZEND_ARG_TYPE_MASK(0, m15, MAY_BE_DOUBLE|MAY_BE_NULL, "0")
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, __construct)
{
    double m0;
    bool m0_is_null = 1;

    double m4;
    bool m4_is_null = 1;

    double m8;
    bool m8_is_null = 1;

    double m12;
    bool m12_is_null = 1;

    double m1;
    bool m1_is_null = 1;

    double m5;
    bool m5_is_null = 1;

    double m9;
    bool m9_is_null = 1;

    double m13;
    bool m13_is_null = 1;

    double m2;
    bool m2_is_null = 1;

    double m6;
    bool m6_is_null = 1;

    double m10;
    bool m10_is_null = 1;

    double m14;
    bool m14_is_null = 1;

    double m3;
    bool m3_is_null = 1;

    double m7;
    bool m7_is_null = 1;

    double m11;
    bool m11_is_null = 1;

    double m15;
    bool m15_is_null = 1;

    ZEND_PARSE_PARAMETERS_START(0, 16)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE_OR_NULL(m0, m0_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m4, m4_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m8, m8_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m12, m12_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m1, m1_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m5, m5_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m9, m9_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m13, m13_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m2, m2_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m6, m6_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m10, m10_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m14, m14_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m3, m3_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m7, m7_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m11, m11_is_null)
        Z_PARAM_DOUBLE_OR_NULL(m15, m15_is_null)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    if (m0_is_null) {
        m0 = 0.0f;
    }

    if (m4_is_null) {
        m4 = 0.0f;
    }

    if (m8_is_null) {
        m8 = 0.0f;
    }

    if (m12_is_null) {
        m12 = 0.0f;
    }

    if (m1_is_null) {
        m1 = 0.0f;
    }

    if (m5_is_null) {
        m5 = 0.0f;
    }

    if (m9_is_null) {
        m9 = 0.0f;
    }

    if (m13_is_null) {
        m13 = 0.0f;
    }

    if (m2_is_null) {
        m2 = 0.0f;
    }

    if (m6_is_null) {
        m6 = 0.0f;
    }

    if (m10_is_null) {
        m10 = 0.0f;
    }

    if (m14_is_null) {
        m14 = 0.0f;
    }

    if (m3_is_null) {
        m3 = 0.0f;
    }

    if (m7_is_null) {
        m7 = 0.0f;
    }

    if (m11_is_null) {
        m11 = 0.0f;
    }

    if (m15_is_null) {
        m15 = 0.0f;
    }



    intern->matrix->data = (Matrix) {
        .m0 = (float) m0,
        .m4 = (float) m4,
        .m8 = (float) m8,
        .m12 = (float) m12,
        .m1 = (float) m1,
        .m5 = (float) m5,
        .m9 = (float) m9,
        .m13 = (float) m13,
        .m2 = (float) m2,
        .m6 = (float) m6,
        .m10 = (float) m10,
        .m14 = (float) m14,
        .m3 = (float) m3,
        .m7 = (float) m7,
        .m11 = (float) m11,
        .m15 = (float) m15
    };
}

static double php_raylib_matrix_get_m0(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m0;
}
/* }}} */

static double php_raylib_matrix_get_m4(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m4;
}
/* }}} */

static double php_raylib_matrix_get_m8(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m8;
}
/* }}} */

static double php_raylib_matrix_get_m12(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m12;
}
/* }}} */

static double php_raylib_matrix_get_m1(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m1;
}
/* }}} */

static double php_raylib_matrix_get_m5(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m5;
}
/* }}} */

static double php_raylib_matrix_get_m9(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m9;
}
/* }}} */

static double php_raylib_matrix_get_m13(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m13;
}
/* }}} */

static double php_raylib_matrix_get_m2(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m2;
}
/* }}} */

static double php_raylib_matrix_get_m6(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m6;
}
/* }}} */

static double php_raylib_matrix_get_m10(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m10;
}
/* }}} */

static double php_raylib_matrix_get_m14(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m14;
}
/* }}} */

static double php_raylib_matrix_get_m3(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m3;
}
/* }}} */

static double php_raylib_matrix_get_m7(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m7;
}
/* }}} */

static double php_raylib_matrix_get_m11(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m11;
}
/* }}} */

static double php_raylib_matrix_get_m15(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix->data.m15;
}
/* }}} */

static int php_raylib_matrix_set_m0(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m0 = 0;
        return ret;
    }

    obj->matrix->data.m0 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m4(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m4 = 0;
        return ret;
    }

    obj->matrix->data.m4 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m8(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m8 = 0;
        return ret;
    }

    obj->matrix->data.m8 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m12(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m12 = 0;
        return ret;
    }

    obj->matrix->data.m12 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m1(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m1 = 0;
        return ret;
    }

    obj->matrix->data.m1 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m5(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m5 = 0;
        return ret;
    }

    obj->matrix->data.m5 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m9(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m9 = 0;
        return ret;
    }

    obj->matrix->data.m9 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m13(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m13 = 0;
        return ret;
    }

    obj->matrix->data.m13 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m2(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m2 = 0;
        return ret;
    }

    obj->matrix->data.m2 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m6(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m6 = 0;
        return ret;
    }

    obj->matrix->data.m6 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m10(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m10 = 0;
        return ret;
    }

    obj->matrix->data.m10 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m14(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m14 = 0;
        return ret;
    }

    obj->matrix->data.m14 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m3(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m3 = 0;
        return ret;
    }

    obj->matrix->data.m3 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m7(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m7 = 0;
        return ret;
    }

    obj->matrix->data.m7 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m11(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m11 = 0;
        return ret;
    }

    obj->matrix->data.m11 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_set_m15(php_raylib_matrix_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        obj->matrix->data.m15 = 0;
        return ret;
    }

    obj->matrix->data.m15 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

const zend_function_entry php_raylib_matrix_methods[] = {
        PHP_ME(Matrix, __construct, arginfo_matrix__construct, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
void php_raylib_matrix_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_matrix_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_matrix_object_handlers.offset = XtOffsetOf(php_raylib_matrix_object, std);
    php_raylib_matrix_object_handlers.free_obj = &php_raylib_matrix_free_storage;
    php_raylib_matrix_object_handlers.clone_obj = php_raylib_matrix_clone;

    // Props
    php_raylib_matrix_object_handlers.get_property_ptr_ptr = php_raylib_matrix_get_property_ptr_ptr;
    php_raylib_matrix_object_handlers.get_gc               = php_raylib_matrix_get_gc;
    php_raylib_matrix_object_handlers.get_properties       = php_raylib_matrix_get_properties;
    php_raylib_matrix_object_handlers.read_property	     = php_raylib_matrix_read_property;
    php_raylib_matrix_object_handlers.write_property       = php_raylib_matrix_write_property;
    php_raylib_matrix_object_handlers.has_property	     = php_raylib_matrix_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Matrix", php_raylib_matrix_methods);
    php_raylib_matrix_ce = zend_register_internal_class(&ce);
    php_raylib_matrix_ce->create_object = php_raylib_matrix_new;

    // Props
    zend_hash_init(&php_raylib_matrix_prop_handlers, 0, NULL, php_raylib_matrix_free_prop_handler, 1);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m0", php_raylib_matrix_get_m0, php_raylib_matrix_set_m0);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m4", php_raylib_matrix_get_m4, php_raylib_matrix_set_m4);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m8", php_raylib_matrix_get_m8, php_raylib_matrix_set_m8);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m12", php_raylib_matrix_get_m12, php_raylib_matrix_set_m12);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m1", php_raylib_matrix_get_m1, php_raylib_matrix_set_m1);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m5", php_raylib_matrix_get_m5, php_raylib_matrix_set_m5);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m9", php_raylib_matrix_get_m9, php_raylib_matrix_set_m9);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m13", php_raylib_matrix_get_m13, php_raylib_matrix_set_m13);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m2", php_raylib_matrix_get_m2, php_raylib_matrix_set_m2);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m6", php_raylib_matrix_get_m6, php_raylib_matrix_set_m6);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m10", php_raylib_matrix_get_m10, php_raylib_matrix_set_m10);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m14", php_raylib_matrix_get_m14, php_raylib_matrix_set_m14);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m3", php_raylib_matrix_get_m3, php_raylib_matrix_set_m3);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m7", php_raylib_matrix_get_m7, php_raylib_matrix_set_m7);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m11", php_raylib_matrix_get_m11, php_raylib_matrix_set_m11);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m15", php_raylib_matrix_get_m15, php_raylib_matrix_set_m15);
}
