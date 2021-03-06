//
// Created by Joseph Montanez on 4/12/18.
//

#ifndef PHP_RAYLIB_MOUSE_H
#define PHP_RAYLIB_MOUSE_H

extern zend_class_entry *php_raylib_mouse_ce;

extern void php_raylib_vector2_free_storage(zend_object *object);

extern zend_object * php_raylib_vector2_new(zend_class_entry *ce);

extern zend_object_handlers php_raylib_vector2_object_handlers;

typedef struct _php_raylib_mouse_object {
    zend_object std;
} php_raylib_mouse_object;

static inline php_raylib_mouse_object *php_raylib_mouse_fetch_object(zend_object *obj) {
    return (php_raylib_mouse_object *)((char *)obj - XtOffsetOf(php_raylib_mouse_object, std));
}

void php_raylib_mouse_free_storage(zend_object *object);
zend_object * php_raylib_mouse_new(zend_class_entry *ce);

#define Z_MOUSE_OBJ_P(zv) php_raylib_mouse_fetch_object(Z_OBJ_P(zv));

void php_raylib_mouse_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MOUSE_H
