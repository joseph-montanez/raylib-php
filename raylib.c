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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_raylib.h"
#include "raylib-vector4.h"
#include "raylib-vector3.h"
#include "raylib-vector2.h"
#include "raylib-rectangle.h"
#include "raylib-utils.h"
#include "raylib-image.h"
#include "raylib-texture.h"
#include "raylib-window.h"
#include "raylib-cursor.h"
#include "raylib-text.h"
#include "raylib-draw.h"
#include "raylib-rendertexture.h"
#include "raylib-camera3d.h"
#include "raylib-camera2d.h"
#include "raylib-timming.h"
#include "raylib-font.h"
#include "raylib-key.h"
#include "raylib-mouse.h"
#include "raylib-collision.h"
#include "raylib-color.h"
#include "raylib-gamepad.h"
#include "raylib-wave.h"
#include "raylib-audio.h"
#include "raylib-npatchinfo.h"
#include "raylib-charinfo.h"


#define RAYLIB_FLAG(name) "raylib\\flags\\" #name


static int le_link, le_plink, le_raylib_image, le_raylib_texture;


/* True global resources - no need for thread safety here */
static int le_raylib;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("raylib.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_raylib_globals, raylib_globals)
    STD_PHP_INI_ENTRY("raylib.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_raylib_globals, raylib_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_raylib_compiled(string arg)
   Return a string to confirm that the module is compiled in */
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

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard

//bool IsKeyPressed(int key);
PHP_FUNCTION(IsKeyPressed)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyPressed(zend_long_2int(key)));
}

//bool IsKeyDown(int key);
PHP_FUNCTION(IsKeyDown)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyDown(zend_long_2int(key)));
}

//bool IsKeyReleased(int key);
PHP_FUNCTION(IsKeyReleased)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyReleased(zend_long_2int(key)));
}

//bool IsKeyUp(int key);
PHP_FUNCTION(IsKeyUp)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsKeyUp(zend_long_2int(key)));
}

// Get key pressed (keycode), call it multiple times for keys queued
// int GetKeyPressed(void);
PHP_FUNCTION(getKeyPressed)
{
    RETURN_LONG(GetKeyPressed());
}

// Get char pressed (unicode), call it multiple times for chars queued
// RLAPI int GetCharPressed(void);
PHP_FUNCTION(getCharPressed)
{
    RETURN_LONG(GetCharPressed());
}

//void SetExitKey(void);
PHP_FUNCTION(SetExitKey)
{
    zend_long key;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(key)
    ZEND_PARSE_PARAMETERS_END();

    SetExitKey(zend_long_2int(key));
}

// Setup window configuration flags (view FLAGS)
// RLAPI void SetConfigFlags(unsigned int flags);
PHP_FUNCTION(SetConfigFlags)
{
    zend_long flags;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(flags)
    ZEND_PARSE_PARAMETERS_END();

    SetConfigFlags((int) flags);
}

// Takes a screenshot of current screen (saved a .png)
// RLAPI void TakeScreenshot(const char *fileName);
PHP_FUNCTION(TakeScreenshot)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    TakeScreenshot(fileName->val);
}

/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_raylib_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_raylib_init_globals(zend_raylib_globals *raylib_globals)
{
	raylib_globals->global_value = 0;
	raylib_globals->global_string = NULL;
}
*/
/* }}} */


/* {{{ raylib_image_dtor
 */
static void raylib_image_dtor(zend_resource *rsrc){
    if (rsrc->ptr != NULL) {
        Image *image = (Image *) rsrc->ptr;
        if (image != NULL && image->data != NULL) {
            UnloadImage(*image);
            // image.data is freed when unloaded we just need to handle the pointer
            free(image);
        }
        image = NULL;
    }
    rsrc->ptr = NULL;
}
/* }}} */

/* {{{ raylib_texture_dtor
 */
