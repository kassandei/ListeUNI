#include <iostream>

using namespace std;

class ListDL {
    public: 
        ListDL();
        ListDL(const ListDL&);
        void repend(int n);
        void apend(int n);
        void print() const;
        int& at(int pos);
        const int& at(int pos) const;

        void deleteNode(int pos);
    
    private:
        struct Node {
            int info;
            Node* next;
            Node* prev;
        };

        Node* head;
        Node* tail;
};