#ifndef PRIORITYQUEUENODE_H
#define PRIORITYQUEUENODE_H

#include <vector>
#include "Node.h"

using namespace std;

class PriorityQueue {
private:
    vector<Node*> heap;

    int parent(int i) {
        return i / 2;
    }

    int leftChild(int i) {
        return 2 * i;
    }

    int rightChild(int i) {
        return 2 * i + 1;
    }

    void heapUp(int i) {
        while (i > 1 && heap[i] < heap[parent(i)]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapDown(int i) {
        int minIndex = i;
        int l = leftChild(i);
        int r = rightChild(i);

        if (l < heap.size() && heap[l] < heap[minIndex]) {
            minIndex = l;
        }

        if (r < heap.size() && heap[r] < heap[minIndex]) {
            minIndex = r;
        }

        if (i != minIndex) {
            swap(heap[i], heap[minIndex]);
            heapDown(minIndex);
        }
    }

public:
    PriorityQueue() {
        // Se agrega un elemento ficticio en el índice 0
        heap.push_back(new Node());
    }

    void push(Node* nodo) {
        // Se ingresa un elemento luego se llama a heapUp para reajustar la cola de prioridad
        heap.push_back(nodo);
        heapUp(heap.size() - 1);
    }

    Node* top() {
        // Se retorna la raíz
        return heap[1];
    }

    Node* pop() {
        // Se intercambia la raíz con el último elemento y se elimina el último elemento
        Node* min = heap[1];
        heap[1] = heap[heap.size() - 1];
        heap.pop_back();
        // Luego se llama heapDown para reajustar la cola de prioridad
        heapDown(1);
        return min;
    }

    bool isEmpty() {
        return heap.size() == 1;
    }

    int size() {
        return heap.size();
    }
};

#endif