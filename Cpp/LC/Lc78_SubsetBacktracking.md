# 78. Subsets (C++)

**Difficulty:** Medium | **Topics:** Array, Backtracking, Bit Manipulation

**Link:** https://leetcode.com/problems/subsets/

---

## Problem Description

Given an integer array `nums` of **unique** elements, return all possible subsets (the power set).

The solution set must **not contain duplicate subsets**. You can return the solution in **any order**.

**Example 1**
```
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**Example 2**
```
Input: nums = [0]
Output: [[],[0]]
```

**Constraints**
- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- All the numbers of `nums` are **unique**.

---

## Intuition and Key Insight

Every element has exactly two choices: it is **in** the subset or it is **out**. With n elements that gives 2^n subsets, and the problem is just enumerating every combination of those choices.

This maps directly to a **decision tree**. At depth `i` you decide about `nums[i]`, branching into "include" and "exclude". Each leaf (depth n) is one complete subset. Backtracking does this by adding the element, recursing, then undoing the add (`pop_back`) and recursing on the other branch.

**Pattern to recognize:** "generate all combinations / subsets / permutations" → backtracking over a decision tree, with a shared path that you extend and then undo.

---

## Approaches

### 1. Backtracking, Include/Exclude Decision Tree (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(0, nums, subset, res);
        return res;
    }

private:
    void dfs(int i, vector<int>& nums, vector<int>& subset, vector<vector<int>>& res) {
        if (i >= nums.size()) {
            res.push_back(subset);              // push_back copies the vector
            return;
        }

        // decision to include nums[i]
        subset.push_back(nums[i]);
        dfs(i + 1, nums, subset, res);

        // decision NOT to include nums[i]
        subset.pop_back();                      // undo the choice (backtrack)
        dfs(i + 1, nums, subset, res);
    }
};
```

- **Time:** O(n x 2^n), since there are 2^n leaves and each copies a subset of up to n elements
- **Space:** O(n) for the recursion depth and the working subset (the output is excluded)
- **Verdict:** Optimal in the sense that the output size itself is O(n x 2^n), so no algorithm can beat this. It is the cleanest version to explain in an interview.

### 2. Backtracking, For-Loop Version (Choose the Next Element)

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(0, nums, subset, res);
        return res;
    }

private:
    void dfs(int start, vector<int>& nums, vector<int>& subset, vector<vector<int>>& res) {
        res.push_back(subset);                  // every node of the tree is a valid subset
        for (int j = start; j < nums.size(); j++) {
            subset.push_back(nums[j]);
            dfs(j + 1, nums, subset, res);      // only look at later elements, so no repeats
            subset.pop_back();
        }
    }
};
```

- **Time:** O(n x 2^n)
- **Space:** O(n) recursion depth
- **Verdict:** Same complexity. Every node of the recursion is recorded as an answer, not just the leaves, so the tree is smaller. This is the template reused in Combinations, Combination Sum and Subsets II.

### 3. Iterative (Build Up by Doubling)

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res = {{}};
        for (int num : nums) {
            int size = res.size();              // fix the size before the loop grows res
            for (int i = 0; i < size; i++) {
                vector<int> next = res[i];      // copy an existing subset
                next.push_back(num);            // and extend it with num
                res.push_back(next);
            }
        }
        return res;
    }
};
```

- **Time:** O(n x 2^n)
- **Space:** O(1) extra (output excluded), with no recursion stack
- **Verdict:** For each new element, the existing subsets are doubled by adding a copy that includes it. Good when you want to avoid recursion.

### 4. Bitmask

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        res.reserve(1 << n);
        for (int mask = 0; mask < (1 << n); mask++) {   // 0 .. 2^n - 1
            vector<int> subset;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) {                  // bit j set means nums[j] is included
                    subset.push_back(nums[j]);
                }
            }
            res.push_back(subset);
        }
        return res;
    }
};
```

- **Time:** O(n x 2^n)
- **Space:** O(1) extra (output excluded)
- **Verdict:** Each integer from 0 to 2^n - 1 is a binary string choosing which elements to include. Neat and iterative, and it works because n is at most 10. `1 << n` overflows `int` once n reaches 31.

---

## Complexity Summary

| Approach | Time | Space (extra) | Notes |
|---|---|---|---|
| **Backtracking, include/exclude** | **O(n x 2^n)** | **O(n)** | **Clearest decision tree** |
| Backtracking, for-loop | O(n x 2^n) | O(n) | Reusable template |
| Iterative doubling | O(n x 2^n) | O(1) | No recursion |
| Bitmask | O(n x 2^n) | O(1) | Iterative, needs small n |

*All are optimal, because the output itself has size Θ(n x 2^n).*

---

## Walkthrough (Include/Exclude)

`nums = [1, 2, 3]`

The decision tree, where each level decides about one element (include on the left, exclude on the right):

```
                          []
               include 1 /    \ exclude 1
                    [1]          []
              inc 2 /  \ exc 2   inc 2 /  \ exc 2
               [1,2]    [1]    [2]       []
              /   \    /   \   /   \    /   \
         [1,2,3] [1,2] [1,3] [1] [2,3] [2] [3]  []
