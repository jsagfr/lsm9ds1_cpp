cmake_minimum_required (VERSION 2.6)
project (lsm9ds1)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_library(lsm9ds1 src/Lsm9ds1.cpp)
set_property(TARGET lsm9ds1 PROPERTY CXX_STANDARD 11)
set_property(TARGET lsm9ds1 PROPERTY CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

target_link_libraries(lsm9ds1 i2c++)
target_include_directories(lsm9ds1 PUBLIC include)
