#include <string>
#include <memory>
#include <vector>

class BTPage;
class BTree;

class BTNode {
  friend class BTPage;

  private:
    int value_;
    std::unique_ptr<BTPage> left_;

  public:
    BTNode(const int &value);
    BTNode(const int &value, std::unique_ptr<BTPage> &left);
    BTNode(BTNode &&node) noexcept;
    BTNode &operator=(BTNode &node) = delete;
    BTNode &operator=(BTNode &&node) noexcept;
};

class BTPage {
  friend class BTree;

  private:
    std::vector<BTNode> elements_;
    int limit_;
    bool leaf_;

    int find_position(const int &value);
    std::unique_ptr<BTNode> split();
    std::unique_ptr<BTNode> insert(BTNode &&node);
    void add_centinel(std::unique_ptr<BTPage> &child);

  public:
    BTPage(const int &limit, std::unique_ptr<BTPage> &&child);
    BTPage &operator=(BTPage &node) = delete;
    BTPage(BTPage &node) = delete;

    std::unique_ptr<BTNode> insert(const int &value);
    bool contains(const int &value);
    int count_pages();
};

class BTree {
  private:
    std::unique_ptr<BTPage> root_;
    int limit_;

  public:
    BTree(const int &limit);
    BTree(BTree &tree) = delete;
    BTree &operator=(BTree &tree) = delete;

    void insert(const int &value);
    bool contains(const int &value);
    int count_pages();
};