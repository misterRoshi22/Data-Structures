#pragma once
#include <iostream>
using namespace std;

class Node {
private:
	int data;
	Node* next;

public:
	Node(int data, Node* next) {
		this->data = data;
		this->next = next;
	}
	void set_data(int data) {
		this->data = data;
	}
	void set_next(Node* next) {
		this->next = next;
	}
	int get_data() const {
		return data;
	}
	Node* get_next() const {
		return next;
	}
	void operator=(int data) {
		this->data = data;
	}
	friend class SLL;
};

class SLL {
private:
	Node* head;
	Node* tail;

	void print_rec(Node* curr) {
		if (curr == nullptr) return;
		print_rec(curr->next);
		cout << curr->data;
		if (curr != head) cout << ",";
	}

public:

	SLL() {
		head = nullptr;
		tail = nullptr;
	}

	SLL(int arr[], int size) {
		head = nullptr;
		tail = nullptr;
		int i = 0;
		while (size--) {
			push_tail(arr[i]);
			i++;
		}
	}

	SLL(const SLL& l2) {
		head = nullptr;
		tail = nullptr;
		if (l2.is_empty()) return;
		Node* curr = l2.head;

		while (curr != nullptr) {
			this->push_tail(curr->data);
			curr = curr->next;
		}
	}

	bool is_empty() const {
		return head == nullptr;
	}

	int front() const {
		if (is_empty()) throw string("ERROR");
		return head->data;
	}

	int back() const {
		if (is_empty()) throw string("ERROR");
		return tail->data;
	}

	void push_tail(int data) {
		Node* curr = new Node(data, nullptr);

		if (is_empty()) {
			head = curr;
			tail = curr;
			return;
		}

		this->tail->next = curr;
		tail = curr;
	}
	
	void push_head(int data) {
		if (is_empty() || head == tail) push_tail(data);

		Node* curr = new Node(data, head);
		this->head = curr;
	}

	void pop_tail() {
		if (is_empty()) return;
		if (head == tail) {
			pop_head();
			return;
		}
		Node* curr = head;
		while (curr->next != tail) {
			curr = curr->next;
		}
		delete tail;
		curr->next = nullptr;
		tail = curr;

	}

	void pop_head() {
		if (is_empty()) return;
		Node* temp = head;
		head = head->next;
		delete temp;
		if (head == nullptr) tail = nullptr;
	}

	size_t get_size() const {
		Node* curr = head;
		size_t size = 0;
		while (curr != nullptr) {
			size++;
			curr = curr->next;
		}
		return size;
	}

	void print(char extra = '\n') const {
		Node* curr = head;
		cout << "[";
		while (curr != nullptr) {
			cout << curr->data;
			if (curr != tail)cout << ",";
			curr = curr->next;
		}
		cout << "]" << extra;
	}

	void print_reverse(char extra = '\n') {
		cout << "[";
		print_rec(head);
		cout << "]" << extra;
	} 

	Node& operator[](int index) const {
		if (index < 0 || index >= get_size())
			throw string("ERROR");
		Node* curr = head;
		while (index--) {
			curr = curr->next;
		}
		return *curr;
	}

	void clear() {
		while (!is_empty()) {
			pop_head();
		}
	}

	void append(const SLL& l2) {
		Node* curr = l2.head;

		while (curr != nullptr) {
			this->push_tail(curr->data);
			curr = curr->next;
		}
	}

	SLL& operator=(const SLL& l2) {
		this->clear();
		int size = l2.get_size();
		Node* curr = l2.head;
		while (curr != nullptr) {
			this->push_tail(curr->data);
			curr = curr->next;
		}
		return *this;
	}

	void pop_at(int index) {
		int size = get_size();
		if (index < 0 || index >= size) return;

		if (index == 0) {
			pop_head();
			return;
		}
		if (index == size - 1) {
			pop_tail();
			return;
		}

		Node* prev = nullptr;
		Node* curr = head;
		Node* next = head->next;
		while (index--) {
			prev = curr;
			next = next->next;
			curr = curr->next;
		}
		delete curr;
		prev->next = next;
	}

	void reverse() {
		if (head == tail) return;

		Node* prev = nullptr;
		Node* curr = head;
		Node* next;
		tail = head;
		while (curr != nullptr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}

	int find(int data) const {
		int i = 0;
		Node* curr = head;
		while (curr != nullptr) {
			if (curr->data == data) return i;
			i++, curr = curr->next;
		}
		return -1;
	}

	SLL find_all(int data) const {
		SLL indices;
		Node* curr = head;
		int i = 0;
		while (curr != nullptr) {
			if (curr->data == data) indices.push_tail(i);
			i++, curr = curr->next;
		}
		return indices;
	}
	
	void remove_after(int data)  {
		if (is_empty()) return;

		Node* curr = head;

		while (1) {
			curr = curr->next;
			if (curr == nullptr) break;
			if (curr->data == data) break;
		}

		if (curr == nullptr) return;

		Node* new_node = curr;
		curr = curr->next;
		Node* del_node;
		while (curr != nullptr) {
			del_node = curr;
			curr = curr->next;
			delete del_node;
		}
		tail = new_node;
		tail->next = nullptr;
	}

	void remove_all(int data) {
		Node* prev = nullptr;
		Node* curr = head;
		Node* next;
		while (curr != nullptr) {
			next = curr->next;
			if (curr == tail && curr->data == data) {
				pop_tail();
				return;
			}
			else if (curr->data == data && curr == head) {
				curr = curr->next;
				pop_head();
			}
			else if(curr->data == data) {
				Node* del_node = curr;
				curr = curr->next;
				prev ->next = curr;
				delete del_node;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}

	void bubble_sort() {
		int n = get_size();
		while (n--) {
			Node* curr = head;
			while (curr != tail) {
				if (curr->data > curr->next->data)
					swap(curr->data, curr->next->data);
				curr = curr->next;
			}
		}
	}

	void selection_sort() {
		if (is_empty()) return;
		Node* min = head;
		while (min != tail) {
			Node* curr = min;
			while (curr != nullptr) {
				if (curr->data < min->data)
					swap(min->data, curr->data);
				curr = curr->next;
			}
			min = min->next;
		}
	}

	void insertion_sort() {
		Node* sorted = tail;
		Node* unsorted = head;

		while (unsorted->next != tail) {
			unsorted = unsorted->next;
		}
	}

	int sum() const {
		Node* curr = head;
		int SUM = 0;
		while (curr != nullptr) {
			SUM += curr->data;
			curr = curr->next;
		}
		return SUM;
	}

	void add_list_before_num(SLL l2, int val) {
		if (is_empty()) return;
		Node* start = head;
		Node* curr = head;
		bool p = 0;

		while (curr != tail) { //find node to insert after
			if (curr->next->data == val) {
				start = curr;
				p = 1;
			}
			curr = curr->next;
		}

		if (!p) {
			SLL l3 = l2;
			while (!l3.is_empty()) {
				this->push_head(l3.back());
				l3.pop_tail();
			}
		}


		Node* l2curr = l2.head;//pointer to travese l2

		while (l2curr != nullptr) {
			Node* insert = new Node(l2curr->data, start->next);
			start->next = insert;
			start = insert;

			l2curr = l2curr->next;
		}
	}

};