static void raylib_texture_dtor(zend_resource *rsrc){
    if (rsrc->ptr != NULL) {
        Texture2D *texture = (Texture2D *) rsrc->ptr;
        if (texture != NULL) {
            UnloadTexture(*texture);
            free(texture);
        }
        texture = NULL;
    }
    rsrc->ptr = NULL;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(raylib)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

    php_raylib_vector4_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vector3_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_vector2_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rectangle_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_image_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_texture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_window_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_cursor_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_text_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_draw_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera3d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_gamepad_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera2d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rendertexture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_timming_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_font_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_key_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_mouse_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_color_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_collision_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_wave_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_audio_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_npatchinfo_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_charinfo_startup(INIT_FUNC_ARGS_PASSTHRU);

    // raylib Config Flags
//    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "RESERVED", FLAG_RESERVED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "MSAA_4X_HINT", FLAG_MSAA_4X_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\Flags", "VSYNC_HINT", FLAG_VSYNC_HINT, CONST_CS | CONST_PERSISTENT);

    // Android Physical Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "BACK", KEY_BACK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "MENU", KEY_MENU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_UP", KEY_VOLUME_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_DOWN", KEY_VOLUME_DOWN, CONST_CS | CONST_PERSISTENT);

    // PixelFormat
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_GRAYSCALE", UNCOMPRESSED_GRAYSCALE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_GRAY_ALPHA", UNCOMPRESSED_GRAY_ALPHA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R5G6B5", UNCOMPRESSED_R5G6B5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R8G8B8", UNCOMPRESSED_R8G8B8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R5G5B5A1", UNCOMPRESSED_R5G5B5A1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R4G4B4A4", UNCOMPRESSED_R4G4B4A4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R8G8B8A8", UNCOMPRESSED_R8G8B8A8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R32", UNCOMPRESSED_R32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R32G32B32", UNCOMPRESSED_R32G32B32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "UNCOMPRESSED_R32G32B32A32", UNCOMPRESSED_R32G32B32A32, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_DXT1_RGB", COMPRESSED_DXT1_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_DXT1_RGBA", COMPRESSED_DXT1_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_DXT3_RGBA", COMPRESSED_DXT3_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_DXT5_RGBA", COMPRESSED_DXT5_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_ETC1_RGB", COMPRESSED_ETC1_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_ETC2_RGB", COMPRESSED_ETC2_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_ETC2_EAC_RGBA", COMPRESSED_ETC2_EAC_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_PVRT_RGB", COMPRESSED_PVRT_RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_PVRT_RGBA", COMPRESSED_PVRT_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_ASTC_4x4_RGBA", COMPRESSED_ASTC_4x4_RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\PixelFormat", "COMPRESSED_ASTC_8x8_RGBA", COMPRESSED_ASTC_8x8_RGBA, CONST_CS | CONST_PERSISTENT);

    // Touch points registered
    //REGISTER_NS_LONG_CONSTANT("raylib\\max", "TOUCH_POINTS", MAX_TOUCH_POINTS, CONST_CS | CONST_PERSISTENT);

    le_raylib_image = zend_register_list_destructors_ex(raylib_image_dtor, NULL, "RAYLIB_IMAGE_TYPE", module_number);
    le_raylib_texture = zend_register_list_destructors_ex(raylib_texture_dtor, NULL, "RAYLIB_TEXTURE_TYPE", module_number);
    // TODO: I need to add other objects here, that are pointers!
//    le_raylib_rectangle = zend_register_list_destructors_ex(raylib_rectangle_dtor, NULL, "RAYLIB_RECTANGLE_TYPE", module_number);
//    le_raylib_wave = zend_register_list_destructors_ex(raylib_wave_dtor, NULL, "RAYLIB_WAVE_TYPE", module_number);
//    le_raylib_vector2 = zend_register_list_destructors_ex(raylib_vector2_dtor, NULL, "RAYLIB_VECTOR2_TYPE", module_number);
//    le_raylib_vector3 = zend_register_list_destructors_ex(raylib_vector3_dtor, NULL, "RAYLIB_VECTOR3_TYPE", module_number);
//    le_raylib_vector4 = zend_register_list_destructors_ex(raylib_vector4_dtor, NULL, "RAYLIB_VECTOR4_TYPE", module_number);

    return SUCCESS;
}
/* }}} */

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
		ZEND_NS_FE("raylib", confirm_raylib_compiled, NULL)
        //------------------------------------------------------------------------------------
        // Input Handling Functions (Module: core)
        //------------------------------------------------------------------------------------
        // Input-related functions: keyboard
        ZEND_NS_FE("raylib", IsKeyPressed, NULL)
        ZEND_NS_FE("raylib", IsKeyDown, NULL)
        ZEND_NS_FE("raylib", IsKeyReleased, NULL)
        ZEND_NS_FE("raylib", IsKeyUp, NULL)
        ZEND_NS_FE("raylib", getKeyPressed, NULL)
        ZEND_NS_FE("raylib", getCharPressed, NULL)
        ZEND_NS_FE("raylib", SetExitKey, NULL)

        // Misc. functions
        ZEND_NS_FE("raylib", SetConfigFlags, NULL)
        ZEND_NS_FE("raylib", TakeScreenshot, NULL)
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
	PHP_RINIT(raylib),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(raylib),	/* Replace with NULL if there's nothing to do at request end */
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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
