FROM php:8.0.2-zts

RUN apt-get update && apt-get install -y build-essential git cmake libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev libzip-dev

RUN git clone --depth 1 https://github.com/raysan5/raylib.git raylib
RUN cd raylib && mkdir build && cd build && cmake -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON .. && make && make install

# Build PHP
RUN docker-php-ext-install zip

# PHP Composer
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer