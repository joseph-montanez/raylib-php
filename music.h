#ifndef PHP_RAYLIB_MUSIC_H
#define PHP_RAYLIB_MUSIC_H

#include "audiostream.h"

extern zend_class_entry * php_raylib_music_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_audiostream_free_storage(zend_object *object);

extern void php_raylib_music_free_storage(zend_object * object);

extern zend_object * php_raylib_music_new(zend_class_entry * ce);

extern zend_object * php_raylib_music_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_music_object_handlers;

typedef struct _php_raylib_music_object {
    Music music;
    HashTable *prop_handler;
    zval stream;
    zend_object std;
} php_raylib_music_object;

static inline php_raylib_music_object *php_raylib_music_fetch_object(zend_object *obj) {
    return (php_raylib_music_object *)((char *)obj - XtOffsetOf(php_raylib_music_object, std));
}

#define Z_MUSIC_OBJ_P(zv) php_raylib_music_fetch_object(Z_OBJ_P(zv));

void php_raylib_music_startup(INIT_FUNC_ARGS);

extern void php_raylib_music_update_intern(php_raylib_music_object *intern);
extern void php_raylib_music_update_intern_reverse(php_raylib_music_object *intern);

#endif //PHP_RAYLIB_MUSIC_H
