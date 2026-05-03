#include <iostream>

using namespace std;
struct Node {
    int info;
    Node* next;
    Node* prev; // grazie a prev possiamo sapere il nodo prima del nostro
};


class ListDL {
    public: 
        ListDL();
        ListDL(const ListDL&);
        void prepend(int n);
        void append(int n);
        void print() const;
        int& at(int pos);
        const int& at(int pos) const;
        void remove(int pos);
        int sommaPari(Node* curr) const;
    
    private:
        void remove_rec(Node* head, Node* tail, int n);
        Node* head;
        Node* tail; // grazie alla coda possiamo andare direttamente alla fine
};

ListDL::ListDL() {
    this->head = nullptr;
    this->tail = nullptr;
}

void ListDL::prepend(int e) {
    Node* pc = new Node{e, nullptr, head};
    if(head == nullptr) { // se head e nullptr la lista e vuota
        this->head = pc;
        this->tail = pc;
    } 
    else {
        this->head->prev = pc;
        this->head = pc;
    }
}

void ListDL::append(int e) {
    Node* pc = new Node{e, tail, nullptr};
    if(tail == nullptr) {
        this->head = pc;
        this->tail = pc;
    }
    else {
        tail->next = pc;
        tail = pc;
    }
}

void ListDL::remove(int pos) {
    Node* pc = head;
    int i = 0;
    while(i < pos && pc != nullptr) {
        i++;
        pc = pc->next;
    }
    if(pc != nullptr) {
        if(pc->prev == nullptr) { // if(pc == head);
            head = pc->next;
            head->prev = nullptr;
        }
        else {
            pc->prev->next = pc->next;
        }
        if(pc->next == nullptr) { // if(pc == tail);
            tail = pc->prev;
        }
        else {
            pc->next->prev = pc->prev;
        }
        delete pc; 
    }
}


int ListDL::sommaPari(Node* curr) const {
    if(!curr) return 0;
    if(curr->info % 2 == 0) {
        return curr->info + sommaPari(curr->next);
    }
    else {
        return sommaPari(curr->next);
    }
}