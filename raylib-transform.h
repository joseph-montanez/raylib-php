#ifndef PHP_RAYLIB_TRANSFORM_H
#define PHP_RAYLIB_TRANSFORM_H

#include "raylib-vector3.h"
#include "raylib-vector4.h"
#include "raylib-vector3.h"

extern zend_class_entry * php_raylib_transform_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);
extern void php_raylib_vector4_free_storage(zend_object *object);

extern void php_raylib_transform_free_storage(zend_object * object);

extern zend_object * php_raylib_transform_new(zend_class_entry * ce);

extern zend_object * php_raylib_transform_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_transform_object_handlers;

typedef struct _php_raylib_transform_object {
    Transform transform;
    HashTable *prop_handler;
    php_raylib_vector3_object *translation;
    php_raylib_vector4_object *rotation;
    php_raylib_vector3_object *scale;
    zend_object std;
} php_raylib_transform_object;

static inline php_raylib_transform_object *php_raylib_transform_fetch_object(zend_object *obj) {
    return (php_raylib_transform_object *)((char *)obj - XtOffsetOf(php_raylib_transform_object, std));
}

#define Z_TRANSFORM_OBJ_P(zv) php_raylib_transform_fetch_object(Z_OBJ_P(zv));

void php_raylib_transform_startup(INIT_FUNC_ARGS);

static void php_raylib_transform_update_intern(php_raylib_transform_object *intern);

#endif //PHP_RAYLIB_TRANSFORM_H
