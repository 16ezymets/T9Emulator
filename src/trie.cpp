/**
 * @file trie.cpp
 * @brief Реализация префиксного дерева
 */

#include "trie.h"

static const char *DIGIT_TO_LETTERS[] = {"",    "",    "abc",  "def", "ghi",
                                         "jkl", "mno", "pqrs", "tuv", "wxyz"};

Trie trie_create() {
  Trie trie;
  TrieNode root;
  root.children = std::vector<int>(ALPHABET_SIZE, NO_CHILD);
  root.is_end = false;
  root.freq = 0;
  trie.nodes.push_back(root);
  return trie;
}

void trie_insert(Trie &trie, const std::string &word, int freq) {
  int cur_idx = 0;

  for (size_t i = 0; i < word.length(); i++) {
    char c = word[i];
    if (c >= 'A' && c <= 'Z')
      c = c - 'A' + 'a';
    if (c < 'a' || c > 'z')
      continue;

    int letter_idx = c - 'a';

    // Создание дочернего узла, если его нет
    if (trie.nodes[cur_idx].children[letter_idx] == NO_CHILD) {
      TrieNode new_node;
      new_node.children = std::vector<int>(ALPHABET_SIZE, NO_CHILD);
      new_node.is_end = false;
      new_node.freq = 0;
      trie.nodes.push_back(new_node);
      trie.nodes[cur_idx].children[letter_idx] = trie.nodes.size() - 1;
    }

    cur_idx = trie.nodes[cur_idx].children[letter_idx];
  }

  trie.nodes[cur_idx].is_end = true;
  trie.nodes[cur_idx].freq = freq;
}

static void collect(Trie &trie, int node_idx, const std::string &prefix,
                    std::vector<std::pair<std::string, int>> &result) {
  if (node_idx == NO_CHILD)
    return;

  if (trie.nodes[node_idx].is_end)
    result.push_back({prefix, trie.nodes[node_idx].freq});

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    int child = trie.nodes[node_idx].children[i];
    if (child != NO_CHILD) {
      char letter = static_cast<char>('a' + i);
      collect(trie, child, prefix + letter, result);
    }
  }
}

static void traverse(Trie &trie, const std::string &digits, size_t pos,
                     int node_idx, const std::string &prefix,
                     std::vector<std::pair<std::string, int>> &result) {
  if (node_idx == NO_CHILD)
    return;
  if (pos >= digits.length()) {
    collect(trie, node_idx, prefix, result);
    return;
  }

  char digit = digits[pos];
  if (digit < '2' || digit > '9')
    return;

  const char *letters = DIGIT_TO_LETTERS[digit - '0'];
  for (int i = 0; letters[i] != '\0'; i++) {
    int letter_idx = letters[i] - 'a';
    int child = trie.nodes[node_idx].children[letter_idx];
    if (child != NO_CHILD)
      traverse(trie, digits, pos + 1, child, prefix + letters[i], result);
  }
}

static void sort_result(std::vector<std::pair<std::string, int>> &result) {
  size_t n = result.size();
  for (size_t i = 0; i < n; i++) {
    size_t max_idx = i;
    for (size_t j = i + 1; j < n; j++) {
      if (result[j].second > result[max_idx].second)
        max_idx = j;
    }
    if (max_idx != i)
      std::swap(result[i], result[max_idx]);
  }
}

std::vector<std::pair<std::string, int>> trie_find(Trie &trie,
                                                   const std::string &digits) {
  std::vector<std::pair<std::string, int>> result;
  if (digits.empty() || trie.nodes.empty())
    return result;

  for (size_t i = 0; i < digits.length(); i++)
    if (digits[i] < '2' || digits[i] > '9')
      return result;

  traverse(trie, digits, 0, 0, "", result);
  sort_result(result);
  return result;
}
