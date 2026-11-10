# 560. Subarray Sum Equals K (C++)

**Difficulty:** Medium | **Topics:** Array, Hash Table, Prefix Sum

**Link:** https://leetcode.com/problems/subarray-sum-equals-k/

---

## Problem Description 

Given an array of integers `nums` and an integer `k`, return the **total number of subarrays** whose sum equals `k`.

A subarray is a contiguous, **non-empty** sequence of elements within the array.

**Example 1**
```
Input: nums = [1,1,1], k = 2
Output: 2
Explanation: The subarrays [1,1] at indices 0..1 and 1..2 both sum to 2.
```

**Example 2**
```
Input: nums = [1,2,3], k = 3
Output: 2
Explanation: [1,2] and [3] both sum to 3.
```

**Constraints**
- `1 <= nums.length <= 2 * 10^4`
- `-1000 <= nums[i] <= 1000`
- `-10^7 <= k <= 10^7`

---

## Intuition and Key Insight

Let `prefix[i]` be the sum of the first `i` elements. The sum of the subarray `nums[j..i-1]` is `prefix[i] - prefix[j]`. We want that to equal `k`, which means:

```
prefix[j] = prefix[i] - k
```

So as you scan, for the current running sum `curSum`, you ask: **how many earlier prefix sums equal `curSum - k`?** Each one marks the start of a subarray ending here with sum `k`. A hash map of `prefix sum -> count of times seen` answers that in O(1).

This is the Two Sum idea applied to prefix sums, and it is why the approach works with **negative numbers**, where a sliding window fails (the window can't decide when to shrink).

**Pattern to recognize:** "count or find subarrays with a given sum" → prefix sums plus a hash map of counts.

---

## Approaches

### 1. Brute Force: Every Subarray

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            int total = 0;
            for (int j = i; j < n; j++) {
                total += nums[j];               // running sum of nums[i..j]
                if (total == k) res++;
            }
        }
        return res;
    }
};
```

- **Time:** O(n²) (the naive version that re-sums each subarray is O(n³))
- **Space:** O(1)
- **Verdict:** With n up to 2 x 10^4 that is about 2 x 10^8 steps, which often passes but is the baseline to beat.

### 2. Prefix Sum Array + Pair Check

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int res = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (prefix[j] - prefix[i] == k) res++;
            }
        }
        return res;
    }
};
```

- **Time:** O(n²)
- **Space:** O(n)
- **Verdict:** Not an improvement over brute force, but it is the stepping stone to the hash map version. It makes the `prefix[j] - prefix[i] = k` relation explicit.

