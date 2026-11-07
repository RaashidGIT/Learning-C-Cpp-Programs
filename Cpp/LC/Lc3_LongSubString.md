# 3. Longest Substring Without Repeating Characters (C++)

**Difficulty:** Medium | **Topics:** Hash Table, String, Sliding Window

**Link:** https://leetcode.com/problems/longest-substring-without-repeating-characters/

---

## Problem Description

Given a string `s`, find the length of the **longest substring** without repeating characters.

A substring is a contiguous, non-empty sequence of characters within the string.

**Example 1**
```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

**Example 2**
```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

**Example 3**
```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

**Constraints**
- `0 <= s.length <= 5 * 10^4`
- `s` consists of English letters, digits, symbols and spaces.

---

## Intuition and Key Insight

Maintain a **window** `[l, r]` that always contains unique characters. Expand it by moving `r` one step at a time. When `s[r]` is already inside the window, shrink from the left until the duplicate is gone, then add `s[r]`. The answer is the largest window size seen.

A set tells you in O(1) whether a character is currently in the window. Each character is added once and removed at most once, so the total work is linear.

**Pattern to recognize:** "longest/shortest contiguous segment satisfying a condition" → sliding window with two pointers and a structure tracking the window's contents.

---

## Approaches

### 1. Brute Force: Check Every Substring

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            unordered_set<char> seen;
            for (int j = i; j < n; j++) {
                if (seen.count(s[j])) break;        // duplicate found, stop extending
                seen.insert(s[j]);
                res = max(res, j - i + 1);
            }
        }
        return res;
    }
};
```

- **Time:** O(n²), for each start `i`, extend until a duplicate appears (the naive version that checks every substring for uniqueness is O(n³))
- **Space:** O(min(n, m)), where m is the alphabet size
- **Verdict:** Passes on LeetCode for n up to 5 x 10^4 in many cases, but it is the baseline to beat. Mention it, then optimize.

### 2. Sliding Window with Set

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;                // characters currently in the window
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            while (charSet.count(s[r])) {           // duplicate: shrink from the left
                charSet.erase(s[l]);
                l++;
            }
            charSet.insert(s[r]);                   // window is now unique again
            res = max(res, r - l + 1);              // update best window size
        }
        return res;
    }
};
```

- **Time:** O(n), since `l` and `r` each move at most n times, so every character is added and removed at most once
- **Space:** O(min(n, m)), where m is the size of the character set (at most about 128 for ASCII)
- **Verdict:** Optimal in time and the standard interview answer. It is easy to reason about.

### 3. Sliding Window with Hash Map (Jump the Left Pointer, Optimal)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastSeen;          // char -> most recent index
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            auto it = lastSeen.find(s[r]);
            if (it != lastSeen.end() && it->second >= l) {
                l = it->second + 1;                 // jump past the previous occurrence
            }
            lastSeen[s[r]] = r;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
```

- **Time:** O(n), one pass with no inner `while` loop
- **Space:** O(min(n, m))
- **Verdict:** Same complexity as the set version, but `l` jumps directly instead of creeping one step at a time. The `it->second >= l` check is essential, because the map may hold stale indices from before the window.

### 4. Fixed-Size Array Variant (Fastest in Practice)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int last[256];
        fill(begin(last), end(last), -1);           // -1 means "never seen"
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            unsigned char c = s[r];                 // avoids negative indices for non-ASCII bytes
            if (last[c] >= l) {
                l = last[c] + 1;
            }
            last[c] = r;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
