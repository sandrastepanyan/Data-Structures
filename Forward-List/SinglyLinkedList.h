#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST
#include <iostream>

template <typename T>
struct Node {
    T data{};
    Node* next{};
    Node() {}
    Node(const T& val);
};

template <typename T>
class List {
public:
    List();
    List(std::size_t size, const T& val = T());
    ~List();

    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    bool empty() const;
    std::size_t size() const;
    void insert(std::size_t pos, const T& val);
    void insert(std::size_t pos, List& list);
    void deleter(std::size_t pos);
    std::size_t find(const T& val) const;

    Node<T>* reverseIter();
    Node<T>* reverse();
    Node<T>* getMiddle() const;

    void print()const;

private:
    Node<T>* reverseRec(Node<T>* head);

private:
    Node<T>* head;
};

#include "SinglyLinkedList.tpp"
#endif // SINGLY_LINKED_LIST
