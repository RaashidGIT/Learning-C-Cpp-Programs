// ============================================================
// Pattern 4: Right-Angled Triangle of Repeated Row Numbers
// Print a triangle where row i (1 to n) prints the number i, i times
// Logic: outer loop = rows, inner loop runs j <= i, print the row number i
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= n; i++) {      // rows
            for (int j = 1; j <= i; j++) {  // repeat i, i times
                cout << i;
            }
            cout << endl;                   // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, n + 1):
//             print(str(i) * i)

// ---------- OUTPUT ----------
// n = 4          n = 2
// 1              1
// 22             22
// 333
// 4444
