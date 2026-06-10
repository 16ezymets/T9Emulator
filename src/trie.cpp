/**
 * @file trie.cpp
 * @brief Реализация префиксного дерева
 */

#include "trie.h"

static const char* DIGIT_TO_LETTERS[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

Trie trie_create()
{
    Trie trie;
    trie.root = new TrieNode();
    trie.root->children = std::vector<TrieNode*>(ALPHABET_SIZE, nullptr);
    trie.root->is_end = false;
    trie.root->freq = 0;
    return trie;
}

static void delete_node(TrieNode* node)
{
    if (node == nullptr) return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            delete_node(node->children[i]);
        }
    }

    delete node;
}

void trie_destroy(Trie& trie)
{
    delete_node(trie.root);
    trie.root = nullptr;
}

void trie_insert(Trie& trie, const std::string& word, int freq)
{
    if (trie.root == nullptr) return;

    TrieNode* cur = trie.root;

    for (size_t i = 0; i < word.length(); i++)
    {
        char c = word[i];
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        if (c < 'a' || c > 'z') continue;

        int idx = c - 'a';

        if (cur->children[idx] == nullptr)
        {
            cur->children[idx] = new TrieNode();
            cur->children[idx]->children = std::vector<TrieNode*>(ALPHABET_SIZE, nullptr);
            cur->children[idx]->is_end = false;
            cur->children[idx]->freq = 0;
        }

        cur = cur->children[idx];
    }

    cur->is_end = true;
    cur->freq = freq;
}

static void collect(TrieNode* node, const std::string& prefix,
                    std::vector<std::pair<std::string, int>>& result)
{
    if (node == nullptr) return;

    if (node->is_end)
    {
        result.push_back({prefix, node->freq});
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            char letter = static_cast<char>('a' + i);
            collect(node->children[i], prefix + letter, result);
        }
    }
}

static void traverse(const std::string& digits, size_t pos, TrieNode* node,
                     const std::string& prefix,
                     std::vector<std::pair<std::string, int>>& result)
{
    if (node == nullptr) return;

    if (pos >= digits.length())
    {
        collect(node, prefix, result);
        return;
    }

    char digit = digits[pos];
    if (digit < '2' || digit > '9') return;

    const char* letters = DIGIT_TO_LETTERS[digit - '0'];
    if (letters == nullptr) return;

    for (int i = 0; letters[i] != '\0'; i++)
    {
        int idx = letters[i] - 'a';
        if (idx >= 0 && idx < ALPHABET_SIZE && node->children[idx] != nullptr)
        {
            traverse(digits, pos + 1, node->children[idx], prefix + letters[i], result);
        }
    }
}

static void sort_result(std::vector<std::pair<std::string, int>>& result)
{
    size_t n = result.size();
    for (size_t i = 0; i < n; i++)
    {
        size_t max_idx = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (result[j].second > result[max_idx].second)
            {
                max_idx = j;
            }
        }
        if (max_idx != i)
        {
            std::swap(result[i], result[max_idx]);
        }
    }
}

std::vector<std::pair<std::string, int>> trie_find(Trie& trie, const std::string& digits)
{
    std::vector<std::pair<std::string, int>> result;

    if (trie.root == nullptr) return result;
    if (digits.empty()) return result;

    for (size_t i = 0; i < digits.length(); i++)
    {
        if (digits[i] < '2' || digits[i] > '9') return result;
    }

    traverse(digits, 0, trie.root, "", result);
    sort_result(result);
    return result;
}
