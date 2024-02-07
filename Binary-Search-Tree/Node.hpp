#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    Node() : key{}, right{}, left{} {}
    Node(T val) : key{val}, right{}, left{} {}

public:
    T key;
    Node* right;
    Node* left;
};

#endif // NODE_H