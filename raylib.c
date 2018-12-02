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
	size_t arg_len, len;
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

//int GetKeyPressed(void);
PHP_FUNCTION(GetKeyPressed)
{
    RETURN_LONG(GetKeyPressed());
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

// Input-related functions: gamepads

//bool IsGamepadAvailable(int gamepad);
PHP_FUNCTION(IsGamepadAvailable)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadAvailable(zend_long_2int(gamepad)));
}

//bool IsGamepadName(int gamepad);
PHP_FUNCTION(IsGamepadName)
{
    zend_long gamepad;
    zend_string *name;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadName(zend_long_2int(gamepad), name->val));
}

//const char *GetGamepadName(int gamepad);
PHP_FUNCTION(GetGamepadName)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    const char *gamepadName = GetGamepadName(zend_long_2int(gamepad));
    zend_string *str = zend_string_init(gamepadName, sizeof(gamepadName)-1, 0);

    RETURN_STR(str);
}

//bool IsGamepadButtonPressed(int gamepad, int button);
PHP_FUNCTION(IsGamepadButtonPressed)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonPressed(zend_long_2int(gamepad), zend_long_2int(button)));
}

//bool IsGamepadButtonDown(int gamepad, int button);
PHP_FUNCTION(IsGamepadButtonDown)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonDown(zend_long_2int(gamepad), zend_long_2int(button)));
}

//bool IsGamepadButtonReleased(int gamepad, int button);
PHP_FUNCTION(IsGamepadButtonReleased)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonReleased(zend_long_2int(gamepad), zend_long_2int(button)));
}

//bool IsGamepadButtonUp(int gamepad, int button);
PHP_FUNCTION(IsGamepadButtonUp)
{
    zend_long gamepad;
    zend_long button;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_LONG(button)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(IsGamepadButtonUp(zend_long_2int(gamepad), zend_long_2int(button)));
}

//int GetGamepadButtonPressed(void);
PHP_FUNCTION(GetGamepadButtonPressed)
{
    RETURN_LONG(GetGamepadButtonPressed());
}

//int GetGamepadAxisCount(int gamepad);
PHP_FUNCTION(GetGamepadAxisCount)
{
    zend_long gamepad;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(gamepad)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(GetGamepadAxisCount(zend_long_2int(gamepad)));
}

