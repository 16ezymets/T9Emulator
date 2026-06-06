find_package(doctest REQUIRED)

add_executable(test_t9
    test_t9.cpp
    ../src/trie.cpp
    ../src/dictionary.cpp
    ../src/engine.cpp
)

target_include_directories(test_t9 PRIVATE ../src)
target_link_libraries(test_t9 PRIVATE doctest::doctest)

add_test(NAME T9Tests COMMAND test_t9)