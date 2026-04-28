#include <iostream>



class Stack {
    public:
        Stack();
        ~Stack();
        Stack(const Stack& s);
        void push(int n);
        void pop();
        int top() const;
        bool is_empty() const;
    private:
        // implementazione a cella e a vector
        struct Cella {
            int info;
            Cella* next;
        };
        Cella* head;
        /*
        vector<int> v;
        */
};


/*
Esercizi:
1) Completare la classe Stack con le liste
2) Data una lista semplice, eliminare l'ultima sequenza contigua di numeri pari !SEQUENZA
3) */

