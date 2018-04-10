//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_DRAW_H
#define PHP_RAYLIB_DRAW_H

extern zend_class_entry *php_raylib_draw_ce;

typedef struct _php_raylib_draw_object {
    zend_object std;
} php_raylib_draw_object;

static inline php_raylib_draw_object *php_raylib_draw_fetch_object(zend_object *obj) {
    return (php_raylib_draw_object *)((char *)obj - XtOffsetOf(php_raylib_draw_object, std));
}

#define Z_DRAW_OBJ_P(zv) php_raylib_draw_fetch_object(Z_OBJ_P(zv));

void php_raylib_draw_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_DRAW_H
