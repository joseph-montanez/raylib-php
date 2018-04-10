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
#include "raylib-rendertexture.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib RenderTexture PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_rendertexture_object_handlers;

void php_raylib_rendertexture_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_rendertexture_object *intern = php_raylib_rendertexture_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadRenderTexture(intern->rendertexture);
}

zend_object * php_raylib_rendertexture_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_rendertexture_object *intern;
    intern = (php_raylib_rendertexture_object*) ecalloc(1, sizeof(php_raylib_rendertexture_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_rendertexture_object_handlers;

    return &intern->std;
}

PHP_METHOD(RenderTexture, __construct)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rendertexture_object *intern = Z_RENDERTEXTURE_OBJ_P(getThis());
    intern->rendertexture = LoadRenderTexture(zend_long_2int(width), zend_long_2int(height));
}

PHP_METHOD(RenderTexture, texture)
{
    php_raylib_rendertexture_object *intern = Z_RENDERTEXTURE_OBJ_P(getThis());

    //-- TODO: Implement
    //RETURN_LONG(intern->rendertexture.texture);
}

PHP_METHOD(RenderTexture, depth)
{
    php_raylib_rendertexture_object *intern = Z_RENDERTEXTURE_OBJ_P(getThis());

    //-- TODO: Implement
    //RETURN_LONG(intern->rendertexture.depth);
}

PHP_METHOD(RenderTexture, id)
{
    php_raylib_rendertexture_object *intern = Z_RENDERTEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->rendertexture.id);
}

const zend_function_entry php_raylib_rendertexture_methods[] = {
        PHP_ME(RenderTexture, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(RenderTexture, texture, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(RenderTexture, depth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(RenderTexture, id, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void php_raylib_rendertexture_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "RenderTexture", php_raylib_rendertexture_methods);
    php_raylib_rendertexture_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_rendertexture_ce->create_object = php_raylib_rendertexture_new;

    memcpy(&php_raylib_rendertexture_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_rendertexture_object_handlers.offset = XtOffsetOf(php_raylib_rendertexture_object, std);
    php_raylib_rendertexture_object_handlers.free_obj = &php_raylib_rendertexture_free_storage;
    php_raylib_rendertexture_object_handlers.clone_obj = NULL;
}

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA