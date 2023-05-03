#ifndef DATA_STRUCTURES_PRACTICE_QUEUEARRAY_H
#define DATA_STRUCTURES_PRACTICE_QUEUEARRAY_H

#include <iostream>

using namespace std;

const int DEFAULT_CAPACITY = 8;

template<class T>
class QueueArray {
private:
    T *data;
    size_t capacity;
    size_t size;
    int first;
    int last;

    bool is_full() const;

    void resize(int new_capacity);

public:
    QueueArray();

    QueueArray(const QueueArray &other);

    ~QueueArray() { delete data; }

    void enqueue(const T &val);

    T dequeue();

    void clear();

    size_t get_size() const;

    T get_first() const;

    T get_last() const;

    bool is_empty() const;

    QueueArray<T> &operator=(const QueueArray &other);

    void print() const;

    void postpone();

    void normalize();
};

template<class T>
void QueueArray<T>::normalize() {
    if (first == 0) return;
    QueueArray<T> temp;
    while (!this->is_empty()) {
        temp.enqueue(this->dequeue());
    }
    *this = temp;
}

template<class T>
void QueueArray<T>::postpone() {
    if (size <= 1) return;
    swap(data[first], data[(first + 1) % capacity]);
}

template<class T>
T QueueArray<T>::get_first() const {
    if (is_empty())
        throw string("EMPTY STRING!");
    return data[first];
}

template<class T>
T QueueArray<T>::get_last() const {
    if (is_empty())
        throw string("EMPTY STRING");
    return data[last];
}

template<class T>
bool QueueArray<T>::is_empty() const {
    return first == -1;
}

template<class T>
bool QueueArray<T>::is_full() const {
    return size == capacity;
}

template<class T>
size_t QueueArray<T>::get_size() const {
    return size;
}

template<class T>
void QueueArray<T>::clear() {
    delete[] data;
    data = new T[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
    last = first = -1;
    size = 0;
}

template<class T>
void QueueArray<T>::enqueue(const T &val) {
    if (is_full())
        resize(capacity * 2);

    last = (last + 1) % capacity;
    data[last] = val;
    ++size;

    if (first == -1)
        first = 0;
}

template<class T>
T QueueArray<T>::dequeue() {
    if (is_empty())
        throw string("EMPTY STRING");

    T temp = data[first];
    first = (first + 1) % capacity;
    size--;
    if (!size) {
        last = first = -1;
    }

    if (size < capacity / 4 && capacity > DEFAULT_CAPACITY)
        resize(capacity / 2);

    return temp;
}

template<class T>
QueueArray<T>::QueueArray() {
    capacity = DEFAULT_CAPACITY;
    data = new T[capacity];
    size = 0;
    first = last = -1;
}

template<class T>
QueueArray<T>::QueueArray(const QueueArray &other) {
    data = nullptr;
    *this = other;
}

template<class T>
QueueArray<T> &QueueArray<T>::operator=(const QueueArray &other) {
    if (this == &other)
        return *this;

    delete[] this->data;
    capacity = other.capacity;
    size = other.size;
    first = other.first;
    last = other.size;

    data = new T[capacity];

    int j = other.first;
    for (int i = 0; i < size; i++) {
        data[i] = other.data[j];
        j = (j + 1) % capacity;
    }
    return *this;
}

template<class T>
void QueueArray<T>::resize(int new_capacity) {
    if (new_capacity < size)
        throw string("INVALID CAPACITY");

    T *new_data = new T[new_capacity];
    int j = this->first;
    for (int i = 0; i < size; i++) {
        new_data[i] = this->data[j];
        j = (j + 1) % capacity;
    }

    delete[] data;

    data = new_data;
    capacity = new_capacity;

    size == 0 ? first = -1 : first = 0;
    size == 0 ? last = -1 : last = size - 1;
}

//template<class T>
//void QueueArray<T>::print() const {
//    cout << "[ ";
//    for (int j = first; j != last; j = (j + 1) % capacity) {
//        cout << data[j] << " ";
//    }
//    cout << "]";
//}

template<class T>
void QueueArray<T>::print() const {
    cout << "[";
    int j = this->first;
    for (int i = 0; i < size; i++) {
        cout << data[j];
        if (i != size - 1) cout << ", ";
        j = (j + 1) % capacity;
    }
    cout << "]";

}


#endif //DATA_STRUCTURES_PRACTICE_QUEUEARRAY_H
