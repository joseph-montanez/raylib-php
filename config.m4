dnl $Id$
dnl config.m4 for extension raylib

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(raylib, for raylib support,
Make sure that the comment is aligned:
[  --with-raylib             Include raylib support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(raylib, whether to enable raylib support,
Make sure that the comment is aligned:
[  --enable-raylib           Enable raylib support])

if test "$PHP_RAYLIB" != "no"; then
  dnl Write more examples of tests here...

  # get library FOO build options from pkg-config output
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  AC_MSG_CHECKING(for libraylib)
  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists raylib; then
    if $PKG_CONFIG raylib --atleast-version 4.5.0; then
      LIBRAYLIB_CFLAGS=`$PKG_CONFIG raylib --cflags`
      LIBRAYLIB_LIBDIR=`$PKG_CONFIG raylib --libs`
      LIBRAYLIB_VERSON=`$PKG_CONFIG raylib --modversion`
      AC_MSG_RESULT(from pkgconfig: version $LIBRAYLIB_VERSON)
    else
      AC_MSG_ERROR(system libraylib is too old: version 4.5.0 required)
    fi
  else
    AC_MSG_ERROR(pkg-config not found)
  fi
  PHP_EVAL_LIBLINE($LIBRAYLIB_LIBDIR, RAYLIB_SHARED_LIBADD)
  PHP_EVAL_INCLINE($LIBRAYLIB_CFLAGS)

  dnl # --with-raylib -> check with-path
  SEARCH_PATH="/usr/local /usr /opt/homebrew/Cellar/raylib/4.5.0 ./cmake-build-debug/_deps/raylib-src/src"     # you might want to change this
  SEARCH_FOR="/include/raylib.h"  # you most likely want to change this
  if test -r $PHP_RAYLIB/$SEARCH_FOR; then # path given as parameter
    RAYLIB_DIR=$PHP_RAYLIB
  else # search default path list
    AC_MSG_CHECKING([for raylib files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        RAYLIB_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$RAYLIB_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the raylib distribution])
  fi

  dnl # --with-raylib -> add include path
  PHP_ADD_INCLUDE($RAYLIB_DIR/include)

  dnl # --with-raylib -> check for lib and symbol presence
  LIBNAME=raylib # you may want to change this
  LIBSYMBOL=SetMouseScale # you most likely want to change this

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $RAYLIB_DIR/$PHP_LIBDIR, RAYLIB_SHARED_LIBADD)
    AC_DEFINE(HAVE_RAYLIBLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong raylib lib version or lib not found])
  ],[
    -L$RAYLIB_DIR/$PHP_LIBDIR -lm
  ])

  PHP_SUBST(RAYLIB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(raylib, raylib.c vector2.c vector3.c vector4.c matrix.c color.c rectangle.c image.c texture.c rendertexture.c npatchinfo.c glyphinfo.c font.c camera3d.c camera2d.c mesh.c shader.c materialmap.c material.c transform.c boneinfo.c model.c modelanimation.c ray.c raycollision.c boundingbox.c wave.c audiostream.c sound.c music.c vrdeviceinfo.c vrstereoconfig.c filepathlist.c include/hashmap.c, $ext_shared,)
fi