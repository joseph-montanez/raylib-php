#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-image.h"
#include "raylib-texture.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Image PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_image_object_handlers;

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

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_image_object_handlers;

    return &intern->std;
}

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

const zend_function_entry php_raylib_image_methods[] = {
        PHP_ME(Image, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Image, toTexture, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_image_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Image", php_raylib_image_methods);
    php_raylib_image_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_image_ce->create_object = php_raylib_image_new;

    memcpy(&php_raylib_image_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_image_object_handlers.offset = XtOffsetOf(php_raylib_image_object, std);
    php_raylib_image_object_handlers.free_obj = &php_raylib_image_free_storage;
    php_raylib_image_object_handlers.clone_obj = NULL;
}

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA