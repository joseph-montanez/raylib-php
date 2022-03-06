#ifndef PHP_RAYLIB_MODELANIMATION_H
#define PHP_RAYLIB_MODELANIMATION_H

#include "boneinfo.h"
#include "transform.h"

extern zend_class_entry * php_raylib_modelanimation_ce;

// External Free Objects - Prevent Circular Dependency
//TODO: Support array/hash
//extern void php_raylib_boneinfo_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_transform_array_free_storage(zend_object *object);

extern void php_raylib_modelanimation_free_storage(zend_object * object);

extern zend_object * php_raylib_modelanimation_new(zend_class_entry * ce);

extern zend_object * php_raylib_modelanimation_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_modelanimation_object_handlers;

typedef struct _php_raylib_modelanimation_object {
    ModelAnimation modelanimation;
    HashTable *prop_handler;
php_raylib_boneinfo_object *bones;
php_raylib_transform_object *frameposes;
    zend_object std;
} php_raylib_modelanimation_object;

static inline php_raylib_modelanimation_object *php_raylib_modelanimation_fetch_object(zend_object *obj) {
    return (php_raylib_modelanimation_object *)((char *)obj - XtOffsetOf(php_raylib_modelanimation_object, std));
}

#define Z_MODELANIMATION_OBJ_P(zv) php_raylib_modelanimation_fetch_object(Z_OBJ_P(zv));

void php_raylib_modelanimation_startup(INIT_FUNC_ARGS);

extern void php_raylib_modelanimation_update_intern(php_raylib_modelanimation_object *intern);

#endif //PHP_RAYLIB_MODELANIMATION_H
