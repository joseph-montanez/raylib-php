//
// Created by Joseph Montanez on 4/9/18.
//

#ifndef RAYLIB_RAYLIB_FONT_H
#define RAYLIB_RAYLIB_FONT_H

extern zend_class_entry *php_raylib_font_ce;

typedef struct _php_raylib_font_object {
    Font font;
    zend_object std;
} php_raylib_font_object;

static inline php_raylib_font_object *php_raylib_font_fetch_object(zend_object *obj) {
    return (php_raylib_font_object *)((char *)obj - XtOffsetOf(php_raylib_font_object, std));
}

void php_raylib_font_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_font_new(zend_class_entry *ce TSRMLS_DC);

#define Z_FONT_OBJ_P(zv) php_raylib_font_fetch_object(Z_OBJ_P(zv));

void php_raylib_font_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_FONT_H
