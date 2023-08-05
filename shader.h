#ifndef PHP_RAYLIB_SHADER_H
#define PHP_RAYLIB_SHADER_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_shader_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_shader_free_storage(zend_object * object);

extern zend_object * php_raylib_shader_new(zend_class_entry * ce);

extern zend_object * php_raylib_shader_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_shader_object_handlers;

typedef enum {
    RL_SHADER_IS_POINTER,
    RL_SHADER_IS_VALUE
} RLShaderDataType;

typedef union {
    Shader *p;
    Shader v;
} ShaderUnion;

struct RL_Shader {
    unsigned int id;
    char *guid;
    ShaderUnion data;
    RLShaderDataType type;
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
    // Cannot support primitive data structure like int * (an array) as zval
    // zval locs;
    zend_object std;
} php_raylib_shader_object;

static inline php_raylib_shader_object *php_raylib_shader_fetch_object(zend_object *obj) {
    return (php_raylib_shader_object *)((char *)obj - XtOffsetOf(php_raylib_shader_object, std));
}

static inline Shader *php_raylib_shader_fetch_data(php_raylib_shader_object *obj) {
    Shader *my_shader;
    if (obj->shader->type == RL_SHADER_IS_POINTER) {
        my_shader = obj->shader->data.p;
    } else {
        my_shader = &obj->shader->data.v;
    }

    return my_shader;
}

#define Z_SHADER_OBJ_P(zv) php_raylib_shader_fetch_object(Z_OBJ_P(zv));

void php_raylib_shader_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_SHADER_H
