#include <exception>

template <typename T>
Node<T>::Node(const T& val) : data{val} {}

template <typename T>
List<T>::List() : head{} {}

template <typename T>
List<T>::List(std::size_t size, const T& val) {
    if (size < 1) {
        return;
    }
    Node<T>* node = new Node(val);
    head = node;
    Node<T>* curr = head;
    for (int i = 1; i < size; ++i) {
        Node<T>* node = new Node(val);
        curr->next = node;
        curr = curr->next;
    }
}

template <typename T>
List<T>::~List() {
    if (head == nullptr) {
        return;
    }
    Node<T>* curr = head;
    while (curr->next != nullptr) {
        Node<T>* next_node = curr->next;
        delete curr;
        curr = next_node;
    }
    delete curr;
}

// operator=

template <typename T>
void List<T>::push_back(const T& val) {
    if (head == nullptr) {
        Node<T>* new_node = new Node(val);
        head = new_node;
        return;
    }
    Node<T>* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    } 
    Node<T>* new_node = new Node(val);
    curr->next = new_node;
}

template <typename T>
void List<T>::push_front(const T& val) {
    Node<T>* new_node = new Node(val);
    new_node->next = head;
    head = new_node;
}

template <typename T>
void List<T>::pop_back() {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node<T>* curr = head;
    while (curr->next->next) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}


template <typename T>
void List<T>::pop_front() {
    if (head == nullptr) {
        return;
    }
    Node<T>* curr = head;
    head = head->next;
    delete curr;
}

template <typename T>
bool List<T>::empty() const {
    return head == nullptr;
}

template <typename T>
std::size_t List<T>::size() const {
    std::size_t size = 0;
    if (head != nullptr) {
        Node<T>* curr = head;
        while (curr->next != nullptr) {
            ++size;
            curr = curr->next;
        }
        ++size;
    }
    return size;
}

template <typename T>
void List<T>::insert(std::size_t pos, const T& val) {
    if (pos > size()) {
        throw std::out_of_range("Out of range!");
    }
    if (pos == 0) {
        push_front(val);
        return;
    }
    else if (pos == size()) {
        push_back(val);
        return;
    }
    Node<T>* curr = head;
    for (int i = 1; i < pos; ++i) {
        curr = curr->next; // points at pos - 1 node
    }
    Node<T>* new_node = new Node(val);
    new_node->next = curr->next;
    curr->next = new_node; 
}

template <typename T>
void List<T>::insert(std::size_t pos, List<T>& list) {
    Node<T>* curr = head;
    for (int i = 1; i < pos; ++i) {
        curr = curr->next;
    }
    Node<T>* tmp = curr->next;
    curr->next = list.head;
    Node<T>* curr2 = list.head;
    while (curr2->next) {
        curr2 = curr2->next;
    }
    curr2->next = tmp;
    list.head = nullptr;
}

template <typename T>
void List<T>::deleter(std::size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("Out of range!");
    }
    if (pos == 0) {
        pop_front();
        return;
    }
    else if (pos == size() - 1) {
        pop_back();
        return;
    }
    Node<T>* curr = head;
    for (int i = 1; i < pos; ++i) {
        curr = curr->next; // points at pos - 1 node
    }
    Node<T>* tmp = curr->next->next;
    delete curr->next;
    curr->next = tmp;
}

template <typename T>
std::size_t List<T>::find(const T& val) const {
    if (head != nullptr) {
        std::size_t pos = 0;
        Node<T>* curr = head;
        while (curr) {
            if (curr->data == val) {
                return pos;
            }
            curr = curr->next;
            ++pos;
        }

    }
    throw std::logic_error("There is no such element");
}

template <typename T>
Node<T>* List<T>::reverseIter() {
    Node<T>* prev = nullptr;
    Node<T>* curr = head;
    Node<T>* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return prev;
}

template <typename T>
Node<T>* List<T>::reverseRec(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node<T>* tmp = reverseRec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return tmp;
}

template <typename T>
Node<T>* List<T>::reverse() {
    head = reverseRec(head);
    return head;
}

template <typename T>
Node<T>* List<T>::getMiddle() const {
    Node<T>* slow = head;
    Node<T>* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

template <typename T>
void List<T>::print() const {
    if (head == nullptr) {
        return;
    }
    Node<T>* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}


