/**
 * @file trie.h
 * @brief Префиксное дерево для словаря T9
 */

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;
const int NO_CHILD = -1;

/**
 * @brief Узел префиксного дерева
 *
 * Хранит индексы дочерних узлов, флаг конца слова и частоту.
 * Все узлы дерева лежат в общем векторе Trie::nodes.
 */
struct TrieNode {
  std::vector<int> children;
  bool is_end;
  int freq;
};

/**
 * @brief Префиксное дерево
 *
 * Все узлы хранятся в одном векторе nodes.
 * Корень всегда имеет индекс 0.
 */
struct Trie {
  std::vector<TrieNode> nodes;
};

/**
 * @brief Создать пустое дерево
 * @return Указатель на корень
 */
Trie trie_create();

/**
 * @brief Добавить слово в дерево
 * @param trie Дерево
 * @param word Слово
 * @param freq Частота
 */
void trie_insert(Trie &trie, const std::string &word, int freq);

/**
 * @brief Найти слова по цифровой последовательности T9
 * @param trie Дерево
 * @param digits Строка цифр ('2'-'9')
 * @return Вектор пар (слово, частота), отсортированный по убыванию частоты
 */
std::vector<std::pair<std::string, int>> trie_find(Trie &trie,
                                                   const std::string &digits);

#endif