//
// Created by Joseph Montanez on 4/11/18.
//

#ifndef PHP_RAYLIB_KEY_H
#define PHP_RAYLIB_KEY_H

extern zend_class_entry *php_raylib_key_ce;

typedef struct _php_raylib_key_object {
    zend_object std;
} php_raylib_key_object;

static inline php_raylib_key_object *php_raylib_key_fetch_object(zend_object *obj) {
    return (php_raylib_key_object *)((char *)obj - XtOffsetOf(php_raylib_key_object, std));
}

void php_raylib_key_free_storage(zend_object *object);
zend_object * php_raylib_key_new(zend_class_entry *ce);

#define Z_KEY_OBJ_P(zv) php_raylib_key_fetch_object(Z_OBJ_P(zv));

void php_raylib_key_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_KEY_H
