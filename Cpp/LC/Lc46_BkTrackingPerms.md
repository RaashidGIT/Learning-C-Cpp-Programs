# 46. Permutations (C++)

**Difficulty:** Medium | **Topics:** Array, Backtracking

**Link:** https://leetcode.com/problems/permutations/

---

## Problem Description

Given an array `nums` of **distinct** integers, return all the possible permutations. You can return the answer in **any order**.

**Example 1**
```
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**Example 2**
```
Input: nums = [0,1]
Output: [[0,1],[1,0]]
```

**Example 3**
```
Input: nums = [1]
Output: [[1]]
```

**Constraints**
- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- All the integers of `nums` are **unique**.

---

## Intuition and Key Insight

A permutation is an ordering, so at each position you choose **one of the elements not yet used**. That gives n choices for the first slot, n - 1 for the second, and so on, for n! permutations in total.

The recursive build-up idea: pick one element out of the array, get all permutations of the remaining elements, then attach the picked element to each of them. Doing this for every choice covers every permutation exactly once.

The standard backtracking alternative keeps a shared path and a "used" marker, and is the template reused in most backtracking problems.

**Pattern to recognize:** "generate all orderings / arrangements" → backtracking where each level picks one unused element.

---

## Approaches

### 1. Recursive Build-Up: Pop, Recurse, Append

C++ translation of the Python solution from your notes. It uses `deque`-style front removal, so the helper takes the vector by value.

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // base case
        if (nums.size() == 1) {
            return {nums};                          // one element: one permutation
        }

        vector<vector<int>> result;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums.front();
            nums.erase(nums.begin());               // take the front element out (O(n))
            vector<vector<int>> perms = permute(nums);   // all permutations of the rest

            for (auto& perm : perms) {
                perm.push_back(x);                  // attach the removed element
            }
            result.insert(result.end(), perms.begin(), perms.end());
            nums.push_back(x);                      // put it at the back, rotating the list
        }
        return result;
    }
};
```

- **Time:** O(n x n!), since there are n! permutations, each built with O(n) work (`erase` at the front also costs O(n) per call)
- **Space:** O(n) recursion depth, plus the intermediate lists, with the output itself O(n x n!)
- **Verdict:** Correct, and the rotation trick is clever. Each iteration removes the front element and appends it to the back afterwards, so across the loop every element takes a turn being the one removed. It is less common than the standard template, so be ready to explain it.

### 2. Backtracking with a Used Array (Standard Template)

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        dfs(nums, path, used, res);
        return res;
    }

private:
    void dfs(vector<int>& nums, vector<int>& path, vector<bool>& used,
             vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);                    // push_back copies the vector
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;                  // already placed in this permutation
            used[i] = true;
            path.push_back(nums[i]);
            dfs(nums, path, used, res);
            path.pop_back();                        // undo
            used[i] = false;
        }
    }
};
```

- **Time:** O(n x n!)
- **Space:** O(n) for `path`, `used` and the recursion
- **Verdict:** The expected interview answer. It is the same decision tree as Subsets, except that each level chooses among unused elements instead of include/exclude.

### 3. Backtracking with Swapping (In-Place)

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        dfs(0, nums, res);
        return res;
    }

private:
    void dfs(int start, vector<int>& nums, vector<vector<int>>& res) {
        if (start == nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);             // choose nums[i] for position start
            dfs(start + 1, nums, res);
            swap(nums[start], nums[i]);             // undo the swap
        }
    }
};
```

- **Time:** O(n x n!)
- **Space:** O(n) recursion only, with no `used` array
- **Verdict:** The most space-efficient version. The prefix `nums[0..start-1]` is the fixed part of the permutation, and the suffix holds the remaining candidates. It mutates `nums` temporarily but restores it.

