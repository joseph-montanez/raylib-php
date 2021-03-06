//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_RENDERTEXTURE_H
#define PHP_RAYLIB_RENDERTEXTURE_H

extern zend_class_entry *php_raylib_rendertexture_ce;

typedef struct _php_raylib_rendertexture_object {
    RenderTexture2D rendertexture;
    zend_object std;
} php_raylib_rendertexture_object;

static inline php_raylib_rendertexture_object *php_raylib_rendertexture_fetch_object(zend_object *obj) {
    return (php_raylib_rendertexture_object *)((char *)obj - XtOffsetOf(php_raylib_rendertexture_object, std));
}

void php_raylib_rendertexture_free_storage(zend_object *object);
zend_object * php_raylib_rendertexture_new(zend_class_entry *ce);

#define Z_RENDERTEXTURE_OBJ_P(zv) php_raylib_rendertexture_fetch_object(Z_OBJ_P(zv));

void php_raylib_rendertexture_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_RENDERTEXTURE_H
