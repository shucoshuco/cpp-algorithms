#include "rbtree.hpp"
#include <memory>
#include <string>

using namespace std;

RBTNode::RBTNode(const int &value, shared_ptr<RBTNode> parent, const bool black) :
    BinaryTreeNode(value),
    black_{black},
    left_{nullptr},
    right_{nullptr},
    parent_{parent}
{ }

const std::shared_ptr<BinaryTreeNode> RBTNode::get_left() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(left_);
}

const std::shared_ptr<BinaryTreeNode> RBTNode::get_right() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(right_);
}

const bool RBTNode::is_black() const {
    return black_;
}
const bool RBTNode::is_red() const {
    return !black_;
}

void RBTNode::set_black() {
    black_ = true;
}

void RBTNode::set_red() {
    black_ = false;
}

const int RBTNode::get_black_depth() const {
    int left_black_depth = left_ ? left_->get_black_depth() : 0;
    int right_black_depth = right_ ? right_->get_black_depth() : 0;
    return (black_ ? 1 : 0) + max(left_black_depth, right_black_depth);
}

const bool RBTNode::is_valid() const {
    int left_black_depth = 0;
    int right_black_depth = 0;
    if (left_) {
        if ((is_red() && left_->is_red()) || !left_->is_valid()) {
            return false;
        }
        left_black_depth = left_->get_black_depth();
    }
    if (right_) {
        if ((is_red() && right_->is_red()) || !right_->is_valid()) {
            return false;
        }
        right_black_depth = right_->get_black_depth();
    }
    return left_black_depth == right_black_depth;
}

shared_ptr<RBTNode> RBTNode::parent() {
    return parent_;
}

shared_ptr<RBTNode> RBTNode::grand_parent() {
    return parent_ ? parent_->parent_ : parent_;
}

shared_ptr<RBTNode> RBTNode::uncle() {
    auto gp = grand_parent();
    if (gp) {
        return parent_->is_left_child()
            ? gp->right_
            : gp->left_;
    }
    return grand_parent();
}

const bool RBTNode::is_left_child() {
    return parent_ && parent_->left_.get() == this;
}
const bool RBTNode::is_right_child() {
    return parent_ && parent_->right_.get() == this;
}

const std::string RBTNode::print() {
    return to_string(value_)
        + (black_ ? "b" :"r")
        + "(p" + (parent_ ? to_string(parent_->value_) : "x") + ")"
        + "["
        + (left_ ? left_->print() : "x")
        + ":"
        + (right_ ? right_->print() : "x")
        + "]";
}

RBTree::RBTree() : root_{nullptr}
{}

RBTree::RBTree(std::initializer_list<int> &list) : root_{nullptr} {
    if (list.begin() == list.end()) {
        throw new invalid_argument(
            "Can't create a empty AVL tree");
    }
    this->insert_all(list);
}

const std::shared_ptr<BinaryTreeNode> RBTree::get_root() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(root_);
}

std::shared_ptr<RBTNode> RBTree::insert(std::shared_ptr<RBTNode> &parent, const int &value) {
    if (value < parent->value_) {
        if (parent->left_) {
            return insert(parent->left_, value);
        }
        parent->left_ = make_shared<RBTNode>(value, parent);
        return parent->left_;
    }
    if (value > parent->value_) {
        if (parent->right_) {
            return insert(parent->right_, value);
        }
        parent->right_ = make_shared<RBTNode>(value, parent);
        return parent->right_;
    }
    return parent;
}


void RBTree::insert(const int &value) {
    if (root_) {
        auto inserted = insert(root_, value);
        if (inserted->parent_) {
            rebalance(inserted);
        } else {
            inserted->parent_ = root_;
        }
    } else {
        root_ = make_shared<RBTNode>(value, nullptr, true);
    }
}

const int RBTree::get_black_depth() {
    return root_
        ? root_->get_black_depth()
        : 0;
}

const bool RBTree::is_valid() {
    return root_
        ? root_->is_valid()
        : true;
}

void RBTree::set_left(std::shared_ptr<RBTNode> &parent, std::shared_ptr<RBTNode> &child) {
    if (parent) {
        parent->left_ = child;
        if (child) {
            child->parent_ = parent;
        }
    }
}

void RBTree::set_right(std::shared_ptr<RBTNode> &parent, std::shared_ptr<RBTNode> &child) {
    if (parent) {
        parent->right_ = child;
        if (child) {
            child->parent_ = parent;
        }
    }
}

void RBTree::replace_node(std::shared_ptr<RBTNode> &old, std::shared_ptr<RBTNode> &new_n) {
    if (old == root_) {
        root_ = new_n;
        new_n->parent_ = nullptr;
    } else {
        if (old->is_left_child()) {
            set_left(old->parent_, new_n);
        } else {
            set_right(old->parent_, new_n);
        }
    }
}

void RBTree::rotate_right(shared_ptr<RBTNode> &node) {
    auto new_root = node->left_;
    replace_node(node, new_root);
    set_left(node, new_root->right_);
    set_right(new_root, node);
}

void RBTree::rotate_left(shared_ptr<RBTNode> &node) {
    auto new_root = node->right_;
    replace_node(node, new_root);
    set_right(node, new_root->left_);
    set_left(new_root, node);
}

void RBTree::rebalance(std::shared_ptr<RBTNode> inserted) {
    if (!inserted->parent_) {
        inserted->set_black();
    } else if (inserted->parent_->is_red()) {
        rebalance_red_parent(inserted);
    }
}

void RBTree::rebalance_red_parent(std::shared_ptr<RBTNode> inserted) {
    auto uncle = inserted->uncle();
    if (uncle && uncle->is_red()) {
        rebalance_red_uncle(inserted);
    } else {
        rebalance_black_uncle(inserted);
    }
}

void RBTree::rebalance_red_uncle(std::shared_ptr<RBTNode> inserted) {
    inserted->parent()->set_black();
    auto uncle = inserted->uncle();
    uncle->set_black();
    auto grand_parent = inserted->grand_parent();
    grand_parent->set_red();
    rebalance(grand_parent);
}

void RBTree::rebalance_black_uncle(std::shared_ptr<RBTNode> inserted) {
    auto target = inserted;
    auto parent = target->parent();
    if (target->is_right_child() && parent->is_left_child()) {
        rotate_left(parent);
        target = parent;
    } else if (target->is_left_child() && parent->is_right_child()) {
        rotate_right(parent);
        target = parent;
    }

    target = target->parent();
    parent = target->parent();
    target->set_black();
    parent->set_red();
    if (target->is_left_child()) {
        rotate_right(parent);
    } else {
        rotate_left(parent);
    }

}