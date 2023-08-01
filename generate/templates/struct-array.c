unsigned int RL_VECTOR3_OBJECT_ID = 0;
unsigned char RL_VECTOR3_INIT = 0;
const unsigned int RL_VECTOR3_MAX_OBJECTS = 999999;

struct RL_Vector3 {
    unsigned int id;
    const char guid[36];
    Vector3 data;
    unsigned refCount;
    unsigned char deleted;
};

struct RL_Vector3 **RL_Vector3_Object_List;
hashmap *RL_Vector3_Object_Map;

char[32] RL_Vector3_Hash_Id(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charset_size = sizeof(charset) - 1;
    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < size - 1; i++) {
        int index = rand() % charset_size;
        str[i] = charset[index];
    }
    str[size-1] = '\0';
    return str;
}

struct RL_Vector3* RL_Vector3_Create() {
    //-- Create the initial data structures
    if (RL_VECTOR3_INIT == 0) {
        RL_Vector3_Object_List = (struct RL_Vector3**) malloc(0);
        RL_Vector3_Object_Map = hashmap_create();
        RL_VECTOR3_INIT = 1;
    }

    //-- Create the container object
    struct RL_Vector3* object = (struct RL_Vector3*) malloc(sizeof(struct RL_Vector3));
    object->id = RL_VECTOR3_OBJECT_ID++;
    object->guid = RL_Vector3_Hash_Id(object->guid, sizeof(object->guid)); // Generate hash ID
    object->refCount = 1;
    object->deleted = 0;

    //-- Push to the dynamic array list
    RL_Vector3_Object_List = (struct RL_Vector3**) realloc(RL_Vector3_Object_List, RL_VECTOR3_OBJECT_ID * sizeof(struct RL_Vector3*));
    RL_Vector3_Object_List[object->id] = object;

    //-- Add to hashmap
    hashmap_set(RL_Vector3_Object_Map, object->guid, sizeof(object->guid) - 1, object);

    return object;
}

void RL_Vector3_Delete(struct RL_Vector3* object, int index) {
    if (index < 0 || index >= RL_VECTOR3_OBJECT_ID) {
        // Error: invalid index
        return;
    }

    hashmap_remove(RL_Vector3_Object_Map, object->guid, sizeof(object->guid) -1);

    // Free the memory for the element being deleted
    free(RL_Vector3_Object_List[index]);

    // Shift the remaining elements over by one
    memmove(&RL_Vector3_Object_List[index], &RL_Vector3_Object_List[index + 1], (RL_VECTOR3_OBJECT_ID - index - 1) * sizeof(struct RL_Vector3 *));

    // Decrement the count and resize the array
    RL_VECTOR3_OBJECT_ID--;
    RL_Vector3_Object_List = (struct RL_Vector3 **)realloc(list, (RL_VECTOR3_OBJECT_ID) * sizeof(struct RL_Vector3 *));
}

void RL_Vector3_Free(struct RL_Vector3* object) {
    free(object);
}