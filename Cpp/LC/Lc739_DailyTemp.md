# 739. Daily Temperatures (C++)

**Difficulty:** Medium | **Topics:** Array, Stack, Monotonic Stack

**Link:** https://leetcode.com/problems/daily-temperatures/

---

## Problem Description

Given an array of integers `temperatures` representing the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `i`-th day to get a **warmer** temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

**Example 1**
```
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

**Example 2**
```
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

**Example 3**
```
Input: temperatures = [30,60,90]
Output: [1,1,0]
```

**Constraints**
- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`

---

## Intuition and Key Insight

For each day you want the **next greater element** to its right, measured as a distance in days. Scanning forward, a day stays "unresolved" until a warmer day shows up. Keep the unresolved days on a stack. When a new temperature `t` arrives, every unresolved day on the stack that is **colder than `t`** is resolved by this day, so pop them and record the gap.

The unresolved days on the stack always have **non-increasing** temperatures from bottom to top (a warmer day would have resolved the colder ones above it). That is why it is called a **monotonic stack**, and why only the top ever needs to be checked.

Each index is pushed once and popped at most once, so the total work is linear.

**Pattern to recognize:** "next greater / next smaller element" → monotonic stack.

---

## Approaches

### 1. Brute Force: Scan Forward for Each Day

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    res[i] = j - i;
                    break;
                }
            }
        }
        return res;
    }
};
```

- **Time:** O(n²) in the worst case (for example a non-increasing array, where nothing is ever found)
- **Space:** O(1) extra (output excluded)
- **Verdict:** With n up to 10^5 that is about 5 x 10^9 steps in the worst case, so it will time out. Mention it as the baseline.

### 2. Monotonic Stack of Pairs (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<pair<int, int>> st;                   // (temp, index) of unresolved days

        for (int i = 0; i < n; i++) {
            int t = temperatures[i];
            while (!st.empty() && t > st.top().first) {     // today is warmer than the top
                int stackInd = st.top().second;
                st.pop();
                res[stackInd] = i - stackInd;               // days waited
            }
            st.push({t, i});                                // today is now unresolved
        }
        return res;
    }
};
```

- **Time:** O(n), since each index is pushed once and popped at most once
- **Space:** O(n) for the stack (a strictly decreasing array keeps everything on it)
- **Verdict:** Optimal and the expected interview answer.

### 3. Monotonic Stack of Indices Only

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> st;                              // indices only

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int j = st.top();
                st.pop();
                res[j] = i - j;
            }
            st.push(i);
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(n)
- **Verdict:** Same algorithm, a bit leaner. The temperature can always be looked up from the index, so storing the pair is redundant.

### 4. Vector as Stack (Faster in Practice)

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        vector<int> st;                             // vector used as a stack of indices
        st.reserve(n);

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.back()]) {
                int j = st.back();
                st.pop_back();
                res[j] = i - j;
            }
            st.push_back(i);
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(n)
- **Verdict:** Avoids the `std::stack` deque overhead. A micro-optimization, but a common LeetCode speed trick.

### 5. Right-to-Left with Jumping (O(1) Extra Space)

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        for (int i = n - 2; i >= 0; i--) {
            int j = i + 1;
            while (temperatures[j] <= temperatures[i]) {
                if (res[j] == 0) {                  // nothing warmer ahead of j either
                    j = n;                          // mark as not found
                    break;
                }
                j += res[j];                        // jump to j's next warmer day
            }
            if (j < n) res[i] = j - i;
        }
        return res;
    }
};
```

- **Time:** O(n) amortized
- **Space:** O(1) extra (output excluded)
- **Verdict:** Reuses the answers already computed to the right to skip ahead. Trickier to get right, but a good answer to "can you avoid the stack?".

---

## Complexity Summary

| Approach | Time | Space (extra) | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | TLE |
| **Monotonic stack, pairs** | **O(n)** | **O(n)** | **Optimal, standard** |
| Monotonic stack, indices | O(n) | O(n) | Leaner |
| Vector as stack | O(n) | O(n) | Fastest in practice |
| Right-to-left jumping | O(n) | O(1) | Trickier, no stack |

---

## Walkthrough (Pairs Stack)

`temperatures = [73, 74, 75, 71, 69, 72, 76, 73]`

