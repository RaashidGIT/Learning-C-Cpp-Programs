/*
   AIM: Program to check if a person is eligible to access the site 
        based on their age.

   CONDITIONS:
   - If age >= 18 → Person is allowed to enter.
   - If age < 0  → Invalid input (not born yet).
   - Else (0 <= age < 18) → Person is too young to enter.
*/

#include <iostream>

int main() 
{
    int age;  // Variable to store the user's age

    // Ask user for their age
    std::cout << "Enter your age: ";
    std::cin >> age;

    // Check age conditions
    if(age >= 18) {
        std::cout << "Welcome to the site!" << std::endl;
    }
    else if(age < 0) {
        std::cout << "You haven't been born yet!" << std::endl;
    }
    else {
        std::cout << "You are not old enough to enter!" << std::endl;
    }

    return 0; // End of program
}
