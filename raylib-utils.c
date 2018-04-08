//
// Created by Joseph Montanez on 4/6/18.
//

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
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

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef DrawTextA
#undef DrawTextExA
#undef LoadImageA