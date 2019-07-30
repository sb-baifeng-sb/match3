
mkdir build

if [ "$1" = "-clean" ]; then
    cd build
    make clean
    make
    cd ..
fi

cd build
cmake ..
make