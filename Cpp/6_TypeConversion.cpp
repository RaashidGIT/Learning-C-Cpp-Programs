/*
=========================================
 AIM: Program to demonstrate Type Conversion 
      (Type Casting) in C++.
=========================================

 THEORY:
 - Type conversion means converting a value of one data type into another.
 - Two types of conversions in C++:
   
   1) Implicit Conversion (Type Promotion / Automatic):
      - Done automatically by the compiler when safe.
      - Example: int → double
   
   2) Explicit Conversion (Type Casting / Manual):
      - Done by the programmer using a cast.
      - Example: (double)num  or  static_cast<double>(num)

 Example:
     int a = 5, b = 2;
     double result = (double)a / b;   // Explicit cast
=========================================
*/

#include <iostream>
using namespace std;

int main()
{
    int correct = 8;       // Number of correct answers
    int questions = 10;    // Total number of questions

    // Explicit type casting:
    // Without (double), result = 8 / 10 = 0 (integer division).
    // With (double), result = 8 / 10.0 = 0.8
    double score = correct / (double)questions * 100;

    // Output the percentage score
    cout << "Score = " << score << "%" << endl;

    return 0;   // End of program
}
