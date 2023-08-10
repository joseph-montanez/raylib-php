#ifndef PHP_RAYLIB_VECTOR2_H
#define PHP_RAYLIB_VECTOR2_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_vector2_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_vector2_free_storage(zend_object * object);

extern zend_object * php_raylib_vector2_new(zend_class_entry * ce);

extern zend_object * php_raylib_vector2_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_vector2_object_handlers;

typedef enum {
    RL_VECTOR2_IS_POINTER,
    RL_VECTOR2_IS_VALUE
} RLVector2DataType;

typedef union {
    Vector2 *p;
    Vector2 v;
} Vector2Union;

struct RL_Vector2 {
    unsigned int id;
    char *guid;
    Vector2Union data;
    RLVector2DataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Vector2 **RL_Vector2_Object_List;
static hashmap *RL_Vector2_Object_Map;

char* RL_Vector2_Hash_Id(char *str, size_t size);
struct RL_Vector2* RL_Vector2_Create();
void RL_Vector2_Delete(struct RL_Vector2* object, int index);
void RL_Vector2_Free(struct RL_Vector2* object);

typedef struct _php_raylib_vector2_object {
    struct RL_Vector2 *vector2;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector2_object;

static inline php_raylib_vector2_object *php_raylib_vector2_fetch_object(zend_object *obj) {
    return (php_raylib_vector2_object *)((char *)obj - XtOffsetOf(php_raylib_vector2_object, std));
}

static inline Vector2 *php_raylib_vector2_fetch_data(php_raylib_vector2_object *obj) {
    Vector2 *my_vector2;
    if (obj->vector2->type == RL_VECTOR2_IS_POINTER) {
        my_vector2 = obj->vector2->data.p;
    } else {
        my_vector2 = &obj->vector2->data.v;
    }

    return my_vector2;
}

#define Z_VECTOR2_OBJ_P(zv) php_raylib_vector2_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector2_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_VECTOR2_H
