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

void php_raylib_window_free_storage(zend_object *object)
{
    php_raylib_window_object *intern = php_raylib_window_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_window_new(zend_class_entry *ce)
{
    php_raylib_window_object *intern;
    intern = (php_raylib_window_object*) ecalloc(1, sizeof(php_raylib_window_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_window_object_handlers;

    return &intern->std;
}

// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_window__construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, __construct)
{
    php_raylib_window_object *intern = Z_WINDOW_OBJ_P(ZEND_THIS);
}

// Initialize window and OpenGL context
// void InitWindow(int width, int height, const char *title);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_init, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()
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

// Check if KEY_ESCAPE pressed or Close icon pressed
// bool WindowShouldClose(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_shouldClose, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, shouldClose)
{
    RETURN_BOOL(WindowShouldClose());
}

// Close window and unload OpenGL context
// void CloseWindow(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_close, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, close)
{
    CloseWindow();
}

// Check if window has been initialized successfully
// bool IsWindowReady(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isReady, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isReady)
{
    RETURN_BOOL(IsWindowReady());
}

// Check if window is currently fullscreen
// bool IsWindowFullscreen(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isFullscreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isFullscreen)
{
//    RETURN_BOOL(false);
    RETURN_BOOL(IsWindowFullscreen());
}

// Check if window is currently hidden (only PLATFORM_DESKTOP)
// bool IsWindowHidden(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isHidden, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isHidden)
{
    RETURN_BOOL(IsWindowHidden());
}

// Check if window is currently minimized (only PLATFORM_DESKTOP)
// bool IsWindowMinimized(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isMinimized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isMinimized)
{
    RETURN_BOOL(IsWindowMinimized());
}

// Check if window is currently maximized (only PLATFORM_DESKTOP)
// bool IsWindowMaximized(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isMaximized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isMaximized)
{
    RETURN_BOOL(IsWindowMaximized());
}

// Check if window is currently focused (only PLATFORM_DESKTOP)
// bool IsWindowFocused(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isFocused, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isFocused)
{
    RETURN_BOOL(IsWindowFocused());
}

// Check if window has been resized last frame
// bool IsWindowResized(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isResized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isResized)
{
    RETURN_BOOL(IsWindowResized());
}

// Check if one specific window flag is enabled
// bool IsWindowState(unsigned int flag);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_isState, 0, 0, 1)
    ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, isState)
{
    zend_long flag;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(flag)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsWindowState(zend_long_2int(flag)));
}

// Set window configuration state using flags
// void SetWindowState(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setState, 0, 0, 1)
    ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, setState)
{
    zend_long flag;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(flag)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowState(zend_long_2int(flag));
}


// Clear window configuration state flags
// void ClearWindowState(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_clearState, 0, 0, 1)
    ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, clearState)
{
    zend_long flag;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(flag)
    ZEND_PARSE_PARAMETERS_END();

    ClearWindowState(zend_long_2int(flag));
}

// Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
// void ToggleFullscreen(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_toggleFullscreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, toggleFullscreen)
{
    ToggleFullscreen();
}

// Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
// void MaximizeWindow(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_maximize, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, maximize)
{
    MaximizeWindow();
}

// Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
// void MinimizeWindow(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_minimize, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, minimize)
{
    MinimizeWindow();
}

// Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
// void RestoreWindow(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_restore, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, restore)
{
    RestoreWindow();
}

// Set icon for window (only PLATFORM_DESKTOP)
// void SetWindowIcon(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setIcon, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, setIcon)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_OBJECT(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *intern = Z_IMAGE_OBJ_P(image);

    SetWindowIcon(intern->image);
}

// Set title for window (only PLATFORM_DESKTOP)
// void SetWindowTitle(const char *title);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setTitle, 0, 0, 1)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, setTitle)
{
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowTitle(title->val);
}

// Set window position on screen (only PLATFORM_DESKTOP)
// void SetWindowPosition(int x, int y);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setPosition, 0, 0, 2)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setMonitor, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, setMonitor)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowMonitor(zend_long_2int(monitor));
}

//void SetWindowMinSize(int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setMinSize, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setSize, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getScreenWidth, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getScreenWidth)
{
    RETURN_LONG(GetScreenWidth());
}

//int GetScreenHeight(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getScreenHeight, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getScreenHeight)
{
    RETURN_LONG(GetScreenHeight());
}

//RLAPI int GetMonitorCount(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorCount, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorCount)
{
    RETURN_LONG(GetMonitorCount());
}

//RLAPI int GetMonitorWidth(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorWidth, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorWidth((int) monitor));
}

//RLAPI int GetMonitorHeight(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorHeight, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorHeight((int) monitor));
}

//RLAPI int GetMonitorPhysicalWidth(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorPhysicalWidth, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorPhysicalWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorPhysicalWidth((int) monitor));
}

//RLAPI int GetMonitorPhysicalHeight(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorPhysicalHeight, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorPhysicalHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorPhysicalHeight((int) monitor));
}

//RLAPI int GetMonitorRefreshRate(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorRefreshRate, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorRefreshRate)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetMonitorRefreshRate((int) monitor));
}

//RLAPI Vector2 GetWindowPosition(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getPosition, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getPosition)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = GetWindowPosition();

    RETURN_OBJ(&result->std);
}

// Get window scale DPI factor
// RLAPI Vector2 GetWindowScaleDPI(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getScaleDPI, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getScaleDPI)
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_vector2_ce);

    php_raylib_vector2_object *result = Z_VECTOR2_OBJ_P(obj);
    result->vector2 = GetWindowScaleDPI();

    RETURN_OBJ(&result->std);
}

//RLAPI const char *GetMonitorName(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getMonitorName, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getMonitorName)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_STRING(GetMonitorName((int) monitor));
}

//RLAPI const char *GetClipboardText(void);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_getClipboardText, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, getClipboardText)
{
    RETURN_STRING(GetClipboardText());
}

//RLAPI void SetClipboardText(const char *text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_setClipboardText, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_METHOD(Window, setClipboardText)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();

    SetClipboardText((const char *)text);
}



const zend_function_entry php_raylib_window_methods[] = {
        PHP_ME(Window, __construct             , arginfo_window__construct              , ZEND_ACC_PUBLIC)
        PHP_ME(Window, init                    , arginfo_window_init                    , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, shouldClose             , arginfo_window_shouldClose             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, close                   , arginfo_window_close                   , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isReady                 , arginfo_window_isReady                 , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isFullscreen            , arginfo_window_isFullscreen            , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isHidden                , arginfo_window_isHidden                , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isMinimized             , arginfo_window_isMinimized             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isMaximized             , arginfo_window_isMaximized             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isFocused               , arginfo_window_isFocused               , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isResized               , arginfo_window_isResized               , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, isState                 , arginfo_window_isState                 , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setState                , arginfo_window_setState                , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, clearState              , arginfo_window_clearState              , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, toggleFullscreen        , arginfo_window_toggleFullscreen        , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, maximize                , arginfo_window_maximize                , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, minimize                , arginfo_window_minimize                , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, restore                 , arginfo_window_restore                 , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setIcon                 , arginfo_window_setIcon                 , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setTitle                , arginfo_window_setTitle                , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setPosition             , arginfo_window_setPosition             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setMonitor              , arginfo_window_setMonitor              , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setMinSize              , arginfo_window_setMinSize              , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setSize                 , arginfo_window_setSize                 , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getScreenWidth          , arginfo_window_getScreenWidth          , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getScreenHeight         , arginfo_window_getScreenHeight         , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorCount         , arginfo_window_getMonitorCount         , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorWidth         , arginfo_window_getMonitorWidth         , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorHeight        , arginfo_window_getMonitorHeight        , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorPhysicalWidth , arginfo_window_getMonitorPhysicalWidth , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorPhysicalHeight, arginfo_window_getMonitorPhysicalHeight, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorRefreshRate   , arginfo_window_getMonitorRefreshRate   , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getPosition             , arginfo_window_getPosition             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getScaleDPI             , arginfo_window_getScaleDPI             , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getMonitorName          , arginfo_window_getMonitorName          , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, getClipboardText        , arginfo_window_getClipboardText        , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Window, setClipboardText        , arginfo_window_setClipboardText        , ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_window_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Window", php_raylib_window_methods);
    php_raylib_window_ce = zend_register_internal_class(&ce);
    php_raylib_window_ce->create_object = php_raylib_window_new;

    memcpy(&php_raylib_window_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_window_object_handlers.offset = XtOffsetOf(php_raylib_window_object, std);
    php_raylib_window_object_handlers.free_obj = &php_raylib_window_free_storage;
    php_raylib_window_object_handlers.clone_obj = NULL;
}