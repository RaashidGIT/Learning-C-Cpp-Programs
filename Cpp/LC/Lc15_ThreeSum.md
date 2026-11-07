# 15. 3Sum (C++)

**Difficulty:** Medium | **Topics:** Array, Two Pointers, Sorting

**Link:** https://leetcode.com/problems/3sum/

---

## Problem Description

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

The solution set must **not contain duplicate triplets**. The order of the triplets and the order within each triplet do not matter.

**Example 1**
```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
```

**Example 2**
```
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
```

**Example 3**
```
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

**Constraints**
- `3 <= nums.length <= 3000`
- `-10^5 <= nums[i] <= 10^5`

---

## Intuition and Key Insight

This is Two Sum with one extra loop. Fix one number `a`, then you need two other numbers that sum to `-a`. If the array is **sorted**, the two-number search becomes a two-pointer sweep from both ends:

- Sum too big → move the right pointer left (smaller value).
- Sum too small → move the left pointer right (larger value).
- Sum equals 0 → record the triplet, then move on.

Sorting also solves the hardest part of the problem, **duplicates**. Equal values sit next to each other, so you can skip repeats of the fixed number and repeats of the left pointer without needing a set.

**Pattern to recognize:** "find k numbers that sum to a target, with no duplicate combinations" → sort, fix k-2 elements, then two pointers on the rest.

---

## Approaches

### 1. Brute Force: Three Nested Loops

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> found;                     // set of sorted triplets removes duplicates
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> t = {nums[i], nums[j], nums[k]};
                        sort(t.begin(), t.end());
                        found.insert(t);
                    }
                }
            }
        }
        return vector<vector<int>>(found.begin(), found.end());
    }
};
```

- **Time:** O(n³), plus a log factor for set insertions
- **Space:** O(m), where m is the number of unique triplets
- **Verdict:** With n up to 3000 that is about 4.5 x 10^9 triples, so it will time out. Mention it as the baseline.

### 2. Hash Set (Two Sum Inside a Loop)

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // skip duplicate first element

            unordered_set<int> seen;
            for (int j = i + 1; j < n; j++) {
                int complement = -nums[i] - nums[j];
                if (seen.count(complement)) {
                    res.push_back({nums[i], complement, nums[j]});
                    while (j + 1 < n && nums[j] == nums[j + 1]) j++;   // skip duplicate second element
                }
                seen.insert(nums[j]);
            }
        }
        return res;
    }
};
```

- **Time:** O(n²)
- **Space:** O(n) for the set
- **Verdict:** Same time as two pointers, but it uses extra space and the duplicate handling is harder to get right. Know it as the "Two Sum inside a loop" idea, then prefer two pointers.

### 3. Sort + Two Pointers (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int a = nums[i];
            if (i > 0 && a == nums[i - 1]) continue;        // skip duplicate first element

            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = a + nums[l] + nums[r];
                if (sum > 0) {
                    r--;                                    // sum too big, need smaller
                } else if (sum < 0) {
                    l++;                                    // sum too small, need bigger
                } else {
                    res.push_back({a, nums[l], nums[r]});
                    l++;
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;                                // skip duplicate second element
                    }
                }
            }
        }
        return res;
    }
};
```

- **Time:** O(n²), since sorting is O(n log n) and each fixed `i` costs one O(n) two-pointer sweep
- **Space:** O(1) extra, or O(log n) for the sort's recursion stack (output excluded)
- **Verdict:** Optimal and the expected interview answer. No hash set is needed because sorting makes duplicates adjacent.

### 4. Sort + Two Pointers with Early Exit (Minor Optimization)

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) break;                         // smallest is positive, no way to reach 0
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum > 0) {
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while (l < r && nums[l] == nums[l - 1]) l++;
                }
            }
        }
        return res;
    }
};
```

- **Time:** O(n²)
- **Space:** O(1) extra
- **Verdict:** Same complexity, with an early `break` once the smallest number is positive. Moving `r` as well after a match is also fine, because the old `r` cannot pair with the new `l` to reach 0.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n³) | O(m) | TLE |
| Hash set per element | O(n²) | O(n) | Duplicate handling is tricky |
| **Sort + two pointers** | **O(n²)** | **O(1)** | **Optimal, expected answer** |
| Two pointers + early exit | O(n²) | O(1) | Slightly faster in practice |

---

## Walkthrough (Two Pointers)

`nums = [-1, 0, 1, 2, -1, -4]` → sorted: `[-4, -1, -1, 0, 1, 2]`

| i | a | l | r | sum | Action | res |
|---|---|---|---|---|---|---|
| 0 | -4 | 1 | 5 | -4 + -1 + 2 = -3 | < 0, `l = 2` | |
| 0 | -4 | 2 | 5 | -4 + -1 + 2 = -3 | < 0, `l = 3` | |
| 0 | -4 | 3 | 5 | -4 + 0 + 2 = -2 | < 0, `l = 4` | |
| 0 | -4 | 4 | 5 | -4 + 1 + 2 = -1 | < 0, `l = 5`, loop ends | |
| 1 | -1 | 2 | 5 | -1 + -1 + 2 = 0 | match, record, `l = 3` | {{-1,-1,2}} |
| 1 | -1 | 3 | 5 | -1 + 0 + 2 = 1 | > 0, `r = 4` | |
| 1 | -1 | 3 | 4 | -1 + 0 + 1 = 0 | match, record, `l = 4` | {{-1,-1,2},{-1,0,1}} |
| 2 | -1 | | | | same as previous, skipped | |
| 3 | 0 | 4 | 5 | 0 + 1 + 2 = 3 | > 0, `r = 4`, loop ends | |
| 4, 5 | | | | | not enough elements on the right | |

Result: `{{-1,-1,2},{-1,0,1}}`.

---

## Why It Works

**Fixing `i`:** after sorting, every triplet `(a, b, c)` with `a <= b <= c` is found when `a` is the fixed element. Skipping `i` when `nums[i] == nums[i - 1]` means each distinct value of `a` is used as the first element only once, so duplicate triplets starting with the same `a` can't appear.

**Two pointers:** for a fixed `a`, if `a + nums[l] + nums[r]` is too large, `nums[r]` cannot pair with *any* `l' >= l` (they are all at least as large as `nums[l]`), so `r` can be discarded. The same reasoning applies symmetrically when the sum is too small.

