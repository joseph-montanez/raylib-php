//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_VECTOR2_H
#define RAYLIB_RAYLIB_VECTOR2_H

extern zend_class_entry *php_raylib_vector2_ce;

typedef struct _php_raylib_vector2_object {
    Vector2 vector2;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector2_object;

static inline php_raylib_vector2_object *php_raylib_vector2_fetch_object(zend_object *obj) {
    return (php_raylib_vector2_object *)((char *)obj - XtOffsetOf(php_raylib_vector2_object, std));
}

#define Z_VECTOR2_OBJ_P(zv) php_raylib_vector2_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector2_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_VECTOR2_H
