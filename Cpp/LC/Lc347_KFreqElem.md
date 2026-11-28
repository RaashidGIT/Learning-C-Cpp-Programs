# 347. Top K Frequent Elements (C++)

**Difficulty:** Medium | **Topics:** Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect

**Link:** https://leetcode.com/problems/top-k-frequent-elements/

---

## Problem Description

Given an integer array `nums` and an integer `k`, return the **k most frequent elements**. You may return the answer in **any order**.

**Example 1**
```
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
```

**Example 2**
```
Input: nums = [1], k = 1
Output: [1]
```

**Constraints**
- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `k` is in the range `[1, the number of unique elements in the array]`.
- It is **guaranteed** that the answer is **unique**.

**Follow-up:** Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

---

## Intuition and Key Insight

Two steps: **count** how often each value appears, then **select the k values with the highest counts**.

Counting is a hash map, O(n). Selection is where the approaches differ:
- Sort all distinct values by count: O(n log n), which the follow-up forbids.
- Keep a min-heap of size k: O(n log k).
- **Bucket sort by frequency:** a value can appear at most n times, so make an array of n + 1 buckets where bucket `c` holds the values that appear exactly `c` times. Then walk from the highest bucket down and collect k values. This is O(n).

**Pattern to recognize:** "top k by frequency" → count with a hash map, then heap (O(n log k)) or bucket sort (O(n)) because frequencies are bounded by n.

---

## Approaches

### 1. Sort by Frequency

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) count[num]++;

        vector<pair<int, int>> items(count.begin(), count.end());   // (value, frequency)
        sort(items.begin(), items.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second > b.second;                        // highest frequency first
             });

        vector<int> res;
        for (int i = 0; i < k; i++) res.push_back(items[i].first);
        return res;
    }
};
```

- **Time:** O(n log n), dominated by sorting the distinct values (up to n of them)
- **Space:** O(n)
- **Verdict:** Simple and correct, but it does not satisfy the follow-up. Mention it as the baseline.

### 2. Min-Heap of Size k

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) count[num]++;

        // min-heap of (frequency, value), smallest frequency on top
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> minHeap;

        for (const auto& [num, c] : count) {
            minHeap.push({c, num});
            if (minHeap.size() > k) minHeap.pop();      // evict the least frequent of the k+1
        }

        vector<int> res;
        while (!minHeap.empty()) {
            res.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return res;
    }
};
```

- **Time:** O(n log k), since each of up to n distinct values costs O(log k)
- **Space:** O(n) for the map, O(k) for the heap
- **Verdict:** The common interview answer, and a good fit when k is much smaller than n.

### 3. Bucket Sort by Frequency (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;                  // value -> frequency
        vector<vector<int>> freq(nums.size() + 1);      // freq[c] = values appearing exactly c times

        for (int n : nums) {
            count[n]++;
        }
        for (const auto& [n, c] : count) {
            freq[c].push_back(n);
        }

        vector<int> res;
        for (int i = freq.size() - 1; i > 0; i--) {     // highest frequency first
            for (int n : freq[i]) {
                res.push_back(n);
                if (res.size() == k) return res;
            }
        }
        return res;                                     // unreachable under the constraints
    }
};
```

- **Time:** O(n), with one pass to count, one to fill buckets, and at most n + 1 buckets to scan
- **Space:** O(n) for the map and the buckets
- **Verdict:** Optimal and satisfies the follow-up. The vector has `nums.size() + 1` slots because a frequency can be anywhere from 1 to n, and index 0 is unused.

### 4. Quickselect with `nth_element`

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) count[num]++;

        vector<pair<int, int>> items(count.begin(), count.end());   // (value, frequency)
        nth_element(items.begin(), items.begin() + k - 1, items.end(),
                    [](const pair<int, int>& a, const pair<int, int>& b) {
                        return a.second > b.second;                 // highest frequency first
                    });

        vector<int> res;
        for (int i = 0; i < k; i++) res.push_back(items[i].first);
        return res;
    }
};
```

- **Time:** O(n) average, O(n²) worst case in theory (libstdc++ uses introselect, which keeps the worst case at O(n log n))
- **Space:** O(n)
- **Verdict:** `std::nth_element` does the quickselect for you, so no hand-written partition is needed. After the call, the first k items are the k most frequent, in no particular order.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Sort by frequency | O(n log n) | O(n) | Fails the follow-up |
| Min-heap of size k | O(n log k) | O(n) | Best when k is small |
| **Bucket sort** | **O(n)** | **O(n)** | **Optimal, meets follow-up** |
| `nth_element` | O(n) avg | O(n) | Short, library quickselect |

---

## Walkthrough (Bucket Sort)

`nums = {1, 1, 1, 2, 2, 3}`, `k = 2`

**Step 1: count**

`count = {1: 3, 2: 2, 3: 1}`

**Step 2: fill buckets** (`freq` has 7 slots, indices 0 to 6)

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| Values | {} | {3} | {2} | {1} | {} | {} | {} |

**Step 3: scan from the right, collecting until `res.size() == k`**

| i | freq[i] | Action | res |
|---|---|---|---|
| 6 | {} | nothing | {} |
| 5 | {} | nothing | {} |
| 4 | {} | nothing | {} |
| 3 | {1} | append 1 | {1} |
| 2 | {2} | append 2, `size == k`, **return** | {1, 2} |

Result: `{1, 2}`.

---

## Why It Works

Bucket index equals frequency, so the buckets are already sorted by frequency. Scanning from the highest index down visits values in descending order of frequency, and stopping after k values returns the k most frequent. No comparison sorting is needed because frequencies are small integers bounded by n.

**Why `n + 1` buckets:** the maximum possible frequency is n (all elements equal), so index n must exist.

**Why the loop stops at index 1:** `i > 0` excludes 0, which is fine because no value has frequency 0.

**Ties:** two values with the same frequency land in the same bucket. The problem guarantees a unique answer, so a tie never straddles the cutoff at k.

---

## C++ Specific Notes

- **Missing return is undefined behavior:** in Python, falling off the end returns `None`. In C++, a non-void function that reaches the end without `return` is undefined behavior. That is why the bucket version ends with `return res;`.
- **Signed/unsigned comparisons:** `res.size() == k` and `minHeap.size() > k` compare `size_t` with `int`. It is safe here since `k` is positive, but it triggers sign-compare warnings. Cast with `(int)` or store `size_t K = k;` if you want clean builds.
- **`int i = freq.size() - 1`:** converting to `int` first matters. If `i` were `size_t`, the condition `i > 0` would still work, but `i >= 0` in a variant would loop forever.
- **Structured bindings:** `for (const auto& [n, c] : count)` needs C++17, which LeetCode supports. Use `kv.first` and `kv.second` for older standards.
- **`count[n]++`** default-inserts 0 for a new key and then increments, which is the intended counting idiom.
- **Min-heap syntax:** `priority_queue` is a max-heap by default. For a min-heap you need `greater<pair<int,int>>` and the container type as template arguments.
- **Pairs compare lexicographically:** `(frequency, value)` orders by frequency first, which is what the heap needs. That is why frequency goes first in the pair.
- **Lambda comparators take `const&`:** by-value parameters would copy pairs on every comparison. The comparator must use `>` or `<`, never `>=` or `<=`.
- **`nth_element` position:** `items.begin() + k - 1` means the element at index `k - 1` is placed correctly, with everything before it comparing as "greater or equal frequency". The first k items are the answer, unordered.
- **Negative values:** they are only map keys, never array indices, so they cause no problem.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. These solutions do not modify the input.

---

## Edge Cases and Pitfalls

- **Single element** (`{1}`, `k = 1`): count is `{1: 1}`, bucket 1 holds `{1}`, and the function returns `{1}`.
- **All elements equal** (`{5,5,5}`, `k = 1`): frequency 3 goes in bucket 3, which is why `n + 1` buckets are needed.
- **All distinct** (`{1,2,3}`, `k = 3`): everything lands in bucket 1, and the answer is all of them.
- **Using the value as an array index:** a bug, since values can be negative. Only the frequency is used as an index.
- **Allocating only `n` buckets:** an all-equal array needs index `n`, so `freq[n]` would be out of bounds, which is undefined behavior in C++.
- **Max-heap by mistake:** the default `priority_queue` would evict the most frequent element. Use `greater<>` for the size-k min-heap.
- **Output order:** highest frequency first in the bucket version, arbitrary in the heap and `nth_element` versions. Any order is accepted.

---

## Interview Follow-Ups

- **"Why is this better than O(n log n)?"** Frequencies are integers in [1, n], so bucketing replaces the comparison sort with direct indexing.
- **"What if k is much smaller than n?"** The heap approach, O(n log k), is simple and uses a tiny heap, so either is reasonable.
- **"What if the data is a stream?"** Keep the count map and a size-k min-heap, updating on each arrival (or use a Count-Min Sketch for approximate counts with bounded memory).
- **"What if the data is too large for memory?"** Hash-partition values into chunks, count each chunk, and merge the per-chunk top-k lists (map-reduce style).
- **"Return the k least frequent?"** Scan the buckets from low to high.
- **"Top k frequent words, sorted with ties broken alphabetically?"** LC 692, using a heap with a custom comparator.
- **"Can you do better than O(n)?"** No, you must read every element.

---

## Related Problems

- **692. Top K Frequent Words:** the same idea with ordering rules
- **215. Kth Largest Element in an Array:** quickselect or heap
- **451. Sort Characters By Frequency:** bucket sort by count
- **973. K Closest Points to Origin:** heap or quickselect
- **703. Kth Largest Element in a Stream:** size-k min-heap
- **295. Find Median from Data Stream:** two heaps
- **49. Group Anagrams:** hash map grouping
- **169. Majority Element:** frequency counting (k = 1 with a threshold)

---