**After a match:** advancing `l` past equal values prevents the same `(a, b, c)` from being recorded twice. `r` doesn't need its own skip loop, because once `l` has moved to a larger value, the old `r` gives a sum above 0, and the usual `r--` move takes care of it.

---

## C++ Specific Notes

- **Correction to my Python notes:** I said the check `nums[l] == nums[l - 1] and l < r` could index out of range. It can't, because a match happens only when `l < r`, so after `l++` we have `l <= r <= n - 1`. Putting `l < r` first is still the better habit, since it short-circuits before the indexing and doesn't depend on that reasoning.
- **Overflow:** values are at most 10^5, so a three-element sum is at most 3 x 10^5 and fits easily in `int`.
- **`push_back({a, b, c})`** builds a `vector<int>` from a braced list directly into the result.
- **`int n = nums.size();`** avoids the signed/unsigned comparison warning. It also matters for `n - 2`: with `size_t`, a vector smaller than 2 elements would wrap to a huge value and the loop would run wild.
- **Sorting mutates the input:** the signature takes `vector<int>&`, so the caller's vector gets reordered. Copy it first if that matters.
- **`std::sort` space:** it is an in-place introsort, using O(log n) stack space.
- **`set<vector<int>>`** works in the brute force because `vector` defines `operator<`. `unordered_set<vector<int>>` does not compile, since there is no default hash for vectors.
- **Return by value:** `return res;` is moved or elided, so there is no copy.

---

## Edge Cases and Pitfalls

- **All zeros** (`[0,0,0,0]`): the answer is a single `{0,0,0}`. The duplicate skips prevent repeats.
- **No solution** (`[0,1,1]`): returns an empty vector.
- **Fewer than 3 elements:** the constraints rule it out, but the loops would simply find nothing.
- **Duplicates must be skipped, not filtered afterward.** Dedupe on the fly with sorting, which is cheaper than building a set of vectors.
- **Compare with the previous element, not the next.** The check is `nums[i] == nums[i - 1]`. Comparing with `nums[i + 1]` would skip the first copy and miss triplets like `{-1,-1,2}`, which need two equal values.
- **Skip check order:** write `l < r && nums[l] == nums[l - 1]`, with the bounds check first.
- **Forgetting to move `l` after a match:** this loops forever, since neither pointer changes.
- **Returning indices instead of values:** a different problem. Sorting loses the original positions, so you would sort `(value, index)` pairs.

---

## Interview Follow-Ups

- **"Can you do better than O(n²)?"** Not in general. 3Sum is the classic problem conjectured to need about quadratic time.
- **"What if you need 4 numbers (4Sum), or k numbers?"** Sort, fix k - 2 elements with nested loops, then two pointers, giving O(n^(k-1)). Use recursion for general k (LC 18), and use `long long` since sums can overflow `int`.
- **"What if the target isn't 0?"** Replace `0` with `target`, and everything else stays the same.
- **"Find the triplet closest to the target."** Same two-pointer structure, tracking the smallest `abs(sum - target)` (LC 16).
- **"Count triplets with sum less than the target."** When `sum < target`, every index between `l` and `r` also works, so add `r - l` (LC 259).
- **"What if the input can't be modified?"** Copy and sort, using O(n) extra space.
- **"Return indices instead of values?"** Sort an array of `(value, index)` pairs.

---

## Related Problems

- **1. Two Sum:** the hash map version of the inner problem
- **167. Two Sum II (Input Array Is Sorted):** the two-pointer sweep used here
- **16. 3Sum Closest:** the same sweep tracking the closest sum
- **18. 4Sum:** one more nested loop
- **259. 3Sum Smaller:** counting with two pointers
- **454. 4Sum II:** hash map of pair sums
- **11. Container With Most Water:** two pointers from both ends
- **42. Trapping Rain Water:** two pointers with running maxima

---
