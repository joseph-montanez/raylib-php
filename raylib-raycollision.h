#ifndef PHP_RAYLIB_RAYCOLLISION_H
#define PHP_RAYLIB_RAYCOLLISION_H

#include "raylib-vector3.h"
#include "raylib-vector3.h"

extern zend_class_entry * php_raylib_raycollision_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_raycollision_free_storage(zend_object * object);

extern zend_object * php_raylib_raycollision_new(zend_class_entry * ce);

extern zend_object * php_raylib_raycollision_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_raycollision_object_handlers;

typedef struct _php_raylib_raycollision_object {
    RayCollision raycollision;
    HashTable *prop_handler;
    php_raylib_vector3_object *point;
    php_raylib_vector3_object *normal;
    zend_object std;
} php_raylib_raycollision_object;

static inline php_raylib_raycollision_object *php_raylib_raycollision_fetch_object(zend_object *obj) {
    return (php_raylib_raycollision_object *)((char *)obj - XtOffsetOf(php_raylib_raycollision_object, std));
}

#define Z_RAYCOLLISION_OBJ_P(zv) php_raylib_raycollision_fetch_object(Z_OBJ_P(zv));

void php_raylib_raycollision_startup(INIT_FUNC_ARGS);

extern void php_raylib_raycollision_update_intern(php_raylib_raycollision_object *intern);

#endif //PHP_RAYLIB_RAYCOLLISION_H
