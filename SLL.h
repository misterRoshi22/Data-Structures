#pragma once
#include<iostream>
using namespace std;

template <typename T> class Node {
public:
	T data;
	Node<T>* next;
	
	Node(T data, Node<T>* next) {
		this->data = data;
		this->next = next;
	}
};


template<typename T> class SLL {
private:
	Node<T>* head;
	Node<T>* tail;
	unsigned int size;

public:
	SLL() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	SLL (T arr[], unsigned int size){
		head = nullptr;
		tail = nullptr;
		this->size = 0;
		while (this->size < size) {
			Node<T>* new_node = new Node<T>(arr[this->size++], nullptr);
			if (tail == nullptr)
				head = new_node;
			else
				tail->next = new_node;
			tail = new_node;
		}
	}

	~SLL() {
		Node<T>* curr = head;
		Node<T>* del_node;
		while (curr != nullptr) {
			del_node = curr;
			curr = curr->next;
			delete del_node;
		}
	}

	bool is_empty() const {
		return size == 0;
	}

	T get_head() const {
		return head->data;
	}

	T get_tail() const {
		return tail->data;
	}

	unsigned int get_size() const {
		return size;
	}

	void print(char extra = '\n') const {
		Node<T>* curr = head;
		cout << "[";
		while (curr != nullptr) {
			cout << curr->data;
			if (curr->next != nullptr) cout << ",";
			curr = curr->next;
		}
		cout << "]" << extra;
	}

	T get_at(unsigned int index) const {
		if (index >= size || index < 0)  return INT_MAX;

		unsigned int it = 0;
		Node<T>* curr = head;
		while (1) {
			if (it == index) return curr->data;
			curr = curr->next;
			it++;
		}
	}

	void push_head(T data) {
		Node<T>* new_node = new Node<T>(data, head);
		head = new_node;
		if (tail == nullptr) tail = new_node;
		size++;
	}

	void push_tail(T data) {
		if (size == 0) {
			push_head(data);
			return;
		}
		else {
			Node<T>* new_node = new Node<T>(data, nullptr);
			tail->next = new_node;
			tail = new_node;
		}
		size++;
	}

	void pop_head() {
		if (is_empty()) return;

		Node<T>* del_node = head;
		head = head->next;
		delete del_node;

		if (head == nullptr)
			tail = nullptr;
		this->size--;
	}

	void pop_tail() {
		if (is_empty()) return;
		if (size == 1) pop_head();
		else {
			Node<T>* STL = head;

			while (STL->next != tail) {
				STL = STL->next;
			}

			delete tail;
			STL->next = nullptr;
			tail = STL;
			size--;
		}
	}

	void pop_at(unsigned int index) {
		if (index >= size || index < 0) return;

		if (index == 0) pop_head();
		else if (index == size - 1) pop_tail();
		else {
			int it = 0;
			Node<T>* curr = head;
			Node<T>* prev = head;
			while (it != index) {
				prev = curr;
				curr = curr->next;
				it++;
			}
			prev->next = curr->next;
			delete curr;
			size--;
		}
	}

	void push_at(unsigned int index, T data) {
		if (index > size || index < 0) return;

		if (index == 0) push_head(data);
		else if (index == size) push_tail(data);
		else {
			Node<T>* new_node = new Node<T>(data, nullptr);
			Node<T>* curr = head;
			int it = 0;
			while (it != index - 1) {
				curr = curr->next;
				it++;
			} 
			new_node->next = (curr->next);
			curr->next = new_node;
			size++;

		}
	}
	
	void assign(T arr[], int size) {
		this->clear();

		for (int i = 0; i < size; i++) {
			this->push_tail(arr[i]);
		}
	}

	int find(T data) const {
		if (is_empty()) return -1;
		Node<T>* curr = head;

		int it = 0;
		while (curr != nullptr) {
			if (curr->data == data) return it;
			it++;
			curr = curr->next;
		}
		return -1;
	}

	SLL<int> find_all(T data) const {
		SLL<int>* indices = new SLL<int>;
		if (this->is_empty()) return *indices;
		Node<T>* curr = head;

		int it = 0;
		while (it < size) {
			if (curr->data == data) indices->push_tail(it);
			curr = curr->next, it++;
		}
		return *indices;
	}

	void clear() {
		while (!is_empty()) {
			this->pop_head();
		}
	}

	void reverse() {
	
		Node<T>* prev = nullptr;
		Node<T>* curr = head;
		Node<T>* next;
		tail = head;

		while (curr != nullptr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}

	T min() const {
		T MIN = head->data;
		Node<T>* curr = head;
		while (curr != nullptr) {
			if (curr->data < MIN) MIN = curr->data;
			curr = curr->next;
		}
		return MIN;
	}

	T max() const {
		T MAX = head->data;
		Node<T>* curr = head;
		while (curr != nullptr) {
			if (curr->data > MAX) MAX = curr->data;
			curr = curr->next;
		}
		return MAX;
	}

	void sort() {
		int n = this->size ;

		while (n--){ 
			Node<T>* curr = head;
			T MIN = head->data;
			int index = 0;
			for (int i = 0; i <= n; i++) {
				if (curr->data < MIN) {
					index = i;
					MIN = curr->data;
				}
				curr = curr->next;
			}
			pop_at(index);
			push_tail(MIN);
		}
	}

	void operator+=(T data) {
		push_tail(data);
	}
	
};
