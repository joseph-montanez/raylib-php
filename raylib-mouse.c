//
// Created by Joseph Montanez on 4/8/18.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowText ShowTextWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-utils.h"
#include "raylib-mouse.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Mouse PHP Custom Object
//------------------------------------------------------------------------------------------------------

static zend_class_entry *php_raylib_mouse_class_entry;
zend_object_handlers php_raylib_mouse_object_handlers;

void php_raylib_mouse_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_mouse_object *intern = php_raylib_mouse_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_mouse_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_mouse_object *intern;
    intern = (php_raylib_mouse_object*) ecalloc(1, sizeof(php_raylib_mouse_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_mouse_object_handlers;

    return &intern->std;
}

/* {{{ REGISTER_RAYLIB_MOUSE_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_MOUSE_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_mouse_class_entry, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling

PHP_METHOD(Mouse, __construct)
{
    php_raylib_mouse_object *intern = Z_MOUSE_OBJ_P(getThis());
}

//bool IsMouseButtonPressed(int button)
PHP_METHOD(Mouse, isButtonPressed)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsMouseButtonPressed(zend_long_2int(button)));
}

//bool IsMouseButtonDown(int button)
PHP_METHOD(Mouse, isButtonDown)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsMouseButtonDown(zend_long_2int(button)));
}

//bool IsMouseButtonReleased(int button)
PHP_METHOD(Mouse, isButtonReleased)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsMouseButtonReleased(zend_long_2int(button)));
}

//bool IsMouseButtonUp(int button)
PHP_METHOD(Mouse, isButtonUp)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsMouseButtonUp(zend_long_2int(button)));
}

//int GetMouseX(void)
PHP_METHOD(Mouse, getX)
{
    RETURN_LONG(GetMouseX());
}

//int GetMouseY(void)
PHP_METHOD(Mouse, getY)
{
    RETURN_LONG(GetMouseY());
}

//Vector2 GetMousePosition(void)
PHP_METHOD(Mouse, getPosition)
{
    Vector2 mousePosition = GetMousePosition();

    array_init(return_value);
    add_assoc_double(return_value, "x", (double) mousePosition.x);
    add_assoc_double(return_value, "y", (double) mousePosition.y);
}

//void SetMousePosition(Vector2 position);
PHP_METHOD(Mouse, setPosition)
{
    zval *position;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(position)
    ZEND_PARSE_PARAMETERS_END();

    SetMousePosition(php_array_to_vector2(position));
}

//void SetMouseScale(float scale);
PHP_METHOD(Mouse, setScale)
{
    double scale;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_DOUBLE(scale)
    ZEND_PARSE_PARAMETERS_END();

    SetMouseScale((float) scale);
}

//int GetMouseWheelMove(void)
PHP_METHOD(Mouse, getWheelMove)
{
    RETURN_LONG(GetMouseWheelMove());
}


const zend_function_entry php_raylib_mouse_methods[] = {
        PHP_ME(Mouse, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Mouse, isButtonPressed, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, isButtonDown, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, isButtonReleased, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, isButtonUp, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getX, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getY, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getPosition, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, setPosition, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, setScale, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getWheelMove, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_mouse_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib\\Input", "Mouse", php_raylib_mouse_methods);
    php_raylib_mouse_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_mouse_ce->create_object = php_raylib_mouse_new;
    php_raylib_mouse_class_entry = zend_register_internal_class(&ce);

    memcpy(&php_raylib_mouse_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_mouse_object_handlers.offset = XtOffsetOf(php_raylib_mouse_object, std);
    php_raylib_mouse_object_handlers.free_obj = &php_raylib_mouse_free_storage;
    php_raylib_mouse_object_handlers.clone_obj = NULL;

    // Mouse Buttons
    REGISTER_RAYLIB_MOUSE_CLASS_CONST_LONG("LEFT_BUTTON", MOUSE_LEFT_BUTTON);
    REGISTER_RAYLIB_MOUSE_CLASS_CONST_LONG("RIGHT_BUTTON", MOUSE_RIGHT_BUTTON);
    REGISTER_RAYLIB_MOUSE_CLASS_CONST_LONG("MIDDLE_BUTTON", MOUSE_MIDDLE_BUTTON);
}

#undef Rectangle
#undef CloseWindow
#undef ShowText
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA

