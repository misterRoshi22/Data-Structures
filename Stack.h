#pragma once
#include "DLL.h"

template <class T>
class StackDLL {
private:
	DLL<T> data;
public:
	void push(T data);
	T pop();
	T top() const;
	size_t size() const;
	bool empty() const;
};

template <class T>
void StackDLL<T>::push(T data) {
	data.push_tail(data);
}

template <class T>
T StackDLL<T>::pop() {
	if (data.is_empty())
		throw string("Can't pop() empty stack");
	else {
		T _top = data.tail_val();
		data.pop_tail();
		return _top;
	}
}

template <class T>
T StackDLL<T>::top() const {
	if (data.is_empty())
		throw string("Empty stack");
	else return
		data.tail_val();
}

template <class T>
size_t StackDLL<T>::size() const {
	return data.get_size();
}

template <class T>
bool StackDLL<T>::empty() const {
	return data.is_empty();
}
