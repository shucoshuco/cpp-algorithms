#include "graph.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>

using namespace std;

TEST_CASE("Create graph", "[create_graph]") {

  SECTION("Raises an exception if size is less than 2") {
    REQUIRE_THROWS(DirectedGraph(-1));
    REQUIRE_THROWS(DirectedGraph(0));
    REQUIRE_THROWS(DirectedGraph(0));
  }

  SECTION("If we include a valid size the graph is created") {
    DirectedGraph graph(10);
    REQUIRE(graph[2][5] == 0);

    graph.link(2, 5, 8);
    REQUIRE(graph[2][5] == 8);
  }
}

TEST_CASE("Dijkstra", "[calculate_distances]") {

  SECTION("Raises an exception if try to calculate with wrong params") {
    DirectedGraph graph(10);
    graph.link(2, 5, 8);
    REQUIRE_THROWS(graph.route(-1, 5));
    REQUIRE_THROWS(graph.route(1, 15));
    REQUIRE_THROWS(graph.route(1, -5));
  }

  SECTION("Calculate valid distance between two points (unidirectional)") {
    DirectedGraph graph(10);
    graph.link(2, 5, 8);
    graph.link(5, 9, 7);

    auto route = graph.route(2, 9);
    auto distance = route->get_distance();
    auto steps = route->get_steps();
    REQUIRE(distance == 15);
    REQUIRE(steps == vector<int>({9,5,2}));

    route = graph.route(9, 2);
    auto distance_r = route->get_distance();
    auto steps_r = route->get_steps();
    vector<int> empty{2};
    REQUIRE(distance_r == INT32_MAX);
    REQUIRE(steps_r == empty);
  }
}

TEST_CASE("Dijkstra in undirected graph", "[calculate_distances_undirected]") {

  SECTION("Calculate valid distance between two points (bidirectional)") {
    UndirectedGraph graph(9);
    graph.link(0, 1, 4);
    graph.link(0, 7, 8);

    graph.link(1, 2, 8);
    graph.link(1, 7, 11);

    graph.link(2, 3, 7);
    graph.link(2, 5, 4);
    graph.link(2, 8, 2);

    graph.link(3, 4, 9);
    graph.link(3, 5, 14);

    graph.link(4, 5, 10);

    graph.link(5, 6, 2);

    graph.link(6, 7, 1);
    graph.link(6, 8, 6);

    graph.link(7, 8, 7);

    auto route = graph.route(0, 4);
    auto distance = route->get_distance();
    auto steps = route->get_steps();
    REQUIRE(distance == 21);
    REQUIRE(steps == vector<int>({4, 5, 6, 7, 0}));

    route = graph.route(4, 0);
    auto distance_r = route->get_distance();
    auto steps_r = route->get_steps();
    std::reverse(steps_r.begin(), steps_r.end());
    REQUIRE(distance == distance_r);
    REQUIRE(steps == steps_r);
  }
}