# 238. Product of Array Except Self (C++)

**Difficulty:** Medium | **Topics:** Array, Prefix Sum

**Link:** https://leetcode.com/problems/product-of-array-except-self/

---

## Problem Description

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` **except** `nums[i]`.

The product of any prefix or suffix of `nums` is **guaranteed** to fit in a 32-bit integer.

You must write an algorithm that runs in **O(n) time** and **without using the division operation**.

**Example 1**
```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

**Example 2**
```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

**Constraints**
- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- The product of any prefix or suffix of `nums` fits in a 32-bit integer.

**Follow-up:** Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)

---

## Intuition and Key Insight

The product of everything except `nums[i]` splits into two independent parts:

```
answer[i] = (product of everything to the LEFT of i) x (product of everything to the RIGHT of i)
```

Each part is a running product, so both can be computed in a single sweep: one left to right (prefix), one right to left (suffix). Division would be the obvious shortcut (total product divided by `nums[i]`), but it is banned, and it also breaks on zeros.

The optimal solution does this in two passes and reuses the output array to store the prefix products, so no extra arrays are needed. That is the O(1) extra space follow-up.

**Pattern to recognize:** "result at i depends on everything except i" → prefix and suffix aggregates, combined at each index.

---

## Approaches

### 1. Brute Force: Multiply Everything Except i

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            int prod = 1;
            for (int j = 0; j < n; j++) {
                if (j != i) prod *= nums[j];
            }
            res[i] = prod;
        }
        return res;
    }
};
```

- **Time:** O(n²)
- **Space:** O(1) extra (output excluded)
- **Verdict:** With n up to 10^5 this is about 10^10 operations, so it will time out. It also violates the O(n) requirement. Mention it as the baseline.
- **Overflow warning:** the product of *all but one* element is not guaranteed to fit in 32 bits, only prefix and suffix products are. The final answer values are products of a prefix and a suffix together, which the problem statement's guarantee is intended to cover, but intermediate products here can behave differently. This is another reason to prefer prefix/suffix.

### 2. Division (Rejected by the Problem)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        long long total = 1;
        int zeros = 0;
        for (int x : nums) {
            if (x == 0) zeros++;
            else total *= x;
        }

        vector<int> res(n, 0);
        if (zeros > 1) return res;                  // everything is 0
        for (int i = 0; i < n; i++) {
            if (zeros == 1) {
                if (nums[i] == 0) res[i] = total;   // only the zero's slot is non-zero
            } else {
                res[i] = total / nums[i];
            }
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(1) extra
- **Verdict:** Not allowed, because the problem forbids division. It is still worth knowing because interviewers often start here and then ask you to remove division. The zero handling is the tricky part: two or more zeros make everything 0, and exactly one zero makes every position 0 except the zero's own position.
- **Overflow note:** `total` is `long long` because the full product of up to 10^5 values can be enormous. With the 32-bit guarantee only covering prefixes and suffixes, this approach is fragile in C++.

### 3. Prefix and Suffix Arrays (O(n) Extra Space)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n, 1);   // prefix[i] = product of nums[0..i-1]
        vector<int> suffix(n, 1);   // suffix[i] = product of nums[i+1..n-1]

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }

        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = prefix[i] * suffix[i];
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(n) extra, for two helper arrays
- **Verdict:** The clearest version to explain and a good first answer in an interview. Then optimize it to approach 4.

