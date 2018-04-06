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

#include <raylib.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_raylib.h"

#define raylib_register_color_constant(name, value) \
	REGISTER_NS_LONG_CONSTANT("raylib\\colors", name, value, CONST_CS | CONST_PERSISTENT)

//#ZEND_DECLARE_MODULE_GLOBALS(raylib)

#define RAYLIB_FLAG(name) "raylib\\flags\\" #name


static int le_link, le_plink, le_raylib_image, le_raylib_texture;

struct Color php_array_to_color(zval *ar) {
    HashTable *arr_hash;
    long num_key;
    zval *val;
    zend_string *key;

    unsigned char* r = (unsigned char *) 255;
    unsigned char* g = (unsigned char *) 255;
    unsigned char* b = (unsigned char *) 255;
    unsigned char* a = (unsigned char *) 255;

    arr_hash = Z_ARRVAL_P(ar);
    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
                if (Z_TYPE_P(val) == IS_LONG) {
                    switch(num_key) {
                        case 0:
                            r = (unsigned char*) val;
                        case 1:
                            g = (unsigned char*) val;
                        case 2:
                            b = (unsigned char*) val;
                        case 3:
                            a = (unsigned char*) val;
                    }
                }
            } ZEND_HASH_FOREACH_END();

    struct Color color = { *r, *b, *g, *a };
    return color;
}

int zend_long_2int(zend_long val) {
	return (val <= INT_MAX) ? (int)((zend_long)val) : -1;
}


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
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

// Window-related functions

//void InitWindow(int width, int height, const char *title);
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

	InitWindow(zend_long_2int(width), zend_long_2int(height), title->val);

	zend_string_free(title);
}

//void CloseWindow(void);
PHP_FUNCTION(CloseWindow)
{
	CloseWindow();
}

//bool IsWindowReady(void);
PHP_FUNCTION(IsWindowReady)
{
	RETURN_BOOL(IsWindowReady());
}

//bool WindowShouldClose(void);
PHP_FUNCTION(WindowShouldClose)
{
    RETURN_BOOL(WindowShouldClose());
}

//bool IsWindowMinimized(void);
PHP_FUNCTION(IsWindowMinimized)
{
    RETURN_BOOL(IsWindowMinimized());
}

//void ToggleFullscreen(void);
PHP_FUNCTION(ToggleFullscreen)
{
    ToggleFullscreen();
}

//void SetWindowIcon(Image image);
PHP_FUNCTION(SetWindowIcon)
{
    zval *image_rez;
    Image *image;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &image_rez) == FAILURE) {
        return;
    }

    if ((image = (Image *)zend_fetch_resource(Z_RES_P(image_rez), "LE_RAYLIB_IMAGE", le_raylib_image)) == NULL) {
        RETURN_FALSE;
    }

    SetWindowIcon(*image);
}

//void SetWindowTitle(const char *title);
PHP_FUNCTION(SetWindowTitle)
{
    zend_string *title;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(title)
    ZEND_PARSE_PARAMETERS_END();


    SetWindowTitle(title->val);
}

//void SetWindowPosition(int x, int y);
PHP_FUNCTION(SetWindowPosition)
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
PHP_FUNCTION(SetWindowMonitor)
{
    zend_long monitor;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(monitor)
    ZEND_PARSE_PARAMETERS_END();

    SetWindowMonitor(zend_long_2int(monitor));
}

//void SetWindowMinSize(int width, int height);
PHP_FUNCTION(SetWindowMinSize)
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
PHP_FUNCTION(SetWindowSize)
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
PHP_FUNCTION(GetScreenWidth)
{
    RETURN_LONG(GetScreenWidth());
}

//int GetScreenHeight(void);
PHP_FUNCTION(GetScreenHeight)
{
    RETURN_LONG(GetScreenHeight());
}

// Timming-related functions

//void SetTargetFPS(int fps);
PHP_FUNCTION(SetTargetFPS)
{
	zend_long fps;

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_LONG(fps)
	ZEND_PARSE_PARAMETERS_END();

	SetTargetFPS(zend_long_2int(fps));
}

//int GetFPS(void);
PHP_FUNCTION(GetFPS)
{
    RETURN_LONG(GetFPS());
}

