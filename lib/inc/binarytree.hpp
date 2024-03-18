#include <string>
#include <memory>
#include <vector>

class BinaryTreeNode {
  friend class BinaryTree;

  protected:
    int value_;

  public:
    BinaryTreeNode(const int &value);
    virtual const int get_depth() const;
    virtual const int get_balance() const;
    virtual const std::shared_ptr<BinaryTreeNode> get_left() const = 0;
    virtual const std::shared_ptr<BinaryTreeNode> get_right() const = 0;
};

class BinaryTree {
  protected:
    void insert_all(std::initializer_list<int> &list);
    virtual const std::shared_ptr<BinaryTreeNode> get_root() const = 0;

  public:
    BinaryTree();
    BinaryTree(BinaryTree &node) = delete;
    BinaryTree &operator=(BinaryTree &tree) = delete;

    virtual void insert(const int &value) = 0;
    bool find(const int &value);
    const int get_depth();
    const int get_balance();
};