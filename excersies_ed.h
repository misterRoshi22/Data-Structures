#pragma once

#include <iostream>
#include <cmath>
using namespace std;


template <class T>
class DLList;

template <class T>
class DLLNode {
public:
    DLLNode(const T& val, DLLNode* next, DLLNode* prev);

    T get_val() const { return val; }
    void set_val(const T& val) { this->val = val; }
    DLLNode* get_next() const { return next; }
    DLLNode* get_prev() const { return prev; }

private:
    T val;
    DLLNode* next;
    DLLNode* prev;

    friend class DLList<T>;
};

template <class T>
DLLNode<T>::DLLNode(const T& val, DLLNode* next, DLLNode* prev)
{
    this->val = val;
    this->next = next;
    this->prev = prev;
}

// A doubly-linked list class to store elements of a generic type T
template <class T>
class DLList {
public:
    DLList();
    DLList(const DLList& other);
    ~DLList();

    bool is_empty() const;

    DLLNode<T>* head_node() const;
    DLLNode<T>* tail_node() const;
    T head_val() const;
    T tail_val() const;

    void add_to_head(const T& val);
    void add_to_tail(const T& val);
    void append(const DLList& otherList);

    void remove_head();
    void remove_tail();
    bool remove(const T& val);
    void clear();

    bool contains(const T& val) const;
    DLList& operator=(const DLList& other);

    DLList prior_v(T v, int count) const;
    DLList rmv_ret_negative();
    void rearrange_neg_pos();
    void insert_before_after(T val, T insertVal, int count);
    void collapse_m_nodes(int m);


private:
    DLLNode<T>* head;
    DLLNode<T>* tail;

    size_t get_size();
    void delete_node(DLLNode<T>* node);
    void insert_between_two_node(DLLNode<T>* prev, DLLNode<T>* next, T val);
    void insert_after_node(DLLNode<T>* node, T val);
    void collapse(DLLNode<T>* node);
    void advance(DLLNode<T>* node, int steps);

};

template <class T>
inline void DLList<T>::advance(DLLNode<T>* node, int steps) {
    if (node == nullptr)
        throw string("NAH BRAH STOP THIS CRAP");
    while (steps--) {
        node = node->next;
        if (node == nullptr) return;
    }
}

template <class T>
inline void DLList<T>::collapse(DLLNode<T>* node) {
    if (node == nullptr) return;

    DLLNode<T>* prev = node->prev;
    T val = node->val;
    delete_node(node);

    prev->val += val;
}

template <class T>
inline void DLList<T>::insert_after_node(DLLNode<T>* node, T val) {
    if (node == tail) {
        add_to_tail(val);
    }
    else if (node == nullptr) {
        add_to_head(val);
    }
    else {
        DLLNode<T>* next = node->next;
        DLLNode<T>* new_node = new DLLNode<T>(val, next, node);
        next->prev = new_node;
        node->next = new_node;
    }

}

template <class T>
inline void DLList<T>::insert_between_two_node(DLLNode<T>* prev, DLLNode<T>* next, T val) {

    DLLNode<T>* new_node = new DLLNode(val, next, prev);
    if (next != nullptr) next->prev = new_node;
    if (prev != nullptr) prev->next = new_node;

    if (next == nullptr) tail = new_node;
    if (prev == nullptr) head = new_node;
}


template <class T>
inline size_t DLList<T>::get_size() {
    size_t size = 0;
    for (DLLNode<T>* curr = head; curr != nullptr; curr = curr->next, size++);
    return size;
}

template <class T>
inline void DLList<T>::delete_node(DLLNode<T>* node) {
    if (node == nullptr)
        throw string("Can't delete nullptr from list");

    if (node == head) remove_head();
    else if (node == tail) remove_tail();
    else {
        DLLNode<T>* prev = node->prev;
        DLLNode<T>* next = node->next;

        prev->next = next;
        next->prev = prev;
        delete node;
    }
}



template <class T>
DLList<T>::DLList()
{
    head = nullptr;
    tail = nullptr;
}

template <class T>
DLList<T>::DLList(const DLList<T>& other) {
    head = nullptr;
    tail = nullptr;
    append(other);
}

template <class T>
DLList<T>::~DLList()
{
    clear();
}

template <class T>
void DLList<T>::clear()
{
    DLLNode<T>* tmp = head;
    DLLNode<T>* del_node;

    while (tmp != nullptr) {
        del_node = tmp;
        tmp = tmp->next;
        delete del_node;
    }

    head = nullptr;
    tail = nullptr;
}

template <class T>
bool DLList<T>::is_empty() const
{
    return head == nullptr;
}

template <class T>
void DLList<T>::add_to_head(const T& val)
{
    DLLNode<T>* new_node = new DLLNode<T>(val, head, nullptr);

    if (head != nullptr)
        head->prev = new_node;

    head = new_node;
    if (tail == nullptr)
        tail = new_node;
}

template <class T>
void DLList<T>::add_to_tail(const T& val)
{
    DLLNode<T>* new_node = new DLLNode<T>(val, nullptr, tail);

    if (tail != nullptr) //If list is non-empty
        tail->next = new_node;

    tail = new_node;
    if (head == nullptr)
        head = new_node;
}

template <class T>
void DLList<T>::remove_head()
{
    DLLNode<T>* del_node = head;

    if (is_empty())
        return;

    if (head == tail) // if only one node in list
        head = tail = nullptr;
    else {
        head = del_node->next;
        head->prev = nullptr;
    }
    delete del_node;
}

template <class T>
void DLList<T>::remove_tail()
{
    if (is_empty())
        return;

    DLLNode<T>* del_node = tail;

    if (head == tail) // if only one node in list
        head = tail = nullptr;
    else {
        tail = del_node->prev;
        tail->next = nullptr;
    }

    delete del_node;
}

