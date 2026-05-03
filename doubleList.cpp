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
        bool removePos(int pos);
        bool removePosRec(int pos, Node* curr);
        bool operator==(ListDL& other) const;
        bool equalRec(Node* list1, Node* list2) const;
    
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
bool ListDL::removePos(int pos) {
    Node* curr = this->head;
    while(curr && pos) {
        pos--;
        curr = curr->next;
    }

    if(!curr) return false;
    if(curr == this->head) {
        this->head = curr->next;
        if(this->head)
            this->head->prev = nullptr;
    }
    else {
        curr->prev->next = curr->next;
        if(curr->next != nullptr)
            curr->next->prev = curr->prev;
    }
    delete curr;
    return true;
}

bool ListDL::removePosRec(int pos, Node* curr) {
    if(!curr) return false;
    if(pos == 0) {
        if(curr->prev == nullptr) {
            this->head = curr->next;
            if(this->head)
                this->head->prev = nullptr;
        }
        else { 
            curr->prev->next = curr->next;
            if(curr->next) 
                curr->next->prev = curr->prev;
        }
        delete curr;
        return true;
    }
    return removePosRec(pos-1, curr->next);
}

bool ListDL::operator==(ListDL& other) const {
    Node* current = this->head;
    Node* otherH = other.head;
    while(current || otherH) {
        if(!current) return false;
        if(!otherH) return false;
        if(current->info != otherH->info) return false;
        current = current->next;
        otherH = otherH->next;
    }
    return true;
    /*
    Ricorsivamente si poteva chiamare
    return this->equalRec(this->head, other.head);
    */
}

bool ListDL::equalRec(Node* list1, Node* list2) const {
    if(!list1 && !list2) return true;
    if(!list1 || !list2) return false;
    if(list1->info == list2->info) return equalRec(list1->next, list2->next);
    else return false;
}