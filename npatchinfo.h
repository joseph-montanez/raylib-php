#ifndef PHP_RAYLIB_NPATCHINFO_H
#define PHP_RAYLIB_NPATCHINFO_H

#include "rectangle.h"

extern zend_class_entry * php_raylib_npatchinfo_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_rectangle_free_storage(zend_object *object);

extern void php_raylib_npatchinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_npatchinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_npatchinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_npatchinfo_object_handlers;

typedef struct _php_raylib_npatchinfo_object {
    NPatchInfo npatchinfo;
    HashTable *prop_handler;
    zval source;
    zend_object std;
} php_raylib_npatchinfo_object;

static inline php_raylib_npatchinfo_object *php_raylib_npatchinfo_fetch_object(zend_object *obj) {
    return (php_raylib_npatchinfo_object *)((char *)obj - XtOffsetOf(php_raylib_npatchinfo_object, std));
}

#define Z_NPATCHINFO_OBJ_P(zv) php_raylib_npatchinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_npatchinfo_startup(INIT_FUNC_ARGS);

extern void php_raylib_npatchinfo_update_intern(php_raylib_npatchinfo_object *intern);
extern void php_raylib_npatchinfo_update_intern_reverse(php_raylib_npatchinfo_object *intern);

#endif //PHP_RAYLIB_NPATCHINFO_H
