// ============================================================
// Pattern 6: Inverted Right-Angled Triangle of Numbers
// Print a triangle where row i (1 to n) prints numbers 1 to (n - i + 1)
// Logic: outer loop = rows, inner loop prints j from 1 to n - i + 1 (column number)
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {              // rows
            for (int j = 1; j <= n - i + 1; j++) {  // print column number j
                cout << j;
            }
            cout << endl;                           // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             for j in range(1, n - i + 2):
//                 print(j, end="")
//             print()

// ---------- OUTPUT ----------
// n = 4          n = 2
// 1234           12
// 123            1
// 12
// 1
