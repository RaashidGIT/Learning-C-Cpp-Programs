/*
=========================================
 AIM: Program to demonstrate the use of 
      typedef and using (type aliases) in C++.
=========================================

 THEORY:
 - A type alias gives an alternative name to an existing data type.
 - In C++, we can create type aliases in two ways:
   1) Using 'typedef' (older way).
   2) Using 'using' (modern way, C++11 and later).

 Example:
     typedef std::string text_t;
     using text_t = std::string;

 Both lines mean: text_t can now be used instead of std::string.
=========================================
*/

#include <iostream>
#include <string>

// Older method (typedef):
// typedef std::string text_t;
// typedef int number_t;

// Modern method (using):
using text_t = std::string;
using number_t = int;

int main() {
    // ===============================
    // Declaring variables with aliases
    // ===============================
    text_t firstName = "Bro";   // Equivalent to std::string firstName
    number_t age = 21;          // Equivalent to int age

    // ===============================
    // OUTPUT
    // ===============================
    std::cout << "Name: " << firstName << '\n';
    std::cout << "Age: " << age << '\n';

    return 0;   // End of program
}
