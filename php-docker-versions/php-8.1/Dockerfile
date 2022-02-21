FROM php:8.1.2-zts

RUN apt-get update && apt-get install -y build-essential git cmake libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev libzip-dev xvfb

RUN git clone --depth 1 -b 4.0.0 https://github.com/raysan5/raylib.git raylib
# CMAKE
#RUN cd raylib && mkdir build && cd build && cmake -DOpenGL_GL_PREFERENCE=GLVND -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON .. && make && make install
# Old Build
RUN cd raylib/src && make && make install

RUN     mkdir ~/.vnc
# Setup a password
RUN     x11vnc -storepasswd 1234 ~/.vnc/passwd

# Build PHP
RUN docker-php-ext-install zip

# PHP Composer
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer