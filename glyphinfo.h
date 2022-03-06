#ifndef PHP_RAYLIB_GLYPHINFO_H
#define PHP_RAYLIB_GLYPHINFO_H

#include "image.h"

extern zend_class_entry * php_raylib_glyphinfo_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_image_free_storage(zend_object *object);

extern void php_raylib_glyphinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_glyphinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_glyphinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_glyphinfo_object_handlers;

typedef struct _php_raylib_glyphinfo_object {
    GlyphInfo glyphinfo;
    HashTable *prop_handler;
    php_raylib_image_object *image;
    zend_object std;
} php_raylib_glyphinfo_object;

static inline php_raylib_glyphinfo_object *php_raylib_glyphinfo_fetch_object(zend_object *obj) {
    return (php_raylib_glyphinfo_object *)((char *)obj - XtOffsetOf(php_raylib_glyphinfo_object, std));
}

#define Z_GLYPHINFO_OBJ_P(zv) php_raylib_glyphinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_glyphinfo_startup(INIT_FUNC_ARGS);

extern void php_raylib_glyphinfo_update_intern(php_raylib_glyphinfo_object *intern);

#endif //PHP_RAYLIB_GLYPHINFO_H
