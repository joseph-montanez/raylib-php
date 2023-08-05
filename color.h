#ifndef PHP_RAYLIB_COLOR_H
#define PHP_RAYLIB_COLOR_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_color_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_color_free_storage(zend_object * object);

extern zend_object * php_raylib_color_new(zend_class_entry * ce);

extern zend_object * php_raylib_color_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_color_object_handlers;

typedef enum {
    RL_COLOR_IS_POINTER,
    RL_COLOR_IS_VALUE
} RLColorDataType;

typedef union {
    Color *p;
    Color v;
} ColorUnion;

struct RL_Color {
    unsigned int id;
    char *guid;
    ColorUnion data;
    RLColorDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Color **RL_Color_Object_List;
static hashmap *RL_Color_Object_Map;

char* RL_Color_Hash_Id(char *str, size_t size);
struct RL_Color* RL_Color_Create();
void RL_Color_Delete(struct RL_Color* object, int index);
void RL_Color_Free(struct RL_Color* object);

typedef struct _php_raylib_color_object {
    struct RL_Color *color;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_color_object;

static inline php_raylib_color_object *php_raylib_color_fetch_object(zend_object *obj) {
    return (php_raylib_color_object *)((char *)obj - XtOffsetOf(php_raylib_color_object, std));
}

static inline Color *php_raylib_color_fetch_data(php_raylib_color_object *obj) {
    Color *my_color;
    if (obj->color->type == RL_COLOR_IS_POINTER) {
        my_color = obj->color->data.p;
    } else {
        my_color = &obj->color->data.v;
    }

    return my_color;
}

#define Z_COLOR_OBJ_P(zv) php_raylib_color_fetch_object(Z_OBJ_P(zv));

void php_raylib_color_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_COLOR_H
