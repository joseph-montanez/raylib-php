#ifndef PHP_RAYLIB_BONEINFO_H
#define PHP_RAYLIB_BONEINFO_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_boneinfo_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_boneinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_boneinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_boneinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_boneinfo_object_handlers;

typedef enum {
    RL_BONEINFO_IS_POINTER,
    RL_BONEINFO_IS_VALUE
} RLBoneInfoDataType;

typedef union {
    BoneInfo *p;
    BoneInfo v;
} BoneInfoUnion;

struct RL_BoneInfo {
    unsigned int id;
    char *guid;
    BoneInfoUnion data;
    RLBoneInfoDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_BoneInfo **RL_BoneInfo_Object_List;
static hashmap *RL_BoneInfo_Object_Map;

char* RL_BoneInfo_Hash_Id(char *str, size_t size);
struct RL_BoneInfo* RL_BoneInfo_Create();
void RL_BoneInfo_Delete(struct RL_BoneInfo* object, int index);
void RL_BoneInfo_Free(struct RL_BoneInfo* object);

typedef struct _php_raylib_boneinfo_object {
    struct RL_BoneInfo *boneinfo;
    HashTable *prop_handler;
    // Cannot support primitive data structure like char (an array) as zval
    // zval name;
    zend_object std;
} php_raylib_boneinfo_object;

static inline php_raylib_boneinfo_object *php_raylib_boneinfo_fetch_object(zend_object *obj) {
    return (php_raylib_boneinfo_object *)((char *)obj - XtOffsetOf(php_raylib_boneinfo_object, std));
}

static inline BoneInfo *php_raylib_boneinfo_fetch_data(php_raylib_boneinfo_object *obj) {
    BoneInfo *my_boneinfo;
    if (obj->boneinfo->type == RL_BONEINFO_IS_POINTER) {
        my_boneinfo = obj->boneinfo->data.p;
    } else {
        my_boneinfo = &obj->boneinfo->data.v;
    }

    return my_boneinfo;
}

#define Z_BONEINFO_OBJ_P(zv) php_raylib_boneinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_boneinfo_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_BONEINFO_H
