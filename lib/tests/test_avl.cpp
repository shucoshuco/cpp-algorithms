#include "avl.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Create AVL Tree", "[create_avl_tree]") {

  SECTION("If created with sorted list, depth of tree is minimum") {
    std::initializer_list list{1, 2, 3, 4, 5, 6, 7};
    AVLTree tree(list);
    REQUIRE(tree.get_depth() == 3);
  }

  SECTION("If created with balanced list, depth of tree is minimum") {
    std::initializer_list list{4, 2, 1, 3, 6, 5, 7};
    AVLTree tree(list);
    REQUIRE(tree.get_depth() == 3);
  }

  SECTION("If created with random list, depth of tree is minimum") {
    srand(time(NULL));
    AVLTree tree;
    for (int i = 0; i < 2048; i++) {
      tree.insert(rand());
    }
    REQUIRE(tree.get_depth() <= 11 * 1.44);
  }
}