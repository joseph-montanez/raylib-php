#ifndef PHP_RAYLIB_SHADER_H
#define PHP_RAYLIB_SHADER_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_shader_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_shader_free_storage(zend_object * object);

extern zend_object * php_raylib_shader_new(zend_class_entry * ce);

extern zend_object * php_raylib_shader_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_shader_object_handlers;

struct RL_Shader {
    unsigned int id;
    char *guid;
    Shader data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Shader **RL_Shader_Object_List;
static hashmap *RL_Shader_Object_Map;

char* RL_Shader_Hash_Id(char *str, size_t size);
struct RL_Shader* RL_Shader_Create();
void RL_Shader_Delete(struct RL_Shader* object, int index);
void RL_Shader_Free(struct RL_Shader* object);

typedef struct _php_raylib_shader_object {
    struct RL_Shader *shader;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_shader_object;

static inline php_raylib_shader_object *php_raylib_shader_fetch_object(zend_object *obj) {
    return (php_raylib_shader_object *)((char *)obj - XtOffsetOf(php_raylib_shader_object, std));
}

#define Z_SHADER_OBJ_P(zv) php_raylib_shader_fetch_object(Z_OBJ_P(zv));

void php_raylib_shader_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_SHADER_H
