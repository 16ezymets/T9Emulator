/**
 * @file dictionary.cpp
 * @brief Реализация загрузки словаря
 */

#include "dictionary.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void dict_load_file(Trie &trie, const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл словаря: " + filename);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::istringstream iss(line);
    std::string word;
    int freq = 0;

    if (!(iss >> word >> freq))
      continue;

    // В нижний регистр
    for (size_t i = 0; i < word.length(); i++) {
      if (word[i] >= 'A' && word[i] <= 'Z') {
        word[i] = word[i] - 'A' + 'a';
      }
    }

    trie_insert(trie, word, freq);
  }
}

void dict_load_builtin(Trie &trie) {
  trie_insert(trie, "hello", 150);
  trie_insert(trie, "help", 100);
  trie_insert(trie, "hell", 30);
  trie_insert(trie, "helicopter", 10);
  trie_insert(trie, "hill", 80);
  trie_insert(trie, "home", 200);
  trie_insert(trie, "good", 180);
  trie_insert(trie, "gone", 50);
  trie_insert(trie, "hood", 40);
  trie_insert(trie, "hope", 90);
  trie_insert(trie, "house", 120);
  trie_insert(trie, "how", 170);
  trie_insert(trie, "happy", 130);
  trie_insert(trie, "ice", 60);
  trie_insert(trie, "idea", 70);
  trie_insert(trie, "if", 190);
  trie_insert(trie, "in", 210);
  trie_insert(trie, "india", 45);
  trie_insert(trie, "ink", 35);
  trie_insert(trie, "inner", 25);
  trie_insert(trie, "cat", 160);
  trie_insert(trie, "call", 140);
  trie_insert(trie, "car", 110);
  trie_insert(trie, "apple", 155);
  trie_insert(trie, "application", 75);
}