#ifndef PHP_RAYLIB_VECTOR4_H
#define PHP_RAYLIB_VECTOR4_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_vector4_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_vector4_free_storage(zend_object * object);

extern zend_object * php_raylib_vector4_new(zend_class_entry * ce);

extern zend_object * php_raylib_vector4_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_vector4_object_handlers;

struct RL_Vector4 {
    unsigned int id;
    char *guid;
    Vector4 data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Vector4 **RL_Vector4_Object_List;
static hashmap *RL_Vector4_Object_Map;

char* RL_Vector4_Hash_Id(char *str, size_t size);
struct RL_Vector4* RL_Vector4_Create();
void RL_Vector4_Delete(struct RL_Vector4* object, int index);
void RL_Vector4_Free(struct RL_Vector4* object);

typedef struct _php_raylib_vector4_object {
    struct RL_Vector4 *vector4;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_vector4_object;

static inline php_raylib_vector4_object *php_raylib_vector4_fetch_object(zend_object *obj) {
    return (php_raylib_vector4_object *)((char *)obj - XtOffsetOf(php_raylib_vector4_object, std));
}

#define Z_VECTOR4_OBJ_P(zv) php_raylib_vector4_fetch_object(Z_OBJ_P(zv));

void php_raylib_vector4_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_VECTOR4_H
