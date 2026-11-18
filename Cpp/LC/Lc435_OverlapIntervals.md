# 435. Non-overlapping Intervals (C++)

**Difficulty:** Medium | **Topics:** Array, Dynamic Programming, Greedy, Sorting

**Link:** https://leetcode.com/problems/non-overlapping-intervals/

---

## Problem Description

Given an array of intervals `intervals` where `intervals[i] = [start_i, end_i]`, return the **minimum number of intervals you need to remove** so that the rest of the intervals are non-overlapping.

Intervals that only touch at an endpoint, like `[1,2]` and `[2,3]`, are **not** overlapping.

**Example 1**
```
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: Remove [1,3] and the rest are non-overlapping.
```

**Example 2**
```
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest non-overlapping.
```

**Example 3**
```
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: Already non-overlapping.
```

**Constraints**
- `1 <= intervals.length <= 10^5`
- `intervals[i].length == 2`
- `-5 * 10^4 <= start_i < end_i <= 5 * 10^4`

---

## Intuition and Key Insight

Removing the minimum number of intervals is the same as **keeping the maximum number of non-overlapping intervals**:

```
answer = n - (max number of intervals you can keep)
```

This is the classic **activity selection** problem. Whenever two intervals overlap, one of them must go. The right one to drop is the one that **ends later**, because an interval that stretches further right blocks more of the future and can never help more than the one that ends sooner.

The sort-by-start solution removes the interval with the larger end by keeping `min(end, prevEnd)` as the running end. Sorting by end is an alternative that makes the greedy choice even simpler (approach 4).

**Pattern to recognize:** "minimum removals to avoid conflicts" or "maximum number of non-conflicting intervals" → sort, then greedily keep the interval that ends earliest.

---

## Approaches

### 1. Brute Force: Recursion (Include or Exclude)

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        return n - dfs(intervals, 0, INT_MIN);
    }

private:
    // max number of intervals we can keep from index i onward
    int dfs(vector<vector<int>>& intervals, int i, int prevEnd) {
        if (i == intervals.size()) return 0;
        int skip = dfs(intervals, i + 1, prevEnd);
        int take = 0;
        if (intervals[i][0] >= prevEnd) {
            take = 1 + dfs(intervals, i + 1, intervals[i][1]);
        }
        return max(skip, take);
    }
};
```

- **Time:** O(2^n)
- **Space:** O(n) for the recursion stack
- **Verdict:** Shows the include/exclude structure but is far too slow for n up to 10^5. Mention it as the baseline.

### 2. DP (Longest Chain Ending at Each Interval)

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        vector<int> dp(n, 1);                       // dp[i] = max kept, with interval i as the last one
        int best = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (intervals[j][1] <= intervals[i][0]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            best = max(best, dp[i]);
        }
        return n - best;
    }
};
```

- **Time:** O(n²)
- **Space:** O(n)
- **Verdict:** This is the Longest Increasing Subsequence pattern, with "does not overlap" as the compatibility test. It times out at n = 10^5, but it is a good stepping stone and the base for the weighted version (LC 1235).

### 3. Greedy, Sort by Start (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());   // sort by start (ties by end)

        int res = 0;                                // intervals removed
        int prevEnd = intervals[0][1];              // end of the last interval we kept
        for (int i = 1; i < intervals.size(); i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            if (start >= prevEnd) {                 // no overlap (touching is fine)
                prevEnd = end;
            } else {                                // overlap: remove one interval
                res++;
                prevEnd = min(end, prevEnd);        // keep the one that ends sooner
            }
        }
        return res;
    }
};
```

- **Time:** O(n log n), dominated by the sort, with a single O(n) pass after it
- **Space:** O(log n) for the sort's recursion stack
- **Verdict:** Optimal and correct. The key line is `prevEnd = min(end, prevEnd)`, which is where the removal decision is made.

### 4. Greedy, Sort by End (Classic Activity Selection)

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];                // sort by end
             });

        int res = 0;
        int prevEnd = INT_MIN;
        for (const auto& iv : intervals) {
            if (iv[0] >= prevEnd) {                 // compatible: keep it
                prevEnd = iv[1];
            } else {                                // overlaps the kept one: remove this one
                res++;
            }
        }
        return res;
    }
};
```

- **Time:** O(n log n)
- **Space:** O(log n) for the sort
- **Verdict:** Equally optimal, and the easiest to prove. Because intervals are processed in order of end time, the interval we already kept always ends no later than the current one, so on a conflict you can always just drop the current one, with no `min` needed. This is the form most editorials use.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Recursion | O(2^n) | O(n) | TLE |
| DP (LIS style) | O(n²) | O(n) | TLE, base for weighted version |
| **Greedy, sort by start** | **O(n log n)** | **O(log n)** | **Optimal, remove the later-ending one** |
| **Greedy, sort by end** | **O(n log n)** | **O(log n)** | **Optimal, simplest to prove** |

---

## Walkthrough (Sort by Start)

`intervals = [[1,2],[2,3],[3,4],[1,3]]` → sorted: `[[1,2],[1,3],[2,3],[3,4]]`

Start with `prevEnd = 2` (from `[1,2]`), `res = 0`.

| interval | start >= prevEnd? | Action | prevEnd | res |
|---|---|---|---|---|
| [1,3] | 1 >= 2? **No** | overlap, `res++`, `prevEnd = min(3, 2)` | 2 | 1 |
| [2,3] | 2 >= 2? Yes | keep, `prevEnd = 3` | 3 | 1 |
| [3,4] | 3 >= 3? Yes | keep, `prevEnd = 4` | 4 | 1 |

Result: `1`.

Duplicate case, `[[1,2],[1,2],[1,2]]`: the first is kept, and each of the other two overlaps it (1 < 2), so `res = 2`.

---

## Why It Works

When two intervals overlap, at least one has to be removed, and it is always safe to remove the one with the **larger end**. Any set of future intervals that is compatible with the larger-end interval is also compatible with the smaller-end one, because the smaller-end one frees up the timeline sooner. So keeping the smaller end never excludes a better solution (an exchange argument).

In the code, `prevEnd = min(end, prevEnd)` does exactly this. It does not track which interval was removed, only the end of the interval that survives.

Why sorting by start is enough: with intervals sorted by start, the current interval's start is at least every earlier start. If it overlaps the last kept interval, it overlaps because `start < prevEnd`, and the only decision left is which of the two ends to keep.

---

## C++ Specific Notes

- **`sort` on `vector<vector<int>>`** uses lexicographic comparison by default, so it sorts by start and breaks ties by end. No custom comparator is needed for approach 3.
- **Custom comparator for sort by end:** a lambda taking `const vector<int>&` avoids copying each inner vector. Taking the parameters by value would copy two vectors on every comparison and slow the sort badly.
- **Comparator must be a strict weak ordering:** use `<`, never `<=`. A comparator that returns true for equal elements is undefined behavior and can crash.
- **`INT_MIN` as a sentinel:** fine here, since it is only compared against and never added to or subtracted from. Needs `<climits>` (LeetCode includes it).
- **`intervals.size()` is unsigned:** `i < intervals.size()` compares `int` with `size_t`. It is fine here, but `int n = intervals.size();` avoids the warning.
- **Empty input:** the constraints guarantee at least one interval, so `intervals[0]` is safe. Without that guarantee, `intervals[0][1]` on an empty vector is undefined behavior, so add `if (intervals.empty()) return 0;`.
- **Avoid copying in the loop:** `for (const auto& iv : intervals)` binds by reference. Writing `for (auto iv : intervals)` copies every inner vector.
- **Overflow:** values stay within ±5 x 10^4, so `int` is safe.
- **Input is mutated** by `sort`, since the signature takes a non-const reference. Copy first if you need the original order.

---

## Edge Cases and Pitfalls

- **Touching intervals** (`[1,2]`, `[2,3]`): not overlapping, so the check must be `start >= prevEnd`. Using `>` would wrongly count them as overlaps.
- **Identical intervals** (`[[1,2],[1,2]]`): the second overlaps the first, so one is removed.
- **One interval:** the answer is `0`, because the loop body never runs.
- **One interval nested inside another** (`[[1,10],[2,3],[4,5]]`): the greedy removes `[1,10]` by keeping the min end, giving `1`. Keeping `[1,10]` would force removing two.
- **Not updating `prevEnd` on overlap:** if you forget `min`, a long interval stays as the barrier and you remove too many (`[[1,10],[2,3],[4,5]]` would return 2).
- **Sorting by end vs by start:** both work, but with sort-by-end you must **not** use `min` logic, and with sort-by-start you must. Mixing the two causes wrong answers.
- **Counting what is kept instead of removed:** `answer = n - kept`. Be careful with off-by-one on the first interval.
- **Subtracting in a comparator:** writing `return a[1] - b[1];` can overflow for extreme values and is not a valid comparator as a bool. Use `<`.

---

## Interview Follow-Ups

- **"Why is it safe to remove the interval that ends later?"** Give the exchange argument above.
- **"Return the intervals that were removed, not just the count."** Track the interval itself instead of only `prevEnd`, and push the one with the larger end onto a result vector on each overlap.
- **"What if intervals have weights and you want maximum total weight kept?"** Greedy fails, so use DP sorted by end with binary search (`upper_bound`) to find the last compatible interval, O(n log n) (LC 1235).
- **"What if touching intervals count as overlapping?"** Change `>=` to `>`.
- **"What's the minimum number of meeting rooms needed?"** A different question, solved with a min-heap (`priority_queue`) or a sweep line (LC 253).
- **"Minimum arrows to burst balloons?"** It is the same greedy, sorting by end and counting groups (LC 452).
- **"Can you do better than O(n log n)?"** Not in general, since sorting is required. If coordinates are bounded (here within 10^5 range), a counting-based approach can reach O(n + range).

---

## Related Problems

- **452. Minimum Number of Arrows to Burst Balloons:** the same greedy, sort by end
- **646. Maximum Length of Pair Chain:** the same activity selection
- **56. Merge Intervals:** sort by start and merge
- **57. Insert Interval:** interval insertion and merging
- **252. Meeting Rooms:** detect any overlap
- **253. Meeting Rooms II:** minimum rooms, heap or sweep line
- **1235. Maximum Profit in Job Scheduling:** the weighted version (DP + binary search)
- **1353. Maximum Number of Events That Can Be Attended:** greedy with a heap
- **300. Longest Increasing Subsequence:** the DP pattern behind approach 2

---
