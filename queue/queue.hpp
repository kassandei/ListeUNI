class Queue {
    public:
        Queue();
        Queue(const Queue& c);
        ~Queue();
        void enqueue(int e);
        void dequeue();
        int& first() const;
        bool isempty() const;
        int head() const;

    private:
        struct Impl;
        Impl* pimpl;
};
