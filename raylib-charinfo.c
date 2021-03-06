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
#include "raylib-image.h"
#include "raylib-charinfo.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib CharInfo PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_charinfo_object_handlers;

static HashTable php_raylib_charinfo_prop_handlers;

typedef zend_long (*raylib_charinfo_read_long_t)(php_raylib_charinfo_object *obj);

typedef int (*raylib_charinfo_write_long_t)(php_raylib_charinfo_object *obj, zval *value);

typedef zend_object* (*raylib_charinfo_read_image_object_t)(php_raylib_charinfo_object *obj);

typedef int (*raylib_charinfo_write_image_object_t)(php_raylib_charinfo_object *obj, zval *value);

typedef struct _raylib_charinfo_prop_handler {
    raylib_charinfo_read_long_t read_long_func;
    raylib_charinfo_write_long_t write_long_func;
    raylib_charinfo_read_image_object_t read_image_func;
    raylib_charinfo_write_image_object_t write_image_func;
} raylib_charinfo_prop_handler;
/* }}} */

static void php_raylib_charinfo_register_prop_handler(HashTable *prop_handler, char *name, raylib_charinfo_read_long_t read_long_func, raylib_charinfo_write_long_t write_long_func) /* {{{ */
{
    raylib_charinfo_prop_handler hnd;

    hnd.read_long_func = read_long_func;
    hnd.write_long_func = write_long_func;
    hnd.read_image_func = NULL;
    hnd.write_image_func = NULL;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_charinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_charinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}

static void php_raylib_charinfo_register_prop_handler_image(HashTable *prop_handler, char *name, raylib_charinfo_read_image_object_t read_image_func, raylib_charinfo_write_image_object_t write_image_func) /* {{{ */
{
    raylib_charinfo_prop_handler hnd;

    hnd.read_long_func = NULL;
    hnd.write_long_func = NULL;
    hnd.read_image_func = read_image_func;
    hnd.write_image_func = write_image_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_charinfo_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_charinfo_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_charinfo_property_reader(php_raylib_charinfo_object *obj, raylib_charinfo_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_long_func) {
        zend_long ret = hnd->read_long_func(obj);
        ZVAL_LONG(rv, (zend_long) ret);
    } else if (obj != NULL && hnd->read_image_func) {
        zend_object *ret = hnd->read_image_func(obj);
        ZVAL_OBJ(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_charinfo_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    zval *retval = NULL;
    raylib_charinfo_prop_handler *hnd = NULL;

    obj = php_raylib_charinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_charinfo_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    zval *retval = NULL;
    raylib_charinfo_prop_handler *hnd = NULL;

    obj = php_raylib_charinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_charinfo_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_charinfo_write_property(zval *object, zval *member, zval *value[, const zend_literal *key])
   Generic object property writer */
zval *php_raylib_charinfo_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_charinfo_object *obj;
    raylib_charinfo_prop_handler *hnd;

    obj = php_raylib_charinfo_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_image_func) {
        hnd->write_image_func(obj, value);
    } else if (hnd && hnd->write_long_func) {
        hnd->write_long_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_charinfo_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_charinfo_object *obj;
    raylib_charinfo_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_charinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_charinfo_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_charinfo_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_charinfo_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_charinfo_object *obj;
    HashTable *props;
    raylib_charinfo_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_charinfo_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_charinfo_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_charinfo_free_storage(zend_object *object)
{
    php_raylib_charinfo_object *intern = php_raylib_charinfo_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}


zend_object * php_raylib_charinfo_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_charinfo_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_charinfo_object), ce);

    intern->prop_handler = &php_raylib_charinfo_prop_handlers;

    if (orig) {
        php_raylib_charinfo_object *other = php_raylib_charinfo_fetch_object(orig);

        zend_object *image = php_raylib_image_new_ex(php_raylib_image_ce, &other->image->std);

        php_raylib_image_object *phpImage = php_raylib_image_fetch_object(image);

        intern->charinfo = (CharInfo) {
                .value = other->charinfo.value,
                .offsetX = other->charinfo.offsetX,
                .offsetY = other->charinfo.offsetY,
                .advanceX = other->charinfo.advanceX,
                .image = phpImage->image,
        };
        intern->image = phpImage;
    } else {
        zend_object *image = php_raylib_image_new_ex(php_raylib_image_ce, NULL);

        php_raylib_image_object *phpImage = php_raylib_image_fetch_object(image);

        intern->charinfo = (CharInfo) {
                .value = 0,
                .offsetX = 0,
                .offsetY = 0,
                .advanceX = 0,
                .image = phpImage->image
        };
        intern->image = phpImage;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_charinfo_object_handlers;

    return &intern->std;
}

zend_object * php_raylib_charinfo_new(zend_class_entry *ce)
{
    return php_raylib_charinfo_new_ex(ce, NULL);
}

static zend_object *php_raylib_charinfo_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_charinfo_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static zend_long php_raylib_charinfo_value(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->charinfo.value;
}
/* }}} */

static zend_long php_raylib_charinfo_offset_x(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->charinfo.offsetX;
}

static zend_long php_raylib_charinfo_offset_y(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->charinfo.offsetY;
}

static zend_long php_raylib_charinfo_advance_x(php_raylib_charinfo_object *obj) /* {{{ */
{
    return (zend_long) obj->charinfo.advanceX;
}

static zend_object * php_raylib_charinfo_image(php_raylib_charinfo_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->image->std);
    return &obj->image->std;
}
/* }}} */



