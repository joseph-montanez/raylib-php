//
// Created by Joseph Montanez on 4/7/18.
//

#ifndef PHP_RAYLIB_CURSOR_H
#define PHP_RAYLIB_CURSOR_H

extern zend_class_entry *php_raylib_cursor_ce;

typedef struct _php_raylib_cursor_object {
    zend_object std;
} php_raylib_cursor_object;

static inline php_raylib_cursor_object *php_raylib_cursor_fetch_object(zend_object *obj) {
    return (php_raylib_cursor_object *)((char *)obj - XtOffsetOf(php_raylib_cursor_object, std));
}

#define Z_CURSOR_OBJ_P(zv) php_raylib_cursor_fetch_object(Z_OBJ_P(zv));

void php_raylib_cursor_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CURSOR_H
