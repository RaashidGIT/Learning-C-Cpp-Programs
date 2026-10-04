// ============================================================
// Pattern 2: Right-Angled Triangle of Stars
// Print a triangle where row i (1 to n) has i stars
// Logic: outer loop = rows, inner loop runs j <= i (stars grow by 1 each row)
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {      // rows
            for (int j = 1; j <= i; j++) {  // stars = row number
                cout << "*";
            }
            cout << endl;                   // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             print("*" * i)

// ---------- OUTPUT ----------
// n = 4          n = 2
// *              *
// **             **
// ***
// ****
