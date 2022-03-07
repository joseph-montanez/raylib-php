cmake_minimum_required(VERSION 3.21)
project(raylib C)

set(CMAKE_C_STANDARD 11)

include_directories(. ../../main/ ../../../deps/include)

add_executable(raylib
        audiostream.c
        audiostream.h
        boneinfo.c
        boneinfo.h
        boundingbox.c
        boundingbox.h
        camera2d.c
        camera2d.h
        camera3d.c
        camera3d.h
        color.c
        color.h
        font.c
        font.h
        glyphinfo.c
        glyphinfo.h
        image.c
        image.h
        material.c
        material.h
        materialmap.c
        materialmap.h
        matrix.c
        matrix.h
        mesh.c
        mesh.h
        model.c
        model.h
        modelanimation.c
        modelanimation.h
        music.c
        music.h
        npatchinfo.c
        npatchinfo.h
        php_raylib.h
        ray.c
        ray.h
        raycollision.c
        raycollision.h
        raylib.c
        rectangle.c
        rectangle.h
        rendertexture.c
        rendertexture.h
        shader.c
        shader.h
        sound.c
        sound.h
        texture.c
        texture.h
        transform.c
        transform.h
        vector2.c
        vector2.h
        vector3.c
        vector3.h
        vector4.c
        vector4.h
        vrdeviceinfo.c
        vrdeviceinfo.h
        vrstereoconfig.c
        vrstereoconfig.h
        wave.c
        wave.h)
