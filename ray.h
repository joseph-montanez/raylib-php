#ifndef PHP_RAYLIB_RAY_H
#define PHP_RAYLIB_RAY_H

#include "include/hashmap.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_ray_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_ray_free_storage(zend_object * object);

extern zend_object * php_raylib_ray_new(zend_class_entry * ce);

extern zend_object * php_raylib_ray_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_ray_object_handlers;

struct RL_Ray {
    unsigned int id;
    char *guid;
    Ray data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Ray **RL_Ray_Object_List;
static hashmap *RL_Ray_Object_Map;

char* RL_Ray_Hash_Id(char *str, size_t size);
struct RL_Ray* RL_Ray_Create();
void RL_Ray_Delete(struct RL_Ray* object, int index);
void RL_Ray_Free(struct RL_Ray* object);

typedef struct _php_raylib_ray_object {
    struct RL_Ray *ray;
    HashTable *prop_handler;
    zval position;
    zval direction;
    zend_object std;
} php_raylib_ray_object;

static inline php_raylib_ray_object *php_raylib_ray_fetch_object(zend_object *obj) {
    return (php_raylib_ray_object *)((char *)obj - XtOffsetOf(php_raylib_ray_object, std));
}

#define Z_RAY_OBJ_P(zv) php_raylib_ray_fetch_object(Z_OBJ_P(zv));

void php_raylib_ray_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_RAY_H
