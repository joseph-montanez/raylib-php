/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Joseph Montanez                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

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
/*#define NONLS           // All NLS defines and routines*/
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
#define VC_EXTRALEAN      // Maybe fix?
#define WIN32_LEAN_AND_MEAN // Maybe fix?

/* Type required before windows.h inclusion  */
typedef struct tagMSG* LPMSG;

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_raylib.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix.h"
#include "color.h"
#include "rectangle.h"
#include "image.h"
#include "texture.h"
#include "rendertexture.h"
#include "npatchinfo.h"
#include "glyphinfo.h"
#include "font.h"
#include "camera3d.h"
#include "camera2d.h"
#include "mesh.h"
#include "shader.h"
#include "materialmap.h"
#include "material.h"
#include "transform.h"
#include "boneinfo.h"
#include "model.h"
#include "modelanimation.h"
#include "ray.h"
#include "raycollision.h"
#include "boundingbox.h"
#include "wave.h"
#include "audiostream.h"
#include "sound.h"
#include "music.h"
#include "vrdeviceinfo.h"
#include "vrstereoconfig.h"
#include "filepathlist.h"
#include "texture.h"
#include "texture.h"
#include "rendertexture.h"
#include "camera3d.h"
#include "vector4.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_confirm_raylib_compiled, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(confirm_raylib_compiled)
{
    char *arg = NULL;
    size_t arg_len;
//    size_t arg_len, len;
    zend_string *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "raylib", arg);

    RETURN_STR(strg);
}

// Initialize window and OpenGL context
// RLAPI void InitWindow(int width, int height, const char * title);
ZEND_BEGIN_ARG_INFO_EX(arginfo_InitWindow, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()
PHP_FUNCTION(InitWindow)
{
    zend_long width;
    zend_long height;
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();


    InitWindow((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, title->val);

}

// Check if KEY_ESCAPE pressed or Close icon pressed
// RLAPI bool WindowShouldClose();
ZEND_BEGIN_ARG_INFO_EX(arginfo_WindowShouldClose, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(WindowShouldClose)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(WindowShouldClose());
}

// Close window and unload OpenGL context
// RLAPI void CloseWindow();
ZEND_BEGIN_ARG_INFO_EX(arginfo_CloseWindow, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CloseWindow)
{

    ZEND_PARSE_PARAMETERS_NONE();

    CloseWindow();

}

// Check if window has been initialized successfully
// RLAPI bool IsWindowReady();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowReady, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowReady)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowReady());
}

// Check if window is currently fullscreen
// RLAPI bool IsWindowFullscreen();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowFullscreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowFullscreen)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowFullscreen());
}

// Check if window is currently hidden (only PLATFORM_DESKTOP)
// RLAPI bool IsWindowHidden();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowHidden, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowHidden)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowHidden());
}

// Check if window is currently minimized (only PLATFORM_DESKTOP)
// RLAPI bool IsWindowMinimized();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowMinimized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowMinimized)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowMinimized());
}

// Check if window is currently maximized (only PLATFORM_DESKTOP)
// RLAPI bool IsWindowMaximized();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowMaximized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowMaximized)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowMaximized());
}

// Check if window is currently focused (only PLATFORM_DESKTOP)
// RLAPI bool IsWindowFocused();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowFocused, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowFocused)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowFocused());
}

// Check if window has been resized last frame
// RLAPI bool IsWindowResized();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowResized, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowResized)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsWindowResized());
}

// Check if one specific window flag is enabled
// RLAPI bool IsWindowState(unsigned int flag);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWindowState, 0, 0, 1)
    ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWindowState)
{
    zend_long flag;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flag)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsWindowState((flag <= INT_MAX) ? (int) ((zend_long) flag) : -1));
}

// Set window configuration state using flags (only PLATFORM_DESKTOP)
// RLAPI void SetWindowState(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowState, 0, 0, 1)
    ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowState)
{
    zend_long flags;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flags)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowState((flags <= INT_MAX) ? (int) ((zend_long) flags) : -1);

}

// Clear window configuration state flags
// RLAPI void ClearWindowState(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ClearWindowState, 0, 0, 1)
    ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ClearWindowState)
{
    zend_long flags;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flags)
    ZEND_PARSE_PARAMETERS_END();


    ClearWindowState((flags <= INT_MAX) ? (int) ((zend_long) flags) : -1);

}

// Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
// RLAPI void ToggleFullscreen();
ZEND_BEGIN_ARG_INFO_EX(arginfo_ToggleFullscreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ToggleFullscreen)
{

    ZEND_PARSE_PARAMETERS_NONE();

    ToggleFullscreen();

}

// Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
// RLAPI void MaximizeWindow();
ZEND_BEGIN_ARG_INFO_EX(arginfo_MaximizeWindow, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(MaximizeWindow)
{

    ZEND_PARSE_PARAMETERS_NONE();

    MaximizeWindow();

}

// Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
// RLAPI void MinimizeWindow();
ZEND_BEGIN_ARG_INFO_EX(arginfo_MinimizeWindow, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(MinimizeWindow)
{

    ZEND_PARSE_PARAMETERS_NONE();

    MinimizeWindow();

}

// Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
// RLAPI void RestoreWindow();
ZEND_BEGIN_ARG_INFO_EX(arginfo_RestoreWindow, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(RestoreWindow)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RestoreWindow();

}

// Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
// RLAPI void SetWindowIcon(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowIcon, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowIcon)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    SetWindowIcon(*php_raylib_image_fetch_data(phpImage));

}

// Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
// RLAPI void SetWindowIcons(Image* images, int count);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowIcons, 0, 0, 2)
    ZEND_ARG_INFO(0, images)
    ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowIcons)
{
    zval *images;
    zend_long count;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(images)
        Z_PARAM_LONG(count)
    ZEND_PARSE_PARAMETERS_END();

    zval *images_element;
    int images_index;
    HashTable *images_hash = Z_ARRVAL_P(images);
    SEPARATE_ARRAY(images);
    int images_count = zend_hash_num_elements(images_hash);
    Image* images_array = safe_emalloc(sizeof(Image*), images_count, 0);
    ZEND_HASH_FOREACH_VAL(images_hash, images_element) {
        ZVAL_DEREF(images_element);
        if ((Z_TYPE_P(images_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(images_element), php_raylib_image_ce))) {
            php_raylib_image_object *image_obj =  Z_IMAGE_OBJ_P(images_element);
            images_array[images_index] = *php_raylib_image_fetch_data(image_obj);
        }

        images_index++;
    } ZEND_HASH_FOREACH_END();

    SetWindowIcons(images_array, (count <= INT_MAX) ? (int) ((zend_long) count) : -1);

}

// Set title for window (only PLATFORM_DESKTOP)
// RLAPI void SetWindowTitle(const char * title);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowTitle, 0, 0, 1)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowTitle)
{
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowTitle(title->val);

}

// Set window position on screen (only PLATFORM_DESKTOP)
// RLAPI void SetWindowPosition(int x, int y);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowPosition, 0, 0, 2)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowPosition)
{
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowPosition((x <= INT_MAX) ? (int) ((zend_long) x) : -1, (y <= INT_MAX) ? (int) ((zend_long) y) : -1);

}

// Set monitor for the current window (fullscreen mode)
// RLAPI void SetWindowMonitor(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowMonitor, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowMonitor)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowMonitor((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1);

}

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
// RLAPI void SetWindowMinSize(int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowMinSize, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowMinSize)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowMinSize((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1);

}

// Set window dimensions
// RLAPI void SetWindowSize(int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetWindowSize, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetWindowSize)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowSize((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1);

}

// Get current screen width
// RLAPI int GetScreenWidth();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetScreenWidth, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetScreenWidth)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetScreenWidth());
}

// Get current screen height
// RLAPI int GetScreenHeight();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetScreenHeight, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetScreenHeight)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetScreenHeight());
}

// Get number of connected monitors
// RLAPI int GetMonitorCount();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorCount, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorCount)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetMonitorCount());
}

// Get current connected monitor
// RLAPI int GetCurrentMonitor();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCurrentMonitor, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCurrentMonitor)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetCurrentMonitor());
}

// Get specified monitor position
// RLAPI Vector2 GetMonitorPosition(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorPosition, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorPosition)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    Vector2 originalResult = GetMonitorPosition((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1);
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get specified monitor width (current video mode used by monitor)
// RLAPI int GetMonitorWidth(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorWidth, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetMonitorWidth((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1));
}

// Get specified monitor height (current video mode used by monitor)
// RLAPI int GetMonitorHeight(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorHeight, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetMonitorHeight((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1));
}

// Get specified monitor physical width in millimetres
// RLAPI int GetMonitorPhysicalWidth(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorPhysicalWidth, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorPhysicalWidth)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetMonitorPhysicalWidth((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1));
}

// Get specified monitor physical height in millimetres
// RLAPI int GetMonitorPhysicalHeight(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorPhysicalHeight, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorPhysicalHeight)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetMonitorPhysicalHeight((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1));
}

// Get specified monitor refresh rate
// RLAPI int GetMonitorRefreshRate(int monitor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMonitorRefreshRate, 0, 0, 1)
    ZEND_ARG_INFO(0, monitor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMonitorRefreshRate)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetMonitorRefreshRate((monitor <= INT_MAX) ? (int) ((zend_long) monitor) : -1));
}

// Get window position XY on monitor
// RLAPI Vector2 GetWindowPosition();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetWindowPosition, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetWindowPosition)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetWindowPosition();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get window scale DPI factor
// RLAPI Vector2 GetWindowScaleDPI();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetWindowScaleDPI, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetWindowScaleDPI)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetWindowScaleDPI();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Set clipboard text content
// RLAPI void SetClipboardText(const char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetClipboardText, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetClipboardText)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    SetClipboardText(text->val);

}

// Enable waiting for events on EndDrawing(), no automatic event polling
// RLAPI void EnableEventWaiting();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EnableEventWaiting, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EnableEventWaiting)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EnableEventWaiting();

}

// Disable waiting for events on EndDrawing(), automatic events polling
// RLAPI void DisableEventWaiting();
ZEND_BEGIN_ARG_INFO_EX(arginfo_DisableEventWaiting, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DisableEventWaiting)
{

    ZEND_PARSE_PARAMETERS_NONE();

    DisableEventWaiting();

}

// Swap back buffer with front buffer (screen drawing)
// RLAPI void SwapScreenBuffer();
ZEND_BEGIN_ARG_INFO_EX(arginfo_SwapScreenBuffer, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SwapScreenBuffer)
{

    ZEND_PARSE_PARAMETERS_NONE();

    SwapScreenBuffer();

}

// Register all input events
// RLAPI void PollInputEvents();
ZEND_BEGIN_ARG_INFO_EX(arginfo_PollInputEvents, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PollInputEvents)
{

    ZEND_PARSE_PARAMETERS_NONE();

    PollInputEvents();

}

// Wait for some time (halt program execution)
// RLAPI void WaitTime(double seconds);
ZEND_BEGIN_ARG_INFO_EX(arginfo_WaitTime, 0, 0, 1)
    ZEND_ARG_INFO(0, seconds)
ZEND_END_ARG_INFO()
PHP_FUNCTION(WaitTime)
{
    double seconds;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(seconds)
    ZEND_PARSE_PARAMETERS_END();


    WaitTime((double) seconds);

}

// Shows cursor
// RLAPI void ShowCursor();
ZEND_BEGIN_ARG_INFO_EX(arginfo_ShowCursor, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ShowCursor)
{

    ZEND_PARSE_PARAMETERS_NONE();

    ShowCursor();

}

// Hides cursor
// RLAPI void HideCursor();
ZEND_BEGIN_ARG_INFO_EX(arginfo_HideCursor, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(HideCursor)
{

    ZEND_PARSE_PARAMETERS_NONE();

    HideCursor();

}

// Check if cursor is not visible
// RLAPI bool IsCursorHidden();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsCursorHidden, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsCursorHidden)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsCursorHidden());
}

// Enables cursor (unlock cursor)
// RLAPI void EnableCursor();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EnableCursor, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EnableCursor)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EnableCursor();

}

// Disables cursor (lock cursor)
// RLAPI void DisableCursor();
ZEND_BEGIN_ARG_INFO_EX(arginfo_DisableCursor, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DisableCursor)
{

    ZEND_PARSE_PARAMETERS_NONE();

    DisableCursor();

}

// Check if cursor is on the screen
// RLAPI bool IsCursorOnScreen();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsCursorOnScreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsCursorOnScreen)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsCursorOnScreen());
}

// Set background color (framebuffer clear color)
// RLAPI void ClearBackground(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ClearBackground, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ClearBackground)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ClearBackground(*php_raylib_color_fetch_data(phpColor));

}

// Setup canvas (framebuffer) to start drawing
// RLAPI void BeginDrawing();
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginDrawing, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginDrawing)
{

    ZEND_PARSE_PARAMETERS_NONE();

    BeginDrawing();

}

// End canvas drawing and swap buffers (double buffering)
// RLAPI void EndDrawing();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndDrawing, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndDrawing)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndDrawing();

}

// Begin 2D mode with custom camera (2D)
// RLAPI void BeginMode2D(Camera2D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginMode2D, 0, 0, 1)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginMode2D)
{
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera2d_object *phpCamera = Z_CAMERA2D_OBJ_P(camera);

    BeginMode2D(*php_raylib_camera2d_fetch_data(phpCamera));

}

// Ends 2D mode with custom camera
// RLAPI void EndMode2D();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndMode2D, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndMode2D)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndMode2D();

}

// Begin 3D mode with custom camera (3D)
// RLAPI void BeginMode3D(Camera3D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginMode3D, 0, 0, 1)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginMode3D)
{
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    BeginMode3D(*php_raylib_camera3d_fetch_data(phpCamera));

}

// Ends 3D mode and returns to default 2D orthographic mode
// RLAPI void EndMode3D();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndMode3D, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndMode3D)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndMode3D();

}

// Begin drawing to render texture
// RLAPI void BeginTextureMode(RenderTexture target);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginTextureMode, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginTextureMode)
{
    zval *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rendertexture_object *phpTarget = Z_RENDERTEXTURE_OBJ_P(target);

    BeginTextureMode(*php_raylib_rendertexture_fetch_data(phpTarget));

}

// Ends drawing to render texture
// RLAPI void EndTextureMode();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndTextureMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndTextureMode)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndTextureMode();

}

// Begin custom shader drawing
// RLAPI void BeginShaderMode(Shader shader);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginShaderMode, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginShaderMode)
{
    zval *shader;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(shader)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);

    BeginShaderMode(*php_raylib_shader_fetch_data(phpShader));

}

// End custom shader drawing (use default shader)
// RLAPI void EndShaderMode();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndShaderMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndShaderMode)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndShaderMode();

}

// Begin blending mode (alpha, additive, multiplied, subtract, custom)
// RLAPI void BeginBlendMode(int mode);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginBlendMode, 0, 0, 1)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginBlendMode)
{
    zend_long mode;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(mode)
    ZEND_PARSE_PARAMETERS_END();


    BeginBlendMode((mode <= INT_MAX) ? (int) ((zend_long) mode) : -1);

}

// End blending mode (reset to default: alpha blending)
// RLAPI void EndBlendMode();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndBlendMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndBlendMode)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndBlendMode();

}

// Begin scissor mode (define screen area for following drawing)
// RLAPI void BeginScissorMode(int x, int y, int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginScissorMode, 0, 0, 4)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginScissorMode)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();


    BeginScissorMode((x <= INT_MAX) ? (int) ((zend_long) x) : -1, (y <= INT_MAX) ? (int) ((zend_long) y) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1);

}

// End scissor mode
// RLAPI void EndScissorMode();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndScissorMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndScissorMode)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndScissorMode();

}

// Begin stereo rendering (requires VR simulator)
// RLAPI void BeginVrStereoMode(VrStereoConfig config);
ZEND_BEGIN_ARG_INFO_EX(arginfo_BeginVrStereoMode, 0, 0, 1)
    ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()
PHP_FUNCTION(BeginVrStereoMode)
{
    zval *config;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(config)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vrstereoconfig_object *phpConfig = Z_VRSTEREOCONFIG_OBJ_P(config);

    BeginVrStereoMode(*php_raylib_vrstereoconfig_fetch_data(phpConfig));

}

// End stereo rendering (requires VR simulator)
// RLAPI void EndVrStereoMode();
ZEND_BEGIN_ARG_INFO_EX(arginfo_EndVrStereoMode, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(EndVrStereoMode)
{

    ZEND_PARSE_PARAMETERS_NONE();

    EndVrStereoMode();

}

// Load VR stereo config for VR simulator device parameters
// RLAPI VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadVrStereoConfig, 0, 0, 1)
    ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadVrStereoConfig)
{
    zval *device;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(device)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vrdeviceinfo_object *phpDevice = Z_VRDEVICEINFO_OBJ_P(device);

    VrStereoConfig originalResult = LoadVrStereoConfig(*php_raylib_vrdeviceinfo_fetch_data(phpDevice));
    zend_object *result = php_raylib_vrstereoconfig_new_ex(php_raylib_vrstereoconfig_ce, NULL);
    php_raylib_vrstereoconfig_object *phpResult = php_raylib_vrstereoconfig_fetch_object(result);
    VrStereoConfig *vrstereoconfigData = php_raylib_vrstereoconfig_fetch_data(phpResult);
    // Dereference vrstereoconfigData for assignment back to object
    *vrstereoconfigData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Unload VR stereo config
// RLAPI void UnloadVrStereoConfig(VrStereoConfig config);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadVrStereoConfig, 0, 0, 1)
    ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadVrStereoConfig)
{
    zval *config;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(config)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vrstereoconfig_object *phpConfig = Z_VRSTEREOCONFIG_OBJ_P(config);

    UnloadVrStereoConfig(*php_raylib_vrstereoconfig_fetch_data(phpConfig));

}

// Load shader from files and bind default locations
// RLAPI Shader LoadShader(const char * vsFileName, const char * fsFileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadShader, 0, 0, 2)
    ZEND_ARG_INFO(0, vsFileName)
    ZEND_ARG_INFO(0, fsFileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadShader)
{
    zend_string *vsFileName;
    zend_string *fsFileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(vsFileName)
        Z_PARAM_STR(fsFileName)
    ZEND_PARSE_PARAMETERS_END();


    Shader originalResult = LoadShader(vsFileName->val, fsFileName->val);
    zend_object *result = php_raylib_shader_new_ex(php_raylib_shader_ce, NULL);
    php_raylib_shader_object *phpResult = php_raylib_shader_fetch_object(result);
    Shader *shaderData = php_raylib_shader_fetch_data(phpResult);
    // Dereference shaderData for assignment back to object
    *shaderData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load shader from code strings and bind default locations
// RLAPI Shader LoadShaderFromMemory(const char * vsCode, const char * fsCode);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadShaderFromMemory, 0, 0, 2)
    ZEND_ARG_INFO(0, vsCode)
    ZEND_ARG_INFO(0, fsCode)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadShaderFromMemory)
{
    zend_string *vsCode;
    zend_string *fsCode;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(vsCode)
        Z_PARAM_STR(fsCode)
    ZEND_PARSE_PARAMETERS_END();


    Shader originalResult = LoadShaderFromMemory(vsCode->val, fsCode->val);
    zend_object *result = php_raylib_shader_new_ex(php_raylib_shader_ce, NULL);
    php_raylib_shader_object *phpResult = php_raylib_shader_fetch_object(result);
    Shader *shaderData = php_raylib_shader_fetch_data(phpResult);
    // Dereference shaderData for assignment back to object
    *shaderData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if a shader is ready
// RLAPI bool IsShaderReady(Shader shader);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsShaderReady, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsShaderReady)
{
    zval *shader;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(shader)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);

    RETURN_BOOL(IsShaderReady(*php_raylib_shader_fetch_data(phpShader)));
}

// Get shader uniform location
// RLAPI int GetShaderLocation(Shader shader, const char * uniformName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetShaderLocation, 0, 0, 2)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, uniformName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetShaderLocation)
{
    zval *shader;
    zend_string *uniformName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(shader)
        Z_PARAM_STR(uniformName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);

    RETURN_LONG(GetShaderLocation(*php_raylib_shader_fetch_data(phpShader), uniformName->val));
}

// Get shader attribute location
// RLAPI int GetShaderLocationAttrib(Shader shader, const char * attribName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetShaderLocationAttrib, 0, 0, 2)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, attribName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetShaderLocationAttrib)
{
    zval *shader;
    zend_string *attribName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(shader)
        Z_PARAM_STR(attribName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);

    RETURN_LONG(GetShaderLocationAttrib(*php_raylib_shader_fetch_data(phpShader), attribName->val));
}

// Set shader uniform value (matrix 4x4)
// RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetShaderValueMatrix, 0, 0, 3)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, locIndex)
    ZEND_ARG_INFO(0, mat)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetShaderValueMatrix)
{
    zval *shader;
    zend_long locIndex;
    zval *mat;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(shader)
        Z_PARAM_LONG(locIndex)
        Z_PARAM_ZVAL(mat)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);
    php_raylib_matrix_object *phpMat = Z_MATRIX_OBJ_P(mat);

    SetShaderValueMatrix(*php_raylib_shader_fetch_data(phpShader), (locIndex <= INT_MAX) ? (int) ((zend_long) locIndex) : -1, *php_raylib_matrix_fetch_data(phpMat));

}

// Set shader uniform value for texture (sampler2d)
// RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetShaderValueTexture, 0, 0, 3)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, locIndex)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetShaderValueTexture)
{
    zval *shader;
    zend_long locIndex;
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(shader)
        Z_PARAM_LONG(locIndex)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    SetShaderValueTexture(*php_raylib_shader_fetch_data(phpShader), (locIndex <= INT_MAX) ? (int) ((zend_long) locIndex) : -1, *php_raylib_texture_fetch_data(phpTexture));

}

// Unload shader from GPU memory (VRAM)
// RLAPI void UnloadShader(Shader shader);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadShader, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadShader)
{
    zval *shader;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(shader)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_shader_object *phpShader = Z_SHADER_OBJ_P(shader);

    UnloadShader(*php_raylib_shader_fetch_data(phpShader));

}

// Get a ray trace from mouse position
// RLAPI Ray GetMouseRay(Vector2 mousePosition, Camera3D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseRay, 0, 0, 2)
    ZEND_ARG_INFO(0, mousePosition)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseRay)
{
    zval *mousePosition;
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(mousePosition)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpMousePosition = Z_VECTOR2_OBJ_P(mousePosition);
    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    Ray originalResult = GetMouseRay(*php_raylib_vector2_fetch_data(phpMousePosition), *php_raylib_camera3d_fetch_data(phpCamera));
    zend_object *result = php_raylib_ray_new_ex(php_raylib_ray_ce, NULL);
    php_raylib_ray_object *phpResult = php_raylib_ray_fetch_object(result);
    Ray *rayData = php_raylib_ray_fetch_data(phpResult);
    // Dereference rayData for assignment back to object
    *rayData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get camera transform matrix (view matrix)
// RLAPI Matrix GetCameraMatrix(Camera3D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCameraMatrix, 0, 0, 1)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCameraMatrix)
{
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    Matrix originalResult = GetCameraMatrix(*php_raylib_camera3d_fetch_data(phpCamera));
    zend_object *result = php_raylib_matrix_new_ex(php_raylib_matrix_ce, NULL);
    php_raylib_matrix_object *phpResult = php_raylib_matrix_fetch_object(result);
    Matrix *matrixData = php_raylib_matrix_fetch_data(phpResult);
    // Dereference matrixData for assignment back to object
    *matrixData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get camera 2d transform matrix
// RLAPI Matrix GetCameraMatrix2D(Camera2D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCameraMatrix2D, 0, 0, 1)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCameraMatrix2D)
{
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera2d_object *phpCamera = Z_CAMERA2D_OBJ_P(camera);

    Matrix originalResult = GetCameraMatrix2D(*php_raylib_camera2d_fetch_data(phpCamera));
    zend_object *result = php_raylib_matrix_new_ex(php_raylib_matrix_ce, NULL);
    php_raylib_matrix_object *phpResult = php_raylib_matrix_fetch_object(result);
    Matrix *matrixData = php_raylib_matrix_fetch_data(phpResult);
    // Dereference matrixData for assignment back to object
    *matrixData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get the screen space position for a 3d world space position
// RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera3D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetWorldToScreen, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetWorldToScreen)
{
    zval *position;
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    Vector2 originalResult = GetWorldToScreen(*php_raylib_vector3_fetch_data(phpPosition), *php_raylib_camera3d_fetch_data(phpCamera));
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get the world space position for a 2d camera screen space position
// RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetScreenToWorld2D, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetScreenToWorld2D)
{
    zval *position;
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_camera2d_object *phpCamera = Z_CAMERA2D_OBJ_P(camera);

    Vector2 originalResult = GetScreenToWorld2D(*php_raylib_vector2_fetch_data(phpPosition), *php_raylib_camera2d_fetch_data(phpCamera));
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get size position for a 3d world space position
// RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera3D camera, int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetWorldToScreenEx, 0, 0, 4)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetWorldToScreenEx)
{
    zval *position;
    zval *camera;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    Vector2 originalResult = GetWorldToScreenEx(*php_raylib_vector3_fetch_data(phpPosition), *php_raylib_camera3d_fetch_data(phpCamera), (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1);
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get the screen space position for a 2d camera world space position
// RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetWorldToScreen2D, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, camera)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetWorldToScreen2D)
{
    zval *position;
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_camera2d_object *phpCamera = Z_CAMERA2D_OBJ_P(camera);

    Vector2 originalResult = GetWorldToScreen2D(*php_raylib_vector2_fetch_data(phpPosition), *php_raylib_camera2d_fetch_data(phpCamera));
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Set target FPS (maximum)
// RLAPI void SetTargetFPS(int fps);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetTargetFPS, 0, 0, 1)
    ZEND_ARG_INFO(0, fps)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetTargetFPS)
{
    zend_long fps;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(fps)
    ZEND_PARSE_PARAMETERS_END();


    SetTargetFPS((fps <= INT_MAX) ? (int) ((zend_long) fps) : -1);

}

// Get current FPS
// RLAPI int GetFPS();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetFPS, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetFPS)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetFPS());
}

// Get time in seconds for last frame drawn (delta time)
// RLAPI float GetFrameTime();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetFrameTime, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetFrameTime)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetFrameTime());
}

// Get elapsed time in seconds since InitWindow()
// RLAPI double GetTime();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTime, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTime)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetTime());
}

// Get a random value between min and max (both included)
// RLAPI int GetRandomValue(int min, int max);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRandomValue, 0, 0, 2)
    ZEND_ARG_INFO(0, min)
    ZEND_ARG_INFO(0, max)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRandomValue)
{
    zend_long min;
    zend_long max;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(min)
        Z_PARAM_LONG(max)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetRandomValue((min <= INT_MAX) ? (int) ((zend_long) min) : -1, (max <= INT_MAX) ? (int) ((zend_long) max) : -1));
}

// Set the seed for the random number generator
// RLAPI void SetRandomSeed(unsigned int seed);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetRandomSeed, 0, 0, 1)
    ZEND_ARG_INFO(0, seed)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetRandomSeed)
{
    zend_long seed;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(seed)
    ZEND_PARSE_PARAMETERS_END();


    SetRandomSeed((seed <= INT_MAX) ? (int) ((zend_long) seed) : -1);

}

// Takes a screenshot of current screen (filename extension defines format)
// RLAPI void TakeScreenshot(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TakeScreenshot, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TakeScreenshot)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    TakeScreenshot(fileName->val);

}

// Setup init configuration flags (view FLAGS)
// RLAPI void SetConfigFlags(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetConfigFlags, 0, 0, 1)
    ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetConfigFlags)
{
    zend_long flags;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flags)
    ZEND_PARSE_PARAMETERS_END();


    SetConfigFlags((flags <= INT_MAX) ? (int) ((zend_long) flags) : -1);

}

// Set the current threshold (minimum) log level
// RLAPI void SetTraceLogLevel(int logLevel);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetTraceLogLevel, 0, 0, 1)
    ZEND_ARG_INFO(0, logLevel)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetTraceLogLevel)
{
    zend_long logLevel;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(logLevel)
    ZEND_PARSE_PARAMETERS_END();


    SetTraceLogLevel((logLevel <= INT_MAX) ? (int) ((zend_long) logLevel) : -1);

}

// Open URL with default system browser (if available)
// RLAPI void OpenURL(const char * url);
ZEND_BEGIN_ARG_INFO_EX(arginfo_OpenURL, 0, 0, 1)
    ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()
PHP_FUNCTION(OpenURL)
{
    zend_string *url;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(url)
    ZEND_PARSE_PARAMETERS_END();


    OpenURL(url->val);

}

// Export data to code (.h), returns true on success
// RLAPI bool ExportDataAsCode(const unsigned char * data, unsigned int size, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportDataAsCode, 0, 0, 3)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportDataAsCode)
{
    zval *data;
    zend_long size;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ARRAY(data)
        Z_PARAM_LONG(size)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    zval *data_element;
    int data_index;
    HashTable *data_hash = Z_ARRVAL_P(data);
    SEPARATE_ARRAY(data);
    int data_count = zend_hash_num_elements(data_hash);
    unsigned char * data_array = safe_emalloc(sizeof(unsigned char *), data_count, 0);
    ZEND_HASH_FOREACH_VAL(data_hash, data_element) {
        ZVAL_DEREF(data_element);
        if (Z_TYPE_P(data_element) == IS_LONG) {
            data_array[data_index] = (const unsigned char) Z_LVAL_P(data_element);
        }

        data_index++;
    } ZEND_HASH_FOREACH_END();

    RETURN_BOOL(ExportDataAsCode(data_array, (size <= INT_MAX) ? (int) ((zend_long) size) : -1, fileName->val));
}

// Unload file text data allocated by LoadFileText()
// RLAPI void UnloadFileText(char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadFileText, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadFileText)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    UnloadFileText(text->val);

}

// Save text data to file (write), string must be '\0' terminated, returns true on success
// RLAPI bool SaveFileText(const char * fileName, char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SaveFileText, 0, 0, 2)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SaveFileText)
{
    zend_string *fileName;
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(fileName)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(SaveFileText(fileName->val, text->val));
}

// Check if file exists
// RLAPI bool FileExists(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_FileExists, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(FileExists)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(FileExists(fileName->val));
}

// Check if a directory path exists
// RLAPI bool DirectoryExists(const char * dirPath);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DirectoryExists, 0, 0, 1)
    ZEND_ARG_INFO(0, dirPath)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DirectoryExists)
{
    zend_string *dirPath;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(dirPath)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(DirectoryExists(dirPath->val));
}

// Check file extension (including point: .png, .wav)
// RLAPI bool IsFileExtension(const char * fileName, const char * ext);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsFileExtension, 0, 0, 2)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, ext)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsFileExtension)
{
    zend_string *fileName;
    zend_string *ext;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(fileName)
        Z_PARAM_STR(ext)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsFileExtension(fileName->val, ext->val));
}

// Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
// RLAPI int GetFileLength(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetFileLength, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetFileLength)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetFileLength(fileName->val));
}

// Change working directory, return true on success
// RLAPI bool ChangeDirectory(const char * dir);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ChangeDirectory, 0, 0, 1)
    ZEND_ARG_INFO(0, dir)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ChangeDirectory)
{
    zend_string *dir;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(dir)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(ChangeDirectory(dir->val));
}

// Check if a given path is a file or a directory
// RLAPI bool IsPathFile(const char * path);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsPathFile, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsPathFile)
{
    zend_string *path;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(path)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsPathFile(path->val));
}

// Load directory filepaths
// RLAPI FilePathList LoadDirectoryFiles(const char * dirPath);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadDirectoryFiles, 0, 0, 1)
    ZEND_ARG_INFO(0, dirPath)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadDirectoryFiles)
{
    zend_string *dirPath;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(dirPath)
    ZEND_PARSE_PARAMETERS_END();


    FilePathList originalResult = LoadDirectoryFiles(dirPath->val);
    zend_object *result = php_raylib_filepathlist_new_ex(php_raylib_filepathlist_ce, NULL);
    php_raylib_filepathlist_object *phpResult = php_raylib_filepathlist_fetch_object(result);
    FilePathList *filepathlistData = php_raylib_filepathlist_fetch_data(phpResult);
    // Dereference filepathlistData for assignment back to object
    *filepathlistData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load directory filepaths with extension filtering and recursive directory scan
// RLAPI FilePathList LoadDirectoryFilesEx(const char * basePath, const char * filter, bool scanSubdirs);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadDirectoryFilesEx, 0, 0, 3)
    ZEND_ARG_INFO(0, basePath)
    ZEND_ARG_INFO(0, filter)
    ZEND_ARG_INFO(0, scanSubdirs)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadDirectoryFilesEx)
{
    zend_string *basePath;
    zend_string *filter;
    bool scanSubdirs;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(basePath)
        Z_PARAM_STR(filter)
        Z_PARAM_BOOL(scanSubdirs)
    ZEND_PARSE_PARAMETERS_END();


    FilePathList originalResult = LoadDirectoryFilesEx(basePath->val, filter->val, scanSubdirs);
    zend_object *result = php_raylib_filepathlist_new_ex(php_raylib_filepathlist_ce, NULL);
    php_raylib_filepathlist_object *phpResult = php_raylib_filepathlist_fetch_object(result);
    FilePathList *filepathlistData = php_raylib_filepathlist_fetch_data(phpResult);
    // Dereference filepathlistData for assignment back to object
    *filepathlistData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Unload filepaths
// RLAPI void UnloadDirectoryFiles(FilePathList files);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadDirectoryFiles, 0, 0, 1)
    ZEND_ARG_INFO(0, files)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadDirectoryFiles)
{
    zval *files;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(files)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_filepathlist_object *phpFiles = Z_FILEPATHLIST_OBJ_P(files);

    UnloadDirectoryFiles(*php_raylib_filepathlist_fetch_data(phpFiles));

}