| i | t | Pops (index, wait) | Stack after (temps) | res after |
|---|---|---|---|---|
| 0 | 73 | none | [73] | [0,0,0,0,0,0,0,0] |
| 1 | 74 | pop 73 (idx 0), 1-0 = 1 | [74] | [1,0,0,0,0,0,0,0] |
| 2 | 75 | pop 74 (idx 1), 2-1 = 1 | [75] | [1,1,0,0,0,0,0,0] |
| 3 | 71 | none | [75, 71] | same |
| 4 | 69 | none | [75, 71, 69] | same |
| 5 | 72 | pop 69 (idx 4) = 1, pop 71 (idx 3) = 2 | [75, 72] | [1,1,0,2,1,0,0,0] |
| 6 | 76 | pop 72 (idx 5) = 1, pop 75 (idx 2) = 4 | [76] | [1,1,4,2,1,1,0,0] |
| 7 | 73 | none | [76, 73] | same |

Result: `{1,1,4,2,1,1,0,0}`. Days 6 and 7 remain on the stack, so their answers stay `0`.

---

## Why It Works

**Invariant:** the stack holds the indices of days with no warmer day found yet, and their temperatures are non-increasing from bottom to top.

**Correctness of popping:** when `t` is greater than the top's temperature, day `i` is the **first** warmer day after the top, because every day between them was either resolved earlier or would have been pushed above the top (and popped first). So `i - stackInd` is exactly the wait.

**Why stop at the first non-smaller top:** everything below it has temperature at least as large as the top, so none of them can be smaller than `t` either.

**Why strict `>`:** equal temperatures are not "warmer", so they stay on the stack.

---

## C++ Specific Notes

- **Check `empty()` before `top()`:** calling `top()` or `pop()` on an empty `std::stack` is undefined behavior, not an exception. The `!st.empty() &&` short-circuit is essential.
- **`pop()` returns void:** read `top()` first, copy what you need, then `pop()`. Holding a reference to `st.top()` across the `pop()` leaves a dangling reference, which is why the code copies `stackInd` before popping.
- **`stack<pair<int,int>>`:** `st.push({t, i})` builds the pair in place. `.first` is the temperature and `.second` is the index.
- **Use `int n = temperatures.size();`:** avoids the signed/unsigned comparison warning, and it matters for `n - 2` in the right-to-left version, where `size_t` would wrap on tiny inputs.
- **Right-to-left version and `n == 1`:** the loop starts at `n - 2 = -1`, so it doesn't run and returns `{0}`. This is safe only because `n` is a signed `int`.
- **`std::stack` uses `deque` by default:** a `vector` as a stack (approach 4) has lower overhead and better cache behavior.
- **`vector<int> res(n, 0)`:** zero-initializes, which is exactly the default answer for unresolved days.
- **Overflow:** none. Values are at most 100 and distances at most 10^5.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. These solutions do not modify the input.

---

## Edge Cases and Pitfalls

- **Single element** (`{50}`): returns `{0}`.
- **Strictly decreasing** (`{90,80,70}`): nothing is ever popped, so all zeros.
- **Strictly increasing** (`{30,40,50,60}`): each day pops the previous one, giving `{1,1,1,0}`.
- **All equal** (`{70,70,70}`): `>` is false, so nothing pops, and the result is all zeros. Using `>=` would be wrong.
- **Unresolved days at the end:** they keep the default `0`, which is exactly the required output, so no cleanup pass is needed.
- **Storing the distance, not the index:** the answer is `i - stackInd`, not `i`.
- **Popping only once:** it must be a `while`, since one warm day can resolve many colder ones (day 6 above resolved two).
- **Reading `top()` after `pop()`:** undefined behavior if the stack is then empty, and the wrong element otherwise.

---

## Interview Follow-Ups

- **"Why is this O(n) when there is a nested loop?"** Each index is pushed once and popped at most once, so the inner `while` runs at most n times in total across all iterations (amortized analysis).
- **"What if you need the next **smaller** element?"** Flip the comparison.
- **"What about the previous greater element?"** Scan the same way and read the stack top **before** pushing, instead of when popping.
- **"Circular array?"** Iterate over `2n` indices with `i % n` (LC 503).
- **"Can you avoid the stack?"** Yes, the right-to-left jumping version uses the already computed answers (approach 5).
- **"Use the small temperature range?"** With temperatures in 30..100, scan right to left keeping the most recent index of each temperature, and for each day check the 70 possible warmer values, giving O(70 x n).
- **"Can you do better than O(n)?"** No, you must read every day.

---

## Related Problems

- **496. Next Greater Element I:** monotonic stack with a lookup map
- **503. Next Greater Element II:** circular array
- **84. Largest Rectangle in Histogram:** monotonic stack for boundaries
- **85. Maximal Rectangle:** histogram per row
- **901. Online Stock Span:** monotonic stack with a running count
- **42. Trapping Rain Water:** monotonic stack alternative
- **402. Remove K Digits:** monotonic stack greedy
- **907. Sum of Subarray Minimums:** monotonic stack with contribution counting
- **20. Valid Parentheses:** the plain stack pattern

---
