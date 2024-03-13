#include "btree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Create B-Tree", "[create_b_tree]") {

  SECTION("If created with sorted list, depth of tree is minimum") {
    std::initializer_list list{1, 2, 3, 4, 5, 6};
    BTree tree(2);
    for (auto it = list.begin(); it != list.end(); it++) {
      tree.insert(*it);
    }
    REQUIRE(tree.count_pages() == 4);
  }

  SECTION("If created with balanced list, depth of tree is minimum") {
    std::initializer_list list{4, 2, 1, 3, 6, 5, 7};
    BTree tree(2);
    for (auto it = list.begin(); it != list.end(); it++) {
      tree.insert(*it);
    }
    REQUIRE(tree.count_pages() == 7);
  }

  SECTION("If created with random list, depth of tree is minimum") {
    srand(time(NULL));
    BTree tree(20);
    for (int i = 0; i < 2048; i++) {
      int value = rand();
      tree.insert(value);
      REQUIRE(tree.contains(value));

    }
    REQUIRE(100 < tree.count_pages());
    REQUIRE(tree.count_pages() < 205);
  }
}