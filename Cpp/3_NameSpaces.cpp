/*
=========================================
 AIM: Program to demonstrate the use of 
      namespaces in C++.
=========================================
*/

#include <iostream>

// ===============================
// Defining namespaces
// ===============================
namespace first {
    int x = 1;   // Variable x inside namespace 'first'
}

namespace second {
    int x = 2;   // Variable x inside namespace 'second'
}

int main() {
    // Local variable 'x'
    int x = 0;

    // ===============================
    // OUTPUT
    // ===============================
    // Here, we print:
    // 1) Local variable x (inside main)
    // 2) Variable x from 'first' namespace
    // 3) Variable x from 'second' namespace
    // ===============================
    std::cout << "Local x: " << x << std::endl;
    std::cout << "Namespace first::x: " << first::x << std::endl;
    std::cout << "Namespace second::x: " << second::x << std::endl;

    return 0;   // End of program
}
