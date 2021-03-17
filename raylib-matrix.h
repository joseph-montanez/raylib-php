//
// Created by Joseph Montanez on 2018-12-01.
//

#ifndef RAYLIB_RAYLIB_MATRIX_H
#define RAYLIB_RAYLIB_MATRIX_H

extern zend_class_entry *php_raylib_matrix_ce;

typedef struct _php_raylib_matrix_object {
    Matrix matrix;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_matrix_object;

static inline php_raylib_matrix_object *php_raylib_matrix_fetch_object(zend_object *obj) {
    return (php_raylib_matrix_object *)((char *)obj - XtOffsetOf(php_raylib_matrix_object, std));
}

#define Z_MATRIX_OBJ_P(zv) php_raylib_matrix_fetch_object(Z_OBJ_P(zv));

void php_raylib_matrix_startup(INIT_FUNC_ARGS);

zend_object * php_raylib_matrix_new_ex(zend_class_entry *ce, zend_object *orig);

#endif //RAYLIB_RAYLIB_MATRIX_H
