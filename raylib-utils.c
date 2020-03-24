/* If defined, the following flags inhibit definition of the indicated items.*/
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include "php.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-utils.h"

struct Color php_array_to_color(zval *ar) {
    HashTable *arr_hash;
    long num_key;
    zval *val;
    zend_string *key;

    unsigned char* r = (unsigned char *) 255;
    unsigned char* g = (unsigned char *) 255;
    unsigned char* b = (unsigned char *) 255;
    unsigned char* a = (unsigned char *) 255;

    arr_hash = Z_ARRVAL_P(ar);
    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
                if (Z_TYPE_P(val) == IS_LONG) {
                    switch(num_key) {
                        case 0:
                            r = (unsigned char*) val;
                        case 1:
                            g = (unsigned char*) val;
                        case 2:
                            b = (unsigned char*) val;
                        case 3:
                            a = (unsigned char*) val;
                    }
                }
            } ZEND_HASH_FOREACH_END();

    struct Color color = { *r, *b, *g, *a };
    return color;
}

int zend_long_2int(zend_long val) {
    return (val <= INT_MAX) ? (int)((zend_long)val) : -1;
}

float zend_double_2float(zval *val) {
    if (Z_TYPE_P(val) == IS_DOUBLE) {
        return (float) Z_DVAL_P(val);
    } else if (Z_TYPE_P(val) == IS_LONG) {
        return (float) Z_LVAL_P(val);
    } else {
        return 0.0f;
    }
}

struct Vector3 php_array_to_vector3(zval *ar) {
    HashTable *arr_hash;
    long num_key;
    zval *val = NULL;
    zend_string *key;

    struct Vector3 vector;

    arr_hash = Z_ARRVAL_P(ar);
    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
                if (key) {
                    if (zend_string_equals_literal(key, "x")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                vector.x = (float) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                vector.x = (float) Z_LVAL_P(val);
                                break;
                            default:
                                vector.x = 0.0f;
                                break;
                        }
                    } else if (zend_string_equals_literal(key, "y")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                vector.y = (float) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                vector.y = (float) Z_LVAL_P(val);
                                break;
                            default:
                                vector.y = 0.0f;
                                break;
                        }
                    } else if (zend_string_equals_literal(key, "z")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                vector.z = (float) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                vector.z = (float) Z_LVAL_P(val);
                                break;
                            default:
                                vector.z = 0.0f;
                                break;
                        }
                    }
                }
            } ZEND_HASH_FOREACH_END();

    return vector;
}

struct Vector2 php_array_to_vector2(zval *ar) {
    HashTable *arr_hash;
    long num_key;
    zval *val = NULL;
    zend_string *key;

    struct Vector2 vector;

    arr_hash = Z_ARRVAL_P(ar);
    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
                if (key) {
                    if (zend_string_equals_literal(key, "x")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                vector.x = (float) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                vector.x = (float) Z_LVAL_P(val);
                                break;
                            default:
                                vector.x = 0.0f;
                                break;

                        }
                    } else if (zend_string_equals_literal(key, "y")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                vector.y = (float) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                vector.y = (float) Z_LVAL_P(val);
                                break;
                            default:
                                vector.y = 0.0f;
                                break;
                        }
                    }
                }
            } ZEND_HASH_FOREACH_END();

    return vector;
}


struct Rectangle php_array_to_rec(zval *ar) {
    HashTable *arr_hash;
    long num_key;
    zval *val = NULL;
    zend_string *key;

    struct Rectangle rec;

    arr_hash = Z_ARRVAL_P(ar);
    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
                if (key) {
                    if (zend_string_equals_literal(key, "x")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                rec.x = (int) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                rec.x = (int) Z_LVAL_P(val);
                                break;
                            default:
                                rec.x = 0.0f;
                                break;
                        }
                    } else if (zend_string_equals_literal(key, "y")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                rec.y = (int) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                rec.y = (int) Z_LVAL_P(val);
                                break;
                            default:
                                rec.y = 0.0f;
                                break;
                        }
                    } else if (zend_string_equals_literal(key, "width")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                rec.width = (int) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                rec.width = (int) Z_LVAL_P(val);
                                break;
                            default:
                                rec.width = 0;
                                break;
                        }
                    } else if (zend_string_equals_literal(key, "height")) {
                        switch (Z_TYPE_P(val)) {
                            case IS_DOUBLE:
                                rec.height = (int) Z_DVAL_P(val);
                                break;
                            case IS_LONG:
                                rec.height = (int) Z_LVAL_P(val);
                                break;
                            default:
                                rec.height = 0;
                                break;
                        }
                    }
                }
            } ZEND_HASH_FOREACH_END();

    return rec;
}