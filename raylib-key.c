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
#include "raylib-key.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Key PHP Custom Object
//------------------------------------------------------------------------------------------------------

static zend_class_entry *php_raylib_key_class_entry;
zend_object_handlers php_raylib_key_object_handlers;

void php_raylib_key_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_key_object *intern = php_raylib_key_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_key_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_key_object *intern;
    intern = (php_raylib_key_object*) ecalloc(1, sizeof(php_raylib_key_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_key_object_handlers;

    return &intern->std;
}

/* {{{ REGISTER_RAYLIB_KEY_CLASS_CONST_LONG */
#define REGISTER_RAYLIB_KEY_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(php_raylib_key_class_entry, const_name, sizeof(const_name)-1, (zend_long)value);
/* }}} */

// PHP object handling

PHP_METHOD(Key, __construct)
{
    php_raylib_key_object *intern = Z_KEY_OBJ_P(getThis());
}

/*
 *
RLAPI bool IsKeyPressed(int key);                             // Detect if a key has been pressed once
RLAPI bool IsKeyDown(int key);                                // Detect if a key is being pressed
RLAPI bool IsKeyReleased(int key);                            // Detect if a key has been released once
RLAPI bool IsKeyUp(int key);                                  // Detect if a key is NOT being pressed
RLAPI int GetKeyPressed(void);                                // Get latest key pressed
RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
 */

//bool IsKeyPressed(int key)
PHP_METHOD(Key, isPressed)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyPressed(zend_long_2int(key)));
}

//bool IsKeyDown(int key)
PHP_METHOD(Key, isDown)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyDown(zend_long_2int(key)));
}

//bool IsKeyReleased(int key)
PHP_METHOD(Key, isReleased)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyReleased(zend_long_2int(key)));
}

//bool IsKeyUp(int key)
PHP_METHOD(Key, isUp)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyUp(zend_long_2int(key)));
}

//int GetKeyPressed(void)
PHP_METHOD(Key, getPressed)
{
    RETURN_LONG(GetKeyPressed());
}

//void SetExitKey(int key)
PHP_METHOD(Key, setExit)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    SetExitKey(zend_long_2int(key));
}


const zend_function_entry php_raylib_key_methods[] = {
        PHP_ME(Key, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Key, isPressed, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Key, isDown, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Key, isReleased, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Key, getPressed, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Key, setExit, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_key_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib\\Input", "Key", php_raylib_key_methods);
    php_raylib_key_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_key_ce->create_object = php_raylib_key_new;
    php_raylib_key_class_entry = zend_register_internal_class(&ce);

    memcpy(&php_raylib_key_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_key_object_handlers.offset = XtOffsetOf(php_raylib_key_object, std);
    php_raylib_key_object_handlers.free_obj = &php_raylib_key_free_storage;
    php_raylib_key_object_handlers.clone_obj = NULL;

    // Keyboard Function Keys
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("SPACE", KEY_SPACE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("ESCAPE", KEY_ESCAPE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("ENTER", KEY_ENTER);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("TAB", KEY_TAB);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("BACKSPACE", KEY_BACKSPACE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("INSERT", KEY_INSERT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("DELETE", KEY_DELETE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("RIGHT", KEY_RIGHT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("LEFT", KEY_LEFT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("DOWN", KEY_DOWN);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("UP", KEY_UP);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("PAGE_UP", KEY_PAGE_UP);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("PAGE_DOWN", KEY_PAGE_DOWN);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("HOME", KEY_HOME);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("END", KEY_END);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("CAPS_LOCK", KEY_CAPS_LOCK);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("SCROLL_LOCK", KEY_SCROLL_LOCK);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("NUM_LOCK", KEY_NUM_LOCK);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("PRINT_SCREEN", KEY_PRINT_SCREEN);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("PAUSE", KEY_PAUSE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F1", KEY_F1);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F2", KEY_F2);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F3", KEY_F3);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F4", KEY_F4);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F5", KEY_F5);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F6", KEY_F6);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F7", KEY_F7);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F8", KEY_F8);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F9", KEY_F9);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F10", KEY_F10);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F11", KEY_F11);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F12", KEY_F12);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("LEFT_SHIFT", KEY_LEFT_SHIFT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("LEFT_CONTROL", KEY_LEFT_CONTROL);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("LEFT_ALT", KEY_LEFT_ALT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("RIGHT_SHIFT", KEY_RIGHT_SHIFT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("RIGHT_CONTROL", KEY_RIGHT_CONTROL);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("RIGHT_ALT", KEY_RIGHT_ALT);

    // Keyboard Alpha Numeric Keys
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("ZERO", KEY_ZERO);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("ONE", KEY_ONE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("TWO", KEY_TWO);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("THREE", KEY_THREE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("FOUR", KEY_FOUR);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("FIVE", KEY_FIVE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("SIX", KEY_SIX);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("SEVEN", KEY_SEVEN);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("EIGHT", KEY_EIGHT);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("NINE", KEY_NINE);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("A", KEY_A);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("B", KEY_B);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("C", KEY_C);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("D", KEY_D);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("E", KEY_E);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("F", KEY_F);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("G", KEY_G);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("H", KEY_H);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("I", KEY_I);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("J", KEY_J);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("K", KEY_K);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("L", KEY_L);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("M", KEY_M);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("N", KEY_N);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("O", KEY_O);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("P", KEY_P);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("Q", KEY_Q);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("R", KEY_R);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("S", KEY_S);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("T", KEY_T);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("U", KEY_U);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("V", KEY_V);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("W", KEY_W);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("X", KEY_X);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("Y", KEY_Y);
    REGISTER_RAYLIB_KEY_CLASS_CONST_LONG("Z", KEY_Z);
}
