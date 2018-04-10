//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_TIMMING_H
#define PHP_RAYLIB_TIMMING_H

extern zend_class_entry *php_raylib_timming_ce;

typedef struct _php_raylib_timming_object {
    zend_object std;
} php_raylib_timming_object;

static inline php_raylib_timming_object *php_raylib_timming_fetch_object(zend_object *obj) {
    return (php_raylib_timming_object *)((char *)obj - XtOffsetOf(php_raylib_timming_object, std));
}

void php_raylib_timming_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_timming_new(zend_class_entry *ce TSRMLS_DC);

#define Z_TIMMING_OBJ_P(zv) php_raylib_timming_fetch_object(Z_OBJ_P(zv));

void php_raylib_timming_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_TIMMING_H
