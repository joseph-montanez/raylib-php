//
// Created by Joseph Montanez on 4/6/18.
//

#ifndef PHP_RAYLIB_TEXTURE_H
#define PHP_RAYLIB_TEXTURE_H

#include "php.h"
#include "raylib.h"

extern zend_class_entry *php_raylib_texture_ce;

typedef struct _php_raylib_texture_object {
    Texture2D texture;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_texture_object;

static inline php_raylib_texture_object *php_raylib_texture_fetch_object(zend_object *obj) {
    return (php_raylib_texture_object *)((char *)obj - XtOffsetOf(php_raylib_texture_object, std));
}

void php_raylib_texture_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_texture_new(zend_class_entry *ce TSRMLS_DC);

#define Z_TEXTURE_OBJ_P(zv) php_raylib_texture_fetch_object(Z_OBJ_P(zv));

void php_raylib_texture_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_TEXTURE_H
