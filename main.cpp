#include <iostream>

#include "libraries/Stack.h"

using std::cout;

int main() {
    auto stack = new Stack<int>;
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);
    stack->push(5);
    stack->push(6);
    stack->push(7);

    while (!stack->is_empty()) {
        cout << stack->pop() << " ";
    }
    return 0;
}
