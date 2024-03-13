#include "btree.hpp"
#include <vector>
#include <memory>

using namespace std;

BTNode::BTNode(const int &value)
    : value_{value}, left_{nullptr}
{}

BTNode::BTNode(const int &value, unique_ptr<BTPage> &left)
    : value_{value}, left_{move(left)}
{}

BTNode::BTNode(BTNode &&node) noexcept
    : value_{node.value_}, left_{move(node.left_)}
{}

BTNode &BTNode::operator=(BTNode &&node) noexcept {
    value_ = node.value_;
    left_ = move(node.left_);
    return *this;
}

BTPage::BTPage(const int &limit, unique_ptr<BTPage> &&child)
    : limit_{limit}, leaf_{child.get() == nullptr}
{
    add_centinel(child);
}

int BTPage::find_position(const int &value) {
    int i = 0;
    for (auto it = elements_.begin(); it != elements_.end() && it->value_ < value; it++, i++);
    return i;
}

void BTPage::add_centinel(std::unique_ptr<BTPage> &child) {
    elements_.push_back(BTNode(INT32_MAX, child));
}

unique_ptr<BTNode> BTPage::insert(BTNode &&node) {
    int position = find_position(node.value_);
    elements_.insert(elements_.begin() + position, BTNode(node.value_, node.left_));
    return elements_.size() > limit_ + 1
        ? split()
        : nullptr;
}

unique_ptr<BTNode> BTPage::split() {
    int toRemove = (elements_.size() - 1) / 2;
    auto newPage = make_unique<BTPage>(limit_, unique_ptr<BTPage>());
    for (int i = 0; i < toRemove; i++) {
        newPage->insert(move(elements_[0]));
        elements_.erase(elements_.begin());
    }
    int midPointValue = elements_[0].value_;
    newPage->elements_.back().left_ = move(elements_[0].left_);
    elements_.erase(elements_.begin());
    return make_unique<BTNode>(midPointValue, newPage);
}

unique_ptr<BTNode> BTPage::insert(const int &value) {
    if (leaf_) {
        return insert(BTNode(value));
    }
    auto node = elements_[find_position(value)].left_->insert(value);
    return node ? insert(move(*node.get())) : nullptr;
};

bool BTPage::contains(const int &value) {
    int position = find_position(value);
    if (elements_[position].value_ == value) {
        return true;
    }
    return elements_[position].left_ != nullptr
        && elements_[position].left_->contains(value);
}

int BTPage::count_pages() {
    int sum = 1;
    for (auto it = elements_.begin(); it != elements_.end(); it++) {
        if (it->left_) {
            sum += it->left_->count_pages();
        }
    }
    return sum;
}

BTree::BTree(const int &limit)
    : limit_{limit}, root_{make_unique<BTPage>(limit, unique_ptr<BTPage>())}
{}

void BTree::insert(const int &value) {
    auto root_node = root_->insert(value);
    if (root_node) {
        auto new_root = make_unique<BTPage>(limit_, move(root_));
        new_root->insert(move(*root_node));
        root_ = move(new_root);
    }
}

bool BTree::contains(const int &value) {
    return root_->contains(value);
}

int BTree::count_pages() {
    return root_->count_pages();
}