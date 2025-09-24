/*
   AIM: Program to display a message based on the student's letter grade.

   CONDITIONS:
   - 'A' → "You did great!"
   - 'B' → "You did good"
   - 'C' → "You did okay"
   - 'D' → "You did not do good"
   - 'F' → "YOU FAILED!"
   - Any other input → "Please only enter in a letter grade (A-F)"
*/

#include <iostream>
using namespace std;

int main() 
{
    char grade;  // Variable to store the letter grade

    // Ask user for their grade
    cout << "What letter grade?: ";
    cin >> grade;

    // Switch statement checks the entered grade
    switch(grade) {
        case 'A':
            cout << "You did great!";
            break;
        case 'B':
            cout << "You did good";
            break;
        case 'C':
            cout << "You did okay";
            break;
        case 'D':
            cout << "You did not do good";
            break;
        case 'F':
            cout << "YOU FAILED!";
            break;
        default:
            cout << "Please only enter in a letter grade (A-F)";
    }

    return 0; // End of program
}
