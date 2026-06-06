cmake_minimum_required(VERSION 3.14)
project(T9_Emulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(t9_emulator
    src/main.cpp
    src/trie.cpp
    src/dictionary.cpp
    src/t9_engine.cpp
)

target_include_directories(t9_emulator PRIVATE src)

add_subdirectory(tests)