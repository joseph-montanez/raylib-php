//
// Created by Joseph Montanez on 4/13/18.
//

#ifndef PHP_RAYLIB_COLOR_H
#define PHP_RAYLIB_COLOR_H

extern zend_class_entry *php_raylib_color_ce;

typedef struct _php_raylib_color_object {
    Color color;
    zend_object std;
} php_raylib_color_object;

static inline php_raylib_color_object *php_raylib_color_fetch_object(zend_object *obj) {
    return (php_raylib_color_object *)((char *)obj - XtOffsetOf(php_raylib_color_object, std));
}

void php_raylib_color_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_color_new(zend_class_entry *ce TSRMLS_DC);

#define Z_COLOR_OBJ_P(zv) php_raylib_color_fetch_object(Z_OBJ_P(zv));

void php_raylib_color_startup(INIT_FUNC_ARGS);


#endif //PHP_RAYLIB_COLOR_H