//float GetFrameTime(void);
PHP_FUNCTION(GetFrameTime)
{
    RETURN_DOUBLE(GetFrameTime());
}

//double GetTime(void);
PHP_FUNCTION(GetTime)
{
    RETURN_DOUBLE(GetTime());
}


//bool BeginDrawing(void);
PHP_FUNCTION(BeginDrawing)
{
	BeginDrawing();
}

//bool EndDrawing(void);
PHP_FUNCTION(EndDrawing)
{
	EndDrawing();
}

//void ClearBackground(Color color)
PHP_FUNCTION(ClearBackground)
{
	zval *ar;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(ar)
	ZEND_PARSE_PARAMETERS_END();

	ClearBackground(php_array_to_color(ar));
}

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image/Texture2D data loading/unloading/saving functions

//Image LoadImage(const char *fileName)
PHP_FUNCTION(LoadImage)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    struct Image *imagePtr;
    struct Image image = LoadImage(fileName->val);

    imagePtr = (struct Image*) malloc(sizeof(struct Image));
    imagePtr->data = image.data;
    imagePtr->format = image.format;
    imagePtr->height = image.height;
    imagePtr->width = image.width;
    imagePtr->mipmaps = image.mipmaps;


    RETURN_RES(zend_register_resource(imagePtr, le_raylib_image));
}

//void UnloadImage(Image image)
PHP_FUNCTION(UnloadImage)
{
    zval *imageRez;
    Image *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(imageRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((image = (Image *)zend_fetch_resource(Z_RES_P(imageRez), "LE_RAYLIB_IMAGE", le_raylib_image)) == NULL) {
        RETURN_FALSE;
    }

    UnloadImage(*image);
    image->data = NULL;
    free(image);
    image = NULL;
}


//Texture2D LoadTexture(const char *fileName);
PHP_FUNCTION(LoadTexture)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    struct Texture2D *texturePtr;
    struct Texture2D texture = LoadTexture(fileName->val);

    texturePtr = (struct Texture2D*) malloc(sizeof(struct Texture2D));
    texturePtr->id = texture.id;
    texturePtr->format = texture.format;
    texturePtr->height = texture.height;
    texturePtr->width = texture.width;
    texturePtr->mipmaps = texture.mipmaps;


    RETURN_RES(zend_register_resource(texturePtr, le_raylib_texture));
}

//Texture2D LoadTextureFromImage(Image image);
PHP_FUNCTION(LoadTextureFromImage)
{
    zval *imageRez;
    Image *image;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(imageRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((image = (Image *)zend_fetch_resource(Z_RES_P(imageRez), "LE_RAYLIB_IMAGE", le_raylib_image)) == NULL) {
        RETURN_FALSE;
    }


    struct Texture2D *texturePtr;
    struct Texture2D texture = LoadTextureFromImage(*image);

    texturePtr = (struct Texture2D*) malloc(sizeof(struct Texture2D));
    texturePtr->id = texture.id;
    texturePtr->format = texture.format;
    texturePtr->height = texture.height;
    texturePtr->width = texture.width;
    texturePtr->mipmaps = texture.mipmaps;

    RETURN_RES(zend_register_resource(texturePtr, le_raylib_texture));
}

//void UnloadTexture(Texture2D texture)
PHP_FUNCTION(UnloadTexture)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    UnloadTexture(*texture);
    free(texture);
    texture = NULL;
}

//void DrawTexture(Texture2D texture, int posX, int posY, Color tint);
PHP_FUNCTION(DrawTexture)
{
    zval *textureRez;
    Texture2D *texture;
    zend_long posX;
    zend_long posY;
    zval *tint;

    ZEND_PARSE_PARAMETERS_START(4, 4)
            Z_PARAM_ZVAL(textureRez)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_ZVAL(tint)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    DrawTexture(*texture, zend_long_2int(posX), zend_long_2int(posY), php_array_to_color(tint));
}

// Texture Resource Functions

PHP_FUNCTION(TextureGetWidth)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    RETURN_LONG(texture->width);
}

PHP_FUNCTION(TextureGetHeight)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    RETURN_LONG(texture->height);
}

PHP_FUNCTION(TextureGetMipmaps)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    RETURN_LONG(texture->mipmaps);
}

