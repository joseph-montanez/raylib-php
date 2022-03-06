#ifndef PHP_RAYLIB_MODEL_H
#define PHP_RAYLIB_MODEL_H

#include "raylib-matrix.h"
#include "raylib-mesh.h"
#include "raylib-material.h"
#include "raylib-boneinfo.h"
#include "raylib-transform.h"

extern zend_class_entry * php_raylib_model_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_matrix_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_mesh_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_material_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_boneinfo_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_transform_array_free_storage(zend_object *object);

extern void php_raylib_model_free_storage(zend_object * object);

extern zend_object * php_raylib_model_new(zend_class_entry * ce);

extern zend_object * php_raylib_model_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_model_object_handlers;

typedef struct _php_raylib_model_object {
    Model model;
    HashTable *prop_handler;
    php_raylib_matrix_object *transform;
php_raylib_mesh_object *meshes;
php_raylib_material_object *materials;
php_raylib_boneinfo_object *bones;
php_raylib_transform_object *bindpose;
    zend_object std;
} php_raylib_model_object;

static inline php_raylib_model_object *php_raylib_model_fetch_object(zend_object *obj) {
    return (php_raylib_model_object *)((char *)obj - XtOffsetOf(php_raylib_model_object, std));
}

#define Z_MODEL_OBJ_P(zv) php_raylib_model_fetch_object(Z_OBJ_P(zv));

void php_raylib_model_startup(INIT_FUNC_ARGS);

extern void php_raylib_model_update_intern(php_raylib_model_object *intern);

#endif //PHP_RAYLIB_MODEL_H
