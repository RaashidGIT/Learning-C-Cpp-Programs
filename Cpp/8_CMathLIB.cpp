/*
=========================================
 AIM: Program to demonstrate common math 
      functions in C++ using <cmath>.
=========================================

 THEORY:
 - The <cmath> library provides built-in mathematical functions.
   Some commonly used ones are:

   1) max(a, b)   → returns the larger of a and b
   2) min(a, b)   → returns the smaller of a and b
   3) pow(a, b)   → returns a raised to the power b (a^b)
   4) sqrt(x)     → returns square root of x
   5) abs(x)      → returns absolute value of x
   6) round(x)    → rounds x to nearest integer
   7) ceil(x)     → rounds x UP to nearest integer
   8) floor(x)    → rounds x DOWN to nearest integer
=========================================
*/

#include <iostream>
#include <cmath>   // Required for math functions
using namespace std;

int main() 
{
    double x = 3.99;
    double y = 4;
    double z;

    // Uncomment one line at a time to test different math functions:

    // z = max(x, y);       // Maximum of x and y
    // z = min(x, y);       // Minimum of x and y
    // z = pow(2, 4);       // 2^4 = 16
    // z = sqrt(9);         // Square root of 9 = 3
    // z = abs(-3);         // Absolute value = 3
    // z = round(x);        // Round 3.99 → 4
    // z = ceil(x);         // Round UP 3.99 → 4
    // z = floor(x);        // Round DOWN 3.99 → 3

    cout << "Result = " << z << endl;

    return 0;   // End of program
}
