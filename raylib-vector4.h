#ifndef PHP_RAYLIB_VECTOR4_H
#define PHP_RAYLIB_VECTOR4_H


extern zend_class_entry * php_raylib_vector4_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_vector4_free_storage(zend_object * object);

extern zend_object * php_raylib_vector4_new(zend_class_entry * ce);

extern zend_object * php_raylib_vector4_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_vector4_object_handlers;

typedef struct _php_raylib_vector4_object {
    Vector4 vector4;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector4_object;

static inline php_raylib_vector4_object *php_raylib_vector4_fetch_object(zend_object *obj) {
    return (php_raylib_vector4_object *)((char *)obj - XtOffsetOf(php_raylib_vector4_object, std));
}

#define Z_VECTOR4_OBJ_P(zv) php_raylib_vector4_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector4_startup(INIT_FUNC_ARGS);

extern void php_raylib_vector4_update_intern(php_raylib_vector4_object *intern);

#endif //PHP_RAYLIB_VECTOR4_H
