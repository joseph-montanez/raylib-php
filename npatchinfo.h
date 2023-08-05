#ifndef PHP_RAYLIB_NPATCHINFO_H
#define PHP_RAYLIB_NPATCHINFO_H

#include "include/hashmap.h"
#include "rectangle.h"

extern zend_class_entry * php_raylib_npatchinfo_ce;

// External Free Objects - Prevent Circular Dependency
extern void php_raylib_rectangle_free_storage(zend_object *object);

extern void php_raylib_npatchinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_npatchinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_npatchinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_npatchinfo_object_handlers;

typedef enum {
    RL_NPATCHINFO_IS_POINTER,
    RL_NPATCHINFO_IS_VALUE
} RLNPatchInfoDataType;

typedef union {
    NPatchInfo *p;
    NPatchInfo v;
} NPatchInfoUnion;

struct RL_NPatchInfo {
    unsigned int id;
    char *guid;
    NPatchInfoUnion data;
    RLNPatchInfoDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_NPatchInfo **RL_NPatchInfo_Object_List;
static hashmap *RL_NPatchInfo_Object_Map;

char* RL_NPatchInfo_Hash_Id(char *str, size_t size);
struct RL_NPatchInfo* RL_NPatchInfo_Create();
void RL_NPatchInfo_Delete(struct RL_NPatchInfo* object, int index);
void RL_NPatchInfo_Free(struct RL_NPatchInfo* object);

typedef struct _php_raylib_npatchinfo_object {
    struct RL_NPatchInfo *npatchinfo;
    HashTable *prop_handler;
    zval source;
    zend_object std;
} php_raylib_npatchinfo_object;

static inline php_raylib_npatchinfo_object *php_raylib_npatchinfo_fetch_object(zend_object *obj) {
    return (php_raylib_npatchinfo_object *)((char *)obj - XtOffsetOf(php_raylib_npatchinfo_object, std));
}

static inline NPatchInfo *php_raylib_npatchinfo_fetch_data(php_raylib_npatchinfo_object *obj) {
    NPatchInfo *my_npatchinfo;
    if (obj->npatchinfo->type == RL_NPATCHINFO_IS_POINTER) {
        my_npatchinfo = obj->npatchinfo->data.p;
    } else {
        my_npatchinfo = &obj->npatchinfo->data.v;
    }

    return my_npatchinfo;
}

#define Z_NPATCHINFO_OBJ_P(zv) php_raylib_npatchinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_npatchinfo_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_NPATCHINFO_H
