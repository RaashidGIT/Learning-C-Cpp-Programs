# 1. Two Sum (C++)

**Difficulty:** Easy | **Topics:** Array, Hash Table

**Link:** https://leetcode.com/problems/two-sum/

---

## Problem Description

Given an array of integers `nums` and an integer `target`, return the **indices** of the two numbers that add up to `target`.

You may assume that each input has **exactly one solution**, and you may not use the same element twice. You can return the answer in any order.

**Example 1**
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] == 9
```

**Example 2**
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Example 3**
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

**Constraints**
- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- Only one valid answer exists.

**Follow-up:** Can you come up with an algorithm that is less than O(n²) time complexity?

---

## Intuition and Key Insight

For each number `x`, you need to know whether `target - x` (its **complement**) exists elsewhere in the array. Searching the array for every element is the O(n²) brute force. A hash map turns "does the complement exist, and where?" into an O(1) lookup.

The key trick is to **build the map as you go**. When you reach index `i`, any valid partner at an earlier index is already in the map. Every pair is therefore found when its second element is processed, with no second pass.

**Pattern to recognize:** "find a pair/element satisfying a relation with the current element" → store what you've seen in a hash map (value → index) and look up the complement.

---

## Approaches

### 1. Brute Force: Check Every Pair

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
```

- **Time:** O(n²)
- **Space:** O(1)
- **Verdict:** With n up to 10^4 this is about 5 x 10^7 comparisons, which passes on LeetCode but is exactly what the follow-up asks you to beat. Mention it as the baseline, then optimize.
- **Overflow note:** `nums[i] + nums[j]` can reach ±2 x 10^9, which exceeds `INT_MAX` (about 2.147 x 10^9) only at the extremes, and the constraints keep it just inside range for a single sum of two values. Using `long long` is still the safer habit.

### 2. Sorting + Two Pointers

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<pair<int, int>> v;               // (value, original index)
        v.reserve(n);
        for (int i = 0; i < n; i++) v.push_back({nums[i], i});

        sort(v.begin(), v.end());               // sorts by value first

        int l = 0, r = n - 1;
        while (l < r) {
            long long sum = (long long)v[l].first + v[r].first;
            if (sum == target) return {v[l].second, v[r].second};
            if (sum < target) l++;              // need a bigger sum
            else r--;                           // need a smaller sum
        }
        return {};
    }
};
```

- **Time:** O(n log n), dominated by the sort
- **Space:** O(n) for the (value, index) pairs
- **Verdict:** Slower than the hash map, and the index bookkeeping costs O(n) space anyway. It is still worth knowing because it is the exact technique for sorted input (LC 167), where it needs only O(1) space.

### 3. Hash Map, Two Passes

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indexOf;        // value -> index
        indexOf.reserve(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            indexOf[nums[i]] = i;               // pass 1: build (keeps LAST index for duplicates)
        }
        for (int i = 0; i < nums.size(); i++) {
            auto it = indexOf.find(target - nums[i]);
            if (it != indexOf.end() && it->second != i) {   // must not reuse the same element
                return {i, it->second};
            }
        }
        return {};
    }
};
```

- **Time:** O(n) average
- **Space:** O(n)
- **Verdict:** Correct and linear, but it needs the `it->second != i` guard and makes two passes. The `[3,3]` case works because the map keeps the **last** index for duplicate values (index 1), so the lookup from `i = 0` finds index 1.

