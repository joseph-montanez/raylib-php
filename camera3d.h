#ifndef PHP_RAYLIB_CAMERA3D_H
#define PHP_RAYLIB_CAMERA3D_H

#include "include/hashmap.h"
#include "vector3.h"

extern zend_class_entry * php_raylib_camera3d_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector3_free_storage(zend_object *object);

extern void php_raylib_camera3d_free_storage(zend_object * object);

extern zend_object * php_raylib_camera3d_new(zend_class_entry * ce);

extern zend_object * php_raylib_camera3d_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_camera3d_object_handlers;

typedef enum {
    RL_CAMERA3D_IS_POINTER,
    RL_CAMERA3D_IS_VALUE
} RLCamera3DDataType;

typedef union {
    Camera3D *p;
    Camera3D v;
} Camera3DUnion;

struct RL_Camera3D {
    unsigned int id;
    char *guid;
    Camera3DUnion data;
    RLCamera3DDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Camera3D **RL_Camera3D_Object_List;
static hashmap *RL_Camera3D_Object_Map;

char* RL_Camera3D_Hash_Id(char *str, size_t size);
struct RL_Camera3D* RL_Camera3D_Create();
void RL_Camera3D_Delete(struct RL_Camera3D* object, int index);
void RL_Camera3D_Free(struct RL_Camera3D* object);

typedef struct _php_raylib_camera3d_object {
    struct RL_Camera3D *camera3d;
    HashTable *prop_handler;
    zval position;
    zval target;
    zval up;
    zend_object std;
} php_raylib_camera3d_object;

static inline php_raylib_camera3d_object *php_raylib_camera3d_fetch_object(zend_object *obj) {
    return (php_raylib_camera3d_object *)((char *)obj - XtOffsetOf(php_raylib_camera3d_object, std));
}

static inline Camera3D *php_raylib_camera3d_fetch_data(php_raylib_camera3d_object *obj) {
    Camera3D *my_camera3d;
    if (obj->camera3d->type == RL_CAMERA3D_IS_POINTER) {
        my_camera3d = obj->camera3d->data.p;
    } else {
        my_camera3d = &obj->camera3d->data.v;
    }

    return my_camera3d;
}

#define Z_CAMERA3D_OBJ_P(zv) php_raylib_camera3d_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera3d_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CAMERA3D_H
