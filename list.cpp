#include <iostream>
//#include <stdexpect>

using namespace std;

struct node {
    int info;  // data
    node* next; // prossimo nodo
};

class List {
    public:
        List();
        List(const List& l);
        ~List();

        void prepend(int e); // O(1) inserisci in testa
        void append(int e);  // O(n) inserisci in coda
        void print() const;


    private:
        node* head;
};

List::List() {
    head = nullptr;
}

List::List(const List& l) {
    node* pc = l.head;
    node* tail = this->head;
    while(pc) {
        node* current = new node;
        current->info = pc->info;

        if(!this->head) {
            this->head = tail = current;
        }
        else {
            tail->next = current;
            tail = tail->next;
        }
        pc = pc->next;
    }
}

List::~List() {
    while(this->head) {
        node* tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
}

void List::prepend(int e) {
   node* first = new node{e, this->head};
   this->head = first;
}

void List::append(int e) {
    if(!this->head) {
        this->prepend(e);
    }
    else {
        node* last = this->head;
        while(last->next) {
            last = last->next;
        }
        last->next = new node{e, nullptr};
    }
}

void List::print() const {
    node* current = this->head;
    while(current) {
        cout << current->info << endl;
        current = current->next;
    }
}


int main(void) {
    List a;
    a.append(10);
    a.append(15);
    a.prepend(3);
    a.print();
}
