#ifndef stack_hpp
#define stack_hpp

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <iostream>

template <class T>
class Stack {
public:
    Stack() = default;
    
    explicit Stack(int new_initial_size) {
        if (new_initial_size <= 0) {
            throw std::invalid_argument("Size of stack must be greater than 0.");
        }
        
        current_size = new_initial_size;
        initialize_custom_size_stack();
    }
    
    ~Stack() {
        delete [] stack;
    }
    
    int size() const {
        return filled_to;
    }
    
    T pop(){
        if (filled_to <= 0) {
            throw std::out_of_range("Stack is empty");
        }
        
        filled_to--;
        return stack[top_position--];
    }
    
    void push(T item) {
        if (filled_to + 1 >= current_size) {
            resize_stack();
        }
        
        filled_to++;
        stack[++top_position] = item;
    }
    
    T peek() {
        return stack[top_position];
    }
    
    int search(T value) {
        int pos = -1;
        
        for (int i = size() - 1; i >= 0; i--) {
            if (stack[i] == value) return i;
        }
        
        return pos;
    }
    
    bool empty() const {
        return filled_to == 0;
    }
    
    std::string to_string() const {
        std::string out = "{";
        
        for (int i = size() - 1; i >= 0; i--) {
            out += " ";
            
            // Works only for types that have implemented std::to_string()
            // Better way would be to leave it out, or implement iterator
            out += std::to_string(stack[i]);
            
            if (i) {
                out += ", ";
            } else {
                out += " }";
            }
        }
        
        return out;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Stack &s) {
        return os << s.to_string();
    }
    
private:
    constexpr static size_t initial_size = 10;
    size_t current_size = initial_size;
    int top_position = -1;
    int filled_to = 0;
    
    T* stack = new T[initial_size];
    
    void resize_stack() {
        size_t new_size = current_size + 10;
        T* new_array = new T[new_size];
        
        memcpy(new_array, stack, new_size * sizeof(T));
        
        current_size = new_size;
        delete [] stack;
        stack = new_array;
    }
    
    void initialize_custom_size_stack() {
        size_t new_size = current_size;
        T* new_array = new T[new_size];
        
        memcpy(new_array, stack, new_size * sizeof(T));
        
        current_size = new_size;
        delete [] stack;
        stack = new_array;
    }
};

#endif /* stack_hpp */
