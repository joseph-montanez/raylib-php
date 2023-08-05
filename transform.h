#ifndef PHP_RAYLIB_TRANSFORM_H
#define PHP_RAYLIB_TRANSFORM_H

#include "include/hashmap.h"
#include "vector3.h"
#include "vector4.h"

extern zend_class_entry * php_raylib_transform_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);
extern void php_raylib_vector4_free_storage(zend_object *object);

extern void php_raylib_transform_free_storage(zend_object * object);

extern zend_object * php_raylib_transform_new(zend_class_entry * ce);

extern zend_object * php_raylib_transform_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_transform_object_handlers;

typedef enum {
    RL_TRANSFORM_IS_POINTER,
    RL_TRANSFORM_IS_VALUE
} RLTransformDataType;

typedef union {
    Transform *p;
    Transform v;
} TransformUnion;

struct RL_Transform {
    unsigned int id;
    char *guid;
    TransformUnion data;
    RLTransformDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Transform **RL_Transform_Object_List;
static hashmap *RL_Transform_Object_Map;

char* RL_Transform_Hash_Id(char *str, size_t size);
struct RL_Transform* RL_Transform_Create();
void RL_Transform_Delete(struct RL_Transform* object, int index);
void RL_Transform_Free(struct RL_Transform* object);

typedef struct _php_raylib_transform_object {
    struct RL_Transform *transform;
    HashTable *prop_handler;
    zval translation;
    zval rotation;
    zval scale;
    zend_object std;
} php_raylib_transform_object;

static inline php_raylib_transform_object *php_raylib_transform_fetch_object(zend_object *obj) {
    return (php_raylib_transform_object *)((char *)obj - XtOffsetOf(php_raylib_transform_object, std));
}

static inline Transform *php_raylib_transform_fetch_data(php_raylib_transform_object *obj) {
    Transform *my_transform;
    if (obj->transform->type == RL_TRANSFORM_IS_POINTER) {
        my_transform = obj->transform->data.p;
    } else {
        my_transform = &obj->transform->data.v;
    }

    return my_transform;
}

#define Z_TRANSFORM_OBJ_P(zv) php_raylib_transform_fetch_object(Z_OBJ_P(zv));

void php_raylib_transform_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_TRANSFORM_H
