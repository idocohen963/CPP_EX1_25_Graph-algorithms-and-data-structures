// idocohen963@gmail.com
#include "../include/PriorityQueue.hpp"
#include <stdexcept>

namespace graph {

PriorityQueue::PriorityQueue(int capacity) : capacity(capacity), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Priority queue capacity must be positive");
    }
    
    heap = new Node[capacity];
    positions = new int[capacity];
    
    // Initialize positions array with -1 (not in heap)
    for (int i = 0; i < capacity; i++) {
        positions[i] = -1;
    }
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] positions;
}

void PriorityQueue::swap(int i, int j) {
    // Update positions array
    positions[heap[i].vertex] = j;
    positions[heap[j].vertex] = i;
    
    // Swap nodes in heap
    Node temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int PriorityQueue::parent(int index) const {
    return (index - 1) / 2;
}

int PriorityQueue::leftChild(int index) const {
    return 2 * index + 1;
}

int PriorityQueue::rightChild(int index) const {
    return 2 * index + 2;
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)].priority > heap[index].priority) {
        swap(index, parent(index));
        index = parent(index);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < size && heap[left].priority < heap[smallest].priority) {
        smallest = left;
    }
    
    if (right < size && heap[right].priority < heap[smallest].priority) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(index, smallest);
        heapifyDown(smallest);
    }
}

void PriorityQueue::insert(int vertex, int priority) {
    if (size == capacity) {
        throw std::overflow_error("Priority queue is full");
    }
    
    if (vertex < 0 || vertex >= capacity) {
        throw std::out_of_range("Vertex index out of range");
    }
    
    if (positions[vertex] != -1) {
        throw std::invalid_argument("Vertex already in priority queue");
    }
    
    // Add new node at the end of the heap
    heap[size].vertex = vertex;
    heap[size].priority = priority;
    positions[vertex] = size;
    
    // Fix the min heap property
    heapifyUp(size);
    size++;
}

int PriorityQueue::extractMin() {
    if (isEmpty()) {
        throw std::underflow_error("Priority queue is empty");
    }
    
    // Store the root vertex
    int minVertex = heap[0].vertex;
    
    // Replace root with last node and remove last node
    heap[0] = heap[size - 1];
    positions[heap[0].vertex] = 0;
    positions[minVertex] = -1;
    size--;
    
    // Fix the min heap property if heap is not empty
    if (size > 0) {
        heapifyDown(0);
    }
    
    return minVertex;
}

void PriorityQueue::decreaseKey(int vertex, int priority) {
    if (vertex < 0 || vertex >= capacity) {
        throw std::out_of_range("Vertex index out of range");
    }
    
    int index = positions[vertex];
    if (index == -1) {
        throw std::invalid_argument("Vertex not in priority queue");
    }
    
    // Only allow priority decrease
    if (priority > heap[index].priority) {
        return;
    }
    
    heap[index].priority = priority;
    heapifyUp(index);
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

bool PriorityQueue::contains(int vertex) const {
    if (vertex < 0 || vertex >= capacity) {
        return false;
    }
    return positions[vertex] != -1;
}

} // namespace graph
