//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_GlyphInfo_H
#define RAYLIB_RAYLIB_GlyphInfo_H
#include "raylib-image.h"

extern zend_class_entry *php_raylib_glyphInfo_ce;

typedef struct _php_raylib_glyphInfo_object {
    GlyphInfo glyphInfo;
    HashTable *prop_handler;
    php_raylib_image_object *image;
    zend_object std;
} php_raylib_glyphInfo_object;

static inline php_raylib_glyphInfo_object *php_raylib_glyphInfo_fetch_object(zend_object *obj) {
    return (php_raylib_glyphInfo_object *)((char *)obj - XtOffsetOf(php_raylib_glyphInfo_object, std));
}

#define Z_GlyphInfo_OBJ_P(zv) php_raylib_glyphInfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_glyphInfo_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_GlyphInfo_H
