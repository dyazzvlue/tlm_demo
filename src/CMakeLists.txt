aux_source_directory(./ SRC)
set(SOURCE ${SRC}
    )

add_executable(test main.cpp)

target_compile_features(test PRIVATE cxx_std_20)

target_include_directories(test PRIVATE 
    "${PROJECT_SOURCE_DIR}/include/"
    "${CONAN_INCLUDE_DIRS}"
    ${CONAN_INCLUDE_DIRS_SYSTEMC}
    )

target_link_libraries(test 
    PUBLIC
    SystemC::systemc
)
target_compile_options(test PUBLIC -fPIC)
