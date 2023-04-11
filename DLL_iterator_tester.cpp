#include <iostream>
#include <algorithm>
#include "DLL_iterator.h"

using namespace std;

int main(void) {

	DLList<int> l1;
	DLList<int> l2;

	for (int i = 1; i <= 10; i++)
		l1.add_to_tail(i);

	for (int i = 5; i <= 15; i++)
		l2.add_to_head(i);

	l1.append(l2);

	l1.selection_sort();

	cout << "Using Node Pointers:\t";

	for (DLLNode<int>* curr = l1.head_node(); curr != nullptr; curr = curr->get_next()) {
		cout << curr->get_val() << ' ';
	}

	cout << "\nUsing Iterators:\t";
	for (DLList<int>::DLLIterator it = l1.begin(); it != l1.end(); it++) {
		cout << *it;
		cout << " ";
	}

	cout << "\nUsing Auto:\t\t";
	for (auto it : l1) {
		cout << it << ' ';
	}


	//Testing Advance
	DLList<int>::DLLIterator it2 = l1.begin();
	l1.advance(it2, 5);
	cout << "\nUsing Iterators:\t";
	for (DLList<int>::DLLIterator it = it2; it != l1.end(); it++) {
		cout << *it;
		cout << " ";
	}


}

