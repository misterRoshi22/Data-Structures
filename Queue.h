#pragma once
#include "DLL.h"

template <class T>
class QueueDLL {
private:
	DLL data;
public:
	void enqueue(const T& val);
	T dequeue();               
	void clear();
	T front() const;
	T back() const;
	size_t size() const;
	bool empty() const;
};

template <class T>
void QueueDLL<T>::enqueue(const T& val) {
	data.push_tail(val);
}

template <class T>
T QueueDLL<T>::dequeue() {
	if (data.is_empty())
		throw string("Can't dequeue empty list");
	else {
		T first = front();
		data.pop_head();
		return first;
	}
}

template <class T>
void QueueDLL<T>::clear() {
	data.clear();
}

template <class T>
T QueueDLL<T>::front() const {
	return data.head_val();
}

template <class T>
T QueueDLL<T>::back() const {
	return data.tail_val();
}

template <class T>
size_t QueueDLL<T>::size() const {
	return data.get_size();
}

template <class T>
bool QueueDLL<T>::empty() const {
	return data.is_empty();
}
