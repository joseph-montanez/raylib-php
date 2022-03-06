#ifndef PHP_RAYLIB_SOUND_H
#define PHP_RAYLIB_SOUND_H

#include "audiostream.h"

extern zend_class_entry * php_raylib_sound_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_audiostream_free_storage(zend_object *object);

extern void php_raylib_sound_free_storage(zend_object * object);

extern zend_object * php_raylib_sound_new(zend_class_entry * ce);

extern zend_object * php_raylib_sound_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_sound_object_handlers;

typedef struct _php_raylib_sound_object {
    Sound sound;
    HashTable *prop_handler;
    php_raylib_audiostream_object *stream;
    zend_object std;
} php_raylib_sound_object;

static inline php_raylib_sound_object *php_raylib_sound_fetch_object(zend_object *obj) {
    return (php_raylib_sound_object *)((char *)obj - XtOffsetOf(php_raylib_sound_object, std));
}

#define Z_SOUND_OBJ_P(zv) php_raylib_sound_fetch_object(Z_OBJ_P(zv));

void php_raylib_sound_startup(INIT_FUNC_ARGS);

extern void php_raylib_sound_update_intern(php_raylib_sound_object *intern);

#endif //PHP_RAYLIB_SOUND_H
