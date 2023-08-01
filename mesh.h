#ifndef PHP_RAYLIB_MESH_H
#define PHP_RAYLIB_MESH_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_mesh_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_mesh_free_storage(zend_object * object);

extern zend_object * php_raylib_mesh_new(zend_class_entry * ce);

extern zend_object * php_raylib_mesh_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_mesh_object_handlers;

struct RL_Mesh {
    unsigned int id;
    char *guid;
    Mesh data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Mesh **RL_Mesh_Object_List;
static hashmap *RL_Mesh_Object_Map;

char* RL_Mesh_Hash_Id(char *str, size_t size);
struct RL_Mesh* RL_Mesh_Create();
void RL_Mesh_Delete(struct RL_Mesh* object, int index);
void RL_Mesh_Free(struct RL_Mesh* object);

typedef struct _php_raylib_mesh_object {
    struct RL_Mesh *mesh;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_mesh_object;

static inline php_raylib_mesh_object *php_raylib_mesh_fetch_object(zend_object *obj) {
    return (php_raylib_mesh_object *)((char *)obj - XtOffsetOf(php_raylib_mesh_object, std));
}

#define Z_MESH_OBJ_P(zv) php_raylib_mesh_fetch_object(Z_OBJ_P(zv));

void php_raylib_mesh_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MESH_H
