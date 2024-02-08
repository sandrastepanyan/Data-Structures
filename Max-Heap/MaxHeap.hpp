#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <initializer_list>

class MaxHeap {
public:
    MaxHeap();
    MaxHeap(std::size_t size);
    MaxHeap(std::initializer_list<int> list);

    void insert(int val);
    int extractMax();
    int getMax() const;
    void increaseKey(int index, int key);
    
    void print() const;

private:
    void maxHeapify(int i);
    void build();

private:
    std::vector<int> arr;
};

#endif