//
// Created by Joseph Montanez on 4/6/18.
//

#ifndef RAYLIB_RAYLIB_UTILS_H
#define RAYLIB_RAYLIB_UTILS_H

#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#include "raylib.h"

struct Color php_array_to_color(zval *ar);
int zend_long_2int(zend_long val);

#endif //RAYLIB_RAYLIB_UTILS_H
