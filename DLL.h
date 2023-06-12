#pragma once
#include <iostream>
using namespace std;

template <class T>
class DLList; // forward declaration

template <class T>
class DLLIterator;

template <class T>
class DLLNode {
private:
    T val;
    DLLNode<T> *next;
    DLLNode<T> *prev;
public:
    DLLNode(T val, DLLNode<T>* next = nullptr, DLLNode<T>* prev = nullptr) {
        this->val = val;
        this->next = next;
        this->prev = prev;
    }
    friend class DLList<T>;
    friend class DLLIterator<T>;
};

template <class T>
class DLLIterator{
private:
    DLLNode<T>* ptr;
    friend class DLList<T>;
public:
    DLLIterator(DLLNode<T>* p = nullptr) {
        ptr = p;
    }
    T& operator*() {
        return ptr->val;
    }
    DLLIterator<T>& operator++() {
        ptr = ptr->next;
        return *this;
    }
    DLLIterator<T>& operator--() {
        ptr = ptr->prev;
        return *this;
    }
    bool operator==(const DLLIterator<T>& right) const {
        return ptr == right.ptr;
    }
    bool operator!=(const DLLIterator<T>& right) const {
        return ptr != right.ptr;
    }
};

template <class T>
class DLList {
private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    size_t size;
    void deleteNode(DLLNode<T>* node){
        if(node == head)
            removeFromHead();
        else if(node == tail)
            removeFromTail();
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            size--;
            delete node;
        }
    }
    DLLNode<T>* search(T& val){
        for(DLLIterator<T> it = begin(); it != end(); ++it)
            if(*it == val)
                return it.ptr;
        return nullptr;
    }
public:
    DLLIterator<T> begin() const {
        return DLLIterator<T>(head);
    }
    DLLIterator<T> end() const {
        return DLLIterator<T>(tail->next);
    }

    DLList() {
        head = tail = nullptr;
        size = 0;
    }
    ~DLList(){
        clear();
    }
    DLList(const DLList<T>& other){
        head = tail = nullptr;
        size = 0;
        this->append(other);
    }
    DLList<T>& operator=(const DLList<T>& other){
        if(this != &other){
            clear();
            this->append(other);
        }
        else
            throw string("Self assignment!");
        return *this;
    }
    void addToHead(T val){
        DLLNode<T>* temp = new DLLNode<T>(val, head);
        if(head == nullptr)
            tail = temp;
        else
            head->prev = temp;
        head = temp;
        size++;
    }
    void addToTail(T val){
        DLLNode<T>* temp = new DLLNode<T>(val, nullptr, tail);
        if(tail == nullptr)
            head = temp;
        else
            tail->next = temp;
        tail = temp;
        size++;
    }
    void removeFromHead() {
        if(isEmpty())
            throw string("Empty list!");

        if(head == tail){
            delete head;
            head = tail = nullptr;
        }
        else{
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        size--;
    }
    void removeFromTail() {
        if(head == tail)
            removeFromHead();
        else{
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            size--;
        }
    }
    void append(const DLList& other){
        for(DLLIterator<T> it = other.begin(); it != other.end(); ++it)
            addToTail(*it);
    }
    void print() const{
        cout <<"[ ";
        for(DLLIterator<T> it = begin(); it != end(); ++it)
            cout << *it << " ";
        cout <<"]\n";
    }
    void clear(){
        while(!isEmpty())
            removeFromHead();
        head = tail = nullptr;
    }
    bool isEmpty() const {
        return head == nullptr;
    }
    size_t getSize() const {
        return size;
    }
    bool remove(T val){
        DLLNode<T>* temp = search(val);
        if(temp != nullptr){
            deleteNode(temp);
            return true;
        }
        return false;
    }
    bool contains(T val) const {
        return search(val) != nullptr;
    }
    void reverse(){
        DLLNode<T>* temp = head;

        while(temp != nullptr) {
            DLLNode<T> *next = temp->next;
            DLLNode<T> *prev = temp->prev;
            temp->next = prev;
            temp->prev = next;
            temp = next;
        }
        DLLNode<T>* temp2 = head;
        head = tail;
        tail = temp2;
    }

    T& operator[](size_t index){
        if(index >= size || index < 0)
            throw string("Index out of bounds!");
        DLLIterator<T> it = begin();
        for(size_t i = 0; i < index; i++)
            ++it;
        return *it;
    }

    DLList sublist(int index1, int index2) const{
        if(index2 < index1 || index1 < 0 || index2 >= size)
            throw string("Invalid indexes!");
        DLList<T> result;
        DLLIterator<T> it = begin();
        for(int i = 0; i < index1; i++)
            ++it;
        for(int i = index1; i <= index2; i++){
            result.addToTail(*it);
            ++it;
        }
        return result;
    }

    void selection_sort(){
        for(DLLIterator<T> it1 = begin(); it1 != end(); ++it1){
            DLLIterator<T> min = it1;
            for(DLLIterator<T> it2 = it1; it2 != end(); ++it2){
                if(*it2 < *min)
                    min = it2;
            }
            if(min != it1)
                swap(*it1, *min);
        }
    }

    void insertion_sort(){
        for(DLLNode<T>* i = head->next; i != nullptr; i = i->next){ // for( int i = 1; i < size; i++)
            T temp = i->val; // int temp = a[i];
            DLLNode<T>* j = i->prev; // int j = i - 1;

            while(j != nullptr && temp < j->val){ // while(j >= 0 && temp < a[j])
                j->next->val = j->val; // a[j + 1] = a[j];
                j = j->prev; // j--;
            }
            if(j)
                j->next->val = temp; // a[j + 1] = temp;
            else {
                head->val = temp;
            }
        }
    }

};
