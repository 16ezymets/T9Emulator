add_executable(test_t9
    test.cpp
    ../src/trie.cpp
    ../src/dictionary.cpp
    ../src/t9engine.cpp
)

target_link_libraries(test_t9 PRIVATE doctest::doctest)
target_include_directories(test_t9 PRIVATE ../src)

add_test(NAME T9Tests COMMAND test_t9)