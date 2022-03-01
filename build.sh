bash clean.sh
phpize
./configure
make clean
make
#Xvfb :1 -ac -screen 0 1024x768x16 +extension GLX +extension R./clen  ENDER &
#export DISPLAY=:1
#php -dextension=modules/raylib.so examples/core/2d-camera.php