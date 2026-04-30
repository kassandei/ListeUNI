#include "stackUnique.hpp"
#include <iostream>
int main() {
    Stack s;
    s.push(10);
    s.push(45);
    while(!s.is_empty()) {
        std::cout << s.top() << std::endl;
        s.pop();
    }
}