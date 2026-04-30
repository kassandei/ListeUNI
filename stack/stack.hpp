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
        struct Cella {
            int info;
            Cella* next;
        };
        Cella* head;
};