### 4. Library: `next_permutation`

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(), nums.end());             // must start from the smallest ordering
        vector<vector<int>> res;
        do {
            res.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return res;
    }
};
```

- **Time:** O(n x n!)
- **Space:** O(1) extra (output excluded)
- **Verdict:** Short and fine in practice. Interviewers usually want the manual version, so mention it as a shortcut only. Sorting first is essential, since `next_permutation` stops after the largest ordering.

---

## Complexity Summary

| Approach | Time | Space (extra) | Notes |
|---|---|---|---|
| Pop / recurse / append | O(n x n!) | O(n) | Elegant, uses list rotation |
| **Backtracking with `used`** | **O(n x n!)** | **O(n)** | **Standard template** |
| Backtracking with swaps | O(n x n!) | O(n) | No `used` array |
| `next_permutation` | O(n x n!) | O(1) | Library shortcut, needs sort |

*All are optimal, because the output has n! permutations of length n.*

---

## Walkthrough (Pop / Recurse / Append)

`nums = {1, 2, 3}`

Top-level loop, with `nums` rotating each time:

| i | nums before | front removed (x) | nums passed down | perms of rest | After appending x | nums after push_back |
|---|---|---|---|---|---|---|
| 0 | {1,2,3} | 1 | {2,3} | {{2,3},{3,2}} | {{2,3,1},{3,2,1}} | {2,3,1} |
| 1 | {2,3,1} | 2 | {3,1} | {{3,1},{1,3}} | {{3,1,2},{1,3,2}} | {3,1,2} |
| 2 | {3,1,2} | 3 | {1,2} | {{1,2},{2,1}} | {{1,2,3},{2,1,3}} | {1,2,3} |

Result: `{{2,3,1},{3,2,1},{3,1,2},{1,3,2},{1,2,3},{2,1,3}}`, which is all 6 permutations.

Walkthrough of the used-array version for `{1,2,3}`, in the order permutations are produced:

`{1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}`

---

## Why It Works

**The rotation:** after n iterations, each of which moves the front element to the back, the list is rotated n times and returns to its original order. That is why `nums` is unchanged when the function returns, which the caller relies on.

**Coverage:** in iteration `i`, the element removed is the one originally at index `i` (since the previous `i` elements have rotated behind it). So every element gets a turn as the "last" element of its permutations, and the recursion covers all orderings of the rest.

**Why the base case returns a copy:** the caller mutates the returned lists with `perm.push_back(x)`. In C++, `return {nums};` builds a new vector of vectors holding a copy of `nums`, so there is no aliasing with the caller's live list.

**Why it builds permutations backwards:** each level appends `x` at the end, so the permutation is assembled from the last position to the first. The order of results differs from the standard template, which is fine since any order is accepted.

---

## C++ Specific Notes

- **No aliasing bug:** `res.push_back(path)` and `return {nums};` copy the vector. The Python "forgot `.copy()`" bug cannot happen here.
- **Pass by reference in the helpers:** `path`, `used` and `res` must be `&`. Passing `path` by value would copy it on every call and break the backtracking.
- **`vector::erase(begin())` is O(n)**, like Python's `pop(0)`. A `deque` with `pop_front()` is O(1), though for n at most 6 it makes no difference.
- **`vector<bool>`** is a bit-packed specialization. It works fine here, but use `vector<char>` if you ever need real references.
- **Swap:** `std::swap(nums[start], nums[i])` is fine even when `start == i` (a self-swap does nothing).
- **`nums.size()` is unsigned:** comparisons with `int` indices give sign-compare warnings. `int n = nums.size();` avoids them.
- **`next_permutation` needs `<algorithm>` and a sorted start.** If the input is not sorted first, it only produces the permutations that come after the starting one, and silently misses the rest.
- **Recursion depth:** at most n + 1 = 7 frames, so no stack concern.
- **Input mutation:** approaches 1 and 3 modify `nums` mid-run but restore it. Approach 4 sorts `nums`, which permanently changes the caller's order.
- **Return by value:** `return res;` is moved or elided, so there is no copy.

---

## Edge Cases and Pitfalls

- **Single element** (`{1}`): returns `{{1}}`, handled by the base case.
- **Two elements** (`{0,1}`): returns both orderings.
- **Forgetting `nums.push_back(x)` after recursing** (approach 1): the vector shrinks permanently and the rotation breaks.
- **Forgetting `used[i] = false`** (approach 2): later branches see elements as taken, and permutations are missing.
- **Forgetting the second swap** (approach 3): the array stays scrambled, and the result has duplicates and misses permutations.
- **Empty input:** the constraints guarantee at least one element. The recursive approach would reach `nums.front()` on an empty vector only if called with one, which is undefined behavior, so guard it in your own code.
- **Duplicates:** this problem guarantees distinct elements. With duplicates you need LC 47, with sorting and a skip rule.
- **`next_permutation` without sorting:** the most common mistake with the library version, as noted above.

---

## Interview Follow-Ups

- **"What if the array has duplicates?"** Sort it, and skip an element if it equals the previous one and the previous one is unused (LC 47).
- **"Can you do it in place without a `used` array?"** Yes, the swap-based version.
- **"Return the next permutation only?"** Find the rightmost ascent, swap with the next larger element to its right, and reverse the suffix, in O(n) (LC 31). This is what `std::next_permutation` does.
- **"Return the k-th permutation?"** Use the factorial number system to pick each digit directly, in O(n²) (LC 60).
- **"Why is the complexity O(n x n!)?"** There are n! leaves, and each permutation costs O(n) to copy into the result.
- **"What if n is large?"** The output is factorial, so generate permutations lazily (for example with `next_permutation` one at a time) instead of storing them all.
- **"Permutations of a subset of size k?"** Stop at depth k instead of n (partial permutations, n!/(n-k)!).

---

## Related Problems

- **47. Permutations II:** permutations with duplicates
- **31. Next Permutation:** the next one in lexicographic order
- **60. Permutation Sequence:** the k-th permutation
- **78. Subsets:** the include/exclude backtracking template
- **77. Combinations:** subsets of fixed size k
- **39. Combination Sum:** backtracking with a target
- **17. Letter Combinations of a Phone Number:** decision tree over digits
- **784. Letter Case Permutation:** binary choice per character
- **996. Number of Squareful Arrays:** permutations with pruning

---
