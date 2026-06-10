/**
 * @file engine.h
 * @brief Движок эмулятора T9
 */

#ifndef T9ENGINE_H
#define T9ENGINE_H

#include <string>
#include <vector>
#include "trie.h"

struct Engine
{
    Trie* trie;                                        ///< Дерево словаря
    std::string digits;                                ///< Введённые цифры
    std::vector<std::pair<std::string, int>> cands;    ///< Кандидаты
    int selected;                                      ///< Индекс выбранного
    std::string text;                                  ///< Итоговый текст
};

/**
 * @brief Создать движок
 * @param trie Указатель на дерево
 * @return Инициализированный движок
 */
Engine engine_create(Trie* trie);

/// Добавить цифру
void engine_add_digit(Engine& eng, char digit);

/// Удалить последнюю цифру
void engine_backspace(Engine& eng);

/// Выбрать предыдущего кандидата
void engine_prev(Engine& eng);

/// Выбрать следующего кандидата
void engine_next(Engine& eng);

/// Закрепить выбранное слово
void engine_commit(Engine& eng);

/// Сбросить текущий ввод
void engine_reset(Engine& eng);

#endif