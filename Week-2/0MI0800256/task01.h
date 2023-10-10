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
    void copyElements(T const*);   
    void copyStack(RStack const&); 

public:
    RStack();
    RStack(RStack const&);
    RStack& operator=(RStack const&);
    ~RStack();

    RStack(RStack&&);
    RStack& operator=(RStack&&);

    bool empty() const;
    void push(T const& x);
    void pop();
    T top() const;

    bool isOpeningBracket(char ch);
    bool isMatchingClosingBracket(char open, char close);
    bool isBalanced(const char* arr);
};

#endif
