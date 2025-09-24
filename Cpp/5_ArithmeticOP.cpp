/*
=========================================
 AIM: Program to demonstrate arithmetic 
      operators in C++.
=========================================

 THEORY:
 - Arithmetic operators are used to perform basic math operations.
   1) Addition (+)
   2) Subtraction (-)
   3) Multiplication (*)
   4) Division (/)
   5) Modulus (%) → gives remainder after division

 - We can also use:
   - Compound assignment operators (+=, -=, *=, /=, %=)
   - Increment (++) and Decrement (--) operators

=========================================
*/

#include <iostream>
using namespace std;

int main() 
{
    int students = 20;   // Initial number of students

    // ------------------
    // Addition examples
    // ------------------
    //students = students + 1;   // Method 1
    //students += 1;             // Method 2 (compound assignment)
    //students++;                // Method 3 (increment operator)

    // ------------------
    // Subtraction examples
    // ------------------
    //students = students - 1;   // Method 1
    //students -= 1;             // Method 2 (compound assignment)
    //students--;                // Method 3 (decrement operator)

    // ------------------
    // Multiplication examples
    // ------------------
    //students = students * 2;   // Method 1
    //students *= 2;             // Method 2

    // ------------------
    // Division examples
    // ------------------
    //students = students / 2;   // Method 1
    //students /= 2;             // Method 2

    // ------------------
    // Modulus example
    // ------------------
    //int remainder = students % 3;
    //cout << "Remainder: " << remainder << endl;

    // ------------------
    // Final Output
    // ------------------
    cout << "Students = " << students << endl;

    return 0;
}
