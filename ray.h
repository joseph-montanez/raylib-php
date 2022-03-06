#ifndef PHP_RAYLIB_RAY_H
#define PHP_RAYLIB_RAY_H

#include "vector3.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_ray_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_ray_free_storage(zend_object * object);

extern zend_object * php_raylib_ray_new(zend_class_entry * ce);

extern zend_object * php_raylib_ray_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_ray_object_handlers;

typedef struct _php_raylib_ray_object {
    Ray ray;
    HashTable *prop_handler;
    php_raylib_vector3_object *position;
    php_raylib_vector3_object *direction;
    zend_object std;
} php_raylib_ray_object;

static inline php_raylib_ray_object *php_raylib_ray_fetch_object(zend_object *obj) {
    return (php_raylib_ray_object *)((char *)obj - XtOffsetOf(php_raylib_ray_object, std));
}

#define Z_RAY_OBJ_P(zv) php_raylib_ray_fetch_object(Z_OBJ_P(zv));

void php_raylib_ray_startup(INIT_FUNC_ARGS);

extern void php_raylib_ray_update_intern(php_raylib_ray_object *intern);

#endif //PHP_RAYLIB_RAY_H
