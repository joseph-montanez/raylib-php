#ifndef PHP_RAYLIB_CAMERA3D_H
#define PHP_RAYLIB_CAMERA3D_H

#include "vector3.h"
#include "vector3.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_camera3d_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_camera3d_free_storage(zend_object * object);

extern zend_object * php_raylib_camera3d_new(zend_class_entry * ce);

extern zend_object * php_raylib_camera3d_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_camera3d_object_handlers;

typedef struct _php_raylib_camera3d_object {
    Camera3D camera3d;
    HashTable *prop_handler;
    php_raylib_vector3_object *position;
    php_raylib_vector3_object *target;
    php_raylib_vector3_object *up;
    zend_object std;
} php_raylib_camera3d_object;

static inline php_raylib_camera3d_object *php_raylib_camera3d_fetch_object(zend_object *obj) {
    return (php_raylib_camera3d_object *)((char *)obj - XtOffsetOf(php_raylib_camera3d_object, std));
}

#define Z_CAMERA3D_OBJ_P(zv) php_raylib_camera3d_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera3d_startup(INIT_FUNC_ARGS);

extern void php_raylib_camera3d_update_intern(php_raylib_camera3d_object *intern);

#endif //PHP_RAYLIB_CAMERA3D_H
