cmake_minimum_required(VERSION 3.8)
project(raylib)

add_custom_target(makefile COMMAND phpize && ./configure -enable-debug  && make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(build COMMAND make WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za /GR /Zi /W4")
add_definitions(-DZEND_WIN32 -DPHP_WIN32 -DZEND_DEBUG=0)
add_custom_target(clean-build COMMAND phpize --clean)

set(SOURCE_FILES raylib.c raylib-vector4.c raylib-vector4.h raylib-vector3.c raylib-vector3.h raylib-vector2.c raylib-vector2.h raylib-texture.c raylib-image.c raylib-texture.h raylib-image.h raylib-utils.c raylib-utils.h raylib-window.c raylib-window.h raylib-cursor.c raylib-cursor.h raylib-draw.c raylib-draw.h raylib-timming.c raylib-timming.h raylib-rendertexture.c raylib-rendertexture.h raylib-camera3d.c raylib-camera3d.h raylib-camera2d.c raylib-camera2d.h raylib-font.c raylib-font.h raylib-text.c raylib-text.h raylib-key.c raylib-key.h raylib-mouse.c raylib-mouse.h raylib-collision.c raylib-collision.h raylib-color.c raylib-color.h raylib-rectangle.c raylib-rectangle.h)

set(RAYLIB_SOURCE C:/src/raylib-2.6.0/src)
set(PHP_SOURCE C:/php-sdk/phpmaster/vc15/x64/php-src)
include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/sapi)
include_directories(${PHP_SOURCE}/pear)
include_directories(${PHP_SOURCE}/TSRM)
include_directories(${PHP_SOURCE})
include_directories(${RAYLIB_SOURCE})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(raylib ${SOURCE_FILES})