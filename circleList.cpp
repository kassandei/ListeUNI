#include <iostream>

using namespace std;

struct Cella {
    int info;
    Cella* next;
};

class ListCirc {
    public:
        ListCirc();
        ListCirc(const ListCirc& c);
        ~ListCirc();

        void insert(int n);
        void print() const;
        bool presente(int n);
        void elimina(int n);
        int sommaPari(Cella* curr) const;
        bool allEvenPositive(Cella* curr) const;
        bool removePos(int pos);
        bool removeRecPos(int pos, Cella*& curr);
    private: 
        Cella* l;  // no head no trail nelle liste circolari
};

ListCirc::ListCirc() {
    l = nullptr;
}

void ListCirc::print() const {
    Cella* pc = l;
    if(pc) {
        do {
            cout << pc->info << endl;
            pc = pc->next;
        } while(pc != l);
    } 
}

void ListCirc::insert(int n) {
    if(!l) l = new Cella{n, l};
    else l->next = new Cella{n, l->next};
}

bool ListCirc::presente(int n) {
    if(l == nullptr) return false; 
    else {
        bool found = false;
        Cella* pc = l;
        do {
            if(pc->info == n) found = true;
            pc = pc->next;
        } while(!found && pc != l);
        return found;
    }
}

void ListCirc::elimina(int n) {
    Cella* pc = l;
    Cella* prev = nullptr;
    bool found = false;
    if(pc) { 
        do {
            if(pc->info == n) found = true;
            else {
                prev = pc;
                pc = pc->next;
            }
        } while(pc != l && !found);
        if(found) {
            if(prev == nullptr) {
                // unico elemento presente in lista
                if(pc->next == pc) {
                    l = nullptr;
                }
                else {
                    // primo elemento da eliminare 
                    Cella* giro = l;
                    while(giro->next != l) {
                        giro = giro->next;
                    }
                    l = l->next;
                    giro->next = l;
                }
            }
            else {
                prev->next = pc->next;
            }
            delete pc; 
        } 
    }
}

int ListCirc::sommaPari(Cella* curr) const {
    /*int sum = 0;
    do {
        if(curr->info % 2 == 0) sum += curr->info;
        curr = curr->next;
    } while(curr != this->l);

    return sum;
    */
    if(curr->next == this->l) {
        if(curr->info % 2 == 0) return curr->info;
        else return 0;
    } 
    if(curr->info % 2 == 0) {
        return curr->info + sommaPari(curr->next);
    }
    else {
        return sommaPari(curr->next);
    }
}

bool ListCirc::allEvenPositive(Cella* curr) const {
    if(!curr) return true;
    bool all = true;
    do {
        if(!(curr->info >= 0 && curr->info % 2 == 0)) {
            all = false;
        }
        curr = curr->next;
    } while(all && curr != this->l);
    return all;
}

bool ListCirc::removePos(int pos) {
    Cella* curr = this->l;
    Cella* prev = nullptr;
    if(!curr) return false;
    else if(pos == 0 && curr->next == this->l) {
        this->l = nullptr;
        delete curr;
    }
    else if(pos == 0) { 
        while(curr->next != this->l) {
            curr = curr->next;
        }
        Cella* tmp = this->l;
        curr->next = this->l->next;
        this->l = this->l->next;
        delete tmp;
    } 
    else {
        while(pos && curr->next != this->l) {
            prev = curr;
            curr = curr->next;
            pos--;
        }

        if(pos > 0 || curr == this->l) return false;
        prev->next = curr->next;
        delete curr;
    }
    return true;
}

// supponiamo che abbia piu di un elemento e che il primo elemento non sia da eliminare
// serve un wrapper pubblico per gestire i casi citati
bool ListCirc::removeRecPos(int pos, Cella*& curr) {
    if(curr == this->l) return false;
    if(pos == 0) {
        Cella* tmp = curr;
        curr = curr->next;
        delete tmp;
        return true;
    }
    return removeRecPos(pos-1, curr->next);
}