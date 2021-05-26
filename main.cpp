#include<atomic>
#include <thread>
#include <iostream>
#include <fstream>

#include "libraries/Stack.h"
#include "libraries/helpers.h"

using std::ref;
using std::cin;
using std::cout;
using std::thread;
using std::string;
using std::ifstream;
using std::to_string;

volatile int consoleLock = false;
volatile int outLock = false;

unsigned __stdcall in(Stack<int> *stack, int &size, const int index) {
    string output = "P" + to_string(index) + " -> ";
    int temp;

    while (InterlockedDecrement(&size) >= 0) {
        temp = randInt(1, 100);
        stack->push(temp);
        output += to_string(temp) + " ";
    }

    while (InterlockedExchange(&consoleLock, true)) Sleep(0);
    cout << output << "\n";
    InterlockedExchange(&consoleLock, false);

    return 0;
}

unsigned __stdcall out(Stack<int> *stack, int &size, const int index) {
    string output = "С" + to_string(index) + " -> ";
    int temp;

    while (size > 0) {
        while (InterlockedExchange(&outLock, true) && !stack->isEmpty()) {
            temp = stack->pop();
            InterlockedExchange(&outLock, false);
            output += to_string(temp) + " ";
            InterlockedDecrement(&size);
        }
        InterlockedExchange(&outLock, false);
    }

    while (InterlockedExchange(&consoleLock, true)) Sleep(0);
    cout << output << "\n";
    InterlockedExchange(&consoleLock, false);

    return 0;
}

int main() {
    srand(time(NULL));

    Stack<int> stack;
    const int numOfInThreads = 3;
    const int numOfOutThreads = 2;

    for (int step = 0; step < 10; ++step) {
        int sizeIn = 50 * numOfInThreads;
        int sizeOut = sizeIn;

        thread threads[numOfInThreads + numOfOutThreads];

        for (int i = 0; i < numOfInThreads; ++i) {
            threads[i] = thread(&in, &stack, ref(sizeIn), i);
        }

        for (int i = numOfInThreads; i < numOfInThreads + numOfOutThreads; ++i) {
            threads[i] = thread(&out, &stack, ref(sizeOut), i - numOfInThreads);
        }

        for (int i = 0; i < numOfInThreads + numOfOutThreads; ++i) {
            threads[i].join();
        }
        cout << "---\n";
    }

    return 0;
}
