#include "binarytree.hpp"
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

BinaryTreeNode::BinaryTreeNode(const int &value) :
    value_{value}
{}

const int BinaryTreeNode::get_depth() const {
    return 1
        + (this->get_left() ? this->get_left()->get_depth() : 0)
        + (this->get_right() ? this->get_right()->get_depth() : 0);
}

const int BinaryTreeNode::get_balance() const {
    int left_depth = this->get_left() ? this->get_left()->get_depth() : 0;
    int right_depth = this->get_right() ? this->get_right()->get_depth() : 0;
    return right_depth - left_depth;
}

BinaryTree::BinaryTree()
{}

void BinaryTree::insert_all(initializer_list<int> &list) {
    for (auto it = list.begin(); it != list.end(); it++) {
        this->insert(*it);
    }
}

bool BinaryTree::find(const int &value) {
    if (!this->get_root()) {
        return false;
    }
    auto current = this->get_root().get();
    while (current) {
        if (current->value_ == value) {
            return true;
        }
        if (value < current->value_) {
            current = current->get_left().get();
        } else {
            current = current->get_right().get();
        }
    }
    return false;
}

const int BinaryTree::get_depth() {
    return this->get_root() ? this->get_root()->get_depth() : 0;
}