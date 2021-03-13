//
// Created by Joseph Montanez on 4/6/18.
//

#ifndef PHP_RAYLIB_IMAGE_H
#define PHP_RAYLIB_IMAGE_H

#include "php.h"
#include "raylib.h"

extern zend_class_entry *php_raylib_image_ce;

typedef struct _php_raylib_image_object {
    Image image;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_image_object;

static inline php_raylib_image_object *php_raylib_image_fetch_object(zend_object *obj) {
    return (php_raylib_image_object *)((char *)obj - XtOffsetOf(php_raylib_image_object, std));
}

#define Z_IMAGE_OBJ_P(zv) php_raylib_image_fetch_object(Z_OBJ_P(zv));

void php_raylib_image_startup(INIT_FUNC_ARGS);

zend_object * php_raylib_image_new_ex(zend_class_entry *ce, zend_object *orig);
zend_object * php_raylib_image_new(zend_class_entry *ce);

#endif //PHP_RAYLIB_IMAGE_H
