#include "trie.hpp"
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

TrieNodeChildren::TrieNodeChildren() : children_{}
{}

TrieNodeChildren &TrieNodeChildren::operator=(TrieNodeChildren &other) {
    if (this != &other) {
        for (auto it = other.children_.begin(); it != other.children_.end(); it++) {
            children_[it->first] = move(it->second);
        }
        other.children_.clear();
    }
    return *this;
}

const int TrieNodeChildren::size() const {
    return children_.size();
}

const bool TrieNodeChildren::contains(const char &c) const {
    return children_.find(c) != children_.end();
}

const vector<char> TrieNodeChildren::keys() {
    vector<char> v;
    for (auto it = children_.begin(); it != children_.end(); it++) {
        v.push_back(it->first);
    }
    return v;
}

void TrieNodeChildren::erase(const char &c) {
    children_.erase(c);
}

std::unique_ptr<TrieNode> &TrieNodeChildren::operator[](const char &c) {
    if (!contains(c)) {
        children_[c] = make_unique<TrieNode>("", false);
    }
    return children_[c];
}

const std::unique_ptr<TrieNode> &TrieNodeChildren::get(const char &c) const {
    return children_.find(c)->second;
}

TrieNode::TrieNode(const std::string &value, const bool final) :
    value_{value},
    final_{final}
{}

TrieNode::TrieNode(const std::string &value, TrieNodeChildren &children, const bool final) :
        value_{value},
        final_{final} {
    children_ = children;
}

const int TrieNode::size() const {
    return value_.size();
}

const int TrieNode::find_diff(const std::string &text) const {
    int size = std::min(value_.size(), text.size());
    for (int i = 0; i < size; i++) {
        if (value_[i] != text[i]) {
            return i;
        }
    }
    return size;
}

const bool TrieNode::find(const std::string &text) const {
    int diff = find_diff(text);
    if (diff == size()) {
        if (diff == text.size()) {
            return final_;
        }
        char next = text[diff];
        if (children_.contains(next)) {
            return children_.get(next)->find(text.substr(diff + 1));
        }
    }
    return false;
}

void TrieNode::insert(const std::string &text) {
    if (value_ == "" && children_.size() == 0) {
        value_ = text;
        final_ = true;
    } else {
        int diff = find_diff(text);
        if (diff < size()) {
            split(diff);
        }
        if (diff < text.size()) {
            children_[text[diff]]->insert(text.substr(diff + 1));
        } else {
            final_ = true;
        }
    }
}

bool TrieNode::remove(const std::string &text) {
    if (text == value_) {
        if (children_.size() == 0) {
            value_ = "";
            final_ = false;
        } else if (children_.size() == 1) {
            char key = children_.keys().front();
            auto child = move(children_[key]);
            value_ += key + child->value_;
            final_ = child->final_;
            children_ = child->children_;
        } else {
            final_ = false;
        }
    } else if (size() < text.size() && text.substr(0, size()) == value_) {
        char discr = text[size()];
        if (children_.contains(discr)) {
            if (children_[discr]->remove(text.substr(size() + 1))) {
                children_.erase(discr);
            }
        }
    }
    return !final_ && children_.size() == 0;
}

void TrieNode::split(int position) {
    children_[value_[position]] = make_unique<TrieNode>(value_.substr(position + 1), children_, final_);
    value_ = value_.substr(0, position);
    final_ = false;
};

Trie::Trie() {}

const bool Trie::find(const std::string &text) const {
    return root_.contains(text[0])
        ? root_.get(text[0])->find(text.substr(1))
        : false;
}

void Trie::insert(const std::string &text) {
    if (text.size() > 0) {
        root_[text[0]]->insert(text.substr(1));
    }
}

void Trie::remove(const std::string &text) {
    if (text.size() > 0 && root_.contains(text[0]) && root_[text[0]]->remove(text.substr(1))) {
        root_.erase(text[0]);
    }
}