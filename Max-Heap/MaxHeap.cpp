#include "MaxHeap.hpp"
#include <exception>
#include <climits>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(std::size_t size) : arr(size) {}

MaxHeap::MaxHeap(std::initializer_list<int> list) {
    for (const auto& i : list) {
        arr.push_back(i);
    }
    build();
}

void MaxHeap::maxHeapify(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int size = arr.size();
    int largeI = i;
    if (left < size && arr[i] < arr[left]) {
        largeI = left;
    }  
    if (right < size && arr[largeI] < arr[right]) {
        largeI = right;
    }
    if (largeI != i) {
        std::swap(arr[i], arr[largeI]);
        maxHeapify(largeI);
    }
}

void MaxHeap::build() {
    for (int i = arr.size() / 2 - 1; i >= 0; --i) {
        maxHeapify(i);
    }
}

int MaxHeap::getMax() const {
    if (arr.size() != 0) {
        return arr[0];
    }
    throw std::logic_error("There are no elements in heap");
}

int MaxHeap::extractMax() {
    int max = arr[0];
    int size = arr.size();
    arr[0] = arr[size - 1];
    arr.pop_back();
    maxHeapify(0);
    return max;
}

void MaxHeap::insert(int val) {
    arr.push_back(INT_MIN);
    int size = arr.size();
    increaseKey(size - 1, val);
}

void MaxHeap::increaseKey(int index, int key) {
    if (index < 0 || index >= arr.size() || arr[index] > key) {
        throw std::logic_error("New key is smaller than current key\n");
    }
    arr[index] = key;
    while (index > 0 && arr[(index - 1) / 2] < arr[index]) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void MaxHeap::print() const {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}