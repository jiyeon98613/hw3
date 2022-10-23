#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
private:

};


template <typename T>
Stack<T>::Stack()
: std::vector<T>()
{}


template <typename T>
Stack<T>::~Stack()
{std::vector<T>::clear();}


template <typename T>
bool Stack<T>::empty() const
{
    return stack.std::vector<T>::empty();
    
}


template <typename T>
size_t Stack<T>::size() const
{
    return stack.std::vector<T>::size();
}


template <typename T>
void Stack<T>::push(const T& item)
{
    stack.std::vector<T>::push_back(item);
}


template <typename T>
void Stack<T>::pop()
{
    if(stack.empty()){throw std::underflow_error("The stack is empty.");}
    stack.std::vector<T>::pop_back(item);
}


template <typename T>
const T& Stack<T>::top() const
{   
    if(stack.empty()){throw std::underflow_error("The stack is empty.");}
    stack.std::vector<T>::back();
}

#endif
