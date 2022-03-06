#ifndef PHP_RAYLIB_RENDERTEXTURE_H
#define PHP_RAYLIB_RENDERTEXTURE_H

#include "raylib-texture.h"
#include "raylib-texture.h"

extern zend_class_entry * php_raylib_rendertexture_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_texture_free_storage(zend_object *object);

extern void php_raylib_rendertexture_free_storage(zend_object * object);

extern zend_object * php_raylib_rendertexture_new(zend_class_entry * ce);

extern zend_object * php_raylib_rendertexture_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_rendertexture_object_handlers;

typedef struct _php_raylib_rendertexture_object {
    RenderTexture rendertexture;
    HashTable *prop_handler;
    php_raylib_texture_object *texture;
    php_raylib_texture_object *depth;
    zend_object std;
} php_raylib_rendertexture_object;

static inline php_raylib_rendertexture_object *php_raylib_rendertexture_fetch_object(zend_object *obj) {
    return (php_raylib_rendertexture_object *)((char *)obj - XtOffsetOf(php_raylib_rendertexture_object, std));
}

#define Z_RENDERTEXTURE_OBJ_P(zv) php_raylib_rendertexture_fetch_object(Z_OBJ_P(zv));

void php_raylib_rendertexture_startup(INIT_FUNC_ARGS);

extern void php_raylib_rendertexture_update_intern(php_raylib_rendertexture_object *intern);

#endif //PHP_RAYLIB_RENDERTEXTURE_H
