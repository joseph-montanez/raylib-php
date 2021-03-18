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
#include "raylib-rectangle.h"
#include "raylib-font.h"
#include "raylib-vector2.h"
#include "raylib-vector4.h"
#include "raylib-texture.h"
#include "raylib-color.h"
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

static zval *php_raylib_image_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
    php_raylib_image_object *obj;
    zval *retval = NULL;
    raylib_image_prop_handler *hnd = NULL;

    obj = php_raylib_image_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd == NULL) {
        retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_image_read_property(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_image_object *obj;
    zval *retval = NULL;
    raylib_image_prop_handler *hnd = NULL;

    obj = php_raylib_image_fetch_object(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, name);
    }

    if (hnd) {
        retval = php_raylib_image_property_reader(obj, hnd, rv);
    } else {
        retval = zend_std_read_property(object, name, type, cache_slot, rv);
    }

    return retval;
}
/* }}} */

static int php_raylib_image_has_property(zend_object *object, zend_string *name, int has_set_exists, void **cache_slot) /* {{{ */
{
    php_raylib_image_object *obj;
    raylib_image_prop_handler *hnd = NULL;
    int ret = 0;

    if ((hnd = zend_hash_find_ptr(obj->prop_handler, name)) != NULL) {
        switch (has_set_exists) {
            case ZEND_PROPERTY_EXISTS:
                ret = 1;
                break;
            case ZEND_PROPERTY_NOT_EMPTY: {
                zval rv;
                zval *value = php_raylib_image_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
                if (value != &EG(uninitialized_zval)) {
                    convert_to_boolean(value);
                    ret = Z_TYPE_P(value) == IS_TRUE ? 1 : 0;
                }
                break;
            }
            case ZEND_PROPERTY_ISSET: {
                zval rv;
                zval *value = php_raylib_image_read_property(object, name, BP_VAR_IS, cache_slot, &rv);
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

static HashTable *php_raylib_image_get_gc(zend_object *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_image_get_properties(zend_object *object)/* {{{ */
{
    php_raylib_image_object *obj;
    HashTable *props;
    raylib_image_prop_handler *hnd;
    zend_string *key;

    obj = php_raylib_image_fetch_object(object);
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

void php_raylib_image_free_storage(zend_object *object)
{
    php_raylib_image_object *intern = php_raylib_image_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadImage(intern->image);
}

zend_object * php_raylib_image_new_ex(zend_class_entry *ce, zend_object *orig)
{
    php_raylib_image_object *intern;
    intern = (php_raylib_image_object*) ecalloc(1, sizeof(php_raylib_image_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_image_prop_handlers;

    if (orig) {
        php_raylib_image_object *other = php_raylib_image_fetch_object(orig);

        intern->image = ImageCopy(other->image);
    } else {
        intern->image = (Image) {
                .data = NULL,
                .width = 0,
                .height = 0,
                .mipmaps = 0,
                .format = 0,
        };
    }

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_image_object_handlers;

    return &intern->std;
}

zend_object * php_raylib_image_new(zend_class_entry *ce)
{
    return php_raylib_image_new_ex(ce, NULL);
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_image__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    intern->image = LoadImage(fileName->val);
}

// Load image from Color array data (RGBA - 32bit)
// RLAPI Image LoadImageEx(Color *pixels, int width, int height);
//PHP_METHOD(Image, fromColors)
//{
//    zval *pixels;
//    zend_long width;
//    zend_long height;
//    HashTable *pixelsArr;
//    zval *zv;
//
//    ZEND_PARSE_PARAMETERS_START(3, 3)
//            Z_PARAM_ARRAY(pixels)
//            Z_PARAM_LONG(width)
//            Z_PARAM_LONG(height)
//    ZEND_PARSE_PARAMETERS_END();
//
//    pixelsArr = Z_ARRVAL_P(pixels);
//
//    // Count the number of elements in array
//    int numPixels = zend_hash_num_elements(pixelsArr);
//    Color *pixelsP = (Color *)safe_emalloc(numPixels, sizeof(Color), 0);
//
//    // Load pixels from hash to an array
//    int n = 0;
//    ZEND_HASH_FOREACH_VAL(pixelsArr, zv) {
//        if (Z_TYPE_P(zv) == IS_OBJECT) {
//            php_raylib_color_object *obj = Z_COLOR_OBJ_P(zv);
//            pixelsP[n] = obj->color;
//        }
//        n++;
//    } ZEND_HASH_FOREACH_END();
//
//    // Create Image Object
//    object_init_ex(return_value, php_raylib_image_ce);
//    zend_object *object = php_raylib_image_new(php_raylib_image_ce);
//    php_raylib_image_object *internImage = php_raylib_image_fetch_object(object);
//
//    // Load From Pixels
//    internImage->image = LoadImageEx(pixelsP, (int) width, (int) height);
//
//    ZVAL_OBJ(return_value, object);
//}

// Load image from RAW file data
// RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_fromRaw, 0, 0, 5)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_INFO(0, headerSize)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, fromRaw)
{
    zend_string *fileName;
    zend_long width;
    zend_long height;
    zend_long format;
    zend_long headerSize;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STR(fileName)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(format)
        Z_PARAM_LONG(headerSize)
    ZEND_PARSE_PARAMETERS_END();

    // Create Image Object
    object_init_ex(return_value, php_raylib_image_ce);
    zend_object *object = php_raylib_image_new(php_raylib_image_ce);
    php_raylib_image_object *internImage = php_raylib_image_fetch_object(object);

    // Load From Pixels
    internImage->image = LoadImageRaw(fileName->val, (int) width, (int) height, (int) format, (int) headerSize);

    ZVAL_OBJ(return_value, object);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_image_toTexture, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, toTexture)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    object_init_ex(return_value, php_raylib_texture_ce);

    zend_object *object = php_raylib_texture_new(php_raylib_texture_ce);

    php_raylib_texture_object *internTexture = php_raylib_texture_fetch_object(object);

    internTexture->texture = LoadTextureFromImage(intern->image);

    ZVAL_OBJ(return_value, object);
}

//Image ImageCopy(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_copy, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, copy)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    object_init_ex(return_value, php_raylib_image_ce);

    zend_object *object = php_raylib_image_new(php_raylib_image_ce);

    php_raylib_image_object *internTexture = php_raylib_image_fetch_object(object);

    internTexture->image = ImageCopy(intern->image);

    ZVAL_OBJ(return_value, object);
}

//ImageToPOT(Image *image, Color fillColor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_toPot, 0, 0, 1)
    ZEND_ARG_INFO(0, fillColor)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, toPot)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    zval *fillColor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(fillColor)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpFillColor = Z_COLOR_OBJ_P(fillColor);

    ImageToPOT(&intern->image, phpFillColor->color);
}

// RLAPI void ExportImage(const char *fileName, Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_export, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, export)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ExportImage(intern->image, fileName->val);
}

// RLAPI void ExportImageAsCode(Image image, const char *fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_exportAsCode, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, exportAsCode)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ExportImageAsCode(intern->image, fileName->val);
}

// Get pixel data from image as a Color struct array
// RLAPI Color *GetImageData(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_getData, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, getData)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    int numOfPixels = intern->image.width * intern->image.height;

    Color* colors = LoadImageColors(intern->image);

    array_init_size(return_value, numOfPixels);

    for (int i = 0; i < numOfPixels; i++) {
        zval *color = malloc(sizeof(zval));
        object_init_ex(color, php_raylib_color_ce);

        php_raylib_color_object *result = Z_COLOR_OBJ_P(color);
        result->color = colors[i];

        add_index_zval(return_value, i, color);
    }
}

// Draw a source image within a destination image (tint applied to source)
// RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_draw, 0, 0, 4)
    ZEND_ARG_INFO(0, src)
    ZEND_ARG_INFO(0, srcRec)
    ZEND_ARG_INFO(0, dstRec)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, draw)
{
    zval *src;
    zval *srcRec;
    zval *dstRec;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(src)
        Z_PARAM_ZVAL(srcRec)
        Z_PARAM_ZVAL(dstRec)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    php_raylib_image_object *phpSrc = Z_IMAGE_OBJ_P(src);
    php_raylib_rectangle_object *phpSrcRec = Z_RECTANGLE_OBJ_P(srcRec);
    php_raylib_rectangle_object *phpDstRec = Z_RECTANGLE_OBJ_P(dstRec);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    ImageDraw(
        &intern->image,
        phpSrc->image,
        phpSrcRec->rectangle,
        phpDstRec->rectangle,
        phpTint->color
    );
}

