#include "utils.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Quicksort", "[quick_sort]") {

  SECTION("If sort empty array don't fail") {
    int a[0];
    c_quicksort(a, 0);
    REQUIRE(true);
  }

  SECTION("If sort array with single element then don't fail") {
    int a[1] = {5};
    c_quicksort(a, 1);
    REQUIRE(a[0] == 5);
  }

  SECTION("If sort random list then valid sort") {
    srand(time(NULL));
    int size = 2048;
    int a[size];
    for (int i = 0; i < size; i++) {
      a[i] = rand();
    }
    c_quicksort(a, size);
    for (int i = 1; i < size; i++) {
      REQUIRE(a[i - 1] <= a[i]);
    }
  }
}