//
// Created by Joseph Montanez on 4/6/18.
//

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