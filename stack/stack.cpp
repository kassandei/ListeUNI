#include <cassert>
//#include "stack.hpp"
#include "stackUnique.hpp"
struct Stack::Impl {
    int info;
    Impl* next;
};

// nel file adesso con Impl devo cambiare tutto da Impl a Impl
Stack::Stack() {
    pimpl = nullptr;
}

Stack::Stack(const Stack& s) {
    pimpl = nullptr;
    Impl* pc = s.pimpl;
    Impl* curr = pimpl;
    while(pc) {
        if(curr) {
            curr->next = new Impl;
            curr = curr->next;
            curr->info = pc->info;
            //curr->next = nullptr;
        }
        else {
            pimpl = new Impl;
            //pimpl->next = nullptr;
            pimpl->info = pc->info;
            curr = pimpl;
        }
        pc = pc->next;
    }

    if(curr != nullptr) {
        curr->next = nullptr; // perche??
    }
}

Stack::~Stack() {
    while(pimpl) {
        Impl* tmp = pimpl;
        pimpl = pimpl->next;
        delete tmp;
    }
}

int Stack::top() const { 
    assert(pimpl!=nullptr); 
    return pimpl->info;
}

void Stack::push(int n) {
    Impl* nodo = new Impl{n, pimpl};
    pimpl = nodo;
}

void Stack::pop() {
    assert(pimpl!=nullptr);
    Impl* tmp = pimpl;
    pimpl = pimpl->next;
    delete tmp;
}

bool Stack::is_empty() const {
    return pimpl == nullptr;
}
