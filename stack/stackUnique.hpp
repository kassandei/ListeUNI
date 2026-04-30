
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
        struct Impl; // sto dicendo solo che esiste dichiarazione non definizione
        Impl* pimpl; // idioma pimpl, la parte privata della classe e un puntatore
                    // a una struttura imp 
                    // dato che e un puntatore ha sempre dimensione uguale
                    // per vedere cosa c'e dentro Impl vedo stack.cpp
};

