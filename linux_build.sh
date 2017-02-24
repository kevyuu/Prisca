rm -r bin
mkdir bin

pushd bin

export LD_LIBRARY_PATH=/usr/lib64

EXTERNAL_LIB="-lglfw3 -ldl -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -lGLEW "

g++ -std=c++11 -g -Wno-reorder \
    ../demo/main.cpp \
    -I../external/include/ \
    $EXTERNAL_LIB
popd