/*
=========================================
 AIM: Program to calculate the circumference 
      of a circle using a constant (PI).
=========================================
*/

#include <iostream>   // Needed for input/output

int main() {
    // ===============================
    // CONSTANTS in C++
    // ===============================
    // A constant is a variable whose value CANNOT be changed once assigned.
    // Use 'const' before the data type to declare it.

    const double PI = 3.14159;   // Constant value of PI

    // PI = 420.69;  ❌ ERROR: You cannot change a constant once it is defined.

    // ===============================
    // Example: Calculate the circumference of a circle
    // ===============================
    double radius = 10;   // Circle radius in cm
    double circumference = 2 * PI * radius;  // Formula: 2πr

    // ===============================
    // OUTPUT
    // ===============================
    std::cout << "The circumference of the circle is: "
              << circumference << " cm" << std::endl;

    return 0;   // End of program
}