template <class T>
bool DLList<T>::remove(const T& val)
{
    if (is_empty())
        return false;

    if (val == head->val) {
        remove_head();
        return true;
    }

    if (val == tail->val) {
        remove_tail();
        return true;
    }

    // traverse list to find the node to be deleted
    for (DLLNode<T>* curr = head->next; curr != nullptr; curr = curr->next) {
        if (curr->val == val) {
            DLLNode<T>* pred = curr->prev;
            DLLNode<T>* succ = curr->next;
            pred->next = succ;
            succ->prev = pred;
            delete curr;
            return true;
        }
    }

    return false;
}

template <class T>
bool DLList<T>::contains(const T& val) const
{
    DLLNode<T>* curr;

    for (curr = head; curr != nullptr; curr = curr->next) {
        if (curr->val == val)
            return true;
    }

    return false;
}

template <class T>
DLLNode<T>* DLList<T>::head_node() const
{
    return head;
}

template <class T>
DLLNode<T>* DLList<T>::tail_node() const
{
    return tail;
}

template <class T>
T DLList<T>::head_val() const
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve a value of the head from an empty list.");

    return head->val;
}

template <class T>
T DLList<T>::tail_val() const
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve a value of the tail from an empty list.");

    return tail->val;
}

template <class T>
void DLList<T>::append(const DLList& other)
{
    if (this == &other)
        throw string("ERROR: Can't append list to itself");

    for (DLLNode<T>* curr = other.head; curr != nullptr; curr = curr->next)
        add_to_tail(curr->val);
}

// copy assignment
template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    if (this == &other)
        return *this;

    clear();
    append(other);

    return *this;
}

template<class T>
ostream& operator<<(ostream& out, const DLList<T>& list) {
    out << "[";

    DLLNode<T>* curr = list.head_node();
    while (curr != nullptr) {
        out << curr->get_val();
        if (curr->get_next() != nullptr)
            out << ", ";
        curr = curr->get_next();
    }
    out << "]";

    return out;
}

template<class T>
inline int replaceVal(DLList<T>& list, T v1, T v2) {
    DLLNode<T>* curr = list.head_node();
    size_t count = 0;
    while (curr != nullptr) {
        if (curr->get_val() == v1) {
            curr->set_val(v2);
            count++;
        }
        curr = curr->get_next();
    }
    return count;
}

template<class T>
inline DLList<T> DLList<T>::prior_v(T v, int count) const {
    if (head == tail) { //in case of empty list or 1 node return the empty list
        return DLList<T>();
    }

    DLLNode<T>* last_node = head; //the last node to be inserted to the new list
    int positon = 0; //the order of the last node to be inserted to the new list
    while (last_node != nullptr) {
        if (last_node->val == v) break;
        last_node = last_node->next;
        positon++;
    }

    if (last_node == nullptr) return DLList<T>();// if val not in list return the empty list

    DLLNode<T>* curr = last_node->prev;//pointer to iterate through list and add nodes 1 by 1
    DLList list;//new list to return

    while (1) {
        if (curr == nullptr || count <= 0) return list;
        list.add_to_head(curr->val);
        curr = curr->prev;
        count--;
    }


}

template <class T>
inline DLList<T> DLList<T>::rmv_ret_negative() {
    if (is_empty()) return DLList<T>();

    DLList<T> new_list;

    for (DLLNode<T>* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->val < 0) {
            new_list.add_to_tail(curr->val);
        }
    }

    DLLNode<T>* curr = head;
    while (curr != nullptr) {
        if (curr->val < 0) {
            DLLNode<T>* temp = curr->next;
            delete_node(curr);
            curr = temp;
        }
        else curr = curr->next;
    }
    return new_list;
}

template <class T>
inline void DLList<T>::rearrange_neg_pos() {
    size_t size = get_size();

    DLLNode<T>* curr = head;
    while (size--) {
        if (curr->val < 0) {
            DLLNode<T>* temp = curr->next;
            add_to_head(curr->val);
            delete_node(curr);
            curr = temp;
        }
        else curr = curr->next;
    }
}

template <class T>
inline void DLList<T>::insert_before_after(T val, T insertVal, int count) {
    DLLNode<T>* insert_node = head;

    while (insert_node != nullptr) {
        if (insert_node->val == val) break;
        insert_node = insert_node->next;
    }

    if (insert_node == nullptr)  // val not found in list so don't perform any insertion
        return;

    DLLNode<T>* prev = insert_node->prev;
    while (count--) {
        insert_after_node(insert_node, insertVal);
        insert_after_node(prev, insertVal);
    }
}

template <class T>
inline void DLList<T>::collapse_m_nodes(int m) {
    if (is_empty()) return;

    DLList<T> new_list;
    DLLNode<T>* curr = head;

    size_t size = get_size();
    size_t o_size = size;
    size = ceil(size / (double)m);

    T* arr = new T[size];
    T* div = new T[size];

    for (int i = 0; i < size - 1; i++) {
        div[i] = m;
    }
    if (o_size % m) div[size - 1] = o_size % m;
    else div[size - 1] = m;


    size_t i = 0;

    while (i < size) { // wrong
        arr[i] = curr->val;
        int j = 0;
        curr = curr->next;
        while (j < m - 1) {
            if (curr == nullptr) break;
            arr[i] += curr->val;
            j++;
            curr = curr->next;
        }
       // if(curr != nullptr) curr = curr->next;
       // cout << arr[i] << ' ';
        arr[i] = arr[i] / div[i];
        i++;
        if (curr == nullptr) break;
    }

    for (int i = 0; i < size; i++) {
        new_list.add_to_tail(arr[i]);
    }

    clear();
    append(new_list);

}





