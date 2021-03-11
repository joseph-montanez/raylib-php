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
#include "raylib-utils.h"
#include "raylib-vector2.h"
#include "raylib-mouse.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Mouse PHP Custom Object
//------------------------------------------------------------------------------------------------------

static zend_class_entry *php_raylib_mouse_class_entry;
zend_object_handlers php_raylib_mouse_object_handlers;

void php_raylib_mouse_free_storage(zend_object *object)
{
    php_raylib_mouse_object *intern = php_raylib_mouse_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_mouse_new(zend_class_entry *ce)
{
    php_raylib_mouse_object *intern;
    intern = (php_raylib_mouse_object*) ecalloc(1, sizeof(php_raylib_mouse_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
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
    php_raylib_mouse_object *intern = Z_MOUSE_OBJ_P(ZEND_THIS);
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
    php_raylib_vector2_object *intern;

    //-- Allocate vector2
    intern = (php_raylib_vector2_object*) ecalloc(1, sizeof(php_raylib_vector2_object) + zend_object_properties_size(php_raylib_vector2_ce));
    //-- Intialize vector2
    zend_object_std_init(&intern->std, php_raylib_vector2_ce);
    object_properties_init(&intern->std, php_raylib_vector2_ce);
    //-- Assigned handler
    intern->std.handlers = &php_raylib_vector2_object_handlers;

    //-- Assigned value to vector2
    intern->vector2 = GetMousePosition();

    RETURN_OBJ(&intern->std);
}

// Set mouse position XY
// void SetMousePosition(int x, int y);
PHP_METHOD(Mouse, setPosition)
{
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
    ZEND_PARSE_PARAMETERS_END();

    SetMousePosition((int) x, (int) y);
}

// Set mouse offset
// void SetMouseOffset(int offsetX, int offsetY);
PHP_METHOD(Mouse, setOffset)
{
    zend_long offsetX;
    zend_long offsetY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(offsetY)
    ZEND_PARSE_PARAMETERS_END();

    SetMouseOffset((int) offsetX, (int) offsetY);
}

// void SetMouseScale(float scale);
PHP_METHOD(Mouse, setScale)
{
    double scaleX;
    double scaleY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(scaleX)
        Z_PARAM_DOUBLE(scaleY)
    ZEND_PARSE_PARAMETERS_END();

    SetMouseScale((float) scaleX, (float) scaleY);
}

// Returns mouse wheel movement Y
// float GetMouseWheelMove(void);
PHP_METHOD(Mouse, getWheelMove)
{
    RETURN_DOUBLE((double) GetMouseWheelMove());
}

// Returns mouse cursor if (MouseCursor enum)
// int GetMouseCursor(void);
PHP_METHOD(Mouse, getCursor)
{
    RETURN_LONG(GetMouseCursor());
}

// Set mouse cursor
// void SetMouseCursor(int cursor);
PHP_METHOD(Mouse, setCursor)
{
    zend_long cursor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(cursor)
    ZEND_PARSE_PARAMETERS_END();

    SetMouseCursor((int) cursor);
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
        PHP_ME(Mouse, setOffset, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, setScale, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getWheelMove, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, getCursor, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Mouse, setCursor, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_mouse_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib\\Input", "Mouse", php_raylib_mouse_methods);
    php_raylib_mouse_ce = zend_register_internal_class(&ce);
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

