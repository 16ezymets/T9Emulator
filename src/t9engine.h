/**
 * @file engine.h
 * @brief Движок эмулятора T9
 */

#ifndef T9ENGINE_H
#define T9ENGINE_H

#include "trie.h"
#include <string>
#include <vector>

/**
 * @brief Состояние эмулятора T9
 * 
 * Хранит дерево словаря, текущий ввод, список кандидатов и итоговый текст.
 */
struct Engine
{
    Trie* trie;                                        
    std::string digits;                                
    std::vector<std::pair<std::string, int>> cands;    
    int selected;                                      
    std::string text;                                  
};

/**
 * @brief Создать движок
 * @param trie Указатель на дерево
 * @return Инициализированный движок
 */
Engine engine_create(Trie *trie);

/// Добавить цифру
void engine_add_digit(Engine &eng, char digit);

/// Удалить последнюю цифру
void engine_backspace(Engine &eng);

/// Выбрать предыдущего кандидата
void engine_prev(Engine &eng);

/// Выбрать следующего кандидата
void engine_next(Engine &eng);

/// Закрепить выбранное слово
void engine_commit(Engine &eng);

/// Сбросить текущий ввод
void engine_reset(Engine &eng);

#endif