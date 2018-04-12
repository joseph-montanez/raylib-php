//
// Created by Joseph Montanez on 4/12/18.
//

#ifndef PHP_RAYLIB_COLLISION_H
#define PHP_RAYLIB_COLLISION_H

extern zend_class_entry *php_raylib_collision_ce;

typedef struct _php_raylib_collision_object {
    zend_object std;
} php_raylib_collision_object;

static inline php_raylib_collision_object *php_raylib_collision_fetch_object(zend_object *obj) {
    return (php_raylib_collision_object *)((char *)obj - XtOffsetOf(php_raylib_collision_object, std));
}

void php_raylib_collision_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_collision_new(zend_class_entry *ce TSRMLS_DC);

#define Z_COLLISION_OBJ_P(zv) php_raylib_collision_fetch_object(Z_OBJ_P(zv));

void php_raylib_collision_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_COLLISION_H