// Draw text (default font) within an image (destination)
// RLAPI void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_drawText, 0, 0, 5)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, drawText)
{
    zend_long posX;
    zend_long posY;
    zend_string *text;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawText(&intern->image, text->val, (int) posX, (int) posY, (int) fontSize, phpColor->color);
}


// Draw text (custom sprite font) within an image (destination)
// RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_drawTextEx, 0, 0, 6)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, drawTextEx)
{
    zval *position;
    zval *font;
    zend_string *text;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);
    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    ImageDrawTextEx(&intern->image, phpFont->font, ZSTR_VAL(text), phpPosition->vector2, (float) fontSize, (float) spacing, phpTint->color);
}

// RLAPI Image ImageText(const char *text, int fontSize, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_fromDefaultFont, 0, 0, 3)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, fromDefaultFont)
{
    zend_string *text;
    zend_long fontSize;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);


    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_image_ce);

    php_raylib_image_object *result = Z_IMAGE_OBJ_P(obj);
    result->image = ImageText(text->val, (int) fontSize, phpTint->color);

    RETURN_OBJ(&result->std);
}

// RLAPI Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_fromFont, 0, 0, 5)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, fromFont)
{
    zval *font;
    zend_string *text;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);


    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_image_ce);

    php_raylib_image_object *result = Z_IMAGE_OBJ_P(obj);
    result->image = ImageTextEx(phpFont->font, text->val, (float) fontSize, (float) spacing, phpTint->color);

    RETURN_OBJ(&result->std);
}

