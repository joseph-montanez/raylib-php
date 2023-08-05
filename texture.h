#ifndef PHP_RAYLIB_TEXTURE_H
#define PHP_RAYLIB_TEXTURE_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_texture_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_texture_free_storage(zend_object * object);

extern zend_object * php_raylib_texture_new(zend_class_entry * ce);

extern zend_object * php_raylib_texture_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_texture_object_handlers;

typedef enum {
    RL_TEXTURE_IS_POINTER,
    RL_TEXTURE_IS_VALUE
} RLTextureDataType;

typedef union {
    Texture *p;
    Texture v;
} TextureUnion;

struct RL_Texture {
    unsigned int id;
    char *guid;
    TextureUnion data;
    RLTextureDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Texture **RL_Texture_Object_List;
static hashmap *RL_Texture_Object_Map;

char* RL_Texture_Hash_Id(char *str, size_t size);
struct RL_Texture* RL_Texture_Create();
void RL_Texture_Delete(struct RL_Texture* object, int index);
void RL_Texture_Free(struct RL_Texture* object);

typedef struct _php_raylib_texture_object {
    struct RL_Texture *texture;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_texture_object;

static inline php_raylib_texture_object *php_raylib_texture_fetch_object(zend_object *obj) {
    return (php_raylib_texture_object *)((char *)obj - XtOffsetOf(php_raylib_texture_object, std));
}

static inline Texture *php_raylib_texture_fetch_data(php_raylib_texture_object *obj) {
    Texture *my_texture;
    if (obj->texture->type == RL_TEXTURE_IS_POINTER) {
        my_texture = obj->texture->data.p;
    } else {
        my_texture = &obj->texture->data.v;
    }

    return my_texture;
}

#define Z_TEXTURE_OBJ_P(zv) php_raylib_texture_fetch_object(Z_OBJ_P(zv));

void php_raylib_texture_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_TEXTURE_H
