#include <string>
#include <memory>
#include <vector>

class CRow {
  friend class DirectedGraph;

  private:
    int **matrix;
    int row;
    CRow(int **matrix, int row_);
public:
    int& operator[](int col);
};

class Route {
  private:
    int distance;
    std::vector<int> steps;

  public:
    Route(int *distances, int *paths, int from, int to);
    const int &get_distance() const;
    std::vector<int> &get_steps();
};

class DirectedGraph {
private:
  int size;
  int **matrix;

  void validate(const int from, const int to);

public:
  DirectedGraph(const int size);

  const void link(const int from, const int to, const int weight);
  const std::string print();
  CRow operator[](const int row);
  std::unique_ptr<Route> route(const int from, const int to);
};

class UndirectedGraph : public DirectedGraph {
public:
  UndirectedGraph(const int size);
  const void link(const int from, const int to, const int weight);
};