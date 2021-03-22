//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_RECTANGLE_H
#define RAYLIB_RAYLIB_RECTANGLE_H

extern zend_class_entry *php_raylib_rectangle_ce;

typedef struct _php_raylib_rectangle_object {
    Rectangle rectangle;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_rectangle_object;

static inline php_raylib_rectangle_object *php_raylib_rectangle_fetch_object(zend_object *obj) {
    return (php_raylib_rectangle_object *)((char *)obj - XtOffsetOf(php_raylib_rectangle_object, std));
}

#define Z_RECTANGLE_OBJ_P(zv) php_raylib_rectangle_fetch_object(Z_OBJ_P(zv));

void php_raylib_rectangle_startup(INIT_FUNC_ARGS);

zend_object * php_raylib_rectangle_new_ex(zend_class_entry *ce, zend_object *orig);
zend_object * php_raylib_rectangle_new(zend_class_entry *ce);

#endif //RAYLIB_RAYLIB_RECTANGLE_H
