cmake_minimum_required(VERSION 3.8)
project(raylib)

add_custom_target(makefile COMMAND phpize && ./configure -enable-debug  && make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(build COMMAND make WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(clean-build COMMAND phpize --clean)

set(SOURCE_FILES raylib.c raylib-texture.c raylib-image.c raylib-texture.h raylib-image.h raylib-utils.c raylib-utils.h raylib-window.c raylib-window.h raylib-cursor.c raylib-cursor.h raylib-draw.c raylib-draw.h raylib-timming.c raylib-timming.h raylib-rendertexture.c raylib-rendertexture.h raylib-camera.c raylib-camera.h raylib-camera2d.c raylib-camera2d.h raylib-spritefont.c raylib-spritefont.h raylib-text.c raylib-text.h raylib-key.c raylib-key.h raylib-mouse.c raylib-mouse.h raylib-collision.c raylib-collision.h raylib-color.c raylib-color.h)

set(PHP_SOURCE /usr/local/include/php/)
include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/sapi)
include_directories(${PHP_SOURCE}/pear)
include_directories(${PHP_SOURCE}/TSRM)
include_directories(${PHP_SOURCE})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(raylib ${SOURCE_FILES})