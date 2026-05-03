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
        int& at_rec(int pos, node* curr);

        void remove(int e); // rimuovi prima occorenza di e
        void remove_last(int e); // rimuovi seconda occorenza di e
        int sum() const;
        void remove_all(int e);
        void remove_up_to_sum(int e);
        void flip();
        void double_even();
        bool equal(const List& curr) const;
        bool countfrom0(int& count) const;    // count elements after the last 0
        bool operator==(const List& other) const;  // element-wise equality
        List   operator+ (const List& other) const;  // concatenation (new list)
        List&  operator= (const List& other);         // copy-assignment (copy-and-swap)
        bool eliminaSeqPari(node*& curr); 
        void swap();
        int sommaPari(node*& curr) const;
        node* getHead(); 
        bool allEvenPositive(node* curr) const;
        bool removePos(int pos);

        bool removeRecPos(int pos, node*& curr); 
        int removeUpToSum(int sum);
        int removeUpToSumRec(int sum, node*& curr);
        int removeFromTail(int sum);
        int removeFromTailRec(int& sum, node*& curr);
        int duplOdd();
        int duplOddRic(node*& curr);
        void removeCons();
        void removeConsRec(node*& curr);

    private:
        node* head;
         
        // funzioni helper
        void print_rev_rec(node* curr) const;
        bool remove_last_recv1(int e, node* prev, node* curr);
        bool remove_last_recv2(int e, node*& curr);
        int sum_rec(node* curr) const;
        int remove_up_to_sum_rec(node*& curr, int e);
        void flip_rec(node*& curr);
        void double_even_rec(node*& curr);
        bool equal    (node* head, node* head_other)  const;  // iterative equality
        bool equal_rec(node* curr, node* curr_other)  const;  // recursive equality
        bool countfrom0_rec  (node* curr, int& count) const;
        void swap_rec(node*& l);
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

// assumi range corretto
int& List::at(int pos) {
    node* curr = this->head;
    for(int i = 0; i < pos && curr; i++) {
        curr = curr->next;
    }
    //assert(pc!=nullptr);
    return curr->info;
}

//
int& List::at_rec(int pos, node* h) {
    //assert(h != nullptr);
    if(pos == 0) return h->info;
    return at_rec(pos-1, h->next);
}


// assumi range corretto
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

void List::remove_all(int e) {
    node** current = &head;
    while(*current) {
        if((*current)->info == e) {
            node* tmp = (*current);
            *current = tmp->next;
            delete tmp;
        }
        else 
            current = &(*current)->next;
    }
}

void List::remove_up_to_sum(int e) {
    remove_up_to_sum_rec(head, e);
}

