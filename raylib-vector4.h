//
// Created by Joseph Montanez on 2018-12-01.
//

#ifndef RAYLIB_RAYLIB_VECTOR4_H
#define RAYLIB_RAYLIB_VECTOR4_H

extern zend_class_entry *php_raylib_vector4_ce;

typedef struct _php_raylib_vector4_object {
    Vector4 vector4;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector4_object;

static inline php_raylib_vector4_object *php_raylib_vector4_fetch_object(zend_object *obj) {
    return (php_raylib_vector4_object *)((char *)obj - XtOffsetOf(php_raylib_vector4_object, std));
}

#define Z_VECTOR4_OBJ_P(zv) php_raylib_vector4_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector4_startup(INIT_FUNC_ARGS);

zend_object * php_raylib_vector4_new_ex(zend_class_entry *ce, zend_object *orig);

#endif //RAYLIB_RAYLIB_VECTOR4_H
