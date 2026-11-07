# 49. Group Anagrams (C++)

**Difficulty:** Medium | **Topics:** Array, Hash Table, String, Sorting

**Link:** https://leetcode.com/problems/group-anagrams/

---

## Problem Description

Given an array of strings `strs`, group the **anagrams** together. You can return the answer in **any order**.

An anagram is a word formed by rearranging the letters of another word, using all the original letters exactly once.

**Example 1**
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Explanation:
- There is no string in strs that can be rearranged to form "bat".
- "nat" and "tan" are anagrams, as they can be rearranged to form each other.
- "ate", "eat", and "tea" are anagrams, as they can be rearranged to form each other.
```

**Example 2**
```
Input: strs = [""]
Output: [[""]]
```

**Example 3**
```
Input: strs = ["a"]
Output: [["a"]]
```

**Constraints**
- `1 <= strs.length <= 10^4`
- `0 <= strs[i].length <= 100`
- `strs[i]` consists of lowercase English letters.

---

## Intuition and Key Insight

Two strings are anagrams exactly when they have the same **letter counts**. So if you can compute a **canonical key** that is identical for every anagram of a word, you can drop each word into a hash map under its key and read off the groups at the end.

There are two standard keys:
- **Sorted string:** `"eat"`, `"tea"` and `"ate"` all become `"aet"`. Cost is O(k log k) per word.
- **Character count key:** a 26-slot frequency array, converted into something hashable. Cost is O(k) per word.

**Pattern to recognize:** "group items that are equivalent under some rearrangement" → compute a canonical form and use it as a hash map key.

---

## Approaches

### 1. Brute Force: Compare Every Pair

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<bool> used(n, false);
        vector<vector<string>> res;

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            vector<string> group = {strs[i]};
            used[i] = true;

            string a = strs[i];
            sort(a.begin(), a.end());
            for (int j = i + 1; j < n; j++) {
                if (used[j]) continue;
                string b = strs[j];
                sort(b.begin(), b.end());
                if (a == b) {
                    group.push_back(strs[j]);
                    used[j] = true;
                }
            }
            res.push_back(group);
        }
        return res;
    }
};
```

- **Time:** O(n² x k log k), where n is the number of strings and k is the max string length
- **Space:** O(n x k) for the output
- **Verdict:** Works but is wasteful, since it compares strings pairwise instead of hashing them to a shared key. Mention it as the baseline, then optimize.

### 2. Hash Map with Sorted String as Key

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());       // all anagrams share this key
            groups[key].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& [key, group] : groups) {
            res.push_back(move(group));         // move avoids copying each group
        }
        return res;
    }
};
```

- **Time:** O(n x k log k), since each word is sorted
- **Space:** O(n x k) for the map and output
- **Verdict:** The shortest and most readable solution, and usually the first one to write in an interview. The log factor on k is tiny because k is at most 100.

### 3. Hash Map with Character Count Key (Optimal)

C++ has no built-in hash for `array<int, 26>` or `vector<int>`, so the Python `tuple(count)` trick doesn't translate directly. The simplest fix is to **encode the counts as a string** and use that as the key.

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;   // count key -> anagrams

        for (const string& s : strs) {
            int count[26] = {0};                        // one slot per letter a..z
            for (char c : s) {
                count[c - 'a']++;
            }

            string key;
            key.reserve(26 * 4);
            for (int i = 0; i < 26; i++) {
                key += to_string(count[i]);
                key += '#';                             // delimiter keeps "1,11" distinct from "11,1"
            }
            groups[key].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& [key, group] : groups) {
            res.push_back(move(group));
        }
        return res;
    }
};
```

- **Time:** O(n x (k + 26)), which is O(n x k) since the 26 is a constant. Counting is O(k) per word, and building the key is O(26).
- **Space:** O(n x k) for the output, plus O(n x 26) for the keys
- **Verdict:** Optimal, and it avoids sorting. The delimiter `#` is essential, as explained in the pitfalls below.

### 3b. Count Key as a Fixed-Length String (Compact Variant)

Counts are at most 100 here, so each fits in a single `char`. That gives a 26-character key with no delimiters.

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            string key(26, 0);                          // 26 chars, each holds a count
            for (char c : s) {
                key[c - 'a']++;
            }
            groups[key].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& [key, group] : groups) {
            res.push_back(move(group));
        }
        return res;
    }
};
```

- **Time:** O(n x k)
- **Space:** O(n x k) output, plus 26 bytes per key
- **Verdict:** The tightest and fastest version in practice. It relies on every count being at most 100, which fits in a `char` (max 127 for signed `char`). If strings could be longer than 127 characters, counts could overflow, so use the delimiter version instead.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n² x k log k) | O(n x k) | Pairwise comparison, slow |
| Sorted string key | O(n x k log k) | O(n x k) | Shortest code, easy to explain |
| **Count string key** | **O(n x k)** | **O(n x k)** | **Optimal, avoids sorting** |
| Count key, fixed 26 chars | O(n x k) | O(n x k) | Most compact, needs counts under 128 |

*Here n = number of strings and k = maximum string length.*

---

## Walkthrough (Count Key)

`strs = ["eat", "tea", "tan", "ate", "nat", "bat"]`

| s | Count key (only non-zero shown) | Map after |
|---|---|---|
| "eat" | a1 e1 t1 | {a1e1t1: ["eat"]} |
| "tea" | a1 e1 t1 | {a1e1t1: ["eat","tea"]} |
| "tan" | a1 n1 t1 | {..., a1n1t1: ["tan"]} |
| "ate" | a1 e1 t1 | {a1e1t1: ["eat","tea","ate"], ...} |
| "nat" | a1 n1 t1 | {..., a1n1t1: ["tan","nat"]} |
| "bat" | a1 b1 t1 | {..., a1b1t1: ["bat"]} |

Result: `{{"eat","tea","ate"}, {"tan","nat"}, {"bat"}}` (group order may vary, since `unordered_map` has no guaranteed iteration order).

The real key in the delimiter version is a string like `"1#0#0#0#1#0#...#1#0#0#0#0#0#"`, and the table above shows only the non-zero entries for readability.

---

## Why It Works

Two strings are anagrams if and only if their letter-frequency vectors are equal. The encoded count string is an exact fingerprint of that vector, so equal keys mean anagrams and different keys mean non-anagrams. There are no false positives (unlike a hash of the characters' sum, which can collide).

---

## C++ Specific Notes

- **No hash for arrays or vectors:** `unordered_map<array<int,26>, ...>` and `unordered_map<vector<int>, ...>` don't compile, because `std::hash` isn't defined for them. Either encode into a `string`, write a custom hash, or use `std::map<vector<int>, ...>` (which works with ordered comparison but costs O(26 log n) per lookup).
- **`std::map` alternative:** `map<vector<int>, vector<string>>` is the closest analogue to Python's tuple key. It is simpler to write but slower, O(n x (k + 26 log n)).
- **Delimiter is required** in the string-encoded key. Without it, counts `[1, 11]` and `[11, 1]` both encode as `"111"`, so different words would collide into the same group.
- **`string key(26, 0)`** creates 26 null characters (value 0), not the digit `'0'`. That is intentional, and `unordered_map<string, ...>` handles embedded nulls correctly because `std::string` stores its length.
- **Structured bindings:** `for (auto& [key, group] : groups)` needs C++17, which LeetCode supports. Use `auto& kv` and `kv.second` for older standards.
- **`move(group)`** transfers ownership of each vector into the result rather than copying. It is safe here because `groups` is discarded afterward.
- **`const string&` in the loop** avoids copying each string.
- **`c - 'a'` indexing** relies on the lowercase-only constraint. Uppercase or other characters would index out of bounds, which is undefined behavior.
- **Output order:** `unordered_map` iterates in arbitrary order. The problem accepts any order, but if you need stable output, sort the groups or use `map`.
- **Pass by reference:** the signature takes `vector<string>&`, so nothing is copied. These solutions don't modify the input.

---

## Edge Cases and Pitfalls

- **Empty string** (`[""]`): the count is all zeros, so it gets its own group. Result is `{{""}}`. Multiple empty strings group together.
- **Single string:** returns a single group containing it.
- **No anagrams:** every word is its own group.
- **All identical words:** one group containing all of them.
- **Missing delimiter** in the string-encoded key: the classic bug described above.
- **Bad keys:** using the sum of character codes as a key is wrong, because different words can share a sum (for example `"ad"` and `"bc"`).
- **Lowercase only:** for uppercase, digits or Unicode, use the sorted string key, or size the count array to 256 (or use a map of counts).
- **Forgetting to sort in the sorted-key version:** sort a **copy** (`string key = s;`), not `s` itself, or the output strings come back rearranged.

---

## Interview Follow-Ups

- **"Can you do better than sorting each word?"** Yes, use the count key, giving O(n x k).
- **"What if the strings contain Unicode or uppercase letters?"** Use the sorted string key, or a count map keyed by character.
- **"What if the dataset is too large for memory?"** Hash each word's key to a bucket, spill buckets to disk, and group each bucket independently, which is a map-reduce style approach.
- **"What if words arrive as a stream?"** Keep the hash map and append to a group as each word arrives. Each insertion is O(k).
- **"Could you shrink the key?"** Use the fixed 26-character key (approach 3b), or a custom hash over the counts.
- **"Return groups sorted?"** Sort each group, and optionally sort the groups, adding O(n x k log n) or so.

---

## Related Problems

- **242. Valid Anagram:** the single-pair version of the same idea
- **438. Find All Anagrams in a String:** sliding window with a frequency count
- **567. Permutation in String:** sliding window with a frequency count
- **760. Find Anagram Mappings:** value to index mapping
- **2273. Find Resultant Array After Removing Anagrams:** adjacent anagram check
- **205. Isomorphic Strings:** canonical form or pattern mapping
- **890. Find and Replace Pattern:** canonical pattern as key
- **1. Two Sum:** the same hash map lookup mindset

---
