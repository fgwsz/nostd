if(Test-Path -Path build){
    Remove-Item build -Recurse
}
mkdir build
cd build
cmake -G"MinGW Makefiles" ..
cmake --build .   
cd ..
./build/nostd.exe
