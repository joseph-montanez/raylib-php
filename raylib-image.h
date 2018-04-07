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
    zend_object std;
} php_raylib_image_object;

static inline php_raylib_image_object *php_raylib_image_fetch_object(zend_object *obj) {
    return (php_raylib_image_object *)((char *)obj - XtOffsetOf(php_raylib_image_object, std));
}

#define Z_IMAGE_OBJ_P(zv) php_raylib_image_fetch_object(Z_OBJ_P(zv));

void php_raylib_image_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_IMAGE_H
