What I am trying to do is hold onto another PHP object in an internal struct. I.E:
```php
<?php

$camera3d = new Camera3D();
$camera3d->position = new Vector3();
$camera3d->position->x++;
```

The reason of this is because the Camera3D struct has additional data I need to track:

```c
// Camera, defines position/orientation in 3d space
typedef struct Camera3D {
	Vector3 position; // Camera position
	Vector3 target; // Camera target it looks-at
	Vector3 up; // Camera up vector (rotation over its axis)
	float fovy; // Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
	int projection; // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
} Camera3D;
```

The ideal is that when `$camera3d->position` is modified, I can update the internal Camera3D struct based on this tracked PHP Object.

Right now it looks like this, but attaching additional internal object in PHP is an issue:

```c
typedef struct _php_raylib_camera3d_object {
	Camera3D camera3d;
	HashTable *prop_handler;
	php_raylib_vector3_object *position; // $camera3d->position
	php_raylib_vector3_object *target; // $camera3d->target
	php_raylib_vector3_object *up; // $camera3d->up
	zend_object std;
} php_raylib_camera3d_object;
```

Just for reference, this is how a getter the C code looks like:

```c
static zend_object * php_raylib_camera2d_get_position(php_raylib_camera3d_object *obj) /* {{{ */
{
    GC_ADDREF(&obj->position->std);
    return &obj->position->std;
}
/* }}} */
```

This is how the setter looks like in C:

```c
static int php_raylib_camera3d_set_position(php_raylib_camera3d_object *obj, zval *newval) /* {{{ */
{
    int ret = SUCCESS;

    if (Z_TYPE_P(newval) == IS_NULL) {
        // Cannot set this to null...
        return ret;
    }

    php_raylib_vector2_object *phpPosition = Z_VECTOR2_OBJ_P(newval);
    GC_ADDREF(&phpPosition->std);
    GC_DELREF(&obj->phpPosition->std);
    obj->position = phpPosition;

    return ret;
}
/* }}} */
```


When in a PHP Loop, accessing the other internal object works, but on for the first time i.e

```c
// Update camera position for selected mode  
// RLAPI void UpdateCamera(Camera3D * camera);  
ZEND_BEGIN_ARG_INFO_EX(arginfo_UpdateCamera, 0, 1, 1)  
    ZEND_ARG_INFO(1, camera)  
ZEND_END_ARG_INFO()  
PHP_FUNCTION(UpdateCamera)  
{
    zval *camera;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(camera)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_camera3d_object *phpCamera = Z_CAMERA3D_OBJ_P(camera);
    
    printf("UpdateCamera:camera3d position %f %f %f\n", phpCamera->position->vector3.x, phpCamera->position->vector3.y, phpCamera->position->vector3.z);
    ...
}
```

The first time this is ran, it fine. But on the second iteration, it segment vaults with an access violation.

Oddly enough, if I move the `prop_handler` down in the struct it then works:

```c
	typedef struct _php_raylib_camera3d_object {
	    Camera3D camera3d;
	    php_raylib_vector3_object *position;
	    php_raylib_vector3_object *target;
	    php_raylib_vector3_object *up;
	    HashTable *prop_handler; // prop_handler moved
	    zend_object std;
	} php_raylib_camera3d_object;
```

However this ONLY works for accessing the PHP `position` object, accessing the `target` then gives the same access violation.

I did try to convert all the other internal objects from pointers to non-pointers:
```c
	typedef struct _php_raylib_camera3d_object {
	    Camera3D camera3d;
	    php_raylib_vector3_object position;
	    php_raylib_vector3_object target;
	    php_raylib_vector3_object up;
	    HashTable *prop_handler; // prop_handler moved
	    zend_object std;
	} php_raylib_camera3d_object;
```

The application no longer crashed... While this did seem to work, internal references were completely disconnected. So the raw `Camera3D` values were completely separate from the attached `Camera3D` PHP Objects (position, target, up). For example:

```php
UpdateCamera($camera3d); //-- should update $camera3d->position

BeginDrawing();
BeginMode3D($camera);
```

That above should update `$camera->position` vector values. It didn't. In the C-code it was assigned to the following, right :

```c
UpdateCamera(&intern->camera3d);

phpPosition->vector3.x = intern->camera3d.position.x;
phpPosition->vector3.y = intern->camera3d.position.y;  
phpPosition->vector3.z = intern->camera3d.position.z;
```

I even tried to `printf` to ensure the values are set. The `UpdateCamera` did not actrually change the camera position... So I tried updating the attached PHP Object in PHP for the position vector i.e

```php
<?php

UpdateCamera($camera3d); //-- doesn't update camera position...
$camera3d->position->x += 0.001; //--- This updates the camera position...

BeginDrawing();
BeginMode3D($camera);
```

This is really weird because `$camera3d->position->x` is not the root `camera3d` **structure**! Now granted I do the reverse assignment before `UpdateCamera` is called.

```c  
//....
intern->camera3d.position = phpPosition->vector3; // assigns $camera3d->position back to the internal camera position
UpdateCamera(&intern->camera3d);
phpPosition->vector3 = intern->camera3d.position; // assigns internval camera3d struct position back to $camera3d->position
//....
```
