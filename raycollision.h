#ifndef PHP_RAYLIB_RAYCOLLISION_H
#define PHP_RAYLIB_RAYCOLLISION_H

#include "include/hashmap.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_raycollision_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_raycollision_free_storage(zend_object * object);

extern zend_object * php_raylib_raycollision_new(zend_class_entry * ce);

extern zend_object * php_raylib_raycollision_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_raycollision_object_handlers;

struct RL_RayCollision {
    unsigned int id;
    char *guid;
    RayCollision data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_RayCollision **RL_RayCollision_Object_List;
static hashmap *RL_RayCollision_Object_Map;

char* RL_RayCollision_Hash_Id(char *str, size_t size);
struct RL_RayCollision* RL_RayCollision_Create();
void RL_RayCollision_Delete(struct RL_RayCollision* object, int index);
void RL_RayCollision_Free(struct RL_RayCollision* object);

typedef struct _php_raylib_raycollision_object {
    struct RL_RayCollision *raycollision;
    HashTable *prop_handler;
    zval point;
    zval normal;
    zend_object std;
} php_raylib_raycollision_object;

static inline php_raylib_raycollision_object *php_raylib_raycollision_fetch_object(zend_object *obj) {
    return (php_raylib_raycollision_object *)((char *)obj - XtOffsetOf(php_raylib_raycollision_object, std));
}

#define Z_RAYCOLLISION_OBJ_P(zv) php_raylib_raycollision_fetch_object(Z_OBJ_P(zv));

void php_raylib_raycollision_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_RAYCOLLISION_H
