// ============================================================
// Pattern 1: Square of Stars
// Print an N x N square of '*' (n rows, each with n stars)
// Logic: outer loop = rows, inner loop = columns, newline after each row
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 0; i < n; i++) {       // rows
            for (int j = 0; j < n; j++) {   // columns
                cout << "*";
            }
            cout << endl;                   // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(n):
//             print("*" * n)

// ---------- OUTPUT ----------
// n = 4          n = 2
// ****           **
// ****           **
// ****
// ****
