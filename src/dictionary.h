/**
 * @file dictionary.h
 * @brief Загрузка словаря
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "trie.h"
#include <string>

void dict_load_file(Trie &trie, const std::string &filename);

void dict_load_builtin(Trie &trie);

#endif