#ifndef PHP_RAYLIB_FILEPATHLIST_H
#define PHP_RAYLIB_FILEPATHLIST_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_filepathlist_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_filepathlist_free_storage(zend_object * object);

extern zend_object * php_raylib_filepathlist_new(zend_class_entry * ce);

extern zend_object * php_raylib_filepathlist_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_filepathlist_object_handlers;

typedef enum {
    RL_FILEPATHLIST_IS_POINTER,
    RL_FILEPATHLIST_IS_VALUE
} RLFilePathListDataType;

typedef union {
    FilePathList *p;
    FilePathList v;
} FilePathListUnion;

struct RL_FilePathList {
    unsigned int id;
    char *guid;
    FilePathListUnion data;
    RLFilePathListDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_FilePathList **RL_FilePathList_Object_List;
static hashmap *RL_FilePathList_Object_Map;

char* RL_FilePathList_Hash_Id(char *str, size_t size);
struct RL_FilePathList* RL_FilePathList_Create();
void RL_FilePathList_Delete(struct RL_FilePathList* object, int index);
void RL_FilePathList_Free(struct RL_FilePathList* object);

typedef struct _php_raylib_filepathlist_object {
    struct RL_FilePathList *filepathlist;
    HashTable *prop_handler;
    zend_object std;
} php_raylib_filepathlist_object;

static inline php_raylib_filepathlist_object *php_raylib_filepathlist_fetch_object(zend_object *obj) {
    return (php_raylib_filepathlist_object *)((char *)obj - XtOffsetOf(php_raylib_filepathlist_object, std));
}

static inline FilePathList *php_raylib_filepathlist_fetch_data(php_raylib_filepathlist_object *obj) {
    FilePathList *my_filepathlist;
    if (obj->filepathlist->type == RL_FILEPATHLIST_IS_POINTER) {
        my_filepathlist = obj->filepathlist->data.p;
    } else {
        my_filepathlist = &obj->filepathlist->data.v;
    }

    return my_filepathlist;
}

#define Z_FILEPATHLIST_OBJ_P(zv) php_raylib_filepathlist_fetch_object(Z_OBJ_P(zv));

void php_raylib_filepathlist_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_FILEPATHLIST_H
