#include <string>
#include <memory>
#include <vector>

class AVLTNode {
  friend class AVLTree;

  private:
    int value_;
    std::unique_ptr<AVLTNode> left_;
    std::unique_ptr<AVLTNode> right_;
    int left_depth_;
    int right_depth_;

    const int recalculate_depth();
  public:
    AVLTNode(const int &value);
    AVLTNode(AVLTNode &node) = delete;
    AVLTNode &operator=(AVLTNode &node) = delete;

    const int get_depth() const;
    const int get_balance() const;
    const std::string print() const;
};

class AVLTree {
  private:
    std::unique_ptr<AVLTNode> root_;
    int insert(const int &value, std::unique_ptr<AVLTNode> &node);
    void balance(std::unique_ptr<AVLTNode> &node);
    void rotate_left(std::unique_ptr<AVLTNode> &node);
    void rotate_right(std::unique_ptr<AVLTNode> &node);

  public:
    AVLTree();
    AVLTree(std::initializer_list<int> &list);
    AVLTree(AVLTree &node) = delete;
    AVLTree &operator=(AVLTree &tree) = delete;

    void insert(const int &value);
    const int get_depth();
    const std::string print();
};