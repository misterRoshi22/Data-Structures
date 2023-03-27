#pragma once
#include <iostream>
using namespace std;

template <class T>
class DLL;

template <class T>
class Node {
private:
	T data;
	Node* next;
	Node* prev;

public:
	Node(T data, Node* next = nullptr, Node* prev = nullptr) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	friend class DLL<T>;
};

template <class T>
class DLL {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	DLL() {
		head = nullptr;
		tail = nullptr;
	}

	DLL(T data[], int size) {
		head = nullptr;
		tail = nullptr;
		for (int i = 0; i < size; i++)
			push_tail(data[i]);
	}

	DLL(const DLL& d2) {
		head = nullptr;
		tail = nullptr;

		for (Node<T>* curr = d2.head; curr != nullptr; curr = curr->next) {
			this->push_tail(curr->data);
		}
	}

	bool is_empty() const {
		return head == nullptr;
	}

	int get_size() const {
		int size = 0;
		for (Node<T>* curr = head; curr != nullptr; curr = curr->next, size++);
		return size;
	}

	T head_val() const {
		if (is_empty())
			throw string("Empty List");
		return head->data;
	}

	T tail_val() const {
		if (is_empty())
			throw string("Empty List");
		return tail->data;
	}

	Node<T>* head_node() const {
		return head;
	}

	Node<T>* tail_node() const {
		return tail;
	}

