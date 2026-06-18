/**
 * @file main.cpp
 * @brief Консольный эмулятор T9
 */

#include "dictionary.h"
#include "t9engine.h"
#include "trie.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>

int get_key() {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  int ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

static void print_header() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "  ЭМУЛЯТОР T9" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "  2-9 - цифры, Backspace - удалить" << std::endl;
  std::cout << "  <-/-> - листать, Tab - выбрать" << std::endl;
  std::cout << "  Enter - сброс, Escape - выход" << std::endl;
  std::cout << "========================================\n" << std::endl;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  Trie trie = trie_create();

  try {
    dict_load_file(trie, "dictionary.txt");
  } catch (const std::exception &e) {
    dict_load_builtin(trie);
  }

  Engine eng = engine_create(&trie);

  system("clear");
  print_header();

  bool running = true;
  while (running) {
    std::cout << "Текст: " << eng.text << std::endl;
    std::cout << "Цифры: " << eng.digits << std::endl;

    if (!eng.digits.empty()) {
      std::cout << "Варианты (" << eng.cands.size() << "):" << std::endl;
      int max_show = static_cast<int>(eng.cands.size());
      if (max_show > 10)
        max_show = 10;

      for (int i = 0; i < max_show; i++) {
        std::cout << (i == eng.selected ? " > " : "   ");
        std::cout << eng.cands[i].first << " (" << eng.cands[i].second << ")"
                  << std::endl;
      }
    } else {
      std::cout << "Введите цифры 2-9" << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Клавиша: " << std::flush;

    int key = get_key();

    if (key == 27) {
      int next = get_key();
      if (next == 91) {
        int arrow = get_key();
        if (arrow == 68)
          engine_prev(eng);
        else if (arrow == 67)
          engine_next(eng);
      } else {
        running = false;
      }
    } else if (key >= '2' && key <= '9') {
      engine_add_digit(eng, static_cast<char>(key));
    } else if (key == 127 || key == 8) {
      engine_backspace(eng);
    } else if (key == 10) {
      engine_reset(eng);
    } else if (key == 9) {
      try {
        engine_commit(eng);
      } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
      }
    }

    system("clear");
    print_header();
  }

  std::cout << "\nИТОГОВЫЙ ТЕКСТ: " << eng.text << std::endl;

  return 0;
}
