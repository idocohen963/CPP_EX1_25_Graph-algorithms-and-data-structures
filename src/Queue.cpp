// idocohen963@gmail.com
#include "../include/Queue.hpp"
#include <stdexcept>

namespace graph {

Queue::Queue(int capacity) : capacity(capacity), front(0), rear(0), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be positive");
    }
    array = new int[capacity];
}

Queue::~Queue() {
    delete[] array;
}

void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    }
    
    array[rear] = value;
    rear = (rear + 1) % capacity;
    size++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    
    int value = array[front];
    front = (front + 1) % capacity;
    size--;
    return value;
}

int Queue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    
    return array[front];
}

bool Queue::isEmpty() const {
    return size == 0;
}

bool Queue::isFull() const {
    return size == capacity;
}

int Queue::getSize() const {
    return size;
}

} // namespace graph
