#pragma once
#include <iostream>
#include "DLList.h"
using namespace std;

const int DEFAULT_SIZE = 15;

template <class T>
class HashTable {
private:
    DLList<T>* table;
    int n; // number of elements
    int m; // number of buckets

    int hash_value(const T &val) const;
    void resize(int new_size) {
        DLList<T> values = elements();
        delete[] table;

        m = new_size;
        table = new DLList<T>[m];

        while(!values.isEmpty()) {
            int index = hash_value(values.headValue());
            table[index].addToTail(values.headValue());
            values.removeFromHead();
        }
    }

public:
    HashTable(){
        m = DEFAULT_SIZE;
        n = 0;
        table = new DLList<T>[m];
    }

    HashTable(const HashTable& other) {
        m = other.m;
        n = other.n;
        table = new DLList<T>[m];
        for(int i = 0; i < m; i++)
            table[i] = other.table[i]; //assignment operator has been overloaded
    }

    ~HashTable() {
            delete[] table;
            //automatically calls the destructor for each DLList
    }

    bool isEmpty() const {
        return n == 0;
    }

    //Asymptotic complexity
    //O(1) if hashing is perfect
    //O(n) if hashing is the worst possible (all elements in same bucket) and the element is not in the list or the last element in the list
    //O(n/m)    if the element are uniformly distributed across the buckets
    //          this is O(1) if n and m are within a constant factor of each other

    bool contains(const T& val) const {
        int index = hash_value(val); // hash value of val
        return table[index].contains(val); // search the list at index
    }

    //Always O(1) regardless of the hash function
    //O(n + m) id resizing is required

    void insert(const T& val) { //allow duplicates
        int index = hash_value(val); // hash value of val
        table[index].addToTail(val); // insert at the end of the list at index
        n++;
        if(n / m >= 8) // if load factor is greater than 8
            resize(2*m);
    }

    bool remove(const T& val) {
        int index = hash_value(val); // hash value of val
        bool removed = table[index].remove(val); // remove val from the list at index
        if(removed)
            n--;
        if(n / m <= 2 && m > DEFAULT_SIZE) // if load factor is less than 2
            resize(m/2);
        return removed;
    }

    DLList<T> elements() const {
        DLList<T> result;
        for(int i = 0; i < m; i++)
            result.append(table[i]);
        return result;
    }

    void clear() {
        delete [] table;
        m = DEFAULT_SIZE;
        n = 0;
        table = new DLList<T>[m];
    }

    HashTable<T>& operator=(const HashTable<T>& other) {
        if(this != &other) {
            delete[] table;
            m = other.m;
            n = other.n;
            table = new DLList<T>[m];
            for(int i = 0; i < m; i++)
                table[i] = other.table[i]; //assignment operator has been overloaded
        }
        return *this;
    }
};


//hash function for integers
template<>
int HashTable<int>::hash_value(const int &val) const {
    return abs(val) % m;
}

//hash function for strings
template<>
int HashTable<string>::hash_value(const string &val) const {
    int sum = 0;
    const int R = 33;
    for(char c : val)
        sum  = (sum * R + c) % m;
    return abs(sum);
}
