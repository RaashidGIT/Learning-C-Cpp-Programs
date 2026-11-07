# 53. Maximum Subarray (C++)

**Difficulty:** Medium | **Topics:** Array, Divide and Conquer, Dynamic Programming

**Link:** https://leetcode.com/problems/maximum-subarray/

---

## Problem Description

Given an integer array `nums`, find the **subarray** (a contiguous, non-empty part of the array) with the largest sum, and return its sum.

**Example 1**
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
```

**Example 2**
```
Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
```

**Example 3**
```
Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
```

**Constraints**
- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

**Follow-up:** If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

---

## Intuition and Key Insight

At each position, you decide: **extend the current subarray, or start fresh here?**

If the running sum before the current element is negative, it can only drag the new sum down, so you are better off discarding it and starting a new subarray at the current element. If it is non-negative, keeping it never hurts.

Reset `curSum` to 0 whenever it goes negative, then add the current number. This is **Kadane's algorithm**.

**Pattern to recognize:** "best contiguous segment" → a running value that either extends or restarts, with a separate variable tracking the best seen so far.

---

## Approaches

### 1. Brute Force: Every Subarray

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int best = INT_MIN;
        for (int i = 0; i < n; i++) {
            int total = 0;
            for (int j = i; j < n; j++) {
                total += nums[j];               // running sum of nums[i..j]
                best = max(best, total);
            }
        }
        return best;
    }
};
```

- **Time:** O(n²), since the inner loop reuses the running sum instead of recomputing it (the naive version that re-sums each subarray is O(n³))
- **Space:** O(1)
- **Verdict:** With n up to 10^5 that is about 5 x 10^9 steps, so it will time out. Mention it as the baseline.

### 2. Kadane's Algorithm, Reset Style (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSub = nums[0];             // best answer so far (non-empty, so seed with nums[0])
        int curSum = 0;                   // sum of the current subarray

        for (int num : nums) {
            if (curSum < 0) {             // a negative prefix only hurts
                curSum = 0;               // drop it and start fresh
            }
            curSum += num;
            maxSub = max(maxSub, curSum);
        }

        return maxSub;
    }
};
```

- **Time:** O(n), one pass
- **Space:** O(1)
- **Verdict:** Optimal and correct. Seeding `maxSub` with `nums[0]` (or `INT_MIN`) rather than `0` is what makes the all-negative case work.

### 3. Kadane's Algorithm, DP Style

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = nums[0], best = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cur = max(nums[i], cur + nums[i]);  // extend, or restart at nums[i]
            best = max(best, cur);
        }
        return best;
    }
};
```

- **Time:** O(n)
- **Space:** O(1)
- **Verdict:** Same algorithm, framed as the recurrence `dp[i] = max(nums[i], dp[i-1] + nums[i])`, where `dp[i]` is the best sum of a subarray **ending at** `i`. This framing is easier to explain in an interview.

### 4. Divide and Conquer (the Follow-Up)

Split the array at the middle. The best subarray is one of three things: entirely in the left half, entirely in the right half, or **crossing the middle**.

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return solve(nums, 0, nums.size() - 1);
    }