PHP_FUNCTION(TextureGetId)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    RETURN_LONG(texture->id);
}

PHP_FUNCTION(TextureGetFormat)
{
    zval *textureRez;
    Texture2D *texture;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(textureRez)
    ZEND_PARSE_PARAMETERS_END();

    if ((texture = (Texture2D *)zend_fetch_resource(Z_RES_P(textureRez), "LE_RAYLIB_TEXTURE", le_raylib_texture)) == NULL) {
        RETURN_FALSE;
    }

    RETURN_LONG(texture->format);
}



//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// Text drawing functions

//void DrawFPS(int posX, int posY)
PHP_FUNCTION(DrawFPS)
{
	zend_long posX;
	zend_long posY;

	ZEND_PARSE_PARAMETERS_START(2, 2)
			Z_PARAM_LONG(posX)
			Z_PARAM_LONG(posY)
	ZEND_PARSE_PARAMETERS_END();

	DrawFPS(zend_long_2int(posX), zend_long_2int(posY));
}

//void DrawText(const char *text, int posX, int posY, int fontSize, Color color)
PHP_FUNCTION(DrawText)
{
	zend_string *text;
	zend_long posX;
	zend_long posY;
	zend_long fontSize;
	zval *ar;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(text)
		Z_PARAM_LONG(posX)
		Z_PARAM_LONG(posY)
		Z_PARAM_LONG(fontSize)
		Z_PARAM_ZVAL(ar)
	ZEND_PARSE_PARAMETERS_END();

	DrawText(text->val, zend_long_2int(posX), zend_long_2int(posY), zend_long_2int(fontSize), php_array_to_color(ar));
}

