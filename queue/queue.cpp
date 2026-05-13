#include "queue.hpp"
#include <cassert>
struct Node {
    int val;
    Node* next;
};

struct Queue::Impl {
    Node* head;
    Node* tail;
};

Queue::Queue() {
    pimpl = new Impl{};
    pimpl->head = nullptr;
    pimpl->tail = nullptr;
}

Queue::~Queue() {
    while(pimpl->head) {
        Node* tmp = pimpl->head;
        pimpl->head = pimpl->head->next;
        delete tmp;
    }
    delete pimpl;
}

Queue::Queue(const Queue& q) : Queue() {
    Node* otherHead = q.pimpl->head;
    while(otherHead) {
        Node* value = new Node{otherHead->val, nullptr};
        if(!pimpl->head) {
            pimpl->head = pimpl->tail = value;
        } 
        else {
            pimpl->tail->next = value;
            pimpl->tail = pimpl->tail->next;
        }
        otherHead = otherHead->next;
    }
}

void Queue::enqueue(int x) {
    Node* val = new Node{x, nullptr};
    if(!pimpl->head) {
        pimpl->head = pimpl->tail = val;
    }
    else {
        pimpl->tail->next = val;
        pimpl->tail = pimpl->tail->next;
    }
}

void Queue::dequeue() {
    assert(pimpl->head);    
    Node* tmp = pimpl->head;
    pimpl->head = pimpl->head->next;
    if(pimpl->head == nullptr) {
        pimpl->tail = nullptr;
    }
    delete tmp;
}

bool Queue::isempty() const {
    return pimpl->head == nullptr;
}

int& Queue::first() const {
    assert(pimpl->head);
    return pimpl->head->val;
}

int Queue::head() const {
    assert(pimpl->head);
    return pimpl->head->val;
}