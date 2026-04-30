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
    pimpl->v.push_back(a);
}

void Stack::pop() {
    assert(pimpl->v.size() == 0);
    pimpl->v.pop_back();
}

bool Stack::is_empty() const {
    return pimpl->v.empty();
}

int Stack::top() const {
    assert(pimpl->v.size() == 0);
    return pimpl->v.at(pimpl->v.size()-1);
}

