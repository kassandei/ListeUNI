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
    Cella* pc = l;
    bool found = false;
    while(pc != l && found) {
       if(pc->info == n) found = true; 
    }
    return found;
}