// Create an image from another image piece
//RLAPI Image ImageFromImage(Image image, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_fromImage, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, fromImage)
{
    zval *image;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);

    //-- Create Image Object
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_image_ce);

    php_raylib_image_object *result = Z_IMAGE_OBJ_P(obj);
    //-- Assign new image struct to image object
    result->image = ImageFromImage(phpImage->image, phpRec->rectangle);

    RETURN_OBJ(&result->std);
}

// Create an image from an animated image, currently only GIF is supported
//RLAPI Image LoadImageAnim(const char *fileName, int *frames);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_fromAnim, 0, 0, 2)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(1, frames)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, fromAnim)
{
    zend_string *fileName;
    zval *frames;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(fileName)
        Z_PARAM_ZVAL(frames)
    ZEND_PARSE_PARAMETERS_END();

    int framesOut;

    zend_object *phpImage = php_raylib_image_new(php_raylib_image_ce);

    php_raylib_image_object *result = php_raylib_image_fetch_object(phpImage);

    //-- Assign new image struct to image object
    result->image = LoadImageAnim(fileName->val, &framesOut);

    //-- Assign frames to the output variable
    ZVAL_DEREF(frames);
    if (Z_TYPE_P(frames) == IS_LONG) {
        Z_LVAL_P(frames) = framesOut;
    } else if (Z_TYPE_P(frames) == IS_DOUBLE) {
        Z_DVAL_P(frames) = framesOut;
    } else {
        php_error_docref(NULL, E_WARNING, "unexpected argument type, $frames must be an int or float.");
    }

    RETURN_OBJ(&result->std);
}

