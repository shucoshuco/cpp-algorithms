#include "rbtree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Create Red/Black Tree", "[create_rb_tree]") {

  SECTION("If created with sorted list, depth of tree is minimum") {
    std::initializer_list list{1, 3, 2, 4, 5, 6, 7, 8};
    RBTree tree(list);
    REQUIRE(tree.is_valid());
  }

  SECTION("If created with balanced list, depth of tree is minimum") {
    std::initializer_list list{4, 2, 1, 3, 6, 5, 7};
    RBTree tree(list);
    REQUIRE(tree.is_valid());
  }

  SECTION("If created with random list, depth of tree is minimum") {
    srand(time(NULL));
    RBTree tree;
    for (int i = 0; i < 2048; i++) {
      int val = rand();
      tree.insert(val);
      REQUIRE(tree.find(val));
    }
    REQUIRE(tree.is_valid());
  }
}