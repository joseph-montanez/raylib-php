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
#include "raylib-texture.h"
#include "raylib-color.h"
#include "raylib-glyphinfo.h"
#include "raylib-vector2.h"
#include "raylib-font.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Font PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_font_object_handlers;

static HashTable php_raylib_font_prop_handlers;

typedef zend_long (*raylib_font_read_long_t)(php_raylib_font_object *obj);

typedef int (*raylib_font_write_long_t)(php_raylib_font_object *obj, zval *value);

typedef zend_object* (*raylib_font_read_texture_object_t)(php_raylib_font_object *obj);

typedef int (*raylib_font_write_texture_object_t)(php_raylib_font_object *obj, zval *value);

typedef zend_object* (*raylib_font_read_glyphInfo_object_t)(php_raylib_font_object *obj);

typedef int (*raylib_font_write_glyphInfo_object_t)(php_raylib_font_object *obj, zval *value);

typedef zend_object* (*raylib_font_read_rectangle_object_t)(php_raylib_font_object *obj);

typedef int (*raylib_font_write_rectangle_object_t)(php_raylib_font_object *obj, zval *value);

typedef struct _raylib_font_prop_handler {
    raylib_font_read_long_t read_long_func;
    raylib_font_write_long_t write_long_func;
    raylib_font_read_texture_object_t read_texture_func;
    raylib_font_write_texture_object_t write_texture_func;
    raylib_font_read_glyphInfo_object_t read_glyphInfo_func;
    raylib_font_write_glyphInfo_object_t write_glyphInfo_func;
    raylib_font_read_rectangle_object_t read_rectangle_func;
    raylib_font_write_rectangle_object_t write_rectangle_func;
} raylib_font_prop_handler;
/* }}} */

/**
 * This will update
 * @param intern
 */
