#include "heap.hpp"
#include "utils.h"
#include <exception>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <array>

using namespace std;

Heap::Heap(const int &init_size, const bool up)
    : data_(new int[init_size]), next_{0}, size_{init_size}, up_{up}
{ }

Heap::Heap(const int &init_size, std::initializer_list<int> &list, const bool up)
    : data_(new int[init_size]), next_{0}, size_{init_size}, up_{up}
{
    for (auto it = list.begin(); it != list.end(); it++) {
        insert(*it);
    }
}

Heap::~Heap() {
    delete data_;
}

const bool Heap::has_priority(const int &target, const int &reference) const {
    return up_
        ? target < reference
        : target > reference;
}

int Heap::get_children(const int &position) const {
    return position * 2 + 1;
}

int Heap::get_parent(const int &position) const {
    return (position + 1) / 2 - 1;
}

void Heap::duplicate_size() {
    int new_size = size_ * 2;
    int * new_root = copy_vector(data_, size_, new_size);
    delete data_;
    data_ = new_root;
    size_ = new_size;
}

const int &Heap::size() {
    return next_;
}

bool Heap::find(const int &position, const int &value) const {
    if (position >= next_ || has_priority(data_[position], value)) {
        return false;
    }
    if (data_[position] == value) {
        return true;
    }
    int children_position = get_children(position);
    return find(children_position, value) || find(children_position + 1, value);
}

void Heap::insert(const int &value) {
    if (next_ >= size_) {
        duplicate_size();
    }
    data_[next_] = value;
    pull_up(next_);
    next_++;
}

void Heap::pull_up(const int &position) {
    if (position > 0) {
        int parent = get_parent(position);
        if (has_priority(data_[position], data_[parent])) {
            change(data_, position, parent);
            pull_up(parent);
        }
    }
}

void Heap::pull_down(const int &position) {
    int child = get_children(position);
    if (child < next_) {
        if (child + 1 < next_ && has_priority(data_[child + 1], data_[child])) {
            child = child + 1;
        }
        if (has_priority(data_[child], data_[position])) {
            change(data_, position, child);
            pull_down(child);
        }
    }
}

const int Heap::pop() {
    if (next_ == 0) {
        throw new invalid_argument(
            "Can't pop from an empty heap");
    }
    int value = data_[0];
    next_--;
    change(data_, 0, next_);
    data_[next_] = 0;
    pull_down(0);
    return value;
}