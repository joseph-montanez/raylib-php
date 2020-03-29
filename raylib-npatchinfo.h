//
// Created by Joseph Montanez on 2018-12-02.
//

#ifndef RAYLIB_RAYLIB_NPATCHINFO_H
#define RAYLIB_RAYLIB_NPATCHINFO_H

extern zend_class_entry *php_raylib_npatchinfo_ce;

typedef struct _php_raylib_npatchinfo_object {
    NPatchInfo npatchinfo;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_npatchinfo_object;

static inline php_raylib_npatchinfo_object *php_raylib_npatchinfo_fetch_object(zend_object *obj) {
    return (php_raylib_npatchinfo_object *)((char *)obj - XtOffsetOf(php_raylib_npatchinfo_object, std));
}

#define Z_NPATCHINFO_OBJ_P(zv) php_raylib_npatchinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_npatchinfo_startup(INIT_FUNC_ARGS);

#endif //RAYLIB_RAYLIB_NPATCHINFO_H
