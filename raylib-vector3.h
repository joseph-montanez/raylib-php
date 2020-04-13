//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_VECTOR3_H
#define RAYLIB_RAYLIB_VECTOR3_H

extern zend_class_entry *php_raylib_vector3_ce;

typedef struct _php_raylib_vector3_object {
    Vector3 vector3;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector3_object;

static inline php_raylib_vector3_object *php_raylib_vector3_fetch_object(zend_object *obj) {
    return (php_raylib_vector3_object *)((char *)obj - XtOffsetOf(php_raylib_vector3_object, std));
}

#define Z_VECTOR3_OBJ_P(zv) php_raylib_vector3_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector3_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_VECTOR3_H
