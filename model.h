#ifndef PHP_RAYLIB_MODEL_H
#define PHP_RAYLIB_MODEL_H

#include "include/hashmap.h"
#include "matrix.h"
#include "mesh.h"
#include "material.h"
#include "boneinfo.h"
#include "transform.h"

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

typedef enum {
    RL_MODEL_IS_POINTER,
    RL_MODEL_IS_VALUE
} RLModelDataType;

typedef union {
    Model *p;
    Model v;
} ModelUnion;

struct RL_Model {
    unsigned int id;
    char *guid;
    ModelUnion data;
    RLModelDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Model **RL_Model_Object_List;
static hashmap *RL_Model_Object_Map;

char* RL_Model_Hash_Id(char *str, size_t size);
struct RL_Model* RL_Model_Create();
void RL_Model_Delete(struct RL_Model* object, int index);
void RL_Model_Free(struct RL_Model* object);

typedef struct _php_raylib_model_object {
    struct RL_Model *model;
    HashTable *prop_handler;
    zval transform;
    zval meshes;
    zval materials;
    zval bones;
    zval bindpose;
    // Cannot support primitive data structure like int * (an array) as zval
    // zval meshmaterial;
    zend_object std;
} php_raylib_model_object;

static inline php_raylib_model_object *php_raylib_model_fetch_object(zend_object *obj) {
    return (php_raylib_model_object *)((char *)obj - XtOffsetOf(php_raylib_model_object, std));
}

static inline Model *php_raylib_model_fetch_data(php_raylib_model_object *obj) {
    Model *my_model;
    if (obj->model->type == RL_MODEL_IS_POINTER) {
        my_model = obj->model->data.p;
    } else {
        my_model = &obj->model->data.v;
    }

    return my_model;
}

#define Z_MODEL_OBJ_P(zv) php_raylib_model_fetch_object(Z_OBJ_P(zv));

void php_raylib_model_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MODEL_H
