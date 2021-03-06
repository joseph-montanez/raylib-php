//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_CAMERA2D_H
#define PHP_RAYLIB_CAMERA2D_H

extern zend_class_entry *php_raylib_camera2d_ce;

extern void php_raylib_vector2_free_storage(zend_object *object);

extern zend_object * php_raylib_vector2_new(zend_class_entry *ce);

extern zend_object_handlers php_raylib_vector2_object_handlers;

typedef struct _php_raylib_camera2d_object {
    Camera2D camera2d;
    zend_object std;
} php_raylib_camera2d_object;

static inline php_raylib_camera2d_object *php_raylib_camera2d_fetch_object(zend_object *obj) {
    return (php_raylib_camera2d_object *)((char *)obj - XtOffsetOf(php_raylib_camera2d_object, std));
}

void php_raylib_camera2d_free_storage(zend_object *object);
zend_object * php_raylib_camera2d_new(zend_class_entry *ce);

#define Z_CAMERA2D_OBJ_P(zv) php_raylib_camera2d_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera2d_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CAMERA2D_H
