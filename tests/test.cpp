#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "t9engine.h"
#include "trie.h"

TEST_CASE("Добавление и поиск слова") {
  Trie trie = trie_create();

  trie_insert(trie, "hello", 100);
  std::vector<std::pair<std::string, int>> result = trie_find(trie, "43556");

  CHECK(result.size() == 1);
  CHECK(result[0].first == "hello");
}

TEST_CASE("Сортировка по частоте") {
  Trie trie = trie_create();

  trie_insert(trie, "home", 200);
  trie_insert(trie, "good", 150);
  trie_insert(trie, "gone", 100);

  std::vector<std::pair<std::string, int>> result = trie_find(trie, "4663");

  REQUIRE(result.size() >= 1);
  CHECK(result[0].first == "home");
}

TEST_CASE("Engine: ввод и выбор слова") {
  Trie trie = trie_create();
  trie_insert(trie, "hello", 100);
  Engine eng = engine_create(&trie);

  engine_add_digit(eng, '4');
  engine_add_digit(eng, '3');
  CHECK(eng.digits == "43");

  engine_backspace(eng);
  CHECK(eng.digits == "4");

  engine_reset(eng);
  CHECK(eng.cands.empty());

  CHECK_THROWS_AS(engine_commit(eng), std::runtime_error);
}