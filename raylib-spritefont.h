//
// Created by Joseph Montanez on 4/9/18.
//

#ifndef RAYLIB_RAYLIB_SPRITEFONT_H
#define RAYLIB_RAYLIB_SPRITEFONT_H

extern zend_class_entry *php_raylib_spritefont_ce;

typedef struct _php_raylib_spritefont_object {
    SpriteFont spritefont;
    zend_object std;
} php_raylib_spritefont_object;

static inline php_raylib_spritefont_object *php_raylib_spritefont_fetch_object(zend_object *obj) {
    return (php_raylib_spritefont_object *)((char *)obj - XtOffsetOf(php_raylib_spritefont_object, std));
}

void php_raylib_spritefont_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_spritefont_new(zend_class_entry *ce TSRMLS_DC);

#define Z_SPRITEFONT_OBJ_P(zv) php_raylib_spritefont_fetch_object(Z_OBJ_P(zv));

void php_raylib_spritefont_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_SPRITEFONT_H