void php_raylib_font_update_intern(php_raylib_font_object *intern) {
    // Grab Rectangles and Update
    int numRecs = zend_hash_num_elements(intern->recs);
    Rectangle *recsP = (Rectangle *)safe_emalloc(numRecs, sizeof(Rectangle), 0);

    int n = 0;
    zval *zv;
    ZEND_HASH_FOREACH_VAL(intern->recs, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_rectangle_object *obj = Z_RECTANGLE_OBJ_P(zv);
            recsP[n] = obj->rectangle;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    intern->font.recs = recsP;
}


static void php_raylib_font_register_prop_handler(HashTable *prop_handler, char *name, raylib_font_read_long_t read_long_func, raylib_font_write_long_t write_long_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_long_func = read_long_func;
    hnd.write_long_func = write_long_func;
    hnd.read_rectangle_func = NULL;
    hnd.write_rectangle_func = NULL;
    hnd.read_glyphInfo_func = NULL;
    hnd.write_glyphInfo_func = NULL;
    hnd.read_texture_func = NULL;
    hnd.write_texture_func = NULL;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */


static void php_raylib_font_register_prop_handler_texture(HashTable *prop_handler, char *name, raylib_font_read_texture_object_t read_texture_func, raylib_font_write_texture_object_t write_texture_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_long_func = NULL;
    hnd.write_long_func = NULL;
    hnd.read_rectangle_func = NULL;
    hnd.write_rectangle_func = NULL;
    hnd.read_glyphInfo_func = NULL;
    hnd.write_glyphInfo_func = NULL;
    hnd.read_texture_func = read_texture_func;
    hnd.write_texture_func = write_texture_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static void php_raylib_font_register_prop_handler_rectangle(HashTable *prop_handler, char *name, raylib_font_read_rectangle_object_t read_rectangle_func, raylib_font_write_rectangle_object_t write_rectangle_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_long_func = NULL;
    hnd.write_long_func = NULL;
    hnd.read_rectangle_func = read_rectangle_func;
    hnd.write_rectangle_func = write_rectangle_func;
    hnd.read_glyphInfo_func = NULL;
    hnd.write_glyphInfo_func = NULL;
    hnd.read_texture_func = NULL;
    hnd.write_texture_func = NULL;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static void php_raylib_font_register_prop_handler_glyphInfo(HashTable *prop_handler, char *name, raylib_font_read_glyphInfo_object_t read_glyphInfo_func, raylib_font_write_glyphInfo_object_t write_glyphInfo_func) /* {{{ */
{
    raylib_font_prop_handler hnd;

    hnd.read_long_func = NULL;
    hnd.write_long_func = NULL;
    hnd.read_rectangle_func = NULL;
    hnd.write_rectangle_func = NULL;
    hnd.read_glyphInfo_func = read_glyphInfo_func;
    hnd.write_glyphInfo_func = write_glyphInfo_func;
    hnd.read_texture_func = NULL;
    hnd.write_texture_func = NULL;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_font_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_font_ce, name, strlen(name), ZEND_ACC_PUBLIC);
}
/* }}} */

static zval *php_raylib_font_property_reader(php_raylib_font_object *obj, raylib_font_prop_handler *hnd, zval *rv) /* {{{ */
{
    if (obj != NULL && hnd->read_texture_func) {
        zend_object *ret = hnd->read_texture_func(obj);
        ZVAL_OBJ(rv, ret);
    } else if (obj != NULL && hnd->read_rectangle_func) {
        zend_object *ret = hnd->read_rectangle_func(obj);
        ZVAL_OBJ(rv, ret);
    } else if (obj != NULL && hnd->read_glyphInfo_func) {
        zend_object *ret = hnd->read_glyphInfo_func(obj);
        ZVAL_OBJ(rv, ret);
    } else if (obj != NULL && hnd->read_long_func) {
        double ret = (double) hnd->read_long_func(obj);
        ZVAL_DOUBLE(rv, ret);
    }

    return rv;
}
/* }}} */

static zval *php_raylib_font_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_font_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_font_object *obj;
    zval *retval = NULL;
    raylib_font_prop_handler *hnd = NULL;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_font_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

/* {{{ php_raylib_font_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
   Generic object property writer */
zval *php_raylib_font_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
    php_raylib_font_object *obj;
    raylib_font_prop_handler *hnd;

    obj = php_raylib_font_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member);
    }

    if (hnd && hnd->write_texture_func) {
        hnd->write_texture_func(obj, value);
    } else if (hnd && hnd->write_rectangle_func) {
        hnd->write_rectangle_func(obj, value);
    } else if (hnd && hnd->write_glyphInfo_func) {
        hnd->write_glyphInfo_func(obj, value);
    } else if (hnd && hnd->write_long_func) {
        hnd->write_long_func(obj, value);
    } else {
        value = zend_std_write_property(object, member, value, cache_slot);
    }

    return value;
}
/* }}} */

static int php_raylib_font_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_font_object *obj;
    raylib_font_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_font_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_font_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_font_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_font_get_properties(zval *object)/* {{{ */
{
    php_raylib_font_object *obj;
    HashTable *props;
    raylib_font_prop_handler *hnd;
    zend_string *key;

    obj = Z_FONT_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
        zval *ret, val;
        ret = php_raylib_font_property_reader(obj, hnd, &val);
        if (ret == NULL) {
            ret = &EG(uninitialized_zval);
        }
        zend_hash_update(props, key, ret);
    } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_font_free_storage(zend_object *object)
{
    php_raylib_font_object *intern = php_raylib_font_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadFont(intern->font);
}


