#include "graph.hpp"
#include "utils.h"
#include <exception>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

DirectedGraph::DirectedGraph(const int size_) {
  if (size_ < 2) {
    throw new invalid_argument(
        "Can't create a graph with less than 2 nodes");
  }
  size = size_;
  matrix = new int*[size];
  for (int i = 0; i < size; i++) {
    matrix[i] = init_vector(size, 0);
  }
}

void DirectedGraph::validate(const int from, const int to) {
  if (from < 0 || from >= size) {
    throw new invalid_argument("Invalid from node " + from);
  }
  if (to < 0 || to >= size) {
    throw new invalid_argument("Invalid to node " + to);
  }
}

const void DirectedGraph::link(const int from, const int to, const int weight) {
  validate(from, to);
  if (weight <= 0) {
    throw new invalid_argument(
      "Invalid weight " + to_string(weight) + " in link");
  }
  matrix[from][to] = weight;
}

const string DirectedGraph::print() {
  string txt;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      txt += to_string(matrix[i][j]) + '\t';
    }
    txt += '\n';
  }
  return txt;
}

CRow DirectedGraph::operator[](const int row) {
    return CRow(matrix, row);
}

unique_ptr<Route> DirectedGraph::route(const int from, const int to) {
  validate(from, to);

  int *vector = init_vector(size, INT32_MAX);
  int *steps = init_vector(size, -1);
  set<int> visited;
  queue<int> pending;

  vector[from] = 0;
  pending.push(from);

  while (!pending.empty()) {
    int next = pending.front();
    pending.pop();
    for (int i = 0; i < size; i++) {
      if (i != next && operator[](next)[i] > 0 && visited.find(i) == visited.end()) {
        int next_value = vector[next] + operator[](next)[i];
        if (next_value < vector[i]) {
          vector[i] = next_value;
          steps[i] = next;
        }
        pending.push(i);
      }
    }
    visited.insert(next);
  }

  auto route = make_unique<Route>(vector, steps, from, to);
  delete vector;
  delete steps;

  return route;
}

UndirectedGraph::UndirectedGraph(int size) : DirectedGraph(size)
{}

const void UndirectedGraph::link(const int from, const int to, const int weight) {
  DirectedGraph::link(from, to, weight);
  DirectedGraph::link(to, from, weight);
}

CRow::CRow(int **matrix_, int row_) : 
    matrix(matrix_),
    row(row_)
{}

int& CRow::operator[](int col) {
    return matrix[row][col];
}

Route::Route(int *distances, int *paths, int from, int to) : 
    distance(distances[to]),
    steps({})
{
  int next = to;
  while (next >= 0) {
    steps.push_back(next);
    next = paths[next];
  }
}

const int &Route::get_distance() const{
  return distance;
}

vector<int> &Route::get_steps() {
  return steps;
}