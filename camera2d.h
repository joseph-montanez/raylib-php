#ifndef PHP_RAYLIB_CAMERA2D_H
#define PHP_RAYLIB_CAMERA2D_H

#include "include/hashmap.h"
#include "vector2.h"

extern zend_class_entry * php_raylib_camera2d_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_vector2_free_storage(zend_object *object);

extern void php_raylib_camera2d_free_storage(zend_object * object);

extern zend_object * php_raylib_camera2d_new(zend_class_entry * ce);

extern zend_object * php_raylib_camera2d_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_camera2d_object_handlers;

typedef enum {
    RL_CAMERA2D_IS_POINTER,
    RL_CAMERA2D_IS_VALUE
} RLCamera2DDataType;

typedef union {
    Camera2D *p;
    Camera2D v;
} Camera2DUnion;

struct RL_Camera2D {
    unsigned int id;
    char *guid;
    Camera2DUnion data;
    RLCamera2DDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Camera2D **RL_Camera2D_Object_List;
static hashmap *RL_Camera2D_Object_Map;

char* RL_Camera2D_Hash_Id(char *str, size_t size);
struct RL_Camera2D* RL_Camera2D_Create();
void RL_Camera2D_Delete(struct RL_Camera2D* object, int index);
void RL_Camera2D_Free(struct RL_Camera2D* object);

typedef struct _php_raylib_camera2d_object {
    struct RL_Camera2D *camera2d;
    HashTable *prop_handler;
    zval offset;
    zval target;
    zend_object std;
} php_raylib_camera2d_object;

static inline php_raylib_camera2d_object *php_raylib_camera2d_fetch_object(zend_object *obj) {
    return (php_raylib_camera2d_object *)((char *)obj - XtOffsetOf(php_raylib_camera2d_object, std));
}

static inline Camera2D *php_raylib_camera2d_fetch_data(php_raylib_camera2d_object *obj) {
    Camera2D *my_camera2d;
    if (obj->camera2d->type == RL_CAMERA2D_IS_POINTER) {
        my_camera2d = obj->camera2d->data.p;
    } else {
        my_camera2d = &obj->camera2d->data.v;
    }

    return my_camera2d;
}

#define Z_CAMERA2D_OBJ_P(zv) php_raylib_camera2d_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera2d_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CAMERA2D_H