```

- **Time:** O(n)
- **Space:** O(1), since the array has a fixed 256 slots
- **Verdict:** A micro-optimization that avoids hashing. It treats the string as bytes, which covers all of ASCII and extended ASCII.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n²) | O(min(n, m)) | Baseline |
| **Sliding window + set** | **O(n)** | **O(min(n, m))** | **Optimal, simplest to explain** |
| Sliding window + last-seen map | **O(n)** | O(min(n, m)) | **Optimal, left pointer jumps** |
| Last-seen array (256) | O(n) | O(1) | Fastest in practice |

*Here m is the size of the alphabet.*

---

## Walkthrough (Set Version)

`s = "abcabcbb"`

| r | s[r] | Duplicate? | Shrink action | Window | charSet | res |
|---|---|---|---|---|---|---|
| 0 | a | No | none | "a" | {a} | 1 |
| 1 | b | No | none | "ab" | {a,b} | 2 |
| 2 | c | No | none | "abc" | {a,b,c} | **3** |
| 3 | a | **Yes** | remove a, `l = 1` | "bca" | {b,c,a} | 3 |
| 4 | b | **Yes** | remove b, `l = 2` | "cab" | {c,a,b} | 3 |
| 5 | c | **Yes** | remove c, `l = 3` | "abc" | {a,b,c} | 3 |
| 6 | b | **Yes** | remove a, b, `l = 5` | "cb" | {c,b} | 3 |
| 7 | b | **Yes** | remove c, b, `l = 7` | "b" | {b} | 3 |

Result: `3`.

---

## Why It Works

At the end of each iteration of the outer loop, the window `s[l..r]` contains no duplicates. The `while` loop removes characters from the left only until `s[r]` is no longer in the set, which gives the **largest** valid window ending at `r` (shrinking more would only lose length). Taking the maximum over all `r` therefore covers the optimal substring, since the optimal substring ends at some `r`.

The window never moves left, and `l` never passes `r`, because once `s[r]` has been removed from the set the loop stops.

---

## C++ Specific Notes

- **`s.size()` is unsigned:** `r < s.size()` compares `int` with `size_t`. It is fine here because `r` is never negative, but it triggers a sign-compare warning. Writing `int n = s.size();` first avoids it.
- **Pass by value vs reference:** LeetCode's signature takes `string s` by value, which copies the string. In your own code, `const string& s` avoids the copy.
- **`char` may be signed:** on most platforms `char` is signed, so characters with values above 127 become negative. Indexing an array with a negative value is undefined behavior, which is why the array version casts to `unsigned char`.
- **`count` vs `find`:** `charSet.count(x)` returns 0 or 1 for a set and is fine for membership checks. For maps, use `find` so you don't insert by accident.
- **Don't read with `lastSeen[c]`:** `operator[]` on a missing key inserts a default value of 0, and index 0 is a valid index, which silently breaks the logic. Use `find`, as in approach 3.
- **`fill(begin(last), end(last), -1)`** initializes the array. `memset(last, -1, sizeof(last))` also works for -1, since all bytes become 0xFF, but it only works for 0 and -1.
- **Hashing overhead:** `unordered_set` and `unordered_map` have real constant-factor costs. For small alphabets, the fixed array version is noticeably faster.
- **Empty string:** `s.size()` is 0, so the loop doesn't run and the function returns 0.

---

## Edge Cases and Pitfalls

- **Empty string** (`""`): the loop doesn't run and the answer is `0`.
- **Single character** (`"a"`): answer is `1`.
- **All identical** (`"bbbbb"`): answer is `1`.
- **All unique** (`"abcdef"`): the whole string, answer is `6`.
- **Substring vs subsequence:** `"pwwkew"` gives `3` (`"wke"`), not `4`. The characters must be contiguous.
- **Spaces and symbols count** as characters, so don't strip them.
- **Update `res` after inserting `s[r]`**, so the window size includes the current character: `r - l + 1`.
- **Stale indices in the map version:** without the `it->second >= l` check, a character seen long before the window would wrongly pull `l` backward. For `"abba"`, this check is what prevents the bug at the final `a`.
- **Use `while`, not `if`,** in the set version. A single removal is not always enough, as the `"abcabcbb"` row at `r = 6` shows.

---

## Interview Follow-Ups

- **"Can you avoid the inner `while` loop?"** Yes, store each character's last index and jump `l` directly (approach 3).
- **"Return the substring itself, not just its length."** Track `start = l` whenever `res` improves, then return `s.substr(start, res)`.
- **"What if at most k distinct characters are allowed?"** Use a hash map of counts and shrink while the number of distinct keys exceeds k (LC 340).
- **"What if at most two distinct characters?"** The same as above with k = 2 (LC 159).
- **"What if the input is a stream?"** The last-seen map version works, since it only needs the current window state.
- **"What about Unicode?"** Use a map keyed by code point. A `std::string` holds bytes (UTF-8), so a multi-byte character spans several `char`s and needs decoding first.
- **"Can you do better than O(n)?"** No, you must read every character at least once.

---

## Related Problems

- **159. Longest Substring with At Most Two Distinct Characters:** sliding window with counts
- **340. Longest Substring with At Most K Distinct Characters:** same, generalized
- **424. Longest Repeating Character Replacement:** sliding window with a max-frequency count
- **438. Find All Anagrams in a String:** fixed-size sliding window
- **567. Permutation in String:** fixed-size sliding window
- **76. Minimum Window Substring:** variable window with required counts
- **209. Minimum Size Subarray Sum:** variable window over numbers
- **121. Best Time to Buy and Sell Stock:** two pointers in a similar style

---
