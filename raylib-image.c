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

static zval *php_raylib_image_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_image_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_image_prop_handler *hnd = NULL;
    const zend_object_handlers *std_hnd;

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
    const zend_object_handlers *std_hnd;

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
    const zend_object_handlers *std_hnd;
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

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    intern->image = LoadImage(fileName->val);
}

// Load image from Color array data (RGBA - 32bit)
// RLAPI Image LoadImageEx(Color *pixels, int width, int height);
PHP_METHOD(Image, fromColors)
{
    zval *pixels;
    zend_long width;
    zend_long height;
    HashTable *pixelsArr;
    zval *zv;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_ARRAY(pixels)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    pixelsArr = Z_ARRVAL_P(pixels);

    // Count the number of elements in array
    int numPixels = zend_hash_num_elements(pixelsArr);
    Color *pixelsP = (Color *)safe_emalloc(numPixels, sizeof(Color), 0);

    // Load pixels from hash to an array
    int n = 0;
    ZEND_HASH_FOREACH_VAL(pixelsArr, zv) {
        if (Z_TYPE_P(zv) == IS_OBJECT) {
            php_raylib_color_object *obj = Z_COLOR_OBJ_P(zv);
            pixelsP[n] = obj->color;
        }
        n++;
    } ZEND_HASH_FOREACH_END();

    // Create Image Object
    object_init_ex(return_value, php_raylib_image_ce);
    zend_object *object = php_raylib_image_new(php_raylib_image_ce);
    php_raylib_image_object *internImage = php_raylib_image_fetch_object(object);

    // Load From Pixels
    internImage->image = LoadImageEx(pixelsP, (int) width, (int) height);

    ZVAL_OBJ(return_value, object);
}

// Load image from RAW file data
// RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);
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
PHP_METHOD(Image, getData)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    int numOfPixels = intern->image.width * intern->image.height;

    Color* colors = GetImageData(intern->image);

    array_init_size(return_value, numOfPixels);

    for (int i = 0; i < numOfPixels; i++) {
        zval *color = malloc(sizeof(zval));
        object_init_ex(color, php_raylib_color_ce);

        php_raylib_color_object *result = Z_COLOR_OBJ_P(color);
        result->color = colors[i];

        add_index_zval(return_value, i, color);
    }
}


// Get pixel data from image as Vector4 array (float normalized)
// Vector4 *GetImageDataNormalized(Image image)
PHP_METHOD(Image, getDataNormalized)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);

    int numOfPixels = intern->image.width * intern->image.height;

    Vector4* vector4s = GetImageDataNormalized(intern->image);

    array_init_size(return_value, numOfPixels);

    for (int i = 0; i < numOfPixels; i++) {
        zval *vector4 = malloc(sizeof(zval));
        object_init_ex(vector4, php_raylib_vector4_ce);

        php_raylib_vector4_object *result = Z_VECTOR4_OBJ_P(vector4);
        result->vector4 = vector4s[i];

        add_index_zval(return_value, i, vector4);
    }
}

// Draw a source image within a destination image (tint applied to source)
// RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);
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
// RLAPI void ImageDrawText(Image *dst, Vector2 position, const char *text, int fontSize, Color color);
PHP_METHOD(Image, drawText)
{
    zval *position;
    zend_string *text;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(position)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawText(&intern->image, phpPosition->vector2, text->val, (int) fontSize, phpColor->color);
}


// Draw text (custom sprite font) within an image (destination)
// RLAPI void ImageDrawTextEx(Image *dst, Vector2 position, Font font, const char *text, float fontSize, float spacing, Color color);
PHP_METHOD(Image, drawTextEx)
{
    zval *position;
    zval *font;
    zend_string *text;
    double fontSize;
    double spacing;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    ImageDrawTextEx(&intern->image, phpPosition->vector2, phpFont->font, text->val, (float) fontSize, (float) spacing, phpColor->color);
}

// RLAPI Image ImageText(const char *text, int fontSize, Color color);
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

// Convert image data to desired format
// RLAPI void ImageFormat(Image *image, int newFormat);
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
PHP_METHOD(Image, alphaPremultiply)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageAlphaPremultiply(&intern->image);
}

// Crop an image to a defined rectangle
// RLAPI void ImageCrop(Image *image, Rectangle crop);
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
PHP_METHOD(Image, genMipmaps)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageMipmaps(&intern->image);
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
// RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);
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
PHP_METHOD(Image, flipVertical)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageFlipVertical(&intern->image);
}

// Flip image horizontally
// RLAPI void ImageFlipHorizontal(Image *image);
PHP_METHOD(Image, flipHorizontal)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageFlipHorizontal(&intern->image);
}

// Rotate image clockwise 90deg
// RLAPI void ImageRotateCW(Image *image);
PHP_METHOD(Image, rotateClockwise)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageRotateCW(&intern->image);
}

// Rotate image counter-clockwise 90deg
// RLAPI void ImageRotateCCW(Image *image);
PHP_METHOD(Image, rotateCounterClockwise)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageRotateCCW(&intern->image);
}

// Modify image color: tint
// RLAPI void ImageColorTint(Image *image, Color color);
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
PHP_METHOD(Image, colorInvert)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageColorInvert(&intern->image);
}

// Modify image color: grayscale
// RLAPI void ImageColorGrayscale(Image *image);
PHP_METHOD(Image, colorGrayscale)
{
    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(ZEND_THIS);
    ImageColorGrayscale(&intern->image);
}

// Modify image color: contrast (-100 to 100)
// RLAPI void ImageColorContrast(Image *image, float contrast);
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

// Extract color palette from image to maximum size (memory should be freed)
// RLAPI Color *ImageExtractPalette(Image image, int maxPaletteSize, int *extractCount);
PHP_METHOD(Image, extractPalette)
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
    Color *colors = ImageExtractPalette(intern->image, (int) maxPaletteSize, &extractCount);
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

const zend_function_entry php_raylib_image_methods[] = {
        PHP_ME(Image, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, fromFont, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromColors, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromImage, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Image, fromRaw, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) // RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);
        PHP_ME(Image, toTexture, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, getData, NULL, ZEND_ACC_PUBLIC) // RLAPI Color *GetImageData(Image image);
        PHP_ME(Image, getDataNormalized, NULL, ZEND_ACC_PUBLIC) // RLAPI Vector4 *GetImageDataNormalized(Image image)
        PHP_ME(Image, copy, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, toPot, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, export, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, exportAsCode, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, draw, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, drawText, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, drawTextEx, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, format, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaMask, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaClear, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaCrop, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, alphaPremultiply, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, crop, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resize, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resizeNearestNeighbor, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, resizeCanvas, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, genMipmaps, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, dither, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, flipVertical, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, flipHorizontal, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, rotateClockwise, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, rotateCounterClockwise, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorTint, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorInvert, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorGrayscale, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorContrast, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorBrightness, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, colorReplace, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, extractPalette, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, getAlphaBorder, NULL, ZEND_ACC_PUBLIC)
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