#ifndef PHP_RAYLIB_AUDIOSTREAM_H
#define PHP_RAYLIB_AUDIOSTREAM_H


extern zend_class_entry * php_raylib_audiostream_ce;

// External Free Objects - Prevent Circular Dependency
//TODO: Support array/hash
//extern void php_raylib_raudiobuffer_array_free_storage(zend_object *object);
extern void php_raylib_raudioprocessor__free_storage(zend_object *object);

extern void php_raylib_audiostream_free_storage(zend_object * object);

extern zend_object * php_raylib_audiostream_new(zend_class_entry * ce);

extern zend_object * php_raylib_audiostream_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_audiostream_object_handlers;

typedef struct _php_raylib_audiostream_object {
    AudioStream audiostream;
    HashTable *prop_handler;
// NO idea what to do with rAudioBuffer
//php_raylib_raudiobuffer_object *buffer;
    zval processor;
    zend_object std;
} php_raylib_audiostream_object;

static inline php_raylib_audiostream_object *php_raylib_audiostream_fetch_object(zend_object *obj) {
    return (php_raylib_audiostream_object *)((char *)obj - XtOffsetOf(php_raylib_audiostream_object, std));
}

#define Z_AUDIOSTREAM_OBJ_P(zv) php_raylib_audiostream_fetch_object(Z_OBJ_P(zv));

void php_raylib_audiostream_startup(INIT_FUNC_ARGS);

extern void php_raylib_audiostream_update_intern(php_raylib_audiostream_object *intern);
extern void php_raylib_audiostream_update_intern_reverse(php_raylib_audiostream_object *intern);

#endif //PHP_RAYLIB_AUDIOSTREAM_H
