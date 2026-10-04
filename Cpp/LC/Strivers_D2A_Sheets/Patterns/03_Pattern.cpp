// ============================================================
// Pattern 3: Right-Angled Triangle of Numbers
// Print a triangle where row i (1 to n) prints numbers 1 to i
// Logic: outer loop = rows, inner loop prints j from 1 to i (the column number)
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {      // rows
            for (int j = 1; j <= i; j++) {  // print column number j
                cout << j;
            }
            cout << endl;                   // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             for j in range(1, i + 1):
//                 print(j, end="")
//             print()

// ---------- OUTPUT ----------
// n = 4          n = 2
// 1              1
// 12             12
// 123
// 1234
