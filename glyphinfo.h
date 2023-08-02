#ifndef PHP_RAYLIB_GLYPHINFO_H
#define PHP_RAYLIB_GLYPHINFO_H

#include "include/hashmap.h"
#include "image.h"

extern zend_class_entry * php_raylib_glyphinfo_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_image_free_storage(zend_object *object);

extern void php_raylib_glyphinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_glyphinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_glyphinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_glyphinfo_object_handlers;

struct RL_GlyphInfo {
    unsigned int id;
    char *guid;
    GlyphInfo data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_GlyphInfo **RL_GlyphInfo_Object_List;
static hashmap *RL_GlyphInfo_Object_Map;

char* RL_GlyphInfo_Hash_Id(char *str, size_t size);
struct RL_GlyphInfo* RL_GlyphInfo_Create();
void RL_GlyphInfo_Delete(struct RL_GlyphInfo* object, int index);
void RL_GlyphInfo_Free(struct RL_GlyphInfo* object);

typedef struct _php_raylib_glyphinfo_object {
    struct RL_GlyphInfo *glyphinfo;
    HashTable *prop_handler;
    zval image;
    zend_object std;
} php_raylib_glyphinfo_object;

static inline php_raylib_glyphinfo_object *php_raylib_glyphinfo_fetch_object(zend_object *obj) {
    return (php_raylib_glyphinfo_object *)((char *)obj - XtOffsetOf(php_raylib_glyphinfo_object, std));
}

#define Z_GLYPHINFO_OBJ_P(zv) php_raylib_glyphinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_glyphinfo_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_GLYPHINFO_H
