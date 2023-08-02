#ifndef PHP_RAYLIB_SOUND_H
#define PHP_RAYLIB_SOUND_H

#include "include/hashmap.h"
#include "audiostream.h"

extern zend_class_entry * php_raylib_sound_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_audiostream_free_storage(zend_object *object);

extern void php_raylib_sound_free_storage(zend_object * object);

extern zend_object * php_raylib_sound_new(zend_class_entry * ce);

extern zend_object * php_raylib_sound_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_sound_object_handlers;

struct RL_Sound {
    unsigned int id;
    char *guid;
    Sound data;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_Sound **RL_Sound_Object_List;
static hashmap *RL_Sound_Object_Map;

char* RL_Sound_Hash_Id(char *str, size_t size);
struct RL_Sound* RL_Sound_Create();
void RL_Sound_Delete(struct RL_Sound* object, int index);
void RL_Sound_Free(struct RL_Sound* object);

typedef struct _php_raylib_sound_object {
    struct RL_Sound *sound;
    HashTable *prop_handler;
    zval stream;
    zend_object std;
} php_raylib_sound_object;

static inline php_raylib_sound_object *php_raylib_sound_fetch_object(zend_object *obj) {
    return (php_raylib_sound_object *)((char *)obj - XtOffsetOf(php_raylib_sound_object, std));
}

#define Z_SOUND_OBJ_P(zv) php_raylib_sound_fetch_object(Z_OBJ_P(zv));

void php_raylib_sound_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_SOUND_H
