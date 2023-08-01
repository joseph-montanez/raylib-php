#ifndef PHP_RAYLIB_FONT_H
#define PHP_RAYLIB_FONT_H

#include "include/hashmap.h"
#include "texture.h"
#include "rectangle.h"
#include "glyphinfo.h"

extern zend_class_entry * php_raylib_font_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_texture_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_rectangle_array_free_storage(zend_object *object);
//TODO: Support array/hash
//extern void php_raylib_glyphinfo_array_free_storage(zend_object *object);

extern void php_raylib_font_free_storage(zend_object * object);

extern zend_object * php_raylib_font_new(zend_class_entry * ce);

extern zend_object * php_raylib_font_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_font_object_handlers;

struct RL_Font {
    unsigned int id;
    char *guid;
    Font data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Font **RL_Font_Object_List;
static hashmap *RL_Font_Object_Map;

char* RL_Font_Hash_Id(char *str, size_t size);
struct RL_Font* RL_Font_Create();
void RL_Font_Delete(struct RL_Font* object, int index);
void RL_Font_Free(struct RL_Font* object);

typedef struct _php_raylib_font_object {
    struct RL_Font *font;
    HashTable *prop_handler;
    zval texture;
    zval recs;
    zval glyphs;
    zend_object std;
} php_raylib_font_object;

static inline php_raylib_font_object *php_raylib_font_fetch_object(zend_object *obj) {
    return (php_raylib_font_object *)((char *)obj - XtOffsetOf(php_raylib_font_object, std));
}

#define Z_FONT_OBJ_P(zv) php_raylib_font_fetch_object(Z_OBJ_P(zv));

void php_raylib_font_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_FONT_H
