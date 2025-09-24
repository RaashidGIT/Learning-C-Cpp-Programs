/*
   AIM: Program to calculate the hypotenuse of a right-angled triangle
        using the Pythagoras Theorem.
        Formula: c = √(a² + b²)
*/

#include <iostream>
#include <cmath>   // For sqrt() and pow() functions

int main() 
{
    // Declare variables for the two sides and hypotenuse
    double a;  
    double b;  
    double c;  

    // Input side A
    std::cout << "Enter side A: ";
    std::cin >> a;

    // Input side B
    std::cout << "Enter side B: ";
    std::cin >> b;

    // Calculate the hypotenuse using Pythagoras theorem
    c = sqrt(pow(a, 2) + pow(b, 2));

    // Display the result
    std::cout << "The length of side C (hypotenuse) is: " << c << std::endl;

    return 0;
}
