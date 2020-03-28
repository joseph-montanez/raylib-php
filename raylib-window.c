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
#include "raylib-utils.h"
#include "raylib-vector2.h"
#include "raylib-window.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Window PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_window_object_handlers;

void php_raylib_window_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_window_object *intern = php_raylib_window_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_window_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_window_object *intern;
    intern = (php_raylib_window_object*) ecalloc(1, sizeof(php_raylib_window_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_window_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Window, __construct)
{
    php_raylib_window_object *intern = Z_WINDOW_OBJ_P(ZEND_THIS);
}

PHP_METHOD(Window, init)
{
    zend_long width;
    zend_long height;
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
            Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();

    InitWindow(zend_long_2int(width), zend_long_2int(height), title->val);
}

PHP_METHOD(Window, isReady)
{
    RETURN_BOOL(IsWindowReady());
}

PHP_METHOD(Window, shouldClose)
{
    RETURN_BOOL(WindowShouldClose());
}

PHP_METHOD(Window, isMinimized)
{
    RETURN_BOOL(IsWindowMinimized());
}

PHP_METHOD(Window, isResized)
{
    RETURN_BOOL(IsWindowResized());
}

PHP_METHOD(Window, isHidden)
{
    RETURN_BOOL(IsWindowHidden());
}

// TODO: Need to link raylib 3.0
//RLAPI bool IsWindowFullscreen(void);
PHP_METHOD(Window, isFullscreen)
{
    RETURN_BOOL(false);
//    RETURN_BOOL(IsWindowFullscreen());
}

PHP_METHOD(Window, unhideWindow)
{
    UnhideWindow();
}

PHP_METHOD(Window, hideWindow)
{
    HideWindow();
}

PHP_METHOD(Window, toggleFullscreen)
{
    ToggleFullscreen();
}

PHP_METHOD(Window, setIcon)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_OBJECT(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(image);

    SetWindowIcon(intern->image);
}

PHP_METHOD(Window, setTitle)
{
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowTitle(title->val);
}

PHP_METHOD(Window, setPosition)
{
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(x)
            Z_PARAM_LONG(y)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowPosition(zend_long_2int(x), zend_long_2int(y));
}

//void SetWindowMonitor(int monitor);
PHP_METHOD(Window, setMonitor)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowMonitor(zend_long_2int(monitor));
}

//void SetWindowMinSize(int width, int height);
PHP_METHOD(Window, setMinSize)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowMinSize(zend_long_2int(width), zend_long_2int(height));
}

//void SetWindowSize(int width, int height);
PHP_METHOD(Window, setSize)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(width)
            Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowSize(zend_long_2int(width), zend_long_2int(height));
}

//int GetScreenWidth(void);
PHP_METHOD(Window, getScreenWidth)
{
    RETURN_LONG(GetScreenWidth());
}

//int GetScreenHeight(void);
PHP_METHOD(Window, getScreenHeight)
{
    RETURN_LONG(GetScreenHeight());
}

//RLAPI int GetMonitorCount(void);
PHP_METHOD(Window, getMonitorCount)
{
    RETURN_LONG(GetMonitorCount());
}

//RLAPI int GetMonitorWidth(int monitor);
PHP_METHOD(Window, getMonitorWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorWidth((int) monitor));
}

//RLAPI int GetMonitorHeight(int monitor);
PHP_METHOD(Window, getMonitorHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorHeight((int) monitor));
}

//RLAPI int GetMonitorPhysicalWidth(int monitor);
PHP_METHOD(Window, getMonitorPhysicalWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorPhysicalWidth((int) monitor));
}

//RLAPI int GetMonitorPhysicalHeight(int monitor);
PHP_METHOD(Window, getMonitorPhysicalHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorPhysicalHeight((int) monitor));
}

//RLAPI Vector2 GetWindowPosition(void);
PHP_METHOD(Window, getWindowPosition)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = GetWindowPosition();

    RETURN_OBJ(&result->std);
}

//RLAPI const char *GetMonitorName(int monitor);
PHP_METHOD(Window, getMonitorName)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_STRING(GetMonitorName((int) monitor));
}

//RLAPI const char *GetClipboardText(void);
PHP_METHOD(Window, getClipboardText)
{
    RETURN_STRING(GetClipboardText());
}

//RLAPI void SetClipboardText(const char *text);
PHP_METHOD(Window, setClipboardText)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();

    SetClipboardText((const char *)text);
}

//void CloseWindow(void);
PHP_METHOD(Window, close)
{
    CloseWindow();
}



const zend_function_entry php_raylib_window_methods[] = {
        PHP_ME(Window, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Window, init, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, shouldClose, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, close, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isReady, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isMinimized, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isResized, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isHidden, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isFullscreen, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, unhideWindow, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, hideWindow, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, toggleFullscreen, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setIcon, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setTitle, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setPosition, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setMonitor, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setMinSize, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setSize, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getScreenWidth, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getScreenHeight, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorCount, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorWidth, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorHeight, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorPhysicalWidth, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorPhysicalHeight, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getWindowPosition, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorName, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getClipboardText, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setClipboardText, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_window_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Window", php_raylib_window_methods);
    php_raylib_window_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_window_ce->create_object = php_raylib_window_new;

    memcpy(&php_raylib_window_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_window_object_handlers.offset = XtOffsetOf(php_raylib_window_object, std);
    php_raylib_window_object_handlers.free_obj = &php_raylib_window_free_storage;
    php_raylib_window_object_handlers.clone_obj = NULL;
}