static int php_raylib_charinfo_write_value(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        charinfo_object->charinfo.value = 0;
        return ret;
    }

    charinfo_object->charinfo.value = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_charinfo_write_offset_x(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        charinfo_object->charinfo.offsetX = 0;
        return ret;
    }

    charinfo_object->charinfo.offsetX = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_charinfo_write_offset_y(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        charinfo_object->charinfo.offsetY = 0;
        return ret;
    }

    charinfo_object->charinfo.offsetY = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_charinfo_write_advance_x(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        charinfo_object->charinfo.advanceX = 0;
        return ret;
    }

    charinfo_object->charinfo.advanceX = (int) zval_get_long(newval);

    return ret;
}

static int php_raylib_charinfo_write_image(php_raylib_charinfo_object *charinfo_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(newval);
    charinfo_object->image = phpImage;

    return ret;
}
/* }}} */

// PHP object handling
ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo__construct, 0, 0, 5)
    ZEND_ARG_INFO(0, value)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, advanceX)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, __construct)
{
    zend_long value, offsetX, offsetY, advanceX;
    zend_object *image;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(value)
            Z_PARAM_LONG(offsetX)
            Z_PARAM_LONG(offsetY)
            Z_PARAM_LONG(advanceX)
            Z_PARAM_OBJ_OF_CLASS(image, php_raylib_image_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = php_raylib_image_fetch_object(image);

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo = (CharInfo) {
            .value = (int) value,
            .offsetX = (int) offsetX,
            .offsetY = (int) offsetY,
            .advanceX = (int) advanceX,
            .image = phpImage->image,
    };

    intern->image = phpImage;

}

// Load font data for further use
// RLAPI CharInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int charsCount, int type);
ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_fromFontData, 0, 0, 5)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, dataSize)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, fontChars)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, fromFontData)
{

    zend_string *fileName;
    zval *fontChars;
    HashTable *fontCharsArr;
    zend_long dataSize, fontSize, type;
    zval *zv;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STR(fileName)
        Z_PARAM_LONG(dataSize)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ARRAY(fontChars)
        Z_PARAM_LONG(type)
    ZEND_PARSE_PARAMETERS_END();

    fontCharsArr = Z_ARRVAL_P(fontChars);
    int numFontChars = zend_hash_num_elements(fontCharsArr);
    int *fontCharsP = (int *)safe_emalloc(numFontChars, sizeof(int), 0);

    int n = 0;
    ZEND_HASH_FOREACH_VAL(fontCharsArr, zv) {
        switch (Z_TYPE_P(zv)) {
            case IS_LONG:
                if (n < numFontChars) {
                    zend_long val = zval_get_long(zv);
                    fontCharsP[n] = (int) val;
                    n++;
                }
                break;
            default:
                php_error_docref(NULL, E_WARNING, "Invalid type for element %i", n);
                RETURN_FALSE;
        }
    } ZEND_HASH_FOREACH_END();

    zval *charinfo = malloc(sizeof(zval));
    object_init_ex(charinfo, php_raylib_charinfo_ce);

    php_raylib_charinfo_object *result = Z_CHARINFO_OBJ_P(charinfo);

    CharInfo *charInfos = LoadFontData(
            fileName->val,
            (int) dataSize,
            (int) fontSize,
            fontCharsP,
            numFontChars,
            (int) type
    );

    array_init_size(return_value, numFontChars);

    for (int i = 0; i < numFontChars; i++) {
        zval *charInfo = malloc(sizeof(zval));
        object_init_ex(charInfo, php_raylib_charinfo_ce);

        php_raylib_charinfo_object *result = Z_CHARINFO_OBJ_P(charInfo);
        result->charinfo = charInfos[i];
        add_index_zval(return_value, i, charInfo);
    }
}
ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_getValue, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, getValue)
{
    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->charinfo.value);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_setValue, 0, 0, 1)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, setValue)
{
    zend_long value;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo.value = (int) value;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_getOffsetX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, getOffsetX)
{
    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->charinfo.offsetX);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_setOffsetX, 0, 0, 1)
    ZEND_ARG_INFO(0, offsetX)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, setOffsetX)
{
    zend_long offsetX;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(offsetX)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo.offsetX = (int) offsetX;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_getOffsetY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, getOffsetY)
{
    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->charinfo.offsetY);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_setOffsetY, 0, 0, 1)
    ZEND_ARG_INFO(0, offsetY)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, setOffsetY)
{
    zend_long offsetY;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(offsetY)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo.offsetY = (int) offsetY;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_getAdvanceX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, getAdvanceX)
{
    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->charinfo.advanceX);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_setAdvanceX, 0, 0, 1)
    ZEND_ARG_INFO(0, advanceX)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, setAdvanceX)
{
    zend_long advanceX;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(advanceX)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo.advanceX = (int) advanceX;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_getImage, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, getImage)
{
    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);
    RETURN_OBJ(&intern->std);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_charinfo_setImage, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_METHOD(CharInfo, setImage)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    php_raylib_charinfo_object *intern = Z_CHARINFO_OBJ_P(ZEND_THIS);

    intern->charinfo.image = phpImage->image;
}


