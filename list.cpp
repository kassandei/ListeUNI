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
        void print_rev() const;
        bool is_present(int e) const;

        int& at(int pos);
        const int& at(int pos) const;

        void remove(int e); // rimuovi prima occorenza di e
        void remove_last(int e); // rimuovi seconda occorenza di e
        int sum() const;

    private:
        node* head;
        
        // funzioni helper
        void print_rev_rec(node* curr) const;
        bool remove_last_recv1(int e, node* prev, node* curr);
        bool remove_last_recv2(int e, node*& curr);
        int sum_rec(node* curr) const;
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

void List::print_rev() const {
    print_rev_rec(this->head);
}

void List::print_rev_rec(node* curr) const {
    if(curr) {
        print_rev_rec(curr->next);
        cout << curr->info << endl;
    }
}

bool List::is_present(int e) const {
    node* current = this->head;
    bool found = false;
    while(current && !found) {
        if(current->info == e) found = true;
        current = current->next;
    }
    return found;
}

int& List::at(int pos) {
    node* curr = this->head;
    for(int i = 0; i < pos; i++) {
        curr = curr->next;
    }
    return curr->info;
}

const int& List::at(int pos) const {
    node* curr = this->head;
    for(int i = 0; i < pos; i++) {
        curr = curr->next;
    }
    return curr->info;
}

void List::remove(int e) {
    node* current = this->head;
    node* prev = nullptr;

    while(current && current->info != e) {
        prev = current;
        current = current->next;
    }

    if(current) {
        if(!prev) {
            this->head = current->next;
        }
        else {
            prev->next = current->next;
        }
        delete current;
    }
}

void List::remove_last(int e) {
    node* current = this->head;
    node* prev = nullptr;
    node* check = nullptr;

    bool found = false;
    while(current) {
        if(current->info == e) {
            found = true;
            check = prev;
        }
        prev = current;
        current = current->next;
    }
    if(!check) {
        node* save = check->next->next;
        delete check->next;
        check->next = save;
    }
    if(found) {
        node* save = this->head->next;
        delete this->head;
        this->head = save;
    }
}
bool List::remove_last_recv1(int e, node* prev, node* current) {
    if(current == nullptr)
        return false;
    bool removed = remove_last_recv1(e, current, current->next);
    if(!removed && current->info == e) {
        if(prev == nullptr) this->head = current->next;
        else prev->next = current->next;
        delete current;
        return true;
    }
    return removed;
}

bool List::remove_last_recv2(int e, node*& current) {
    if(current == nullptr) return false;
    bool removed = remove_last_recv2(e, current->next);

    if(!removed && current->info == e) {
        node* cp = current;
        current = current->next;
        delete cp;
        return true;
    }
    return removed;
}

int List::sum() const {
    return sum_rec(this->head);
}

int List::sum_rec(node* current) const {
    if(current == nullptr) return 0;
    return current->info + sum_rec(current->next);
}


int main(void) {
    List a;
    a.append(10);
    a.append(15);
    a.prepend(3);
    a.print();
}
