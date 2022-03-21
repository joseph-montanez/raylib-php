#ifndef PHP_RAYLIB_SHADER_H
#define PHP_RAYLIB_SHADER_H


extern zend_class_entry * php_raylib_shader_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_shader_free_storage(zend_object * object);

extern zend_object * php_raylib_shader_new(zend_class_entry * ce);

extern zend_object * php_raylib_shader_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_shader_object_handlers;

typedef struct _php_raylib_shader_object {
    Shader shader;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_shader_object;

static inline php_raylib_shader_object *php_raylib_shader_fetch_object(zend_object *obj) {
    return (php_raylib_shader_object *)((char *)obj - XtOffsetOf(php_raylib_shader_object, std));
}

#define Z_SHADER_OBJ_P(zv) php_raylib_shader_fetch_object(Z_OBJ_P(zv));

void php_raylib_shader_startup(INIT_FUNC_ARGS);

extern void php_raylib_shader_update_intern(php_raylib_shader_object *intern);
extern void php_raylib_shader_update_intern_reverse(php_raylib_shader_object *intern);

#endif //PHP_RAYLIB_SHADER_H