### 4. Prefix and Postfix with Output Array Reuse (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);

        int prefix = 1;
        for (int i = 0; i < n; i++) {
            res[i] = prefix;            // product of everything left of i
            prefix *= nums[i];          // extend prefix to include nums[i]
        }

        int postfix = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= postfix;          // multiply in product of everything right of i
            postfix *= nums[i];         // extend postfix to include nums[i]
        }
        return res;
    }
};
```

- **Time:** O(n), two passes
- **Space:** O(1) extra (the output array is not counted)
- **Verdict:** Optimal, and it satisfies the follow-up. The two running variables replace the two helper arrays from approach 3.

---

## Complexity Summary

| Approach | Time | Space (extra) | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(1) | TLE |
| Division | O(n) | O(1) | Not allowed, zero handling is tricky |
| Prefix + suffix arrays | O(n) | O(n) | Clearest to explain |
| **Prefix + postfix, reuse output** | **O(n)** | **O(1)** | **Optimal, meets the follow-up** |

---

## Walkthrough (Optimal Solution)

`nums = [1, 2, 3, 4]`

**Pass 1 (left to right):** write the product of everything to the left.

| i | nums[i] | res[i] = prefix | prefix after |
|---|---|---|---|
| 0 | 1 | 1 | 1 |
| 1 | 2 | 1 | 2 |
| 2 | 3 | 2 | 6 |
| 3 | 4 | 6 | 24 |

`res = [1, 1, 2, 6]`

**Pass 2 (right to left):** multiply in the product of everything to the right.

| i | nums[i] | res[i] before | postfix used | res[i] after | postfix after |
|---|---|---|---|---|---|
| 3 | 4 | 6 | 1 | 6 | 4 |
| 2 | 3 | 2 | 4 | 8 | 12 |
| 1 | 2 | 1 | 12 | 12 | 24 |
| 0 | 1 | 1 | 24 | 24 | 24 |

`res = [24, 12, 8, 6]`

---

## Here is the line-by-line breakdown:

* **`class Solution:`**
Defines the class containing the method, standard for LeetCode problems.
* **`def productExceptSelf(self, nums: list[int]) -> list[int]:`**
Defines the function that takes a list of integers (`nums`) and returns a new list of integers.
* **`res = [1] * (len(nums))`**
Creates the result array `res`, initialized with `1`s, completely matching the length of the input array.
* **`prefix = 1`**
Initializes a running multiplier for the "left side" (prefix) product. It starts at `1` because there are no elements to the left of the first item.
* **`for i in range(len(nums)):`**
Starts a forward loop to iterate through every index from left to right.
* **`res[i] = prefix`**
Sets the current position in `res` to the product of all elements that came *before* index `i`.
* **`prefix *= nums[i]`**
Updates the running `prefix` product by multiplying it by the current element, so the next index will include this number in its left-side product.
* **`postfix = 1`**
Initializes a running multiplier for the "right side" (postfix) product. It starts at `1` because there are no elements to the right of the last item.
* **`for i in range(len(nums) - 1, -1, -1):`**
Starts a backward loop from the last index (`len(nums) - 1`) down to `0`.
* **`res[i] *= postfix`**
Multiplies the existing value in `res[i]` (which currently holds the left-side product) by the `postfix` (the right-side product). This gives the final answer for that index.
* **`postfix *= nums[i]`**
Updates the running `postfix` product by multiplying it by the current element, so the next index (moving leftwards) will include this number in its right-side product.
* **`return res`**
Returns the fully populated result array.

---

## Here is the step-by-step execution for `nums = [1, 2, 3, 4]`.

**Initial Setup**

* `nums = [1, 2, 3, 4]`
* `res = [1, 1, 1, 1]` (Initialized to 1s matching the length of `nums`)

### 1. Forward Loop (Prefix Pass)

We track the product of all numbers to the *left* of the current index.

* `prefix = 1`

**i = 0 (nums[0] = 1)**

* `res[0] = prefix` ➔ `res` becomes `[1, 1, 1, 1]`
* `prefix = prefix * nums[0]` ➔ `1 * 1 = 1`

**i = 1 (nums[1] = 2)**

* `res[1] = prefix` ➔ `res` becomes `[1, 1, 1, 1]`
* `prefix = prefix * nums[1]` ➔ `1 * 2 = 2`

**i = 2 (nums[2] = 3)**

* `res[2] = prefix` ➔ `res` becomes `[1, 1, 2, 1]`
* `prefix = prefix * nums[2]` ➔ `2 * 3 = 6`

**i = 3 (nums[3] = 4)**

* `res[3] = prefix` ➔ `res` becomes `[1, 1, 2, 6]`
* `prefix = prefix * nums[3]` ➔ `6 * 4 = 24`

*State of `res` after the first loop: `[1, 1, 2, 6]*`

---

### 2. Backward Loop (Postfix Pass)

We track the product of all numbers to the *right* of the current index and multiply it with the existing `res` value.

* `postfix = 1`

**i = 3 (nums[3] = 4)**

* `res[3] = res[3] * postfix` ➔ `6 * 1 = 6` ➔ `res` remains `[1, 1, 2, 6]`
* `postfix = postfix * nums[3]` ➔ `1 * 4 = 4`

**i = 2 (nums[2] = 3)**

* `res[2] = res[2] * postfix` ➔ `2 * 4 = 8` ➔ `res` becomes `[1, 1, 8, 6]`
* `postfix = postfix * nums[2]` ➔ `4 * 3 = 12`

**i = 1 (nums[1] = 2)**

* `res[1] = res[1] * postfix` ➔ `1 * 12 = 12` ➔ `res` becomes `[1, 12, 8, 6]`
* `postfix = postfix * nums[1]` ➔ `12 * 2 = 24`

**i = 0 (nums[0] = 1)**

* `res[0] = res[0] * postfix` ➔ `1 * 24 = 24` ➔ `res` becomes `[24, 12, 8, 6]`
* `postfix = postfix * nums[0]` ➔ `24 * 1 = 24`

### Final Result

The function returns `[24, 12, 8, 6]`.

---

## Why It Works

After pass 1, `res[i]` holds the product of all elements strictly left of `i`. In pass 2, `postfix` holds the product of all elements strictly right of `i` at the moment it is applied, because it is multiplied in *before* `nums[i]` is folded into it. So `res[i]` ends up as left product x right product, which excludes `nums[i]` itself.

The order of operations inside each loop matters. Read or write first, then update the running product.

---

## C++ Specific Notes

- **Return by value is cheap:** `return res;` uses move semantics or copy elision, so there is no copy of the vector.
- **`vector<int> res(n, 1)`** allocates and fills in one step. The fill with 1 is technically redundant here, since pass 1 overwrites every slot, but it is harmless and clear.
- **Loop counter types:** `int n = nums.size();` avoids the signed/unsigned comparison warning, and it is essential for the reverse loop. With a `size_t i`, the condition `i >= 0` is always true and the loop never ends (it wraps around to a huge value). Use `int i` for downward loops.
- **Overflow of the running products:** the problem guarantees that every prefix and suffix product fits in 32-bit `int`, so `prefix` and `postfix` are safe. The *final* `res[i] *= postfix` multiplies a prefix and a suffix, and the problem also guarantees the answer fits in `int`.
- **Why `long long` in the division approach but not here:** the full product (used in the division approach) has no such guarantee, but prefix/suffix products do.
- **Pass by reference:** the signature takes `vector<int>&`, so nothing is copied. This solution does not modify the input.
- **`const` correctness:** you can't change LeetCode's signature, but in your own code `const vector<int>&` documents that the input isn't modified.

---

## Edge Cases and Pitfalls

- **One zero** (`[-1,1,0,-3,3]`): only the position of the zero gets a non-zero result (here `9`), and every other position is `0`. The prefix/postfix method handles this with no special case, unlike the division approach.
- **Two or more zeros:** every result is `0`.
- **Length 2** (`[a, b]`): result is `{b, a}`.
- **Negative numbers:** signs work out naturally.
- **Updating the running product before using it:** if you did `prefix *= nums[i]` before `res[i] = prefix`, you would include `nums[i]` itself. Use first, then update.
- **Reverse loop with `size_t`:** a classic C++ infinite-loop bug, as noted above.
- **Counting the output as extra space:** the problem explicitly excludes it. Say so in an interview to make the O(1) claim clear.

---

## Interview Follow-Ups

- **"Can you do it without division?"** Yes, that is the prefix/postfix method.
- **"Can you use O(1) extra space?"** Reuse the output array, as in approach 4.
- **"What if division were allowed?"** Compute the total product and divide, handling zeros separately as in approach 2.
- **"What if the result must be modulo a prime?"** Division then needs modular inverses, which don't exist for 0 and fail when the modulus divides an element, so prefix/suffix is the safer approach.
- **"What if the array is huge or arrives in chunks?"** Compute per-chunk products and combine prefix and suffix across chunks, which parallelizes well.
- **"Can you do it in one pass?"** Not in a single sweep, since each position needs information from both sides. Two sweeps is the practical minimum.

---

## Related Problems

- **42. Trapping Rain Water:** prefix max and suffix max arrays, the same left/right structure
- **135. Candy:** left pass and right pass over the array
- **152. Maximum Product Subarray:** product tracking with sign flips
- **724. Find Pivot Index:** prefix sum compared with suffix sum
- **560. Subarray Sum Equals K:** prefix sums with a hash map
- **1352. Product of the Last K Numbers:** prefix product design problem
- **53. Maximum Subarray:** another one-pass running-value pattern

---
