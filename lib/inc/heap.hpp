#include <memory>

class Heap {
  private:
    int *data_;
    int size_;
    int next_;
    bool up_;
    const bool has_priority(const int &target, const int &reference) const;
    int get_children(const int &position) const;
    int get_parent(const int &position) const;
    bool find(const int &position, const int &value) const;
    void duplicate_size();
    void pull_up(const int &position);
    void pull_down(const int &position);

  public:
    Heap(const int &init_size, const bool up = true);
    Heap(const int &init_size, std::initializer_list<int> &list, const bool up = true);
    ~Heap();
    Heap(Heap &heap) = delete;
    Heap &operator=(Heap &heap) = delete;

    const int &size();
    void insert(const int &value);
    const int pop();
};