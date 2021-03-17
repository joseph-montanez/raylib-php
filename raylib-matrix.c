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
/*#define NONLS             // All NLS defines and routines*/
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

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include "php.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-matrix.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Matrix PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_matrix_object_handlers;

static HashTable php_raylib_matrix_prop_handlers;

typedef double (*raylib_matrix_read_float_t)(php_raylib_matrix_object *obj);

typedef int (*raylib_matrix_write_float_t)(php_raylib_matrix_object *obj, zval *value);

typedef struct _raylib_matrix_prop_handler {
    raylib_matrix_read_float_t read_float_func;
    raylib_matrix_write_float_t write_float_func;
} raylib_matrix_prop_handler;
/* }}} */

static void php_raylib_matrix_register_prop_handler(HashTable *prop_handler, char *name, raylib_matrix_read_float_t read_float_func, raylib_matrix_write_float_t write_float_func) /* {{{ */
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
    double ret = 0;

    if (obj != NULL && hnd->read_float_func) {
//        php_error_docref(NULL, E_WARNING, "Internal raylib matrix found");
        ret = hnd->read_float_func(obj);
    } else {
//        php_error_docref(NULL, E_WARNING, "Internal raylib vectro2 error returned");
    }

    ZVAL_DOUBLE(rv, (double) ret);

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

/* {{{ php_raylib_matrix_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_matrix_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_matrix_object *obj;
    raylib_matrix_prop_handler *hnd;

    obj = php_raylib_matrix_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd) {
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

void php_raylib_matrix_free_storage(zend_object *object)
{
    php_raylib_matrix_object *intern = php_raylib_matrix_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}


zend_object * php_raylib_matrix_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_matrix_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_matrix_object), ce);

    intern->prop_handler = &php_raylib_matrix_prop_handlers;

    if (orig) {
        php_raylib_matrix_object *other = php_raylib_matrix_fetch_object(orig);
        intern->matrix = other->matrix;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_matrix_object_handlers;

    return &intern->std;
}


/* {{{  */
static zend_object *php_raylib_matrix_new(zend_class_entry *class_type)
{
    return php_raylib_matrix_new_ex(class_type, NULL);
}
/* }}} */

static zend_object *php_raylib_matrix_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_matrix_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static double php_raylib_matrix_m0(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m0;
}
/* }}} */

static double php_raylib_matrix_m1(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m1;
}
/* }}} */

static double php_raylib_matrix_m2(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m2;
}
/* }}} */

static double php_raylib_matrix_m3(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m3;
}
/* }}} */

static double php_raylib_matrix_m4(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m4;
}
/* }}} */

static double php_raylib_matrix_m5(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m5;
}
/* }}} */

static double php_raylib_matrix_m6(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m6;
}
/* }}} */

static double php_raylib_matrix_m7(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m7;
}
/* }}} */

static double php_raylib_matrix_m8(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m8;
}
/* }}} */

static double php_raylib_matrix_m9(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m9;
}
/* }}} */

static double php_raylib_matrix_m10(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m10;
}
/* }}} */

static double php_raylib_matrix_m11(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m11;
}
/* }}} */

static double php_raylib_matrix_m12(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m12;
}
/* }}} */

static double php_raylib_matrix_m13(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m13;
}
/* }}} */

static double php_raylib_matrix_m14(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m14;
}
/* }}} */

static double php_raylib_matrix_m15(php_raylib_matrix_object *obj) /* {{{ */
{
    return (double) obj->matrix.m15;
}
/* }}} */

static int php_raylib_matrix_write_m0(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m0 = 0;
        return ret;
    }

    matrix_object->matrix.m0 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m1(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m1 = 0;
        return ret;
    }

    matrix_object->matrix.m1 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m2(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m2 = 0;
        return ret;
    }

    matrix_object->matrix.m2 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m3(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m3 = 0;
        return ret;
    }

    matrix_object->matrix.m3 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m4(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m4 = 0;
        return ret;
    }

    matrix_object->matrix.m4 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m5(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m5 = 0;
        return ret;
    }

    matrix_object->matrix.m5 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m6(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m6 = 0;
        return ret;
    }

    matrix_object->matrix.m6 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m7(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m7 = 0;
        return ret;
    }

    matrix_object->matrix.m7 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m8(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m8 = 0;
        return ret;
    }

    matrix_object->matrix.m8 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m9(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m9 = 0;
        return ret;
    }

    matrix_object->matrix.m9 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m10(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m10 = 0;
        return ret;
    }

    matrix_object->matrix.m10 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m11(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m11 = 0;
        return ret;
    }

    matrix_object->matrix.m11 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m12(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m12 = 0;
        return ret;
    }

    matrix_object->matrix.m12 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m13(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m13 = 0;
        return ret;
    }

    matrix_object->matrix.m13 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m14(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m14 = 0;
        return ret;
    }

    matrix_object->matrix.m14 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */

static int php_raylib_matrix_write_m15(php_raylib_matrix_object *matrix_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        matrix_object->matrix.m15 = 0;
        return ret;
    }

    matrix_object->matrix.m15 = (float) zval_get_double(newval);

    return ret;
}
/* }}} */


// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix__construct, 0, 0, 16)
                ZEND_ARG_INFO(0, m0)
                ZEND_ARG_INFO(0, m1)
                ZEND_ARG_INFO(0, m2)
                ZEND_ARG_INFO(0, m3)
                ZEND_ARG_INFO(0, m4)
                ZEND_ARG_INFO(0, m5)
                ZEND_ARG_INFO(0, m6)
                ZEND_ARG_INFO(0, m7)
                ZEND_ARG_INFO(0, m8)
                ZEND_ARG_INFO(0, m9)
                ZEND_ARG_INFO(0, m10)
                ZEND_ARG_INFO(0, m11)
                ZEND_ARG_INFO(0, m12)
                ZEND_ARG_INFO(0, m13)
                ZEND_ARG_INFO(0, m14)
                ZEND_ARG_INFO(0, m15)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, __construct)
{
    double m0, m4, m8, m12;
    double m1, m5, m9, m13;
    double m2, m6, m10, m14;
    double m3, m7, m11, m15;

    ZEND_PARSE_PARAMETERS_START(16, 16)
        Z_PARAM_DOUBLE(m0)
        Z_PARAM_DOUBLE(m1)
        Z_PARAM_DOUBLE(m2)
        Z_PARAM_DOUBLE(m3)
        Z_PARAM_DOUBLE(m4)
        Z_PARAM_DOUBLE(m5)
        Z_PARAM_DOUBLE(m6)
        Z_PARAM_DOUBLE(m7)
        Z_PARAM_DOUBLE(m8)
        Z_PARAM_DOUBLE(m9)
        Z_PARAM_DOUBLE(m10)
        Z_PARAM_DOUBLE(m11)
        Z_PARAM_DOUBLE(m12)
        Z_PARAM_DOUBLE(m13)
        Z_PARAM_DOUBLE(m14)
        Z_PARAM_DOUBLE(m15)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix = (Matrix) {
        .m0 = (float) m0,
        .m1 = (float) m1,
        .m2 = (float) m2,
        .m3 = (float) m3,
        .m4 = (float) m4,
        .m5 = (float) m5,
        .m6 = (float) m6,
        .m7 = (float) m7,
        .m8 = (float) m8,
        .m9 = (float) m9,
        .m10 = (float) m10,
        .m11 = (float) m11,
        .m12 = (float) m12,
        .m13 = (float) m13,
        .m14 = (float) m14,
        .m15 = (float) m15
    };

}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM0, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM0)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM0, 0, 0, 1)
                ZEND_ARG_INFO(0, m0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM0)
{
    double m0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m0)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m0 = (float) m0;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM1, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM1)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m1);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM1, 0, 0, 1)
                ZEND_ARG_INFO(0, m1)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM1)
{
    double m1;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m1)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m1 = (float) m1;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM2, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM2)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m2);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM2, 0, 0, 1)
                ZEND_ARG_INFO(0, m2)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM2)
{
    double m2;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m2 = (float) m2;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM3, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM3)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m3);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM3, 0, 0, 1)
                ZEND_ARG_INFO(0, m3)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM3)
{
    double m3;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m3)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m3 = (float) m3;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM4, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM4)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m4);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM4, 0, 0, 1)
                ZEND_ARG_INFO(0, m4)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM4)
{
    double m4;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m4)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m4 = (float) m4;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM5, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM5)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m5);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM5, 0, 0, 1)
                ZEND_ARG_INFO(0, m5)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM5)
{
    double m5;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m5)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m5 = (float) m5;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM6, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM6)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m6);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM6, 0, 0, 1)
                ZEND_ARG_INFO(0, m6)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM6)
{
    double m6;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m6)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m6 = (float) m6;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM7, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM7)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m7);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM7, 0, 0, 1)
                ZEND_ARG_INFO(0, m7)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM7)
{
    double m7;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m7)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m7 = (float) m7;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM8, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM8)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m8);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM8, 0, 0, 1)
                ZEND_ARG_INFO(0, m8)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM8)
{
    double m8;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m8)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m8 = (float) m8;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM9, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM9)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m9);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM9, 0, 0, 1)
                ZEND_ARG_INFO(0, m9)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM9)
{
    double m9;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m9)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m9 = (float) m9;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM10, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM10)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m10);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM10, 0, 0, 1)
                ZEND_ARG_INFO(0, m10)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM10)
{
    double m10;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m10)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m10 = (float) m10;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM11, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM11)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m11);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM11, 0, 0, 1)
                ZEND_ARG_INFO(0, m11)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM11)
{
    double m11;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m11)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m11 = (float) m11;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM12, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM12)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m12);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM12, 0, 0, 1)
                ZEND_ARG_INFO(0, m12)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM12)
{
    double m12;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m12)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m12 = (float) m12;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM13, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM13)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m13);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM13, 0, 0, 1)
                ZEND_ARG_INFO(0, m13)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM13)
{
    double m13;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m13)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m13 = (float) m13;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM14, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM14)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m14);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM14, 0, 0, 1)
                ZEND_ARG_INFO(0, m14)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM14)
{
    double m14;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m14)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m14 = (float) m14;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_getM15, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, getM15)
{
    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);
    RETURN_DOUBLE(intern->matrix.m15);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_matrix_setM15, 0, 0, 1)
                ZEND_ARG_INFO(0, m15)
