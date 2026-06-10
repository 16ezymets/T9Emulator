/**
 * @file engine.cpp
 * @brief Реализация движка эмулятора T9
 */

#include "t9engine.h"
#include <stdexcept>

Engine engine_create(Trie* trie)
{
    Engine eng;
    eng.trie = trie;
    eng.selected = 0;
    return eng;
}

void engine_add_digit(Engine& eng, char digit)
{
    if (digit >= '2' && digit <= '9')
    {
        eng.digits += digit;
        eng.cands = trie_find(*eng.trie, eng.digits);
        eng.selected = 0;
    }
}

void engine_backspace(Engine& eng)
{
    if (!eng.digits.empty())
    {
        eng.digits.pop_back();
        eng.cands = trie_find(*eng.trie, eng.digits);
        eng.selected = 0;
    }
}

void engine_prev(Engine& eng)
{
    if (!eng.cands.empty() && eng.selected > 0)
    {
        eng.selected--;
    }
}

void engine_next(Engine& eng)
{
    if (!eng.cands.empty() && eng.selected < static_cast<int>(eng.cands.size()) - 1)
    {
        eng.selected++;
    }
}

void engine_commit(Engine& eng)
{
    if (eng.cands.empty() || eng.selected >= static_cast<int>(eng.cands.size()))
    {
        throw std::runtime_error("Нет кандидатов для выбора");
    }

    if (!eng.text.empty()) eng.text += " ";
    eng.text += eng.cands[eng.selected].first;

    eng.digits.clear();
    eng.cands.clear();
    eng.selected = 0;
}

void engine_reset(Engine& eng)
{
    eng.digits.clear();
    eng.cands.clear();
    eng.selected = 0;
}