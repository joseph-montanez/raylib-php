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
#include "raylib-gamepad.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Gamepad PHP Custom Object
//------------------------------------------------------------------------------------------------------

static zend_class_entry *php_raylib_gamepad_class_entry;
zend_object_handlers php_raylib_gamepad_object_handlers;

void php_raylib_gamepad_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_gamepad_object *intern = php_raylib_gamepad_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_gamepad_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_gamepad_object *intern;
    intern = (php_raylib_gamepad_object*) ecalloc(1, sizeof(php_raylib_gamepad_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_gamepad_object_handlers;

    return &intern->std;
}

/* {{{ REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_gamepad_class_entry, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling

PHP_METHOD(Gamepad, __construct)
{
    php_raylib_gamepad_object *intern = Z_GAMEPAD_OBJ_P(getThis());
}

// Detect if a gamepad is available
// RLAPI bool IsGamepadAvailable(int gamepad);
PHP_METHOD(Gamepad, isAvailable)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadAvailable(zend_long_2int(gamepad)));
}

// Check gamepad name (if available)
// RLAPI bool IsGamepadName(int gamepad, const char *name);
PHP_METHOD(Gamepad, isName)
{
    zend_long gamepad;
    zend_string *name;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadName(zend_long_2int(gamepad), name->val));
}

// Return gamepad internal name id
// RLAPI const char *GetGamepadName(int gamepad);
PHP_METHOD(Gamepad, getName)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    const char *gamepadName = GetGamepadName(zend_long_2int(gamepad));
    zend_string *str = zend_string_init(gamepadName, sizeof(gamepadName)-1, 0);

    RETURN_STR(str);
}

// Detect if a gamepad button has been pressed once
// RLAPI bool IsGamepadButtonPressed(int gamepad, int button);
PHP_METHOD(Gamepad, isButtonPressed)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonPressed(zend_long_2int(gamepad), zend_long_2int(button)));
}

// Detect if a gamepad button is being pressed
// RLAPI bool IsGamepadButtonDown(int gamepad, int button);
PHP_METHOD(Gamepad, isButtonDown)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonDown(zend_long_2int(gamepad), zend_long_2int(button)));
}

// Detect if a gamepad button has been released once
// RLAPI bool IsGamepadButtonReleased(int gamepad, int button);
PHP_METHOD(Gamepad, isButtonReleased)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_LONG(gamepad)
    Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonReleased(zend_long_2int(gamepad), zend_long_2int(button)));
}

// Detect if a gamepad button is NOT being pressed
// RLAPI bool IsGamepadButtonUp(int gamepad, int button);
PHP_METHOD(Gamepad, isButtonUp)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonUp(zend_long_2int(gamepad), zend_long_2int(button)));
}

// Get the last gamepad button pressed
// int GetGamepadButtonPressed(void)
PHP_METHOD(Gamepad, getButtonPressed)
{
    RETURN_LONG(GetGamepadButtonPressed());
}

// Return gamepad axis count for a gamepad
// RLAPI int GetGamepadAxisCount(int gamepad);
PHP_METHOD(Gamepad, getAxisCount)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetGamepadAxisCount(zend_long_2int(gamepad)));
}

// Return axis movement value for a gamepad axis
// RLAPI float GetGamepadAxisMovement(int gamepad, int axis);
PHP_METHOD(Gamepad, getAxisMovement)
{
    zend_long gamepad;
    zend_long axis;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(axis)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_DOUBLE(GetGamepadAxisMovement(zend_long_2int(gamepad), zend_long_2int(axis)));
}

const zend_function_entry php_raylib_gamepad_methods[] = {
        PHP_ME(Gamepad, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Gamepad, isAvailable, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, isName, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, getName, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, isButtonPressed, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, isButtonDown, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, isButtonReleased, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, isButtonUp, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, getButtonPressed, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, getAxisCount, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Gamepad, getAxisMovement, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_gamepad_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib\\Input", "Gamepad", php_raylib_gamepad_methods);
    php_raylib_gamepad_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_gamepad_ce->create_object = php_raylib_gamepad_new;
    php_raylib_gamepad_class_entry = zend_register_internal_class(&ce);

    memcpy(&php_raylib_gamepad_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_gamepad_object_handlers.offset = XtOffsetOf(php_raylib_gamepad_object, std);
    php_raylib_gamepad_object_handlers.free_obj = &php_raylib_gamepad_free_storage;
    php_raylib_gamepad_object_handlers.clone_obj = NULL;

    // Gamepad Number
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("PLAYER1", GAMEPAD_PLAYER1);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("PLAYER2", GAMEPAD_PLAYER2);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("PLAYER3", GAMEPAD_PLAYER3);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("PLAYER4", GAMEPAD_PLAYER4);

    // Gamepad Buttons
    // This is here just for error checking
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN);

    // This is normally a DPAD
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT);

    // This normally corresponds with PlayStation and Xbox controllers
    // XBOX: [Y,X,A,B]
    // PS3: [Triangle,Square,Cross,Circle]
    // No support for 6 button controllers though..
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

    // Triggers
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2);

    // These are buttons in the center of the gamepad
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT);    //PS3 Select
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE);              //PS Button/XBOX Button
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT);  //PS3 Start

    // These are the joystick press in buttons
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB);


    // This is here just for error checking
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_UNKNOWN", GAMEPAD_AXIS_UNKNOWN);

    // Left stick
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y);

    // Right stick
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X);
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y);

    // Pressure levels for the back triggers
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER);    // [1..-1] (pressure-level)
    REGISTER_RAYLIB_GAMEPAD_CLASS_CONST_LONG("AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER);  // [1..-1] (pressure-level)
}

