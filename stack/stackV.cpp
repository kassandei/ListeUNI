#include <cassert>
#include <vector>
#include <stackUnique.hpp>

struct Stack::Impl {
    std::vector<int> v;
};

Stack::Stack() {
   pimpl = new Impl; 
}

Stack::~Stack() {

}

Stack::Stack(const Stack& s) {
    pimpl = new Impl;
    pimpl->v = (s.pimpl)->v;
}

void Stack::push(int a) {
    v.push_back(a);
}

void Stack::pop() {
    assert(v.size() == 0);
    v.pop_back();
}

bool Stack::is_empty() const {
    return v.empty();
}

int Stack::top() const {
    assert(v.size() == 0);
    return v.at(v.size()-1);
}

