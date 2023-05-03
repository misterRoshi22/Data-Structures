#include <iostream>
#include "QueueArray.h"

using namespace std;

template<class T>
void remove_all(QueueArray<T> &queue, const T &val) {
    QueueArray<T> temp;
    while (!queue.is_empty()) {
        T first = queue.dequeue();
        if (first != val)
            temp.enqueue(first);
    }
    queue = temp;
}

template<class T>
void move_first_to(QueueArray<T> &queue, int position) {
    if (position >= queue.get_size())
        throw string("INVALID POSITION");

    QueueArray<T> new_queue;
    T old_first = queue.dequeue();
    int n = queue.get_size() + 1;

    for (int i = 0; i < n; i++) {
        if (i == position)new_queue.enqueue(old_first);
        else new_queue.enqueue(queue.dequeue());
    }

    queue = new_queue;


}

int main(void) {
    QueueArray<int> q1;

    for (int i = 0; i <= 7; i++)
        q1.enqueue(i);

    q1.print();
    move_first_to(q1, 3);
    cout << endl;
    q1.print();

    return 0;
}
