#include "trie.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Create Trie", "[create_trie]") {

  SECTION("If created with multiple entries, only find exact ones") {
    Trie trie;
    const std::initializer_list list{
      "value1", "value2", "value3", "victory", "hello", "different entry", "val"};

    for (auto it = list.begin(); it != list.end(); it++) {
      trie.insert(*it);
    }
    for (auto it = list.begin(); it != list.end(); it++) {
      REQUIRE(trie.find(*it));
    }
    REQUIRE(!trie.find("value"));
    REQUIRE(!trie.find("value4"));
  }

  SECTION("If removed after creation, only find remainig ones") {
    Trie trie;
    int size = 7;
    const char *list[size] = {
      "value1", "value2", "value3", "victory", "hello", "different entry", "val"
    };

    for (int i = 0; i < size; i++) {
      trie.insert(list[i]);
      REQUIRE(trie.find(list[i]));
    }

    for (int i = 0; i < size; i++) {
      trie.remove(list[i]);
      REQUIRE(!trie.find(list[i]));
      for (int j = i + 1; j < size; j++) {
        REQUIRE(trie.find(list[j]));
      }
    }
  }
}