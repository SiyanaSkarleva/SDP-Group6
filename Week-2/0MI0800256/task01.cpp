#include <iostream>
using namespace std;
#include "task01.h"

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
bool RStack<T>::full() const {
    return topIndex == capacity - 1;
}

template <typename T>
void RStack<T>::eraseStack() {
    delete[] elements;
}

template <typename T>
void RStack<T>::copyElements(T const* stackElements) {
    elements = new T[capacity];
    for (unsigned i = 0; i < capacity; i++) {
        elements[i] = stackElements[i];
    }
}

template <typename T>
void RStack<T>::copyStack(RStack const& stack) {
    topIndex = stack.topIndex;
    capacity = stack.capacity;
    copyElements(stack.elements);
}

template <typename T>
void RStack<T>::resize() {
    T* oldStackPtr = elements;
    elements = new T[2 * capacity];
    for (unsigned i = 0; i < capacity; i++) {
        elements[i] = oldStackPtr[i];
    }
    capacity *= 2;        
    delete[] oldStackPtr; 
}

template <typename T>
RStack<T>::RStack() : topIndex(-1), capacity(INITIAL_CAPACITY) {
    elements = new T[capacity];
}

template <typename T>
RStack<T>::RStack(RStack<T> const& stack) {
    copyStack(stack);
}

template <typename T>
RStack<T>& RStack<T>::operator=(RStack<T> const& stack) {
    if (this != &stack) {
        eraseStack();
        copyStack(stack);
    }
    return *this;
}

template <typename T>
RStack<T>::~RStack() {
    eraseStack();
}

template <typename T>
RStack<T>::RStack(RStack&& other) {
    topIndex = other.topIndex;
    capacity = other.capacity;

    elements = other.elements;
    other.elements = nullptr;
}

template <typename T>
RStack<T>& RStack<T>::operator=(RStack<T>&& other) {
    if (this != &other) {
        topIndex = other.topIndex;
        capacity = other.capacity;

        eraseStack();
        elements = other.elements;
        other.elements = nullptr;
    }

    return *this;
}

template <typename T>
bool RStack<T>::empty() const {
    return topIndex == -1;
}

template <typename T>
void RStack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("You can not delete the top element of an empty stack!");
    }

    topIndex--;
}

template <typename T>
T RStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return elements[topIndex];
}

template <typename T>
void RStack<T>::push(T const& x) {
    if (full()) {
        resize();
    }
    elements[++topIndex] = x;
}

bool RStack<char>::isOpeningBracket(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

bool RStack<char>::isMatchingClosingBracket(char open, char close) {
    return (open == '(' && close == ')') || (open == '{' && close == '}') || (open == '[' && close == ']');
}

bool RStack<char>::isBalanced(const char* arr) {
    RStack<char> stack;
    unsigned size = strlen(arr);

        for (int i = 0; i < size; i++) {
            if (isOpeningBracket(arr[i])) {
                stack.push(arr[i]);
            } else {
                if (!isMatchingClosingBracket(stack.top(), arr[i])) {
                    return false;
                }

                stack.pop();
            }
        }
        return stack.empty();
}

int main()
{
    
}
