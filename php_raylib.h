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

#ifndef PHP_RAYLIB_H
#define PHP_RAYLIB_H

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include <raylib.h>
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "raylib-texture.h"

extern zend_module_entry raylib_module_entry;
#define phpext_raylib_ptr &raylib_module_entry

#define PHP_RAYLIB_VERSION "1.9.7"

zend_class_entry *php_raylib_image_ce;
zend_class_entry *php_raylib_texture_ce;
zend_class_entry *php_raylib_window_ce;
zend_class_entry *php_raylib_cursor_ce;
zend_class_entry *php_raylib_text_ce;
zend_class_entry *php_raylib_draw_ce;
zend_class_entry *php_raylib_rendertexture_ce;
zend_class_entry *php_raylib_camera_ce;
zend_class_entry *php_raylib_camera2d_ce;
zend_class_entry *php_raylib_timming_ce;
zend_class_entry *php_raylib_spritefont_ce;
zend_class_entry *php_raylib_key_ce;
zend_class_entry *php_raylib_mouse_ce;
zend_class_entry *php_raylib_color_ce;
zend_class_entry *php_raylib_collision_ce;


#ifdef PHP_WIN32
#	define PHP_RAYLIB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_RAYLIB_API __attribute__ ((visibility("default")))
#else
#	define PHP_RAYLIB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(raylib)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(raylib)
*/

/* Always refer to the globals in your function as RAYLIB_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define RAYLIB_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(raylib, v)

#if defined(ZTS) && defined(COMPILE_DL_RAYLIB)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_RAYLIB_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
