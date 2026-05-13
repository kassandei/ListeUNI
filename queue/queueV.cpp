#include <vector>
#include <cassert>
#include "queue.hpp"
struct Queue::Impl {
    std::vector<int> v; 
    int last;
    int next;
    int elem;
};
Queue::Queue() {
    pimpl = new Impl{};
    pimpl->v.resize(100);
    pimpl->last = 0;
    pimpl->next = 0;
    pimpl->elem = 0;
}

Queue::~Queue() {
    delete pimpl;
}

void Queue::enqueue(int x) {
    /* 
    se il vettore e pieno devo allungarlo, raddoppio lo spazio e 
    riordino gli elementi
    */
    if(pimpl->elem == pimpl->v.size()) {
        int oldSize = pimpl->v.size();
        int newSize = oldSize * 2; 
        std::vector<int> newV(newSize);
        
        // riempo il nuovo vettore
        for(int i = 0; i < oldSize; i++) {
            newV.at(i) = pimpl->v.at((pimpl->last+i) % oldSize);
        }
        // uso la move semantics per spostare il vettore cosi evito la deep copy
        pimpl->v = std::move(newV);
        pimpl->next = pimpl->elem;
        pimpl->last = 0;
    }
    
    pimpl->v.at(pimpl->next) = x;
    pimpl->next = (pimpl->next+1) % pimpl->v.size();
    pimpl->elem++;
}

void Queue::dequeue() {
    if(pimpl->elem > 0) {
        pimpl->last = (pimpl->last+1) % pimpl->v.size();
        pimpl->elem--;
    }
}

int Queue::head() const {
    assert(pimpl->elem > 0);
    return pimpl->v.at(pimpl->last);
}

bool Queue::isempty() const {
    return (pimpl->elem == 0);
}

