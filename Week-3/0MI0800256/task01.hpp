#ifndef _RESIZABLE_STACK_HPP
#define _RESIZABLE_STACK_HPP

#include <iostream>

template <typename T>
class RStack {
private:
    T* elements;
    int topIndex;                  
    int capacity;                 

    bool full() const;            
    void resize();                 
    void eraseStack();             
    void copyElements(T const* other);   
    void copyStack(RStack const& other); 

public:
    RStack();
    RStack(const RStack& other);
    RStack& operator=(const RStack& other);
    ~RStack();

    // Move семантики
    RStack(RStack&& other);
    RStack& operator=(RStack&& other);

    bool empty() const;
    void push(T const& x);
    void pop();
    T top() const;
};

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
RStack<T>::RStack(const RStack<T>& stack) {
    copyStack(stack);
}

template <typename T>
RStack<T>& RStack<T>::operator=(const RStack<T>& stack) {
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

template <typename T>
class Queue {
private:
    RStack<T> reversed; //reversed
    RStack<T> ordered; //ordered

    void transfer(RStack<T>& source, RStack<T>& destination) {
        while (!source.empty()){
            destination.push(source.top());
            source.pop();
        }
    }

public:
    bool empty() const;
    void push(T const& x);
    void pop();
    T head() const;
};

template <typename T>
bool Queue<T>::empty() const {
    return reversed.empty() && ordered.empty();
}

template <typename T>
void Queue<T>::push(T const& x) {
    this->transfer(ordered, reversed);
    this->reversed.push(x);
}

template <typename T>
void Queue<T>::pop() {
    this->transfer(reversed, ordered);
    this->ordered.pop();
}

template <typename T>
T Queue<T>::head() const {
    this->transfer(reversed, ordered);
    return this->ordered.top();
}
#endif
