// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <string>

class PMTree {
public:
    PMTree(const std::vector<char>& elements);
    ~PMTree();
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPermByNumber(int num) const;
    int totalPermutations() const;

private:
    struct Node {
        char symbol;
        std::vector<Node*> children;
        Node(char ch) : symbol(ch) {}
    };

    Node* root;
    int n;
    std::vector<int> factorials;

    void buildTree(Node* node, const std::vector<char>& elements);
    void collectPerms(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& perms) const;
    void clearTree(Node* node);
    void precomputeFactorials();
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