zend_object * php_raylib_font_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_font_object *intern;

    intern = zend_object_alloc(sizeof(php_raylib_font_object), ce);

    intern->prop_handler = &php_raylib_font_prop_handlers;

    if (orig) {
        php_raylib_font_object *other = php_raylib_font_fetch_object(orig);

//        zend_object *texture = php_raylib_texture_new_ex(php_raylib_texture_ce, &other->texture->std);
//        php_raylib_texture_object *phpTexture = php_raylib_texture_fetch_object(texture);

        //-- Copy Recs
        int numRecs = zend_hash_num_elements(other->recs);
        Rectangle *recsP = (Rectangle *)safe_emalloc(numRecs, sizeof(Rectangle), 0);

        int n = 0;
        zval *zv;
        ZEND_HASH_FOREACH_VAL(other->recs, zv) {
            if (Z_TYPE_P(zv) == IS_OBJECT) {
                php_raylib_rectangle_object *obj = Z_RECTANGLE_OBJ_P(zv);
                recsP[n] = obj->rectangle;
            }
            n++;
        } ZEND_HASH_FOREACH_END();

        HashTable *recs;
        ALLOC_HASHTABLE(recs);
        zend_hash_init(recs, 0, NULL, NULL, 0);
        zend_hash_copy(recs, other->recs, NULL);

        //-- Copy Chars
        int numChars = zend_hash_num_elements(other->chars);
        GlyphInfo *charsP = (GlyphInfo *)safe_emalloc(numChars, sizeof(GlyphInfo), 0);

        int j = 0;
        zval *zv2;
        ZEND_HASH_FOREACH_VAL(other->chars, zv2) {
            if (Z_TYPE_P(zv2) == IS_OBJECT) {
                php_raylib_glyphInfo_object *obj = Z_GlyphInfo_OBJ_P(zv2);
                charsP[j] = obj->glyphInfo;
            }
            j++;
        } ZEND_HASH_FOREACH_END();

        HashTable *chars;
        ALLOC_HASHTABLE(chars);
        zend_hash_init(chars, 0, NULL, NULL, 0);
        zend_hash_copy(chars, other->chars, NULL);


        intern->font = (Font) {
                .baseSize = other->font.baseSize,
                .glyphCount = other->font.glyphCount,
                .glyphPadding = other->font.glyphPadding,
//                .texture = phpTexture->texture,
                .recs = recsP,
                .glyphs = charsP
        };
//        intern->recs = phpTexture;
        intern->recs = recs;
        intern->chars = chars;
    } else {
//        zend_object *offset = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
//        zend_object *target = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);

//        php_raylib_vector2_object *phpOffset = php_raylib_vector2_fetch_object(offset);
//        php_raylib_vector2_object *phpTarget = php_raylib_vector2_fetch_object(target);

        /*
         *     int baseSize;           // Base size (default chars height)
    int glyphCount;         // Number of glyph characters
    int glyphPadding;       // Padding around the glyph characters
    Texture2D texture;      // Texture atlas containing the glyphs
    Rectangle *recs;        // Rectangles in texture for the glyphs
    GlyphInfo *glyphs;      // Glyphs info data
         */
        intern->font = (Font) {
                .baseSize = 0,
                .glyphPadding = 0
        };
//        intern->texture = phpOffset;
//        intern->target = phpTarget;
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &php_raylib_font_object_handlers;

    return &intern->std;
}

