#include "BST.h"
#include <algorithm>
#include <queue>
#include <iostream>

template <typename T>
BST<T>::BST() : root{}, m_size{} {}

template <typename T>
BST<T>::BST(std::vector<T>& vec) 
    : m_size{vec.size()}
{
    std::sort(vec.begin(), vec.end());
    root = makeBST(vec, 0, m_size - 1);
}

template <typename T>
Node<T>* BST<T>::makeBST(const std::vector<T>& vec, int start, int end) {
    if (start > end) { return nullptr; }
    int mid = (start + end) / 2;
    Node<T>* node = new Node<T>(vec[mid]);
    node->left = makeBST(vec, start, mid - 1);
    node->right = makeBST(vec, mid + 1, end);
    return node;
}

template <typename T>
BST<T>::~BST() {
    if (!root) return;
    inOrderTraverse(root->left);
    delete root;
    inOrderTraverse(root->right);
}

template <typename T>
void BST<T>::insert(const T& val) {
    Node<T>* x = root;
    Node<T>* z = new Node<T>(val);
    Node<T>* y = nullptr;
    while (x) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (!y) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    ++m_size;
}

template <typename T>
bool BST<T>::search(const T& val) const {
    return search(root, val);
}

template <typename T>
bool BST<T>::search(Node<T>* node, const T& val) const {
    if (!node) { return false; }
    if (node.key == val) { return true; }
    if (node->key > val) {
        return search(node->left, val);
    }
    return search(node->right, val);
}

template <typename T>
std::size_t BST<T>::size() const {
    return m_size;
}

template <typename T>
int BST<T>::getHeight() const {
    return getHeight(root);
}

template <typename T>
int BST<T>::getHeight(Node<T>* node) const {
    if (!node) { return -1; }
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T>
void BST<T>::inOrderTraverse() const {
    inOrderTraverse(root);
}

template <typename T>
void BST<T>::inOrderTraverse(Node<T>* node) const {
    if (!node) return;
    inOrderTraverse(node->left);
    std::cout << node->key << " ";
    inOrderTraverse(node->right);
}

template <typename T>
Node<T>* BST<T>::getMaxNode() const {
    getMaxNode(root);
}

template <typename T>
Node<T>* BST<T>::getMinNode() const {
    getMinNode(root);
}

template <typename T>
Node<T>* BST<T>::getMinNode(Node<T>* node) const {
    Node<T>* x = node;
    while (x->left) {
        x = x->left;
    }
    return x;
}

template <typename T>
Node<T>* BST<T>::getMaxNode(Node<T>* node) const {
    Node<T>* x = node;
    while (x->right) {
        x = x->right;
    }
    return x;
}


template <typename T>
void BST<T>::levelOrderTraverse() const {
    levelOrderTraverse(root);
}

template <typename T>
void BST<T>::levelOrderTraverse(Node<T>* node) const {
    if (!node) { return; }
    std::queue<Node<T>*> q;
    q.push(node);
    int size = 0;
    while (!q.empty()) {
        size = q.size();
        for (int i = 0; i < size; ++i) {
            Node<T>* tmp = q.front();
            if (tmp) {
                q.pop();
                std::cout << tmp->key << " ";
                if (tmp->left) {
                    q.push(tmp->left);
                }
                if (tmp->right) {
                    q.push(tmp->right);
                }

            }
        }
        std::cout << std::endl;
    }
}

template <typename T>
Node<T>* BST<T>::getSuccesor(Node<T>* node) const {
    if (!node) { return nullptr; }
    if (node->right) {
        return getMinNode(node->right);
    }
    Node<T>* successor = nullptr;
    Node<T>* ancestor = root;
    while (ancestor != node) {
        if (node->key < ancestor->key) {
            successor = ancestor;
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

template <typename T>
Node<T>* BST<T>::getPredecessor(Node<T>* node) const {
    if (!node) { return nullptr; }
    if (node->left) {
        return getMaxNode(node->left);
    }
    Node<T>* predecessor = nullptr;
    Node<T>* ancestor = root;
    while (ancestor != node) {
        if (node->key > ancestor->key) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else {
            ancestor = ancestor->left;
        }
    }
    return predecessor;
}   


template <typename T>
void BST<T>::erase(const T& val) {
    Node<T>* prev = nullptr;
    erase(root, val);
}

template <typename T>
Node<T>* BST<T>::erase(Node<T>* node, const T& val) {
    if (!node) { return nullptr; }
    --m_size;
    if (node->key < val) {
        node->right = erase(node->right, val);
    }
    else if (node->key > val) {
        node->left = erase(node->left, val);
    }
    else {
        if (!node->left) {
            Node<T>* tmp = node->right;
            delete node;
            return tmp;
        }
        else if (!node->right) {
            Node<T>* tmp = node->left;
            delete node;
            return tmp;
        } 
        else {
            Node<T>* tmp = node->right;
            while (tmp->left) {
                tmp = tmp->left;
            }
            node->key = tmp->key;
            node->right = erase(node->right, tmp->key);
        }
    }
    return node;
}