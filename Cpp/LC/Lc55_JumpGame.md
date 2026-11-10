# 55. Jump Game (C++)

**Difficulty:** Medium | **Topics:** Array, Dynamic Programming, Greedy

**Link:** https://leetcode.com/problems/jump-game/

---

## Problem Description

You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element represents your **maximum jump length** at that position.

Return `true` if you can reach the last index, or `false` otherwise.

**Example 1**
```
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2**
```
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0,
which makes it impossible to reach the last index.
```

**Constraints**
- `1 <= nums.length <= 10^4`
- `0 <= nums[i] <= 10^5`

---

## Intuition and Key Insight

Work **backwards**. The last index is the goal. An index `i` can reach the goal if `i + nums[i] >= goal`. If it can, then `i` itself becomes the new goal, because reaching `i` is now good enough. Repeat for every index moving left. At the end, if the goal has moved all the way to index 0, the start can reach the end.

The forward view is equivalent: track the **farthest index reachable** so far, and fail if you ever stand at an index beyond it.

**Pattern to recognize:** "can I reach the end / is a path possible" with flexible step sizes → greedy, tracking a single frontier (farthest reach or earliest good position) instead of exploring all paths.

---

## Approaches

### 1. Brute Force: Recursion (Try Every Jump)

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        return dfs(nums, 0);
    }

private:
    bool dfs(vector<int>& nums, int i) {
        int n = nums.size();
        if (i >= n - 1) return true;
        for (int step = 1; step <= nums[i]; step++) {
            if (dfs(nums, i + step)) return true;
        }
        return false;
    }
};
```

- **Time:** O(2^n) in the worst case, since there are exponentially many jump sequences
- **Space:** O(n) for the recursion stack
- **Verdict:** Correct but far too slow. Mention it to show the search space, then add memoization.

### 2. Top-Down DP (Memoization)

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<int> memo(nums.size(), -1);          // -1 unknown, 0 false, 1 true
        return dfs(nums, 0, memo);
    }

private:
    bool dfs(vector<int>& nums, int i, vector<int>& memo) {
        int n = nums.size();
        if (i >= n - 1) return true;
        if (memo[i] != -1) return memo[i];

        for (int step = 1; step <= nums[i]; step++) {
            if (dfs(nums, i + step, memo)) {
                return memo[i] = 1;
            }
        }
        return memo[i] = 0;
    }
};
```

- **Time:** O(n²), since each index is solved once and tries up to n jumps
- **Space:** O(n) for the memo and recursion stack
- **Verdict:** Fixes the exponential blowup and shows the DP structure. Recursion depth is at most 10^4, which is fine in C++.

### 3. Bottom-Up DP

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> good(n, false);
        good[n - 1] = true;                         // last index trivially reaches itself

        for (int i = n - 2; i >= 0; i--) {
            int furthest = min(i + nums[i], n - 1);
            for (int j = i + 1; j <= furthest; j++) {
                if (good[j]) {
                    good[i] = true;
                    break;
                }
            }
        }
        return good[0];
    }
};
```

- **Time:** O(n²)
- **Space:** O(n)
- **Verdict:** Same idea as memoization without recursion. It is the stepping stone to the greedy insight that you only need to remember the **leftmost good index**.

### 4. Greedy, Move the Goal Backwards (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int goal = n - 1;                           // index we must reach

        for (int i = n - 1; i >= 0; i--) {
            if (i + nums[i] >= goal) {              // i can reach the current goal
                goal = i;                           // so i is the new goal
            }
        }

        return goal == 0;
    }
};
```

- **Time:** O(n), one pass
- **Space:** O(1)
- **Verdict:** Optimal.

### 5. Greedy, Track Farthest Reach (Forward)

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0;

        for (int i = 0; i < n; i++) {
            if (i > farthest) return false;         // stranded: cannot even reach index i
            farthest = max(farthest, i + nums[i]);
            if (farthest >= n - 1) return true;     // early exit
        }
        return true;
    }
};
```

- **Time:** O(n)
- **Space:** O(1)
- **Verdict:** Equally optimal, and many people find it the more intuitive framing. It can exit early, unlike the backward version.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Recursion | O(2^n) | O(n) | TLE |
| Top-down DP | O(n²) | O(n) | Memo with -1/0/1 states |
| Bottom-up DP | O(n²) | O(n) | Stepping stone to greedy |
| **Greedy, goal moves back** | **O(n)** | **O(1)** | **Optimal** |
| **Greedy, farthest reach** | **O(n)** | **O(1)** | **Optimal, early exit** |

---

## Walkthrough (Goal Moves Back)

`nums = [2, 3, 1, 1, 4]`, starting with `goal = 4`