zend_object * php_raylib_font_new(zend_class_entry *ce)
{
    php_raylib_font_object *intern;
    intern = (php_raylib_font_object*) ecalloc(1, sizeof(php_raylib_font_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_font_prop_handlers;

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_font_object_handlers;

    return &intern->std;
}

static zend_object *php_raylib_font_clone(zend_object *old_object)
{
    zend_object *new_object;

    new_object = php_raylib_font_new_ex(old_object->ce, old_object);

    zend_objects_clone_members(new_object, old_object);

    return new_object;
}

// PHP property handling

static zend_long php_raylib_font_base_size(php_raylib_font_object *obj) /* {{{ */
{
    return (zend_long) obj->font.baseSize;
}
/* }}} */

static zend_long php_raylib_font_chars_count(php_raylib_font_object *obj) /* {{{ */
{
    return (zend_long) obj->font.glyphCount;
}
/* }}} */

static zval * php_raylib_font_texture(php_raylib_font_object *obj) /* {{{ */
{
//    php_raylib_texture_object *result = Z_TEXTURE_OBJ_P(obj->texture);
    return &obj->texture;
}
/* }}} */

static HashTable * php_raylib_font_recs(php_raylib_font_object *obj) /* {{{ */
{
//    GC_ADDREF(&obj->recs);
    return &obj->recs;
}
/* }}} */

static zval * php_raylib_font_chars(php_raylib_font_object *obj) /* {{{ */
{
    zval *glyphInfos = malloc(sizeof(zval));
//    object_init_ex(glyphInfos, php_raylib_texture_ce);

//    php_raylib_texture_object *result = Z_TEXTURE_OBJ_P(texture);
//    result->texture = obj->glyphInfo.texture;

    array_init_size(glyphInfos, obj->font.glyphCount);

    for (int i = 0; i < obj->font.glyphCount; i++) {
        zval *glyphInfo = malloc(sizeof(zval));
        object_init_ex(glyphInfo, php_raylib_glyphInfo_ce);

        php_raylib_glyphInfo_object *result = Z_GlyphInfo_OBJ_P(glyphInfo);
        result->glyphInfo = obj->font.glyphs[i];
        add_index_zval(glyphInfos, i, glyphInfo);
    }

    return glyphInfos;
}
/* }}} */



static int php_raylib_font_write_base_size(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        font_object->font.baseSize = 0;
        return ret;
    }

    font_object->font.baseSize = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_write_chars_count(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        font_object->font.glyphCount = 0;
        return ret;
    }

    font_object->font.glyphCount = (int) zval_get_long(newval);

    return ret;
}
/* }}} */

static int php_raylib_font_write_texture(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_texture_object *phpImage = Z_TEXTURE_OBJ_P(newval);

    font_object->font.texture = phpImage->texture;

    return ret;
}
/* }}} */

static int php_raylib_font_write_recs(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    HashTable *rectsArr = Z_ARRVAL_P(newval);
    font_object->recs = rectsArr;

    /*
    int numRecs = zend_hash_num_elements(rectsArr);
    Rectangle *recsP = (Rectangle *)safe_emalloc(numRecs, sizeof(Rectangle), 0);

    int n = 0;
    zval *zv;
    ZEND_HASH_FOREACH_VAL(rectsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_rectangle_object *obj = Z_RECTANGLE_OBJ_P(zv);
            recsP[n] = obj->rectangle;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    font_object->font.recs = recsP;
     */

    return ret;
}
/* }}} */

static int php_raylib_font_write_chars(php_raylib_font_object *font_object, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    HashTable *charsArr = Z_ARRVAL_P(newval);
    int numChars = zend_hash_num_elements(charsArr);
    GlyphInfo *charsP = (GlyphInfo *)safe_emalloc(numChars, sizeof(GlyphInfo), 0);

    int n = 0;
    zval *zv;
    ZEND_HASH_FOREACH_VAL(charsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_glyphInfo_object *obj = Z_GlyphInfo_OBJ_P(zv);
            charsP[n] = obj->glyphInfo;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    font_object->font.glyphs = charsP;

    return ret;
}
/* }}} */

/* {{{ REGISTER_RAYLIB_GlyphInfo_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_FONT_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_font_ce, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling
// RLAPI Font LoadFont(const char *fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_font__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);

    intern->font = LoadFont(fileName->val);

    //-- Create PHP Texture Object
    zval *texture = malloc(sizeof(zval));
    object_init_ex(texture, php_raylib_texture_ce);

    php_raylib_texture_object *result = Z_TEXTURE_OBJ_P(texture);
    result->texture = intern->font.texture;

    intern->texture = result;
}

// Draw text using font and additional parameters
// RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_font_draw, 0, 0, 5)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, draw)
{
    zend_string *text;
    zval *position;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STR(text)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextEx(intern->font, text->val, phpPosition->vector2, (float) fontSize, (float) spacing, phpTint->color);
}

// RLAPI Font GetFontDefault(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_font_fromDefault, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, fromDefault)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_font_ce);
    
    php_raylib_font_object *result = Z_FONT_OBJ_P(obj);
    result->font = GetFontDefault();
    
    RETURN_OBJ(&result->std);
}

// RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);
ZEND_BEGIN_ARG_INFO_EX(arginfo_font_measureText, 0, 0, 3)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, measureText)
{
    zend_string *text;
    double fontSize;
    double spacing;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = MeasureTextEx(intern->font, text->val, (float) fontSize, (float) spacing);

    RETURN_OBJ(&result->std);
}

//RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int glyphCount)
ZEND_BEGIN_ARG_INFO_EX(arginfo_font_fromCustom, 0, 0, 4)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, fontChars)
    ZEND_ARG_INFO(0, glyphCount)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, fromCustom)
{
    zend_string *fileName;
    zend_long fontSize;
    zend_long glyphCount;
    zval *fontChars;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_STR(fileName)
            Z_PARAM_LONG(fontSize)
            Z_PARAM_ZVAL(fontChars)
            Z_PARAM_LONG(glyphCount)
    ZEND_PARSE_PARAMETERS_END();

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_font_ce);
    
    php_raylib_font_object *result = Z_FONT_OBJ_P(obj);

    if (Z_TYPE_P(fontChars) != IS_NULL) {
        result->font = LoadFontEx(fileName->val, (int) fontSize, (int *) Z_LVAL_P(fontChars), (int) glyphCount);
    } else {
        result->font = LoadFontEx(fileName->val, (int) fontSize, NULL, (int) glyphCount);
    }

    //-- Create PHP Texture Object
//    zval *texture;
//    object_init_ex(texture, php_raylib_texture_ce);
//
//    php_raylib_texture_object *texture_result = Z_TEXTURE_OBJ_P(&texture);
//    texture_result->texture = result->font.texture;
//
//    result->texture = texture;

    RETURN_OBJ(&result->std);
}
ZEND_BEGIN_ARG_INFO_EX(arginfo_font_fromRaw, 0, 0, 5)
    ZEND_ARG_INFO(0, baseSize)
    ZEND_ARG_INFO(0, glyphCount)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, recs)
    ZEND_ARG_INFO(0, chars)
ZEND_END_ARG_INFO()
PHP_METHOD(Font, fromRaw)
{
    zend_long baseSize;
    zend_long glyphCount;
    zval *texture;
    zval *recs;
    zval *chars;
    HashTable *recsArr, *charsArr;
    zval *zv;
    int numRecs, numChars, n;
    Rectangle *recsP;
    GlyphInfo *charsP;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_LONG(baseSize)
            Z_PARAM_LONG(glyphCount)
            Z_PARAM_ZVAL(texture)
            Z_PARAM_ARRAY(recs)
            Z_PARAM_ARRAY(chars)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);


    recsArr = Z_ARRVAL_P(recs);
    numRecs = zend_hash_num_elements(recsArr);
    recsP = (Rectangle *)safe_emalloc(numRecs, sizeof(Rectangle), 0);
    n = 0;
    ZEND_HASH_FOREACH_VAL(recsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_rectangle_object *obj = Z_RECTANGLE_OBJ_P(zv);
            recsP[n] = obj->rectangle;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    charsArr = Z_ARRVAL_P(chars);
    numChars = zend_hash_num_elements(charsArr);
    charsP = (GlyphInfo *)safe_emalloc(numChars, sizeof(GlyphInfo), 0);
    ZEND_HASH_FOREACH_VAL(charsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_glyphInfo_object *obj = Z_GlyphInfo_OBJ_P(zv);
            charsP[n] = obj->glyphInfo;
        }
    } ZEND_HASH_FOREACH_END();


    intern->font = (Font) {
            .baseSize = (int) baseSize,
            .glyphCount = (int) glyphCount,
            .texture = phpTexture->texture,
            .recs = recsP,
            .glyphs = charsP
    };
}

//PHP_METHOD(Font, getX)
//{
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->font.x);
//}

//PHP_METHOD(Font, setX)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//
//    intern->font.x = zend_double_2float(val);
//}
//
//PHP_METHOD(Font, getY)
//{
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//    RETURN_DOUBLE(intern->font.y);
//}
//
//PHP_METHOD(Font, setY)
//{
//    zval *val;
//
//    ZEND_PARSE_PARAMETERS_START(1, 1)
//            Z_PARAM_ZVAL(val)
//    ZEND_PARSE_PARAMETERS_END();
//
//    php_raylib_font_object *intern = Z_FONT_OBJ_P(ZEND_THIS);
//
//    intern->font.y = zend_double_2float(val);
//}

const zend_function_entry php_raylib_font_methods[] = {
        PHP_ME(Font, __construct, arginfo_font__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Font, fromRaw    , arginfo_font_fromRaw, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Font, fromDefault, arginfo_font_fromDefault, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Font, fromCustom , arginfo_font_fromCustom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Font, measureText, arginfo_font_measureText, ZEND_ACC_PUBLIC)
        PHP_ME(Font, draw       , arginfo_font_draw, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getBaseSize, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setBaseSize, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getglyphCount, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setglyphCount, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getTexture, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setTexture, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getRecs, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setRecs, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, getChars, NULL, ZEND_ACC_PUBLIC)
//        PHP_ME(Font, setChars, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_font_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_font_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    memcpy(&php_raylib_font_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_font_object_handlers.offset = XtOffsetOf(php_raylib_font_object, std);
    php_raylib_font_object_handlers.free_obj = &php_raylib_font_free_storage;
    php_raylib_font_object_handlers.clone_obj = php_raylib_font_clone;

    // Props
    php_raylib_font_object_handlers.get_property_ptr_ptr = php_raylib_font_get_property_ptr_ptr;
    php_raylib_font_object_handlers.get_gc               = php_raylib_font_get_gc;
    php_raylib_font_object_handlers.get_properties       = php_raylib_font_get_properties;
    php_raylib_font_object_handlers.read_property	     = php_raylib_font_read_property;
    php_raylib_font_object_handlers.write_property       = php_raylib_font_write_property;
    php_raylib_font_object_handlers.has_property	     = php_raylib_font_has_property;

    // Init
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Font", php_raylib_font_methods);
    php_raylib_font_ce = zend_register_internal_class(&ce);
    php_raylib_font_ce->create_object = php_raylib_font_new;

    // Props
    zend_hash_init(&php_raylib_font_prop_handlers, 0, NULL, php_raylib_font_free_prop_handler, 1);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "baseSize", php_raylib_font_base_size, php_raylib_font_write_base_size);
    php_raylib_font_register_prop_handler(&php_raylib_font_prop_handlers, "charCount", php_raylib_font_chars_count, php_raylib_font_write_chars_count);
    php_raylib_font_register_prop_handler_texture(&php_raylib_font_prop_handlers, "texture", php_raylib_font_texture, php_raylib_font_write_texture);
    php_raylib_font_register_prop_handler_rectangle(&php_raylib_font_prop_handlers, "recs", php_raylib_font_recs, php_raylib_font_write_recs);
    php_raylib_font_register_prop_handler_glyphInfo(&php_raylib_font_prop_handlers, "chars", php_raylib_font_chars, php_raylib_font_write_chars);


    // Types
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_DEFAULT", FONT_DEFAULT);
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_BITMAP", FONT_BITMAP);
    REGISTER_RAYLIB_FONT_CLASS_CONST_LONG("FONT_SDF", FONT_SDF);
}