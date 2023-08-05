#ifndef PHP_RAYLIB_RECTANGLE_H
#define PHP_RAYLIB_RECTANGLE_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_rectangle_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_rectangle_free_storage(zend_object * object);

extern zend_object * php_raylib_rectangle_new(zend_class_entry * ce);

extern zend_object * php_raylib_rectangle_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_rectangle_object_handlers;

typedef enum {
    RL_RECTANGLE_IS_POINTER,
    RL_RECTANGLE_IS_VALUE
} RLRectangleDataType;

typedef union {
    Rectangle *p;
    Rectangle v;
} RectangleUnion;

struct RL_Rectangle {
    unsigned int id;
    char *guid;
    RectangleUnion data;
    RLRectangleDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Rectangle **RL_Rectangle_Object_List;
static hashmap *RL_Rectangle_Object_Map;

char* RL_Rectangle_Hash_Id(char *str, size_t size);
struct RL_Rectangle* RL_Rectangle_Create();
void RL_Rectangle_Delete(struct RL_Rectangle* object, int index);
void RL_Rectangle_Free(struct RL_Rectangle* object);

typedef struct _php_raylib_rectangle_object {
    struct RL_Rectangle *rectangle;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_rectangle_object;

static inline php_raylib_rectangle_object *php_raylib_rectangle_fetch_object(zend_object *obj) {
    return (php_raylib_rectangle_object *)((char *)obj - XtOffsetOf(php_raylib_rectangle_object, std));
}

static inline Rectangle *php_raylib_rectangle_fetch_data(php_raylib_rectangle_object *obj) {
    Rectangle *my_rectangle;
    if (obj->rectangle->type == RL_RECTANGLE_IS_POINTER) {
        my_rectangle = obj->rectangle->data.p;
    } else {
        my_rectangle = &obj->rectangle->data.v;
    }

    return my_rectangle;
}

#define Z_RECTANGLE_OBJ_P(zv) php_raylib_rectangle_fetch_object(Z_OBJ_P(zv));

void php_raylib_rectangle_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_RECTANGLE_H
