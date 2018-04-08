//
// Created by Joseph Montanez on 4/7/18.
//
#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"
#include "raylib-cursor.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Cursor PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_cursor_object_handlers;

void php_raylib_cursor_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_cursor_object *intern = php_raylib_cursor_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_cursor_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_cursor_object *intern;
    intern = (php_raylib_cursor_object*) ecalloc(1, sizeof(php_raylib_cursor_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_cursor_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Cursor, __construct)
{
    php_raylib_cursor_object *intern = Z_CURSOR_OBJ_P(getThis());
}

//void ShowCursor(void);
PHP_METHOD(Cursor, show)
{
    ShowCursor();
}

//void HideCursor(void);
PHP_METHOD(Cursor, hide)
{
    HideCursor();
}

//bool IsCursorHidden(void);
PHP_METHOD(Cursor, isHidden)
{
    RETURN_BOOL(IsWindowReady());
}

//void EnableCursor(void);
PHP_METHOD(Cursor, enable)
{
    EnableCursor();
}

//void DisableCursor(void);
PHP_METHOD(Cursor, disable)
{
    DisableCursor();
}


const zend_function_entry php_raylib_cursor_methods[] = {
        PHP_ME(Cursor, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Cursor, show, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Cursor, hide, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Cursor, isHidden, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Cursor, enable, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Cursor, disable, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_cursor_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Cursor", php_raylib_cursor_methods);
    php_raylib_cursor_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_cursor_ce->create_object = php_raylib_cursor_new;

    memcpy(&php_raylib_cursor_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_cursor_object_handlers.offset = XtOffsetOf(php_raylib_cursor_object, std);
    php_raylib_cursor_object_handlers.free_obj = &php_raylib_cursor_free_storage;
    php_raylib_cursor_object_handlers.clone_obj = NULL;
}