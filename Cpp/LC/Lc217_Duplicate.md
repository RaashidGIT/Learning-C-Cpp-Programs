# 217. Contains Duplicate (C++)

**Difficulty:** Easy | **Topics:** Array, Hash Table, Sorting

---

## Problem Description

Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

**Example 1**
```
Input: nums = [1,2,3,1]
Output: true
```

**Example 2**
```
Input: nums = [1,2,3,4]
Output: false
```

**Example 3**
```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

**Constraints**
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## Intuition and Key Insight

The question is "have I seen this value before?" That points to a **hash set**, which gives O(1) average lookup and insertion. Checking before inserting lets you return as soon as the first duplicate appears.

**Pattern to recognize:** existence or duplicate checks → hash set, or sort and compare neighbors.

---

## Approaches

### 1. Brute Force: Compare Every Pair

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] == nums[j]) return true;
            }
        }
        return false;
    }
};
```

- **Time:** O(n²)
- **Space:** O(1)
- **Verdict:** With n up to 10^5 that's about 10^10 comparisons, so it will time out. Mention it as the baseline, then move on.

### 2. Sorting

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) return true;
        }
        return false;
    }
};
```

- **Time:** O(n log n), dominated by the sort
- **Space:** O(log n) for `std::sort`'s recursion stack (introsort, in place). It is O(n) if you copy the array to avoid mutating the input.
- **Verdict:** A good answer when memory is tight, since it avoids the extra hash set. The tradeoff is slower time and mutating the input (the vector is passed by non-const reference).

### 3. Hash Set, Single Pass (Optimal)

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        seen.reserve(nums.size());          // avoid rehashing as the set grows
        for (int num : nums) {
            if (seen.count(num)) {          // O(1) average lookup
                return true;                // early exit on first duplicate
            }
            seen.insert(num);               // record this value
        }
        return false;                       // finished with no repeats
    }
};
```

A slightly tighter variant uses the return value of `insert`, which saves one hash lookup per element:

```cpp
for (int num : nums) {
    if (!seen.insert(num).second) return true;  // .second == false means already present
}
return false;
```

- **Time:** O(n) average, one pass with O(1) average operations
- **Space:** O(n), since the set holds up to n elements when there are no duplicates
- **Verdict:** This is the expected interview answer. The `insert(...).second` form is idiomatic C++ and worth knowing.

### 4. One-Liner

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        return s.size() != nums.size();
    }
};
```

- **Time:** O(n) average
- **Space:** O(n)
- **Verdict:** Concise, but it always builds the full set, so there is no early exit. Write approach 3 first in an interview and mention this as a shortcut.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | TLE on large inputs |
| Sorting | O(n log n) | O(log n) | Mutates input, saves memory |
| `unordered_set` (single pass) | **O(n)** avg | **O(n)** | **Optimal, early exit** |
| Construct set from range | O(n) avg | O(n) | Concise, no early exit |

---

## Walkthrough (Hash Set)

`nums = [1, 2, 3, 1]`

| Step | num | In `seen`? | Action | `seen` |
|---|---|---|---|---|
| 1 | 1 | No | insert | {1} |
| 2 | 2 | No | insert | {1, 2} |
| 3 | 3 | No | insert | {1, 2, 3} |
| 4 | 1 | **Yes** | return `true` | |

---

## C++ Specific Notes

- **`unordered_set` vs `set`:** `std::set` is a balanced tree with O(log n) operations, so the total is O(n log n). `unordered_set` is a hash table with O(1) average. Prefer `unordered_set` here, since order doesn't matter.
- **Worst case for `unordered_set` is O(n) per operation**, which makes the total O(n²). This happens with heavy hash collisions. On Codeforces-style platforms, adversarial inputs can trigger it against the default `std::hash<int>`. On LeetCode it's not a concern, but it's a good thing to mention if the interviewer pushes on "average" vs "worst".
- **`reserve(n)`** prevents repeated rehashing and speeds things up noticeably on large inputs.
- **`count()` vs `find()` vs `insert().second`:** all are valid. `insert().second` does check and insert in one hash computation.
- **Passing by reference:** the signature takes `vector<int>&` (non-const), which is why sorting in place mutates the caller's data. Copy the vector first if that matters.
- **Don't use `unordered_set` for the sorted-input follow-up.** Adjacent comparison is O(n) time and O(1) space.

---

## Edge Cases and Pitfalls

- **Single element** (`[5]`): return `false`. The loop handles it naturally.
- **All identical** (`[2,2,2,2]`): returns `true` at the second element.
- **Negative numbers and zero:** handled with no special treatment.
- **Check before inserting**, or use `insert().second`. If you insert first and then check with `count`, every element looks like a duplicate.
- **Sorting loop bounds:** start at `i = 1` and compare with `nums[i - 1]`. Starting at 0 reads `nums[-1]`, which is undefined behavior.
- **Don't use `int` overflow-prone tricks** like summing the array. Values go up to 10^9, so sums overflow.

---

## Interview Follow-Ups

- **"What if memory is limited?"** Use sorting, with O(log n) extra space at O(n log n) time.
- **"What if the array is already sorted?"** Compare adjacent elements in O(n) time and O(1) space.
- **"What if the array is too large for memory?"** Use external sorting, or hash-partition the data into buckets that fit in memory and check each bucket.
- **"What if values fall in a small known range?"** Use a `vector<bool>` or `bitset` as the lookup table.

---

## Related Problems

- **219. Contains Duplicate II:** duplicates within distance k (hash map or sliding window)
- **220. Contains Duplicate III:** duplicates within value difference t and index distance k (`std::set` with `lower_bound`, or bucketing)
- **1. Two Sum:** hash map for complement lookup
- **242. Valid Anagram:** frequency counting
- **287. Find the Duplicate Number:** O(1) space using Floyd's cycle detection
- **136. Single Number:** XOR trick

---

Send the next problem when you're ready. I can also merge the Python and C++ versions of 217 into one combined note if you'd like.