// Convert image data to desired format
// RLAPI void ImageFormat(Image *image, int newFormat);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_format, 0, 0, 1)
    ZEND_ARG_INFO(0, newFormat)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, format)
{
    zend_long newFormat;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(newFormat)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageFormat(&intern->image, (int) newFormat);
}

// Apply alpha mask to image
// RLAPI void ImageAlphaMask(Image *image, Image alphaMask);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_alphaMask, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, alphaMask)
{
    zval *alphaMask;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(alphaMask)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_image_object *phpAlphaMask = Z_IMAGE_OBJ_P(alphaMask);

    ImageAlphaMask(&intern->image, phpAlphaMask->image);
}

// Clear alpha channel to desired color
// RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_alphaClear, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, alphaClear)
{
    zval *color;
    double threshold;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageAlphaClear(&intern->image, phpColor->color, (float) threshold);
}

// Crop image depending on alpha value
// RLAPI void ImageAlphaCrop(Image *image, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_alphaCrop, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, alphaCrop)
{
    zval *color;
    double threshold;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageAlphaClear(&intern->image, phpColor->color, (float) threshold);
}

// Premultiply alpha channel
// RLAPI void ImageAlphaPremultiply(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_alphaPremultiply, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, alphaPremultiply)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageAlphaPremultiply(&intern->image);
}

// Crop an image to a defined rectangle
// RLAPI void ImageCrop(Image *image, Rectangle crop);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_crop, 0, 0, 1)
    ZEND_ARG_INFO(0, crop)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, crop)
{
    zval *crop;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(crop)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_rectangle_object *phpCrop = Z_RECTANGLE_OBJ_P(crop);

    ImageCrop(&intern->image, phpCrop->rectangle);
}

// Resize image (Bicubic scaling algorithm)
// RLAPI void ImageResize(Image *image, int newWidth, int newHeight);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_resize, 0, 0, 2)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, resize)
{
    zend_long newWidth;
    zend_long newHeight;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageResize(&intern->image, (int) newWidth, (int) newHeight);
}

// Resize image (Nearest-Neighbor scaling algorithm)
// RLAPI void ImageResizeNN(Image *image, int newWidth, int newHeight);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_resizeNearestNeighbor, 0, 0, 2)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, resizeNearestNeighbor)
{
    zend_long newWidth;
    zend_long newHeight;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageResizeNN(&intern->image, (int) newWidth, (int) newHeight);
}

// Resize canvas and fill with color
// RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_resizeCanvas, 0, 0, 5)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, resizeCanvas)
{
    zend_long newWidth;
    zend_long newHeight;
    zend_long offsetX;
    zend_long offsetY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(offsetY)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageResizeCanvas(&intern->image, (int) newWidth, (int) newHeight, (int) offsetX, (int) offsetY, phpColor->color);
}

// Generate all mipmap levels for a provided image
// RLAPI void ImageMipmaps(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_genMipmaps, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, genMipmaps)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageMipmaps(&intern->image);
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
// RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_dither, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, dither)
{
    zend_long rBpp;
    zend_long gBpp;
    zend_long bBpp;
    zend_long aBpp;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(rBpp)
        Z_PARAM_LONG(gBpp)
        Z_PARAM_LONG(bBpp)
        Z_PARAM_LONG(aBpp)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageDither(&intern->image, (int) rBpp, (int) gBpp, (int) bBpp, (int) aBpp);
}

// Flip image vertically
// RLAPI void ImageFlipVertical(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_flipVertical, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, flipVertical)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageFlipVertical(&intern->image);
}

// Flip image horizontally
// RLAPI void ImageFlipHorizontal(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_flipHorizontal, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, flipHorizontal)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageFlipHorizontal(&intern->image);
}

