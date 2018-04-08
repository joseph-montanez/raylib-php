//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_TEXT_H
#define PHP_RAYLIB_TEXT_H

extern zend_class_entry *php_raylib_text_ce;

typedef struct _php_raylib_text_object {
    zend_object std;
} php_raylib_text_object;

static inline php_raylib_text_object *php_raylib_text_fetch_object(zend_object *obj) {
    return (php_raylib_text_object *)((char *)obj - XtOffsetOf(php_raylib_text_object, std));
}

#define Z_TEXT_OBJ_P(zv) php_raylib_text_fetch_object(Z_OBJ_P(zv));

void php_raylib_text_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_TEXT_H