// Check if a file has been dropped into window
// RLAPI bool IsFileDropped();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsFileDropped, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsFileDropped)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsFileDropped());
}

// Load dropped filepaths
// RLAPI FilePathList LoadDroppedFiles();
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadDroppedFiles, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadDroppedFiles)
{

    ZEND_PARSE_PARAMETERS_NONE();

    FilePathList originalResult = LoadDroppedFiles();
    zend_object *result = php_raylib_filepathlist_new_ex(php_raylib_filepathlist_ce, NULL);
    php_raylib_filepathlist_object *phpResult = php_raylib_filepathlist_fetch_object(result);
    FilePathList *filepathlistData = php_raylib_filepathlist_fetch_data(phpResult);
    // Dereference filepathlistData for assignment back to object
    *filepathlistData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Unload dropped filepaths
// RLAPI void UnloadDroppedFiles(FilePathList files);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadDroppedFiles, 0, 0, 1)
    ZEND_ARG_INFO(0, files)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadDroppedFiles)
{
    zval *files;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(files)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_filepathlist_object *phpFiles = Z_FILEPATHLIST_OBJ_P(files);

    UnloadDroppedFiles(*php_raylib_filepathlist_fetch_data(phpFiles));

}

// Get file modification time (last write time)
// RLAPI long GetFileModTime(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetFileModTime, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetFileModTime)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetFileModTime(fileName->val));
}

// Check if a key has been pressed once
// RLAPI bool IsKeyPressed(int key);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsKeyPressed, 0, 0, 1)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsKeyPressed)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsKeyPressed((key <= INT_MAX) ? (int) ((zend_long) key) : -1));
}

// Check if a key is being pressed
// RLAPI bool IsKeyDown(int key);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsKeyDown, 0, 0, 1)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsKeyDown)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsKeyDown((key <= INT_MAX) ? (int) ((zend_long) key) : -1));
}

// Check if a key has been released once
// RLAPI bool IsKeyReleased(int key);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsKeyReleased, 0, 0, 1)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsKeyReleased)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsKeyReleased((key <= INT_MAX) ? (int) ((zend_long) key) : -1));
}

// Check if a key is NOT being pressed
// RLAPI bool IsKeyUp(int key);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsKeyUp, 0, 0, 1)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsKeyUp)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsKeyUp((key <= INT_MAX) ? (int) ((zend_long) key) : -1));
}

// Set a custom key to exit program (default is ESC)
// RLAPI void SetExitKey(int key);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetExitKey, 0, 0, 1)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetExitKey)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();


    SetExitKey((key <= INT_MAX) ? (int) ((zend_long) key) : -1);

}

// Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
// RLAPI int GetKeyPressed();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetKeyPressed, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetKeyPressed)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetKeyPressed());
}

// Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
// RLAPI int GetCharPressed();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCharPressed, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCharPressed)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetCharPressed());
}

// Check if a gamepad is available
// RLAPI bool IsGamepadAvailable(int gamepad);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGamepadAvailable, 0, 0, 1)
    ZEND_ARG_INFO(0, gamepad)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGamepadAvailable)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGamepadAvailable((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1));
}

// Check if a gamepad button has been pressed once
// RLAPI bool IsGamepadButtonPressed(int gamepad, int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGamepadButtonPressed, 0, 0, 2)
    ZEND_ARG_INFO(0, gamepad)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGamepadButtonPressed)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGamepadButtonPressed((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1, (button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a gamepad button is being pressed
// RLAPI bool IsGamepadButtonDown(int gamepad, int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGamepadButtonDown, 0, 0, 2)
    ZEND_ARG_INFO(0, gamepad)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGamepadButtonDown)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGamepadButtonDown((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1, (button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a gamepad button has been released once
// RLAPI bool IsGamepadButtonReleased(int gamepad, int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGamepadButtonReleased, 0, 0, 2)
    ZEND_ARG_INFO(0, gamepad)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGamepadButtonReleased)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGamepadButtonReleased((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1, (button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a gamepad button is NOT being pressed
// RLAPI bool IsGamepadButtonUp(int gamepad, int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGamepadButtonUp, 0, 0, 2)
    ZEND_ARG_INFO(0, gamepad)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGamepadButtonUp)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGamepadButtonUp((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1, (button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Get the last gamepad button pressed
// RLAPI int GetGamepadButtonPressed();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGamepadButtonPressed, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGamepadButtonPressed)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetGamepadButtonPressed());
}

// Get gamepad axis count for a gamepad
// RLAPI int GetGamepadAxisCount(int gamepad);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGamepadAxisCount, 0, 0, 1)
    ZEND_ARG_INFO(0, gamepad)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGamepadAxisCount)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetGamepadAxisCount((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1));
}

// Get axis movement value for a gamepad axis
// RLAPI float GetGamepadAxisMovement(int gamepad, int axis);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGamepadAxisMovement, 0, 0, 2)
    ZEND_ARG_INFO(0, gamepad)
    ZEND_ARG_INFO(0, axis)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGamepadAxisMovement)
{
    zend_long gamepad;
    zend_long axis;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(gamepad)
        Z_PARAM_LONG(axis)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_DOUBLE((double) GetGamepadAxisMovement((gamepad <= INT_MAX) ? (int) ((zend_long) gamepad) : -1, (axis <= INT_MAX) ? (int) ((zend_long) axis) : -1));
}

// Set internal gamepad mappings (SDL_GameControllerDB)
// RLAPI int SetGamepadMappings(const char * mappings);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetGamepadMappings, 0, 0, 1)
    ZEND_ARG_INFO(0, mappings)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetGamepadMappings)
{
    zend_string *mappings;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(mappings)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(SetGamepadMappings(mappings->val));
}

// Check if a mouse button has been pressed once
// RLAPI bool IsMouseButtonPressed(int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMouseButtonPressed, 0, 0, 1)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMouseButtonPressed)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsMouseButtonPressed((button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a mouse button is being pressed
// RLAPI bool IsMouseButtonDown(int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMouseButtonDown, 0, 0, 1)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMouseButtonDown)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsMouseButtonDown((button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a mouse button has been released once
// RLAPI bool IsMouseButtonReleased(int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMouseButtonReleased, 0, 0, 1)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMouseButtonReleased)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsMouseButtonReleased((button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Check if a mouse button is NOT being pressed
// RLAPI bool IsMouseButtonUp(int button);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMouseButtonUp, 0, 0, 1)
    ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMouseButtonUp)
{
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsMouseButtonUp((button <= INT_MAX) ? (int) ((zend_long) button) : -1));
}

// Get mouse position X
// RLAPI int GetMouseX();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseX)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetMouseX());
}

// Get mouse position Y
// RLAPI int GetMouseY();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseY)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetMouseY());
}

// Get mouse position XY
// RLAPI Vector2 GetMousePosition();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMousePosition, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMousePosition)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetMousePosition();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get mouse delta between frames
// RLAPI Vector2 GetMouseDelta();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseDelta, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseDelta)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetMouseDelta();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Set mouse position XY
// RLAPI void SetMousePosition(int x, int y);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMousePosition, 0, 0, 2)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMousePosition)
{
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
    ZEND_PARSE_PARAMETERS_END();


    SetMousePosition((x <= INT_MAX) ? (int) ((zend_long) x) : -1, (y <= INT_MAX) ? (int) ((zend_long) y) : -1);

}

// Set mouse offset
// RLAPI void SetMouseOffset(int offsetX, int offsetY);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMouseOffset, 0, 0, 2)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, offsetY)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMouseOffset)
{
    zend_long offsetX;
    zend_long offsetY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(offsetY)
    ZEND_PARSE_PARAMETERS_END();


    SetMouseOffset((offsetX <= INT_MAX) ? (int) ((zend_long) offsetX) : -1, (offsetY <= INT_MAX) ? (int) ((zend_long) offsetY) : -1);

}

// Set mouse scaling
// RLAPI void SetMouseScale(float scaleX, float scaleY);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMouseScale, 0, 0, 2)
    ZEND_ARG_INFO(0, scaleX)
    ZEND_ARG_INFO(0, scaleY)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMouseScale)
{
    double scaleX;
    double scaleY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(scaleX)
        Z_PARAM_DOUBLE(scaleY)
    ZEND_PARSE_PARAMETERS_END();


    SetMouseScale((float) scaleX, (float) scaleY);

}

// Get mouse wheel movement for X or Y, whichever is larger
// RLAPI float GetMouseWheelMove();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseWheelMove, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseWheelMove)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetMouseWheelMove());
}

// Get mouse wheel movement for both X and Y
// RLAPI Vector2 GetMouseWheelMoveV();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMouseWheelMoveV, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMouseWheelMoveV)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetMouseWheelMoveV();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Set mouse cursor
// RLAPI void SetMouseCursor(int cursor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMouseCursor, 0, 0, 1)
    ZEND_ARG_INFO(0, cursor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMouseCursor)
{
    zend_long cursor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(cursor)
    ZEND_PARSE_PARAMETERS_END();


    SetMouseCursor((cursor <= INT_MAX) ? (int) ((zend_long) cursor) : -1);

}

// Get touch position X for touch point 0 (relative to screen size)
// RLAPI int GetTouchX();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTouchX, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTouchX)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetTouchX());
}

// Get touch position Y for touch point 0 (relative to screen size)
// RLAPI int GetTouchY();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTouchY, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTouchY)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetTouchY());
}

// Get touch position XY for a touch point index (relative to screen size)
// RLAPI Vector2 GetTouchPosition(int index);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTouchPosition, 0, 0, 1)
    ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTouchPosition)
{
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();


    Vector2 originalResult = GetTouchPosition((index <= INT_MAX) ? (int) ((zend_long) index) : -1);
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get touch point identifier for given index
// RLAPI int GetTouchPointId(int index);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTouchPointId, 0, 0, 1)
    ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTouchPointId)
{
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetTouchPointId((index <= INT_MAX) ? (int) ((zend_long) index) : -1));
}

// Get number of touch points
// RLAPI int GetTouchPointCount();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetTouchPointCount, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetTouchPointCount)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetTouchPointCount());
}

// Enable a set of gestures using flags
// RLAPI void SetGesturesEnabled(unsigned int flags);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetGesturesEnabled, 0, 0, 1)
    ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetGesturesEnabled)
{
    zend_long flags;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flags)
    ZEND_PARSE_PARAMETERS_END();


    SetGesturesEnabled((flags <= INT_MAX) ? (int) ((zend_long) flags) : -1);

}

// Check if a gesture have been detected
// RLAPI bool IsGestureDetected(int gesture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsGestureDetected, 0, 0, 1)
    ZEND_ARG_INFO(0, gesture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsGestureDetected)
{
    zend_long gesture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(gesture)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(IsGestureDetected((gesture <= INT_MAX) ? (int) ((zend_long) gesture) : -1));
}

// Get latest detected gesture
// RLAPI int GetGestureDetected();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGestureDetected, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGestureDetected)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(GetGestureDetected());
}

// Get gesture hold time in milliseconds
// RLAPI float GetGestureHoldDuration();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGestureHoldDuration, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGestureHoldDuration)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetGestureHoldDuration());
}

// Get gesture drag vector
// RLAPI Vector2 GetGestureDragVector();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGestureDragVector, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGestureDragVector)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetGestureDragVector();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get gesture drag angle
// RLAPI float GetGestureDragAngle();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGestureDragAngle, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGestureDragAngle)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetGestureDragAngle());
}

// Get gesture pinch delta
// RLAPI Vector2 GetGesturePinchVector();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGesturePinchVector, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGesturePinchVector)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Vector2 originalResult = GetGesturePinchVector();
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get gesture pinch angle
// RLAPI float GetGesturePinchAngle();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGesturePinchAngle, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGesturePinchAngle)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_DOUBLE((double) GetGesturePinchAngle());
}

// Update camera position for selected mode
// RLAPI void UpdateCamera(Camera3D* camera, int mode);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UpdateCamera, 0, 0, 2)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UpdateCamera)
{
    zval *camera;
    zend_long mode;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_LONG(mode)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);

    UpdateCamera(php_raylib_camera3d_fetch_data(phpCamera), (mode <= INT_MAX) ? (int) ((zend_long) mode) : -1);

}

// Update camera movement/rotation
// RLAPI void UpdateCameraPro(Camera3D* camera, Vector3 movement, Vector3 rotation, float zoom);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UpdateCameraPro, 0, 0, 4)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, movement)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, zoom)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UpdateCameraPro)
{
    zval *camera;
    zval *movement;
    zval *rotation;
    double zoom;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_ZVAL(movement)
        Z_PARAM_ZVAL(rotation)
        Z_PARAM_DOUBLE(zoom)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);
    php_raylib_vector3_object *phpMovement = Z_VECTOR3_OBJ_P(movement);
    php_raylib_vector3_object *phpRotation = Z_VECTOR3_OBJ_P(rotation);

    UpdateCameraPro(php_raylib_camera3d_fetch_data(phpCamera), *php_raylib_vector3_fetch_data(phpMovement), *php_raylib_vector3_fetch_data(phpRotation), (float) zoom);

}

// Set texture and rectangle to be used on shapes drawing
// RLAPI void SetShapesTexture(Texture texture, Rectangle source);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetShapesTexture, 0, 0, 2)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetShapesTexture)
{
    zval *texture;
    zval *source;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(source)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(source);

    SetShapesTexture(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_rectangle_fetch_data(phpSource));

}

