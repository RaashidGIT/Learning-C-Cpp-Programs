# 11. Container With Most Water (C++)

**Difficulty:** Medium | **Topics:** Array, Two Pointers, Greedy

**Link:** https://leetcode.com/problems/container-with-most-water/

---

## Problem Description

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that, together with the x-axis, form a container that holds the **most water**. Return the maximum amount of water a container can store. You may not slant the container.

**Example 1**
```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The lines at index 1 (height 8) and index 8 (height 7) give
width 7 x min height 7 = 49.
```

**Example 2**
```
Input: height = [1,1]
Output: 1
```

**Constraints**
- `n == height.length`
- `2 <= n <= 10^5`
- `0 <= height[i] <= 10^4`

---

## Intuition and Key Insight

The water held between lines `l` and `r` is:

```
area = (r - l) x min(height[l], height[r])
```

The water level is capped by the **shorter** line, and the width is the distance between them.

Start with the **widest** container (`l = 0`, `r = n - 1`). From here, moving either pointer inward shrinks the width, so the only way to get a larger area is to find a taller **shorter side**. That tells you which pointer to move: the one at the **shorter line**. Moving the taller one can never help, because the area is still capped by the same short line while the width has shrunk.

**Pattern to recognize:** "maximize a function of two indices where one factor shrinks as they move inward" → two pointers from the ends, discarding the side that cannot improve the answer.

---

## Approaches

### 1. Brute Force: Try Every Pair

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int res = 0;
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                int area = (r - l) * min(height[l], height[r]);
                res = max(res, area);
            }
        }
        return res;
    }
};
```

- **Time:** O(n²)
- **Space:** O(1)
- **Verdict:** Correct, but with n up to 10^5 that is about 5 x 10^9 pair checks, so it gets Time Limit Exceeded on LeetCode. Mention it as the baseline, then optimize.

### 2. Two Pointers with Skipping (Minor Optimization)

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int res = 0;
        while (l < r) {
            int h = min(height[l], height[r]);
            res = max(res, (r - l) * h);
            // skip lines that are no taller than the one we just used
            if (height[l] < height[r]) {
                while (l < r && height[l] <= h) l++;
            } else {
                while (l < r && height[r] <= h) r--;
            }
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(1)
- **Verdict:** Same idea as approach 3, but it skips lines that cannot beat the current height, since they have a smaller width and no greater height. It is a small constant-factor gain and not needed in an interview.

### 3. Two Pointers (Optimal)

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;
        int l = 0, r = height.size() - 1;       // start with the widest container

        while (l < r) {
            int area = (r - l) * min(height[l], height[r]);
            res = max(res, area);

            if (height[l] < height[r]) {        // left line is the bottleneck
                l++;                            // only a taller left line can help
            } else {                            // right line is the bottleneck (or tie)
                r--;
            }
        }

        return res;
    }
};
```

- **Time:** O(n), since each iteration moves a pointer inward and they meet after n - 1 steps
- **Space:** O(1)
- **Verdict:** Optimal. This is the expected interview answer.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | TLE on large inputs |
| Two pointers + skipping | O(n) | O(1) | Small constant-factor gain |
| **Two pointers** | **O(n)** | **O(1)** | **Optimal, simplest** |

---

## Walkthrough (Two Pointers)

`height = [1, 8, 6, 2, 5, 4, 8, 3, 7]`

| l | r | min height | width | area | best | Move |
|---|---|---|---|---|---|---|
| 0 | 8 | min(1,7) = 1 | 8 | 8 | 8 | left is shorter, `l = 1` |
| 1 | 8 | min(8,7) = 7 | 7 | 49 | **49** | right is shorter, `r = 7` |
| 1 | 7 | min(8,3) = 3 | 6 | 18 | 49 | `r = 6` |
| 1 | 6 | min(8,8) = 8 | 5 | 40 | 49 | tie, `r = 5` |
| 1 | 5 | min(8,4) = 4 | 4 | 16 | 49 | `r = 4` |
| 1 | 4 | min(8,5) = 5 | 3 | 15 | 49 | `r = 3` |
| 1 | 3 | min(8,2) = 2 | 2 | 4 | 49 | `r = 2` |
| 1 | 2 | min(8,6) = 6 | 1 | 6 | 49 | `r = 1`, loop ends |