//bool GetGamepadAxisMovement(int gamepad, int button);
PHP_FUNCTION(GetGamepadAxisMovement)
{
    zend_long gamepad;
    zend_long axis;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(gamepad)
            Z_PARAM_LONG(axis)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_DOUBLE(GetGamepadAxisMovement(zend_long_2int(gamepad), zend_long_2int(axis)));
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

    php_raylib_image_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_texture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_window_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_cursor_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_text_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_draw_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera3d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_camera2d_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_rendertexture_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_timming_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_font_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_key_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_mouse_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_color_startup(INIT_FUNC_ARGS_PASSTHRU);
    php_raylib_collision_startup(INIT_FUNC_ARGS_PASSTHRU);

    // raylib Config Flags
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "SHOW_LOGO", FLAG_SHOW_LOGO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "MSAA_4X_HINT", FLAG_MSAA_4X_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "FLAG_VSYNC_HINTLOGO", FLAG_VSYNC_HINT, CONST_CS | CONST_PERSISTENT);

    // Android Physical Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "BACK", KEY_BACK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "MENU", KEY_MENU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_UP", KEY_VOLUME_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_DOWN", KEY_VOLUME_DOWN, CONST_CS | CONST_PERSISTENT);

    // Touch points registered
    REGISTER_NS_LONG_CONSTANT("raylib\\max", "TOUCH_POINTS", MAX_TOUCH_POINTS, CONST_CS | CONST_PERSISTENT);
    

    // Gamepad Number
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad", "PLAYER1", GAMEPAD_PLAYER1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad", "PLAYER2", GAMEPAD_PLAYER2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad", "PLAYER3", GAMEPAD_PLAYER3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad", "PLAYER4", GAMEPAD_PLAYER4, CONST_CS | CONST_PERSISTENT);

    // Gamepad Buttons/Axis

    // PS3 USB Controller Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "TRIANGLE", GAMEPAD_PS3_BUTTON_TRIANGLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "CIRCLE", GAMEPAD_PS3_BUTTON_CIRCLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "CROSS", GAMEPAD_PS3_BUTTON_CROSS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "SQUARE", GAMEPAD_PS3_BUTTON_SQUARE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "L1", GAMEPAD_PS3_BUTTON_L1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "R1", GAMEPAD_PS3_BUTTON_R1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "L2", GAMEPAD_PS3_BUTTON_L2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "R2", GAMEPAD_PS3_BUTTON_R2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "START", GAMEPAD_PS3_BUTTON_START, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "SELECT", GAMEPAD_PS3_BUTTON_SELECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "UP", GAMEPAD_PS3_BUTTON_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "RIGHT", GAMEPAD_PS3_BUTTON_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "DOWN", GAMEPAD_PS3_BUTTON_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "LEFT", GAMEPAD_PS3_BUTTON_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\button", "PS", GAMEPAD_PS3_BUTTON_PS, CONST_CS | CONST_PERSISTENT);

    // PS3 USB Controller Axis
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "LEFT_X", GAMEPAD_PS3_AXIS_LEFT_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "LEFT_Y", GAMEPAD_PS3_AXIS_LEFT_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "RIGHT_X", GAMEPAD_PS3_AXIS_RIGHT_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "RIGHT_Y", GAMEPAD_PS3_AXIS_RIGHT_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "L2", GAMEPAD_PS3_AXIS_L2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\ps3\\axis", "R2", GAMEPAD_PS3_AXIS_R2, CONST_CS | CONST_PERSISTENT);

    // Xbox360 USB Controller Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "A", GAMEPAD_XBOX_BUTTON_A, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "B", GAMEPAD_XBOX_BUTTON_B, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "X", GAMEPAD_XBOX_BUTTON_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "Y", GAMEPAD_XBOX_BUTTON_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "LB", GAMEPAD_XBOX_BUTTON_LB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "RB", GAMEPAD_XBOX_BUTTON_RB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "SELECT", GAMEPAD_XBOX_BUTTON_SELECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "START", GAMEPAD_XBOX_BUTTON_START, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "UP", GAMEPAD_XBOX_BUTTON_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "RIGHT", GAMEPAD_XBOX_BUTTON_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "DOWN", GAMEPAD_XBOX_BUTTON_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "LEFT", GAMEPAD_XBOX_BUTTON_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\gamepad\\xbox\\button", "HOME", GAMEPAD_XBOX_BUTTON_HOME, CONST_CS | CONST_PERSISTENT);


    // Shader and material limits
    REGISTER_NS_LONG_CONSTANT("raylib\\max", "SHADER_LOCATIONS", MAX_SHADER_LOCATIONS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\max", "MATERIAL_MAPS", MAX_MATERIAL_MAPS, CONST_CS | CONST_PERSISTENT);

    le_raylib_image = zend_register_list_destructors_ex(raylib_image_dtor, NULL, "RAYLIB_IMAGE_TYPE", module_number);
    le_raylib_texture = zend_register_list_destructors_ex(raylib_texture_dtor, NULL, "RAYLIB_TEXTURE_TYPE", module_number);

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
        ZEND_NS_FE("raylib", GetKeyPressed, NULL)
        ZEND_NS_FE("raylib", SetExitKey, NULL)
        // Input-related functions: gamepads
        ZEND_NS_FE("raylib", IsGamepadAvailable, NULL)
        ZEND_NS_FE("raylib", IsGamepadName, NULL)
        ZEND_NS_FE("raylib", GetGamepadName, NULL)
        ZEND_NS_FE("raylib", IsGamepadButtonPressed, NULL)
        ZEND_NS_FE("raylib", IsGamepadButtonDown, NULL)
        ZEND_NS_FE("raylib", IsGamepadButtonReleased, NULL)
        ZEND_NS_FE("raylib", IsGamepadButtonUp, NULL)
        ZEND_NS_FE("raylib", GetGamepadButtonPressed, NULL)
        ZEND_NS_FE("raylib", GetGamepadAxisCount, NULL)
        ZEND_NS_FE("raylib", GetGamepadAxisMovement, NULL)
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
