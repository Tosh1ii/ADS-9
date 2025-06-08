// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <vector>
#include  "tree.h"


PMTree::PMTree(const std::vector<char>& elements) {
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    n = sorted.size();
    root = new Node('\0');
    precomputeFactorials();
    buildTree(root, sorted);
}

PMTree::~PMTree() {
    clearTree(root);
}

void PMTree::precomputeFactorials() {
    factorials.resize(n + 1);
    factorials[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }
}

void PMTree::buildTree(Node* node, const std::vector<char>& elements) {
    for (char ch : elements) {
        Node* child = new Node(ch);
        node->children.push_back(child);

        std::vector<char> remaining;
        for (char c : elements) {
            if (c != ch) {
                remaining.push_back(c);
            }
        }

        buildTree(child, remaining);
    }
}

void PMTree::clearTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        clearTree(child);
    }
    delete node;
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> perms;
    std::vector<char> current;
    for (Node* child : root->children) {
        collectPerms(child, current, perms);
    }
    return perms;
}

void PMTree::collectPerms(Node* node, std::vector<char>& current,
                          std::vector<std::vector<char>>& perms) const {
    current.push_back(node->symbol);
    if (node->children.empty()) {
        perms.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectPerms(child, current, perms);
        }
    }
    current.pop_back();
}

int PMTree::totalPermutations() const {
    return factorials[n];
}

std::vector<char> PMTree::getPermByNumber(int num) const {
    if (num < 1 || num > totalPermutations()) {
        return {};
    }

    std::vector<char> permutation;
    Node* current = root;
    int currentNum = num;
    int remainingSize = n;

    for (int i = 0; i < n; ++i) {
        int branchSize = factorials[remainingSize - 1];
        int childIndex = (currentNum - 1) / branchSize;
        Node* child = current->children[childIndex];
        permutation.push_back(child->symbol);
        currentNum = (currentNum - 1) % branchSize + 1;
        current = child;
        remainingSize--;
    }

    return permutation;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto allPerms = tree.getAllPerms();
    if (num < 1 || num > allPerms.size()) {
        return {};
    }
    return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPermByNumber(num);
}