### 4. Hash Map, One Pass (Optimal)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;           // value -> index
        seen.reserve(nums.size());              // avoid rehashing as the map grows
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            auto it = seen.find(complement);    // O(1) average lookup
            if (it != seen.end()) {
                return {it->second, i};         // earlier index first
            }
            seen[nums[i]] = i;                  // insert AFTER checking
        }
        return {};                              // unreachable: a solution is guaranteed
    }
};
```

- **Time:** O(n) average, one pass with O(1) average lookups and inserts
- **Space:** O(n), since the map holds up to n - 1 entries before the answer is found
- **Verdict:** This is the expected interview answer. Checking before inserting means an element can never match itself, so no index guard is needed, and it exits early.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | Passes here, but the follow-up wants better |
| Sort + two pointers | O(n log n) | O(n) | Must track original indices |
| Hash map (two pass) | O(n) avg | O(n) | Needs the same-index guard |
| **Hash map (one pass)** | **O(n) avg** | **O(n)** | **Optimal, early exit, simplest logic** |

---

## Walkthrough (One-Pass Hash Map)

`nums = [2, 7, 11, 15]`, `target = 9`

| i | nums[i] | complement | In `seen`? | Action | `seen` |
|---|---|---|---|---|---|
| 0 | 2 | 7 | No | store `2 -> 0` | {2: 0} |
| 1 | 7 | 2 | **Yes** (index 0) | return `{0, 1}` | |

Duplicate case, `nums = [3, 3]`, `target = 6`:

| i | nums[i] | complement | In `seen`? | Action | `seen` |
|---|---|---|---|---|---|
| 0 | 3 | 3 | No (map is empty) | store `3 -> 0` | {3: 0} |
| 1 | 3 | 3 | **Yes** (index 0) | return `{0, 1}` | |

---

## C++ Specific Notes

- **`find` vs `count` vs `operator[]`:** use `find` for lookups. `seen[x]` on a missing key **inserts** a default value (0), which silently corrupts the map. Using `operator[]` to *read* is a classic bug, because index 0 is also a valid index.
- **`reserve(n)`** prevents repeated rehashing and noticeably speeds up large inputs.
- **`it->second` vs `it.second`:** an iterator needs `->`. Using `.second` on an iterator is a compile error.
- **Return braces:** `return {a, b};` constructs a `vector<int>` directly. `return {};` returns an empty vector.
- **`size()` is unsigned:** `i < nums.size()` compares `int` with `size_t`. It is fine here since `i` is never negative, but it triggers warnings and can bite you in loops that count downward.
- **`unordered_map` worst case** is O(n) per operation with heavy collisions, which makes the total O(n²). This isn't a concern on LeetCode, but it is the "average" qualifier an interviewer may probe. `std::map` is the guaranteed O(log n) alternative, for O(n log n) total.
- **Overflow:** `target - nums[i]` ranges within about ±2 x 10^9, which sits at the edge of `int` range (about ±2.147 x 10^9). It is safe under these constraints, but use `long long` for the complement if you want to be defensive, and then convert carefully when looking up.

---

## Edge Cases and Pitfalls

- **Same element twice** (`nums = [3,2,4]`, `target = 6`): `3 + 3 = 6`, but there is only one 3, so the answer is `{1, 2}` (2 + 4), not `{0, 0}`. Checking before inserting prevents this.
- **Duplicate values** (`[3,3]`, target 6): valid, because they are two different indices. The one-pass version handles this naturally.
- **Return indices, not values.** This is a common slip, and it's why sorting needs extra bookkeeping.
- **Negative numbers and zero:** no special handling. `[-3, 4, 3, 90]` with target 0 gives `{0, 2}`, and `[0, 4, 3, 0]` with target 0 gives `{0, 3}`.
- **Insert after the lookup.** If you insert `nums[i]` first, an element can match itself and `[3,2,4]` with target 6 would wrongly return `{0, 0}`.
- **Don't read with `seen[x]`.** See the C++ notes above.

---

## Interview Follow-Ups

- **"What if the array is sorted?"** Use two pointers in O(n) time and O(1) space (LC 167).
- **"What if there can be multiple solutions, or you need all pairs?"** Use a map of value → vector of indices, or sort and use two pointers while skipping duplicates (the pattern in 3Sum).
- **"What if memory is constrained?"** Sort with two pointers, accepting O(n log n) time. If you need original indices you must still store them, so the savings only apply when you need the values, not the indices.
- **"What if numbers arrive as a stream?"** This is a data structure design problem (LC 170): store counts in a hash map, so `add` is O(1) and `find` is O(n).
- **"What if the array is too large for memory?"** Hash-partition the values by `x` and `target - x` into the same bucket, so each pair lands together, then solve each bucket in memory.

---

## Related Problems

- **167. Two Sum II (Input Array Is Sorted):** two pointers, O(1) space
- **15. 3Sum:** sort + two pointers, skipping duplicates
- **18. 4Sum:** generalization of 3Sum
- **653. Two Sum IV (BST):** the same idea on a binary search tree
- **170. Two Sum III (Data Structure Design):** streaming version
- **560. Subarray Sum Equals K:** prefix sums with a hash map, the same "look up the complement" idea
- **454. 4Sum II:** split into two halves and use a hash map of pair sums

---

Send the next problem when you're ready. I can also merge the Python and C++ versions of 1 and 217 into one combined study document whenever you like.
