#include <thread>
#include <iostream>

#include "libraries/Stack.h"

using std::cin;
using std::cout;
using std::thread;

unsigned __stdcall in(Stack<int> *stack) {
    for (int i = 0; i < 5000; ++i) {
        stack->push(i);
    }

    return 0;
}

unsigned __stdcall out(Stack<int> *stack) {
    for (int i = 0; i < 5000; ++i) {
        if(!stack->is_empty()) {
            cout << stack->pop() << "\n";
        }
    }

    return 0;
}

int main() {
    const int numOfInThreads = 3;
    const int numOfOutThreads = 2;

    thread threads[numOfInThreads + numOfOutThreads];

    Stack<int> stack;

    for (int i = 0; i < numOfInThreads; ++i) {
        threads[i] = thread(&in, &stack);
    }

    for (int i = numOfInThreads; i < numOfInThreads + numOfOutThreads; ++i) {
        threads[i] = thread(&out, &stack);
    }

    for (int i = 0; i < numOfInThreads + numOfOutThreads; ++i) {
        threads[i].join();
    }

    return 0;
}
