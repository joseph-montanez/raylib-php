#ifndef PHP_RAYLIB_RENDERTEXTURE_H
#define PHP_RAYLIB_RENDERTEXTURE_H

#include "include/hashmap.h"
#include "texture.h"

extern zend_class_entry * php_raylib_rendertexture_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_texture_free_storage(zend_object *object);

extern void php_raylib_rendertexture_free_storage(zend_object * object);

extern zend_object * php_raylib_rendertexture_new(zend_class_entry * ce);

extern zend_object * php_raylib_rendertexture_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_rendertexture_object_handlers;

typedef enum {
    RL_RENDERTEXTURE_IS_POINTER,
    RL_RENDERTEXTURE_IS_VALUE
} RLRenderTextureDataType;

typedef union {
    RenderTexture *p;
    RenderTexture v;
} RenderTextureUnion;

struct RL_RenderTexture {
    unsigned int id;
    char *guid;
    RenderTextureUnion data;
    RLRenderTextureDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_RenderTexture **RL_RenderTexture_Object_List;
static hashmap *RL_RenderTexture_Object_Map;

char* RL_RenderTexture_Hash_Id(char *str, size_t size);
struct RL_RenderTexture* RL_RenderTexture_Create();
void RL_RenderTexture_Delete(struct RL_RenderTexture* object, int index);
void RL_RenderTexture_Free(struct RL_RenderTexture* object);

typedef struct _php_raylib_rendertexture_object {
    struct RL_RenderTexture *rendertexture;
    HashTable *prop_handler;
    zval texture;
    zval depth;
    zend_object std;
} php_raylib_rendertexture_object;

static inline php_raylib_rendertexture_object *php_raylib_rendertexture_fetch_object(zend_object *obj) {
    return (php_raylib_rendertexture_object *)((char *)obj - XtOffsetOf(php_raylib_rendertexture_object, std));
}

static inline RenderTexture *php_raylib_rendertexture_fetch_data(php_raylib_rendertexture_object *obj) {
    RenderTexture *my_rendertexture;
    if (obj->rendertexture->type == RL_RENDERTEXTURE_IS_POINTER) {
        my_rendertexture = obj->rendertexture->data.p;
    } else {
        my_rendertexture = &obj->rendertexture->data.v;
    }

    return my_rendertexture;
}

#define Z_RENDERTEXTURE_OBJ_P(zv) php_raylib_rendertexture_fetch_object(Z_OBJ_P(zv));

void php_raylib_rendertexture_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_RENDERTEXTURE_H
