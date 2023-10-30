mkdir build && cd build
conan install ..
conan build ..
./src/test
