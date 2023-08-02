#ifndef PHP_RAYLIB_BOUNDINGBOX_H
#define PHP_RAYLIB_BOUNDINGBOX_H

#include "include/hashmap.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_boundingbox_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_boundingbox_free_storage(zend_object * object);

extern zend_object * php_raylib_boundingbox_new(zend_class_entry * ce);

extern zend_object * php_raylib_boundingbox_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_boundingbox_object_handlers;

struct RL_BoundingBox {
    unsigned int id;
    char *guid;
    BoundingBox data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_BoundingBox **RL_BoundingBox_Object_List;
static hashmap *RL_BoundingBox_Object_Map;

char* RL_BoundingBox_Hash_Id(char *str, size_t size);
struct RL_BoundingBox* RL_BoundingBox_Create();
void RL_BoundingBox_Delete(struct RL_BoundingBox* object, int index);
void RL_BoundingBox_Free(struct RL_BoundingBox* object);

typedef struct _php_raylib_boundingbox_object {
    struct RL_BoundingBox *boundingbox;
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

#endif //PHP_RAYLIB_BOUNDINGBOX_H
