#include <iostream>
#include "stack.hpp"

int main(int argc, const char * argv[]) {
    
    Stack<int> stack (30);
    
    std::cout << std::boolalpha;
    std::cout << "Is empty: " << stack.empty() << "\n";
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(3);
    stack.push(4);
    
    std::cout << "Is empty: " << stack.empty() << "\n";
    std::cout << "Peek: " << stack.peek() << "\n";
    
    std::cout << "Pop: " << stack.pop() << "\n";
    
    std::cout << "Search: " << stack.search(2) << "\n";
    std::cout << "Search: " << stack.search(10) << "\n";
    
    for (int i = 0; i < 20; i++) {
        stack.push(i);
    }
    
    std::cout << stack << "\n";
    
    while (!stack.empty()) {
        std::cout << "Pop: " << stack.pop() << "\n";
    }
    
    return 0;
}
