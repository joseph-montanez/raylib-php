#ifndef PHP_RAYLIB_VRSTEREOCONFIG_H
#define PHP_RAYLIB_VRSTEREOCONFIG_H

#include "include/hashmap.h"
#include "matrix.h"

extern zend_class_entry * php_raylib_vrstereoconfig_ce;

// External Free Objects - Prevent Circular Dependency
//TODO: Support array/hash
//extern void php_raylib_matrix_array_free_storage(zend_object *object);

extern void php_raylib_vrstereoconfig_free_storage(zend_object * object);

extern zend_object * php_raylib_vrstereoconfig_new(zend_class_entry * ce);

extern zend_object * php_raylib_vrstereoconfig_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_vrstereoconfig_object_handlers;

struct RL_VrStereoConfig {
    unsigned int id;
    char *guid;
    VrStereoConfig data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_VrStereoConfig **RL_VrStereoConfig_Object_List;
static hashmap *RL_VrStereoConfig_Object_Map;

char* RL_VrStereoConfig_Hash_Id(char *str, size_t size);
struct RL_VrStereoConfig* RL_VrStereoConfig_Create();
void RL_VrStereoConfig_Delete(struct RL_VrStereoConfig* object, int index);
void RL_VrStereoConfig_Free(struct RL_VrStereoConfig* object);

typedef struct _php_raylib_vrstereoconfig_object {
    struct RL_VrStereoConfig *vrstereoconfig;
    HashTable *prop_handler;
    zval projection;
    zval viewoffset;
    zend_object std;
} php_raylib_vrstereoconfig_object;

static inline php_raylib_vrstereoconfig_object *php_raylib_vrstereoconfig_fetch_object(zend_object *obj) {
    return (php_raylib_vrstereoconfig_object *)((char *)obj - XtOffsetOf(php_raylib_vrstereoconfig_object, std));
}

#define Z_VRSTEREOCONFIG_OBJ_P(zv) php_raylib_vrstereoconfig_fetch_object(Z_OBJ_P(zv));

void php_raylib_vrstereoconfig_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_VRSTEREOCONFIG_H