ZEND_END_ARG_INFO()
PHP_METHOD(Matrix, setM15)
{
    double m15;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(m15)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_matrix_object *intern = Z_MATRIX_OBJ_P(ZEND_THIS);

    intern->matrix.m15 = (float) m15;
}

const zend_function_entry php_raylib_matrix_methods[] = {
        PHP_ME(Matrix, __construct, arginfo_matrix__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM0      , arginfo_matrix_getM0     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM0      , arginfo_matrix_setM0     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM1      , arginfo_matrix_getM1     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM1      , arginfo_matrix_setM1     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM2      , arginfo_matrix_getM2     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM2      , arginfo_matrix_setM2     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM3      , arginfo_matrix_getM3     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM3      , arginfo_matrix_setM3     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM4      , arginfo_matrix_getM4     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM4      , arginfo_matrix_setM4     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM5      , arginfo_matrix_getM5     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM5      , arginfo_matrix_setM5     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM6      , arginfo_matrix_getM6     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM6      , arginfo_matrix_setM6     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM7      , arginfo_matrix_getM7     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM7      , arginfo_matrix_setM7     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM8      , arginfo_matrix_getM8     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM8      , arginfo_matrix_setM8     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM9      , arginfo_matrix_getM9     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM9      , arginfo_matrix_setM9     , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM10     , arginfo_matrix_getM10    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM10     , arginfo_matrix_setM10    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM11     , arginfo_matrix_getM11    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM11     , arginfo_matrix_setM11    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM12     , arginfo_matrix_getM12    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM12     , arginfo_matrix_setM12    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM13     , arginfo_matrix_getM13    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM13     , arginfo_matrix_setM13    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM14     , arginfo_matrix_getM14    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM14     , arginfo_matrix_setM14    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, getM15     , arginfo_matrix_getM15    , ZEND_ACC_PUBLIC)
        PHP_ME(Matrix, setM15     , arginfo_matrix_setM15    , ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_matrix_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

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
    php_raylib_matrix_object_handlers.read_property	       = php_raylib_matrix_read_property;
    php_raylib_matrix_object_handlers.write_property       = php_raylib_matrix_write_property;
    php_raylib_matrix_object_handlers.has_property	       = php_raylib_matrix_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Matrix", php_raylib_matrix_methods);
    php_raylib_matrix_ce = zend_register_internal_class(&ce);
    php_raylib_matrix_ce->create_object = php_raylib_matrix_new;

    // Props
    zend_hash_init(&php_raylib_matrix_prop_handlers, 0, NULL, php_raylib_matrix_free_prop_handler, 1);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m0", php_raylib_matrix_m0, php_raylib_matrix_write_m0);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m1", php_raylib_matrix_m1, php_raylib_matrix_write_m1);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m2", php_raylib_matrix_m2, php_raylib_matrix_write_m2);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m3", php_raylib_matrix_m3, php_raylib_matrix_write_m3);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m4", php_raylib_matrix_m4, php_raylib_matrix_write_m4);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m5", php_raylib_matrix_m5, php_raylib_matrix_write_m5);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m6", php_raylib_matrix_m6, php_raylib_matrix_write_m6);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m7", php_raylib_matrix_m7, php_raylib_matrix_write_m7);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m8", php_raylib_matrix_m8, php_raylib_matrix_write_m8);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m9", php_raylib_matrix_m9, php_raylib_matrix_write_m9);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m10", php_raylib_matrix_m10, php_raylib_matrix_write_m10);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m11", php_raylib_matrix_m11, php_raylib_matrix_write_m11);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m12", php_raylib_matrix_m12, php_raylib_matrix_write_m12);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m13", php_raylib_matrix_m13, php_raylib_matrix_write_m13);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m14", php_raylib_matrix_m14, php_raylib_matrix_write_m14);
    php_raylib_matrix_register_prop_handler(&php_raylib_matrix_prop_handlers, "m15", php_raylib_matrix_m15, php_raylib_matrix_write_m15);

}