/* }}} */
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

    // raylib Config Flags
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "SHOW_LOGO", FLAG_SHOW_LOGO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_DECORATED", FLAG_WINDOW_DECORATED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "MSAA_4X_HINT", FLAG_MSAA_4X_HINT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\flags", "FLAG_VSYNC_HINTLOGO", FLAG_VSYNC_HINT, CONST_CS | CONST_PERSISTENT);

    // Keyboard Function Keys
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "SPACE", KEY_SPACE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "ESCAPE", KEY_ESCAPE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "ENTER", KEY_ENTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "TAB", KEY_TAB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "BACKSPACE", KEY_BACKSPACE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "INSERT", KEY_INSERT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "DELETE", KEY_DELETE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "RIGHT", KEY_RIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "LEFT", KEY_LEFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "DOWN", KEY_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "UP", KEY_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "PAGE_UP", KEY_PAGE_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "PAGE_DOWN", KEY_PAGE_DOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "HOME", KEY_HOME, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "END", KEY_END, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "CAPS_LOCK", KEY_CAPS_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "SCROLL_LOCK", KEY_SCROLL_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "NUM_LOCK", KEY_NUM_LOCK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "PRINT_SCREEN", KEY_PRINT_SCREEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "PAUSE", KEY_PAUSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F1", KEY_F1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F2", KEY_F2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F3", KEY_F3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F4", KEY_F4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F5", KEY_F5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F6", KEY_F6, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F7", KEY_F7, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F8", KEY_F8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F9", KEY_F9, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F10", KEY_F10, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F11", KEY_F11, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F12", KEY_F12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "LEFT_SHIFT", KEY_LEFT_SHIFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "LEFT_CONTROL", KEY_LEFT_CONTROL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "LEFT_ALT", KEY_LEFT_ALT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "RIGHT_SHIFT", KEY_RIGHT_SHIFT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "RIGHT_CONTROL", KEY_RIGHT_CONTROL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "RIGHT_ALT", KEY_RIGHT_ALT, CONST_CS | CONST_PERSISTENT);

    // Keyboard Alpha Numeric Keys
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "ZERO", KEY_ZERO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "ONE", KEY_ONE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "TWO", KEY_TWO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "THREE", KEY_THREE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "FOUR", KEY_FOUR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "FIVE", KEY_FIVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "SIX", KEY_SIX, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "SEVEN", KEY_SEVEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "EIGHT", KEY_EIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "NINE", KEY_NINE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "A", KEY_A, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "B", KEY_B, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "C", KEY_C, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "D", KEY_D, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "E", KEY_E, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "F", KEY_F, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "G", KEY_G, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "H", KEY_H, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "I", KEY_I, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "J", KEY_J, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "K", KEY_K, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "L", KEY_L, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "M", KEY_M, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "N", KEY_N, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "O", KEY_O, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "P", KEY_P, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "Q", KEY_Q, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "R", KEY_R, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "S", KEY_S, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "T", KEY_T, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "U", KEY_U, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "V", KEY_V, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "W", KEY_W, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "X", KEY_X, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "Y", KEY_Y, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "Z", KEY_Z, CONST_CS | CONST_PERSISTENT);


    // Android Physical Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "BACK", KEY_BACK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "MENU", KEY_MENU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_UP", KEY_VOLUME_UP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\keys", "VOLUME_DOWN", KEY_VOLUME_DOWN, CONST_CS | CONST_PERSISTENT);


    // Mouse Buttons
    REGISTER_NS_LONG_CONSTANT("raylib\\mouse", "LEFT_BUTTON", MOUSE_LEFT_BUTTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\mouse", "RIGHT_BUTTON", MOUSE_RIGHT_BUTTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("raylib\\mouse", "MIDDLE_BUTTON", MOUSE_MIDDLE_BUTTON, CONST_CS | CONST_PERSISTENT);

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
		// Window and Graphics Device Functions (Module: core)
		//------------------------------------------------------------------------------------
		// Window-related functions
		ZEND_NS_FE("raylib", InitWindow, NULL)
		ZEND_NS_FE("raylib", CloseWindow, NULL)
		ZEND_NS_FE("raylib", IsWindowReady, NULL)
        ZEND_NS_FE("raylib", WindowShouldClose, NULL)
        ZEND_NS_FE("raylib", ToggleFullscreen, NULL)
        ZEND_NS_FE("raylib", SetWindowIcon, NULL)
        ZEND_NS_FE("raylib", SetWindowTitle, NULL)
        ZEND_NS_FE("raylib", SetWindowPosition, NULL)
        ZEND_NS_FE("raylib", SetWindowMonitor, NULL)
        ZEND_NS_FE("raylib", SetWindowMinSize, NULL)
        ZEND_NS_FE("raylib", SetWindowSize, NULL)
        ZEND_NS_FE("raylib", GetScreenWidth, NULL)
        ZEND_NS_FE("raylib", GetScreenHeight, NULL)
		// Drawing-related functions
		ZEND_NS_FE("raylib", ClearBackground, NULL)
		ZEND_NS_FE("raylib", BeginDrawing, NULL)
		ZEND_NS_FE("raylib", EndDrawing, NULL)
		// Timming-related functions
		ZEND_NS_FE("raylib", SetTargetFPS, NULL)
		ZEND_NS_FE("raylib", GetFPS, NULL)
        //------------------------------------------------------------------------------------
        // Texture Loading and Drawing Functions (Module: textures)
        //------------------------------------------------------------------------------------
        // Image/Texture2D data loading/unloading/saving functions
        ZEND_NS_FE("raylib", LoadImage, NULL)
        ZEND_NS_FE("raylib", UnloadImage, NULL)
        ZEND_NS_FE("raylib", LoadTexture, NULL)
        ZEND_NS_FE("raylib", LoadTextureFromImage, NULL)
        ZEND_NS_FE("raylib", UnloadTexture, NULL)
        ZEND_NS_FE("raylib", DrawTexture, NULL)
        // Texture2D Resource Functions
        ZEND_NS_FE("raylib", TextureGetHeight, NULL)
        ZEND_NS_FE("raylib", TextureGetWidth, NULL)
        ZEND_NS_FE("raylib", TextureGetId, NULL)
        ZEND_NS_FE("raylib", TextureGetMipmaps, NULL)
        ZEND_NS_FE("raylib", TextureGetFormat, NULL)
		//------------------------------------------------------------------------------------
		// Font Loading and Text Drawing Functions (Module: text)
		//------------------------------------------------------------------------------------
		// Text drawing functions
		ZEND_NS_FE("raylib", DrawFPS, NULL)
		ZEND_NS_FE("raylib", DrawText, NULL)
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