int List::remove_up_to_sum_rec(node*& curr, int e) {
    if(!curr) return 0;
    int rightSum = remove_up_to_sum_rec(curr->next, e);
    int sum = rightSum + curr->info;
    if(sum <= e) {
        node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    return sum;
}

void List::flip() {
    node* current = head;
    node* prev = nullptr;
    node* tmp = nullptr;
    while(current) {
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
    }
    head = current;
}

void List::flip_rec(node*& current) {
    if(!current || !current->next) return;
    node* tmp = current;
    node* tmp2 = current->next;
    flip_rec(current->next);
    node* nuova = current->next;
    tmp2->next = tmp;
    tmp = nullptr;
    current = nuova;
}

void List::double_even() {
    node* curr = head;
    while(curr) {
        node* next = curr->next;
        if(curr->info % 2 == 0) {
            node* tmp = new node{curr->info, next};
            curr->next = tmp;
        }
        curr = next;
    }
}

void List::double_even_rec(node*& curr) {
    if(!curr) return;
    node* next = curr->next;
    if(curr->info % 2 == 0) {
        node* tmp = new node{curr->info, next};
        curr->next = tmp;
    }
    return double_even_rec(next);
}

bool List::equal(const List& curr) const {
    if(this->head == curr.head) return true;
    else return equal_rec(this->head, curr.head);
}

bool List::equal_rec(node* curr, node* curr_other) const {
    if(!curr && !curr_other) return true;
    if(!curr || !curr_other) return false;
    if(curr->info == curr_other->info) return equal_rec(curr->next, curr_other->next);
    else return false;
}

bool List::equal(node* curr, node* curr_other) const {
    while(curr || curr_other) {
        if(!curr) return false;
        if(!curr_other) return false;
        if(curr->info == curr_other->info) {
            curr = curr->next;
            curr_other = curr_other->next;
        }
        else return false;
    } 
    return true;
}

bool List::countfrom0(int& counter) const {
    node* current = this->head;
    bool found = false;
    while(current) {
        if(current->info == 0) {
            found = true;
            counter = 0;
        } else {
            counter++;
        }
        current = current->next;
    }
    return found;
}

bool List::countfrom0_rec(node* curr, int& counter) const {
    if(!curr) return false;

    if(curr->info == 0) {
        counter = 0;
        countfrom0_rec(curr->next, counter);
        return true;
    } 
    else {
        counter++;
        return countfrom0_rec(curr->next, counter);
    }
}

bool List::operator==(const List& other) const {
    return this->equal(other);
}
List List::operator+(const List& other) const {
    List tmp;
    node** current = &(tmp.head);
    node* firstL = this->head;
    node* secondL = other.head;

    while(firstL) {
        node* newNode = new node{firstL->info, nullptr};
        *current = newNode;
        firstL = firstL->next;
        current = &(*current)->next; 
    }
    while(secondL) {
        node* newNode = new node{secondL->info, nullptr};
        *current = newNode;
        secondL = secondL->next;
        current = &(*current)->next;
    }
    return tmp;
}
List& List::operator=(const List& other) {
    if(this->head != other.head) {
        node* elimina = this->head;
        node* current = other.head;
        while(elimina) {
            node* tmp = elimina;
            elimina = elimina->next; 
            delete tmp;
        }
        this->head = nullptr; 
        node** dlt = &(this->head); 
        while(current) {
            node* newNode = new node{current->info, nullptr};
            *dlt = newNode;
            current = current->next;
            dlt = &(*dlt)->next;
        }
    }
    return *this;
}        

void List::swap() {
    swap_rec(head);
}

void List::swap_rec(node*& curr) {
    if(!curr || !curr->next) {
        return;
    }
    node* tmp = curr;
    curr = curr->next;
    node* tmp2 = curr->next;
    curr->next = tmp;
    tmp->next = tmp2;
}


int List::sommaPari(node*& curr) const {
    if(!curr) return 0;
    if(curr->info % 2 == 0) {
        return curr->info + sommaPari(curr->next);
    }
    else {
        return sommaPari(curr->next);
    }
}

node* List::getHead() {
    return this->head;
}


bool List::allEvenPositive(node* curr) const {
    if(!curr) return true;
    if( !(curr->info >= 0 && curr->info % 2 == 0) )
        return false;
    return allEvenPositive(curr->next);
}


bool List::removePos(int pos) {
    node* curr = this->head;
    node* prev = nullptr;
    while(curr && pos) {
        prev = curr;
        curr = curr->next;
        pos--;
    }

    if(!curr)
        return false;

    if(curr == this->head) {
        this->head = curr->next;
    }
    else 
        prev->next = curr->next;

    delete curr;
    return true;
}

bool List::removeRecPos(int pos, node*& curr) {
    if(!curr) return false;
    if(pos == 0) {
        node* tmp = curr;
        curr = curr->next;
        delete tmp;
        return true;
    }
    return removeRecPos(pos-1, curr->next);
}

int List::removeUpToSum(int sum) {
    node* curr = this->head;
    int count = 0;
    while(curr) {
        if(sum - curr->info < 0) break;
        node* tmp = curr;
        sum -= curr->info;
        curr = curr->next;
        count++;
        delete tmp;
    }

    this->head = curr;
    return count;
}

int List::removeUpToSumRec(int sum, node*& curr) {
    if(!curr) return 0;
    if(sum - curr->info < 0) {
        return 0;
    } 
    int val = curr->info; 
    node* tmp = curr;
    curr = curr->next;
    delete tmp;

    return 1 + removeUpToSumRec(sum - val, curr);
}
int List::removeFromTail(int sum) {
    int deleteUp = sum;
    int fromend = 0;
    while(deleteUp && this->head) {
        node* curr = this->head;
        node* prev = nullptr;
        while(curr->next) {
            prev = curr;
            curr = curr->next;
        }
        if(deleteUp - curr->info >= 0) {
            if(prev == nullptr) {
                this->head = nullptr;
            }
            else prev->next = curr->next;
            fromend += curr->info;
            deleteUp -= curr->info;
            delete curr;
        }
        else {
            break;
        }
    } 
    return fromend;
}

int List::removeFromTailRec(int& sum, node*& curr) {
    if(!curr) return 0;
    int fromend = removeFromTailRec(sum, curr->next);
    int tmp = 0;
    if(sum - curr->info >= 0) {
        sum -= curr->info;
        tmp = curr->info;
        delete curr;
        curr = nullptr;
    }
    return fromend + tmp;
}

int List::duplOdd() {
    node* curr = this->head;
    int count = 0;
    while(curr) {
        if(curr->info % 2 != 0) {
            node* nuovo = new node{curr->info, curr->next};
            curr->next = nuovo;
            curr = nuovo->next;
            count++;
        }
        else {
            curr = curr->next;
        }
    }
    return count;
}
int List::duplOddRic(node*& curr) {
    if(!curr) return 0;
    if(curr->info % 2 != 0) {
        node* nuovo = new node{curr->info, curr->next};
        curr->next = nuovo;
        return 1 + duplOddRic(nuovo->next);
    }
    else 
        return duplOddRic(curr->next);
}

void List::removeCons() {
    node* curr = this->head;
    while(curr && curr->next) {
        if(curr->info == curr->next->info) {
            node* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp;
        }
        else
            curr = curr->next;
    }
}

void List::removeConsRec(node*& curr) {
    if(!curr || !curr->next) return;
    if(curr->info == curr->next->info) {
        node* tmp = curr->next;
        curr->next = curr->next->next;
        delete tmp;
        removeConsRec(curr);
    }
    else 
        removeConsRec(curr->next);
}


int main(void) {
    List a;
    a.append(10);
    a.append(12);
    a.prepend(2);
    a.print();
    node* head = a.getHead();
    int b = a.sommaPari(head);
    std::cout << b;
}
