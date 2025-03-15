cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(CPSC365EE2 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(interp interp.cpp)
# Can change optimization and profiling flags in the following line:
target_compile_options(interp PUBLIC -pg -O0)
target_link_options(interp PUBLIC -pg)



