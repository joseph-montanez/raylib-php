#ifndef PHP_RAYLIB_FONT_H
#define PHP_RAYLIB_FONT_H

#include "texture.h"
#include "rectangle.h"
#include "glyphinfo.h"

extern zend_class_entry * php_raylib_font_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_texture_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_rectangle_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_glyphinfo_array_free_storage(zend_object *object);

extern void php_raylib_font_free_storage(zend_object * object);

extern zend_object * php_raylib_font_new(zend_class_entry * ce);

extern zend_object * php_raylib_font_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_font_object_handlers;

typedef struct _php_raylib_font_object {
    Font font;
    HashTable *prop_handler;
    php_raylib_texture_object *texture;
php_raylib_rectangle_object *recs;
php_raylib_glyphinfo_object *glyphs;
    zend_object std;
} php_raylib_font_object;

static inline php_raylib_font_object *php_raylib_font_fetch_object(zend_object *obj) {
    return (php_raylib_font_object *)((char *)obj - XtOffsetOf(php_raylib_font_object, std));
}

#define Z_FONT_OBJ_P(zv) php_raylib_font_fetch_object(Z_OBJ_P(zv));

void php_raylib_font_startup(INIT_FUNC_ARGS);

extern void php_raylib_font_update_intern(php_raylib_font_object *intern);

#endif //PHP_RAYLIB_FONT_H