// Draw a pixel
// RLAPI void DrawPixel(int posX, int posY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPixel, 0, 0, 3)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPixel)
{
    zend_long posX;
    zend_long posY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPixel((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a pixel (Vector version)
// RLAPI void DrawPixelV(Vector2 position, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPixelV, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPixelV)
{
    zval *position;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPixelV(*php_raylib_vector2_fetch_data(phpPosition), *php_raylib_color_fetch_data(phpColor));

}

// Draw a line
// RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLine, 0, 0, 5)
    ZEND_ARG_INFO(0, startPosX)
    ZEND_ARG_INFO(0, startPosY)
    ZEND_ARG_INFO(0, endPosX)
    ZEND_ARG_INFO(0, endPosY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLine)
{
    zend_long startPosX;
    zend_long startPosY;
    zend_long endPosX;
    zend_long endPosY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(startPosX)
        Z_PARAM_LONG(startPosY)
        Z_PARAM_LONG(endPosX)
        Z_PARAM_LONG(endPosY)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLine((startPosX <= INT_MAX) ? (int) ((zend_long) startPosX) : -1, (startPosY <= INT_MAX) ? (int) ((zend_long) startPosY) : -1, (endPosX <= INT_MAX) ? (int) ((zend_long) endPosX) : -1, (endPosY <= INT_MAX) ? (int) ((zend_long) endPosY) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a line (Vector version)
// RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineV, 0, 0, 3)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineV)
{
    zval *startPos;
    zval *endPos;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineV(*php_raylib_vector2_fetch_data(phpStartPos), *php_raylib_vector2_fetch_data(phpEndPos), *php_raylib_color_fetch_data(phpColor));

}

// Draw a line defining thickness
// RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineEx, 0, 0, 4)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineEx)
{
    zval *startPos;
    zval *endPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(thick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineEx(*php_raylib_vector2_fetch_data(phpStartPos), *php_raylib_vector2_fetch_data(phpEndPos), (float) thick, *php_raylib_color_fetch_data(phpColor));

}

// Draw a line using cubic-bezier curves in-out
// RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineBezier, 0, 0, 4)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineBezier)
{
    zval *startPos;
    zval *endPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(thick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineBezier(*php_raylib_vector2_fetch_data(phpStartPos), *php_raylib_vector2_fetch_data(phpEndPos), (float) thick, *php_raylib_color_fetch_data(phpColor));

}

// Draw line using quadratic bezier curves with a control point
// RLAPI void DrawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineBezierQuad, 0, 0, 5)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, controlPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineBezierQuad)
{
    zval *startPos;
    zval *endPos;
    zval *controlPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_ZVAL(controlPos)
        Z_PARAM_DOUBLE(thick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_vector2_object *phpControlPos = Z_VECTOR2_OBJ_P(controlPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineBezierQuad(*php_raylib_vector2_fetch_data(phpStartPos), *php_raylib_vector2_fetch_data(phpEndPos), *php_raylib_vector2_fetch_data(phpControlPos), (float) thick, *php_raylib_color_fetch_data(phpColor));

}

// Draw line using cubic bezier curves with 2 control points
// RLAPI void DrawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineBezierCubic, 0, 0, 6)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, startControlPos)
    ZEND_ARG_INFO(0, endControlPos)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineBezierCubic)
{
    zval *startPos;
    zval *endPos;
    zval *startControlPos;
    zval *endControlPos;
    double thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_ZVAL(startControlPos)
        Z_PARAM_ZVAL(endControlPos)
        Z_PARAM_DOUBLE(thick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos = Z_VECTOR2_OBJ_P(startPos);
    php_raylib_vector2_object *phpEndPos = Z_VECTOR2_OBJ_P(endPos);
    php_raylib_vector2_object *phpStartControlPos = Z_VECTOR2_OBJ_P(startControlPos);
    php_raylib_vector2_object *phpEndControlPos = Z_VECTOR2_OBJ_P(endControlPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineBezierCubic(*php_raylib_vector2_fetch_data(phpStartPos), *php_raylib_vector2_fetch_data(phpEndPos), *php_raylib_vector2_fetch_data(phpStartControlPos), *php_raylib_vector2_fetch_data(phpEndControlPos), (float) thick, *php_raylib_color_fetch_data(phpColor));

}

// Draw lines sequence
// RLAPI void DrawLineStrip(Vector2* points, int pointCount, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLineStrip, 0, 0, 3)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, pointCount)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLineStrip)
{
    zval *points;
    zend_long pointCount;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ARRAY(points)
        Z_PARAM_LONG(pointCount)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    zval *points_element;
    int points_index;
    HashTable *points_hash = Z_ARRVAL_P(points);
    SEPARATE_ARRAY(points);
    int points_count = zend_hash_num_elements(points_hash);
    Vector2* points_array = safe_emalloc(sizeof(Vector2*), points_count, 0);
    ZEND_HASH_FOREACH_VAL(points_hash, points_element) {
        ZVAL_DEREF(points_element);
        if ((Z_TYPE_P(points_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(points_element), php_raylib_vector2_ce))) {
            php_raylib_vector2_object *vector2_obj =  Z_VECTOR2_OBJ_P(points_element);
            points_array[points_index] = *php_raylib_vector2_fetch_data(vector2_obj);
        }

        points_index++;
    } ZEND_HASH_FOREACH_END();
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLineStrip(points_array, (pointCount <= INT_MAX) ? (int) ((zend_long) pointCount) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled circle
// RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircle, 0, 0, 4)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircle)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircle((centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (float) radius, *php_raylib_color_fetch_data(phpColor));

}

// Draw a piece of a circle
// RLAPI void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircleSector, 0, 0, 6)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircleSector)
{
    zval *center;
    double radius;
    double startAngle;
    double endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(startAngle)
        Z_PARAM_DOUBLE(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleSector(*php_raylib_vector2_fetch_data(phpCenter), (float) radius, (float) startAngle, (float) endAngle, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw circle sector outline
// RLAPI void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircleSectorLines, 0, 0, 6)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircleSectorLines)
{
    zval *center;
    double radius;
    double startAngle;
    double endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(startAngle)
        Z_PARAM_DOUBLE(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleSectorLines(*php_raylib_vector2_fetch_data(phpCenter), (float) radius, (float) startAngle, (float) endAngle, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a gradient-filled circle
// RLAPI void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircleGradient, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircleGradient)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(color1)
        Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawCircleGradient((centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (float) radius, *php_raylib_color_fetch_data(phpColor1), *php_raylib_color_fetch_data(phpColor2));

}

// Draw a color-filled circle (Vector version)
// RLAPI void DrawCircleV(Vector2 center, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircleV, 0, 0, 3)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircleV)
{
    zval *center;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleV(*php_raylib_vector2_fetch_data(phpCenter), (float) radius, *php_raylib_color_fetch_data(phpColor));

}

// Draw circle outline
// RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircleLines, 0, 0, 4)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircleLines)
{
    zend_long centerX;
    zend_long centerY;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircleLines((centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (float) radius, *php_raylib_color_fetch_data(phpColor));

}

// Draw ellipse
// RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawEllipse, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radiusH)
    ZEND_ARG_INFO(0, radiusV)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawEllipse)
{
    zend_long centerX;
    zend_long centerY;
    double radiusH;
    double radiusV;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_DOUBLE(radiusH)
        Z_PARAM_DOUBLE(radiusV)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawEllipse((centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (float) radiusH, (float) radiusV, *php_raylib_color_fetch_data(phpColor));

}

// Draw ellipse outline
// RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawEllipseLines, 0, 0, 5)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radiusH)
    ZEND_ARG_INFO(0, radiusV)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawEllipseLines)
{
    zend_long centerX;
    zend_long centerY;
    double radiusH;
    double radiusV;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_DOUBLE(radiusH)
        Z_PARAM_DOUBLE(radiusV)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawEllipseLines((centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (float) radiusH, (float) radiusV, *php_raylib_color_fetch_data(phpColor));

}

// Draw ring
// RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRing, 0, 0, 7)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, innerRadius)
    ZEND_ARG_INFO(0, outerRadius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRing)
{
    zval *center;
    double innerRadius;
    double outerRadius;
    double startAngle;
    double endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(innerRadius)
        Z_PARAM_DOUBLE(outerRadius)
        Z_PARAM_DOUBLE(startAngle)
        Z_PARAM_DOUBLE(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRing(*php_raylib_vector2_fetch_data(phpCenter), (float) innerRadius, (float) outerRadius, (float) startAngle, (float) endAngle, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw ring outline
// RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRingLines, 0, 0, 7)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, innerRadius)
    ZEND_ARG_INFO(0, outerRadius)
    ZEND_ARG_INFO(0, startAngle)
    ZEND_ARG_INFO(0, endAngle)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRingLines)
{
    zval *center;
    double innerRadius;
    double outerRadius;
    double startAngle;
    double endAngle;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(innerRadius)
        Z_PARAM_DOUBLE(outerRadius)
        Z_PARAM_DOUBLE(startAngle)
        Z_PARAM_DOUBLE(endAngle)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRingLines(*php_raylib_vector2_fetch_data(phpCenter), (float) innerRadius, (float) outerRadius, (float) startAngle, (float) endAngle, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled rectangle
// RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangle, 0, 0, 5)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangle)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangle((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled rectangle (Vector version)
// RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleV, 0, 0, 3)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleV)
{
    zval *position;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleV(*php_raylib_vector2_fetch_data(phpPosition), *php_raylib_vector2_fetch_data(phpSize), *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled rectangle
// RLAPI void DrawRectangleRec(Rectangle rec, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleRec, 0, 0, 2)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleRec)
{
    zval *rec;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRec(*php_raylib_rectangle_fetch_data(phpRec), *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled rectangle with pro parameters
// RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectanglePro, 0, 0, 4)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectanglePro)
{
    zval *rec;
    zval *origin;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectanglePro(*php_raylib_rectangle_fetch_data(phpRec), *php_raylib_vector2_fetch_data(phpOrigin), (float) rotation, *php_raylib_color_fetch_data(phpColor));

}

// Draw a vertical-gradient-filled rectangle
// RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleGradientV, 0, 0, 6)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleGradientV)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color1)
        Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawRectangleGradientV((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor1), *php_raylib_color_fetch_data(phpColor2));

}

// Draw a horizontal-gradient-filled rectangle
// RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleGradientH, 0, 0, 6)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleGradientH)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color1;
    zval *color2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color1)
        Z_PARAM_ZVAL(color2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor1 = Z_COLOR_OBJ_P(color1);
    php_raylib_color_object *phpColor2 = Z_COLOR_OBJ_P(color2);

    DrawRectangleGradientH((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor1), *php_raylib_color_fetch_data(phpColor2));

}

// Draw a gradient-filled rectangle with custom vertex colors
// RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleGradientEx, 0, 0, 5)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, col1)
    ZEND_ARG_INFO(0, col2)
    ZEND_ARG_INFO(0, col3)
    ZEND_ARG_INFO(0, col4)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleGradientEx)
{
    zval *rec;
    zval *col1;
    zval *col2;
    zval *col3;
    zval *col4;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_ZVAL(col1)
        Z_PARAM_ZVAL(col2)
        Z_PARAM_ZVAL(col3)
        Z_PARAM_ZVAL(col4)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpCol1 = Z_COLOR_OBJ_P(col1);
    php_raylib_color_object *phpCol2 = Z_COLOR_OBJ_P(col2);
    php_raylib_color_object *phpCol3 = Z_COLOR_OBJ_P(col3);
    php_raylib_color_object *phpCol4 = Z_COLOR_OBJ_P(col4);

    DrawRectangleGradientEx(*php_raylib_rectangle_fetch_data(phpRec), *php_raylib_color_fetch_data(phpCol1), *php_raylib_color_fetch_data(phpCol2), *php_raylib_color_fetch_data(phpCol3), *php_raylib_color_fetch_data(phpCol4));

}

// Draw rectangle outline
// RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleLines, 0, 0, 5)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleLines)
{
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleLines((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle outline with extended parameters
// RLAPI void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleLinesEx, 0, 0, 3)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, lineThick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleLinesEx)
{
    zval *rec;
    double lineThick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_DOUBLE(lineThick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleLinesEx(*php_raylib_rectangle_fetch_data(phpRec), (float) lineThick, *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle with rounded edges
// RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleRounded, 0, 0, 4)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, roundness)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleRounded)
{
    zval *rec;
    double roundness;
    zend_long segments;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_DOUBLE(roundness)
        Z_PARAM_LONG(segments)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRounded(*php_raylib_rectangle_fetch_data(phpRec), (float) roundness, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle with rounded edges outline
// RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRectangleRoundedLines, 0, 0, 5)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, roundness)
    ZEND_ARG_INFO(0, segments)
    ZEND_ARG_INFO(0, lineThick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRectangleRoundedLines)
{
    zval *rec;
    double roundness;
    zend_long segments;
    double lineThick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_DOUBLE(roundness)
        Z_PARAM_LONG(segments)
        Z_PARAM_DOUBLE(lineThick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRectangleRoundedLines(*php_raylib_rectangle_fetch_data(phpRec), (float) roundness, (segments <= INT_MAX) ? (int) ((zend_long) segments) : -1, (float) lineThick, *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
// RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangle, 0, 0, 4)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
    ZEND_ARG_INFO(0, v3)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangle)
{
    zval *v1;
    zval *v2;
    zval *v3;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(v1)
        Z_PARAM_ZVAL(v2)
        Z_PARAM_ZVAL(v3)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpV1 = Z_VECTOR2_OBJ_P(v1);
    php_raylib_vector2_object *phpV2 = Z_VECTOR2_OBJ_P(v2);
    php_raylib_vector2_object *phpV3 = Z_VECTOR2_OBJ_P(v3);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangle(*php_raylib_vector2_fetch_data(phpV1), *php_raylib_vector2_fetch_data(phpV2), *php_raylib_vector2_fetch_data(phpV3), *php_raylib_color_fetch_data(phpColor));

}

// Draw triangle outline (vertex in counter-clockwise order!)
// RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangleLines, 0, 0, 4)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
    ZEND_ARG_INFO(0, v3)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangleLines)
{
    zval *v1;
    zval *v2;
    zval *v3;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(v1)
        Z_PARAM_ZVAL(v2)
        Z_PARAM_ZVAL(v3)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpV1 = Z_VECTOR2_OBJ_P(v1);
    php_raylib_vector2_object *phpV2 = Z_VECTOR2_OBJ_P(v2);
    php_raylib_vector2_object *phpV3 = Z_VECTOR2_OBJ_P(v3);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleLines(*php_raylib_vector2_fetch_data(phpV1), *php_raylib_vector2_fetch_data(phpV2), *php_raylib_vector2_fetch_data(phpV3), *php_raylib_color_fetch_data(phpColor));

}

// Draw a triangle fan defined by points (first vertex is the center)
// RLAPI void DrawTriangleFan(Vector2* points, int pointCount, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangleFan, 0, 0, 3)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, pointCount)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangleFan)
{
    zval *points;
    zend_long pointCount;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ARRAY(points)
        Z_PARAM_LONG(pointCount)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    zval *points_element;
    int points_index;
    HashTable *points_hash = Z_ARRVAL_P(points);
    SEPARATE_ARRAY(points);
    int points_count = zend_hash_num_elements(points_hash);
    Vector2* points_array = safe_emalloc(sizeof(Vector2*), points_count, 0);
    ZEND_HASH_FOREACH_VAL(points_hash, points_element) {
        ZVAL_DEREF(points_element);
        if ((Z_TYPE_P(points_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(points_element), php_raylib_vector2_ce))) {
            php_raylib_vector2_object *vector2_obj =  Z_VECTOR2_OBJ_P(points_element);
            points_array[points_index] = *php_raylib_vector2_fetch_data(vector2_obj);
        }

        points_index++;
    } ZEND_HASH_FOREACH_END();
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleFan(points_array, (pointCount <= INT_MAX) ? (int) ((zend_long) pointCount) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a triangle strip defined by points
// RLAPI void DrawTriangleStrip(Vector2* points, int pointCount, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangleStrip, 0, 0, 3)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, pointCount)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangleStrip)
{
    zval *points;
    zend_long pointCount;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ARRAY(points)
        Z_PARAM_LONG(pointCount)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    zval *points_element;
    int points_index;
    HashTable *points_hash = Z_ARRVAL_P(points);
    SEPARATE_ARRAY(points);
    int points_count = zend_hash_num_elements(points_hash);
    Vector2* points_array = safe_emalloc(sizeof(Vector2*), points_count, 0);
    ZEND_HASH_FOREACH_VAL(points_hash, points_element) {
        ZVAL_DEREF(points_element);
        if ((Z_TYPE_P(points_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(points_element), php_raylib_vector2_ce))) {
            php_raylib_vector2_object *vector2_obj =  Z_VECTOR2_OBJ_P(points_element);
            points_array[points_index] = *php_raylib_vector2_fetch_data(vector2_obj);
        }

        points_index++;
    } ZEND_HASH_FOREACH_END();
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleStrip(points_array, (pointCount <= INT_MAX) ? (int) ((zend_long) pointCount) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a regular polygon (Vector version)
// RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPoly, 0, 0, 5)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPoly)
{
    zval *center;
    zend_long sides;
    double radius;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPoly(*php_raylib_vector2_fetch_data(phpCenter), (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, (float) radius, (float) rotation, *php_raylib_color_fetch_data(phpColor));

}

// Draw a polygon outline of n sides
// RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPolyLines, 0, 0, 5)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPolyLines)
{
    zval *center;
    zend_long sides;
    double radius;
    double rotation;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPolyLines(*php_raylib_vector2_fetch_data(phpCenter), (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, (float) radius, (float) rotation, *php_raylib_color_fetch_data(phpColor));

}

// Draw a polygon outline of n sides with extended parameters
// RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPolyLinesEx, 0, 0, 6)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, lineThick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPolyLinesEx)
{
    zval *center;
    zend_long sides;
    double radius;
    double rotation;
    double lineThick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_DOUBLE(lineThick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPolyLinesEx(*php_raylib_vector2_fetch_data(phpCenter), (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, (float) radius, (float) rotation, (float) lineThick, *php_raylib_color_fetch_data(phpColor));

}

// Check collision between two rectangles
// RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionRecs, 0, 0, 2)
    ZEND_ARG_INFO(0, rec1)
    ZEND_ARG_INFO(0, rec2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionRecs)
{
    zval *rec1;
    zval *rec2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec1)
        Z_PARAM_ZVAL(rec2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec1 = Z_RECTANGLE_OBJ_P(rec1);
    php_raylib_rectangle_object *phpRec2 = Z_RECTANGLE_OBJ_P(rec2);

    RETURN_BOOL(CheckCollisionRecs(*php_raylib_rectangle_fetch_data(phpRec1), *php_raylib_rectangle_fetch_data(phpRec2)));
}

// Check collision between two circles
// RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionCircles, 0, 0, 4)
    ZEND_ARG_INFO(0, center1)
    ZEND_ARG_INFO(0, radius1)
    ZEND_ARG_INFO(0, center2)
    ZEND_ARG_INFO(0, radius2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionCircles)
{
    zval *center1;
    double radius1;
    zval *center2;
    double radius2;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(center1)
        Z_PARAM_DOUBLE(radius1)
        Z_PARAM_ZVAL(center2)
        Z_PARAM_DOUBLE(radius2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter1 = Z_VECTOR2_OBJ_P(center1);
    php_raylib_vector2_object *phpCenter2 = Z_VECTOR2_OBJ_P(center2);

    RETURN_BOOL(CheckCollisionCircles(*php_raylib_vector2_fetch_data(phpCenter1), (float) radius1, *php_raylib_vector2_fetch_data(phpCenter2), (float) radius2));
}

// Check collision between circle and rectangle
// RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionCircleRec, 0, 0, 3)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionCircleRec)
{
    zval *center;
    double radius;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);

    RETURN_BOOL(CheckCollisionCircleRec(*php_raylib_vector2_fetch_data(phpCenter), (float) radius, *php_raylib_rectangle_fetch_data(phpRec)));
}

// Check if point is inside rectangle
// RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionPointRec, 0, 0, 2)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionPointRec)
{
    zval *point;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);

    RETURN_BOOL(CheckCollisionPointRec(*php_raylib_vector2_fetch_data(phpPoint), *php_raylib_rectangle_fetch_data(phpRec)));
}

// Check if point is inside circle
// RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionPointCircle, 0, 0, 3)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionPointCircle)
{
    zval *point;
    zval *center;
    double radius;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);

    RETURN_BOOL(CheckCollisionPointCircle(*php_raylib_vector2_fetch_data(phpPoint), *php_raylib_vector2_fetch_data(phpCenter), (float) radius));
}

// Check if point is inside a triangle
// RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionPointTriangle, 0, 0, 4)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, p1)
    ZEND_ARG_INFO(0, p2)
    ZEND_ARG_INFO(0, p3)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionPointTriangle)
{
    zval *point;
    zval *p1;
    zval *p2;
    zval *p3;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(p1)
        Z_PARAM_ZVAL(p2)
        Z_PARAM_ZVAL(p3)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_vector2_object *phpP1 = Z_VECTOR2_OBJ_P(p1);
    php_raylib_vector2_object *phpP2 = Z_VECTOR2_OBJ_P(p2);
    php_raylib_vector2_object *phpP3 = Z_VECTOR2_OBJ_P(p3);

    RETURN_BOOL(CheckCollisionPointTriangle(*php_raylib_vector2_fetch_data(phpPoint), *php_raylib_vector2_fetch_data(phpP1), *php_raylib_vector2_fetch_data(phpP2), *php_raylib_vector2_fetch_data(phpP3)));
}

// Check if point is within a polygon described by array of vertices
// RLAPI bool CheckCollisionPointPoly(Vector2 point, Vector2* points, int pointCount);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionPointPoly, 0, 0, 3)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, pointCount)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionPointPoly)
{
    zval *point;
    zval *points;
    zend_long pointCount;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ARRAY(points)
        Z_PARAM_LONG(pointCount)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    zval *points_element;
    int points_index;
    HashTable *points_hash = Z_ARRVAL_P(points);
    SEPARATE_ARRAY(points);
    int points_count = zend_hash_num_elements(points_hash);
    Vector2* points_array = safe_emalloc(sizeof(Vector2*), points_count, 0);
    ZEND_HASH_FOREACH_VAL(points_hash, points_element) {
        ZVAL_DEREF(points_element);
        if ((Z_TYPE_P(points_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(points_element), php_raylib_vector2_ce))) {
            php_raylib_vector2_object *vector2_obj =  Z_VECTOR2_OBJ_P(points_element);
            points_array[points_index] = *php_raylib_vector2_fetch_data(vector2_obj);
        }

        points_index++;
    } ZEND_HASH_FOREACH_END();

    RETURN_BOOL(CheckCollisionPointPoly(*php_raylib_vector2_fetch_data(phpPoint), points_array, (pointCount <= INT_MAX) ? (int) ((zend_long) pointCount) : -1));
}

// Check the collision between two lines defined by two points each, returns collision point by reference
// RLAPI bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2* collisionPoint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionLines, 0, 0, 5)
    ZEND_ARG_INFO(0, startPos1)
    ZEND_ARG_INFO(0, endPos1)
    ZEND_ARG_INFO(0, startPos2)
    ZEND_ARG_INFO(0, endPos2)
    ZEND_ARG_INFO(0, collisionPoint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionLines)
{
    zval *startPos1;
    zval *endPos1;
    zval *startPos2;
    zval *endPos2;
    zval *collisionPoint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(startPos1)
        Z_PARAM_ZVAL(endPos1)
        Z_PARAM_ZVAL(startPos2)
        Z_PARAM_ZVAL(endPos2)
        Z_PARAM_ZVAL(collisionPoint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpStartPos1 = Z_VECTOR2_OBJ_P(startPos1);
    php_raylib_vector2_object *phpEndPos1 = Z_VECTOR2_OBJ_P(endPos1);
    php_raylib_vector2_object *phpStartPos2 = Z_VECTOR2_OBJ_P(startPos2);
    php_raylib_vector2_object *phpEndPos2 = Z_VECTOR2_OBJ_P(endPos2);
    php_raylib_vector2_object *phpCollisionPoint = Z_VECTOR2_OBJ_P(collisionPoint);

    RETURN_BOOL(CheckCollisionLines(*php_raylib_vector2_fetch_data(phpStartPos1), *php_raylib_vector2_fetch_data(phpEndPos1), *php_raylib_vector2_fetch_data(phpStartPos2), *php_raylib_vector2_fetch_data(phpEndPos2), php_raylib_vector2_fetch_data(phpCollisionPoint)));
}

// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
// RLAPI bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionPointLine, 0, 0, 4)
    ZEND_ARG_INFO(0, point)
    ZEND_ARG_INFO(0, p1)
    ZEND_ARG_INFO(0, p2)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionPointLine)
{
    zval *point;
    zval *p1;
    zval *p2;
    zend_long threshold;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(point)
        Z_PARAM_ZVAL(p1)
        Z_PARAM_ZVAL(p2)
        Z_PARAM_LONG(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector2_object *phpPoint = Z_VECTOR2_OBJ_P(point);
    php_raylib_vector2_object *phpP1 = Z_VECTOR2_OBJ_P(p1);
    php_raylib_vector2_object *phpP2 = Z_VECTOR2_OBJ_P(p2);

    RETURN_BOOL(CheckCollisionPointLine(*php_raylib_vector2_fetch_data(phpPoint), *php_raylib_vector2_fetch_data(phpP1), *php_raylib_vector2_fetch_data(phpP2), (threshold <= INT_MAX) ? (int) ((zend_long) threshold) : -1));
}

// Get collision rectangle for two rectangles collision
// RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCollisionRec, 0, 0, 2)
    ZEND_ARG_INFO(0, rec1)
    ZEND_ARG_INFO(0, rec2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCollisionRec)
{
    zval *rec1;
    zval *rec2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(rec1)
        Z_PARAM_ZVAL(rec2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rectangle_object *phpRec1 = Z_RECTANGLE_OBJ_P(rec1);
    php_raylib_rectangle_object *phpRec2 = Z_RECTANGLE_OBJ_P(rec2);

    Rectangle originalResult = GetCollisionRec(*php_raylib_rectangle_fetch_data(phpRec1), *php_raylib_rectangle_fetch_data(phpRec2));
    zend_object *result = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);
    php_raylib_rectangle_object *phpResult = php_raylib_rectangle_fetch_object(result);
    Rectangle *rectangleData = php_raylib_rectangle_fetch_data(phpResult);
    // Dereference rectangleData for assignment back to object
    *rectangleData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image from file into CPU memory (RAM)
// RLAPI Image LoadImage(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImage, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImage)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = LoadImage(fileName->val);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image from RAW file data
// RLAPI Image LoadImageRaw(const char * fileName, int width, int height, int format, int headerSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImageRaw, 0, 0, 5)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_INFO(0, headerSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImageRaw)
{
    zend_string *fileName;
    zend_long width;
    zend_long height;
    zend_long format;
    zend_long headerSize;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STR(fileName)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(format)
        Z_PARAM_LONG(headerSize)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = LoadImageRaw(fileName->val, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (format <= INT_MAX) ? (int) ((zend_long) format) : -1, (headerSize <= INT_MAX) ? (int) ((zend_long) headerSize) : -1);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image sequence from file (frames appended to image.data)
// RLAPI Image LoadImageAnim(const char * fileName, int * frames);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImageAnim, 0, 0, 2)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, frames)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImageAnim)
{
    zend_string *fileName;
    zval *frames;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(fileName)
        Z_PARAM_ARRAY(frames)
    ZEND_PARSE_PARAMETERS_END();

    zval *frames_element;
    int frames_index;
    HashTable *frames_hash = Z_ARRVAL_P(frames);
    SEPARATE_ARRAY(frames);
    int frames_count = zend_hash_num_elements(frames_hash);
    int * frames_array = safe_emalloc(sizeof(int *), frames_count, 0);
    ZEND_HASH_FOREACH_VAL(frames_hash, frames_element) {
        ZVAL_DEREF(frames_element);
        if (Z_TYPE_P(frames_element) == IS_LONG) {
            frames_array[frames_index] = (int) Z_LVAL_P(frames_element);
        }

        frames_index++;
    } ZEND_HASH_FOREACH_END();

    Image originalResult = LoadImageAnim(fileName->val, frames_array);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image from memory buffer, fileType refers to extension: i.e. '.png'
// RLAPI Image LoadImageFromMemory(const char * fileType, const unsigned char * fileData, int dataSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImageFromMemory, 0, 0, 3)
    ZEND_ARG_INFO(0, fileType)
    ZEND_ARG_INFO(0, fileData)
    ZEND_ARG_INFO(0, dataSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImageFromMemory)
{
    zend_string *fileType;
    zval *fileData;
    zend_long dataSize;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(fileType)
        Z_PARAM_ARRAY(fileData)
        Z_PARAM_LONG(dataSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *filedata_element;
    int filedata_index;
    HashTable *filedata_hash = Z_ARRVAL_P(fileData);
    SEPARATE_ARRAY(fileData);
    int filedata_count = zend_hash_num_elements(filedata_hash);
    unsigned char * filedata_array = safe_emalloc(sizeof(unsigned char *), filedata_count, 0);
    ZEND_HASH_FOREACH_VAL(filedata_hash, filedata_element) {
        ZVAL_DEREF(filedata_element);
        if (Z_TYPE_P(filedata_element) == IS_LONG) {
            filedata_array[filedata_index] = (const unsigned char) Z_LVAL_P(filedata_element);
        }

        filedata_index++;
    } ZEND_HASH_FOREACH_END();

    Image originalResult = LoadImageFromMemory(fileType->val, filedata_array, (dataSize <= INT_MAX) ? (int) ((zend_long) dataSize) : -1);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image from GPU texture data
// RLAPI Image LoadImageFromTexture(Texture texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImageFromTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImageFromTexture)
{
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    Image originalResult = LoadImageFromTexture(*php_raylib_texture_fetch_data(phpTexture));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load image from screen buffer and (screenshot)
// RLAPI Image LoadImageFromScreen();
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadImageFromScreen, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadImageFromScreen)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Image originalResult = LoadImageFromScreen();
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if an image is ready
// RLAPI bool IsImageReady(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsImageReady, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsImageReady)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    RETURN_BOOL(IsImageReady(*php_raylib_image_fetch_data(phpImage)));
}

// Unload image from CPU memory (RAM)
// RLAPI void UnloadImage(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadImage, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadImage)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    UnloadImage(*php_raylib_image_fetch_data(phpImage));

}

// Export image data to file, returns true on success
// RLAPI bool ExportImage(Image image, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportImage, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportImage)
{
    zval *image;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    RETURN_BOOL(ExportImage(*php_raylib_image_fetch_data(phpImage), fileName->val));
}

// Export image as code file defining an array of bytes, returns true on success
// RLAPI bool ExportImageAsCode(Image image, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportImageAsCode, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportImageAsCode)
{
    zval *image;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    RETURN_BOOL(ExportImageAsCode(*php_raylib_image_fetch_data(phpImage), fileName->val));
}

// Generate image: plain color
// RLAPI Image GenImageColor(int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageColor, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageColor)
{
    zend_long width;
    zend_long height;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Image originalResult = GenImageColor((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: vertical gradient
// RLAPI Image GenImageGradientV(int width, int height, Color top, Color bottom);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageGradientV, 0, 0, 4)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, top)
    ZEND_ARG_INFO(0, bottom)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageGradientV)
{
    zend_long width;
    zend_long height;
    zval *top;
    zval *bottom;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(top)
        Z_PARAM_ZVAL(bottom)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpTop = Z_COLOR_OBJ_P(top);
    php_raylib_color_object *phpBottom = Z_COLOR_OBJ_P(bottom);

    Image originalResult = GenImageGradientV((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpTop), *php_raylib_color_fetch_data(phpBottom));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: horizontal gradient
// RLAPI Image GenImageGradientH(int width, int height, Color left, Color right);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageGradientH, 0, 0, 4)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, left)
    ZEND_ARG_INFO(0, right)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageGradientH)
{
    zend_long width;
    zend_long height;
    zval *left;
    zval *right;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(left)
        Z_PARAM_ZVAL(right)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpLeft = Z_COLOR_OBJ_P(left);
    php_raylib_color_object *phpRight = Z_COLOR_OBJ_P(right);

    Image originalResult = GenImageGradientH((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpLeft), *php_raylib_color_fetch_data(phpRight));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: radial gradient
// RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageGradientRadial, 0, 0, 5)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, density)
    ZEND_ARG_INFO(0, inner)
    ZEND_ARG_INFO(0, outer)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageGradientRadial)
{
    zend_long width;
    zend_long height;
    double density;
    zval *inner;
    zval *outer;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_DOUBLE(density)
        Z_PARAM_ZVAL(inner)
        Z_PARAM_ZVAL(outer)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpInner = Z_COLOR_OBJ_P(inner);
    php_raylib_color_object *phpOuter = Z_COLOR_OBJ_P(outer);

    Image originalResult = GenImageGradientRadial((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (float) density, *php_raylib_color_fetch_data(phpInner), *php_raylib_color_fetch_data(phpOuter));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: checked
// RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageChecked, 0, 0, 6)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, checksX)
    ZEND_ARG_INFO(0, checksY)
    ZEND_ARG_INFO(0, col1)
    ZEND_ARG_INFO(0, col2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageChecked)
{
    zend_long width;
    zend_long height;
    zend_long checksX;
    zend_long checksY;
    zval *col1;
    zval *col2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(checksX)
        Z_PARAM_LONG(checksY)
        Z_PARAM_ZVAL(col1)
        Z_PARAM_ZVAL(col2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpCol1 = Z_COLOR_OBJ_P(col1);
    php_raylib_color_object *phpCol2 = Z_COLOR_OBJ_P(col2);

    Image originalResult = GenImageChecked((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (checksX <= INT_MAX) ? (int) ((zend_long) checksX) : -1, (checksY <= INT_MAX) ? (int) ((zend_long) checksY) : -1, *php_raylib_color_fetch_data(phpCol1), *php_raylib_color_fetch_data(phpCol2));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: white noise
// RLAPI Image GenImageWhiteNoise(int width, int height, float factor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageWhiteNoise, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, factor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageWhiteNoise)
{
    zend_long width;
    zend_long height;
    double factor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_DOUBLE(factor)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = GenImageWhiteNoise((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (float) factor);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: perlin noise
// RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImagePerlinNoise, 0, 0, 5)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, scale)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImagePerlinNoise)
{
    zend_long width;
    zend_long height;
    zend_long offsetX;
    zend_long offsetY;
    double scale;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(offsetY)
        Z_PARAM_DOUBLE(scale)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = GenImagePerlinNoise((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (offsetX <= INT_MAX) ? (int) ((zend_long) offsetX) : -1, (offsetY <= INT_MAX) ? (int) ((zend_long) offsetY) : -1, (float) scale);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: cellular algorithm, bigger tileSize means bigger cells
// RLAPI Image GenImageCellular(int width, int height, int tileSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageCellular, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, tileSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageCellular)
{
    zend_long width;
    zend_long height;
    zend_long tileSize;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(tileSize)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = GenImageCellular((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (tileSize <= INT_MAX) ? (int) ((zend_long) tileSize) : -1);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate image: grayscale image from text data
// RLAPI Image GenImageText(int width, int height, const char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenImageText, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenImageText)
{
    zend_long width;
    zend_long height;
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    Image originalResult = GenImageText((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, text->val);
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Create an image duplicate (useful for transformations)
// RLAPI Image ImageCopy(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_rlImageCopy, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(rlImageCopy)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    Image originalResult = ImageCopy(*php_raylib_image_fetch_data(phpImage));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Create an image from another image piece
// RLAPI Image ImageFromImage(Image image, Rectangle rec);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageFromImage, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, rec)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageFromImage)
{
    zval *image;
    zval *rec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(rec)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);

    Image originalResult = ImageFromImage(*php_raylib_image_fetch_data(phpImage), *php_raylib_rectangle_fetch_data(phpRec));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Create an image from text (default font)
// RLAPI Image ImageText(const char * text, int fontSize, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageText, 0, 0, 3)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageText)
{
    zend_string *text;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Image originalResult = ImageText(text->val, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1, *php_raylib_color_fetch_data(phpColor));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Create an image from text (custom sprite font)
// RLAPI Image ImageTextEx(Font font, const char * text, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageTextEx, 0, 0, 5)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageTextEx)
{
    zval *font;
    zend_string *text;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    Image originalResult = ImageTextEx(*php_raylib_font_fetch_data(phpFont), text->val, (float) fontSize, (float) spacing, *php_raylib_color_fetch_data(phpTint));
    zend_object *result = php_raylib_image_new_ex(php_raylib_image_ce, NULL);
    php_raylib_image_object *phpResult = php_raylib_image_fetch_object(result);
    Image *imageData = php_raylib_image_fetch_data(phpResult);
    // Dereference imageData for assignment back to object
    *imageData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Convert image data to desired format
// RLAPI void ImageFormat(Image* image, int newFormat);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageFormat, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, newFormat)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageFormat)
{
    zval *image;
    zend_long newFormat;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(newFormat)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageFormat(php_raylib_image_fetch_data(phpImage), (newFormat <= INT_MAX) ? (int) ((zend_long) newFormat) : -1);

}

// Convert image to POT (power-of-two)
// RLAPI void ImageToPOT(Image* image, Color fill);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageToPOT, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, fill)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageToPOT)
{
    zval *image;
    zval *fill;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(fill)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpFill = Z_COLOR_OBJ_P(fill);

    ImageToPOT(php_raylib_image_fetch_data(phpImage), *php_raylib_color_fetch_data(phpFill));

}

// Crop an image to a defined rectangle
// RLAPI void ImageCrop(Image* image, Rectangle crop);
ZEND_BEGIN_ARG_INFO_EX(arginfo_rlImageCrop, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, crop)
ZEND_END_ARG_INFO()
PHP_FUNCTION(rlImageCrop)
{
    zval *image;
    zval *crop;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(crop)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_rectangle_object *phpCrop = Z_RECTANGLE_OBJ_P(crop);

    ImageCrop(php_raylib_image_fetch_data(phpImage), *php_raylib_rectangle_fetch_data(phpCrop));

}

// Crop image depending on alpha value
// RLAPI void ImageAlphaCrop(Image* image, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageAlphaCrop, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageAlphaCrop)
{
    zval *image;
    double threshold;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageAlphaCrop(php_raylib_image_fetch_data(phpImage), (float) threshold);

}

// Clear alpha channel to desired color
// RLAPI void ImageAlphaClear(Image* image, Color color, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageAlphaClear, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageAlphaClear)
{
    zval *image;
    zval *color;
    double threshold;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageAlphaClear(php_raylib_image_fetch_data(phpImage), *php_raylib_color_fetch_data(phpColor), (float) threshold);

}

// Apply alpha mask to image
// RLAPI void ImageAlphaMask(Image* image, Image alphaMask);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageAlphaMask, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, alphaMask)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageAlphaMask)
{
    zval *image;
    zval *alphaMask;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(alphaMask)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_image_object *phpAlphaMask = Z_IMAGE_OBJ_P(alphaMask);

    ImageAlphaMask(php_raylib_image_fetch_data(phpImage), *php_raylib_image_fetch_data(phpAlphaMask));

}

// Premultiply alpha channel
// RLAPI void ImageAlphaPremultiply(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageAlphaPremultiply, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageAlphaPremultiply)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageAlphaPremultiply(php_raylib_image_fetch_data(phpImage));

}

// Apply Gaussian blur using a box blur approximation
// RLAPI void ImageBlurGaussian(Image* image, int blurSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageBlurGaussian, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, blurSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageBlurGaussian)
{
    zval *image;
    zend_long blurSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(blurSize)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageBlurGaussian(php_raylib_image_fetch_data(phpImage), (blurSize <= INT_MAX) ? (int) ((zend_long) blurSize) : -1);

}

// Resize image (Bicubic scaling algorithm)
// RLAPI void ImageResize(Image* image, int newWidth, int newHeight);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageResize, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageResize)
{
    zval *image;
    zend_long newWidth;
    zend_long newHeight;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageResize(php_raylib_image_fetch_data(phpImage), (newWidth <= INT_MAX) ? (int) ((zend_long) newWidth) : -1, (newHeight <= INT_MAX) ? (int) ((zend_long) newHeight) : -1);

}

// Resize image (Nearest-Neighbor scaling algorithm)
// RLAPI void ImageResizeNN(Image* image, int newWidth, int newHeight);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageResizeNN, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageResizeNN)
{
    zval *image;
    zend_long newWidth;
    zend_long newHeight;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageResizeNN(php_raylib_image_fetch_data(phpImage), (newWidth <= INT_MAX) ? (int) ((zend_long) newWidth) : -1, (newHeight <= INT_MAX) ? (int) ((zend_long) newHeight) : -1);

}

// Resize canvas and fill with color
// RLAPI void ImageResizeCanvas(Image* image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageResizeCanvas, 0, 0, 6)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, newWidth)
    ZEND_ARG_INFO(0, newHeight)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, fill)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageResizeCanvas)
{
    zval *image;
    zend_long newWidth;
    zend_long newHeight;
    zend_long offsetX;
    zend_long offsetY;
    zval *fill;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(newWidth)
        Z_PARAM_LONG(newHeight)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(offsetY)
        Z_PARAM_ZVAL(fill)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpFill = Z_COLOR_OBJ_P(fill);

    ImageResizeCanvas(php_raylib_image_fetch_data(phpImage), (newWidth <= INT_MAX) ? (int) ((zend_long) newWidth) : -1, (newHeight <= INT_MAX) ? (int) ((zend_long) newHeight) : -1, (offsetX <= INT_MAX) ? (int) ((zend_long) offsetX) : -1, (offsetY <= INT_MAX) ? (int) ((zend_long) offsetY) : -1, *php_raylib_color_fetch_data(phpFill));

}

// Compute all mipmap levels for a provided image
// RLAPI void ImageMipmaps(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageMipmaps, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageMipmaps)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageMipmaps(php_raylib_image_fetch_data(phpImage));

}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
// RLAPI void ImageDither(Image* image, int rBpp, int gBpp, int bBpp, int aBpp);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDither, 0, 0, 5)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, rBpp)
    ZEND_ARG_INFO(0, gBpp)
    ZEND_ARG_INFO(0, bBpp)
    ZEND_ARG_INFO(0, aBpp)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDither)
{
    zval *image;
    zend_long rBpp;
    zend_long gBpp;
    zend_long bBpp;
    zend_long aBpp;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(rBpp)
        Z_PARAM_LONG(gBpp)
        Z_PARAM_LONG(bBpp)
        Z_PARAM_LONG(aBpp)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageDither(php_raylib_image_fetch_data(phpImage), (rBpp <= INT_MAX) ? (int) ((zend_long) rBpp) : -1, (gBpp <= INT_MAX) ? (int) ((zend_long) gBpp) : -1, (bBpp <= INT_MAX) ? (int) ((zend_long) bBpp) : -1, (aBpp <= INT_MAX) ? (int) ((zend_long) aBpp) : -1);

}

// Flip image vertically
// RLAPI void ImageFlipVertical(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageFlipVertical, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageFlipVertical)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageFlipVertical(php_raylib_image_fetch_data(phpImage));

}

// Flip image horizontally
// RLAPI void ImageFlipHorizontal(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageFlipHorizontal, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageFlipHorizontal)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageFlipHorizontal(php_raylib_image_fetch_data(phpImage));

}

// Rotate image clockwise 90deg
// RLAPI void ImageRotateCW(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageRotateCW, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageRotateCW)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageRotateCW(php_raylib_image_fetch_data(phpImage));

}

// Rotate image counter-clockwise 90deg
// RLAPI void ImageRotateCCW(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageRotateCCW, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageRotateCCW)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageRotateCCW(php_raylib_image_fetch_data(phpImage));

}

// Modify image color: tint
// RLAPI void ImageColorTint(Image* image, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorTint, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorTint)
{
    zval *image;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageColorTint(php_raylib_image_fetch_data(phpImage), *php_raylib_color_fetch_data(phpColor));

}

// Modify image color: invert
// RLAPI void ImageColorInvert(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorInvert, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorInvert)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageColorInvert(php_raylib_image_fetch_data(phpImage));

}

// Modify image color: grayscale
// RLAPI void ImageColorGrayscale(Image* image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorGrayscale, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorGrayscale)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageColorGrayscale(php_raylib_image_fetch_data(phpImage));

}

// Modify image color: contrast (-100 to 100)
// RLAPI void ImageColorContrast(Image* image, float contrast);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorContrast, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, contrast)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorContrast)
{
    zval *image;
    double contrast;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_DOUBLE(contrast)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageColorContrast(php_raylib_image_fetch_data(phpImage), (float) contrast);

}

// Modify image color: brightness (-255 to 255)
// RLAPI void ImageColorBrightness(Image* image, int brightness);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorBrightness, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, brightness)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorBrightness)
{
    zval *image;
    zend_long brightness;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(brightness)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    ImageColorBrightness(php_raylib_image_fetch_data(phpImage), (brightness <= INT_MAX) ? (int) ((zend_long) brightness) : -1);

}

// Modify image color: replace color
// RLAPI void ImageColorReplace(Image* image, Color color, Color replace);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageColorReplace, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, replace)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageColorReplace)
{
    zval *image;
    zval *color;
    zval *replace;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(color)
        Z_PARAM_ZVAL(replace)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_color_object *phpReplace = Z_COLOR_OBJ_P(replace);

    ImageColorReplace(php_raylib_image_fetch_data(phpImage), *php_raylib_color_fetch_data(phpColor), *php_raylib_color_fetch_data(phpReplace));

}

// Unload color data loaded with LoadImageColors()
// RLAPI void UnloadImageColors(Color* colors);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadImageColors, 0, 0, 1)
    ZEND_ARG_INFO(0, colors)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadImageColors)
{
    zval *colors;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(colors)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColors = Z_COLOR_OBJ_P(colors);

    UnloadImageColors(php_raylib_color_fetch_data(phpColors));

}

// Unload colors palette loaded with LoadImagePalette()
// RLAPI void UnloadImagePalette(Color* colors);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadImagePalette, 0, 0, 1)
    ZEND_ARG_INFO(0, colors)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadImagePalette)
{
    zval *colors;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(colors)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColors = Z_COLOR_OBJ_P(colors);

    UnloadImagePalette(php_raylib_color_fetch_data(phpColors));

}

// Get image alpha border rectangle
// RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetImageAlphaBorder, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetImageAlphaBorder)
{
    zval *image;
    double threshold;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_DOUBLE(threshold)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    Rectangle originalResult = GetImageAlphaBorder(*php_raylib_image_fetch_data(phpImage), (float) threshold);
    zend_object *result = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);
    php_raylib_rectangle_object *phpResult = php_raylib_rectangle_fetch_object(result);
    Rectangle *rectangleData = php_raylib_rectangle_fetch_data(phpResult);
    // Dereference rectangleData for assignment back to object
    *rectangleData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get image pixel color at (x, y) position
// RLAPI Color GetImageColor(Image image, int x, int y);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetImageColor, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetImageColor)
{
    zval *image;
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    Color originalResult = GetImageColor(*php_raylib_image_fetch_data(phpImage), (x <= INT_MAX) ? (int) ((zend_long) x) : -1, (y <= INT_MAX) ? (int) ((zend_long) y) : -1);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Clear image background with given color
// RLAPI void ImageClearBackground(Image* dst, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageClearBackground, 0, 0, 2)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageClearBackground)
{
    zval *dst;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageClearBackground(php_raylib_image_fetch_data(phpDst), *php_raylib_color_fetch_data(phpColor));

}

// Draw pixel within an image
// RLAPI void ImageDrawPixel(Image* dst, int posX, int posY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawPixel, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawPixel)
{
    zval *dst;
    zend_long posX;
    zend_long posY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawPixel(php_raylib_image_fetch_data(phpDst), (posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw pixel within an image (Vector version)
// RLAPI void ImageDrawPixelV(Image* dst, Vector2 position, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawPixelV, 0, 0, 3)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawPixelV)
{
    zval *dst;
    zval *position;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawPixelV(php_raylib_image_fetch_data(phpDst), *php_raylib_vector2_fetch_data(phpPosition), *php_raylib_color_fetch_data(phpColor));

}

// Draw line within an image
// RLAPI void ImageDrawLine(Image* dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawLine, 0, 0, 6)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, startPosX)
    ZEND_ARG_INFO(0, startPosY)
    ZEND_ARG_INFO(0, endPosX)
    ZEND_ARG_INFO(0, endPosY)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawLine)
{
    zval *dst;
    zend_long startPosX;
    zend_long startPosY;
    zend_long endPosX;
    zend_long endPosY;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_LONG(startPosX)
        Z_PARAM_LONG(startPosY)
        Z_PARAM_LONG(endPosX)
        Z_PARAM_LONG(endPosY)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawLine(php_raylib_image_fetch_data(phpDst), (startPosX <= INT_MAX) ? (int) ((zend_long) startPosX) : -1, (startPosY <= INT_MAX) ? (int) ((zend_long) startPosY) : -1, (endPosX <= INT_MAX) ? (int) ((zend_long) endPosX) : -1, (endPosY <= INT_MAX) ? (int) ((zend_long) endPosY) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw line within an image (Vector version)
// RLAPI void ImageDrawLineV(Image* dst, Vector2 start, Vector2 end, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawLineV, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, start)
    ZEND_ARG_INFO(0, end)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawLineV)
{
    zval *dst;
    zval *start;
    zval *end;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(start)
        Z_PARAM_ZVAL(end)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_vector2_object *phpStart = Z_VECTOR2_OBJ_P(start);
    php_raylib_vector2_object *phpEnd = Z_VECTOR2_OBJ_P(end);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawLineV(php_raylib_image_fetch_data(phpDst), *php_raylib_vector2_fetch_data(phpStart), *php_raylib_vector2_fetch_data(phpEnd), *php_raylib_color_fetch_data(phpColor));

}

// Draw a filled circle within an image
// RLAPI void ImageDrawCircle(Image* dst, int centerX, int centerY, int radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawCircle, 0, 0, 5)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawCircle)
{
    zval *dst;
    zend_long centerX;
    zend_long centerY;
    zend_long radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_LONG(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawCircle(php_raylib_image_fetch_data(phpDst), (centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (radius <= INT_MAX) ? (int) ((zend_long) radius) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a filled circle within an image (Vector version)
// RLAPI void ImageDrawCircleV(Image* dst, Vector2 center, int radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawCircleV, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawCircleV)
{
    zval *dst;
    zval *center;
    zend_long radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawCircleV(php_raylib_image_fetch_data(phpDst), *php_raylib_vector2_fetch_data(phpCenter), (radius <= INT_MAX) ? (int) ((zend_long) radius) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw circle outline within an image
// RLAPI void ImageDrawCircleLines(Image* dst, int centerX, int centerY, int radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawCircleLines, 0, 0, 5)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, centerX)
    ZEND_ARG_INFO(0, centerY)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawCircleLines)
{
    zval *dst;
    zend_long centerX;
    zend_long centerY;
    zend_long radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_LONG(centerX)
        Z_PARAM_LONG(centerY)
        Z_PARAM_LONG(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawCircleLines(php_raylib_image_fetch_data(phpDst), (centerX <= INT_MAX) ? (int) ((zend_long) centerX) : -1, (centerY <= INT_MAX) ? (int) ((zend_long) centerY) : -1, (radius <= INT_MAX) ? (int) ((zend_long) radius) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw circle outline within an image (Vector version)
// RLAPI void ImageDrawCircleLinesV(Image* dst, Vector2 center, int radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawCircleLinesV, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawCircleLinesV)
{
    zval *dst;
    zval *center;
    zend_long radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(center)
        Z_PARAM_LONG(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_vector2_object *phpCenter = Z_VECTOR2_OBJ_P(center);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawCircleLinesV(php_raylib_image_fetch_data(phpDst), *php_raylib_vector2_fetch_data(phpCenter), (radius <= INT_MAX) ? (int) ((zend_long) radius) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle within an image
// RLAPI void ImageDrawRectangle(Image* dst, int posX, int posY, int width, int height, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawRectangle, 0, 0, 6)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawRectangle)
{
    zval *dst;
    zend_long posX;
    zend_long posY;
    zend_long width;
    zend_long height;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawRectangle(php_raylib_image_fetch_data(phpDst), (posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle within an image (Vector version)
// RLAPI void ImageDrawRectangleV(Image* dst, Vector2 position, Vector2 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawRectangleV, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawRectangleV)
{
    zval *dst;
    zval *position;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawRectangleV(php_raylib_image_fetch_data(phpDst), *php_raylib_vector2_fetch_data(phpPosition), *php_raylib_vector2_fetch_data(phpSize), *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle within an image
// RLAPI void ImageDrawRectangleRec(Image* dst, Rectangle rec, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawRectangleRec, 0, 0, 3)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawRectangleRec)
{
    zval *dst;
    zval *rec;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawRectangleRec(php_raylib_image_fetch_data(phpDst), *php_raylib_rectangle_fetch_data(phpRec), *php_raylib_color_fetch_data(phpColor));

}

// Draw rectangle lines within an image
// RLAPI void ImageDrawRectangleLines(Image* dst, Rectangle rec, int thick, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawRectangleLines, 0, 0, 4)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, rec)
    ZEND_ARG_INFO(0, thick)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawRectangleLines)
{
    zval *dst;
    zval *rec;
    zend_long thick;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(rec)
        Z_PARAM_LONG(thick)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_rectangle_object *phpRec = Z_RECTANGLE_OBJ_P(rec);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawRectangleLines(php_raylib_image_fetch_data(phpDst), *php_raylib_rectangle_fetch_data(phpRec), (thick <= INT_MAX) ? (int) ((zend_long) thick) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a source image within a destination image (tint applied to source)
// RLAPI void ImageDraw(Image* dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDraw, 0, 0, 5)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, src)
    ZEND_ARG_INFO(0, srcRec)
    ZEND_ARG_INFO(0, dstRec)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDraw)
{
    zval *dst;
    zval *src;
    zval *srcRec;
    zval *dstRec;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(src)
        Z_PARAM_ZVAL(srcRec)
        Z_PARAM_ZVAL(dstRec)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_image_object *phpSrc = Z_IMAGE_OBJ_P(src);
    php_raylib_rectangle_object *phpSrcRec = Z_RECTANGLE_OBJ_P(srcRec);
    php_raylib_rectangle_object *phpDstRec = Z_RECTANGLE_OBJ_P(dstRec);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    ImageDraw(php_raylib_image_fetch_data(phpDst), *php_raylib_image_fetch_data(phpSrc), *php_raylib_rectangle_fetch_data(phpSrcRec), *php_raylib_rectangle_fetch_data(phpDstRec), *php_raylib_color_fetch_data(phpTint));

}

// Draw text (using default font) within an image (destination)
// RLAPI void ImageDrawText(Image* dst, const char * text, int posX, int posY, int fontSize, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawText, 0, 0, 6)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawText)
{
    zval *dst;
    zend_string *text;
    zend_long posX;
    zend_long posY;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    ImageDrawText(php_raylib_image_fetch_data(phpDst), text->val, (posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw text (custom sprite font) within an image (destination)
// RLAPI void ImageDrawTextEx(Image* dst, Font font, const char * text, Vector2 position, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ImageDrawTextEx, 0, 0, 7)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ImageDrawTextEx)
{
    zval *dst;
    zval *font;
    zend_string *text;
    zval *position;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpDst = Z_IMAGE_OBJ_P(dst);
    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    ImageDrawTextEx(php_raylib_image_fetch_data(phpDst), *php_raylib_font_fetch_data(phpFont), text->val, *php_raylib_vector2_fetch_data(phpPosition), (float) fontSize, (float) spacing, *php_raylib_color_fetch_data(phpTint));

}

// Load texture from file into GPU memory (VRAM)
// RLAPI Texture LoadTexture(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadTexture)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Texture originalResult = LoadTexture(fileName->val);
    zend_object *result = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
    php_raylib_texture_object *phpResult = php_raylib_texture_fetch_object(result);
    Texture *textureData = php_raylib_texture_fetch_data(phpResult);
    // Dereference textureData for assignment back to object
    *textureData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load texture from image data
// RLAPI Texture LoadTextureFromImage(Image image);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadTextureFromImage, 0, 0, 1)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadTextureFromImage)
{
    zval *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(image)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    Texture originalResult = LoadTextureFromImage(*php_raylib_image_fetch_data(phpImage));
    zend_object *result = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
    php_raylib_texture_object *phpResult = php_raylib_texture_fetch_object(result);
    Texture *textureData = php_raylib_texture_fetch_data(phpResult);
    // Dereference textureData for assignment back to object
    *textureData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load cubemap from image, multiple image cubemap layouts supported
// RLAPI Texture LoadTextureCubemap(Image image, int layout);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadTextureCubemap, 0, 0, 2)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, layout)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadTextureCubemap)
{
    zval *image;
    zend_long layout;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(image)
        Z_PARAM_LONG(layout)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);

    Texture originalResult = LoadTextureCubemap(*php_raylib_image_fetch_data(phpImage), (layout <= INT_MAX) ? (int) ((zend_long) layout) : -1);
    zend_object *result = php_raylib_texture_new_ex(php_raylib_texture_ce, NULL);
    php_raylib_texture_object *phpResult = php_raylib_texture_fetch_object(result);
    Texture *textureData = php_raylib_texture_fetch_data(phpResult);
    // Dereference textureData for assignment back to object
    *textureData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load texture for rendering (framebuffer)
// RLAPI RenderTexture LoadRenderTexture(int width, int height);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadRenderTexture, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadRenderTexture)
{
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();


    RenderTexture originalResult = LoadRenderTexture((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1);
    zend_object *result = php_raylib_rendertexture_new_ex(php_raylib_rendertexture_ce, NULL);
    php_raylib_rendertexture_object *phpResult = php_raylib_rendertexture_fetch_object(result);
    RenderTexture *rendertextureData = php_raylib_rendertexture_fetch_data(phpResult);
    // Dereference rendertextureData for assignment back to object
    *rendertextureData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if a texture is ready
// RLAPI bool IsTextureReady(Texture texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsTextureReady, 0, 0, 1)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsTextureReady)
{
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    RETURN_BOOL(IsTextureReady(*php_raylib_texture_fetch_data(phpTexture)));
}

// Unload texture from GPU memory (VRAM)
// RLAPI void UnloadTexture(Texture texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadTexture)
{
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    UnloadTexture(*php_raylib_texture_fetch_data(phpTexture));

}

// Check if a render texture is ready
// RLAPI bool IsRenderTextureReady(RenderTexture target);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsRenderTextureReady, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsRenderTextureReady)
{
    zval *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rendertexture_object *phpTarget = Z_RENDERTEXTURE_OBJ_P(target);

    RETURN_BOOL(IsRenderTextureReady(*php_raylib_rendertexture_fetch_data(phpTarget)));
}

// Unload render texture from GPU memory (VRAM)
// RLAPI void UnloadRenderTexture(RenderTexture target);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadRenderTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadRenderTexture)
{
    zval *target;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(target)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_rendertexture_object *phpTarget = Z_RENDERTEXTURE_OBJ_P(target);

    UnloadRenderTexture(*php_raylib_rendertexture_fetch_data(phpTarget));

}

// Generate GPU mipmaps for a texture
// RLAPI void GenTextureMipmaps(Texture* texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenTextureMipmaps, 0, 0, 1)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenTextureMipmaps)
{
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    GenTextureMipmaps(php_raylib_texture_fetch_data(phpTexture));

}

// Set texture scaling filter mode
// RLAPI void SetTextureFilter(Texture texture, int filter);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetTextureFilter, 0, 0, 2)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetTextureFilter)
{
    zval *texture;
    zend_long filter;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_LONG(filter)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    SetTextureFilter(*php_raylib_texture_fetch_data(phpTexture), (filter <= INT_MAX) ? (int) ((zend_long) filter) : -1);

}

// Set texture wrapping mode
// RLAPI void SetTextureWrap(Texture texture, int wrap);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetTextureWrap, 0, 0, 2)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, wrap)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetTextureWrap)
{
    zval *texture;
    zend_long wrap;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_LONG(wrap)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    SetTextureWrap(*php_raylib_texture_fetch_data(phpTexture), (wrap <= INT_MAX) ? (int) ((zend_long) wrap) : -1);

}

// Draw a Texture2D
// RLAPI void DrawTexture(Texture texture, int posX, int posY, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTexture, 0, 0, 4)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTexture)
{
    zval *texture;
    zend_long posX;
    zend_long posY;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTexture(*php_raylib_texture_fetch_data(phpTexture), (posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, *php_raylib_color_fetch_data(phpTint));

}

// Draw a Texture2D with position defined as Vector2
// RLAPI void DrawTextureV(Texture texture, Vector2 position, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextureV, 0, 0, 3)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextureV)
{
    zval *texture;
    zval *position;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextureV(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_vector2_fetch_data(phpPosition), *php_raylib_color_fetch_data(phpTint));

}

// Draw a Texture2D with extended parameters
// RLAPI void DrawTextureEx(Texture texture, Vector2 position, float rotation, float scale, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextureEx, 0, 0, 5)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextureEx)
{
    zval *texture;
    zval *position;
    double rotation;
    double scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_DOUBLE(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextureEx(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_vector2_fetch_data(phpPosition), (float) rotation, (float) scale, *php_raylib_color_fetch_data(phpTint));

}

// Draw a part of a texture defined by a rectangle
// RLAPI void DrawTextureRec(Texture texture, Rectangle source, Vector2 position, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextureRec, 0, 0, 4)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, source)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextureRec)
{
    zval *texture;
    zval *source;
    zval *position;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(source)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(source);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextureRec(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_rectangle_fetch_data(phpSource), *php_raylib_vector2_fetch_data(phpPosition), *php_raylib_color_fetch_data(phpTint));

}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
// RLAPI void DrawTexturePro(Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTexturePro, 0, 0, 6)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, source)
    ZEND_ARG_INFO(0, dest)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTexturePro)
{
    zval *texture;
    zval *source;
    zval *dest;
    zval *origin;
    double rotation;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(source)
        Z_PARAM_ZVAL(dest)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(source);
    php_raylib_rectangle_object *phpDest = Z_RECTANGLE_OBJ_P(dest);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTexturePro(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_rectangle_fetch_data(phpSource), *php_raylib_rectangle_fetch_data(phpDest), *php_raylib_vector2_fetch_data(phpOrigin), (float) rotation, *php_raylib_color_fetch_data(phpTint));

}

// Draws a texture (or part of it) that stretches or shrinks nicely
// RLAPI void DrawTextureNPatch(Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextureNPatch, 0, 0, 6)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, nPatchInfo)
    ZEND_ARG_INFO(0, dest)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextureNPatch)
{
    zval *texture;
    zval *nPatchInfo;
    zval *dest;
    zval *origin;
    double rotation;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(nPatchInfo)
        Z_PARAM_ZVAL(dest)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_npatchinfo_object *phpNPatchInfo = Z_NPATCHINFO_OBJ_P(nPatchInfo);
    php_raylib_rectangle_object *phpDest = Z_RECTANGLE_OBJ_P(dest);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextureNPatch(*php_raylib_texture_fetch_data(phpTexture), *php_raylib_npatchinfo_fetch_data(phpNPatchInfo), *php_raylib_rectangle_fetch_data(phpDest), *php_raylib_vector2_fetch_data(phpOrigin), (float) rotation, *php_raylib_color_fetch_data(phpTint));

}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
// RLAPI Color Fade(Color color, float alpha);
ZEND_BEGIN_ARG_INFO_EX(arginfo_Fade, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
PHP_FUNCTION(Fade)
{
    zval *color;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(alpha)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Color originalResult = Fade(*php_raylib_color_fetch_data(phpColor), (float) alpha);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get hexadecimal value for a Color
// RLAPI int ColorToInt(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorToInt, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorToInt)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    RETURN_LONG(ColorToInt(*php_raylib_color_fetch_data(phpColor)));
}

// Get Color normalized as float [0..1]
// RLAPI Vector4 ColorNormalize(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorNormalize, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorNormalize)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Vector4 originalResult = ColorNormalize(*php_raylib_color_fetch_data(phpColor));
    zend_object *result = php_raylib_vector4_new_ex(php_raylib_vector4_ce, NULL);
    php_raylib_vector4_object *phpResult = php_raylib_vector4_fetch_object(result);
    Vector4 *vector4Data = php_raylib_vector4_fetch_data(phpResult);
    // Dereference vector4Data for assignment back to object
    *vector4Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get Color from normalized values [0..1]
// RLAPI Color ColorFromNormalized(Vector4 normalized);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorFromNormalized, 0, 0, 1)
    ZEND_ARG_INFO(0, normalized)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorFromNormalized)
{
    zval *normalized;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(normalized)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector4_object *phpNormalized = Z_VECTOR4_OBJ_P(normalized);

    Color originalResult = ColorFromNormalized(*php_raylib_vector4_fetch_data(phpNormalized));
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get HSV values for a Color, hue [0..360], saturation/value [0..1]
// RLAPI Vector3 ColorToHSV(Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorToHSV, 0, 0, 1)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorToHSV)
{
    zval *color;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Vector3 originalResult = ColorToHSV(*php_raylib_color_fetch_data(phpColor));
    zend_object *result = php_raylib_vector3_new_ex(php_raylib_vector3_ce, NULL);
    php_raylib_vector3_object *phpResult = php_raylib_vector3_fetch_object(result);
    Vector3 *vector3Data = php_raylib_vector3_fetch_data(phpResult);
    // Dereference vector3Data for assignment back to object
    *vector3Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get a Color from HSV values, hue [0..360], saturation/value [0..1]
// RLAPI Color ColorFromHSV(float hue, float saturation, float value);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorFromHSV, 0, 0, 3)
    ZEND_ARG_INFO(0, hue)
    ZEND_ARG_INFO(0, saturation)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorFromHSV)
{
    double hue;
    double saturation;
    double value;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(hue)
        Z_PARAM_DOUBLE(saturation)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();


    Color originalResult = ColorFromHSV((float) hue, (float) saturation, (float) value);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get color multiplied with another color
// RLAPI Color ColorTint(Color color, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorTint, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorTint)
{
    zval *color;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    Color originalResult = ColorTint(*php_raylib_color_fetch_data(phpColor), *php_raylib_color_fetch_data(phpTint));
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
// RLAPI Color ColorBrightness(Color color, float factor);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorBrightness, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, factor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorBrightness)
{
    zval *color;
    double factor;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(factor)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Color originalResult = ColorBrightness(*php_raylib_color_fetch_data(phpColor), (float) factor);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get color with contrast correction, contrast values between -1.0f and 1.0f
// RLAPI Color ColorContrast(Color color, float contrast);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorContrast, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, contrast)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorContrast)
{
    zval *color;
    double contrast;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(contrast)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Color originalResult = ColorContrast(*php_raylib_color_fetch_data(phpColor), (float) contrast);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
// RLAPI Color ColorAlpha(Color color, float alpha);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorAlpha, 0, 0, 2)
    ZEND_ARG_INFO(0, color)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorAlpha)
{
    zval *color;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(color)
        Z_PARAM_DOUBLE(alpha)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    Color originalResult = ColorAlpha(*php_raylib_color_fetch_data(phpColor), (float) alpha);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get src alpha-blended into dst color with tint
// RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ColorAlphaBlend, 0, 0, 3)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, src)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ColorAlphaBlend)
{
    zval *dst;
    zval *src;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(dst)
        Z_PARAM_ZVAL(src)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpDst = Z_COLOR_OBJ_P(dst);
    php_raylib_color_object *phpSrc = Z_COLOR_OBJ_P(src);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    Color originalResult = ColorAlphaBlend(*php_raylib_color_fetch_data(phpDst), *php_raylib_color_fetch_data(phpSrc), *php_raylib_color_fetch_data(phpTint));
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get Color structure from hexadecimal value
// RLAPI Color GetColor(unsigned int hexValue);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetColor, 0, 0, 1)
    ZEND_ARG_INFO(0, hexValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetColor)
{
    zend_long hexValue;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(hexValue)
    ZEND_PARSE_PARAMETERS_END();


    Color originalResult = GetColor((hexValue <= INT_MAX) ? (int) ((zend_long) hexValue) : -1);
    zend_object *result = php_raylib_color_new_ex(php_raylib_color_ce, NULL);
    php_raylib_color_object *phpResult = php_raylib_color_fetch_object(result);
    Color *colorData = php_raylib_color_fetch_data(phpResult);
    // Dereference colorData for assignment back to object
    *colorData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get pixel data size in bytes for certain format
// RLAPI int GetPixelDataSize(int width, int height, int format);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetPixelDataSize, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetPixelDataSize)
{
    zend_long width;
    zend_long height;
    zend_long format;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_LONG(format)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetPixelDataSize((width <= INT_MAX) ? (int) ((zend_long) width) : -1, (height <= INT_MAX) ? (int) ((zend_long) height) : -1, (format <= INT_MAX) ? (int) ((zend_long) format) : -1));
}

// Get the default Font
// RLAPI Font GetFontDefault();
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetFontDefault, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetFontDefault)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Font originalResult = GetFontDefault();
    zend_object *result = php_raylib_font_new_ex(php_raylib_font_ce, NULL);
    php_raylib_font_object *phpResult = php_raylib_font_fetch_object(result);
    Font *fontData = php_raylib_font_fetch_data(phpResult);
    // Dereference fontData for assignment back to object
    *fontData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load font from file into GPU memory (VRAM)
// RLAPI Font LoadFont(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadFont, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadFont)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Font originalResult = LoadFont(fileName->val);
    zend_object *result = php_raylib_font_new_ex(php_raylib_font_ce, NULL);
    php_raylib_font_object *phpResult = php_raylib_font_fetch_object(result);
    Font *fontData = php_raylib_font_fetch_data(phpResult);
    // Dereference fontData for assignment back to object
    *fontData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load font from file with extended parameters, use NULL for fontChars and 0 for glyphCount to load the default character set
// RLAPI Font LoadFontEx(const char * fileName, int fontSize, int * fontChars, int glyphCount);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadFontEx, 0, 0, 4)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, fontChars)
    ZEND_ARG_INFO(0, glyphCount)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadFontEx)
{
    zend_string *fileName;
    zend_long fontSize;
    zval *fontChars;
    zend_long glyphCount;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_STR(fileName)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ARRAY(fontChars)
        Z_PARAM_LONG(glyphCount)
    ZEND_PARSE_PARAMETERS_END();

    zval *fontchars_element;
    int fontchars_index;
    HashTable *fontchars_hash = Z_ARRVAL_P(fontChars);
    SEPARATE_ARRAY(fontChars);
    int fontchars_count = zend_hash_num_elements(fontchars_hash);
    int * fontchars_array = safe_emalloc(sizeof(int *), fontchars_count, 0);
    ZEND_HASH_FOREACH_VAL(fontchars_hash, fontchars_element) {
        ZVAL_DEREF(fontchars_element);
        if (Z_TYPE_P(fontchars_element) == IS_LONG) {
            fontchars_array[fontchars_index] = (int) Z_LVAL_P(fontchars_element);
        }

        fontchars_index++;
    } ZEND_HASH_FOREACH_END();

    Font originalResult = LoadFontEx(fileName->val, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1, fontchars_array, (glyphCount <= INT_MAX) ? (int) ((zend_long) glyphCount) : -1);
    zend_object *result = php_raylib_font_new_ex(php_raylib_font_ce, NULL);
    php_raylib_font_object *phpResult = php_raylib_font_fetch_object(result);
    Font *fontData = php_raylib_font_fetch_data(phpResult);
    // Dereference fontData for assignment back to object
    *fontData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load font from Image (XNA style)
// RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadFontFromImage, 0, 0, 3)
    ZEND_ARG_INFO(0, image)
    ZEND_ARG_INFO(0, key)
    ZEND_ARG_INFO(0, firstChar)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadFontFromImage)
{
    zval *image;
    zval *key;
    zend_long firstChar;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(image)
        Z_PARAM_ZVAL(key)
        Z_PARAM_LONG(firstChar)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpImage = Z_IMAGE_OBJ_P(image);
    php_raylib_color_object *phpKey = Z_COLOR_OBJ_P(key);

    Font originalResult = LoadFontFromImage(*php_raylib_image_fetch_data(phpImage), *php_raylib_color_fetch_data(phpKey), (firstChar <= INT_MAX) ? (int) ((zend_long) firstChar) : -1);
    zend_object *result = php_raylib_font_new_ex(php_raylib_font_ce, NULL);
    php_raylib_font_object *phpResult = php_raylib_font_fetch_object(result);
    Font *fontData = php_raylib_font_fetch_data(phpResult);
    // Dereference fontData for assignment back to object
    *fontData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
// RLAPI Font LoadFontFromMemory(const char * fileType, const unsigned char * fileData, int dataSize, int fontSize, int * fontChars, int glyphCount);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadFontFromMemory, 0, 0, 6)
    ZEND_ARG_INFO(0, fileType)
    ZEND_ARG_INFO(0, fileData)
    ZEND_ARG_INFO(0, dataSize)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, fontChars)
    ZEND_ARG_INFO(0, glyphCount)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadFontFromMemory)
{
    zend_string *fileType;
    zval *fileData;
    zend_long dataSize;
    zend_long fontSize;
    zval *fontChars;
    zend_long glyphCount;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_STR(fileType)
        Z_PARAM_ARRAY(fileData)
        Z_PARAM_LONG(dataSize)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ARRAY(fontChars)
        Z_PARAM_LONG(glyphCount)
    ZEND_PARSE_PARAMETERS_END();

    zval *filedata_element;
    int filedata_index;
    HashTable *filedata_hash = Z_ARRVAL_P(fileData);
    SEPARATE_ARRAY(fileData);
    int filedata_count = zend_hash_num_elements(filedata_hash);
    unsigned char * filedata_array = safe_emalloc(sizeof(unsigned char *), filedata_count, 0);
    ZEND_HASH_FOREACH_VAL(filedata_hash, filedata_element) {
        ZVAL_DEREF(filedata_element);
        if (Z_TYPE_P(filedata_element) == IS_LONG) {
            filedata_array[filedata_index] = (const unsigned char) Z_LVAL_P(filedata_element);
        }

        filedata_index++;
    } ZEND_HASH_FOREACH_END();
    zval *fontchars_element;
    int fontchars_index;
    HashTable *fontchars_hash = Z_ARRVAL_P(fontChars);
    SEPARATE_ARRAY(fontChars);
    int fontchars_count = zend_hash_num_elements(fontchars_hash);
    int * fontchars_array = safe_emalloc(sizeof(int *), fontchars_count, 0);
    ZEND_HASH_FOREACH_VAL(fontchars_hash, fontchars_element) {
        ZVAL_DEREF(fontchars_element);
        if (Z_TYPE_P(fontchars_element) == IS_LONG) {
            fontchars_array[fontchars_index] = (int) Z_LVAL_P(fontchars_element);
        }

        fontchars_index++;
    } ZEND_HASH_FOREACH_END();

    Font originalResult = LoadFontFromMemory(fileType->val, filedata_array, (dataSize <= INT_MAX) ? (int) ((zend_long) dataSize) : -1, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1, fontchars_array, (glyphCount <= INT_MAX) ? (int) ((zend_long) glyphCount) : -1);
    zend_object *result = php_raylib_font_new_ex(php_raylib_font_ce, NULL);
    php_raylib_font_object *phpResult = php_raylib_font_fetch_object(result);
    Font *fontData = php_raylib_font_fetch_data(phpResult);
    // Dereference fontData for assignment back to object
    *fontData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if a font is ready
// RLAPI bool IsFontReady(Font font);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsFontReady, 0, 0, 1)
    ZEND_ARG_INFO(0, font)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsFontReady)
{
    zval *font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(font)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    RETURN_BOOL(IsFontReady(*php_raylib_font_fetch_data(phpFont)));
}

// Unload font chars info data (RAM)
// RLAPI void UnloadFontData(GlyphInfo* chars, int glyphCount);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadFontData, 0, 0, 2)
    ZEND_ARG_INFO(0, chars)
    ZEND_ARG_INFO(0, glyphCount)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadFontData)
{
    zval *chars;
    zend_long glyphCount;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(chars)
        Z_PARAM_LONG(glyphCount)
    ZEND_PARSE_PARAMETERS_END();

    zval *chars_element;
    int chars_index;
    HashTable *chars_hash = Z_ARRVAL_P(chars);
    SEPARATE_ARRAY(chars);
    int chars_count = zend_hash_num_elements(chars_hash);
    GlyphInfo* chars_array = safe_emalloc(sizeof(GlyphInfo*), chars_count, 0);
    ZEND_HASH_FOREACH_VAL(chars_hash, chars_element) {
        ZVAL_DEREF(chars_element);
        if ((Z_TYPE_P(chars_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(chars_element), php_raylib_glyphinfo_ce))) {
            php_raylib_glyphinfo_object *glyphinfo_obj =  Z_GLYPHINFO_OBJ_P(chars_element);
            chars_array[chars_index] = *php_raylib_glyphinfo_fetch_data(glyphinfo_obj);
        }

        chars_index++;
    } ZEND_HASH_FOREACH_END();

    UnloadFontData(chars_array, (glyphCount <= INT_MAX) ? (int) ((zend_long) glyphCount) : -1);

}

// Unload font from GPU memory (VRAM)
// RLAPI void UnloadFont(Font font);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadFont, 0, 0, 1)
    ZEND_ARG_INFO(0, font)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadFont)
{
    zval *font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(font)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    UnloadFont(*php_raylib_font_fetch_data(phpFont));

}

// Export font as code file, returns true on success
// RLAPI bool ExportFontAsCode(Font font, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportFontAsCode, 0, 0, 2)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportFontAsCode)
{
    zval *font;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    RETURN_BOOL(ExportFontAsCode(*php_raylib_font_fetch_data(phpFont), fileName->val));
}

// Draw current FPS
// RLAPI void DrawFPS(int posX, int posY);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawFPS, 0, 0, 2)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawFPS)
{
    zend_long posX;
    zend_long posY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
    ZEND_PARSE_PARAMETERS_END();


    DrawFPS((posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1);

}

// Draw text (using default font)
// RLAPI void DrawText(const char * text, int posX, int posY, int fontSize, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawText, 0, 0, 5)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, posX)
    ZEND_ARG_INFO(0, posY)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawText)
{
    zend_string *text;
    zend_long posX;
    zend_long posY;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(posX)
        Z_PARAM_LONG(posY)
        Z_PARAM_LONG(fontSize)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawText(text->val, (posX <= INT_MAX) ? (int) ((zend_long) posX) : -1, (posY <= INT_MAX) ? (int) ((zend_long) posY) : -1, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw text using font and additional parameters
// RLAPI void DrawTextEx(Font font, const char * text, Vector2 position, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextEx, 0, 0, 6)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextEx)
{
    zval *font;
    zend_string *text;
    zval *position;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextEx(*php_raylib_font_fetch_data(phpFont), text->val, *php_raylib_vector2_fetch_data(phpPosition), (float) fontSize, (float) spacing, *php_raylib_color_fetch_data(phpTint));

}

// Draw text using Font and pro parameters (rotation)
// RLAPI void DrawTextPro(Font font, const char * text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextPro, 0, 0, 8)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextPro)
{
    zval *font;
    zend_string *text;
    zval *position;
    zval *origin;
    double rotation;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(8, 8)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextPro(*php_raylib_font_fetch_data(phpFont), text->val, *php_raylib_vector2_fetch_data(phpPosition), *php_raylib_vector2_fetch_data(phpOrigin), (float) rotation, (float) fontSize, (float) spacing, *php_raylib_color_fetch_data(phpTint));

}

// Draw one character (codepoint)
// RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextCodepoint, 0, 0, 5)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, codepoint)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextCodepoint)
{
    zval *font;
    zend_long codepoint;
    zval *position;
    double fontSize;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(font)
        Z_PARAM_LONG(codepoint)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextCodepoint(*php_raylib_font_fetch_data(phpFont), (codepoint <= INT_MAX) ? (int) ((zend_long) codepoint) : -1, *php_raylib_vector2_fetch_data(phpPosition), (float) fontSize, *php_raylib_color_fetch_data(phpTint));

}

// Draw multiple character (codepoint)
// RLAPI void DrawTextCodepoints(Font font, const int * codepoints, int count, Vector2 position, float fontSize, float spacing, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTextCodepoints, 0, 0, 7)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, codepoints)
    ZEND_ARG_INFO(0, count)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTextCodepoints)
{
    zval *font;
    zval *codepoints;
    zend_long count;
    zval *position;
    double fontSize;
    double spacing;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_ZVAL(font)
        Z_PARAM_ARRAY(codepoints)
        Z_PARAM_LONG(count)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);
    zval *codepoints_element;
    int codepoints_index;
    HashTable *codepoints_hash = Z_ARRVAL_P(codepoints);
    SEPARATE_ARRAY(codepoints);
    int codepoints_count = zend_hash_num_elements(codepoints_hash);
    int * codepoints_array = safe_emalloc(sizeof(int *), codepoints_count, 0);
    ZEND_HASH_FOREACH_VAL(codepoints_hash, codepoints_element) {
        ZVAL_DEREF(codepoints_element);
        if (Z_TYPE_P(codepoints_element) == IS_LONG) {
            codepoints_array[codepoints_index] = (const int) Z_LVAL_P(codepoints_element);
        }

        codepoints_index++;
    } ZEND_HASH_FOREACH_END();
    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawTextCodepoints(*php_raylib_font_fetch_data(phpFont), codepoints_array, (count <= INT_MAX) ? (int) ((zend_long) count) : -1, *php_raylib_vector2_fetch_data(phpPosition), (float) fontSize, (float) spacing, *php_raylib_color_fetch_data(phpTint));

}

// Measure string width for default font
// RLAPI int MeasureText(const char * text, int fontSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_MeasureText, 0, 0, 2)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(MeasureText)
{
    zend_string *text;
    zend_long fontSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text)
        Z_PARAM_LONG(fontSize)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(MeasureText(text->val, (fontSize <= INT_MAX) ? (int) ((zend_long) fontSize) : -1));
}

// Measure string size for Font
// RLAPI Vector2 MeasureTextEx(Font font, const char * text, float fontSize, float spacing);
ZEND_BEGIN_ARG_INFO_EX(arginfo_MeasureTextEx, 0, 0, 4)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, fontSize)
    ZEND_ARG_INFO(0, spacing)
ZEND_END_ARG_INFO()
PHP_FUNCTION(MeasureTextEx)
{
    zval *font;
    zend_string *text;
    double fontSize;
    double spacing;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(font)
        Z_PARAM_STR(text)
        Z_PARAM_DOUBLE(fontSize)
        Z_PARAM_DOUBLE(spacing)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    Vector2 originalResult = MeasureTextEx(*php_raylib_font_fetch_data(phpFont), text->val, (float) fontSize, (float) spacing);
    zend_object *result = php_raylib_vector2_new_ex(php_raylib_vector2_ce, NULL);
    php_raylib_vector2_object *phpResult = php_raylib_vector2_fetch_object(result);
    Vector2 *vector2Data = php_raylib_vector2_fetch_data(phpResult);
    // Dereference vector2Data for assignment back to object
    *vector2Data = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
// RLAPI int GetGlyphIndex(Font font, int codepoint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGlyphIndex, 0, 0, 2)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, codepoint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGlyphIndex)
{
    zval *font;
    zend_long codepoint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(font)
        Z_PARAM_LONG(codepoint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    RETURN_LONG(GetGlyphIndex(*php_raylib_font_fetch_data(phpFont), (codepoint <= INT_MAX) ? (int) ((zend_long) codepoint) : -1));
}

// Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
// RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGlyphInfo, 0, 0, 2)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, codepoint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGlyphInfo)
{
    zval *font;
    zend_long codepoint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(font)
        Z_PARAM_LONG(codepoint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    GlyphInfo originalResult = GetGlyphInfo(*php_raylib_font_fetch_data(phpFont), (codepoint <= INT_MAX) ? (int) ((zend_long) codepoint) : -1);
    zend_object *result = php_raylib_glyphinfo_new_ex(php_raylib_glyphinfo_ce, NULL);
    php_raylib_glyphinfo_object *phpResult = php_raylib_glyphinfo_fetch_object(result);
    GlyphInfo *glyphinfoData = php_raylib_glyphinfo_fetch_data(phpResult);
    // Dereference glyphinfoData for assignment back to object
    *glyphinfoData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
// RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetGlyphAtlasRec, 0, 0, 2)
    ZEND_ARG_INFO(0, font)
    ZEND_ARG_INFO(0, codepoint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetGlyphAtlasRec)
{
    zval *font;
    zend_long codepoint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(font)
        Z_PARAM_LONG(codepoint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_font_object *phpFont = Z_FONT_OBJ_P(font);

    Rectangle originalResult = GetGlyphAtlasRec(*php_raylib_font_fetch_data(phpFont), (codepoint <= INT_MAX) ? (int) ((zend_long) codepoint) : -1);
    zend_object *result = php_raylib_rectangle_new_ex(php_raylib_rectangle_ce, NULL);
    php_raylib_rectangle_object *phpResult = php_raylib_rectangle_fetch_object(result);
    Rectangle *rectangleData = php_raylib_rectangle_fetch_data(phpResult);
    // Dereference rectangleData for assignment back to object
    *rectangleData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Unload UTF-8 text encoded from codepoints array
// RLAPI void UnloadUTF8(char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadUTF8, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadUTF8)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    UnloadUTF8(text->val);

}

// Unload codepoints data from memory
// RLAPI void UnloadCodepoints(int * codepoints);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadCodepoints, 0, 0, 1)
    ZEND_ARG_INFO(0, codepoints)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadCodepoints)
{
    zval *codepoints;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(codepoints)
    ZEND_PARSE_PARAMETERS_END();

    zval *codepoints_element;
    int codepoints_index;
    HashTable *codepoints_hash = Z_ARRVAL_P(codepoints);
    SEPARATE_ARRAY(codepoints);
    int codepoints_count = zend_hash_num_elements(codepoints_hash);
    int * codepoints_array = safe_emalloc(sizeof(int *), codepoints_count, 0);
    ZEND_HASH_FOREACH_VAL(codepoints_hash, codepoints_element) {
        ZVAL_DEREF(codepoints_element);
        if (Z_TYPE_P(codepoints_element) == IS_LONG) {
            codepoints_array[codepoints_index] = (int) Z_LVAL_P(codepoints_element);
        }

        codepoints_index++;
    } ZEND_HASH_FOREACH_END();

    UnloadCodepoints(codepoints_array);

}

// Get total number of codepoints in a UTF-8 encoded string
// RLAPI int GetCodepointCount(const char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCodepointCount, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCodepointCount)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(GetCodepointCount(text->val));
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepoint(const char * text, int * codepointSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCodepoint, 0, 0, 2)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, codepointSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCodepoint)
{
    zend_string *text;
    zval *codepointSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text)
        Z_PARAM_ARRAY(codepointSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *codepointsize_element;
    int codepointsize_index;
    HashTable *codepointsize_hash = Z_ARRVAL_P(codepointSize);
    SEPARATE_ARRAY(codepointSize);
    int codepointsize_count = zend_hash_num_elements(codepointsize_hash);
    int * codepointsize_array = safe_emalloc(sizeof(int *), codepointsize_count, 0);
    ZEND_HASH_FOREACH_VAL(codepointsize_hash, codepointsize_element) {
        ZVAL_DEREF(codepointsize_element);
        if (Z_TYPE_P(codepointsize_element) == IS_LONG) {
            codepointsize_array[codepointsize_index] = (int) Z_LVAL_P(codepointsize_element);
        }

        codepointsize_index++;
    } ZEND_HASH_FOREACH_END();

    RETURN_LONG(GetCodepoint(text->val, codepointsize_array));
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointNext(const char * text, int * codepointSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCodepointNext, 0, 0, 2)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, codepointSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCodepointNext)
{
    zend_string *text;
    zval *codepointSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text)
        Z_PARAM_ARRAY(codepointSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *codepointsize_element;
    int codepointsize_index;
    HashTable *codepointsize_hash = Z_ARRVAL_P(codepointSize);
    SEPARATE_ARRAY(codepointSize);
    int codepointsize_count = zend_hash_num_elements(codepointsize_hash);
    int * codepointsize_array = safe_emalloc(sizeof(int *), codepointsize_count, 0);
    ZEND_HASH_FOREACH_VAL(codepointsize_hash, codepointsize_element) {
        ZVAL_DEREF(codepointsize_element);
        if (Z_TYPE_P(codepointsize_element) == IS_LONG) {
            codepointsize_array[codepointsize_index] = (int) Z_LVAL_P(codepointsize_element);
        }

        codepointsize_index++;
    } ZEND_HASH_FOREACH_END();

    RETURN_LONG(GetCodepointNext(text->val, codepointsize_array));
}

// Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointPrevious(const char * text, int * codepointSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetCodepointPrevious, 0, 0, 2)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, codepointSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetCodepointPrevious)
{
    zend_string *text;
    zval *codepointSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text)
        Z_PARAM_ARRAY(codepointSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *codepointsize_element;
    int codepointsize_index;
    HashTable *codepointsize_hash = Z_ARRVAL_P(codepointSize);
    SEPARATE_ARRAY(codepointSize);
    int codepointsize_count = zend_hash_num_elements(codepointsize_hash);
    int * codepointsize_array = safe_emalloc(sizeof(int *), codepointsize_count, 0);
    ZEND_HASH_FOREACH_VAL(codepointsize_hash, codepointsize_element) {
        ZVAL_DEREF(codepointsize_element);
        if (Z_TYPE_P(codepointsize_element) == IS_LONG) {
            codepointsize_array[codepointsize_index] = (int) Z_LVAL_P(codepointsize_element);
        }

        codepointsize_index++;
    } ZEND_HASH_FOREACH_END();

    RETURN_LONG(GetCodepointPrevious(text->val, codepointsize_array));
}

// Copy one string to another, returns bytes copied
// RLAPI int TextCopy(char * dst, const char * src);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextCopy, 0, 0, 2)
    ZEND_ARG_INFO(0, dst)
    ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextCopy)
{
    zend_string *dst;
    zend_string *src;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(dst)
        Z_PARAM_STR(src)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(TextCopy(dst->val, src->val));
}

// Check if two text string are equal
// RLAPI bool TextIsEqual(const char * text1, const char * text2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextIsEqual, 0, 0, 2)
    ZEND_ARG_INFO(0, text1)
    ZEND_ARG_INFO(0, text2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextIsEqual)
{
    zend_string *text1;
    zend_string *text2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text1)
        Z_PARAM_STR(text2)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_BOOL(TextIsEqual(text1->val, text2->val));
}

// Get text length, checks for '\0' ending
// RLAPI unsigned int TextLength(const char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextLength, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextLength)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(TextLength(text->val));
}

// Append text at specific position and move cursor!
// RLAPI void TextAppend(char * text, const char * append, int * position);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextAppend, 0, 0, 3)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, append)
    ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextAppend)
{
    zend_string *text;
    zend_string *append;
    zval *position;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(text)
        Z_PARAM_STR(append)
        Z_PARAM_ARRAY(position)
    ZEND_PARSE_PARAMETERS_END();

    zval *position_element;
    int position_index;
    HashTable *position_hash = Z_ARRVAL_P(position);
    SEPARATE_ARRAY(position);
    int position_count = zend_hash_num_elements(position_hash);
    int * position_array = safe_emalloc(sizeof(int *), position_count, 0);
    ZEND_HASH_FOREACH_VAL(position_hash, position_element) {
        ZVAL_DEREF(position_element);
        if (Z_TYPE_P(position_element) == IS_LONG) {
            position_array[position_index] = (int) Z_LVAL_P(position_element);
        }

        position_index++;
    } ZEND_HASH_FOREACH_END();

    TextAppend(text->val, append->val, position_array);

}

// Find first text occurrence within a string
// RLAPI int TextFindIndex(const char * text, const char * find);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextFindIndex, 0, 0, 2)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, find)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextFindIndex)
{
    zend_string *text;
    zend_string *find;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(text)
        Z_PARAM_STR(find)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(TextFindIndex(text->val, find->val));
}

// Get integer value from text (negative values not supported)
// RLAPI int TextToInteger(const char * text);
ZEND_BEGIN_ARG_INFO_EX(arginfo_TextToInteger, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
PHP_FUNCTION(TextToInteger)
{
    zend_string *text;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(text)
    ZEND_PARSE_PARAMETERS_END();


    RETURN_LONG(TextToInteger(text->val));
}

// Draw a line in 3D world space
// RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawLine3D, 0, 0, 3)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawLine3D)
{
    zval *startPos;
    zval *endPos;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpStartPos = Z_VECTOR3_OBJ_P(startPos);
    php_raylib_vector3_object *phpEndPos = Z_VECTOR3_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawLine3D(*php_raylib_vector3_fetch_data(phpStartPos), *php_raylib_vector3_fetch_data(phpEndPos), *php_raylib_color_fetch_data(phpColor));

}

// Draw a point in 3D space, actually a small line
// RLAPI void DrawPoint3D(Vector3 position, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPoint3D, 0, 0, 2)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPoint3D)
{
    zval *position;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPoint3D(*php_raylib_vector3_fetch_data(phpPosition), *php_raylib_color_fetch_data(phpColor));

}

// Draw a circle in 3D world space
// RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCircle3D, 0, 0, 5)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rotationAxis)
    ZEND_ARG_INFO(0, rotationAngle)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCircle3D)
{
    zval *center;
    double radius;
    zval *rotationAxis;
    double rotationAngle;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(rotationAxis)
        Z_PARAM_DOUBLE(rotationAngle)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenter = Z_VECTOR3_OBJ_P(center);
    php_raylib_vector3_object *phpRotationAxis = Z_VECTOR3_OBJ_P(rotationAxis);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCircle3D(*php_raylib_vector3_fetch_data(phpCenter), (float) radius, *php_raylib_vector3_fetch_data(phpRotationAxis), (float) rotationAngle, *php_raylib_color_fetch_data(phpColor));

}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
// RLAPI void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangle3D, 0, 0, 4)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
    ZEND_ARG_INFO(0, v3)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangle3D)
{
    zval *v1;
    zval *v2;
    zval *v3;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(v1)
        Z_PARAM_ZVAL(v2)
        Z_PARAM_ZVAL(v3)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpV1 = Z_VECTOR3_OBJ_P(v1);
    php_raylib_vector3_object *phpV2 = Z_VECTOR3_OBJ_P(v2);
    php_raylib_vector3_object *phpV3 = Z_VECTOR3_OBJ_P(v3);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangle3D(*php_raylib_vector3_fetch_data(phpV1), *php_raylib_vector3_fetch_data(phpV2), *php_raylib_vector3_fetch_data(phpV3), *php_raylib_color_fetch_data(phpColor));

}

// Draw a triangle strip defined by points
// RLAPI void DrawTriangleStrip3D(Vector3* points, int pointCount, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawTriangleStrip3D, 0, 0, 3)
    ZEND_ARG_INFO(0, points)
    ZEND_ARG_INFO(0, pointCount)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawTriangleStrip3D)
{
    zval *points;
    zend_long pointCount;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ARRAY(points)
        Z_PARAM_LONG(pointCount)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    zval *points_element;
    int points_index;
    HashTable *points_hash = Z_ARRVAL_P(points);
    SEPARATE_ARRAY(points);
    int points_count = zend_hash_num_elements(points_hash);
    Vector3* points_array = safe_emalloc(sizeof(Vector3*), points_count, 0);
    ZEND_HASH_FOREACH_VAL(points_hash, points_element) {
        ZVAL_DEREF(points_element);
        if ((Z_TYPE_P(points_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(points_element), php_raylib_vector3_ce))) {
            php_raylib_vector3_object *vector3_obj =  Z_VECTOR3_OBJ_P(points_element);
            points_array[points_index] = *php_raylib_vector3_fetch_data(vector3_obj);
        }

        points_index++;
    } ZEND_HASH_FOREACH_END();
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawTriangleStrip3D(points_array, (pointCount <= INT_MAX) ? (int) ((zend_long) pointCount) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw cube
// RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCube, 0, 0, 5)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, length)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCube)
{
    zval *position;
    double width;
    double height;
    double length;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_DOUBLE(length)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCube(*php_raylib_vector3_fetch_data(phpPosition), (float) width, (float) height, (float) length, *php_raylib_color_fetch_data(phpColor));

}

// Draw cube (Vector version)
// RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCubeV, 0, 0, 3)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCubeV)
{
    zval *position;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpSize = Z_VECTOR3_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCubeV(*php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector3_fetch_data(phpSize), *php_raylib_color_fetch_data(phpColor));

}

// Draw cube wires
// RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCubeWires, 0, 0, 5)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, length)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCubeWires)
{
    zval *position;
    double width;
    double height;
    double length;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_DOUBLE(length)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCubeWires(*php_raylib_vector3_fetch_data(phpPosition), (float) width, (float) height, (float) length, *php_raylib_color_fetch_data(phpColor));

}

// Draw cube wires (Vector version)
// RLAPI void DrawCubeWiresV(Vector3 position, Vector3 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCubeWiresV, 0, 0, 3)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCubeWiresV)
{
    zval *position;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpSize = Z_VECTOR3_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCubeWiresV(*php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector3_fetch_data(phpSize), *php_raylib_color_fetch_data(phpColor));

}

// Draw sphere
// RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawSphere, 0, 0, 3)
    ZEND_ARG_INFO(0, centerPos)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawSphere)
{
    zval *centerPos;
    double radius;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(centerPos)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenterPos = Z_VECTOR3_OBJ_P(centerPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawSphere(*php_raylib_vector3_fetch_data(phpCenterPos), (float) radius, *php_raylib_color_fetch_data(phpColor));

}

// Draw sphere with extended parameters
// RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawSphereEx, 0, 0, 5)
    ZEND_ARG_INFO(0, centerPos)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawSphereEx)
{
    zval *centerPos;
    double radius;
    zend_long rings;
    zend_long slices;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(centerPos)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(rings)
        Z_PARAM_LONG(slices)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenterPos = Z_VECTOR3_OBJ_P(centerPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawSphereEx(*php_raylib_vector3_fetch_data(phpCenterPos), (float) radius, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw sphere wires
// RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawSphereWires, 0, 0, 5)
    ZEND_ARG_INFO(0, centerPos)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawSphereWires)
{
    zval *centerPos;
    double radius;
    zend_long rings;
    zend_long slices;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(centerPos)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(rings)
        Z_PARAM_LONG(slices)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenterPos = Z_VECTOR3_OBJ_P(centerPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawSphereWires(*php_raylib_vector3_fetch_data(phpCenterPos), (float) radius, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a cylinder/cone
// RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCylinder, 0, 0, 6)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, radiusTop)
    ZEND_ARG_INFO(0, radiusBottom)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCylinder)
{
    zval *position;
    double radiusTop;
    double radiusBottom;
    double height;
    zend_long slices;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(radiusTop)
        Z_PARAM_DOUBLE(radiusBottom)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_LONG(slices)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCylinder(*php_raylib_vector3_fetch_data(phpPosition), (float) radiusTop, (float) radiusBottom, (float) height, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a cylinder with base at startPos and top at endPos
// RLAPI void DrawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCylinderEx, 0, 0, 6)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, startRadius)
    ZEND_ARG_INFO(0, endRadius)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCylinderEx)
{
    zval *startPos;
    zval *endPos;
    double startRadius;
    double endRadius;
    zend_long sides;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(startRadius)
        Z_PARAM_DOUBLE(endRadius)
        Z_PARAM_LONG(sides)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpStartPos = Z_VECTOR3_OBJ_P(startPos);
    php_raylib_vector3_object *phpEndPos = Z_VECTOR3_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCylinderEx(*php_raylib_vector3_fetch_data(phpStartPos), *php_raylib_vector3_fetch_data(phpEndPos), (float) startRadius, (float) endRadius, (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a cylinder/cone wires
// RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCylinderWires, 0, 0, 6)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, radiusTop)
    ZEND_ARG_INFO(0, radiusBottom)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCylinderWires)
{
    zval *position;
    double radiusTop;
    double radiusBottom;
    double height;
    zend_long slices;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(radiusTop)
        Z_PARAM_DOUBLE(radiusBottom)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_LONG(slices)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCylinderWires(*php_raylib_vector3_fetch_data(phpPosition), (float) radiusTop, (float) radiusBottom, (float) height, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a cylinder wires with base at startPos and top at endPos
// RLAPI void DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCylinderWiresEx, 0, 0, 6)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, startRadius)
    ZEND_ARG_INFO(0, endRadius)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCylinderWiresEx)
{
    zval *startPos;
    zval *endPos;
    double startRadius;
    double endRadius;
    zend_long sides;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(startRadius)
        Z_PARAM_DOUBLE(endRadius)
        Z_PARAM_LONG(sides)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpStartPos = Z_VECTOR3_OBJ_P(startPos);
    php_raylib_vector3_object *phpEndPos = Z_VECTOR3_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCylinderWiresEx(*php_raylib_vector3_fetch_data(phpStartPos), *php_raylib_vector3_fetch_data(phpEndPos), (float) startRadius, (float) endRadius, (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a capsule with the center of its sphere caps at startPos and endPos
// RLAPI void DrawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCapsule, 0, 0, 6)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCapsule)
{
    zval *startPos;
    zval *endPos;
    double radius;
    zend_long slices;
    zend_long rings;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(slices)
        Z_PARAM_LONG(rings)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpStartPos = Z_VECTOR3_OBJ_P(startPos);
    php_raylib_vector3_object *phpEndPos = Z_VECTOR3_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCapsule(*php_raylib_vector3_fetch_data(phpStartPos), *php_raylib_vector3_fetch_data(phpEndPos), (float) radius, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw capsule wireframe with the center of its sphere caps at startPos and endPos
// RLAPI void DrawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawCapsuleWires, 0, 0, 6)
    ZEND_ARG_INFO(0, startPos)
    ZEND_ARG_INFO(0, endPos)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawCapsuleWires)
{
    zval *startPos;
    zval *endPos;
    double radius;
    zend_long slices;
    zend_long rings;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(startPos)
        Z_PARAM_ZVAL(endPos)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(slices)
        Z_PARAM_LONG(rings)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpStartPos = Z_VECTOR3_OBJ_P(startPos);
    php_raylib_vector3_object *phpEndPos = Z_VECTOR3_OBJ_P(endPos);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawCapsuleWires(*php_raylib_vector3_fetch_data(phpStartPos), *php_raylib_vector3_fetch_data(phpEndPos), (float) radius, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, *php_raylib_color_fetch_data(phpColor));

}

// Draw a plane XZ
// RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawPlane, 0, 0, 3)
    ZEND_ARG_INFO(0, centerPos)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawPlane)
{
    zval *centerPos;
    zval *size;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(centerPos)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenterPos = Z_VECTOR3_OBJ_P(centerPos);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawPlane(*php_raylib_vector3_fetch_data(phpCenterPos), *php_raylib_vector2_fetch_data(phpSize), *php_raylib_color_fetch_data(phpColor));

}

// Draw a ray line
// RLAPI void DrawRay(Ray ray, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawRay, 0, 0, 2)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawRay)
{
    zval *ray;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawRay(*php_raylib_ray_fetch_data(phpRay), *php_raylib_color_fetch_data(phpColor));

}

// Draw a grid (centered at (0, 0, 0))
// RLAPI void DrawGrid(int slices, float spacing);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawGrid, 0, 0, 2)
    ZEND_ARG_INFO(0, slices)
    ZEND_ARG_INFO(0, spacing)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawGrid)
{
    zend_long slices;
    double spacing;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(slices)
        Z_PARAM_DOUBLE(spacing)
    ZEND_PARSE_PARAMETERS_END();


    DrawGrid((slices <= INT_MAX) ? (int) ((zend_long) slices) : -1, (float) spacing);

}

// Load model from files (meshes and materials)
// RLAPI Model LoadModel(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadModel, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadModel)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Model originalResult = LoadModel(fileName->val);
    zend_object *result = php_raylib_model_new_ex(php_raylib_model_ce, NULL);
    php_raylib_model_object *phpResult = php_raylib_model_fetch_object(result);
    Model *modelData = php_raylib_model_fetch_data(phpResult);
    // Dereference modelData for assignment back to object
    *modelData = originalResult;


    for (int i = 0; i < php_raylib_model_fetch_data(phpResult)->meshCount; i++) {
        // Create PHP Object holder of this data
        zend_object *meshesResult = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);

        // Fetch the data inside the PHP Object
        php_raylib_mesh_object *pMeshObject = php_raylib_mesh_fetch_object(meshesResult);
        Mesh *meshElement = php_raylib_mesh_fetch_data(pMeshObject);

        // Link this as a pointer, rather than copying data between each other
        pMeshObject->mesh->type = RL_MESH_IS_POINTER;
        pMeshObject->mesh->data.p = &php_raylib_model_fetch_data(phpResult)->meshes[i];

        // Go through each sub-object and assign values (references)
        // Push element to PHP array which should just be an object that is also a data pointer,
        // if this is changed should update original data?
        add_next_index_object(&phpResult->meshes, meshesResult);
    }

    for (int i = 0; i < php_raylib_model_fetch_data(phpResult)->materialCount; i++) {
        // Create PHP Object holder of this data
        zend_object *materialsResult = php_raylib_material_new_ex(php_raylib_material_ce, NULL);

        // Fetch the data inside the PHP Object
        php_raylib_material_object *pMaterialObject = php_raylib_material_fetch_object(materialsResult);
        Material *materialElement = php_raylib_material_fetch_data(pMaterialObject);

        // Link this as a pointer, rather than copying data between each other
        pMaterialObject->material->type = RL_MATERIAL_IS_POINTER;
        pMaterialObject->material->data.p = &php_raylib_model_fetch_data(phpResult)->materials[i];

        // Go through each sub-object and assign values (references)
        php_raylib_shader_object *phpMaterialShaderObject = Z_SHADER_OBJ_P(&pMaterialObject->shader);
        phpMaterialShaderObject->shader->type = RL_SHADER_IS_POINTER;
        phpMaterialShaderObject->shader->data.p = &pMaterialObject->material->data.p->shader;

        for (int n = 0; n < 12; n++) {
            MaterialMap *materialMap = &pMaterialObject->material->data.p->maps[n];

            // Create PHP Object holder of this data
            zend_object *materialMapResult = php_raylib_materialmap_new_ex(php_raylib_materialmap_ce, NULL);
            php_raylib_materialmap_object *pMaterialMaterialMapObject = php_raylib_materialmap_fetch_object(materialMapResult);

            pMaterialMaterialMapObject->materialmap->type = RL_MATERIALMAP_IS_POINTER;
            pMaterialMaterialMapObject->materialmap->data.p = materialMap;

            /*
            * Need to also populate the following sub SUB objects
            * zval texture;
            * zval color;
            */

            add_next_index_object(&pMaterialObject->maps, materialMapResult);
        }

        // Push element to PHP array which should just be an object that is also a data pointer,
        // if this is changed should update original data?
        add_next_index_object(&phpResult->materials, materialsResult);
    }

    for (int i = 0; i < php_raylib_model_fetch_data(phpResult)->boneCount; i++) {
        // Create PHP Object holder of this data
        zend_object *bonesResult = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, NULL);

        // Fetch the data inside the PHP Object
        php_raylib_boneinfo_object *pBoneinfoObject = php_raylib_boneinfo_fetch_object(bonesResult);
        BoneInfo *boneinfoElement = php_raylib_boneinfo_fetch_data(pBoneinfoObject);

        // Link this as a pointer, rather than copying data between each other
        pBoneinfoObject->boneinfo->type = RL_BONEINFO_IS_POINTER;
        pBoneinfoObject->boneinfo->data.p = &php_raylib_model_fetch_data(phpResult)->bones[i];

        // Go through each sub-object and assign values (references)
        // Push element to PHP array which should just be an object that is also a data pointer,
        // if this is changed should update original data?
        add_next_index_object(&phpResult->bones, bonesResult);
    }

    for (int i = 0; i < php_raylib_model_fetch_data(phpResult)->boneCount; i++) {
        // Create PHP Object holder of this data
        zend_object *bindPoseResult = php_raylib_transform_new_ex(php_raylib_transform_ce, NULL);

        // Fetch the data inside the PHP Object
        php_raylib_transform_object *pTransformObject = php_raylib_transform_fetch_object(bindPoseResult);
        Transform *transformElement = php_raylib_transform_fetch_data(pTransformObject);

        // Link this as a pointer, rather than copying data between each other
        pTransformObject->transform->type = RL_TRANSFORM_IS_POINTER;
        pTransformObject->transform->data.p = &php_raylib_model_fetch_data(phpResult)->bindPose[i];

        // Go through each sub-object and assign values (references)
        php_raylib_vector3_object *phpTransformVector3Object = Z_VECTOR3_OBJ_P(&pTransformObject->translation);
        phpTransformVector3Object->vector3->type = RL_VECTOR3_IS_POINTER;
        phpTransformVector3Object->vector3->data.p = &pTransformObject->transform->data.p->translation;

        php_raylib_vector4_object *phpTransformVector4Object = Z_VECTOR4_OBJ_P(&pTransformObject->rotation);
        phpTransformVector4Object->vector4->type = RL_VECTOR4_IS_POINTER;
        phpTransformVector4Object->vector4->data.p = &pTransformObject->transform->data.p->rotation;

        php_raylib_vector3_object *phpTransformVector31Object = Z_VECTOR3_OBJ_P(&pTransformObject->scale);
        phpTransformVector31Object->vector3->type = RL_VECTOR3_IS_POINTER;
        phpTransformVector31Object->vector3->data.p = &pTransformObject->transform->data.p->scale;

        // Push element to PHP array which should just be an object that is also a data pointer,
        // if this is changed should update original data?
        add_next_index_object(&phpResult->bindpose, bindPoseResult);
    }


    RETURN_OBJ(&phpResult->std);
}

// Load model from generated mesh (default material)
// RLAPI Model LoadModelFromMesh(Mesh mesh);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadModelFromMesh, 0, 0, 1)
    ZEND_ARG_INFO(0, mesh)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadModelFromMesh)
{
    zval *mesh;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(mesh)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    Model originalResult = LoadModelFromMesh(*php_raylib_mesh_fetch_data(phpMesh));
    zend_object *result = php_raylib_model_new_ex(php_raylib_model_ce, NULL);
    php_raylib_model_object *phpResult = php_raylib_model_fetch_object(result);
    Model *modelData = php_raylib_model_fetch_data(phpResult);
    // Dereference modelData for assignment back to object
    *modelData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if a model is ready
// RLAPI bool IsModelReady(Model model);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsModelReady, 0, 0, 1)
    ZEND_ARG_INFO(0, model)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsModelReady)
{
    zval *model;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(model)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);

    RETURN_BOOL(IsModelReady(*php_raylib_model_fetch_data(phpModel)));
}

// Unload model (including meshes) from memory (RAM and/or VRAM)
// RLAPI void UnloadModel(Model model);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadModel, 0, 0, 1)
    ZEND_ARG_INFO(0, model)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadModel)
{
    zval *model;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(model)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);

    UnloadModel(*php_raylib_model_fetch_data(phpModel));

}

// Compute model bounding box limits (considers all meshes)
// RLAPI BoundingBox GetModelBoundingBox(Model model);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetModelBoundingBox, 0, 0, 1)
    ZEND_ARG_INFO(0, model)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetModelBoundingBox)
{
    zval *model;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(model)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);

    BoundingBox originalResult = GetModelBoundingBox(*php_raylib_model_fetch_data(phpModel));
    zend_object *result = php_raylib_boundingbox_new_ex(php_raylib_boundingbox_ce, NULL);
    php_raylib_boundingbox_object *phpResult = php_raylib_boundingbox_fetch_object(result);
    BoundingBox *boundingboxData = php_raylib_boundingbox_fetch_data(phpResult);
    // Dereference boundingboxData for assignment back to object
    *boundingboxData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Draw a model (with texture if set)
// RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawModel, 0, 0, 4)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawModel)
{
    zval *model;
    zval *position;
    double scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawModel(*php_raylib_model_fetch_data(phpModel), *php_raylib_vector3_fetch_data(phpPosition), (float) scale, *php_raylib_color_fetch_data(phpTint));

}

// Draw a model with extended parameters
// RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawModelEx, 0, 0, 6)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, rotationAxis)
    ZEND_ARG_INFO(0, rotationAngle)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawModelEx)
{
    zval *model;
    zval *position;
    zval *rotationAxis;
    double rotationAngle;
    zval *scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(rotationAxis)
        Z_PARAM_DOUBLE(rotationAngle)
        Z_PARAM_ZVAL(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpRotationAxis = Z_VECTOR3_OBJ_P(rotationAxis);
    php_raylib_vector3_object *phpScale = Z_VECTOR3_OBJ_P(scale);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawModelEx(*php_raylib_model_fetch_data(phpModel), *php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector3_fetch_data(phpRotationAxis), (float) rotationAngle, *php_raylib_vector3_fetch_data(phpScale), *php_raylib_color_fetch_data(phpTint));

}

// Draw a model wires (with texture if set)
// RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawModelWires, 0, 0, 4)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawModelWires)
{
    zval *model;
    zval *position;
    double scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawModelWires(*php_raylib_model_fetch_data(phpModel), *php_raylib_vector3_fetch_data(phpPosition), (float) scale, *php_raylib_color_fetch_data(phpTint));

}

// Draw a model wires (with texture if set) with extended parameters
// RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawModelWiresEx, 0, 0, 6)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, rotationAxis)
    ZEND_ARG_INFO(0, rotationAngle)
    ZEND_ARG_INFO(0, scale)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawModelWiresEx)
{
    zval *model;
    zval *position;
    zval *rotationAxis;
    double rotationAngle;
    zval *scale;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(rotationAxis)
        Z_PARAM_DOUBLE(rotationAngle)
        Z_PARAM_ZVAL(scale)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpRotationAxis = Z_VECTOR3_OBJ_P(rotationAxis);
    php_raylib_vector3_object *phpScale = Z_VECTOR3_OBJ_P(scale);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawModelWiresEx(*php_raylib_model_fetch_data(phpModel), *php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector3_fetch_data(phpRotationAxis), (float) rotationAngle, *php_raylib_vector3_fetch_data(phpScale), *php_raylib_color_fetch_data(phpTint));

}

// Draw bounding box (wires)
// RLAPI void DrawBoundingBox(BoundingBox box, Color color);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawBoundingBox, 0, 0, 2)
    ZEND_ARG_INFO(0, box)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawBoundingBox)
{
    zval *box;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(box)
        Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_boundingbox_object *phpBox = Z_BOUNDINGBOX_OBJ_P(box);
    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawBoundingBox(*php_raylib_boundingbox_fetch_data(phpBox), *php_raylib_color_fetch_data(phpColor));

}

// Draw a billboard texture
// RLAPI void DrawBillboard(Camera3D camera, Texture texture, Vector3 position, float size, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawBillboard, 0, 0, 5)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawBillboard)
{
    zval *camera;
    zval *texture;
    zval *position;
    double size;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(position)
        Z_PARAM_DOUBLE(size)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawBillboard(*php_raylib_camera3d_fetch_data(phpCamera), *php_raylib_texture_fetch_data(phpTexture), *php_raylib_vector3_fetch_data(phpPosition), (float) size, *php_raylib_color_fetch_data(phpTint));

}

// Draw a billboard texture defined by source
// RLAPI void DrawBillboardRec(Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector2 size, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawBillboardRec, 0, 0, 6)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, source)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawBillboardRec)
{
    zval *camera;
    zval *texture;
    zval *source;
    zval *position;
    zval *size;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(source)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(source);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawBillboardRec(*php_raylib_camera3d_fetch_data(phpCamera), *php_raylib_texture_fetch_data(phpTexture), *php_raylib_rectangle_fetch_data(phpSource), *php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector2_fetch_data(phpSize), *php_raylib_color_fetch_data(phpTint));

}

// Draw a billboard texture defined by source and rotation
// RLAPI void DrawBillboardPro(Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawBillboardPro, 0, 0, 9)
    ZEND_ARG_INFO(0, camera)
    ZEND_ARG_INFO(0, texture)
    ZEND_ARG_INFO(0, source)
    ZEND_ARG_INFO(0, position)
    ZEND_ARG_INFO(0, up)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, origin)
    ZEND_ARG_INFO(0, rotation)
    ZEND_ARG_INFO(0, tint)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawBillboardPro)
{
    zval *camera;
    zval *texture;
    zval *source;
    zval *position;
    zval *up;
    zval *size;
    zval *origin;
    double rotation;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(9, 9)
        Z_PARAM_ZVAL(camera)
        Z_PARAM_ZVAL(texture)
        Z_PARAM_ZVAL(source)
        Z_PARAM_ZVAL(position)
        Z_PARAM_ZVAL(up)
        Z_PARAM_ZVAL(size)
        Z_PARAM_ZVAL(origin)
        Z_PARAM_DOUBLE(rotation)
        Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);
    php_raylib_rectangle_object *phpSource = Z_RECTANGLE_OBJ_P(source);
    php_raylib_vector3_object *phpPosition = Z_VECTOR3_OBJ_P(position);
    php_raylib_vector3_object *phpUp = Z_VECTOR3_OBJ_P(up);
    php_raylib_vector2_object *phpSize = Z_VECTOR2_OBJ_P(size);
    php_raylib_vector2_object *phpOrigin = Z_VECTOR2_OBJ_P(origin);
    php_raylib_color_object *phpTint = Z_COLOR_OBJ_P(tint);

    DrawBillboardPro(*php_raylib_camera3d_fetch_data(phpCamera), *php_raylib_texture_fetch_data(phpTexture), *php_raylib_rectangle_fetch_data(phpSource), *php_raylib_vector3_fetch_data(phpPosition), *php_raylib_vector3_fetch_data(phpUp), *php_raylib_vector2_fetch_data(phpSize), *php_raylib_vector2_fetch_data(phpOrigin), (float) rotation, *php_raylib_color_fetch_data(phpTint));

}

// Upload mesh vertex data in GPU and provide VAO/VBO ids
// RLAPI void UploadMesh(Mesh* mesh, bool dynamic);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UploadMesh, 0, 0, 2)
    ZEND_ARG_INFO(0, mesh)
    ZEND_ARG_INFO(0, dynamic)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UploadMesh)
{
    zval *mesh;
    bool dynamic;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(mesh)
        Z_PARAM_BOOL(dynamic)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    UploadMesh(php_raylib_mesh_fetch_data(phpMesh), dynamic);

}

// Unload mesh data from CPU and GPU
// RLAPI void UnloadMesh(Mesh mesh);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadMesh, 0, 0, 1)
    ZEND_ARG_INFO(0, mesh)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadMesh)
{
    zval *mesh;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(mesh)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    UnloadMesh(*php_raylib_mesh_fetch_data(phpMesh));

}

// Draw a 3d mesh with material and transform
// RLAPI void DrawMesh(Mesh mesh, Material material, Matrix transform);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawMesh, 0, 0, 3)
    ZEND_ARG_INFO(0, mesh)
    ZEND_ARG_INFO(0, material)
    ZEND_ARG_INFO(0, transform)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawMesh)
{
    zval *mesh;
    zval *material;
    zval *transform;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(mesh)
        Z_PARAM_ZVAL(material)
        Z_PARAM_ZVAL(transform)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);
    php_raylib_material_object *phpMaterial = Z_MATERIAL_OBJ_P(material);
    php_raylib_matrix_object *phpTransform = Z_MATRIX_OBJ_P(transform);

    DrawMesh(*php_raylib_mesh_fetch_data(phpMesh), *php_raylib_material_fetch_data(phpMaterial), *php_raylib_matrix_fetch_data(phpTransform));

}

// Draw multiple mesh instances with material and different transforms
// RLAPI void DrawMeshInstanced(Mesh mesh, Material material, Matrix* transforms, int instances);
ZEND_BEGIN_ARG_INFO_EX(arginfo_DrawMeshInstanced, 0, 0, 4)
    ZEND_ARG_INFO(0, mesh)
    ZEND_ARG_INFO(0, material)
    ZEND_ARG_INFO(0, transforms)
    ZEND_ARG_INFO(0, instances)
ZEND_END_ARG_INFO()
PHP_FUNCTION(DrawMeshInstanced)
{
    zval *mesh;
    zval *material;
    zval *transforms;
    zend_long instances;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(mesh)
        Z_PARAM_ZVAL(material)
        Z_PARAM_ZVAL(transforms)
        Z_PARAM_LONG(instances)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);
    php_raylib_material_object *phpMaterial = Z_MATERIAL_OBJ_P(material);
    php_raylib_matrix_object *phpTransforms = Z_MATRIX_OBJ_P(transforms);

    DrawMeshInstanced(*php_raylib_mesh_fetch_data(phpMesh), *php_raylib_material_fetch_data(phpMaterial), php_raylib_matrix_fetch_data(phpTransforms), (instances <= INT_MAX) ? (int) ((zend_long) instances) : -1);

}

// Export mesh data to file, returns true on success
// RLAPI bool ExportMesh(Mesh mesh, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportMesh, 0, 0, 2)
    ZEND_ARG_INFO(0, mesh)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportMesh)
{
    zval *mesh;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(mesh)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    RETURN_BOOL(ExportMesh(*php_raylib_mesh_fetch_data(phpMesh), fileName->val));
}

// Compute mesh bounding box limits
// RLAPI BoundingBox GetMeshBoundingBox(Mesh mesh);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMeshBoundingBox, 0, 0, 1)
    ZEND_ARG_INFO(0, mesh)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMeshBoundingBox)
{
    zval *mesh;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(mesh)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    BoundingBox originalResult = GetMeshBoundingBox(*php_raylib_mesh_fetch_data(phpMesh));
    zend_object *result = php_raylib_boundingbox_new_ex(php_raylib_boundingbox_ce, NULL);
    php_raylib_boundingbox_object *phpResult = php_raylib_boundingbox_fetch_object(result);
    BoundingBox *boundingboxData = php_raylib_boundingbox_fetch_data(phpResult);
    // Dereference boundingboxData for assignment back to object
    *boundingboxData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Compute mesh tangents
// RLAPI void GenMeshTangents(Mesh* mesh);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshTangents, 0, 0, 1)
    ZEND_ARG_INFO(0, mesh)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshTangents)
{
    zval *mesh;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(mesh)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);

    GenMeshTangents(php_raylib_mesh_fetch_data(phpMesh));

}

// Generate polygonal mesh
// RLAPI Mesh GenMeshPoly(int sides, float radius);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshPoly, 0, 0, 2)
    ZEND_ARG_INFO(0, sides)
    ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshPoly)
{
    zend_long sides;
    double radius;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(sides)
        Z_PARAM_DOUBLE(radius)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshPoly((sides <= INT_MAX) ? (int) ((zend_long) sides) : -1, (float) radius);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate plane mesh (with subdivisions)
// RLAPI Mesh GenMeshPlane(float width, float length, int resX, int resZ);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshPlane, 0, 0, 4)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, length)
    ZEND_ARG_INFO(0, resX)
    ZEND_ARG_INFO(0, resZ)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshPlane)
{
    double width;
    double length;
    zend_long resX;
    zend_long resZ;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(length)
        Z_PARAM_LONG(resX)
        Z_PARAM_LONG(resZ)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshPlane((float) width, (float) length, (resX <= INT_MAX) ? (int) ((zend_long) resX) : -1, (resZ <= INT_MAX) ? (int) ((zend_long) resZ) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate cuboid mesh
// RLAPI Mesh GenMeshCube(float width, float height, float length);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshCube, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshCube)
{
    double width;
    double height;
    double length;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_DOUBLE(length)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshCube((float) width, (float) height, (float) length);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate sphere mesh (standard sphere)
// RLAPI Mesh GenMeshSphere(float radius, int rings, int slices);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshSphere, 0, 0, 3)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, slices)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshSphere)
{
    double radius;
    zend_long rings;
    zend_long slices;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(rings)
        Z_PARAM_LONG(slices)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshSphere((float) radius, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate half-sphere mesh (no bottom cap)
// RLAPI Mesh GenMeshHemiSphere(float radius, int rings, int slices);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshHemiSphere, 0, 0, 3)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, rings)
    ZEND_ARG_INFO(0, slices)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshHemiSphere)
{
    double radius;
    zend_long rings;
    zend_long slices;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_LONG(rings)
        Z_PARAM_LONG(slices)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshHemiSphere((float) radius, (rings <= INT_MAX) ? (int) ((zend_long) rings) : -1, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate cylinder mesh
// RLAPI Mesh GenMeshCylinder(float radius, float height, int slices);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshCylinder, 0, 0, 3)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, slices)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshCylinder)
{
    double radius;
    double height;
    zend_long slices;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_LONG(slices)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshCylinder((float) radius, (float) height, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate cone/pyramid mesh
// RLAPI Mesh GenMeshCone(float radius, float height, int slices);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshCone, 0, 0, 3)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, slices)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshCone)
{
    double radius;
    double height;
    zend_long slices;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(height)
        Z_PARAM_LONG(slices)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshCone((float) radius, (float) height, (slices <= INT_MAX) ? (int) ((zend_long) slices) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate torus mesh
// RLAPI Mesh GenMeshTorus(float radius, float size, int radSeg, int sides);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshTorus, 0, 0, 4)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, radSeg)
    ZEND_ARG_INFO(0, sides)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshTorus)
{
    double radius;
    double size;
    zend_long radSeg;
    zend_long sides;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(size)
        Z_PARAM_LONG(radSeg)
        Z_PARAM_LONG(sides)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshTorus((float) radius, (float) size, (radSeg <= INT_MAX) ? (int) ((zend_long) radSeg) : -1, (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate trefoil knot mesh
// RLAPI Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshKnot, 0, 0, 4)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, radSeg)
    ZEND_ARG_INFO(0, sides)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshKnot)
{
    double radius;
    double size;
    zend_long radSeg;
    zend_long sides;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(size)
        Z_PARAM_LONG(radSeg)
        Z_PARAM_LONG(sides)
    ZEND_PARSE_PARAMETERS_END();


    Mesh originalResult = GenMeshKnot((float) radius, (float) size, (radSeg <= INT_MAX) ? (int) ((zend_long) radSeg) : -1, (sides <= INT_MAX) ? (int) ((zend_long) sides) : -1);
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate heightmap mesh from image data
// RLAPI Mesh GenMeshHeightmap(Image heightmap, Vector3 size);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshHeightmap, 0, 0, 2)
    ZEND_ARG_INFO(0, heightmap)
    ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshHeightmap)
{
    zval *heightmap;
    zval *size;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(heightmap)
        Z_PARAM_ZVAL(size)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpHeightmap = Z_IMAGE_OBJ_P(heightmap);
    php_raylib_vector3_object *phpSize = Z_VECTOR3_OBJ_P(size);

    Mesh originalResult = GenMeshHeightmap(*php_raylib_image_fetch_data(phpHeightmap), *php_raylib_vector3_fetch_data(phpSize));
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Generate cubes-based map mesh from image data
// RLAPI Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GenMeshCubicmap, 0, 0, 2)
    ZEND_ARG_INFO(0, cubicmap)
    ZEND_ARG_INFO(0, cubeSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GenMeshCubicmap)
{
    zval *cubicmap;
    zval *cubeSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(cubicmap)
        Z_PARAM_ZVAL(cubeSize)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_image_object *phpCubicmap = Z_IMAGE_OBJ_P(cubicmap);
    php_raylib_vector3_object *phpCubeSize = Z_VECTOR3_OBJ_P(cubeSize);

    Mesh originalResult = GenMeshCubicmap(*php_raylib_image_fetch_data(phpCubicmap), *php_raylib_vector3_fetch_data(phpCubeSize));
    zend_object *result = php_raylib_mesh_new_ex(php_raylib_mesh_ce, NULL);
    php_raylib_mesh_object *phpResult = php_raylib_mesh_fetch_object(result);
    Mesh *meshData = php_raylib_mesh_fetch_data(phpResult);
    // Dereference meshData for assignment back to object
    *meshData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
// RLAPI Material LoadMaterialDefault();
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadMaterialDefault, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadMaterialDefault)
{

    ZEND_PARSE_PARAMETERS_NONE();

    Material originalResult = LoadMaterialDefault();
    zend_object *result = php_raylib_material_new_ex(php_raylib_material_ce, NULL);
    php_raylib_material_object *phpResult = php_raylib_material_fetch_object(result);
    Material *materialData = php_raylib_material_fetch_data(phpResult);
    // Dereference materialData for assignment back to object
    *materialData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Check if a material is ready
// RLAPI bool IsMaterialReady(Material material);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMaterialReady, 0, 0, 1)
    ZEND_ARG_INFO(0, material)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMaterialReady)
{
    zval *material;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(material)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_material_object *phpMaterial = Z_MATERIAL_OBJ_P(material);

    RETURN_BOOL(IsMaterialReady(*php_raylib_material_fetch_data(phpMaterial)));
}

// Unload material from GPU memory (VRAM)
// RLAPI void UnloadMaterial(Material material);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadMaterial, 0, 0, 1)
    ZEND_ARG_INFO(0, material)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadMaterial)
{
    zval *material;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(material)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_material_object *phpMaterial = Z_MATERIAL_OBJ_P(material);

    UnloadMaterial(*php_raylib_material_fetch_data(phpMaterial));

}

// Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
// RLAPI void SetMaterialTexture(Material* material, int mapType, Texture texture);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMaterialTexture, 0, 0, 3)
    ZEND_ARG_INFO(0, material)
    ZEND_ARG_INFO(0, mapType)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMaterialTexture)
{
    zval *material;
    zend_long mapType;
    zval *texture;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(material)
        Z_PARAM_LONG(mapType)
        Z_PARAM_ZVAL(texture)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_material_object *phpMaterial = Z_MATERIAL_OBJ_P(material);
    php_raylib_texture_object *phpTexture = Z_TEXTURE_OBJ_P(texture);

    SetMaterialTexture(php_raylib_material_fetch_data(phpMaterial), (mapType <= INT_MAX) ? (int) ((zend_long) mapType) : -1, *php_raylib_texture_fetch_data(phpTexture));

}

// Set material for a mesh
// RLAPI void SetModelMeshMaterial(Model* model, int meshId, int materialId);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetModelMeshMaterial, 0, 0, 3)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, meshId)
    ZEND_ARG_INFO(0, materialId)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetModelMeshMaterial)
{
    zval *model;
    zend_long meshId;
    zend_long materialId;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(model)
        Z_PARAM_LONG(meshId)
        Z_PARAM_LONG(materialId)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);

    SetModelMeshMaterial(php_raylib_model_fetch_data(phpModel), (meshId <= INT_MAX) ? (int) ((zend_long) meshId) : -1, (materialId <= INT_MAX) ? (int) ((zend_long) materialId) : -1);

}

// Load model animations from file
// RLAPI Model LoadModelFromMesh(Mesh mesh);
//ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadModelAnimations, 0, 1, 2)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_LoadModelAnimations, 0, 2, IS_ARRAY, 0)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_TYPE_INFO(1, animCount, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadModelAnimations)
{
    zend_string *fileName;
    zval *zAnimsCount = NULL;
    unsigned int i;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(fileName)
        Z_PARAM_ZVAL(zAnimsCount)
    ZEND_PARSE_PARAMETERS_END();

    unsigned int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations(fileName->val, &animsCount);

    if (zAnimsCount) {
        ZEND_TRY_ASSIGN_REF_LONG(zAnimsCount, animsCount);
    }

    // Create a PHP array with the default size of the animation count
    array_init_size(return_value, animsCount);

    for (i = 0; i < animsCount; i++) {
        // Create the animation
        zend_object *modelAnimation = php_raylib_modelanimation_new_ex(php_raylib_modelanimation_ce, NULL);
        php_raylib_modelanimation_object *phpModelAnimation = php_raylib_modelanimation_fetch_object(modelAnimation);

        // Assign model animation to PHP object
        phpModelAnimation->modelanimation->type = RL_MODELANIMATION_IS_POINTER;
        phpModelAnimation->modelanimation->data.p = &anims[i];

        // Create sub-object BoneInfo
        for (int n = 0; n < anims[i].boneCount; n++) {
            zend_object *boneInfo = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, NULL);
            php_raylib_boneinfo_object *phpBoneInfo = php_raylib_boneinfo_fetch_object(boneInfo);
            phpBoneInfo->boneinfo->type = RL_BONEINFO_IS_POINTER;
            phpBoneInfo->boneinfo->data.p = &anims[i].bones[n];

            add_next_index_object(&phpModelAnimation->bones,  boneInfo);
        }

        // Create sub-object Transform
        for (int w = 0; w < anims[i].frameCount; w++) {
            zend_object *transform = php_raylib_transform_new_ex(php_raylib_transform_ce, NULL);
            php_raylib_transform_object *phpTransform = php_raylib_transform_fetch_object(transform);
            phpTransform->transform->type = RL_TRANSFORM_IS_POINTER;
            phpTransform->transform->data.p = anims[i].framePoses[w];

            add_next_index_object(&phpModelAnimation->frameposes,  transform);
        }

        // Push PHP object to array
        add_next_index_object(return_value,  &phpModelAnimation->std);
    }
}


// Update model animation pose
// RLAPI void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UpdateModelAnimation, 0, 0, 3)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, anim)
    ZEND_ARG_INFO(0, frame)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UpdateModelAnimation)
{
    zval *model;
    zval *anim;
    zend_long frame;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(anim)
        Z_PARAM_LONG(frame)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_modelanimation_object *phpAnim = Z_MODELANIMATION_OBJ_P(anim);

    UpdateModelAnimation(*php_raylib_model_fetch_data(phpModel), *php_raylib_modelanimation_fetch_data(phpAnim), (frame <= INT_MAX) ? (int) ((zend_long) frame) : -1);

}

// Unload animation data
// RLAPI void UnloadModelAnimation(ModelAnimation anim);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadModelAnimation, 0, 0, 1)
    ZEND_ARG_INFO(0, anim)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadModelAnimation)
{
    zval *anim;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(anim)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_modelanimation_object *phpAnim = Z_MODELANIMATION_OBJ_P(anim);

    UnloadModelAnimation(*php_raylib_modelanimation_fetch_data(phpAnim));

}

// Unload animation array data
// RLAPI void UnloadModelAnimations(ModelAnimation* animations, unsigned int count);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadModelAnimations, 0, 0, 2)
    ZEND_ARG_INFO(0, animations)
    ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadModelAnimations)
{
    zval *animations;
    zend_long count;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(animations)
        Z_PARAM_LONG(count)
    ZEND_PARSE_PARAMETERS_END();

    zval *animations_element;
    int animations_index;
    HashTable *animations_hash = Z_ARRVAL_P(animations);
    SEPARATE_ARRAY(animations);
    int animations_count = zend_hash_num_elements(animations_hash);
    ModelAnimation* animations_array = safe_emalloc(sizeof(ModelAnimation*), animations_count, 0);
    ZEND_HASH_FOREACH_VAL(animations_hash, animations_element) {
        ZVAL_DEREF(animations_element);
        if ((Z_TYPE_P(animations_element) == IS_OBJECT && instanceof_function(Z_OBJCE_P(animations_element), php_raylib_modelanimation_ce))) {
            php_raylib_modelanimation_object *modelanimation_obj =  Z_MODELANIMATION_OBJ_P(animations_element);
            animations_array[animations_index] = *php_raylib_modelanimation_fetch_data(modelanimation_obj);
        }

        animations_index++;
    } ZEND_HASH_FOREACH_END();

    UnloadModelAnimations(animations_array, (count <= INT_MAX) ? (int) ((zend_long) count) : -1);

}

// Check model animation skeleton match
// RLAPI bool IsModelAnimationValid(Model model, ModelAnimation anim);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsModelAnimationValid, 0, 0, 2)
    ZEND_ARG_INFO(0, model)
    ZEND_ARG_INFO(0, anim)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsModelAnimationValid)
{
    zval *model;
    zval *anim;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(model)
        Z_PARAM_ZVAL(anim)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_model_object *phpModel = Z_MODEL_OBJ_P(model);
    php_raylib_modelanimation_object *phpAnim = Z_MODELANIMATION_OBJ_P(anim);

    RETURN_BOOL(IsModelAnimationValid(*php_raylib_model_fetch_data(phpModel), *php_raylib_modelanimation_fetch_data(phpAnim)));
}

// Check collision between two spheres
// RLAPI bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionSpheres, 0, 0, 4)
    ZEND_ARG_INFO(0, center1)
    ZEND_ARG_INFO(0, radius1)
    ZEND_ARG_INFO(0, center2)
    ZEND_ARG_INFO(0, radius2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionSpheres)
{
    zval *center1;
    double radius1;
    zval *center2;
    double radius2;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(center1)
        Z_PARAM_DOUBLE(radius1)
        Z_PARAM_ZVAL(center2)
        Z_PARAM_DOUBLE(radius2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_vector3_object *phpCenter1 = Z_VECTOR3_OBJ_P(center1);
    php_raylib_vector3_object *phpCenter2 = Z_VECTOR3_OBJ_P(center2);

    RETURN_BOOL(CheckCollisionSpheres(*php_raylib_vector3_fetch_data(phpCenter1), (float) radius1, *php_raylib_vector3_fetch_data(phpCenter2), (float) radius2));
}

// Check collision between two bounding boxes
// RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionBoxes, 0, 0, 2)
    ZEND_ARG_INFO(0, box1)
    ZEND_ARG_INFO(0, box2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionBoxes)
{
    zval *box1;
    zval *box2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(box1)
        Z_PARAM_ZVAL(box2)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_boundingbox_object *phpBox1 = Z_BOUNDINGBOX_OBJ_P(box1);
    php_raylib_boundingbox_object *phpBox2 = Z_BOUNDINGBOX_OBJ_P(box2);

    RETURN_BOOL(CheckCollisionBoxes(*php_raylib_boundingbox_fetch_data(phpBox1), *php_raylib_boundingbox_fetch_data(phpBox2)));
}

// Check collision between box and sphere
// RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius);
ZEND_BEGIN_ARG_INFO_EX(arginfo_CheckCollisionBoxSphere, 0, 0, 3)
    ZEND_ARG_INFO(0, box)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CheckCollisionBoxSphere)
{
    zval *box;
    zval *center;
    double radius;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(box)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_boundingbox_object *phpBox = Z_BOUNDINGBOX_OBJ_P(box);
    php_raylib_vector3_object *phpCenter = Z_VECTOR3_OBJ_P(center);

    RETURN_BOOL(CheckCollisionBoxSphere(*php_raylib_boundingbox_fetch_data(phpBox), *php_raylib_vector3_fetch_data(phpCenter), (float) radius));
}

// Get collision info between ray and sphere
// RLAPI RayCollision GetRayCollisionSphere(Ray ray, Vector3 center, float radius);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRayCollisionSphere, 0, 0, 3)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, center)
    ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRayCollisionSphere)
{
    zval *ray;
    zval *center;
    double radius;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(center)
        Z_PARAM_DOUBLE(radius)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_vector3_object *phpCenter = Z_VECTOR3_OBJ_P(center);

    RayCollision originalResult = GetRayCollisionSphere(*php_raylib_ray_fetch_data(phpRay), *php_raylib_vector3_fetch_data(phpCenter), (float) radius);
    zend_object *result = php_raylib_raycollision_new_ex(php_raylib_raycollision_ce, NULL);
    php_raylib_raycollision_object *phpResult = php_raylib_raycollision_fetch_object(result);
    RayCollision *raycollisionData = php_raylib_raycollision_fetch_data(phpResult);
    // Dereference raycollisionData for assignment back to object
    *raycollisionData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get collision info between ray and box
// RLAPI RayCollision GetRayCollisionBox(Ray ray, BoundingBox box);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRayCollisionBox, 0, 0, 2)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, box)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRayCollisionBox)
{
    zval *ray;
    zval *box;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(box)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_boundingbox_object *phpBox = Z_BOUNDINGBOX_OBJ_P(box);

    RayCollision originalResult = GetRayCollisionBox(*php_raylib_ray_fetch_data(phpRay), *php_raylib_boundingbox_fetch_data(phpBox));
    zend_object *result = php_raylib_raycollision_new_ex(php_raylib_raycollision_ce, NULL);
    php_raylib_raycollision_object *phpResult = php_raylib_raycollision_fetch_object(result);
    RayCollision *raycollisionData = php_raylib_raycollision_fetch_data(phpResult);
    // Dereference raycollisionData for assignment back to object
    *raycollisionData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get collision info between ray and mesh
// RLAPI RayCollision GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRayCollisionMesh, 0, 0, 3)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, mesh)
    ZEND_ARG_INFO(0, transform)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRayCollisionMesh)
{
    zval *ray;
    zval *mesh;
    zval *transform;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(mesh)
        Z_PARAM_ZVAL(transform)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_mesh_object *phpMesh = Z_MESH_OBJ_P(mesh);
    php_raylib_matrix_object *phpTransform = Z_MATRIX_OBJ_P(transform);

    RayCollision originalResult = GetRayCollisionMesh(*php_raylib_ray_fetch_data(phpRay), *php_raylib_mesh_fetch_data(phpMesh), *php_raylib_matrix_fetch_data(phpTransform));
    zend_object *result = php_raylib_raycollision_new_ex(php_raylib_raycollision_ce, NULL);
    php_raylib_raycollision_object *phpResult = php_raylib_raycollision_fetch_object(result);
    RayCollision *raycollisionData = php_raylib_raycollision_fetch_data(phpResult);
    // Dereference raycollisionData for assignment back to object
    *raycollisionData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get collision info between ray and triangle
// RLAPI RayCollision GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRayCollisionTriangle, 0, 0, 4)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, p1)
    ZEND_ARG_INFO(0, p2)
    ZEND_ARG_INFO(0, p3)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRayCollisionTriangle)
{
    zval *ray;
    zval *p1;
    zval *p2;
    zval *p3;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(p1)
        Z_PARAM_ZVAL(p2)
        Z_PARAM_ZVAL(p3)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_vector3_object *phpP1 = Z_VECTOR3_OBJ_P(p1);
    php_raylib_vector3_object *phpP2 = Z_VECTOR3_OBJ_P(p2);
    php_raylib_vector3_object *phpP3 = Z_VECTOR3_OBJ_P(p3);

    RayCollision originalResult = GetRayCollisionTriangle(*php_raylib_ray_fetch_data(phpRay), *php_raylib_vector3_fetch_data(phpP1), *php_raylib_vector3_fetch_data(phpP2), *php_raylib_vector3_fetch_data(phpP3));
    zend_object *result = php_raylib_raycollision_new_ex(php_raylib_raycollision_ce, NULL);
    php_raylib_raycollision_object *phpResult = php_raylib_raycollision_fetch_object(result);
    RayCollision *raycollisionData = php_raylib_raycollision_fetch_data(phpResult);
    // Dereference raycollisionData for assignment back to object
    *raycollisionData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Get collision info between ray and quad
// RLAPI RayCollision GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetRayCollisionQuad, 0, 0, 5)
    ZEND_ARG_INFO(0, ray)
    ZEND_ARG_INFO(0, p1)
    ZEND_ARG_INFO(0, p2)
    ZEND_ARG_INFO(0, p3)
    ZEND_ARG_INFO(0, p4)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetRayCollisionQuad)
{
    zval *ray;
    zval *p1;
    zval *p2;
    zval *p3;
    zval *p4;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(ray)
        Z_PARAM_ZVAL(p1)
        Z_PARAM_ZVAL(p2)
        Z_PARAM_ZVAL(p3)
        Z_PARAM_ZVAL(p4)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_ray_object *phpRay = Z_RAY_OBJ_P(ray);
    php_raylib_vector3_object *phpP1 = Z_VECTOR3_OBJ_P(p1);
    php_raylib_vector3_object *phpP2 = Z_VECTOR3_OBJ_P(p2);
    php_raylib_vector3_object *phpP3 = Z_VECTOR3_OBJ_P(p3);
    php_raylib_vector3_object *phpP4 = Z_VECTOR3_OBJ_P(p4);

    RayCollision originalResult = GetRayCollisionQuad(*php_raylib_ray_fetch_data(phpRay), *php_raylib_vector3_fetch_data(phpP1), *php_raylib_vector3_fetch_data(phpP2), *php_raylib_vector3_fetch_data(phpP3), *php_raylib_vector3_fetch_data(phpP4));
    zend_object *result = php_raylib_raycollision_new_ex(php_raylib_raycollision_ce, NULL);
    php_raylib_raycollision_object *phpResult = php_raylib_raycollision_fetch_object(result);
    RayCollision *raycollisionData = php_raylib_raycollision_fetch_data(phpResult);
    // Dereference raycollisionData for assignment back to object
    *raycollisionData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Initialize audio device and context
// RLAPI void InitAudioDevice();
ZEND_BEGIN_ARG_INFO_EX(arginfo_InitAudioDevice, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(InitAudioDevice)
{

    ZEND_PARSE_PARAMETERS_NONE();

    InitAudioDevice();

}

// Close the audio device and context
// RLAPI void CloseAudioDevice();
ZEND_BEGIN_ARG_INFO_EX(arginfo_CloseAudioDevice, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(CloseAudioDevice)
{

    ZEND_PARSE_PARAMETERS_NONE();

    CloseAudioDevice();

}

// Check if audio device has been initialized successfully
// RLAPI bool IsAudioDeviceReady();
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsAudioDeviceReady, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsAudioDeviceReady)
{

    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_BOOL(IsAudioDeviceReady());
}

// Set master volume (listener)
// RLAPI void SetMasterVolume(float volume);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMasterVolume, 0, 0, 1)
    ZEND_ARG_INFO(0, volume)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMasterVolume)
{
    double volume;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(volume)
    ZEND_PARSE_PARAMETERS_END();


    SetMasterVolume((float) volume);

}

// Load wave data from file
// RLAPI Wave LoadWave(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadWave, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadWave)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Wave originalResult = LoadWave(fileName->val);
    zend_object *result = php_raylib_wave_new_ex(php_raylib_wave_ce, NULL);
    php_raylib_wave_object *phpResult = php_raylib_wave_fetch_object(result);
    Wave *waveData = php_raylib_wave_fetch_data(phpResult);
    // Dereference waveData for assignment back to object
    *waveData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
// RLAPI Wave LoadWaveFromMemory(const char * fileType, const unsigned char * fileData, int dataSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadWaveFromMemory, 0, 0, 3)
    ZEND_ARG_INFO(0, fileType)
    ZEND_ARG_INFO(0, fileData)
    ZEND_ARG_INFO(0, dataSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadWaveFromMemory)
{
    zend_string *fileType;
    zval *fileData;
    zend_long dataSize;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(fileType)
        Z_PARAM_ARRAY(fileData)
        Z_PARAM_LONG(dataSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *filedata_element;
    int filedata_index;
    HashTable *filedata_hash = Z_ARRVAL_P(fileData);
    SEPARATE_ARRAY(fileData);
    int filedata_count = zend_hash_num_elements(filedata_hash);
    unsigned char * filedata_array = safe_emalloc(sizeof(unsigned char *), filedata_count, 0);
    ZEND_HASH_FOREACH_VAL(filedata_hash, filedata_element) {
        ZVAL_DEREF(filedata_element);
        if (Z_TYPE_P(filedata_element) == IS_LONG) {
            filedata_array[filedata_index] = (const unsigned char) Z_LVAL_P(filedata_element);
        }

        filedata_index++;
    } ZEND_HASH_FOREACH_END();

    Wave originalResult = LoadWaveFromMemory(fileType->val, filedata_array, (dataSize <= INT_MAX) ? (int) ((zend_long) dataSize) : -1);
    zend_object *result = php_raylib_wave_new_ex(php_raylib_wave_ce, NULL);
    php_raylib_wave_object *phpResult = php_raylib_wave_fetch_object(result);
    Wave *waveData = php_raylib_wave_fetch_data(phpResult);
    // Dereference waveData for assignment back to object
    *waveData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Checks if wave data is ready
// RLAPI bool IsWaveReady(Wave wave);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsWaveReady, 0, 0, 1)
    ZEND_ARG_INFO(0, wave)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsWaveReady)
{
    zval *wave;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(wave)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    RETURN_BOOL(IsWaveReady(*php_raylib_wave_fetch_data(phpWave)));
}

// Load sound from file
// RLAPI Sound LoadSound(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadSound, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadSound)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Sound originalResult = LoadSound(fileName->val);
    zend_object *result = php_raylib_sound_new_ex(php_raylib_sound_ce, NULL);
    php_raylib_sound_object *phpResult = php_raylib_sound_fetch_object(result);
    Sound *soundData = php_raylib_sound_fetch_data(phpResult);
    // Dereference soundData for assignment back to object
    *soundData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load sound from wave data
// RLAPI Sound LoadSoundFromWave(Wave wave);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadSoundFromWave, 0, 0, 1)
    ZEND_ARG_INFO(0, wave)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadSoundFromWave)
{
    zval *wave;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(wave)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    Sound originalResult = LoadSoundFromWave(*php_raylib_wave_fetch_data(phpWave));
    zend_object *result = php_raylib_sound_new_ex(php_raylib_sound_ce, NULL);
    php_raylib_sound_object *phpResult = php_raylib_sound_fetch_object(result);
    Sound *soundData = php_raylib_sound_fetch_data(phpResult);
    // Dereference soundData for assignment back to object
    *soundData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Checks if a sound is ready
// RLAPI bool IsSoundReady(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsSoundReady, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsSoundReady)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    RETURN_BOOL(IsSoundReady(*php_raylib_sound_fetch_data(phpSound)));
}

// Unload wave data
// RLAPI void UnloadWave(Wave wave);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadWave, 0, 0, 1)
    ZEND_ARG_INFO(0, wave)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadWave)
{
    zval *wave;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(wave)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    UnloadWave(*php_raylib_wave_fetch_data(phpWave));

}

// Unload sound
// RLAPI void UnloadSound(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadSound, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadSound)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    UnloadSound(*php_raylib_sound_fetch_data(phpSound));

}

// Export wave data to file, returns true on success
// RLAPI bool ExportWave(Wave wave, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportWave, 0, 0, 2)
    ZEND_ARG_INFO(0, wave)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportWave)
{
    zval *wave;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(wave)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    RETURN_BOOL(ExportWave(*php_raylib_wave_fetch_data(phpWave), fileName->val));
}

// Export wave sample data to code (.h), returns true on success
// RLAPI bool ExportWaveAsCode(Wave wave, const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ExportWaveAsCode, 0, 0, 2)
    ZEND_ARG_INFO(0, wave)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ExportWaveAsCode)
{
    zval *wave;
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(wave)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    RETURN_BOOL(ExportWaveAsCode(*php_raylib_wave_fetch_data(phpWave), fileName->val));
}

// Play a sound
// RLAPI void PlaySound(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PlaySound, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PlaySound)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    PlaySound(*php_raylib_sound_fetch_data(phpSound));

}

// Stop playing a sound
// RLAPI void StopSound(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_StopSound, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(StopSound)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    StopSound(*php_raylib_sound_fetch_data(phpSound));

}

// Pause a sound
// RLAPI void PauseSound(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PauseSound, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PauseSound)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    PauseSound(*php_raylib_sound_fetch_data(phpSound));

}

// Resume a paused sound
// RLAPI void ResumeSound(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ResumeSound, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ResumeSound)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    ResumeSound(*php_raylib_sound_fetch_data(phpSound));

}

// Check if a sound is currently playing
// RLAPI bool IsSoundPlaying(Sound sound);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsSoundPlaying, 0, 0, 1)
    ZEND_ARG_INFO(0, sound)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsSoundPlaying)
{
    zval *sound;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(sound)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    RETURN_BOOL(IsSoundPlaying(*php_raylib_sound_fetch_data(phpSound)));
}

// Set volume for a sound (1.0 is max level)
// RLAPI void SetSoundVolume(Sound sound, float volume);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetSoundVolume, 0, 0, 2)
    ZEND_ARG_INFO(0, sound)
    ZEND_ARG_INFO(0, volume)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetSoundVolume)
{
    zval *sound;
    double volume;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(sound)
        Z_PARAM_DOUBLE(volume)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    SetSoundVolume(*php_raylib_sound_fetch_data(phpSound), (float) volume);

}

// Set pitch for a sound (1.0 is base level)
// RLAPI void SetSoundPitch(Sound sound, float pitch);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetSoundPitch, 0, 0, 2)
    ZEND_ARG_INFO(0, sound)
    ZEND_ARG_INFO(0, pitch)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetSoundPitch)
{
    zval *sound;
    double pitch;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(sound)
        Z_PARAM_DOUBLE(pitch)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    SetSoundPitch(*php_raylib_sound_fetch_data(phpSound), (float) pitch);

}

// Set pan for a sound (0.5 is center)
// RLAPI void SetSoundPan(Sound sound, float pan);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetSoundPan, 0, 0, 2)
    ZEND_ARG_INFO(0, sound)
    ZEND_ARG_INFO(0, pan)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetSoundPan)
{
    zval *sound;
    double pan;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(sound)
        Z_PARAM_DOUBLE(pan)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_sound_object *phpSound = Z_SOUND_OBJ_P(sound);

    SetSoundPan(*php_raylib_sound_fetch_data(phpSound), (float) pan);

}

// Copy a wave to a new wave
// RLAPI Wave WaveCopy(Wave wave);
ZEND_BEGIN_ARG_INFO_EX(arginfo_WaveCopy, 0, 0, 1)
    ZEND_ARG_INFO(0, wave)
ZEND_END_ARG_INFO()
PHP_FUNCTION(WaveCopy)
{
    zval *wave;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(wave)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    Wave originalResult = WaveCopy(*php_raylib_wave_fetch_data(phpWave));
    zend_object *result = php_raylib_wave_new_ex(php_raylib_wave_ce, NULL);
    php_raylib_wave_object *phpResult = php_raylib_wave_fetch_object(result);
    Wave *waveData = php_raylib_wave_fetch_data(phpResult);
    // Dereference waveData for assignment back to object
    *waveData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Crop a wave to defined samples range
// RLAPI void WaveCrop(Wave* wave, int initSample, int finalSample);
ZEND_BEGIN_ARG_INFO_EX(arginfo_WaveCrop, 0, 0, 3)
    ZEND_ARG_INFO(0, wave)
    ZEND_ARG_INFO(0, initSample)
    ZEND_ARG_INFO(0, finalSample)
ZEND_END_ARG_INFO()
PHP_FUNCTION(WaveCrop)
{
    zval *wave;
    zend_long initSample;
    zend_long finalSample;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(wave)
        Z_PARAM_LONG(initSample)
        Z_PARAM_LONG(finalSample)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    WaveCrop(php_raylib_wave_fetch_data(phpWave), (initSample <= INT_MAX) ? (int) ((zend_long) initSample) : -1, (finalSample <= INT_MAX) ? (int) ((zend_long) finalSample) : -1);

}

// Convert wave data to desired format
// RLAPI void WaveFormat(Wave* wave, int sampleRate, int sampleSize, int channels);
ZEND_BEGIN_ARG_INFO_EX(arginfo_WaveFormat, 0, 0, 4)
    ZEND_ARG_INFO(0, wave)
    ZEND_ARG_INFO(0, sampleRate)
    ZEND_ARG_INFO(0, sampleSize)
    ZEND_ARG_INFO(0, channels)
ZEND_END_ARG_INFO()
PHP_FUNCTION(WaveFormat)
{
    zval *wave;
    zend_long sampleRate;
    zend_long sampleSize;
    zend_long channels;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(wave)
        Z_PARAM_LONG(sampleRate)
        Z_PARAM_LONG(sampleSize)
        Z_PARAM_LONG(channels)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *phpWave = Z_WAVE_OBJ_P(wave);

    WaveFormat(php_raylib_wave_fetch_data(phpWave), (sampleRate <= INT_MAX) ? (int) ((zend_long) sampleRate) : -1, (sampleSize <= INT_MAX) ? (int) ((zend_long) sampleSize) : -1, (channels <= INT_MAX) ? (int) ((zend_long) channels) : -1);

}

// Unload samples data loaded with LoadWaveSamples()
// RLAPI void UnloadWaveSamples(float * samples);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadWaveSamples, 0, 0, 1)
    ZEND_ARG_INFO(0, samples)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadWaveSamples)
{
    zval *samples;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(samples)
    ZEND_PARSE_PARAMETERS_END();

    zval *samples_element;
    int samples_index;
    HashTable *samples_hash = Z_ARRVAL_P(samples);
    SEPARATE_ARRAY(samples);
    int samples_count = zend_hash_num_elements(samples_hash);
    float * samples_array = safe_emalloc(sizeof(float *), samples_count, 0);
    ZEND_HASH_FOREACH_VAL(samples_hash, samples_element) {
        ZVAL_DEREF(samples_element);
        if (Z_TYPE_P(samples_element) == IS_LONG) {
            samples_array[samples_index] = (float) Z_LVAL_P(samples_element);
        }

        samples_index++;
    } ZEND_HASH_FOREACH_END();

    UnloadWaveSamples((float *) samples);

}

// Load music stream from file
// RLAPI Music LoadMusicStream(const char * fileName);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadMusicStream)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();


    Music originalResult = LoadMusicStream(fileName->val);
    zend_object *result = php_raylib_music_new_ex(php_raylib_music_ce, NULL);
    php_raylib_music_object *phpResult = php_raylib_music_fetch_object(result);
    Music *musicData = php_raylib_music_fetch_data(phpResult);
    // Dereference musicData for assignment back to object
    *musicData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Load music stream from data
// RLAPI Music LoadMusicStreamFromMemory(const char * fileType, const unsigned char * data, int dataSize);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadMusicStreamFromMemory, 0, 0, 3)
    ZEND_ARG_INFO(0, fileType)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, dataSize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadMusicStreamFromMemory)
{
    zend_string *fileType;
    zval *data;
    zend_long dataSize;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STR(fileType)
        Z_PARAM_ARRAY(data)
        Z_PARAM_LONG(dataSize)
    ZEND_PARSE_PARAMETERS_END();

    zval *data_element;
    int data_index;
    HashTable *data_hash = Z_ARRVAL_P(data);
    SEPARATE_ARRAY(data);
    int data_count = zend_hash_num_elements(data_hash);
    unsigned char * data_array = safe_emalloc(sizeof(unsigned char *), data_count, 0);
    ZEND_HASH_FOREACH_VAL(data_hash, data_element) {
        ZVAL_DEREF(data_element);
        if (Z_TYPE_P(data_element) == IS_LONG) {
            data_array[data_index] = (const unsigned char) Z_LVAL_P(data_element);
        }

        data_index++;
    } ZEND_HASH_FOREACH_END();

    Music originalResult = LoadMusicStreamFromMemory(fileType->val, data_array, (dataSize <= INT_MAX) ? (int) ((zend_long) dataSize) : -1);
    zend_object *result = php_raylib_music_new_ex(php_raylib_music_ce, NULL);
    php_raylib_music_object *phpResult = php_raylib_music_fetch_object(result);
    Music *musicData = php_raylib_music_fetch_data(phpResult);
    // Dereference musicData for assignment back to object
    *musicData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Checks if a music stream is ready
// RLAPI bool IsMusicReady(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMusicReady, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMusicReady)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    RETURN_BOOL(IsMusicReady(*php_raylib_music_fetch_data(phpMusic)));
}

// Unload music stream
// RLAPI void UnloadMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    UnloadMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Start music playing
// RLAPI void PlayMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PlayMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PlayMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    PlayMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Check if music is playing
// RLAPI bool IsMusicStreamPlaying(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsMusicStreamPlaying, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsMusicStreamPlaying)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    RETURN_BOOL(IsMusicStreamPlaying(*php_raylib_music_fetch_data(phpMusic)));
}

// Updates buffers for music streaming
// RLAPI void UpdateMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UpdateMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UpdateMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    UpdateMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Stop music playing
// RLAPI void StopMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_StopMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(StopMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    StopMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Pause music playing
// RLAPI void PauseMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PauseMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PauseMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    PauseMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Resume playing paused music
// RLAPI void ResumeMusicStream(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ResumeMusicStream, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ResumeMusicStream)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    ResumeMusicStream(*php_raylib_music_fetch_data(phpMusic));

}

// Seek music to a position (in seconds)
// RLAPI void SeekMusicStream(Music music, float position);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SeekMusicStream, 0, 0, 2)
    ZEND_ARG_INFO(0, music)
    ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SeekMusicStream)
{
    zval *music;
    double position;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(music)
        Z_PARAM_DOUBLE(position)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    SeekMusicStream(*php_raylib_music_fetch_data(phpMusic), (float) position);

}

// Set volume for music (1.0 is max level)
// RLAPI void SetMusicVolume(Music music, float volume);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMusicVolume, 0, 0, 2)
    ZEND_ARG_INFO(0, music)
    ZEND_ARG_INFO(0, volume)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMusicVolume)
{
    zval *music;
    double volume;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(music)
        Z_PARAM_DOUBLE(volume)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    SetMusicVolume(*php_raylib_music_fetch_data(phpMusic), (float) volume);

}

// Set pitch for a music (1.0 is base level)
// RLAPI void SetMusicPitch(Music music, float pitch);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMusicPitch, 0, 0, 2)
    ZEND_ARG_INFO(0, music)
    ZEND_ARG_INFO(0, pitch)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMusicPitch)
{
    zval *music;
    double pitch;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(music)
        Z_PARAM_DOUBLE(pitch)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    SetMusicPitch(*php_raylib_music_fetch_data(phpMusic), (float) pitch);

}

// Set pan for a music (0.5 is center)
// RLAPI void SetMusicPan(Music music, float pan);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetMusicPan, 0, 0, 2)
    ZEND_ARG_INFO(0, music)
    ZEND_ARG_INFO(0, pan)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetMusicPan)
{
    zval *music;
    double pan;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(music)
        Z_PARAM_DOUBLE(pan)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    SetMusicPan(*php_raylib_music_fetch_data(phpMusic), (float) pan);

}

// Get music time length (in seconds)
// RLAPI float GetMusicTimeLength(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMusicTimeLength, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMusicTimeLength)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    RETURN_DOUBLE((double) GetMusicTimeLength(*php_raylib_music_fetch_data(phpMusic)));
}

// Get current music time played (in seconds)
// RLAPI float GetMusicTimePlayed(Music music);
ZEND_BEGIN_ARG_INFO_EX(arginfo_GetMusicTimePlayed, 0, 0, 1)
    ZEND_ARG_INFO(0, music)
ZEND_END_ARG_INFO()
PHP_FUNCTION(GetMusicTimePlayed)
{
    zval *music;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(music)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_music_object *phpMusic = Z_MUSIC_OBJ_P(music);

    RETURN_DOUBLE((double) GetMusicTimePlayed(*php_raylib_music_fetch_data(phpMusic)));
}

// Load audio stream (to stream raw audio pcm data)
// RLAPI AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadAudioStream, 0, 0, 3)
    ZEND_ARG_INFO(0, sampleRate)
    ZEND_ARG_INFO(0, sampleSize)
    ZEND_ARG_INFO(0, channels)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadAudioStream)
{
    zend_long sampleRate;
    zend_long sampleSize;
    zend_long channels;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(sampleRate)
        Z_PARAM_LONG(sampleSize)
        Z_PARAM_LONG(channels)
    ZEND_PARSE_PARAMETERS_END();


    AudioStream originalResult = LoadAudioStream((sampleRate <= INT_MAX) ? (int) ((zend_long) sampleRate) : -1, (sampleSize <= INT_MAX) ? (int) ((zend_long) sampleSize) : -1, (channels <= INT_MAX) ? (int) ((zend_long) channels) : -1);
    zend_object *result = php_raylib_audiostream_new_ex(php_raylib_audiostream_ce, NULL);
    php_raylib_audiostream_object *phpResult = php_raylib_audiostream_fetch_object(result);
    AudioStream *audiostreamData = php_raylib_audiostream_fetch_data(phpResult);
    // Dereference audiostreamData for assignment back to object
    *audiostreamData = originalResult;

    RETURN_OBJ(&phpResult->std);
}

// Checks if an audio stream is ready
// RLAPI bool IsAudioStreamReady(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsAudioStreamReady, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsAudioStreamReady)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    RETURN_BOOL(IsAudioStreamReady(*php_raylib_audiostream_fetch_data(phpStream)));
}

// Unload audio stream and free memory
// RLAPI void UnloadAudioStream(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_UnloadAudioStream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(UnloadAudioStream)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    UnloadAudioStream(*php_raylib_audiostream_fetch_data(phpStream));

}

// Check if any audio stream buffers requires refill
// RLAPI bool IsAudioStreamProcessed(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsAudioStreamProcessed, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsAudioStreamProcessed)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    RETURN_BOOL(IsAudioStreamProcessed(*php_raylib_audiostream_fetch_data(phpStream)));
}

// Play audio stream
// RLAPI void PlayAudioStream(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PlayAudioStream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PlayAudioStream)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    PlayAudioStream(*php_raylib_audiostream_fetch_data(phpStream));

}

// Pause audio stream
// RLAPI void PauseAudioStream(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_PauseAudioStream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PauseAudioStream)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    PauseAudioStream(*php_raylib_audiostream_fetch_data(phpStream));

}

// Resume audio stream
// RLAPI void ResumeAudioStream(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_ResumeAudioStream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(ResumeAudioStream)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    ResumeAudioStream(*php_raylib_audiostream_fetch_data(phpStream));

}

// Check if audio stream is playing
// RLAPI bool IsAudioStreamPlaying(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_IsAudioStreamPlaying, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(IsAudioStreamPlaying)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    RETURN_BOOL(IsAudioStreamPlaying(*php_raylib_audiostream_fetch_data(phpStream)));
}

// Stop audio stream
// RLAPI void StopAudioStream(AudioStream stream);
ZEND_BEGIN_ARG_INFO_EX(arginfo_StopAudioStream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()
PHP_FUNCTION(StopAudioStream)
{
    zval *stream;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(stream)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    StopAudioStream(*php_raylib_audiostream_fetch_data(phpStream));

}

// Set volume for audio stream (1.0 is max level)
// RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetAudioStreamVolume, 0, 0, 2)
    ZEND_ARG_INFO(0, stream)
    ZEND_ARG_INFO(0, volume)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetAudioStreamVolume)
{
    zval *stream;
    double volume;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(stream)
        Z_PARAM_DOUBLE(volume)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    SetAudioStreamVolume(*php_raylib_audiostream_fetch_data(phpStream), (float) volume);

}

// Set pitch for audio stream (1.0 is base level)
// RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetAudioStreamPitch, 0, 0, 2)
    ZEND_ARG_INFO(0, stream)
    ZEND_ARG_INFO(0, pitch)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetAudioStreamPitch)
{
    zval *stream;
    double pitch;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(stream)
        Z_PARAM_DOUBLE(pitch)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    SetAudioStreamPitch(*php_raylib_audiostream_fetch_data(phpStream), (float) pitch);

}

// Set pan for audio stream (0.5 is centered)
// RLAPI void SetAudioStreamPan(AudioStream stream, float pan);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetAudioStreamPan, 0, 0, 2)
    ZEND_ARG_INFO(0, stream)
    ZEND_ARG_INFO(0, pan)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetAudioStreamPan)
{
    zval *stream;
    double pan;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(stream)
        Z_PARAM_DOUBLE(pan)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audiostream_object *phpStream = Z_AUDIOSTREAM_OBJ_P(stream);

    SetAudioStreamPan(*php_raylib_audiostream_fetch_data(phpStream), (float) pan);

}

// Default size for new audio streams
// RLAPI void SetAudioStreamBufferSizeDefault(int size);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetAudioStreamBufferSizeDefault, 0, 0, 1)
    ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetAudioStreamBufferSizeDefault)
{
    zend_long size;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(size)
    ZEND_PARSE_PARAMETERS_END();


    SetAudioStreamBufferSizeDefault((size <= INT_MAX) ? (int) ((zend_long) size) : -1);

}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(raylib)
{
    php_raylib_vector2_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vector3_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vector4_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_matrix_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_color_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rectangle_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_image_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_texture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rendertexture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_npatchinfo_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_glyphinfo_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_font_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera3d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera2d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_mesh_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_shader_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_materialmap_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_material_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_transform_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_boneinfo_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_model_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_modelanimation_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_ray_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_raycollision_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_boundingbox_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_wave_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_audiostream_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_sound_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_music_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vrdeviceinfo_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vrstereoconfig_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_filepathlist_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_texture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_texture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rendertexture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera3d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vector4_startup(INIT_FUNC_ARGS_PASSTHRU);

    // raylib Config Flags
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_VSYNC_HINT", FLAG_VSYNC_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_MINIMIZED", FLAG_WINDOW_MINIMIZED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_MAXIMIZED", FLAG_WINDOW_MAXIMIZED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_UNFOCUSED", FLAG_WINDOW_UNFOCUSED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_TOPMOST", FLAG_WINDOW_TOPMOST, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_WINDOW_MOUSE_PASSTHROUGH", FLAG_WINDOW_MOUSE_PASSTHROUGH, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_MSAA_4X_HINT", FLAG_MSAA_4X_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ConfigFlags", "FLAG_INTERLACED_HINT", FLAG_INTERLACED_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_ALL", LOG_ALL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_TRACE", LOG_TRACE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_DEBUG", LOG_DEBUG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_INFO", LOG_INFO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_WARNING", LOG_WARNING, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_ERROR", LOG_ERROR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_FATAL", LOG_FATAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TraceLogLevel", "LOG_NONE", LOG_NONE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_NULL", KEY_NULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_APOSTROPHE", KEY_APOSTROPHE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_COMMA", KEY_COMMA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_MINUS", KEY_MINUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_PERIOD", KEY_PERIOD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SLASH", KEY_SLASH, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_ZERO", KEY_ZERO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_ONE", KEY_ONE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_TWO", KEY_TWO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_THREE", KEY_THREE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_FOUR", KEY_FOUR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_FIVE", KEY_FIVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SIX", KEY_SIX, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SEVEN", KEY_SEVEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_EIGHT", KEY_EIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_NINE", KEY_NINE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SEMICOLON", KEY_SEMICOLON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_EQUAL", KEY_EQUAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_A", KEY_A, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_B", KEY_B, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_C", KEY_C, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_D", KEY_D, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_E", KEY_E, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F", KEY_F, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_G", KEY_G, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_H", KEY_H, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_I", KEY_I, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_J", KEY_J, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_K", KEY_K, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_L", KEY_L, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_M", KEY_M, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_N", KEY_N, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_O", KEY_O, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_P", KEY_P, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_Q", KEY_Q, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_R", KEY_R, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_S", KEY_S, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_T", KEY_T, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_U", KEY_U, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_V", KEY_V, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_W", KEY_W, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_X", KEY_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_Y", KEY_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_Z", KEY_Z, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT_BRACKET", KEY_LEFT_BRACKET, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_BACKSLASH", KEY_BACKSLASH, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_GRAVE", KEY_GRAVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SPACE", KEY_SPACE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_ESCAPE", KEY_ESCAPE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_ENTER", KEY_ENTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_TAB", KEY_TAB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_BACKSPACE", KEY_BACKSPACE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_INSERT", KEY_INSERT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_DELETE", KEY_DELETE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT", KEY_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT", KEY_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_DOWN", KEY_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_UP", KEY_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_PAGE_UP", KEY_PAGE_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_PAGE_DOWN", KEY_PAGE_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_HOME", KEY_HOME, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_END", KEY_END, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_CAPS_LOCK", KEY_CAPS_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_SCROLL_LOCK", KEY_SCROLL_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_NUM_LOCK", KEY_NUM_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_PRINT_SCREEN", KEY_PRINT_SCREEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_PAUSE", KEY_PAUSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F1", KEY_F1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F2", KEY_F2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F3", KEY_F3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F4", KEY_F4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F5", KEY_F5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F6", KEY_F6, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F7", KEY_F7, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F8", KEY_F8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F9", KEY_F9, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F10", KEY_F10, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F11", KEY_F11, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_F12", KEY_F12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT_SHIFT", KEY_LEFT_SHIFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT_CONTROL", KEY_LEFT_CONTROL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT_ALT", KEY_LEFT_ALT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_LEFT_SUPER", KEY_LEFT_SUPER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT_ALT", KEY_RIGHT_ALT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_RIGHT_SUPER", KEY_RIGHT_SUPER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KB_MENU", KEY_KB_MENU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_0", KEY_KP_0, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_1", KEY_KP_1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_2", KEY_KP_2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_3", KEY_KP_3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_4", KEY_KP_4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_5", KEY_KP_5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_6", KEY_KP_6, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_7", KEY_KP_7, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_8", KEY_KP_8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_9", KEY_KP_9, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_DECIMAL", KEY_KP_DECIMAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_DIVIDE", KEY_KP_DIVIDE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_MULTIPLY", KEY_KP_MULTIPLY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_SUBTRACT", KEY_KP_SUBTRACT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_ADD", KEY_KP_ADD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_ENTER", KEY_KP_ENTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_KP_EQUAL", KEY_KP_EQUAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_BACK", KEY_BACK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_MENU", KEY_MENU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_VOLUME_UP", KEY_VOLUME_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\KeyboardKey", "KEY_VOLUME_DOWN", KEY_VOLUME_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_SIDE", MOUSE_BUTTON_SIDE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_EXTRA", MOUSE_BUTTON_EXTRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_FORWARD", MOUSE_BUTTON_FORWARD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseButton", "MOUSE_BUTTON_BACK", MOUSE_BUTTON_BACK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_DEFAULT", MOUSE_CURSOR_DEFAULT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_ARROW", MOUSE_CURSOR_ARROW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_IBEAM", MOUSE_CURSOR_IBEAM, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_CROSSHAIR", MOUSE_CURSOR_CROSSHAIR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_POINTING_HAND", MOUSE_CURSOR_POINTING_HAND, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_RESIZE_EW", MOUSE_CURSOR_RESIZE_EW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_RESIZE_NS", MOUSE_CURSOR_RESIZE_NS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_RESIZE_NWSE", MOUSE_CURSOR_RESIZE_NWSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_RESIZE_NESW", MOUSE_CURSOR_RESIZE_NESW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_RESIZE_ALL", MOUSE_CURSOR_RESIZE_ALL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MouseCursor", "MOUSE_CURSOR_NOT_ALLOWED", MOUSE_CURSOR_NOT_ALLOWED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadButton", "GAMEPAD_BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\GamepadAxis", "GAMEPAD_AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_ALBEDO", MATERIAL_MAP_ALBEDO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_METALNESS", MATERIAL_MAP_METALNESS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_NORMAL", MATERIAL_MAP_NORMAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_ROUGHNESS", MATERIAL_MAP_ROUGHNESS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_OCCLUSION", MATERIAL_MAP_OCCLUSION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_EMISSION", MATERIAL_MAP_EMISSION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_HEIGHT", MATERIAL_MAP_HEIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_CUBEMAP", MATERIAL_MAP_CUBEMAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_IRRADIANCE", MATERIAL_MAP_IRRADIANCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_PREFILTER", MATERIAL_MAP_PREFILTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\MaterialMapIndex", "MATERIAL_MAP_BRDF", MATERIAL_MAP_BRDF, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_POSITION", SHADER_LOC_VERTEX_POSITION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_TEXCOORD01", SHADER_LOC_VERTEX_TEXCOORD01, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_TEXCOORD02", SHADER_LOC_VERTEX_TEXCOORD02, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_NORMAL", SHADER_LOC_VERTEX_NORMAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_TANGENT", SHADER_LOC_VERTEX_TANGENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VERTEX_COLOR", SHADER_LOC_VERTEX_COLOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MATRIX_MVP", SHADER_LOC_MATRIX_MVP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MATRIX_VIEW", SHADER_LOC_MATRIX_VIEW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MATRIX_PROJECTION", SHADER_LOC_MATRIX_PROJECTION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MATRIX_MODEL", SHADER_LOC_MATRIX_MODEL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MATRIX_NORMAL", SHADER_LOC_MATRIX_NORMAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_VECTOR_VIEW", SHADER_LOC_VECTOR_VIEW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_COLOR_DIFFUSE", SHADER_LOC_COLOR_DIFFUSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_COLOR_SPECULAR", SHADER_LOC_COLOR_SPECULAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_COLOR_AMBIENT", SHADER_LOC_COLOR_AMBIENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_ALBEDO", SHADER_LOC_MAP_ALBEDO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_METALNESS", SHADER_LOC_MAP_METALNESS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_NORMAL", SHADER_LOC_MAP_NORMAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_ROUGHNESS", SHADER_LOC_MAP_ROUGHNESS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_OCCLUSION", SHADER_LOC_MAP_OCCLUSION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_EMISSION", SHADER_LOC_MAP_EMISSION, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_HEIGHT", SHADER_LOC_MAP_HEIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_CUBEMAP", SHADER_LOC_MAP_CUBEMAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_IRRADIANCE", SHADER_LOC_MAP_IRRADIANCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_PREFILTER", SHADER_LOC_MAP_PREFILTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderLocationIndex", "SHADER_LOC_MAP_BRDF", SHADER_LOC_MAP_BRDF, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_FLOAT", SHADER_UNIFORM_FLOAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_VEC2", SHADER_UNIFORM_VEC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_VEC3", SHADER_UNIFORM_VEC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_VEC4", SHADER_UNIFORM_VEC4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_INT", SHADER_UNIFORM_INT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_IVEC2", SHADER_UNIFORM_IVEC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_IVEC3", SHADER_UNIFORM_IVEC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_IVEC4", SHADER_UNIFORM_IVEC4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderUniformDataType", "SHADER_UNIFORM_SAMPLER2D", SHADER_UNIFORM_SAMPLER2D, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderAttributeDataType", "SHADER_ATTRIB_FLOAT", SHADER_ATTRIB_FLOAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderAttributeDataType", "SHADER_ATTRIB_VEC2", SHADER_ATTRIB_VEC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderAttributeDataType", "SHADER_ATTRIB_VEC3", SHADER_ATTRIB_VEC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\ShaderAttributeDataType", "SHADER_ATTRIB_VEC4", SHADER_ATTRIB_VEC4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE", PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA", PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R5G6B5", PIXELFORMAT_UNCOMPRESSED_R5G6B5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R8G8B8", PIXELFORMAT_UNCOMPRESSED_R8G8B8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1", PIXELFORMAT_UNCOMPRESSED_R5G5B5A1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4", PIXELFORMAT_UNCOMPRESSED_R4G4B4A4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R32", PIXELFORMAT_UNCOMPRESSED_R32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R32G32B32", PIXELFORMAT_UNCOMPRESSED_R32G32B32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32", PIXELFORMAT_UNCOMPRESSED_R32G32B32A32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_DXT1_RGB", PIXELFORMAT_COMPRESSED_DXT1_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_DXT1_RGBA", PIXELFORMAT_COMPRESSED_DXT1_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_DXT3_RGBA", PIXELFORMAT_COMPRESSED_DXT3_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_DXT5_RGBA", PIXELFORMAT_COMPRESSED_DXT5_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_ETC1_RGB", PIXELFORMAT_COMPRESSED_ETC1_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_ETC2_RGB", PIXELFORMAT_COMPRESSED_ETC2_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA", PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_PVRT_RGB", PIXELFORMAT_COMPRESSED_PVRT_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_PVRT_RGBA", PIXELFORMAT_COMPRESSED_PVRT_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA", PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA", PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_POINT", TEXTURE_FILTER_POINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_BILINEAR", TEXTURE_FILTER_BILINEAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_TRILINEAR", TEXTURE_FILTER_TRILINEAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_ANISOTROPIC_4X", TEXTURE_FILTER_ANISOTROPIC_4X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_ANISOTROPIC_8X", TEXTURE_FILTER_ANISOTROPIC_8X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureFilter", "TEXTURE_FILTER_ANISOTROPIC_16X", TEXTURE_FILTER_ANISOTROPIC_16X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureWrap", "TEXTURE_WRAP_REPEAT", TEXTURE_WRAP_REPEAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureWrap", "TEXTURE_WRAP_CLAMP", TEXTURE_WRAP_CLAMP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureWrap", "TEXTURE_WRAP_MIRROR_REPEAT", TEXTURE_WRAP_MIRROR_REPEAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\TextureWrap", "TEXTURE_WRAP_MIRROR_CLAMP", TEXTURE_WRAP_MIRROR_CLAMP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_AUTO_DETECT", CUBEMAP_LAYOUT_AUTO_DETECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_LINE_VERTICAL", CUBEMAP_LAYOUT_LINE_VERTICAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_LINE_HORIZONTAL", CUBEMAP_LAYOUT_LINE_HORIZONTAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR", CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE", CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CubemapLayout", "CUBEMAP_LAYOUT_PANORAMA", CUBEMAP_LAYOUT_PANORAMA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\FontType", "FONT_DEFAULT", FONT_DEFAULT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\FontType", "FONT_BITMAP", FONT_BITMAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\FontType", "FONT_SDF", FONT_SDF, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_ALPHA", BLEND_ALPHA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_ADDITIVE", BLEND_ADDITIVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_MULTIPLIED", BLEND_MULTIPLIED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_ADD_COLORS", BLEND_ADD_COLORS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_SUBTRACT_COLORS", BLEND_SUBTRACT_COLORS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_ALPHA_PREMULTIPLY", BLEND_ALPHA_PREMULTIPLY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_CUSTOM", BLEND_CUSTOM, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\BlendMode", "BLEND_CUSTOM_SEPARATE", BLEND_CUSTOM_SEPARATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_NONE", GESTURE_NONE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_TAP", GESTURE_TAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_DOUBLETAP", GESTURE_DOUBLETAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_HOLD", GESTURE_HOLD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_DRAG", GESTURE_DRAG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_SWIPE_RIGHT", GESTURE_SWIPE_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_SWIPE_LEFT", GESTURE_SWIPE_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_SWIPE_UP", GESTURE_SWIPE_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_SWIPE_DOWN", GESTURE_SWIPE_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_PINCH_IN", GESTURE_PINCH_IN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Gesture", "GESTURE_PINCH_OUT", GESTURE_PINCH_OUT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraMode", "CAMERA_CUSTOM", CAMERA_CUSTOM, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraMode", "CAMERA_FREE", CAMERA_FREE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraMode", "CAMERA_ORBITAL", CAMERA_ORBITAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraMode", "CAMERA_FIRST_PERSON", CAMERA_FIRST_PERSON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraMode", "CAMERA_THIRD_PERSON", CAMERA_THIRD_PERSON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraProjection", "CAMERA_PERSPECTIVE", CAMERA_PERSPECTIVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\CameraProjection", "CAMERA_ORTHOGRAPHIC", CAMERA_ORTHOGRAPHIC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\NPatchLayout", "NPATCH_NINE_PATCH", NPATCH_NINE_PATCH, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\NPatchLayout", "NPATCH_THREE_PATCH_VERTICAL", NPATCH_THREE_PATCH_VERTICAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\NPatchLayout", "NPATCH_THREE_PATCH_HORIZONTAL", NPATCH_THREE_PATCH_HORIZONTAL, CONST_CS | CONST_PERSISTENT);

    return SUCCESS;
} /* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(raylib)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(raylib)
{
#if defined(COMPILE_DL_RAYLIB) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(raylib)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(raylib)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "raylib support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */
/* {{{ raylib_functions[]
 *
 * Every user visible function must have an entry in raylib_functions[].
 */
const zend_function_entry raylib_functions[] = {
        ZEND_NS_FE("raylib", confirm_raylib_compiled, arginfo_confirm_raylib_compiled)
        // Misc. functions
        ZEND_FE(InitWindow, arginfo_InitWindow)
        ZEND_FE(WindowShouldClose, arginfo_WindowShouldClose)
        ZEND_FE(CloseWindow, arginfo_CloseWindow)
        ZEND_FE(IsWindowReady, arginfo_IsWindowReady)
        ZEND_FE(IsWindowFullscreen, arginfo_IsWindowFullscreen)
        ZEND_FE(IsWindowHidden, arginfo_IsWindowHidden)
        ZEND_FE(IsWindowMinimized, arginfo_IsWindowMinimized)
        ZEND_FE(IsWindowMaximized, arginfo_IsWindowMaximized)
        ZEND_FE(IsWindowFocused, arginfo_IsWindowFocused)
        ZEND_FE(IsWindowResized, arginfo_IsWindowResized)
        ZEND_FE(IsWindowState, arginfo_IsWindowState)
        ZEND_FE(SetWindowState, arginfo_SetWindowState)
        ZEND_FE(ClearWindowState, arginfo_ClearWindowState)
        ZEND_FE(ToggleFullscreen, arginfo_ToggleFullscreen)
        ZEND_FE(MaximizeWindow, arginfo_MaximizeWindow)
        ZEND_FE(MinimizeWindow, arginfo_MinimizeWindow)
        ZEND_FE(RestoreWindow, arginfo_RestoreWindow)
        ZEND_FE(SetWindowIcon, arginfo_SetWindowIcon)
        ZEND_FE(SetWindowIcons, arginfo_SetWindowIcons)
        ZEND_FE(SetWindowTitle, arginfo_SetWindowTitle)
        ZEND_FE(SetWindowPosition, arginfo_SetWindowPosition)
        ZEND_FE(SetWindowMonitor, arginfo_SetWindowMonitor)
        ZEND_FE(SetWindowMinSize, arginfo_SetWindowMinSize)
        ZEND_FE(SetWindowSize, arginfo_SetWindowSize)
        ZEND_FE(GetScreenWidth, arginfo_GetScreenWidth)
        ZEND_FE(GetScreenHeight, arginfo_GetScreenHeight)
        ZEND_FE(GetMonitorCount, arginfo_GetMonitorCount)
        ZEND_FE(GetCurrentMonitor, arginfo_GetCurrentMonitor)
        ZEND_FE(GetMonitorPosition, arginfo_GetMonitorPosition)
        ZEND_FE(GetMonitorWidth, arginfo_GetMonitorWidth)
        ZEND_FE(GetMonitorHeight, arginfo_GetMonitorHeight)
        ZEND_FE(GetMonitorPhysicalWidth, arginfo_GetMonitorPhysicalWidth)
        ZEND_FE(GetMonitorPhysicalHeight, arginfo_GetMonitorPhysicalHeight)
        ZEND_FE(GetMonitorRefreshRate, arginfo_GetMonitorRefreshRate)
        ZEND_FE(GetWindowPosition, arginfo_GetWindowPosition)
        ZEND_FE(GetWindowScaleDPI, arginfo_GetWindowScaleDPI)
        ZEND_FE(SetClipboardText, arginfo_SetClipboardText)
        ZEND_FE(EnableEventWaiting, arginfo_EnableEventWaiting)
        ZEND_FE(DisableEventWaiting, arginfo_DisableEventWaiting)
        ZEND_FE(SwapScreenBuffer, arginfo_SwapScreenBuffer)
        ZEND_FE(PollInputEvents, arginfo_PollInputEvents)
        ZEND_FE(WaitTime, arginfo_WaitTime)
        ZEND_FE(ShowCursor, arginfo_ShowCursor)
        ZEND_FE(HideCursor, arginfo_HideCursor)
        ZEND_FE(IsCursorHidden, arginfo_IsCursorHidden)
        ZEND_FE(EnableCursor, arginfo_EnableCursor)
        ZEND_FE(DisableCursor, arginfo_DisableCursor)
        ZEND_FE(IsCursorOnScreen, arginfo_IsCursorOnScreen)
        ZEND_FE(ClearBackground, arginfo_ClearBackground)
        ZEND_FE(BeginDrawing, arginfo_BeginDrawing)
        ZEND_FE(EndDrawing, arginfo_EndDrawing)
        ZEND_FE(BeginMode2D, arginfo_BeginMode2D)
        ZEND_FE(EndMode2D, arginfo_EndMode2D)
        ZEND_FE(BeginMode3D, arginfo_BeginMode3D)
        ZEND_FE(EndMode3D, arginfo_EndMode3D)
        ZEND_FE(BeginTextureMode, arginfo_BeginTextureMode)
        ZEND_FE(EndTextureMode, arginfo_EndTextureMode)
        ZEND_FE(BeginShaderMode, arginfo_BeginShaderMode)
        ZEND_FE(EndShaderMode, arginfo_EndShaderMode)
        ZEND_FE(BeginBlendMode, arginfo_BeginBlendMode)
        ZEND_FE(EndBlendMode, arginfo_EndBlendMode)
        ZEND_FE(BeginScissorMode, arginfo_BeginScissorMode)
        ZEND_FE(EndScissorMode, arginfo_EndScissorMode)
        ZEND_FE(BeginVrStereoMode, arginfo_BeginVrStereoMode)
        ZEND_FE(EndVrStereoMode, arginfo_EndVrStereoMode)
        ZEND_FE(LoadVrStereoConfig, arginfo_LoadVrStereoConfig)
        ZEND_FE(UnloadVrStereoConfig, arginfo_UnloadVrStereoConfig)
        ZEND_FE(LoadShader, arginfo_LoadShader)
        ZEND_FE(LoadShaderFromMemory, arginfo_LoadShaderFromMemory)
        ZEND_FE(IsShaderReady, arginfo_IsShaderReady)
        ZEND_FE(GetShaderLocation, arginfo_GetShaderLocation)
        ZEND_FE(GetShaderLocationAttrib, arginfo_GetShaderLocationAttrib)
        ZEND_FE(SetShaderValueMatrix, arginfo_SetShaderValueMatrix)
        ZEND_FE(SetShaderValueTexture, arginfo_SetShaderValueTexture)
        ZEND_FE(UnloadShader, arginfo_UnloadShader)
        ZEND_FE(GetMouseRay, arginfo_GetMouseRay)
        ZEND_FE(GetCameraMatrix, arginfo_GetCameraMatrix)
        ZEND_FE(GetCameraMatrix2D, arginfo_GetCameraMatrix2D)
        ZEND_FE(GetWorldToScreen, arginfo_GetWorldToScreen)
        ZEND_FE(GetScreenToWorld2D, arginfo_GetScreenToWorld2D)
        ZEND_FE(GetWorldToScreenEx, arginfo_GetWorldToScreenEx)
        ZEND_FE(GetWorldToScreen2D, arginfo_GetWorldToScreen2D)
        ZEND_FE(SetTargetFPS, arginfo_SetTargetFPS)
        ZEND_FE(GetFPS, arginfo_GetFPS)
        ZEND_FE(GetFrameTime, arginfo_GetFrameTime)
        ZEND_FE(GetTime, arginfo_GetTime)
        ZEND_FE(GetRandomValue, arginfo_GetRandomValue)
        ZEND_FE(SetRandomSeed, arginfo_SetRandomSeed)
        ZEND_FE(TakeScreenshot, arginfo_TakeScreenshot)
        ZEND_FE(SetConfigFlags, arginfo_SetConfigFlags)
        ZEND_FE(SetTraceLogLevel, arginfo_SetTraceLogLevel)
        ZEND_FE(OpenURL, arginfo_OpenURL)
        ZEND_FE(ExportDataAsCode, arginfo_ExportDataAsCode)
        ZEND_FE(UnloadFileText, arginfo_UnloadFileText)
        ZEND_FE(SaveFileText, arginfo_SaveFileText)
        ZEND_FE(FileExists, arginfo_FileExists)
        ZEND_FE(DirectoryExists, arginfo_DirectoryExists)
        ZEND_FE(IsFileExtension, arginfo_IsFileExtension)
        ZEND_FE(GetFileLength, arginfo_GetFileLength)
        ZEND_FE(ChangeDirectory, arginfo_ChangeDirectory)
        ZEND_FE(IsPathFile, arginfo_IsPathFile)
        ZEND_FE(LoadDirectoryFiles, arginfo_LoadDirectoryFiles)
        ZEND_FE(LoadDirectoryFilesEx, arginfo_LoadDirectoryFilesEx)
        ZEND_FE(UnloadDirectoryFiles, arginfo_UnloadDirectoryFiles)
        ZEND_FE(IsFileDropped, arginfo_IsFileDropped)
        ZEND_FE(LoadDroppedFiles, arginfo_LoadDroppedFiles)
        ZEND_FE(UnloadDroppedFiles, arginfo_UnloadDroppedFiles)
        ZEND_FE(GetFileModTime, arginfo_GetFileModTime)
        ZEND_FE(IsKeyPressed, arginfo_IsKeyPressed)
        ZEND_FE(IsKeyDown, arginfo_IsKeyDown)
        ZEND_FE(IsKeyReleased, arginfo_IsKeyReleased)
        ZEND_FE(IsKeyUp, arginfo_IsKeyUp)
        ZEND_FE(SetExitKey, arginfo_SetExitKey)
        ZEND_FE(GetKeyPressed, arginfo_GetKeyPressed)
        ZEND_FE(GetCharPressed, arginfo_GetCharPressed)
        ZEND_FE(IsGamepadAvailable, arginfo_IsGamepadAvailable)
        ZEND_FE(IsGamepadButtonPressed, arginfo_IsGamepadButtonPressed)
        ZEND_FE(IsGamepadButtonDown, arginfo_IsGamepadButtonDown)
        ZEND_FE(IsGamepadButtonReleased, arginfo_IsGamepadButtonReleased)
        ZEND_FE(IsGamepadButtonUp, arginfo_IsGamepadButtonUp)
        ZEND_FE(GetGamepadButtonPressed, arginfo_GetGamepadButtonPressed)
        ZEND_FE(GetGamepadAxisCount, arginfo_GetGamepadAxisCount)
        ZEND_FE(GetGamepadAxisMovement, arginfo_GetGamepadAxisMovement)
        ZEND_FE(SetGamepadMappings, arginfo_SetGamepadMappings)
        ZEND_FE(IsMouseButtonPressed, arginfo_IsMouseButtonPressed)
        ZEND_FE(IsMouseButtonDown, arginfo_IsMouseButtonDown)
        ZEND_FE(IsMouseButtonReleased, arginfo_IsMouseButtonReleased)
        ZEND_FE(IsMouseButtonUp, arginfo_IsMouseButtonUp)
        ZEND_FE(GetMouseX, arginfo_GetMouseX)
        ZEND_FE(GetMouseY, arginfo_GetMouseY)
        ZEND_FE(GetMousePosition, arginfo_GetMousePosition)
        ZEND_FE(GetMouseDelta, arginfo_GetMouseDelta)
        ZEND_FE(SetMousePosition, arginfo_SetMousePosition)
        ZEND_FE(SetMouseOffset, arginfo_SetMouseOffset)
        ZEND_FE(SetMouseScale, arginfo_SetMouseScale)
        ZEND_FE(GetMouseWheelMove, arginfo_GetMouseWheelMove)
        ZEND_FE(GetMouseWheelMoveV, arginfo_GetMouseWheelMoveV)
        ZEND_FE(SetMouseCursor, arginfo_SetMouseCursor)
        ZEND_FE(GetTouchX, arginfo_GetTouchX)
        ZEND_FE(GetTouchY, arginfo_GetTouchY)
        ZEND_FE(GetTouchPosition, arginfo_GetTouchPosition)
        ZEND_FE(GetTouchPointId, arginfo_GetTouchPointId)
        ZEND_FE(GetTouchPointCount, arginfo_GetTouchPointCount)
        ZEND_FE(SetGesturesEnabled, arginfo_SetGesturesEnabled)
        ZEND_FE(IsGestureDetected, arginfo_IsGestureDetected)
        ZEND_FE(GetGestureDetected, arginfo_GetGestureDetected)
        ZEND_FE(GetGestureHoldDuration, arginfo_GetGestureHoldDuration)
        ZEND_FE(GetGestureDragVector, arginfo_GetGestureDragVector)
        ZEND_FE(GetGestureDragAngle, arginfo_GetGestureDragAngle)
        ZEND_FE(GetGesturePinchVector, arginfo_GetGesturePinchVector)
        ZEND_FE(GetGesturePinchAngle, arginfo_GetGesturePinchAngle)
        ZEND_FE(UpdateCamera, arginfo_UpdateCamera)
        ZEND_FE(UpdateCameraPro, arginfo_UpdateCameraPro)
        ZEND_FE(SetShapesTexture, arginfo_SetShapesTexture)
        ZEND_FE(DrawPixel, arginfo_DrawPixel)
        ZEND_FE(DrawPixelV, arginfo_DrawPixelV)
        ZEND_FE(DrawLine, arginfo_DrawLine)
        ZEND_FE(DrawLineV, arginfo_DrawLineV)
        ZEND_FE(DrawLineEx, arginfo_DrawLineEx)
        ZEND_FE(DrawLineBezier, arginfo_DrawLineBezier)
        ZEND_FE(DrawLineBezierQuad, arginfo_DrawLineBezierQuad)
        ZEND_FE(DrawLineBezierCubic, arginfo_DrawLineBezierCubic)
        ZEND_FE(DrawLineStrip, arginfo_DrawLineStrip)
        ZEND_FE(DrawCircle, arginfo_DrawCircle)
        ZEND_FE(DrawCircleSector, arginfo_DrawCircleSector)
        ZEND_FE(DrawCircleSectorLines, arginfo_DrawCircleSectorLines)
        ZEND_FE(DrawCircleGradient, arginfo_DrawCircleGradient)
        ZEND_FE(DrawCircleV, arginfo_DrawCircleV)
        ZEND_FE(DrawCircleLines, arginfo_DrawCircleLines)
        ZEND_FE(DrawEllipse, arginfo_DrawEllipse)
        ZEND_FE(DrawEllipseLines, arginfo_DrawEllipseLines)
        ZEND_FE(DrawRing, arginfo_DrawRing)
        ZEND_FE(DrawRingLines, arginfo_DrawRingLines)
        ZEND_FE(DrawRectangle, arginfo_DrawRectangle)
        ZEND_FE(DrawRectangleV, arginfo_DrawRectangleV)
        ZEND_FE(DrawRectangleRec, arginfo_DrawRectangleRec)
        ZEND_FE(DrawRectanglePro, arginfo_DrawRectanglePro)
        ZEND_FE(DrawRectangleGradientV, arginfo_DrawRectangleGradientV)
        ZEND_FE(DrawRectangleGradientH, arginfo_DrawRectangleGradientH)
        ZEND_FE(DrawRectangleGradientEx, arginfo_DrawRectangleGradientEx)
        ZEND_FE(DrawRectangleLines, arginfo_DrawRectangleLines)
        ZEND_FE(DrawRectangleLinesEx, arginfo_DrawRectangleLinesEx)
        ZEND_FE(DrawRectangleRounded, arginfo_DrawRectangleRounded)
        ZEND_FE(DrawRectangleRoundedLines, arginfo_DrawRectangleRoundedLines)
        ZEND_FE(DrawTriangle, arginfo_DrawTriangle)
        ZEND_FE(DrawTriangleLines, arginfo_DrawTriangleLines)
        ZEND_FE(DrawTriangleFan, arginfo_DrawTriangleFan)
        ZEND_FE(DrawTriangleStrip, arginfo_DrawTriangleStrip)
        ZEND_FE(DrawPoly, arginfo_DrawPoly)
        ZEND_FE(DrawPolyLines, arginfo_DrawPolyLines)
        ZEND_FE(DrawPolyLinesEx, arginfo_DrawPolyLinesEx)
        ZEND_FE(CheckCollisionRecs, arginfo_CheckCollisionRecs)
        ZEND_FE(CheckCollisionCircles, arginfo_CheckCollisionCircles)
        ZEND_FE(CheckCollisionCircleRec, arginfo_CheckCollisionCircleRec)
        ZEND_FE(CheckCollisionPointRec, arginfo_CheckCollisionPointRec)
        ZEND_FE(CheckCollisionPointCircle, arginfo_CheckCollisionPointCircle)
        ZEND_FE(CheckCollisionPointTriangle, arginfo_CheckCollisionPointTriangle)
        ZEND_FE(CheckCollisionPointPoly, arginfo_CheckCollisionPointPoly)
        ZEND_FE(CheckCollisionLines, arginfo_CheckCollisionLines)
        ZEND_FE(CheckCollisionPointLine, arginfo_CheckCollisionPointLine)
        ZEND_FE(GetCollisionRec, arginfo_GetCollisionRec)
        ZEND_FE(LoadImage, arginfo_LoadImage)
        ZEND_FE(LoadImageRaw, arginfo_LoadImageRaw)
        ZEND_FE(LoadImageAnim, arginfo_LoadImageAnim)
        ZEND_FE(LoadImageFromMemory, arginfo_LoadImageFromMemory)
        ZEND_FE(LoadImageFromTexture, arginfo_LoadImageFromTexture)
        ZEND_FE(LoadImageFromScreen, arginfo_LoadImageFromScreen)
        ZEND_FE(IsImageReady, arginfo_IsImageReady)
        ZEND_FE(UnloadImage, arginfo_UnloadImage)
        ZEND_FE(ExportImage, arginfo_ExportImage)
        ZEND_FE(ExportImageAsCode, arginfo_ExportImageAsCode)
        ZEND_FE(GenImageColor, arginfo_GenImageColor)
        ZEND_FE(GenImageGradientV, arginfo_GenImageGradientV)
        ZEND_FE(GenImageGradientH, arginfo_GenImageGradientH)
        ZEND_FE(GenImageGradientRadial, arginfo_GenImageGradientRadial)
        ZEND_FE(GenImageChecked, arginfo_GenImageChecked)
        ZEND_FE(GenImageWhiteNoise, arginfo_GenImageWhiteNoise)
        ZEND_FE(GenImagePerlinNoise, arginfo_GenImagePerlinNoise)
        ZEND_FE(GenImageCellular, arginfo_GenImageCellular)
        ZEND_FE(GenImageText, arginfo_GenImageText)
        ZEND_FE(rlImageCopy, arginfo_rlImageCopy)
        ZEND_FE(ImageFromImage, arginfo_ImageFromImage)
        ZEND_FE(ImageText, arginfo_ImageText)
        ZEND_FE(ImageTextEx, arginfo_ImageTextEx)
        ZEND_FE(ImageFormat, arginfo_ImageFormat)
        ZEND_FE(ImageToPOT, arginfo_ImageToPOT)
        ZEND_FE(rlImageCrop, arginfo_rlImageCrop)
        ZEND_FE(ImageAlphaCrop, arginfo_ImageAlphaCrop)
        ZEND_FE(ImageAlphaClear, arginfo_ImageAlphaClear)
        ZEND_FE(ImageAlphaMask, arginfo_ImageAlphaMask)
        ZEND_FE(ImageAlphaPremultiply, arginfo_ImageAlphaPremultiply)
        ZEND_FE(ImageBlurGaussian, arginfo_ImageBlurGaussian)
        ZEND_FE(ImageResize, arginfo_ImageResize)
        ZEND_FE(ImageResizeNN, arginfo_ImageResizeNN)
        ZEND_FE(ImageResizeCanvas, arginfo_ImageResizeCanvas)
        ZEND_FE(ImageMipmaps, arginfo_ImageMipmaps)
        ZEND_FE(ImageDither, arginfo_ImageDither)
        ZEND_FE(ImageFlipVertical, arginfo_ImageFlipVertical)
        ZEND_FE(ImageFlipHorizontal, arginfo_ImageFlipHorizontal)
        ZEND_FE(ImageRotateCW, arginfo_ImageRotateCW)
        ZEND_FE(ImageRotateCCW, arginfo_ImageRotateCCW)
        ZEND_FE(ImageColorTint, arginfo_ImageColorTint)
        ZEND_FE(ImageColorInvert, arginfo_ImageColorInvert)
        ZEND_FE(ImageColorGrayscale, arginfo_ImageColorGrayscale)
        ZEND_FE(ImageColorContrast, arginfo_ImageColorContrast)
        ZEND_FE(ImageColorBrightness, arginfo_ImageColorBrightness)
        ZEND_FE(ImageColorReplace, arginfo_ImageColorReplace)
        ZEND_FE(UnloadImageColors, arginfo_UnloadImageColors)
        ZEND_FE(UnloadImagePalette, arginfo_UnloadImagePalette)
        ZEND_FE(GetImageAlphaBorder, arginfo_GetImageAlphaBorder)
        ZEND_FE(GetImageColor, arginfo_GetImageColor)
        ZEND_FE(ImageClearBackground, arginfo_ImageClearBackground)
        ZEND_FE(ImageDrawPixel, arginfo_ImageDrawPixel)
        ZEND_FE(ImageDrawPixelV, arginfo_ImageDrawPixelV)
        ZEND_FE(ImageDrawLine, arginfo_ImageDrawLine)
        ZEND_FE(ImageDrawLineV, arginfo_ImageDrawLineV)
        ZEND_FE(ImageDrawCircle, arginfo_ImageDrawCircle)
        ZEND_FE(ImageDrawCircleV, arginfo_ImageDrawCircleV)
        ZEND_FE(ImageDrawCircleLines, arginfo_ImageDrawCircleLines)
        ZEND_FE(ImageDrawCircleLinesV, arginfo_ImageDrawCircleLinesV)
        ZEND_FE(ImageDrawRectangle, arginfo_ImageDrawRectangle)
        ZEND_FE(ImageDrawRectangleV, arginfo_ImageDrawRectangleV)
        ZEND_FE(ImageDrawRectangleRec, arginfo_ImageDrawRectangleRec)
        ZEND_FE(ImageDrawRectangleLines, arginfo_ImageDrawRectangleLines)
        ZEND_FE(ImageDraw, arginfo_ImageDraw)
        ZEND_FE(ImageDrawText, arginfo_ImageDrawText)
        ZEND_FE(ImageDrawTextEx, arginfo_ImageDrawTextEx)
        ZEND_FE(LoadTexture, arginfo_LoadTexture)
        ZEND_FE(LoadTextureFromImage, arginfo_LoadTextureFromImage)
        ZEND_FE(LoadTextureCubemap, arginfo_LoadTextureCubemap)
        ZEND_FE(LoadRenderTexture, arginfo_LoadRenderTexture)
        ZEND_FE(IsTextureReady, arginfo_IsTextureReady)
        ZEND_FE(UnloadTexture, arginfo_UnloadTexture)
        ZEND_FE(IsRenderTextureReady, arginfo_IsRenderTextureReady)
        ZEND_FE(UnloadRenderTexture, arginfo_UnloadRenderTexture)
        ZEND_FE(GenTextureMipmaps, arginfo_GenTextureMipmaps)
        ZEND_FE(SetTextureFilter, arginfo_SetTextureFilter)
        ZEND_FE(SetTextureWrap, arginfo_SetTextureWrap)
        ZEND_FE(DrawTexture, arginfo_DrawTexture)
        ZEND_FE(DrawTextureV, arginfo_DrawTextureV)
        ZEND_FE(DrawTextureEx, arginfo_DrawTextureEx)
        ZEND_FE(DrawTextureRec, arginfo_DrawTextureRec)
        ZEND_FE(DrawTexturePro, arginfo_DrawTexturePro)
        ZEND_FE(DrawTextureNPatch, arginfo_DrawTextureNPatch)
        ZEND_FE(Fade, arginfo_Fade)
        ZEND_FE(ColorToInt, arginfo_ColorToInt)
        ZEND_FE(ColorNormalize, arginfo_ColorNormalize)
        ZEND_FE(ColorFromNormalized, arginfo_ColorFromNormalized)
        ZEND_FE(ColorToHSV, arginfo_ColorToHSV)
        ZEND_FE(ColorFromHSV, arginfo_ColorFromHSV)
        ZEND_FE(ColorTint, arginfo_ColorTint)
        ZEND_FE(ColorBrightness, arginfo_ColorBrightness)
        ZEND_FE(ColorContrast, arginfo_ColorContrast)
        ZEND_FE(ColorAlpha, arginfo_ColorAlpha)
        ZEND_FE(ColorAlphaBlend, arginfo_ColorAlphaBlend)
        ZEND_FE(GetColor, arginfo_GetColor)
        ZEND_FE(GetPixelDataSize, arginfo_GetPixelDataSize)
        ZEND_FE(GetFontDefault, arginfo_GetFontDefault)
        ZEND_FE(LoadFont, arginfo_LoadFont)
        ZEND_FE(LoadFontEx, arginfo_LoadFontEx)
        ZEND_FE(LoadFontFromImage, arginfo_LoadFontFromImage)
        ZEND_FE(LoadFontFromMemory, arginfo_LoadFontFromMemory)
        ZEND_FE(IsFontReady, arginfo_IsFontReady)
        ZEND_FE(UnloadFontData, arginfo_UnloadFontData)
        ZEND_FE(UnloadFont, arginfo_UnloadFont)
        ZEND_FE(ExportFontAsCode, arginfo_ExportFontAsCode)
        ZEND_FE(DrawFPS, arginfo_DrawFPS)
        ZEND_FE(DrawText, arginfo_DrawText)
        ZEND_FE(DrawTextEx, arginfo_DrawTextEx)
        ZEND_FE(DrawTextPro, arginfo_DrawTextPro)
        ZEND_FE(DrawTextCodepoint, arginfo_DrawTextCodepoint)
        ZEND_FE(DrawTextCodepoints, arginfo_DrawTextCodepoints)
        ZEND_FE(MeasureText, arginfo_MeasureText)
        ZEND_FE(MeasureTextEx, arginfo_MeasureTextEx)
        ZEND_FE(GetGlyphIndex, arginfo_GetGlyphIndex)
        ZEND_FE(GetGlyphInfo, arginfo_GetGlyphInfo)
        ZEND_FE(GetGlyphAtlasRec, arginfo_GetGlyphAtlasRec)
        ZEND_FE(UnloadUTF8, arginfo_UnloadUTF8)
        ZEND_FE(UnloadCodepoints, arginfo_UnloadCodepoints)
        ZEND_FE(GetCodepointCount, arginfo_GetCodepointCount)
        ZEND_FE(GetCodepoint, arginfo_GetCodepoint)
        ZEND_FE(GetCodepointNext, arginfo_GetCodepointNext)
        ZEND_FE(GetCodepointPrevious, arginfo_GetCodepointPrevious)
        ZEND_FE(TextCopy, arginfo_TextCopy)
        ZEND_FE(TextIsEqual, arginfo_TextIsEqual)
        ZEND_FE(TextLength, arginfo_TextLength)
        ZEND_FE(TextAppend, arginfo_TextAppend)
        ZEND_FE(TextFindIndex, arginfo_TextFindIndex)
        ZEND_FE(TextToInteger, arginfo_TextToInteger)
        ZEND_FE(DrawLine3D, arginfo_DrawLine3D)
        ZEND_FE(DrawPoint3D, arginfo_DrawPoint3D)
        ZEND_FE(DrawCircle3D, arginfo_DrawCircle3D)
        ZEND_FE(DrawTriangle3D, arginfo_DrawTriangle3D)
        ZEND_FE(DrawTriangleStrip3D, arginfo_DrawTriangleStrip3D)
        ZEND_FE(DrawCube, arginfo_DrawCube)
        ZEND_FE(DrawCubeV, arginfo_DrawCubeV)
        ZEND_FE(DrawCubeWires, arginfo_DrawCubeWires)
        ZEND_FE(DrawCubeWiresV, arginfo_DrawCubeWiresV)
        ZEND_FE(DrawSphere, arginfo_DrawSphere)
        ZEND_FE(DrawSphereEx, arginfo_DrawSphereEx)
        ZEND_FE(DrawSphereWires, arginfo_DrawSphereWires)
        ZEND_FE(DrawCylinder, arginfo_DrawCylinder)
        ZEND_FE(DrawCylinderEx, arginfo_DrawCylinderEx)
        ZEND_FE(DrawCylinderWires, arginfo_DrawCylinderWires)
        ZEND_FE(DrawCylinderWiresEx, arginfo_DrawCylinderWiresEx)
        ZEND_FE(DrawCapsule, arginfo_DrawCapsule)
        ZEND_FE(DrawCapsuleWires, arginfo_DrawCapsuleWires)
        ZEND_FE(DrawPlane, arginfo_DrawPlane)
        ZEND_FE(DrawRay, arginfo_DrawRay)
        ZEND_FE(DrawGrid, arginfo_DrawGrid)
        ZEND_FE(LoadModel, arginfo_LoadModel)
        ZEND_FE(LoadModelFromMesh, arginfo_LoadModelFromMesh)
        ZEND_FE(IsModelReady, arginfo_IsModelReady)
        ZEND_FE(UnloadModel, arginfo_UnloadModel)
        ZEND_FE(GetModelBoundingBox, arginfo_GetModelBoundingBox)
        ZEND_FE(DrawModel, arginfo_DrawModel)
        ZEND_FE(DrawModelEx, arginfo_DrawModelEx)
        ZEND_FE(DrawModelWires, arginfo_DrawModelWires)
        ZEND_FE(DrawModelWiresEx, arginfo_DrawModelWiresEx)
        ZEND_FE(DrawBoundingBox, arginfo_DrawBoundingBox)
        ZEND_FE(DrawBillboard, arginfo_DrawBillboard)
        ZEND_FE(DrawBillboardRec, arginfo_DrawBillboardRec)
        ZEND_FE(DrawBillboardPro, arginfo_DrawBillboardPro)
        ZEND_FE(UploadMesh, arginfo_UploadMesh)
        ZEND_FE(UnloadMesh, arginfo_UnloadMesh)
        ZEND_FE(DrawMesh, arginfo_DrawMesh)
        ZEND_FE(DrawMeshInstanced, arginfo_DrawMeshInstanced)
        ZEND_FE(ExportMesh, arginfo_ExportMesh)
        ZEND_FE(GetMeshBoundingBox, arginfo_GetMeshBoundingBox)
        ZEND_FE(GenMeshTangents, arginfo_GenMeshTangents)
        ZEND_FE(GenMeshPoly, arginfo_GenMeshPoly)
        ZEND_FE(GenMeshPlane, arginfo_GenMeshPlane)
        ZEND_FE(GenMeshCube, arginfo_GenMeshCube)
        ZEND_FE(GenMeshSphere, arginfo_GenMeshSphere)
        ZEND_FE(GenMeshHemiSphere, arginfo_GenMeshHemiSphere)
        ZEND_FE(GenMeshCylinder, arginfo_GenMeshCylinder)
        ZEND_FE(GenMeshCone, arginfo_GenMeshCone)
        ZEND_FE(GenMeshTorus, arginfo_GenMeshTorus)
        ZEND_FE(GenMeshKnot, arginfo_GenMeshKnot)
        ZEND_FE(GenMeshHeightmap, arginfo_GenMeshHeightmap)
        ZEND_FE(GenMeshCubicmap, arginfo_GenMeshCubicmap)
        ZEND_FE(LoadMaterialDefault, arginfo_LoadMaterialDefault)
        ZEND_FE(IsMaterialReady, arginfo_IsMaterialReady)
        ZEND_FE(UnloadMaterial, arginfo_UnloadMaterial)
        ZEND_FE(SetMaterialTexture, arginfo_SetMaterialTexture)
        ZEND_FE(SetModelMeshMaterial, arginfo_SetModelMeshMaterial)
        ZEND_FE(LoadModelAnimations, arginfo_LoadModelAnimations)
        ZEND_FE(UpdateModelAnimation, arginfo_UpdateModelAnimation)
        ZEND_FE(UnloadModelAnimation, arginfo_UnloadModelAnimation)
        ZEND_FE(UnloadModelAnimations, arginfo_UnloadModelAnimations)
        ZEND_FE(IsModelAnimationValid, arginfo_IsModelAnimationValid)
        ZEND_FE(CheckCollisionSpheres, arginfo_CheckCollisionSpheres)
        ZEND_FE(CheckCollisionBoxes, arginfo_CheckCollisionBoxes)
        ZEND_FE(CheckCollisionBoxSphere, arginfo_CheckCollisionBoxSphere)
        ZEND_FE(GetRayCollisionSphere, arginfo_GetRayCollisionSphere)
        ZEND_FE(GetRayCollisionBox, arginfo_GetRayCollisionBox)
        ZEND_FE(GetRayCollisionMesh, arginfo_GetRayCollisionMesh)
        ZEND_FE(GetRayCollisionTriangle, arginfo_GetRayCollisionTriangle)
        ZEND_FE(GetRayCollisionQuad, arginfo_GetRayCollisionQuad)
        ZEND_FE(InitAudioDevice, arginfo_InitAudioDevice)
        ZEND_FE(CloseAudioDevice, arginfo_CloseAudioDevice)
        ZEND_FE(IsAudioDeviceReady, arginfo_IsAudioDeviceReady)
        ZEND_FE(SetMasterVolume, arginfo_SetMasterVolume)
        ZEND_FE(LoadWave, arginfo_LoadWave)
        ZEND_FE(LoadWaveFromMemory, arginfo_LoadWaveFromMemory)
        ZEND_FE(IsWaveReady, arginfo_IsWaveReady)
        ZEND_FE(LoadSound, arginfo_LoadSound)
        ZEND_FE(LoadSoundFromWave, arginfo_LoadSoundFromWave)
        ZEND_FE(IsSoundReady, arginfo_IsSoundReady)
        ZEND_FE(UnloadWave, arginfo_UnloadWave)
        ZEND_FE(UnloadSound, arginfo_UnloadSound)
        ZEND_FE(ExportWave, arginfo_ExportWave)
        ZEND_FE(ExportWaveAsCode, arginfo_ExportWaveAsCode)
        ZEND_FE(PlaySound, arginfo_PlaySound)
        ZEND_FE(StopSound, arginfo_StopSound)
        ZEND_FE(PauseSound, arginfo_PauseSound)
        ZEND_FE(ResumeSound, arginfo_ResumeSound)
        ZEND_FE(IsSoundPlaying, arginfo_IsSoundPlaying)
        ZEND_FE(SetSoundVolume, arginfo_SetSoundVolume)
        ZEND_FE(SetSoundPitch, arginfo_SetSoundPitch)
        ZEND_FE(SetSoundPan, arginfo_SetSoundPan)
        ZEND_FE(WaveCopy, arginfo_WaveCopy)
        ZEND_FE(WaveCrop, arginfo_WaveCrop)
        ZEND_FE(WaveFormat, arginfo_WaveFormat)
        ZEND_FE(UnloadWaveSamples, arginfo_UnloadWaveSamples)
        ZEND_FE(LoadMusicStream, arginfo_LoadMusicStream)
        ZEND_FE(LoadMusicStreamFromMemory, arginfo_LoadMusicStreamFromMemory)
        ZEND_FE(IsMusicReady, arginfo_IsMusicReady)
        ZEND_FE(UnloadMusicStream, arginfo_UnloadMusicStream)
        ZEND_FE(PlayMusicStream, arginfo_PlayMusicStream)
        ZEND_FE(IsMusicStreamPlaying, arginfo_IsMusicStreamPlaying)
        ZEND_FE(UpdateMusicStream, arginfo_UpdateMusicStream)
        ZEND_FE(StopMusicStream, arginfo_StopMusicStream)
        ZEND_FE(PauseMusicStream, arginfo_PauseMusicStream)
        ZEND_FE(ResumeMusicStream, arginfo_ResumeMusicStream)
        ZEND_FE(SeekMusicStream, arginfo_SeekMusicStream)
        ZEND_FE(SetMusicVolume, arginfo_SetMusicVolume)
        ZEND_FE(SetMusicPitch, arginfo_SetMusicPitch)
        ZEND_FE(SetMusicPan, arginfo_SetMusicPan)
        ZEND_FE(GetMusicTimeLength, arginfo_GetMusicTimeLength)
        ZEND_FE(GetMusicTimePlayed, arginfo_GetMusicTimePlayed)
        ZEND_FE(LoadAudioStream, arginfo_LoadAudioStream)
        ZEND_FE(IsAudioStreamReady, arginfo_IsAudioStreamReady)
        ZEND_FE(UnloadAudioStream, arginfo_UnloadAudioStream)
        ZEND_FE(IsAudioStreamProcessed, arginfo_IsAudioStreamProcessed)
        ZEND_FE(PlayAudioStream, arginfo_PlayAudioStream)
        ZEND_FE(PauseAudioStream, arginfo_PauseAudioStream)
        ZEND_FE(ResumeAudioStream, arginfo_ResumeAudioStream)
        ZEND_FE(IsAudioStreamPlaying, arginfo_IsAudioStreamPlaying)
        ZEND_FE(StopAudioStream, arginfo_StopAudioStream)
        ZEND_FE(SetAudioStreamVolume, arginfo_SetAudioStreamVolume)
        ZEND_FE(SetAudioStreamPitch, arginfo_SetAudioStreamPitch)
        ZEND_FE(SetAudioStreamPan, arginfo_SetAudioStreamPan)
        ZEND_FE(SetAudioStreamBufferSizeDefault, arginfo_SetAudioStreamBufferSizeDefault)
        PHP_FE_END
};
/* }}} */
/* {{{ raylib_module_entry
 */
zend_module_entry raylib_module_entry = {
    STANDARD_MODULE_HEADER,
    "raylib",
    raylib_functions,
    PHP_MINIT(raylib),
    PHP_MSHUTDOWN(raylib),
    PHP_RINIT(raylib),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(raylib),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(raylib),
    PHP_RAYLIB_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_RAYLIB
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(raylib)
#endif
