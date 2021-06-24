mkdir $1
cd $1
cp ../c ../r ../CMakeLists.txt .
mkdir bin
mkdir tests
cd bin
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cp compile_commands.json ..
