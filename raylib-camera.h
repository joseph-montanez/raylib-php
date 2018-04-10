//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_CAMERA_H
#define PHP_RAYLIB_CAMERA_H

extern zend_class_entry *php_raylib_camera_ce;

typedef struct _php_raylib_camera_object {
    Camera camera;
    zend_object std;
} php_raylib_camera_object;

static inline php_raylib_camera_object *php_raylib_camera_fetch_object(zend_object *obj) {
    return (php_raylib_camera_object *)((char *)obj - XtOffsetOf(php_raylib_camera_object, std));
}

void php_raylib_camera_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_camera_new(zend_class_entry *ce TSRMLS_DC);

#define Z_CAMERA_OBJ_P(zv) php_raylib_camera_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CAMERA_H
