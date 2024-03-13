#include <string>
#include <memory>
#include <map>
#include <vector>

class TrieNode;

class TrieNodeChildren {
  private:
    std::map<char, std::unique_ptr<TrieNode>> children_;

  public:
    TrieNodeChildren();
    TrieNodeChildren(TrieNodeChildren &children) = delete;
    TrieNodeChildren &operator=(TrieNodeChildren &children);

    const int size() const;
    const std::vector<char> keys();
    const bool contains(const char &c) const;
    std::unique_ptr<TrieNode> &operator[](const char &c);
    const std::unique_ptr<TrieNode> &get(const char &c) const;
    void erase(const char &c);
};

class TrieNode {
  friend class Trie;

  private:
    std::string value_;
    bool final_;
    TrieNodeChildren children_;
    const int find_diff(const std::string &text) const;
    void split(int position);

  public:
    TrieNode(const std::string &value, const bool final);
    TrieNode(const std::string &value, TrieNodeChildren &children, const bool final);
    TrieNode(TrieNode &node) = delete;
    TrieNode &operator=(TrieNode &node) = delete;

    const int size() const;
    const bool find(const std::string &text) const;
    void insert(const std::string &text);
    bool remove(const std::string &text);
};

class Trie {
  private:
    TrieNodeChildren root_;

  public:
    Trie();
    Trie(Trie &node) = delete;
    Trie &operator=(Trie &tree) = delete;

    const bool find(const std::string &text) const;
    void insert(const std::string &text);
    void remove(const std::string &text);
};