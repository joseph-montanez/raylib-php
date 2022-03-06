#ifndef PHP_RAYLIB_MATERIAL_H
#define PHP_RAYLIB_MATERIAL_H

#include "shader.h"
#include "materialmap.h"

extern zend_class_entry * php_raylib_material_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_shader_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_materialmap_array_free_storage(zend_object *object);

extern void php_raylib_material_free_storage(zend_object * object);

extern zend_object * php_raylib_material_new(zend_class_entry * ce);

extern zend_object * php_raylib_material_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_material_object_handlers;

typedef struct _php_raylib_material_object {
    Material material;
    HashTable *prop_handler;
    php_raylib_shader_object *shader;
php_raylib_materialmap_object *maps;
    zend_object std;
} php_raylib_material_object;

static inline php_raylib_material_object *php_raylib_material_fetch_object(zend_object *obj) {
    return (php_raylib_material_object *)((char *)obj - XtOffsetOf(php_raylib_material_object, std));
}

#define Z_MATERIAL_OBJ_P(zv) php_raylib_material_fetch_object(Z_OBJ_P(zv));

void php_raylib_material_startup(INIT_FUNC_ARGS);

extern void php_raylib_material_update_intern(php_raylib_material_object *intern);

#endif //PHP_RAYLIB_MATERIAL_H
