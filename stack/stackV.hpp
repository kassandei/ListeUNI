#include <vector>

class StackV {
    public:
        StackV();
        ~StackV();
        StackV(const StackV& s);
        void push(int n);
        void pop();
        int top() const;
        bool is_empty() const;
    private:
        std::vector<int> v;
};
