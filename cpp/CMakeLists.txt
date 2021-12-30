cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER clang++)

project(
    AdventOfCode2021
    VERSION 0.0.1
    LANGUAGES CXX
)

add_compile_options(-Wall -Wextra -Wpedantic -O3 -march=native)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 8.0.1
)

FetchContent_Declare(vectorclass
  GIT_REPOSITORY https://github.com/vectorclass/version2.git
  GIT_TAG v2.01.04
)

set(ABSL_PROPAGATE_CXX_STD ON)
FetchContent_Declare(abseil_cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG 20211102.0
)

FetchContent_MakeAvailable(fmt vectorclass abseil_cpp)

include_directories(${vectorclass_SOURCE_DIR})

add_executable(
    main
    common.cc
    main.cc
    day01.cc
    day02.cc
    day03.cc
    day04.cc
    day06.cc
    day07.cc
    day12.cc
    day14.cc
    day15.cc
    day20.cc
    day25.cc
)
target_link_libraries(main PUBLIC fmt::fmt absl::base absl::flat_hash_map absl::hash)