	void push_tail(T data) {
		Node<T>* new_node = new Node<T>(data);

		if (is_empty()) {
			head = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
	}

	void push_head(T data) {
		Node<T>* new_node = new Node<T>(data);

		if (is_empty()) push_tail(data);
		else {
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
	}

	void pop_head() {
		if (is_empty())
			return;
		else if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node<T>* del_node = head;
			head = head->next;
			head->prev = nullptr;
			delete del_node;
		}
	}

	void pop_tail() {
		if (head == tail)
			pop_head();
		else {
			Node<T>* del_node = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete del_node;
		}
	}

	void remove(T data) {
		while (!this->is_empty() && this->head_val() == data)
			this->pop_head();
		this->print();

		Node<T>* curr = head;
		while (curr != tail) {
			if (curr->data == data) {
				Node<T>* del_node = curr;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				curr = curr->next;
				delete del_node;
			}
			else
				curr = curr->next;
		}

		if(this->tail_val() == data)
			this->pop_tail();
	}

	void remove(int index1, int index2) {
		int size = get_size();
		if (index1 < 0 || index1 >= size)
			throw string("Invalid index passed to remove()");

		if (index1 == 0) {
			index2++;
			while (index2-- && !is_empty()) 
				this->pop_head();
			return;
		}
		
		int index = index1;
		Node<T>* curr = head;
		while (index--)
			curr = curr->next;

		Node<T>* prev = curr->prev;

		int count = index2 - index1 + 1;

		while (count-- && curr != nullptr) {
			Node<T>* del_node = curr;
			curr = curr->next;
			prev->next = curr;
			if (curr != nullptr) curr->prev = prev;
			else {
				tail = prev;
			}
			delete del_node;
		}
			
	}
		
	void clear() {
		while (!is_empty())
			this->pop_head();
	}

	void append(const DLL& d2) {
		if (this == &d2) {
			throw string("Can't append list to itself");
		}


		for (Node<T>* i = d2.head; i != nullptr; i = i->next) {
			this->push_tail(i->data);
		}
	}

	void bubble_sort() {
		for (Node<T>* i = head; i != tail; i = i->next) {
			Node<T>* stop = head;
			for (Node<T>* j = tail; j != stop; j = j->prev) {
				if (j->data < j->prev->data) {
					swap(j->data, j->prev->data);
				}
			}
			stop = stop->next;
		}
	}

	void selection_sort() {
		for (Node<T>* i = head; i != tail; i = i->next) {
			Node<T>* min_node = i;
			for (Node<T>* j = i; j != nullptr; j = j->next) {
				if (j->data < min_node->data)
					min_node = j;
			}
			if (min_node != i)
				swap(min_node->data, i->data);
		}
	}

	void insertion_sort() {
		if (head == tail) return;

		for (Node<T>* i = head->next; i != nullptr; i = i->next) {
			T temp = i->data;
			Node<T>* j = i->prev;
			while (j != nullptr && temp < j->data) {
				j->next->data = j->data;
				j = j->prev;
			}
			if (j == nullptr) head->data = temp;
			else j->next->data = temp;
		}
	}

	bool is_sorted() const {
		if (head == tail)
			return true;

		for (Node<T>* i = head; i != tail; i = i->next) 
			if (i->data > i->next->data) return false;
		return true;
	}

	void print(char extra = '\n') const {
		cout << "[";
		for (Node<T>* curr = head; curr != nullptr; curr = curr->next) {
			cout << curr->data;
			if (curr != tail) cout << ",";
		}
		cout << "]" << extra;
	}

	void reverse() {
		if (head == tail)
			return;

		Node<T>* curr = head;

		while (curr != nullptr) {
			Node<T>* temp = curr->next;
			curr->next = curr->prev;
			curr->prev = temp;

			curr = curr->prev;
		}
		Node<T>* temp = head;
		head = tail;
		tail = temp;
	}

	void insert(T data) {
		if (!is_sorted()) {
			throw string("Can't perform insertion on non-sorted list");
			return;
		}

		if (is_empty() || data <= head_val())
			push_head(data);
		else if (data >= tail_val())
			push_tail(data);
		else {
			Node<T>* new_node = new Node<T>(data);
			Node<T>* curr = head;
			while (curr != nullptr) {
				if (curr->data <= data && curr->next->data >= data) break;
				curr = curr->next;
			}

			curr->next->prev = new_node;
			new_node->next = curr->next;

			curr->next = new_node;
			new_node->prev = curr;
		}
	}

	void merge(const DLL& d2) {
		if (!d2.is_sorted() || !is_sorted())
			throw string("Can't merge unsorted array");

		DLL temp;

		Node<T>* curr = this->head;
		Node<T>* d2_curr = d2.head;

		while (1) {
			if (curr == nullptr && d2_curr == nullptr) break;

			if (curr == nullptr) {
				temp.insert(d2_curr->data);
				d2_curr = d2_curr->next;
			}
			else if (d2_curr == nullptr) {
				temp.insert(curr->data);
				curr = curr->next;
			}
			else if (curr < d2_curr) {
				temp.insert(curr->data);
				curr = curr->next;
			}
			else {
				temp.insert(d2_curr->data);
				d2_curr = d2_curr->next;
			}
		}
		this->clear();

		this->append(temp);
	}

	DLL& operator=(const DLL& d2) {
		if (this == &d2)
			return *this;

		this->clear();
		this->append(d2);

		return *this;
	}

	T get_at(int index) const {
		if (index >= get_size() || index < 0)
			throw string("Invalid Index passed to get_at()");

		Node<T>* curr = head;
		while (index--) {
			curr = curr->next;
		}
		return curr->data;
	}

	DLL<T> sublist(int index1, int index2) const {
		int size = this->get_size();
		if (index1 > index2 || index1 < 0 || index2 >= size)
			throw string("Invalid index passed to sublist()"); 

		int index = index1;
		Node<T>* start = head;
		while (index--)
			start = start->next;

		DLL<T> new_list;

		int count = index2 - index1 + 1;

		while (count--) {
			new_list.push_tail(start->data);
			start = start->next;
		}
		return new_list;
	}

	DLL<T> find_common(const DLL& d2) const {
		DLL<T> common;
		for (Node<T>* i = head; i != nullptr; i = i->next) {
			for (Node<T>* j = d2.head; j != nullptr; j = j->next) {
				if (i->data == j->data) {
					common.insert(i->data);
					break;
				}
			}
		}
		return common;
	}

	void unique() {
		if (!is_sorted())
			throw string("Can't call unique() on unsorted list");

		if (head == tail)
			return;

		DLL uni;

		Node<T>* curr = head;

		while (curr != nullptr) {
			if (uni.is_empty())
				uni.push_tail(curr->data);
			else if (curr->data != uni.tail_val())
				uni.push_tail(curr->data);
			curr = curr->next;
		}
		clear();
		append(uni);
	}
};
