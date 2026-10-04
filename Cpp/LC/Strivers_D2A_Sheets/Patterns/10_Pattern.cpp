// ============================================================
// Pattern 10: Half Diamond of Stars (Right Arrow Shape)
// Print 2n - 1 rows, row i has i stars for i <= n, then (2n - i) stars after that
// Logic: loop i from 1 to 2n - 1, stars = i if i <= n, else 2n - i
// Time: O(n^2)   Space: O(1)
// ============================================================

// ---------- C++  ----------
class Solution {
public:
    void printPattern(int n) {
        for (int i = 1; i <= 2 * n - 1; i++) {      // rows
            int stars = i;
            if (i > n) stars = 2 * n - i;           // shrink after middle row
            for (int j = 1; j <= stars; j++) {      // print stars
                cout << "*";
            }
            cout << endl;                           // next row
        }
    }
};

// ---------- Python ----------
// class Solution:
//     def printPattern(self, n):
//         for i in range(1, 2 * n):
//             stars = i if i <= n else 2 * n - i
//             print("*" * stars)

// ---------- OUTPUT ----------
// n = 4          n = 2
// *              *
// **             **
// ***            *
// ****
// ***
// **
// *