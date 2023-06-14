if(Test-Path -Path build){}else{
    mkdir build
}
cd build
cmake -G"MinGW Makefiles" ..
cmake --build .   
cd ..
./build/nostd.exe
