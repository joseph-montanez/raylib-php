#ifndef PHP_RAYLIB_MESH_H
#define PHP_RAYLIB_MESH_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_mesh_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_mesh_free_storage(zend_object * object);

extern zend_object * php_raylib_mesh_new(zend_class_entry * ce);

extern zend_object * php_raylib_mesh_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_mesh_object_handlers;

typedef enum {
    RL_MESH_IS_POINTER,
    RL_MESH_IS_VALUE
} RLMeshDataType;

typedef union {
    Mesh *p;
    Mesh v;
} MeshUnion;

struct RL_Mesh {
    unsigned int id;
    char *guid;
    MeshUnion data;
    RLMeshDataType type;
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
    // Cannot support primitive data structure like float * (an array) as zval
    // zval vertices;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval texcoords;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval texcoords2;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval normals;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval tangents;
    // Cannot support primitive data structure like unsigned char * (an array) as zval
    // zval colors;
    // Cannot support primitive data structure like unsigned short * (an array) as zval
    // zval indices;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval animvertices;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval animnormals;
    // Cannot support primitive data structure like unsigned char * (an array) as zval
    // zval boneids;
    // Cannot support primitive data structure like float * (an array) as zval
    // zval boneweights;
    zend_object std;
} php_raylib_mesh_object;

static inline php_raylib_mesh_object *php_raylib_mesh_fetch_object(zend_object *obj) {
    return (php_raylib_mesh_object *)((char *)obj - XtOffsetOf(php_raylib_mesh_object, std));
}

static inline Mesh *php_raylib_mesh_fetch_data(php_raylib_mesh_object *obj) {
    Mesh *my_mesh;
    if (obj->mesh->type == RL_MESH_IS_POINTER) {
        my_mesh = obj->mesh->data.p;
    } else {
        my_mesh = &obj->mesh->data.v;
    }

    return my_mesh;
}

#define Z_MESH_OBJ_P(zv) php_raylib_mesh_fetch_object(Z_OBJ_P(zv));

void php_raylib_mesh_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MESH_H