Result: `49`.

---

## Why Moving the Shorter Pointer Is Safe

Suppose `height[l] < height[r]`. Consider the line at `l` paired with any `r'` where `l < r' < r`.
- Its width `r' - l` is smaller than `r - l`.
- Its height is still at most `height[l]`, since `height[l]` is the shorter side limit.

So every such pair has an area **no greater** than the pair `(l, r)` we have just measured. Line `l` has no better partner available, so we can discard it with `l++` and lose nothing. The same argument applies symmetrically on the right side.

Moving the taller pointer would be unsafe, because it could discard the pair that gives the answer.

---

## C++ Specific Notes

- **Overflow:** the largest possible area is about 10^5 x 10^4 = 10^9, which fits in `int` (max about 2.147 x 10^9). `long long` is only needed if the constraints grow.
- **`height.size() - 1` is unsigned:** assigning it to an `int` is fine here since `n >= 2`. On an empty vector it would wrap to a huge value.
- **Use `int` for `l` and `r`:** with `size_t`, expressions like `r - l` stay safe (since `r > l`), but decrementing `r` below zero would wrap around. `int` avoids that class of bug.
- **`min` and `max`** come from `<algorithm>`. LeetCode includes it for you, but add it in your own setup.
- **Both arguments must have the same type:** `min(height[l], height[r])` is fine because both are `int`. Mixing `int` and `long long` fails to compile.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. These solutions do not modify the input.

---

## Edge Cases and Pitfalls

- **Two lines** (`[1,1]`): one iteration, area `1 x 1 = 1`.
- **Zero heights** (`[0,0]` or `[0,5,0]`): area can be `0`. `res` starts at `0`, which handles it.
- **Tie in heights:** either pointer can move. Moving `r` in the `else` branch is fine, and moving both is also valid.
- **Strictly increasing or decreasing heights:** the algorithm still runs in O(n), because it never reconsiders a pointer.
- **Confusing this with Trapping Rain Water (LC 42):** here the container has only two walls and no interior bars matter. In LC 42 every bar contributes.
- **Moving the wrong pointer:** moving the taller one is the classic mistake, and it gives wrong answers.
- **Pointer direction slips:** the left pointer only ever increases and the right pointer only ever decreases. Moving `r` upward pushes it past the end of the vector, which is undefined behavior in C++.
- **Return value:** the area, not the indices of the lines.

---

## Interview Follow-Ups

- **"Why does moving the shorter side work?"** Give the proof above: the discarded line can only form smaller areas with the remaining partners.
- **"Can you return the indices of the two lines?"** Store `{l, r}` whenever `res` improves.
- **"What if you can slant the container?"** Then the water level is the lower of the two ends and the problem changes, so clarify the constraints with the interviewer.
- **"What if the lines have thickness?"** Width becomes the distance minus the thicknesses of the lines, but the greedy argument still applies.
- **"What if the input is sorted?"** The best container is formed by the widest pair at the largest heights, which is a much simpler case.
- **"Can you do better than O(n)?"** No. Any algorithm must read every height at least once.

---

## Related Problems

- **42. Trapping Rain Water:** prefix/suffix maxima or two pointers, where every bar contributes
- **167. Two Sum II (Input Array Is Sorted):** two pointers from the ends
- **15. 3Sum:** sort + two pointers
- **16. 3Sum Closest:** two pointers with a target
- **125. Valid Palindrome:** two pointers from both ends
- **84. Largest Rectangle in Histogram:** stack-based, a different area-maximization pattern
- **1793. Maximum Score of a Good Subarray:** two pointers expanding outward

---

Send the next problem when you're ready. With 1, 11, 49, 53, 121, 217 and 238 done in both languages, I can also merge everything into one study document whenever you like.
