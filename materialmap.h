#ifndef PHP_RAYLIB_MATERIALMAP_H
#define PHP_RAYLIB_MATERIALMAP_H

#include "include/hashmap.h"
#include "texture.h"
#include "color.h"

extern zend_class_entry * php_raylib_materialmap_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_texture_free_storage(zend_object *object);
extern void php_raylib_color_free_storage(zend_object *object);

extern void php_raylib_materialmap_free_storage(zend_object * object);

extern zend_object * php_raylib_materialmap_new(zend_class_entry * ce);

extern zend_object * php_raylib_materialmap_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_materialmap_object_handlers;

struct RL_MaterialMap {
    unsigned int id;
    char *guid;
    MaterialMap data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_MaterialMap **RL_MaterialMap_Object_List;
static hashmap *RL_MaterialMap_Object_Map;

char* RL_MaterialMap_Hash_Id(char *str, size_t size);
struct RL_MaterialMap* RL_MaterialMap_Create();
void RL_MaterialMap_Delete(struct RL_MaterialMap* object, int index);
void RL_MaterialMap_Free(struct RL_MaterialMap* object);

typedef struct _php_raylib_materialmap_object {
    struct RL_MaterialMap *materialmap;
    HashTable *prop_handler;
    zval texture;
    zval color;
    zend_object std;
} php_raylib_materialmap_object;

static inline php_raylib_materialmap_object *php_raylib_materialmap_fetch_object(zend_object *obj) {
    return (php_raylib_materialmap_object *)((char *)obj - XtOffsetOf(php_raylib_materialmap_object, std));
}

#define Z_MATERIALMAP_OBJ_P(zv) php_raylib_materialmap_fetch_object(Z_OBJ_P(zv));

void php_raylib_materialmap_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_MATERIALMAP_H