const zend_function_entry php_raylib_charinfo_methods[] = {
        PHP_ME(CharInfo, __construct,  arginfo_charinfo__construct, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, fromFontData, arginfo_charinfo_fromFontData, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CharInfo, getValue,     arginfo_charinfo_getValue, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, setValue,     arginfo_charinfo_setValue, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, getOffsetX,   arginfo_charinfo_getOffsetX, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, setOffsetX,   arginfo_charinfo_setOffsetX, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, getOffsetY,   arginfo_charinfo_getOffsetY, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, setOffsetY,   arginfo_charinfo_setOffsetY, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, getAdvanceX,  arginfo_charinfo_getAdvanceX, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, setAdvanceX,  arginfo_charinfo_setAdvanceX, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, getImage,     arginfo_charinfo_getImage, ZEND_ACC_PUBLIC)
        PHP_ME(CharInfo, setImage,     arginfo_charinfo_setImage, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_charinfo_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_charinfo_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_charinfo_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_charinfo_object_handlers.offset = XtOffsetOf(php_raylib_charinfo_object, std);
    php_raylib_charinfo_object_handlers.free_obj = &php_raylib_charinfo_free_storage;
    php_raylib_charinfo_object_handlers.clone_obj = php_raylib_charinfo_clone;

    // Props
    php_raylib_charinfo_object_handlers.get_property_ptr_ptr = php_raylib_charinfo_get_property_ptr_ptr;
    php_raylib_charinfo_object_handlers.get_gc               = php_raylib_charinfo_get_gc;
    php_raylib_charinfo_object_handlers.get_properties       = php_raylib_charinfo_get_properties;
    php_raylib_charinfo_object_handlers.read_property	     = php_raylib_charinfo_read_property;
    php_raylib_charinfo_object_handlers.write_property       = php_raylib_charinfo_write_property;
    php_raylib_charinfo_object_handlers.has_property	     = php_raylib_charinfo_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "CharInfo", php_raylib_charinfo_methods);
    php_raylib_charinfo_ce = zend_register_internal_class(&ce);
    php_raylib_charinfo_ce->create_object = php_raylib_charinfo_new;

    // Props
    zend_hash_init(&php_raylib_charinfo_prop_handlers, 0, NULL, php_raylib_charinfo_free_prop_handler, 1);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "value", php_raylib_charinfo_value, php_raylib_charinfo_write_value);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "offsetX", php_raylib_charinfo_offset_x, php_raylib_charinfo_write_offset_x);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "offsetY", php_raylib_charinfo_offset_y, php_raylib_charinfo_write_offset_y);
    php_raylib_charinfo_register_prop_handler(&php_raylib_charinfo_prop_handlers, "advanceX", php_raylib_charinfo_advance_x, php_raylib_charinfo_write_advance_x);
    php_raylib_charinfo_register_prop_handler_image(&php_raylib_charinfo_prop_handlers, "image", php_raylib_charinfo_image, php_raylib_charinfo_write_image);
}