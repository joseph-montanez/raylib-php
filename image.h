#ifndef PHP_RAYLIB_IMAGE_H
#define PHP_RAYLIB_IMAGE_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_image_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_image_free_storage(zend_object * object);

extern zend_object * php_raylib_image_new(zend_class_entry * ce);

extern zend_object * php_raylib_image_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_image_object_handlers;

struct RL_Image {
    unsigned int id;
    char *guid;
    Image data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Image **RL_Image_Object_List;
static hashmap *RL_Image_Object_Map;

char* RL_Image_Hash_Id(char *str, size_t size);
struct RL_Image* RL_Image_Create();
void RL_Image_Delete(struct RL_Image* object, int index);
void RL_Image_Free(struct RL_Image* object);

typedef struct _php_raylib_image_object {
    struct RL_Image *image;
    HashTable *prop_handler;
    // Cannot support primitive data structure like void * (an array) as zval
    // zval data;
    zend_object std;
} php_raylib_image_object;

static inline php_raylib_image_object *php_raylib_image_fetch_object(zend_object *obj) {
    return (php_raylib_image_object *)((char *)obj - XtOffsetOf(php_raylib_image_object, std));
}

#define Z_IMAGE_OBJ_P(zv) php_raylib_image_fetch_object(Z_OBJ_P(zv));

void php_raylib_image_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_IMAGE_H
