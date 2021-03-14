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
#include "raylib-rectangle.h"
#include "raylib-vector2.h"
#include "raylib-texture.h"
#include "raylib-utils.h"
#include "raylib-color.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Texture PHP Custom Object
//------------------------------------------------------------------------------------------------------
/* {{{ ZE2 OO definitions */

zend_object_handlers php_raylib_texture_object_handlers;

static HashTable php_raylib_texture_prop_handlers;

typedef zend_long (*raylib_texture_read_int_t)(php_raylib_texture_object *texture);

typedef struct _raylib_texture_prop_handler {
    raylib_texture_read_int_t read_int_func;
} raylib_texture_prop_handler;
/* }}} */

static void php_raylib_texture_register_prop_handler(HashTable *prop_handler, char *name, raylib_texture_read_int_t read_int_func) /* {{{ */
{
    raylib_texture_prop_handler hnd;

    hnd.read_int_func = read_int_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_texture_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_texture_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_texture_property_reader(php_raylib_texture_object *obj, raylib_texture_prop_handler *hnd, zval *rv) /* {{{ */
{
    zend_long retint = 0;

    if (obj != NULL && hnd->read_int_func) {
        retint = hnd->read_int_func(obj);
        if (retint == -1) {
            php_error_docref(NULL, E_WARNING, "Internal raylib texture error returned");
            return NULL;
        }
    }

    ZVAL_LONG(rv, retint);

    return rv;
}
/* }}} */

static zval *php_raylib_texture_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_texture_object *obj;
    zval *retval = NULL;
    raylib_texture_prop_handler *hnd = NULL;

    obj = php_raylib_texture_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_texture_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_texture_object *obj;
    zval *retval = NULL;
    raylib_texture_prop_handler *hnd = NULL;

    obj = php_raylib_texture_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_texture_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static int php_raylib_texture_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_texture_object *obj;
    raylib_texture_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_texture_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_texture_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_texture_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_texture_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_texture_object *obj;
    HashTable *props;
    raylib_texture_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_texture_fetch_object(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_texture_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_texture_free_storage(zend_object *object)
{
    php_raylib_texture_object *intern = php_raylib_texture_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadTexture(intern->texture);
}

zend_object * php_raylib_texture_new(zend_class_entry *ce)
{
    php_raylib_texture_object *intern;
    intern = (php_raylib_texture_object*) ecalloc(1, sizeof(php_raylib_texture_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_texture_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_texture_object_handlers;

    return &intern->std;
}

// PHP property handling

static zend_long php_raylib_texture_width(php_raylib_texture_object *obj) /* {{{ */
{
    return (zend_long) obj->texture.width;
}
/* }}} */

static zend_long php_raylib_texture_height(php_raylib_texture_object *obj) /* {{{ */
{
    return (zend_long) obj->texture.height;
}
/* }}} */

static zend_long php_raylib_texture_mipmaps(php_raylib_texture_object *obj) /* {{{ */
{
    return (zend_long) obj->texture.mipmaps;
}
/* }}} */

static zend_long php_raylib_texture_format(php_raylib_texture_object *obj) /* {{{ */
{
    return (zend_long) obj->texture.format;
}
/* }}} */

static zend_long php_raylib_texture_id(php_raylib_texture_object *obj) /* {{{ */
{
    return (zend_long) obj->texture.id;
}
/* }}} */

/* {{{ REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_texture_ce, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    intern->texture = LoadTexture(fileName->val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_width, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, width)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->texture.width);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_height, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, height)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->texture.height);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_format, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, format)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->texture.format);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_id, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, id)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->texture.id);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_mipmaps, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, mipmaps)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->texture.mipmaps);
}

// RLAPI void SetTextureFilter(Texture2D texture, int filterMode);
ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_setFilter, 0, 0, 1)
    ZEND_ARG_INFO(0, filterMode)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, setFilter)
{
    zend_long filterMode;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(filterMode)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    SetTextureFilter(intern->texture, (int) filterMode);
}

// RLAPI void GenTextureMipmaps(Texture2D *texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_genMipmaps, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, genMipmaps)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    GenTextureMipmaps(&intern->texture);
}

// RLAPI void SetTextureWrap(Texture2D texture, int wrapMode);
ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_setWrap, 0, 0, 1)
    ZEND_ARG_INFO(0, wrapMode)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, setWrap)
{
    zend_long wrapMode;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(wrapMode)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);
    SetTextureWrap(intern->texture, (int) wrapMode);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_draw, 0, 0, 3)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, draw)
{
    zend_long posX;
    zend_long posY;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();


//    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTexture(intern->texture, (int) posX, (int) posY, phpTint->color);
}


// Draw a Texture2D with position defined as Vector2
// RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_drawV, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, drawV)
{
    zval *position;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTextureV(intern->texture, phpPosition->vector2, phpTint->color);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_drawEx, 0, 0, 4)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, drawEx)
{
    zval *position;
    double rotation;
    double scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_DOUBLE(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();


    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTextureEx(intern->texture, phpPosition->vector2, (float) rotation, (float) scale, phpTint->color);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_drawRec, 0, 0, 3)
    ZEND_ARG_INFO(0, sourceRec)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, drawRec)
{
    zval *sourceRec;
    zval *position;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(sourceRec)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();


    php_raylib_rectangle_object *phpSourceRec = Z_RECTANGLE_OBJ_P(sourceRec);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTextureRec(intern->texture, phpSourceRec->rectangle, phpPosition->vector2, phpTint->color);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_drawQuad, 0, 0, 4)
    ZEND_ARG_INFO(0, tiling)
    ZEND_ARG_INFO(0, offset)
    ZEND_ARG_INFO(0, quad)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, drawQuad)
{
    zval *tiling;
    zval *offset;
    zval *quad;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(tiling)
        Z_PARAM_ZVAL(offset)
        Z_PARAM_ZVAL(quad)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpTiling = Z_VECTOR2_OBJ_P(tiling);
    php_raylib_vector2_object *phpOffset = Z_VECTOR2_OBJ_P(offset);
    php_raylib_rectangle_object *phpQuad = Z_RECTANGLE_OBJ_P(quad);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTextureQuad(intern->texture, phpTiling->vector2, phpOffset->vector2, phpQuad->rectangle, phpTint->color);
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
// RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_texture_drawPro, 0, 0, 5)
    ZEND_ARG_INFO(0, sourceRec)
    ZEND_ARG_INFO(0, destRec)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Texture, drawPro)
{
    zval *sourceRec;
    zval *destRec;
    zval *origin;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(sourceRec)
        Z_PARAM_ZVAL(destRec)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();


    php_raylib_rectangle_object *phpSourceRec = Z_RECTANGLE_OBJ_P(sourceRec);
    php_raylib_rectangle_object *phpDestRec = Z_RECTANGLE_OBJ_P(destRec);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(ZEND_THIS);

    DrawTexturePro(intern->texture, phpSourceRec->rectangle, phpDestRec->rectangle, phpOrigin->vector2, (float) rotation, phpColor->color);
}

const zend_function_entry php_raylib_texture_methods[] = {
        PHP_ME(Texture, __construct, arginfo_texture__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, width      , arginfo_texture_width, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, height     , arginfo_texture_height, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, format     , arginfo_texture_format, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, id         , arginfo_texture_id, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, mipmaps    , arginfo_texture_mipmaps, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, genMipmaps , arginfo_texture_genMipmaps, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, setFilter  , arginfo_texture_setFilter, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, setWrap    , arginfo_texture_setWrap, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, draw       , arginfo_texture_draw, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, drawV      , arginfo_texture_drawV, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, drawEx     , arginfo_texture_drawEx, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, drawRec    , arginfo_texture_drawRec, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, drawQuad   , arginfo_texture_drawQuad, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, drawPro    , arginfo_texture_drawPro, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_texture_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

void php_raylib_texture_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    //-- Object handlers
    memcpy(&php_raylib_texture_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_texture_object_handlers.offset    = XtOffsetOf(php_raylib_texture_object, std);
    php_raylib_texture_object_handlers.free_obj  = &php_raylib_texture_free_storage;
    php_raylib_texture_object_handlers.clone_obj = NULL;
    
    // Props
    php_raylib_texture_object_handlers.get_property_ptr_ptr = php_raylib_texture_get_property_ptr_ptr;
    php_raylib_texture_object_handlers.get_gc               = php_raylib_texture_get_gc;
    php_raylib_texture_object_handlers.get_properties       = php_raylib_texture_get_properties;
    php_raylib_texture_object_handlers.read_property        = php_raylib_texture_read_property;
    php_raylib_texture_object_handlers.has_property         = php_raylib_texture_has_property;
    
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Texture", php_raylib_texture_methods);
    php_raylib_texture_ce = zend_register_internal_class(&ce);
    php_raylib_texture_ce->create_object = php_raylib_texture_new;
    
    // Props
    zend_hash_init(&php_raylib_texture_prop_handlers, 0, NULL, php_raylib_texture_free_prop_handler, 1);
    php_raylib_texture_register_prop_handler(&php_raylib_texture_prop_handlers, "width", php_raylib_texture_width);
    php_raylib_texture_register_prop_handler(&php_raylib_texture_prop_handlers, "height", php_raylib_texture_height);
    php_raylib_texture_register_prop_handler(&php_raylib_texture_prop_handlers, "mipmaps", php_raylib_texture_mipmaps);
    php_raylib_texture_register_prop_handler(&php_raylib_texture_prop_handlers, "height", php_raylib_texture_format);
    php_raylib_texture_register_prop_handler(&php_raylib_texture_prop_handlers, "id", php_raylib_texture_id);

    // Filters
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_POINT", FILTER_POINT);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_BILINEAR", FILTER_BILINEAR);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_TRILINEAR", FILTER_TRILINEAR);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_ANISOTROPIC_4X", FILTER_ANISOTROPIC_4X);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_ANISOTROPIC_8X", FILTER_ANISOTROPIC_8X);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("FILTER_ANISOTROPIC_16X", FILTER_ANISOTROPIC_16X);

    // Wraps
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("WRAP_REPEAT", WRAP_REPEAT);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("WRAP_CLAMP", WRAP_CLAMP);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("WRAP_MIRROR_REPEAT", WRAP_MIRROR_REPEAT);
    REGISTER_RAYLIB_TEXTURE_CLASS_CONST_LONG("WRAP_MIRROR_CLAMP", WRAP_MIRROR_CLAMP);
}