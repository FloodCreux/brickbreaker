#!/bin/bash

mkdir -p build
pushd build
pwd

# Build Raylib
mkdir -p raylib
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/rcore.c -o raylib/rcore.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/raudio.c -o raylib/raudio.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -x objective-c -c ../include/raylib/src/rglfw.c -o raylib/rglfw.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/rmodels.c -o raylib/rmodels.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/rshapes.c -o raylib/rshapes.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/rtext.c -o raylib/rtext.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/rtextures.c -o raylib/rtextures.o
clang -g -DPLATFORM_DESKTOP -fPIC -DSUPPORT_FILEFORMAT_FLAC=1 \
    -I../include/raylib/src/external/glfw/include \
    -DGRAPHICS_API_OPENGL_33 -c ../include/raylib/src/utils.c -o raylib/utils.o

cc -shared -fPIC -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL \
    -install_name @rpath/libraylib.dylib -o raylib/libraylib.dylib \
    raylib/rcore.o raylib/raudio.o raylib/rglfw.o raylib/rmodels.o raylib/rshapes.o raylib/rtext.o raylib/rtextures.o raylib/utils.o

# Build the executable
clang -Wall -Wextra -g -I. -I../include/raylib/src/ -o brickbreaker ../src/brickbreaker.c \
    raylib/libraylib.dylib \
    -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL \
    -lm -ldl -lpthread -rpath . -rpath raylib

popd
