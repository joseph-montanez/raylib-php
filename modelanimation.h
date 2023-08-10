#ifndef PHP_RAYLIB_MODELANIMATION_H
#define PHP_RAYLIB_MODELANIMATION_H

#include "include/hashmap.h"
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

typedef enum {
    RL_MODELANIMATION_IS_POINTER,
    RL_MODELANIMATION_IS_VALUE
} RLModelAnimationDataType;

typedef union {
    ModelAnimation *p;
    ModelAnimation v;
} ModelAnimationUnion;

struct RL_ModelAnimation {
    unsigned int id;
    char *guid;
    ModelAnimationUnion data;
    RLModelAnimationDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_ModelAnimation **RL_ModelAnimation_Object_List;
static hashmap *RL_ModelAnimation_Object_Map;

char* RL_ModelAnimation_Hash_Id(char *str, size_t size);
struct RL_ModelAnimation* RL_ModelAnimation_Create();
void RL_ModelAnimation_Delete(struct RL_ModelAnimation* object, int index);
void RL_ModelAnimation_Free(struct RL_ModelAnimation* object);

typedef struct _php_raylib_modelanimation_object {
    struct RL_ModelAnimation *modelanimation;
    HashTable *prop_handler;
    zval bones;
    zval frameposes;
    zend_object std;
} php_raylib_modelanimation_object;

static inline php_raylib_modelanimation_object *php_raylib_modelanimation_fetch_object(zend_object *obj) {
    return (php_raylib_modelanimation_object *)((char *)obj - XtOffsetOf(php_raylib_modelanimation_object, std));
}

static inline ModelAnimation *php_raylib_modelanimation_fetch_data(php_raylib_modelanimation_object *obj) {
    ModelAnimation *my_modelanimation;
    if (obj->modelanimation->type == RL_MODELANIMATION_IS_POINTER) {
        my_modelanimation = obj->modelanimation->data.p;
    } else {
        my_modelanimation = &obj->modelanimation->data.v;
    }

    return my_modelanimation;
}

#define Z_MODELANIMATION_OBJ_P(zv) php_raylib_modelanimation_fetch_object(Z_OBJ_P(zv));

void php_raylib_modelanimation_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MODELANIMATION_H
