#ifndef PHP_RAYLIB_VRDEVICEINFO_H
#define PHP_RAYLIB_VRDEVICEINFO_H

#include "include/hashmap.h"

extern zend_class_entry * php_raylib_vrdeviceinfo_ce;

// External Free Objects - Prevent Circular Dependency

extern void php_raylib_vrdeviceinfo_free_storage(zend_object * object);

extern zend_object * php_raylib_vrdeviceinfo_new(zend_class_entry * ce);

extern zend_object * php_raylib_vrdeviceinfo_new_ex(zend_class_entry *ce, zend_object *orig);

extern zend_object_handlers php_raylib_vrdeviceinfo_object_handlers;

typedef enum {
    RL_VRDEVICEINFO_IS_POINTER,
    RL_VRDEVICEINFO_IS_VALUE
} RLVrDeviceInfoDataType;

typedef union {
    VrDeviceInfo *p;
    VrDeviceInfo v;
} VrDeviceInfoUnion;

struct RL_VrDeviceInfo {
    unsigned int id;
    char *guid;
    VrDeviceInfoUnion data;
    RLVrDeviceInfoDataType type;
    unsigned refCount;
    unsigned char deleted;
};

static struct RL_VrDeviceInfo **RL_VrDeviceInfo_Object_List;
static hashmap *RL_VrDeviceInfo_Object_Map;

char* RL_VrDeviceInfo_Hash_Id(char *str, size_t size);
struct RL_VrDeviceInfo* RL_VrDeviceInfo_Create();
void RL_VrDeviceInfo_Delete(struct RL_VrDeviceInfo* object, int index);
void RL_VrDeviceInfo_Free(struct RL_VrDeviceInfo* object);

typedef struct _php_raylib_vrdeviceinfo_object {
    struct RL_VrDeviceInfo *vrdeviceinfo;
    HashTable *prop_handler;
    // Cannot support primitive data structure like float (an array) as zval
    // zval lensdistortionvalues;
    // Cannot support primitive data structure like float (an array) as zval
    // zval chromaabcorrection;
    zend_object std;
} php_raylib_vrdeviceinfo_object;

static inline php_raylib_vrdeviceinfo_object *php_raylib_vrdeviceinfo_fetch_object(zend_object *obj) {
    return (php_raylib_vrdeviceinfo_object *)((char *)obj - XtOffsetOf(php_raylib_vrdeviceinfo_object, std));
}

static inline VrDeviceInfo *php_raylib_vrdeviceinfo_fetch_data(php_raylib_vrdeviceinfo_object *obj) {
    VrDeviceInfo *my_vrdeviceinfo;
    if (obj->vrdeviceinfo->type == RL_VRDEVICEINFO_IS_POINTER) {
        my_vrdeviceinfo = obj->vrdeviceinfo->data.p;
    } else {
        my_vrdeviceinfo = &obj->vrdeviceinfo->data.v;
    }

    return my_vrdeviceinfo;
}

#define Z_VRDEVICEINFO_OBJ_P(zv) php_raylib_vrdeviceinfo_fetch_object(Z_OBJ_P(zv));

void php_raylib_vrdeviceinfo_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_VRDEVICEINFO_H
