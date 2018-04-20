//
// Created by Toreno on 21.04.2018.
//

#include "ostov.h"

Ostov::Ostov(int size) {
    end_size = size;
    current_size = 0;
    inTree.resize(end_size, false);
}

bool Ostov::add(int vertex) {
    inTree[vertex] = true;
    current_size++;
    return current_size == end_size;
}

bool Ostov::in_tree(int vertex) const {
    return inTree[vertex];
}