#ifndef PHP_RAYLIB_AUDIOSTREAM_H
#define PHP_RAYLIB_AUDIOSTREAM_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_audiostream_ce;

// External Free Objects - Prevent Circular Dependency
//TODO: Support array/hash
//extern void php_raylib_raudiobuffer_array_free_storage(zend_object *object);
extern void php_raylib_raudioprocessor__free_storage(zend_object *object);

extern void php_raylib_audiostream_free_storage(zend_object * object);

extern zend_object * php_raylib_audiostream_new(zend_class_entry * ce);

extern zend_object * php_raylib_audiostream_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_audiostream_object_handlers;

typedef enum {
    RL_AUDIOSTREAM_IS_POINTER,
    RL_AUDIOSTREAM_IS_VALUE
} RLAudioStreamDataType;

typedef union {
    AudioStream *p;
    AudioStream v;
} AudioStreamUnion;

struct RL_AudioStream {
    unsigned int id;
    char *guid;
    AudioStreamUnion data;
    RLAudioStreamDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_AudioStream **RL_AudioStream_Object_List;
static hashmap *RL_AudioStream_Object_Map;

char* RL_AudioStream_Hash_Id(char *str, size_t size);
struct RL_AudioStream* RL_AudioStream_Create();
void RL_AudioStream_Delete(struct RL_AudioStream* object, int index);
void RL_AudioStream_Free(struct RL_AudioStream* object);

typedef struct _php_raylib_audiostream_object {
    struct RL_AudioStream *audiostream;
    HashTable *prop_handler;
// NO idea what to do with rAudioBuffer
//php_raylib_raudiobuffer_object *buffer;
    zval processor;
    zend_object std;
} php_raylib_audiostream_object;

static inline php_raylib_audiostream_object *php_raylib_audiostream_fetch_object(zend_object *obj) {
    return (php_raylib_audiostream_object *)((char *)obj - XtOffsetOf(php_raylib_audiostream_object, std));
}

static inline AudioStream *php_raylib_audiostream_fetch_data(php_raylib_audiostream_object *obj) {
    AudioStream *my_audiostream;
    if (obj->audiostream->type == RL_AUDIOSTREAM_IS_POINTER) {
        my_audiostream = obj->audiostream->data.p;
    } else {
        my_audiostream = &obj->audiostream->data.v;
    }

    return my_audiostream;
}

#define Z_AUDIOSTREAM_OBJ_P(zv) php_raylib_audiostream_fetch_object(Z_OBJ_P(zv));

void php_raylib_audiostream_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_AUDIOSTREAM_H