// Rotate image clockwise 90deg
// RLAPI void ImageRotateCW(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_rotateClockwise, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, rotateClockwise)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageRotateCW(&intern->image);
}

// Rotate image counter-clockwise 90deg
// RLAPI void ImageRotateCCW(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_rotateCounterClockwise, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, rotateCounterClockwise)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageRotateCCW(&intern->image);
}

// Modify image color: tint
// RLAPI void ImageColorTint(Image *image, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorTint, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorTint)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageColorTint(&intern->image, phpColor->color);
}

// Modify image color: invert
// RLAPI void ImageColorInvert(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorInvert, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorInvert)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageColorInvert(&intern->image);
}

// Modify image color: grayscale
// RLAPI void ImageColorGrayscale(Image *image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorGrayscale, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorGrayscale)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageColorGrayscale(&intern->image);
}

// Modify image color: contrast (-100 to 100)
// RLAPI void ImageColorContrast(Image *image, float contrast);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorContrast, 0, 0, 1)
    ZEND_ARG_INFO(0, contrast)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorContrast)
{
    double contrast;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(contrast)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageColorContrast(&intern->image, (float) contrast);
}

// Modify image color: brightness (-255 to 255)
// RLAPI void ImageColorBrightness(Image *image, int brightness);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorBrightness, 0, 0, 1)
    ZEND_ARG_INFO(0, brightness)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorBrightness) // new ImageColorBrightness
{
    zend_long brightness;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(brightness)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    ImageColorBrightness(&intern->image, (int) brightness);
}

// Modify image color: replace color
// RLAPI void ImageColorReplace(Image *image, Color color, Color replace);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_colorReplace, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, replace)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, colorReplace) // new ImageColorReplace
{
    zval *color;
    zval *replace;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_ZVAL(color)
            Z_PARAM_ZVAL(replace)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_color_object *phpReplace = Z_COLOR_OBJ_P(replace);

    ImageColorReplace(&intern->image, phpColor->color, phpReplace->color);
}

// Load colors palette from image as a Color array (RGBA - 32bit)
// RLAPI Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorsCount);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_loadPalette, 0, 0, 2)
    ZEND_ARG_INFO(0, maxPaletteSize)
    ZEND_ARG_INFO(0, z_extractCount)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, loadPalette)
{
    double maxPaletteSize;
    zval *z_extractCount;
    int extractCount;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(maxPaletteSize)
        Z_PARAM_ZVAL(z_extractCount)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    extractCount = (int) zval_get_long(z_extractCount);
    Color *colors = LoadImagePalette(intern->image, (int) maxPaletteSize, &extractCount);
    ZEND_TRY_ASSIGN_REF_LONG(z_extractCount, extractCount);

    array_init_size(return_value, extractCount);

    for (int i = 0; i < extractCount; i++) {
        zval *color = malloc(sizeof(zval));
        object_init_ex(color, php_raylib_color_ce);

        php_raylib_color_object *result = Z_COLOR_OBJ_P(color);
        result->color = colors[i];
        add_index_zval(return_value, i, color);
    }
}

// Get image alpha border rectangle
// RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_getAlphaBorder, 0, 0, 1)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, getAlphaBorder)
{
    double threshold;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_rectangle_ce);

    php_raylib_rectangle_object *result = Z_RECTANGLE_OBJ_P(obj);
    result->rectangle = GetImageAlphaBorder(intern->image, (float) threshold);

    RETURN_OBJ(&result->std);
}

// Draw rectangle within an image
// RLAPI void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_image_drawRectangleRec, 0, 0, 2)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_METHOD(Image, drawRectangleRec)
{
    zval *rec;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec);
        Z_PARAM_ZVAL(color);
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawRectangleRec(
        &intern->image,
        phpRec->rectangle,
        phpColor->color
    );
}

