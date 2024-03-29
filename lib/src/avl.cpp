#include "avl.hpp"
#include "utils.h"
#include <exception>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <set>
#include <queue>
#include <iostream>
#include <memory>

using namespace std;


AVLTNode::AVLTNode(const int &value) :
    BinaryTreeNode(value),
    left_{nullptr},
    right_{nullptr},
    left_depth_{0},
    right_depth_{0}
{}

const std::shared_ptr<BinaryTreeNode> AVLTNode::get_left() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(left_);
}

const std::shared_ptr<BinaryTreeNode> AVLTNode::get_right() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(right_);
}

const int AVLTNode::get_depth() const {
    return max(left_depth_, right_depth_) + 1;
}

const int AVLTNode::get_balance() const {
    return right_depth_ - left_depth_;
}

const int AVLTNode::recalculate_depth() {
    left_depth_ = left_.get() == nullptr ? 0 : left_->recalculate_depth();
    right_depth_ = right_.get() == nullptr ? 0 : right_->recalculate_depth();
    return get_depth();
};

const string AVLTNode::print() const {
    string left = "left: " + to_string(left_ ? left_->value_ : 0);
    string right = "right: " + to_string(right_ ? right_->value_ : 0);
    return to_string(value_) + " (" + left + " / " + right + ")";
}

AVLTree::AVLTree() : root_{nullptr}
{}

AVLTree::AVLTree(initializer_list<int> &list) : root_{nullptr} {
    if (list.begin() == list.end()) {
        throw new invalid_argument(
            "Can't create a empty AVL tree");
    }
    this->insert_all(list);
}

const std::shared_ptr<BinaryTreeNode> AVLTree::get_root() const {
    return static_cast<std::shared_ptr<BinaryTreeNode>>(root_);
}

void AVLTree::insert(const int &value) {
    if (root_ == nullptr) {
        root_ = make_shared<AVLTNode>(value);
    } else {
        this->insert(value, root_);
    }
    root_->recalculate_depth();
}

int AVLTree::insert(const int &value, std::shared_ptr<AVLTNode> &node) {
    if (node.get() == nullptr) {
        node = make_shared<AVLTNode>(value);
    } else if (value == node->value_) {
        cout << "Duplicated value " << value << endl;
    } else if (value < node->value_) {
        node->left_depth_ = insert(value, node->left_);
        balance(node);
    } else {
        node->right_depth_ = insert(value, node->right_);
        balance(node);
    }
    return node->get_depth(); 
}

void AVLTree::balance(std::shared_ptr<AVLTNode> &node) {
    int balance = node->get_balance();
    if (balance < -1) {
        if (node->left_->get_balance() > 1) {
            rotate_left(node->left_);
        }
        rotate_right(node);
    } else if (balance > 1) {
        if (node->right_->get_balance() < -1) {
            rotate_right(node->right_);
        }
        rotate_left(node);
    }
};

void AVLTree::rotate_right(std::shared_ptr<AVLTNode> &node) {
    std::shared_ptr<AVLTNode> root = std::move(node);
    node = std::move(root->left_);
    root->left_ = std::move(node->right_);
    node->right_ = std::move(root);
};

void AVLTree::rotate_left(std::shared_ptr<AVLTNode> &node) {
    std::shared_ptr<AVLTNode> root = std::move(node);
    node = std::move(root->right_);
    root->right_ = std::move(node->left_);
    node->left_ = std::move(root);
}