private:
    int solve(vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        int mid = l + (r - l) / 2;              // avoids overflow of l + r

        // best sum of a subarray that crosses the midpoint
        int leftBest = INT_MIN, total = 0;
        for (int i = mid; i >= l; i--) {        // extend leftward from mid
            total += nums[i];
            leftBest = max(leftBest, total);
        }

        int rightBest = INT_MIN;
        total = 0;
        for (int i = mid + 1; i <= r; i++) {    // extend rightward from mid + 1
            total += nums[i];
            rightBest = max(rightBest, total);
        }

        int cross = leftBest + rightBest;
        return max({solve(nums, l, mid), solve(nums, mid + 1, r), cross});
    }
};
```

- **Time:** O(n log n), from T(n) = 2T(n/2) + O(n)
- **Space:** O(log n) for the recursion stack
- **Verdict:** Slower than Kadane's, but it is what the follow-up asks for. Returning a struct of (total, prefix, suffix, best) from each call gets this down to O(n), which is how segment trees answer range max-subarray queries.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | TLE on large inputs |
| **Kadane (reset style)** | **O(n)** | **O(1)** | **Optimal** |
| Kadane (DP style) | **O(n)** | **O(1)** | **Optimal, easiest to explain** |
| Divide and conquer | O(n log n) | O(log n) | The follow-up |

---

## Walkthrough (Reset Style)

`nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`

| num | curSum before | Reset? | curSum after | maxSub |
|---|---|---|---|---|
| -2 | 0 | No | -2 | -2 |
| 1 | -2 | **Yes** → 0 | 1 | 1 |
| -3 | 1 | No | -2 | 1 |
| 4 | -2 | **Yes** → 0 | 4 | 4 |
| -1 | 4 | No | 3 | 4 |
| 2 | 3 | No | 5 | 5 |
| 1 | 5 | No | 6 | **6** |
| -5 | 6 | No | 1 | 6 |
| 4 | 1 | No | 5 | 6 |

Result: `6`, from the subarray `[4, -1, 2, 1]`.

---

## Why the Reset Is Safe

If `curSum < 0`, any subarray that continues through the current position is strictly better off without that negative prefix, because dropping it raises its sum. So no optimal subarray needs to include it, and restarting never skips a better answer.

The check is `< 0`, not `<= 0`. Resetting on exactly 0 would also be correct (a tie either way), but `< 0` is the standard form.

---

## C++ Specific Notes

- **Overflow:** the largest possible sum is 10^5 x 10^4 = 10^9, which fits in `int` (max about 2.147 x 10^9). `long long` is only needed if the constraints grow.
- **`INT_MIN` pitfalls:** `INT_MIN` as a seed is fine for `max`, but never add to it. In the divide and conquer version, `leftBest + rightBest` is safe because both loops run at least once and replace `INT_MIN` with a real sum. If either loop could be empty, the addition would overflow.
- **`max({a, b, c})`** with an initializer list takes three arguments and needs `<algorithm>`. Nested `max(a, max(b, c))` works too.
- **`mid = l + (r - l) / 2`** is the overflow-safe midpoint habit. It isn't needed at n = 10^5, but interviewers like to see it.
- **`nums.size() - 1` is unsigned:** passing it to an `int` parameter is fine here since the constraints guarantee at least one element. On an empty vector it would wrap to a huge value.
- **`for (int num : nums)`** copies each int, which is fine. Use `const auto&` for large element types.
- **Private helper in a class:** LeetCode allows this. Define the helper below `public:` so the entry point stays at the top, or use a lambda with `std::function` if you prefer a self-contained function.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. These solutions do not modify the input.

---

## Edge Cases and Pitfalls

- **All negative** (`[-3, -1, -2]`): the answer is `-1`, the largest single element, since the subarray must be non-empty. This is why `maxSub` starts at `nums[0]` and not `0`. Initializing to `0` would wrongly return `0`.
- **Single element** (`[1]` or `[-5]`): returns that element.
- **All positive:** the whole array is the answer, and `curSum` is never reset.
- **Mixed with zeros** (`[0, -1, 0]`): returns `0`.
- **Returning the subarray itself:** track a `start` index. Set `start = i` when you reset, and record `(start, i)` whenever `maxSub` improves.
- **Seeding `maxSub = 0`:** the most common bug. It silently fails on all-negative inputs.

---

## Interview Follow-Ups

- **"Return the subarray, not just the sum."** Track the start index on resets, as above.
- **"What if the array is circular?"** Answer is `max(kadane_max, total - kadane_min)`, with a special case when all elements are negative (LC 918).
- **"What about maximum product instead of sum?"** Track both the running max and min, since a negative can flip them (LC 152).
- **"What if the subarray must have length at least k?"** Combine prefix sums with a running minimum prefix.
- **"Can you do it with divide and conquer?"** Yes, see approach 4. Mention that it is O(n log n), or O(n) with the combine-node trick.
- **"What about a 2D version?"** Fix a pair of rows, collapse to 1D, and run Kadane's, giving O(rows² x cols).

---

## Related Problems

- **121. Best Time to Buy and Sell Stock:** the same problem over the differences array
- **152. Maximum Product Subarray:** track max and min
- **918. Maximum Sum Circular Subarray:** Kadane's plus the total-minus-min trick
- **1749. Maximum Absolute Sum of Any Subarray:** run Kadane's for both max and min
- **325. Maximum Size Subarray Sum Equals k:** prefix sums with a hash map
- **560. Subarray Sum Equals K:** prefix sums with a hash map
- **238. Product of Array Except Self:** a related prefix/suffix pattern

---