const zend_function_entry php_raylib_image_methods[] = {
//        PHP_ME(Image, fromColors, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, __construct           , arginfo_image__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Image, fromDefaultFont       , arginfo_image_fromDefaultFont, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromFont              , arginfo_image_fromFont, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromImage             , arginfo_image_fromImage, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromAnim              , arginfo_image_fromAnim, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromRaw               , arginfo_image_fromRaw, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) // RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);
        PHP_ME(Image, toTexture             , arginfo_image_toTexture, ZEND_ACC_PUBLIC)
        PHP_ME(Image, getData               , arginfo_image_getData, ZEND_ACC_PUBLIC)                 // RLAPI Color *GetImageData(Image image);
        PHP_ME(Image, copy                  , arginfo_image_copy, ZEND_ACC_PUBLIC)
        PHP_ME(Image, toPot                 , arginfo_image_toPot, ZEND_ACC_PUBLIC)
        PHP_ME(Image, export                , arginfo_image_export, ZEND_ACC_PUBLIC)
        PHP_ME(Image, exportAsCode          , arginfo_image_exportAsCode, ZEND_ACC_PUBLIC)
        PHP_ME(Image, draw                  , arginfo_image_draw, ZEND_ACC_PUBLIC)
        PHP_ME(Image, drawText              , arginfo_image_drawText, ZEND_ACC_PUBLIC)
        PHP_ME(Image, drawTextEx            , arginfo_image_drawTextEx,ZEND_ACC_PUBLIC)
        PHP_ME(Image, drawRectangleRec      , arginfo_image_drawRectangleRec, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaMask             , arginfo_image_alphaMask, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaClear            , arginfo_image_alphaClear, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaCrop             , arginfo_image_alphaCrop, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaPremultiply      , arginfo_image_alphaPremultiply, ZEND_ACC_PUBLIC)
        PHP_ME(Image, crop                  , arginfo_image_crop, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resize                , arginfo_image_resize, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resizeNearestNeighbor , arginfo_image_resizeNearestNeighbor, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resizeCanvas          , arginfo_image_resizeCanvas, ZEND_ACC_PUBLIC)
        PHP_ME(Image, genMipmaps            , arginfo_image_genMipmaps, ZEND_ACC_PUBLIC)
        PHP_ME(Image, dither                , arginfo_image_dither, ZEND_ACC_PUBLIC)
        PHP_ME(Image, flipVertical          , arginfo_image_flipVertical, ZEND_ACC_PUBLIC)
        PHP_ME(Image, flipHorizontal        , arginfo_image_flipHorizontal, ZEND_ACC_PUBLIC)
        PHP_ME(Image, rotateClockwise       , arginfo_image_rotateClockwise, ZEND_ACC_PUBLIC)
        PHP_ME(Image, rotateCounterClockwise, arginfo_image_rotateCounterClockwise, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorTint             , arginfo_image_colorTint, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorInvert           , arginfo_image_colorInvert, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorGrayscale        , arginfo_image_colorGrayscale, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorContrast         , arginfo_image_colorContrast, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorBrightness       , arginfo_image_colorBrightness, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorReplace          , arginfo_image_colorReplace, ZEND_ACC_PUBLIC)
        PHP_ME(Image, loadPalette           , arginfo_image_loadPalette, ZEND_ACC_PUBLIC)
        PHP_ME(Image, getAlphaBorder        , arginfo_image_getAlphaBorder, ZEND_ACC_PUBLIC)

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
    php_raylib_image_ce = zend_register_internal_class(&ce);
    php_raylib_image_ce->create_object = php_raylib_image_new;

    zend_hash_init(&php_raylib_image_prop_handlers, 0, NULL, php_raylib_image_free_prop_handler, 1);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "width", php_raylib_image_width);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "height", php_raylib_image_height);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "mipmaps", php_raylib_image_mipmaps);
    php_raylib_image_register_prop_handler(&php_raylib_image_prop_handlers, "height", php_raylib_image_format);

}