```

The leaves, read left to right, are the recorded subsets:

`{1,2,3}, {1,2}, {1,3}, {1}, {2,3}, {2}, {3}, {}`

That is 8 subsets, which equals 2^3.

Trace of the first few calls:

| Call | subset before | Action | subset after |
|---|---|---|---|
| dfs(0) | {} | include 1 | {1} |
| dfs(1) | {1} | include 2 | {1,2} |
| dfs(2) | {1,2} | include 3 | {1,2,3} |
| dfs(3) | {1,2,3} | `i >= size`, **record** `{1,2,3}` | |
| back in dfs(2) | {1,2,3} | `pop_back`, subset = {1,2} | {1,2} |
| dfs(3) | {1,2} | **record** `{1,2}` | |

---

## Why It Works

Each root-to-leaf path in the tree is a unique sequence of include/exclude decisions, so each of the 2^n leaves is a distinct subset, and no subset is missed. There are no duplicates because the elements are unique and every decision is made exactly once in a fixed order.

**Backtracking** is what lets one shared vector represent every path. After exploring the "include" branch, `pop_back()` restores `subset` to its state before that choice, so the "exclude" branch starts from the correct path.

**Copy semantics:** `res.push_back(subset)` copies the vector's contents into `res`. In Python you must copy explicitly, but in C++ passing a vector by value to `push_back` already does it.

---

## C++ Specific Notes

- **No explicit copy needed:** unlike Python, `res.push_back(subset)` copies the contents. The Python "forgot `.copy()`" bug cannot happen here.
- **Pass by reference:** `subset` and `res` must be passed as `vector<...>&`. Passing `subset` by value would copy it on every call and break the backtracking, because `pop_back` would act on a local copy.
- **Alternative to helper parameters:** use a lambda with `function<void(int)>`, or make `nums`, `subset` and `res` member variables. The private helper is the most common LeetCode style.
- **`nums.size()` is unsigned:** `i >= nums.size()` compares `int` with `size_t`. It is fine here since `i` is never negative, but `int n = nums.size();` avoids the warning.
- **Private helper in a class:** LeetCode allows it. Declare it below `public:` so the entry point stays at the top.
- **`res.reserve(1 << n)`** avoids reallocations of the outer vector in the bitmask version.
- **`1 << n` overflow:** fine for n up to 10 (and up to 30), but undefined at n >= 31 for a 32-bit `int`. Use `1LL << n` for larger n.
- **Iterative version size capture:** `int size = res.size();` must be taken before the inner loop, because `res` grows during it. Using `res.size()` in the loop condition would never terminate.
- **Don't hold references across `push_back`:** in the iterative version, `vector<int>& cur = res[i]; ... res.push_back(cur + num)` can break, since `push_back` may reallocate and invalidate `cur`. Copying `res[i]` into `next` first avoids that.
- **Recursion depth:** at most n + 1 = 11 frames, so no stack concern.

---

## Edge Cases and Pitfalls

- **Forgetting `pop_back`:** the include choice leaks into the exclude branch, and every subset after the first is wrong.
- **Empty subset:** it must be in the answer. The include/exclude version produces it as the all-exclude leaf, and the other versions add it explicitly.
- **Single element** (`{0}`): returns `{{}, {0}}`.
- **Order of output:** any order is accepted, and different approaches produce different orders.
- **Unique elements only:** this problem guarantees it. With duplicates you need LC 90 and a sorted array with a skip rule.
- **Passing `subset` by value in the recursive helper:** the classic C++ backtracking bug, described above.
- **Iterative version:** looping with `i < res.size()` while pushing into `res` loops forever.
- **Bitmask shift:** use `1 << j` and check with `&`. Writing `mask & j` tests the wrong thing.

---

## Interview Follow-Ups

- **"What if the array has duplicates?"** Sort it, and in the for-loop version skip `nums[j]` when `j > start && nums[j] == nums[j - 1]` (LC 90).
- **"Can you do it without recursion?"** Yes, use the iterative doubling or bitmask versions.
- **"Only subsets of size k?"** That is Combinations (LC 77). Stop recording unless `subset.size() == k`, and prune when there are not enough elements left.
- **"Subsets that sum to a target?"** Combination Sum style (LC 39, 40, 216), with pruning when the sum exceeds the target.
- **"What's the space complexity?"** O(n) extra for recursion, and O(n x 2^n) including the output. State both.
- **"Can you do better than O(n x 2^n)?"** No, because the output itself contains n x 2^(n-1) elements in total.
- **"What if n is large?"** The answer is exponential, so you would generate subsets lazily (for example with a Gray code or an iterator) instead of returning them all.

---

## Related Problems

- **90. Subsets II:** the same problem with duplicates
- **77. Combinations:** subsets of fixed size k
- **46. Permutations:** backtracking over orderings
- **47. Permutations II:** permutations with duplicates
- **39. Combination Sum:** backtracking with a target
- **40. Combination Sum II:** with duplicates and single use
- **17. Letter Combinations of a Phone Number:** decision tree over digits
- **131. Palindrome Partitioning:** backtracking over cut positions
- **79. Word Search:** backtracking on a grid

---