| i | nums[i] | i + nums[i] | >= goal? | goal after |
|---|---|---|---|---|
| 4 | 4 | 8 | Yes | 4 |
| 3 | 1 | 4 | Yes | 3 |
| 2 | 1 | 3 | Yes | 2 |
| 1 | 3 | 4 | Yes (4 >= 2) | 1 |
| 0 | 2 | 2 | Yes (2 >= 1) | **0** |

`goal == 0`, so the answer is `true`.

Failing case, `nums = [3, 2, 1, 0, 4]`, starting with `goal = 4`

| i | nums[i] | i + nums[i] | >= goal? | goal after |
|---|---|---|---|---|
| 4 | 4 | 8 | Yes | 4 |
| 3 | 0 | 3 | No | 4 |
| 2 | 1 | 3 | No | 4 |
| 1 | 2 | 3 | No | 4 |
| 0 | 3 | 3 | No | 4 |

`goal == 4`, not 0, so the answer is `false`.

---

## Why It Works

At each step, `goal` is the **leftmost index known to reach the end**. For an index `i` to be good, it only needs to reach *some* good index, and a jump of length `nums[i]` can land on **any** index from `i + 1` to `i + nums[i]`. So if `i + nums[i] >= goal`, you can choose a jump that lands exactly on `goal`.

That makes `i + nums[i] >= goal` both necessary and sufficient, and moving `goal` left as soon as it succeeds never loses information.

---

## C++ Specific Notes

- **Overflow:** `i + nums[i]` is at most about 10^4 + 10^5, which fits easily in `int`.
- **Use `int` for the reverse loop:** with `size_t i`, the condition `i >= 0` is always true and the loop never ends, because decrementing past 0 wraps to a huge value. Take `int n = nums.size();` first.
- **`vector<bool>` is a bit-packed specialization.** It works fine here, but it returns proxy objects instead of real references. Use `vector<char>` or `vector<int>` if you need to take addresses or want faster access.
- **Memo encoding:** `vector<int>` with -1/0/1 distinguishes "unknown" from "false", which a plain `vector<bool>` cannot do.
- **Assignment as expression:** `return memo[i] = 1;` assigns and returns in one step. It converts the int to `bool` on return.
- **Private helper in a class:** LeetCode allows it. Pass `nums` and `memo` by reference to avoid copying on each recursive call.
- **Recursion depth:** at most 10^4 frames here, which is safe in C++, unlike Python's default limit of 1000.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. These solutions do not modify the input.

---

## Edge Cases and Pitfalls

- **Single element** (`[0]`): you are already at the last index, so the answer is `true`. Here `goal = 0` from the start, and the loop leaves it at 0.
- **Zero at the start with length > 1** (`[0, 1]`): `false`, because you can't move.
- **A zero in the middle isn't always fatal** (`[2, 0, 0]`): you can jump over it, so the answer is `true`.
- **A zero you can't jump over** (`[3, 2, 1, 0, 4]`): `false`. Every path ends at index 3, and the farthest reach stalls there.
- **Large jumps:** `i + nums[i]` can exceed the array length, and the `>=` comparison handles it. No clamping is needed.
- **`>=` not `==`:** you do not need to land exactly on the goal, because you can always choose a shorter jump.
- **Loop direction in the backward version:** it must go right to left, since each decision depends on the goal found to its right.
- **Forward version:** check `i > farthest` **before** updating `farthest`, otherwise an unreachable index can extend the reach.

---

## Interview Follow-Ups

- **"What's the minimum number of jumps?"** That is LC 45 (Jump Game II), solved with a greedy BFS over reachable ranges in O(n).
- **"Return the path, not just true or false."** Use the forward version and store, for each index, the index that first reached it, or do DP with parent pointers.
- **"What if you can also jump backwards?"** The problem becomes graph reachability, so use BFS or DFS (LC 1306, LC 1345).
- **"What if each jump must be exactly nums[i]?"** Then it is a graph traversal from index 0 with visited tracking (LC 1306 style).
- **"Why is greedy correct here but not for other path problems?"** Because reachability is monotone: if you can reach index `x`, you can reach every index before `x` that is also within range, so only the frontier matters.
- **"Can you do better than O(n)?"** No, since every element can affect the answer.

---

## Related Problems

- **45. Jump Game II:** minimum number of jumps, greedy
- **1306. Jump Game III:** reachability with jumps in both directions (BFS/DFS)
- **1345. Jump Game IV:** BFS over a graph with value-based edges
- **1340. Jump Game V:** DP with bounded jumps
- **1696. Jump Game VI:** DP with a sliding window maximum
- **134. Gas Station:** greedy on a circular reachability idea
- **763. Partition Labels:** greedy with a running frontier
- **53. Maximum Subarray:** another single-pass greedy running-value problem

---
