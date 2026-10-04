// ============================================================
// Pattern 9: Diamond of Stars (Pyramid + Inverted Pyramid)
// Print the Pattern 7 pyramid on top, then the Pattern 8 inverted pyramid below it
// Logic: 1st outer loop = upper half (n - i spaces, 2i - 1 stars)
//        2nd outer loop = lower half (i - 1 spaces, 2(n - i) + 1 stars)
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {                   // upper half
            for (int j = 1; j <= n - i; j++) {           // spaces = n - i
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++) {       // stars = 2i - 1
                cout << "*";
            }
            cout << endl;
        }
        for (int i = 1; i <= n; i++) {                   // lower half
            for (int j = 1; j <= i - 1; j++) {           // spaces = i - 1
                cout << " ";
            }
            for (int j = 1; j <= 2 * (n - i) + 1; j++) { // stars = 2(n - i) + 1
                cout << "*";
            }
            cout << endl;
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             print(" " * (n - i) + "*" * (2 * i - 1))
//         for i in range(1, n + 1):
//             print(" " * (i - 1) + "*" * (2 * (n - i) + 1))

// ---------- OUTPUT ----------
// n = 4          n = 2
//    *            *
//   ***          ***
//  *****         ***
// *******         *
// *******
//  *****
//   ***
//    *