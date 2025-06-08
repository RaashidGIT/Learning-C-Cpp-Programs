/*
    Aim: To implement First Fit memory allocation strategy in C
         where each process is allocated to the first memory hole
         that is large enough to accommodate it.

### ✅ **Descriptive Algorithm**

---

#### **Step 1: Initialization**

1. Declare arrays:

   * `p[10]` for storing **Process** structures.
   * `h[10]` for storing **Hole** structures.
2. Each process has:

   * `size`: memory needed.
   * `flag`: 0 if not allocated, 1 if allocated.
   * `holeId`: index of the hole it gets allocated to (if any).
3. Each hole has:

   * `size`: available memory (reduced after allocation).
   * `actual`: original size (preserved for reporting later).

---

#### **Step 2: Input Memory Hole Information**

1. Ask the user to input number of holes `nh`.
2. For each hole `H[i]`, input its `size`.
3. Store this size in both `h[i].size` and `h[i].actual`.

---

#### **Step 3: Input Process Information**

1. Ask the user to input number of processes `np`.
2. For each process `P[i]`, input its `size`.
3. Initialize `p[i].flag = 0` to indicate that no allocation has been done yet.

---

#### **Step 4: First Fit Allocation Algorithm**

1. For each process `P[i]` (from `i = 0` to `np - 1`):

   * Traverse the holes from `j = 0` to `nh - 1`.
   * If `P[i]` is not yet allocated (`flag == 0`) **and** `P[i].size <= H[j].size`:

     * Assign the hole to the process: `p[i].holeId = j`.
     * Mark the process as allocated: `p[i].flag = 1`.
     * Reduce available hole size: `h[j].size -= p[i].size`.
     * Break the inner loop and move to next process.
   * This ensures each process gets the **first available hole** large enough — that's why it's called **First Fit**.

---

#### **Step 5: Display Allocation Results**

1. Print header: `"First Fit Allocation"`.
2. For each process:

   * Print process ID and size.
   * If `flag == 1`, print the hole ID (`H[p[i].holeId]`) it's allocated to.
   * Else, print `"Not allocated"`.

---

#### **Step 6: Display Remaining Hole Sizes**

1. Print header: `"Hole\tActual\tAvailable"`.
2. For each hole:

   * Print hole ID.
   * Print original size (`actual`) and remaining available size (`size` after allocations).

------

*/

#include <stdio.h>

// Structure to represent a process
struct Process {
    int size;     // Size of the process
    int flag;     // Allocation flag (0 = not allocated, 1 = allocated)
    int holeId;   // Index of the hole to which the process is allocated
} p[10];          // Array of up to 10 processes

// Structure to represent a hole
struct Hole {
    int size;     // Available size in the hole (gets reduced as processes are allocated)
    int actual;   // Original size of the hole (for reporting)
} h[10];          // Array of up to 10 holes

int main() {
    int np, nh;   // np = number of processes, nh = number of holes

    // Step 1: Input number and sizes of memory holes
    printf("Enter number of Holes: ");
    scanf("%d", &nh);
    for (int i = 0; i < nh; i++) {
        printf("Size of hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size;  // Save the original size
    }

    // Step 2: Input number and sizes of processes
    printf("\nEnter number of Processes: ");
    scanf("%d", &np);
    for (int i = 0; i < np; i++) {
        printf("Size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0;  // Initialize allocation flag as not allocated
    }

    // Step 3: First Fit Allocation
    for (int i = 0; i < np; i++) {          // Loop through all processes
        for (int j = 0; j < nh; j++) {      // Loop through all holes
            if (!p[i].flag && p[i].size <= h[j].size) {  // If not yet allocated and hole is large enough
                p[i].flag = 1;              // Mark process as allocated
                p[i].holeId = j;            // Save the hole ID
                h[j].size -= p[i].size;     // Reduce the hole size
                break;                      // Move to the next process
            }
        }
    }

    // Step 4: Display allocation result
    printf("\n\tFirst Fit Allocation\nProcess\tSize\tHole");
    for (int i = 0; i < np; i++) {
        printf("\nP%d\t%d\t", i, p[i].size);
        if (p[i].flag)
            printf("H%d", p[i].holeId);
        else
            printf("Not allocated");
    }

    // Step 5: Display final hole availability
    printf("\n\nHole\tActual\tAvailable");
    for (int i = 0; i < nh; i++)
        printf("\nH%d\t%d\t%d", i, h[i].actual, h[i].size);

    return 0;
}

/*
-------------------------------SIMULATED OUTPUT-----------------------------------

Enter number of Processes: 4
Size of process P0: 214
Size of process P1: 417
Size of process P2: 112
Size of process P3: 426

        First Fit Allocation
Process Size    Hole
P0      214     H1
P1      417     Not allocated
P2      112     H1
P3      426     Not allocated

Hole    Actual  Available
H0      100     100
H1      500     174
H2      200     200

*/
