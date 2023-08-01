#ifndef PHP_RAYLIB_WAVE_H
#define PHP_RAYLIB_WAVE_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_wave_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_wave_free_storage(zend_object * object);

extern zend_object * php_raylib_wave_new(zend_class_entry * ce);

extern zend_object * php_raylib_wave_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_wave_object_handlers;

struct RL_Wave {
    unsigned int id;
    char *guid;
    Wave data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Wave **RL_Wave_Object_List;
static hashmap *RL_Wave_Object_Map;

char* RL_Wave_Hash_Id(char *str, size_t size);
struct RL_Wave* RL_Wave_Create();
void RL_Wave_Delete(struct RL_Wave* object, int index);
void RL_Wave_Free(struct RL_Wave* object);

typedef struct _php_raylib_wave_object {
    struct RL_Wave *wave;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_wave_object;

static inline php_raylib_wave_object *php_raylib_wave_fetch_object(zend_object *obj) {
    return (php_raylib_wave_object *)((char *)obj - XtOffsetOf(php_raylib_wave_object, std));
}

#define Z_WAVE_OBJ_P(zv) php_raylib_wave_fetch_object(Z_OBJ_P(zv));

void php_raylib_wave_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_WAVE_H
