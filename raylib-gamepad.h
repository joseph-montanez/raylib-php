//
// Created by Joseph Montanez on 4/12/18.
//

#ifndef PHP_RAYLIB_GAMEPAD_H
#define PHP_RAYLIB_GAMEPAD_H

extern zend_class_entry *php_raylib_gamepad_ce;

extern void php_raylib_vector2_free_storage(zend_object *object TSRMLS_DC);

extern zend_object * php_raylib_vector2_new(zend_class_entry *ce TSRMLS_DC);

extern zend_object_handlers php_raylib_vector2_object_handlers;

typedef struct _php_raylib_gamepad_object {
    zend_object std;
} php_raylib_gamepad_object;

static inline php_raylib_gamepad_object *php_raylib_gamepad_fetch_object(zend_object *obj) {
    return (php_raylib_gamepad_object *)((char *)obj - XtOffsetOf(php_raylib_gamepad_object, std));
}

void php_raylib_gamepad_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_gamepad_new(zend_class_entry *ce TSRMLS_DC);

#define Z_GAMEPAD_OBJ_P(zv) php_raylib_gamepad_fetch_object(Z_OBJ_P(zv));

void php_raylib_gamepad_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_GAMEPAD_H
