#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-texture.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Texture PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_texture_object_handlers;

void php_raylib_texture_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_texture_object *intern = php_raylib_texture_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadTexture(intern->texture);
}

zend_object * php_raylib_texture_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_texture_object *intern;
    intern = (php_raylib_texture_object*) ecalloc(1, sizeof(php_raylib_texture_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_texture_object_handlers;

    return &intern->std;
}

PHP_METHOD(Texture, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    intern->texture = LoadTexture(fileName->val);
}

PHP_METHOD(Texture, width)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->texture.width);
}

PHP_METHOD(Texture, height)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->texture.height);
}

PHP_METHOD(Texture, format)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->texture.format);
}

PHP_METHOD(Texture, id)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->texture.id);
}

PHP_METHOD(Texture, mipmaps)
{
    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());
    RETURN_LONG(intern->texture.mipmaps);
}

PHP_METHOD(Texture, draw)
{
    zend_long posX;
    zend_long posY;
    zval *colorArr;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_ZVAL(colorArr)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *intern = Z_TEXTURE_OBJ_P(getThis());

    DrawTexture(intern->texture, zend_long_2int(posX), zend_long_2int(posY), php_array_to_color(colorArr));
}

const zend_function_entry php_raylib_texture_methods[] = {
        PHP_ME(Texture, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, width, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, height, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, format, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, id, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, mipmaps, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Texture, draw, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void php_raylib_texture_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Texture", php_raylib_texture_methods);
    php_raylib_texture_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_texture_ce->create_object = php_raylib_texture_new;

    memcpy(&php_raylib_texture_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_texture_object_handlers.offset = XtOffsetOf(php_raylib_texture_object, std);
    php_raylib_texture_object_handlers.free_obj = &php_raylib_texture_free_storage;
    php_raylib_texture_object_handlers.clone_obj = NULL;
}