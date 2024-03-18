#include <memory>
#include <string>

class RBTNode {
  friend class RBTree;

  private:
    int value_;
    bool black_;
    std::shared_ptr<RBTNode> left_;
    std::shared_ptr<RBTNode> right_;
    std::shared_ptr<RBTNode> parent_;

  public:
    RBTNode(const int &value, std::shared_ptr<RBTNode> parent, const bool black = false);
    RBTNode(RBTNode &node) = delete;
    RBTNode &operator=(RBTNode &node) = delete;

    const int get_black_depth() const;
    const bool is_valid() const;
    const bool is_black() const;
    const bool is_red() const;

    void set_black();
    void set_red();

    std::shared_ptr<RBTNode> parent();
    std::shared_ptr<RBTNode> grand_parent();
    std::shared_ptr<RBTNode> uncle();

    const bool is_left_child();
    const bool is_right_child();
    const std::string print();
};

class RBTree {
  private:
    std::shared_ptr<RBTNode> root_;
    std::shared_ptr<RBTNode> insert(std::shared_ptr<RBTNode> &parent, const int &value);
    void rotate_left(std::shared_ptr<RBTNode> &node);
    void rotate_right(std::shared_ptr<RBTNode> &node);
    void rebalance(std::shared_ptr<RBTNode> inserted);
    void rebalance_red_parent(std::shared_ptr<RBTNode> inserted);
    void rebalance_red_uncle(std::shared_ptr<RBTNode> inserted);
    void rebalance_black_uncle(std::shared_ptr<RBTNode> inserted);

    void set_left(std::shared_ptr<RBTNode> &parent, std::shared_ptr<RBTNode> &node);
    void set_right(std::shared_ptr<RBTNode> &parent, std::shared_ptr<RBTNode> &node);
    void replace_node(std::shared_ptr<RBTNode> &old, std::shared_ptr<RBTNode> &new_n);

  public:
    RBTree();
    RBTree(std::initializer_list<int> &list);
    RBTree(RBTree &node) = delete;
    RBTree &operator=(RBTree &tree) = delete;

    bool find(const int &value);
    void insert(const int &value);
    const int get_black_depth();
    const bool is_valid();
};