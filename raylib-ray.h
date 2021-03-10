//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_RAY_H
#define RAYLIB_RAYLIB_RAY_H

extern zend_class_entry *php_raylib_ray_ce;

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

#endif //RAYLIB_RAYLIB_RAY_H
