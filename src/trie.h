/**
 * @file trie.h
 * @brief Префиксное дерево для словаря T9
 */

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;

/// Узел префиксного дерева
struct TrieNode
{
    std::vector<TrieNode*> children;  ///< Дочерние узлы (26 букв)
    bool is_end;                      ///< Конец слова
    int freq;                         ///< Частота слова
};

/// Префиксное дерево: добавление слов, поиск по цифрам T9
struct Trie
{
    TrieNode* root;
};

/**
 * @brief Создать пустое дерево
 * @return Указатель на корень
 */
Trie trie_create();

/**
 * @brief Удалить дерево и освободить память
 * @param trie Дерево
 */
void trie_destroy(Trie& trie);

/**
 * @brief Добавить слово в дерево
 * @param trie Дерево
 * @param word Слово
 * @param freq Частота
 */
void trie_insert(Trie& trie, const std::string& word, int freq);

/**
 * @brief Найти слова по цифровой последовательности T9
 * @param trie Дерево
 * @param digits Строка цифр ('2'-'9')
 * @return Вектор пар (слово, частота), отсортированный по убыванию частоты
 */
std::vector<std::pair<std::string, int>> trie_find(Trie& trie, const std::string& digits);

#endif