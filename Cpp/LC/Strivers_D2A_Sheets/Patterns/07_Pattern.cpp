// ============================================================
// Pattern 7: Pyramid of Stars
// Print a centered pyramid where row i (1 to n) has (n - i) spaces, then (2i - 1) stars
// Logic: outer loop = rows, 1st inner loop prints spaces, 2nd inner loop prints stars
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {              // rows
            for (int j = 1; j <= n - i; j++) {      // spaces = n - i
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++) {  // stars = 2i - 1
                cout << "*";
            }
            cout << endl;                           // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             print(" " * (n - i) + "*" * (2 * i - 1))

// ---------- OUTPUT ----------
// n = 4          n = 2
//    *            *
//   ***          ***
//  *****
// *******
