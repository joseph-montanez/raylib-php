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
#include "raylib-texture.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Image PHP Custom Object
//------------------------------------------------------------------------------------------------------
/* {{{ ZE2 OO definitions */
zend_object_handlers php_raylib_image_object_handlers;

static HashTable php_raylib_image_prop_handlers;

typedef int (*raylib_image_read_int_t)(struct Image *image);

typedef struct _raylib_image_prop_handler {
    raylib_image_read_int_t read_int_func;
} raylib_image_prop_handler;
/* }}} */


static void php_raylib_image_register_prop_handler(HashTable *prop_handler, char *name, raylib_image_read_int_t read_int_func) /* {{{ */
{
    raylib_image_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_image_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_image_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_image_property_reader(php_raylib_image_object *obj, raylib_image_prop_handler *hnd, zval *rv) /* {{{ */
{
    int retint = 0;

    if (obj != NULL && hnd->read_int_func) {
        retint = hnd->read_int_func(&obj->image);
        if (retint == -1) {
            php_error_docref(NULL, E_WARNING, "Internal raylib image error returned");
            return NULL;
        }
    }

    ZVAL_LONG(rv, (long)retint);

    return rv;
}
/* }}} */

static zval *php_raylib_image_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_image_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_image_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_IMAGE_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd == NULL) {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_image_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_image_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_image_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_IMAGE_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        retval = php_raylib_image_property_reader(obj, hnd, rv);
        if (retval == NULL) {
            retval = &EG(uninitialized_zval);
        }
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static int php_raylib_image_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_image_object *obj;
    zval tmp_member;
    raylib_image_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_IMAGE_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_image_property_reader(obj, hnd, &tmp)) != NULL) {
            if (type == 1) {
                retval = zend_is_true(&tmp);
            } else if (type == 0) {
                retval = (Z_TYPE(tmp) != IS_NULL);
            }
        }

        zval_ptr_dtor(&tmp);
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->has_property(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static HashTable *php_raylib_image_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_image_get_properties(zval *object)/* {{{ */
{
    php_raylib_image_object *obj;
    HashTable *props;
    raylib_image_prop_handler *hnd;
    zend_string *key;

    obj = Z_IMAGE_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
                zval *ret, val;
                ret = php_raylib_image_property_reader(obj, hnd, &val);
                if (ret == NULL) {
                    ret = &EG(uninitialized_zval);
                }
                zend_hash_update(props, key, ret);
            } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_image_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_image_object *intern = php_raylib_image_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadImage(intern->image);
}

zend_object * php_raylib_image_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_image_object *intern;
    intern = (php_raylib_image_object*) ecalloc(1, sizeof(php_raylib_image_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_image_prop_handlers;

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_image_object_handlers;

    return &intern->std;
}

// PHP property handling

static int php_raylib_image_width(struct Image *image) /* {{{ */
{
    return image->width;
}
/* }}} */

static int php_raylib_image_height(struct Image *image) /* {{{ */
{
    return image->height;
}
/* }}} */

static int php_raylib_image_mipmaps(struct Image *image) /* {{{ */
{
    return image->mipmaps;
}
/* }}} */

static int php_raylib_image_format(struct Image *image) /* {{{ */
{
    return image->format;
}
/* }}} */

// PHP object handling

PHP_METHOD(Image, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(getThis());
    intern->image = LoadImage(fileName->val);
}

PHP_METHOD(Image, toTexture)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(getThis());

    object_init_ex(return_value, php_raylib_texture_ce);

    zend_object *object = php_raylib_texture_new(php_raylib_texture_ce);

    php_raylib_texture_object *internTexture = php_raylib_texture_fetch_object(object);

    internTexture->texture = LoadTextureFromImage(intern->image);

    ZVAL_OBJ(return_value, object);
}

//Image ImageCopy(Image image);
PHP_METHOD(Image, copy)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(getThis());

    object_init_ex(return_value, php_raylib_image_ce);

    zend_object *object = php_raylib_image_new(php_raylib_image_ce);

    php_raylib_image_object *internTexture = php_raylib_image_fetch_object(object);

    internTexture->image = ImageCopy(intern->image);

    ZVAL_OBJ(return_value, object);
}

//void ImageToPOT(Image *image, Color fillColor);
PHP_METHOD(Image, toPot)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(getThis());
    zval *colorArr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(colorArr)
    ZEND_PARSE_PARAMETERS_END();


    ImageToPOT(&intern->image, php_array_to_color(colorArr));
}

const zend_function_entry php_raylib_image_methods[] = {
        PHP_ME(Image, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, toTexture, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, copy, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, toPot, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_image_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_image_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    //-- Object handlers
    memcpy(&php_raylib_image_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_image_object_handlers.offset = XtOffsetOf(php_raylib_image_object, std);
    php_raylib_image_object_handlers.free_obj = &php_raylib_image_free_storage;
    php_raylib_image_object_handlers.clone_obj = NULL;

    // Props
    php_raylib_image_object_handlers.get_property_ptr_ptr = php_raylib_image_get_property_ptr_ptr;
    php_raylib_image_object_handlers.get_gc         = php_raylib_image_get_gc;
    php_raylib_image_object_handlers.get_properties = php_raylib_image_get_properties;
    php_raylib_image_object_handlers.read_property	= php_raylib_image_read_property;
    php_raylib_image_object_handlers.has_property	= php_raylib_image_has_property;


    //-- Class Methods
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Image", php_raylib_image_methods);
    php_raylib_image_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_image_ce->create_object = php_raylib_image_new;

    zend_hash_init(&php_raylib_image_prop_handlers, 0, NULL, php_raylib_image_free_prop_handler, 1);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "width", php_raylib_image_width);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "height", php_raylib_image_height);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "mipmaps", php_raylib_image_mipmaps);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "height", php_raylib_image_format);
}