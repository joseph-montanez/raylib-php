//
// Created by Joseph Montanez on 4/9/18.
//

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
#include "raylib-spritefont.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib SpriteFont PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_spritefont_object_handlers;

void php_raylib_spritefont_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_spritefont_object *intern = php_raylib_spritefont_fetch_object(object);

    zend_object_std_dtor(&intern->std);

    UnloadSpriteFont(intern->spritefont);
}

zend_object * php_raylib_spritefont_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_spritefont_object *intern;
    intern = (php_raylib_spritefont_object*) ecalloc(1, sizeof(php_raylib_spritefont_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_spritefont_object_handlers;

    return &intern->std;
}

PHP_METHOD(SpriteFont, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_spritefont_object *intern = Z_SPRITEFONT_OBJ_P(getThis());
    intern->spritefont = LoadSpriteFont(fileName->val);
}


const zend_function_entry php_raylib_spritefont_methods[] = {
        PHP_ME(SpriteFont, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void php_raylib_spritefont_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "SpriteFont", php_raylib_spritefont_methods);
    php_raylib_spritefont_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_spritefont_ce->create_object = php_raylib_spritefont_new;

    memcpy(&php_raylib_spritefont_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_spritefont_object_handlers.offset = XtOffsetOf(php_raylib_spritefont_object, std);
    php_raylib_spritefont_object_handlers.free_obj = &php_raylib_spritefont_free_storage;
    php_raylib_spritefont_object_handlers.clone_obj = NULL;
}

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA
