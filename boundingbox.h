#ifndef PHP_RAYLIB_BOUNDINGBOX_H
#define PHP_RAYLIB_BOUNDINGBOX_H

#include "vector3.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_boundingbox_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_boundingbox_free_storage(zend_object * object);

extern zend_object * php_raylib_boundingbox_new(zend_class_entry * ce);

extern zend_object * php_raylib_boundingbox_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_boundingbox_object_handlers;

typedef struct _php_raylib_boundingbox_object {
    BoundingBox boundingbox;
    HashTable *prop_handler;
    zval min;
    zval max;
    zend_object std;
} php_raylib_boundingbox_object;

static inline php_raylib_boundingbox_object *php_raylib_boundingbox_fetch_object(zend_object *obj) {
    return (php_raylib_boundingbox_object *)((char *)obj - XtOffsetOf(php_raylib_boundingbox_object, std));
}

#define Z_BOUNDINGBOX_OBJ_P(zv) php_raylib_boundingbox_fetch_object(Z_OBJ_P(zv));

void php_raylib_boundingbox_startup(INIT_FUNC_ARGS);

extern void php_raylib_boundingbox_update_intern(php_raylib_boundingbox_object *intern);
extern void php_raylib_boundingbox_update_intern_reverse(php_raylib_boundingbox_object *intern);

#endif //PHP_RAYLIB_BOUNDINGBOX_H
