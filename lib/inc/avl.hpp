#include "binarytree.hpp"
#include <string>
#include <memory>
#include <vector>

class AVLTNode : public BinaryTreeNode {
  friend class AVLTree;

  private:
    std::shared_ptr<AVLTNode> left_;
    std::shared_ptr<AVLTNode> right_;
    int left_depth_;
    int right_depth_;

    const int recalculate_depth();
  public:
    AVLTNode(const int &value);
    AVLTNode(AVLTNode &node) = delete;
    AVLTNode &operator=(AVLTNode &node) = delete;

    const std::shared_ptr<BinaryTreeNode> get_left() const;
    const std::shared_ptr<BinaryTreeNode> get_right() const;
    const int get_depth() const;
    const int get_balance() const;
    const std::string print() const;
};

class AVLTree : public BinaryTree {
  private:
    std::shared_ptr<AVLTNode> root_;
    const std::shared_ptr<BinaryTreeNode> get_root() const;
    int insert(const int &value, std::shared_ptr<AVLTNode> &node);
    void balance(std::shared_ptr<AVLTNode> &node);
    void rotate_left(std::shared_ptr<AVLTNode> &node);
    void rotate_right(std::shared_ptr<AVLTNode> &node);

  public:
    AVLTree();
    AVLTree(std::initializer_list<int> &list);
    AVLTree(AVLTree &node) = delete;
    AVLTree &operator=(AVLTree &tree) = delete;

    void insert(const int &value);
};