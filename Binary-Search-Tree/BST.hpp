#ifndef BST_H
#define BST_H
#include <vector>
#include "Node.hpp"

template <typename T>
class BST {
public:
    BST();
    BST(std::vector<T>& vec);
    ~BST();

    void insert(const T& val);
    void erase(const T& val);
    bool search(const T& val) const;
    std::size_t size() const;
    int getHeight() const;
    Node<T>* getMinNode() const;
    Node<T>* getMaxNode() const;
    Node<T>* getSuccesor(Node<T>* node) const;
    Node<T>* getPredecessor(Node<T>* node) const;
    void inOrderTraverse() const;
    void levelOrderTraverse() const;

private:
    void inOrderTraverse(Node<T>* node) const;
    void levelOrderTraverse(Node<T>* node) const;
    Node<T>* erase(Node<T>* node, const T& val);
    bool search(Node<T>* node, const T& val) const;
    int getHeight(Node<T>* node) const;
    Node<T>* makeBST(const std::vector<T>& vec, int start, int end);
    Node<T>* getMinNode(Node<T>* node) const;
    Node<T>* getMaxNode(Node<T>* node) const;

private:
    Node<T>* root;
    std::size_t m_size;
};

#include "BST.tpp"

#endif // BST_H