### 3. Prefix Sum + Hash Map, One Pass (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        int curSum = 0;
        unordered_map<int, int> prefixSums;         // prefix sum -> times seen
        prefixSums.reserve(nums.size() + 1);
        prefixSums[0] = 1;                          // empty prefix: sum 0 seen once

        for (int num : nums) {
            curSum += num;
            int diff = curSum - k;                  // needed earlier prefix sum

            auto it = prefixSums.find(diff);
            if (it != prefixSums.end()) {
                res += it->second;                  // subarrays ending here that sum to k
            }
            prefixSums[curSum]++;                   // record AFTER querying
        }

        return res;
    }
};
```

- **Time:** O(n) average, one pass with O(1) average lookups
- **Space:** O(n), since the map holds up to n + 1 distinct prefix sums
- **Verdict:** Optimal and the expected interview answer.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | Baseline |
| Prefix array + pairs | O(n²) | O(n) | Stepping stone |
| **Prefix sum + hash map** | **O(n) avg** | **O(n)** | **Optimal, handles negatives** |

---

## Walkthrough (Hash Map)

`nums = [1, 2, 3]`, `k = 3`

| num | curSum | diff = curSum - k | `prefixSums` lookup | res | `prefixSums` after |
|---|---|---|---|---|---|
| (start) | 0 | | | 0 | {0: 1} |
| 1 | 1 | -2 | 0 | 0 | {0: 1, 1: 1} |
| 2 | 3 | 0 | 1 (the empty prefix) | 1 | {0: 1, 1: 1, 3: 1} |
| 3 | 6 | 3 | 1 | 2 | {0: 1, 1: 1, 3: 1, 6: 1} |

Result: `2`, for the subarrays `{1,2}` and `{3}`.

---

## Why It Works

Every subarray ending at the current index corresponds to exactly one earlier prefix (including the empty prefix). It sums to `k` precisely when that earlier prefix equals `curSum - k`. Counting how many earlier prefixes have that value counts every valid subarray ending here, and summing over all end positions counts each subarray exactly once.

**Why `prefixSums[0] = 1` at the start:** it represents the empty prefix. Without it, subarrays that start at index 0 (like `{1,2}` above, where `curSum == k`) would be missed.

**Why record after querying:** the current prefix must not match itself. If `k = 0`, recording first would count an empty subarray at every position.

---

## C++ Specific Notes

- **Overflow:** the largest possible prefix sum is 2 x 10^4 x 1000 = 2 x 10^7, and `curSum - k` is at most about 3 x 10^7 in magnitude. Both fit comfortably in `int`.
- **`operator[]` for writing is fine here:** `prefixSums[curSum]++` default-inserts 0 for a missing key and then increments, which is exactly the behavior we want for counting.
- **But use `find` for reading:** `prefixSums[diff]` would insert `diff` into the map when missing. The result would still be correct (it adds 0), but it grows the map with junk entries and slows things down.
- **`reserve(n + 1)`** avoids rehashing as the map grows.
- **`unordered_map` worst case:** with heavy collisions an operation can degrade to O(n). It is not a concern on LeetCode, but it is the "average" qualifier an interviewer may probe. `std::map` guarantees O(log n) per operation, for O(n log n) total.
- **Negative keys are fine:** `std::hash<int>` handles negative values with no special treatment.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. This solution doesn't modify the input.
- **`for (int num : nums)`** copies each int, which is fine for primitives.

---

## Edge Cases and Pitfalls

- **Negative numbers:** the main reason a sliding window fails here. A window can't know whether extending or shrinking will help, but prefix sums handle it naturally.
- **Zeros and `k = 0`** (`{0,0,0}`, `k = 0`): the answer is 6, since every non-empty subarray sums to 0. The map counts (not just presence) are what make this work.
- **Forgetting `prefixSums[0] = 1`:** misses every subarray that starts at index 0.
- **Using an `unordered_set` instead of counts:** undercounts when the same prefix sum occurs multiple times, as it does with zeros or cancelling values.
- **Updating the map before the lookup:** counts empty subarrays when `k = 0`.
- **Single element** (`{1}`, `k = 1`): answer is 1. `{1}`, `k = 2`: answer is 0.
- **Answer is a count, not the subarrays themselves.** Returning them would need the map to store index lists.

---

## Interview Follow-Ups

- **"Why doesn't a sliding window work?"** Negative numbers break its monotonicity. Sliding window only works when all elements are non-negative (compare LC 209).
- **"What if all numbers are positive?"** A sliding window gives O(n) time and O(1) space.
- **"Return the longest subarray with sum k."** Store the **first index** of each prefix sum instead of a count (LC 325).
- **"Return the subarrays themselves."** Store a vector of indices per prefix sum, though the output itself can be O(n²).
- **"What about subarray sum divisible by k?"** Track prefix sums modulo k, handling negative remainders with `((x % k) + k) % k` (LC 974).
- **"Binary arrays, equal 0s and 1s?"** Map 0 to -1 and look for sum 0 (LC 525).
- **"What if the data is a stream?"** The one-pass version works unchanged, using O(distinct prefix sums) memory.

---

## Related Problems

- **1. Two Sum:** the same "look up the complement" idea
- **325. Maximum Size Subarray Sum Equals k:** hash map of first indices
- **523. Continuous Subarray Sum:** prefix sums modulo k
- **525. Contiguous Array:** prefix sums with a 0/1 to -1/+1 mapping
- **974. Subarray Sums Divisible by K:** prefix remainders with counts
- **209. Minimum Size Subarray Sum:** sliding window, positives only
- **53. Maximum Subarray:** Kadane's, a different running-value pattern
- **930. Binary Subarrays With Sum:** prefix sums or sliding window
- **437. Path Sum III:** the same technique on a tree path

---
