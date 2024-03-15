#include "heap.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE("Create Heap", "[create_heap]") {

  SECTION("Created with sorted list up sort") {
    std::initializer_list list{1, 2, 3, 4, 5, 6, 7};
    Heap heap(10, list, true);

    REQUIRE(heap.size() == list.size());

    for (auto it = list.begin(); it != list.end(); it++) {
      REQUIRE(heap.pop() == *it);
    }

    REQUIRE(heap.size() == 0);
  }

  SECTION("If created with random list, up sort, priority is valid") {
    srand(time(NULL));
    int size = 2048;
    Heap heap(size / 2, true);
    for (int i = 0; i < size; i++) {
      heap.insert(rand());
    }

    REQUIRE(heap.size() == size);

    int last = INT32_MIN;
    for (int i = 0; i < size; i++) {
      int next = heap.pop();
      REQUIRE(next >= last);
      last = next;
    }

    REQUIRE(heap.size() == 0);
  }

  SECTION("If created with random list, down sort, priority is valid") {
    srand(time(NULL));
    int size = 2048;
    Heap heap(size / 2, false);
    for (int i = 0; i < size; i++) {
      heap.insert(rand());
    }

    REQUIRE(heap.size() == size);

    int last = INT32_MAX;
    for (int i = 0; i < size; i++) {
      int next = heap.pop();
      REQUIRE(next <= last);
      last = next;
    }

    REQUIRE(heap.size() == 0);
  }
}