#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<class T>
class DLList;

template< class T>
class DLLNode {
private:
	T val;
	DLLNode* next;
	DLLNode* prev;

	friend class DLList<T>;
public:
	DLLNode(T val, DLLNode* next = nullptr, DLLNode* prev = nullptr) {
		this->val = val;
		this->next = next;
		this->prev = prev;
	}

    T get_val() const { return val; }
	DLLNode* get_next() const{ return next; }
	DLLNode* get_prev() const { return prev; }
};


template <class T>
class DLList{
public:
    using Node = DLLNode<T>;
private:
	Node* head;
	Node* tail;
	size_t size;
public:
    DLList() { head = tail = nullptr; size = 0; }
    DLList(const DLList& other) { head = tail = nullptr; append(other); }
	~DLList() { clear(); }

    bool empty() const { return size == 0; }

    Node* head_node() const { return head; }
    Node* tail_node() const { return tail; }
    T head_val() const { return head->val; }
    T tail_val() const { return tail->val; }

    void add_to_head(const T& val);
    void add_to_tail(const T& val);
    void append(const DLList& otherList);

    void remove_head();
    void remove_tail();
    void clear();

    bool contains(const T& val) const;
    DLList& operator=(const DLList& other);

    class DLLIterator { //Inner Class
    private:
        friend class DLList<T>;
        Node* nodePtr;
        DLLIterator(Node* new_ptr) :nodePtr(new_ptr) {} //Private as we only want are friends to construct

    public:
        DLLIterator() : nodePtr(nullptr) {};

		bool operator== (const DLLIterator& itr) const { return nodePtr == itr.nodePtr; }
        bool operator!= (const DLLIterator& itr) const { return nodePtr != itr.nodePtr; }
        T& operator *() const { return nodePtr->val; }

		DLLIterator& operator=(const DLLIterator& other) {
			this->nodePtr = other.nodePtr;
			return *this;
		}
		DLLIterator operator++() {
			nodePtr = nodePtr->next;
			return *this;
		}
		DLLIterator operator--() {
			nodePtr = nodePtr->prev;
			return *this;
		}
        DLLIterator operator++(int) {
            DLLIterator temp = *this;
            nodePtr = nodePtr->next;
            return temp;
        }
		DLLIterator operator--(int) {
			DLLIterator temp = *this;
			nodePtr = nodePtr->prev;
			return temp;
		}
		
    }; //End of Inner Class

	DLLIterator begin() const { return DLLIterator(head); }
	DLLIterator rbegin() const { return DLLIterator(tail); }

	DLLIterator end() const { return DLLIterator(nullptr); }

	void selection_sort();

	void advance(DLLIterator& position, int steps);
};

template<class T>
inline void DLList<T>::add_to_head(const T& val)
{
	if (empty()) {
		Node* new_node = new Node(val, nullptr, nullptr);
		head = tail = new_node;
	}
	else {
		Node* new_node = new Node(val, head, nullptr);
		head->prev = new_node;
		head = new_node;
	}
	size++;
}

template<class T>
inline void DLList<T>::add_to_tail(const T& val)
{
	if (empty()) {
		add_to_head(val);
	}
	else {
		Node* new_node = new Node(val, nullptr, tail);
		tail->next = new_node;
		tail = new_node;
		size++;
	}
}

template<class T>
inline void DLList<T>::append(const DLList& otherList)
{
	if (this == &otherList)
		throw string("Can't append list to itself");
	for (auto it: otherList) {
		this->add_to_tail(it);
	}
}


template<class T>
inline void DLList<T>::remove_head()
{
	if (size <= 1) {
		delete head;
		head = tail = nullptr;
	}
	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	size--;
}

template<class T>
inline void DLList<T>::remove_tail()
{
	if (size <= 1) remove_head();
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		size--;
	}
}

template<class T>
inline void DLList<T>::clear()
{
	while (!empty()) {
		remove_head();
	}
	head = tail = nullptr;
}

template<class T>
inline bool DLList<T>::contains(const T& val) const
{
	for (DLLIterator it = begin(); it != end(); it++) {
		if (*it == val)return true;
	}
	return false;
}

template<class T>
inline DLList<T>& DLList<T>::operator=(const DLList& other)
{
	this->clear();
	this->append(other);
}

template<class T>
inline void DLList<T>::selection_sort()
{
	for (DLLIterator i = begin(); i != end(); i++) {
		DLLIterator min = i;
		for (DLLIterator j = i; j != end(); j++) {
			if (*j < *min) {
				min = j;
			}
		}
		if (i != min) {
			swap(*i, *min);
		}
	}
}

template<class T>
inline void DLList<T>::advance(DLLIterator& position, int steps) {
	while (steps--) {
		position++;
		if (position == nullptr)
			break;
	}
}
